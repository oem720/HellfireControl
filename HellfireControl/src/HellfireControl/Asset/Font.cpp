
#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Asset/Converters/Font/FontCommon.hpp>

Font::~Font() {
	//TODO: Bitmap textures must be removed from VRAM
}

void Font::Initialize() {
	//TODO: Bitmap textures must be submitted to the GPU and the character map must be prepped for rendering.
}

std::shared_ptr<Asset> FontParser::Parse(File& _fAssetFile) const {
	std::shared_ptr<Font> pFontAsset = std::make_shared<Font>();

	_fAssetFile.GoToStart();

	HCGRFHeader gHeader;
	HCGRFTableDirectoryEntry tdeCMap;
	HCGRFTableDirectoryEntry tdeUVBV;
	HCGRFTableDirectoryEntry tdeImag;

	_fAssetFile.Read(&gHeader, sizeof(HCGRFHeader));

	//TODO: Check for compression!
	pFontAsset->m_ftType = GetTypeFromFlags(gHeader.m_u8Flags);

	if (pFontAsset->m_ftType & FontType::FONT_INVALID) {
		std::cout << "WARNING: Font invalid! Name: " << _fAssetFile.GetFileName() << std::endl;
		return nullptr;
	}

	//TODO: Check for the optional table!
	_fAssetFile.Read(&tdeCMap, sizeof(HCGRFTableDirectoryEntry));
	_fAssetFile.Read(&tdeUVBV, sizeof(HCGRFTableDirectoryEntry));
	_fAssetFile.Read(&tdeImag, sizeof(HCGRFTableDirectoryEntry));

	pFontAsset->m_mCharacterMap = GetCharacterMap(_fAssetFile, tdeCMap.m_u32Offset, tdeUVBV.m_u32Offset, 0); //TODO: Handle optional table!
	pFontAsset->m_vAtlases = GetAtlases(_fAssetFile, tdeImag.m_u32Offset);

	return pFontAsset;
}

FontType FontParser::GetTypeFromFlags(uint8_t _u8Flags) const {
	if (_u8Flags & IS_MULTI_CHANNEL) {
		return FontType::FONT_MULTI_CHANNEL_SDF;
	}

	if (_u8Flags & IS_SINGLE_CHANNEL) {
		return FontType::FONT_SINGLE_CHANNEL_SDF;
	}

	if (_u8Flags & IS_BITMAP) {
		return FontType::FONT_BITMAP;
	}

	return FontType::FONT_INVALID;
}

std::map<UTF8PaddedChar, BakedGlyphBoxInfo> FontParser::GetCharacterMap(File& _fFontFile, uint32_t _u32CMapOffset, uint32_t _u32UVBVOffset, uint32_t _u32GASTOffset) const {
	if (_u32GASTOffset != 0) {
		//TODO: Handle optional Glyph Assembly Table!
	}

	_fFontFile.GoToByte(_u32UVBVOffset);

	uint32_t u32VolumeCount;
	_fFontFile.Read(&u32VolumeCount, sizeof(uint32_t));

	std::vector<BakedGlyphBoxInfo> vGlyphInfo(u32VolumeCount);
	_fFontFile.Read(vGlyphInfo.data(), sizeof(BakedGlyphBoxInfo) * u32VolumeCount);

	_fFontFile.GoToByte(_u32CMapOffset);

	uint32_t u32SegmentCount;
	_fFontFile.Read(&u32SegmentCount, sizeof(uint32_t));

	std::vector<HCGRFCMapEntry> vSegments(u32SegmentCount);
	_fFontFile.Read(vSegments.data(), sizeof(HCGRFCMapEntry) * u32SegmentCount);

	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> mCMap;
	for (const auto& aSegment : vSegments) {
		uint32_t u32EndCode = aSegment.m_u32StartCode + aSegment.m_u32CodeCount;
		for (UTF8PaddedChar cCode = aSegment.m_u32StartCode, u32Index = aSegment.m_u32GlyphIndex; cCode < u32EndCode; ++cCode, ++u32Index) {
			mCMap[cCode] = vGlyphInfo[u32Index];
		}
	}

	return mCMap;
}

std::vector<ImageRGB8> FontParser::GetAtlases(File& _fFontFile, uint32_t _u32ImagOffset) const {
	_fFontFile.GoToByte(_u32ImagOffset);

	std::vector<ImageRGB8> vAtlases;

	while (!_fFontFile.AtEOF()) {
		HCGRFImageDescriptor idImage;

		_fFontFile.Read(&idImage, sizeof(HCGRFImageDescriptor));

		uint32_t u32ImageBytes = idImage.m_u32ImageWidth * idImage.m_u32ImageHeight * idImage.m_u8NumChannels;

		ImageRGB8 iAtlas(idImage.m_u32ImageWidth, idImage.m_u32ImageHeight);

		_fFontFile.Read(iAtlas.GetPixelData().get(), u32ImageBytes);

		vAtlases.push_back(std::move(iAtlas));
	}

	return vAtlases;
}
