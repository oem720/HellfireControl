#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

enum FontType : uint8 {
	FONT_BITMAP = 0,
	FONT_SINGLE_CHANNEL_SDF = 1,
	FONT_MULTI_CHANNEL_SDF = 2,
	FONT_INVALID = 0xFF
};

class Font : public Asset {
private:
	FontType m_ftType = FontType::FONT_BITMAP;
	Array<ImageRGB8> m_vAtlases;
	Map<UTF8PaddedChar, BakedGlyphBoxInfo> m_mCharacterMap;
public:
	~Font();

	void Init();

	friend class FontProcessor;
	friend class FontParser;
};

class FontParser : public AssetParser {
public:
	Shared<Asset> Parse(File& _fAssetFile) const;

private:
	FontType GetTypeFromFlags(uint8 _u8Flags) const;
	Map<UTF8PaddedChar, BakedGlyphBoxInfo> GetCharacterMap(File& _fFontFile, uint32 _u32CMapOffset, uint32 _u32UVBVOffset, uint32 _u32GASTOffset = 0) const;
	Array<ImageRGB8> GetAtlases(File& _fFontFile, uint32 _u32ImagOffset) const;
};