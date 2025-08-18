
#include <HellfireControl/Asset/Converters/Font/FontProcessor.hpp>

#include <HellfireControl/Asset/Converters/Font/FontParser.hpp>
#include <HellfireControl/Asset/Converters/Font/FontRasterizer.hpp>

#include <HellfireControl/Core/Image.hpp>

Font FontProcessor::ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);

	FontInfo fiInfo = FontParser::InitializeFont(fFontFile, static_cast<float>(_u16FontSize));

	std::map<UTF8PaddedChar, GlyphInfo> mGlyphData;

	for (const auto& aGlyphPair : fiInfo.m_cmCMap) {
		mGlyphData[aGlyphPair.first] = FontParser::GetGlyphInfo(fFontFile, fiInfo, aGlyphPair.second);
	}

	std::vector<ImageRGB8> vBitmaps;
	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> mBakedData = FontRasterizer::RasterizeGlyphs(fiInfo, mGlyphData, vBitmaps, _strFilepath);

	Font fFont;
	fFont.m_ftType = _ftType;
	fFont.m_mCharacterMap = mBakedData;
	fFont.m_vAtlases = std::move(vBitmaps);

	return fFont;
}

Font FontProcessor::ProcessFont(const std::string& _strFilepath, CharacterRange _crCharactersToProcess, uint16_t _u16FontSize, FontType _ftType) {
	//TODO: Implement
	return Font();
}

Font FontProcessor::ProcessFont(const std::string& _strFilepath, std::vector<CharacterRange>& _vCharacterRanges, uint16_t _u16FontSize, FontType _ftType) {
	//TODO: Implement
	return Font();
}

enum HCGRFFlags : uint8_t {
	IS_COMPRESSED = (1 << 0),
	IS_BITMAP = (1 << 1),
	IS_SINGLE_CHANNEL = (1 << 2),
	IS_MULTI_CHANNEL = (1 << 3),
	SEGMENTED_ATLAS = (1 << 4)
};

constexpr uint32_t HC_GRF_MAGIC_NUMBER = 1179797320U;

struct HCGRFHeader {
	uint32_t m_u32MagicNumber;
	uint16_t m_u16Version;
	uint8_t m_u8Flags;
	uint8_t m_u8DirectorySize;
};

struct HCGRFTableDirectoryEntry {
	char m_cTag[4];
	uint32_t m_u32Offset;
};

struct HCGRFCMapEntry {
	uint32_t m_u32StartCode;
	uint32_t m_u32CodeCount;
	uint32_t m_u32GlyphIndex;
};

struct HCGRFImageDescriptor {
	uint32_t m_u32ImageWidth;
	uint32_t m_u32ImageHeight;
	uint8_t m_u8NumChannels;
};

void OrderBoundingVolumes(std::map<UTF8PaddedChar, BakedGlyphBoxInfo>& _mMap, std::vector<HCGRFCMapEntry>& _vOutMap, std::vector<BakedGlyphBoxInfo>& _vOutOrderedBVs);

HCUID FontProcessor::SaveFontToDisk(const std::string& _strFilepath, const Font& _fFontData) {
	File fFileDest(_strFilepath, FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_BINARY);

	HCGRFHeader hHeader = {
		.m_u32MagicNumber = HC_GRF_MAGIC_NUMBER,
		.m_u16Version = HC_FILE_FORMAT_VERSION_NUMBER(0, 1),
		.m_u8Flags = IS_BITMAP,
		.m_u8DirectorySize = 3
	};

	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> mCharacterMapCopy = _fFontData.m_mCharacterMap;
	std::vector<HCGRFCMapEntry> vCMap;
	std::vector<BakedGlyphBoxInfo> vOrderedBVs;
	OrderBoundingVolumes(mCharacterMapCopy, vCMap, vOrderedBVs);

	//TODO: Change this to be based on the settings of the font. This may include the GAST table as well.
	HCGRFTableDirectoryEntry tdeCmap = { .m_cTag = {'c', 'm', 'a', 'p'}, .m_u32Offset = sizeof(HCGRFHeader) + (sizeof(HCGRFTableDirectoryEntry) * 3) };
	HCGRFTableDirectoryEntry tdeUvbv = { .m_cTag = {'u', 'v', 'b', 'v'}, .m_u32Offset = tdeCmap.m_u32Offset + static_cast<uint32_t>(vCMap.size() * sizeof(HCGRFCMapEntry)) };
	HCGRFTableDirectoryEntry tdeImag = { .m_cTag = {'i', 'm', 'a', 'g'}, .m_u32Offset = tdeUvbv.m_u32Offset + static_cast<uint32_t>(vOrderedBVs.size() * sizeof(BakedGlyphBoxInfo)) };

	fFileDest.Write(&hHeader, sizeof(HCGRFHeader));
	fFileDest.Write(&tdeCmap, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(&tdeUvbv, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(&tdeImag, sizeof(HCGRFTableDirectoryEntry));
	fFileDest.Write(vCMap.data(), sizeof(HCGRFCMapEntry) * vCMap.size());
	fFileDest.Write(vOrderedBVs.data(), sizeof(BakedGlyphBoxInfo) * vOrderedBVs.size());
	
	for (const ImageRGB8& aImage : _fFontData.m_vAtlases) {
		HCGRFImageDescriptor idImageHeader = {
			.m_u32ImageWidth = aImage.GetWidth(),
			.m_u32ImageHeight = aImage.GetHeight(),
			.m_u8NumChannels = aImage.GetChannels()
		};

		fFileDest.Write(&idImageHeader, sizeof(uint32_t) * 2 + sizeof(uint8_t)); //Thanks to alignment, this has to be calculated manually
		fFileDest.Write(aImage.GetPixelData().get(), sizeof(ImageRGB8::Pixel) * aImage.GetPixelCount());
	}

	fFileDest.Close();

	//TODO: Add this GUID to the asset manifest before returning it.
	return HCUID::ConstructFromFilepath(_strFilepath);
}

void OrderBoundingVolumes(std::map<UTF8PaddedChar, BakedGlyphBoxInfo>& _mMap, std::vector<HCGRFCMapEntry>& _vOutMap, std::vector<BakedGlyphBoxInfo>& _vOutOrderedBVs) {
	HCGRFCMapEntry cmeEntry = { .m_u32CodeCount = 0 };
	
	for (UTF8PaddedChar u8Char = 0; u8Char < UINT32_MAX && _mMap.size() > 0; ++u8Char) {
		if (_mMap.contains(u8Char)) {
			_vOutOrderedBVs.push_back(_mMap.at(u8Char));
			_mMap.erase(u8Char);

			if (cmeEntry.m_u32CodeCount == 0) {
				cmeEntry = {
					.m_u32StartCode = u8Char,
					.m_u32CodeCount = 1,
					.m_u32GlyphIndex = static_cast<uint32_t>(_vOutOrderedBVs.size()) - 1
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