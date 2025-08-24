#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

struct FontInfo;
struct GlyphInfo;

class FontRasterizer {
public:
	static std::map<UTF8PaddedChar, BakedGlyphBoxInfo> RasterizeGlyphs(const FontInfo& _fiInfo, const std::map<UTF8PaddedChar, GlyphInfo>& _mGlyphData, std::vector<ImageRGB8>& _vImages, const std::string& _strFilePathTEMP);
private:

};