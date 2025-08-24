#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

enum FontType : uint8_t {
	FONT_BITMAP = 0,
	FONT_SINGLE_CHANNEL_SDF = 1,
	FONT_MULTI_CHANNEL_SDF = 2,
	FONT_INVALID = 0xFF
};

class Font : public Asset {
private:
	FontType m_ftType = FontType::FONT_BITMAP;
	std::vector<ImageRGB8> m_vAtlases;
	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> m_mCharacterMap;
public:
	~Font();

	void Initialize();

	friend class FontProcessor;
	friend class FontParser;
};

class FontParser : public AssetParser {
public:
	std::shared_ptr<Asset> Parse(File& _fAssetFile) const;

private:
	FontType GetTypeFromFlags(uint8_t _u8Flags) const;
	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> GetCharacterMap(File& _fFontFile, uint32_t _u32CMapOffset, uint32_t _u32UVBVOffset, uint32_t _u32GASTOffset = 0) const;
	std::vector<ImageRGB8> GetAtlases(File& _fFontFile, uint32_t _u32ImagOffset) const;
};