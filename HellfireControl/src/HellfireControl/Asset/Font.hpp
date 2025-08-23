#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

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
};