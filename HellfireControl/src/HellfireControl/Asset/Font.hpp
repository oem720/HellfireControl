#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Image.hpp>

#include <HellfireControl/Math/Vector.hpp>

#include <HellfireControl/Asset/Asset.hpp>

enum FontType : uint8_t {
	FONT_BITMAP = 0,
	FONT_SINGLE_CHANNEL_SDF = 1,
	FONT_MULTI_CHANNEL_SDF = 2
};

struct FontGlyphBox {
	Vec4F m_v4BoundingBox = Vec4F();
	float m_fAdvanceWidth = 0.0f;
	float m_fHorizontalShift = 0.0f;
	float m_fVerticalShift = 0.0f;
	uint32_t m_u32AtlasIndex = 0;
};

class Font : public Asset {
private:
	FontType m_ftType = FontType::FONT_BITMAP;
	std::vector<ImageRGB8> m_vAtlases;
	std::map<UTF8PaddedChar, FontGlyphBox> m_mCharacterMap;
public:

	friend class FontProcessor;
};