#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

class Font : public Asset {
private:
	FontType m_ftType = FontType::FONT_BITMAP;
	std::vector<ImageRGB8> m_vAtlases;
	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> m_mCharacterMap;
public:

	friend class FontProcessor;
};