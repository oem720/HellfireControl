#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Asset/Asset.hpp>
#include <HellfireControl/Asset/Texture.hpp>

class Font : public Asset {
	friend class FontProcessor;

private:
	struct Glyph {
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		int originX = 0;
		int originY = 0;
	};

	std::map<char8_t, Glyph> m_mGlyphMap;

	std::unique_ptr<Texture> m_texSDF;

	Font() = delete;

	Font(const std::vector<uint8_t>& _vData, std::unique_ptr<Texture> m_texSDF);
public:
	~Font();
};