
#include <HellfireControl/Asset/Converters/Font/FontProcessor.hpp>

#include <HellfireControl/Asset/Converters/Font/FontParser.hpp>
#include <HellfireControl/Asset/Converters/Font/FontRasterizer.hpp>

#include <HellfireControl/Asset/AssetManifest.hpp>

#include <HellfireControl/Core/Image.hpp>

Font FontProcessor::ProcessFont(const String& _strFilepath, uint16 _u16FontSize, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);

	FontInfo fiInfo = FontTTFParser::InitializeFont(fFontFile, static_cast<float>(_u16FontSize));

	Map<UTF8PaddedChar, GlyphInfo> mGlyphData;

	uint16 spaceIndex = fiInfo.m_cmCMap[static_cast<UTF8PaddedChar>(' ')];

	for (const auto& aGlyphPair : fiInfo.m_cmCMap) {
		mGlyphData[aGlyphPair.first] = FontTTFParser::GetGlyphInfo(fFontFile, fiInfo, aGlyphPair.second);
	}

	Array<ImageRGB8> vBitmaps;
	Map<UTF8PaddedChar, BakedGlyphBoxInfo> mBakedData = FontRasterizer::RasterizeGlyphs(fiInfo, mGlyphData, vBitmaps, _strFilepath);

	Font fFont;
	fFont.m_ftType = _ftType;
	fFont.m_mCharacterMap = mBakedData;
	fFont.m_vAtlases = std::move(vBitmaps);

	return fFont;
}

Font FontProcessor::ProcessFont(const String& _strFilepath, CharacterRange _crCharactersToProcess, uint16 _u16FontSize, FontType _ftType) {
	//TODO: Implement
	return Font();
}

Font FontProcessor::ProcessFont(const String& _strFilepath, Array<CharacterRange>& _vCharacterRanges, uint16 _u16FontSize, FontType _ftType) {
	//TODO: Implement
	return Font();
}

void OrderBoundingVolumes(Map<UTF8PaddedChar, BakedGlyphBoxInfo>& _mMap, Array<HCGRFCMapEntry>& _vOutMap, Array<BakedGlyphBoxInfo>& _vOutOrderedBVs);

HCUID FontProcessor::SaveFontToDisk(const String& _strFilepath, const Font& _fFontData) {
	File fFileDest(_strFilepath, FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_BINARY);

	HCGRFHeader hHeader = {
		.m_u32MagicNumber = HC_FONT_IDENTIFIER,
		.m_u16Version = HC_FILE_FORMAT_VERSION_NUMBER(0, 1),
		.m_u8Flags = IS_BITMAP,
		.m_u8DirectorySize = 3
	};

	Map<UTF8PaddedChar, BakedGlyphBoxInfo> mCharacterMapCopy = _fFontData.m_mCharacterMap;
	Array<HCGRFCMapEntry> vCMap;
	Array<BakedGlyphBoxInfo> vOrderedBVs;
	OrderBoundingVolumes(mCharacterMapCopy, vCMap, vOrderedBVs);
	uint32 u32SegmentCount = vCMap.size();
	uint32 u32BoundingVolumeCount = vOrderedBVs.size();

	//TODO: Change this to be based on the settings of the font. This may include the GAST table as well.
	HCGRFTableDirectoryEntry tdeCmap = { .m_cTag = {'c', 'm', 'a', 'p'}, .m_u32Offset = sizeof(HCGRFHeader) + (sizeof(HCGRFTableDirectoryEntry) * 3) };
	HCGRFTableDirectoryEntry tdeUvbv = { .m_cTag = {'u', 'v', 'b', 'v'}, .m_u32Offset = tdeCmap.m_u32Offset + static_cast<uint32>(vCMap.size() * sizeof(HCGRFCMapEntry)) + sizeof(uint32)};
	HCGRFTableDirectoryEntry tdeImag = { .m_cTag = {'i', 'm', 'a', 'g'}, .m_u32Offset = tdeUvbv.m_u32Offset + static_cast<uint32>(vOrderedBVs.size() * sizeof(BakedGlyphBoxInfo)) + sizeof(uint32) };

	fFileDest.Write(&hHeader, sizeof(HCGRFHeader));
	fFileDest.Write(&tdeCmap, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(&tdeUvbv, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(&tdeImag, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(&u32SegmentCount, sizeof(uint32));
	fFileDest.Write(vCMap.data(), sizeof(HCGRFCMapEntry) * vCMap.size());
	fFileDest.Write(&u32BoundingVolumeCount, sizeof(uint32));
	fFileDest.Write(vOrderedBVs.data(), sizeof(BakedGlyphBoxInfo) * vOrderedBVs.size());
	
	for (const ImageRGB8& aImage : _fFontData.m_vAtlases) {
		HCGRFImageDescriptor idImageHeader = {
			.m_u32ImageWidth = aImage.GetWidth(),
			.m_u32ImageHeight = aImage.GetHeight(),
			.m_u8NumChannels = aImage.GetChannels()
		};

		fFileDest.Write(&idImageHeader, sizeof(uint32) * 2 + sizeof(uint8)); //Thanks to alignment, this has to be calculated manually
		fFileDest.Write(aImage.GetPixelData().get(), sizeof(ImageRGB8::Pixel) * aImage.GetPixelCount());
	}

	fFileDest.Close();

	HCUID gId = HCUID::ConstructFromFilepath(_strFilepath);

	AssetManifest::GetInstance()->SetManifestEntry(gId, _strFilepath);

	return gId;
}

void OrderBoundingVolumes(Map<UTF8PaddedChar, BakedGlyphBoxInfo>& _mMap, Array<HCGRFCMapEntry>& _vOutMap, Array<BakedGlyphBoxInfo>& _vOutOrderedBVs) {
	HCGRFCMapEntry cmeEntry = { .m_u32CodeCount = 0 };
	
	for (UTF8PaddedChar u8Char = 0; u8Char < UINT32_MAX && _mMap.size() > 0; ++u8Char) {
		if (_mMap.contains(u8Char)) {
			_vOutOrderedBVs.push_back(_mMap.at(u8Char));
			_mMap.erase(u8Char);

			if (cmeEntry.m_u32CodeCount == 0) {
				cmeEntry = {
					.m_u32StartCode = u8Char,
					.m_u32CodeCount = 1,
					.m_u32GlyphIndex = static_cast<uint32>(_vOutOrderedBVs.size()) - 1
				};
			}
			else {
				cmeEntry.m_u32CodeCount++;
			}
		}
		else if (cmeEntry.m_u32CodeCount != 0) {
			_vOutMap.push_back(cmeEntry);
			cmeEntry.m_u32CodeCount = 0;
		}
	}

	if (cmeEntry.m_u32CodeCount != 0) {
		_vOutMap.push_back(cmeEntry);
	}
}