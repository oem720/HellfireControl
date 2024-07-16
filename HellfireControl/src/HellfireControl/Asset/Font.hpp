#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Asset/Asset.hpp>

class Texture;

enum FontType : uint8_t {
	FONT_BITMAP = 0,
	FONT_SINGLE_CHANNEL_SDF = 1,
	FONT_MULTI_CHANNEL_SDF = 2
};

class Font : public Asset {
private:
	

public:
	~Font();

	friend class FontProcessor;
};