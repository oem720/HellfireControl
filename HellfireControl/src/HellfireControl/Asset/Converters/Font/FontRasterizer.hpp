#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Image.hpp>

struct FontInfo;
struct GlyphInfo;

class FontRasterizer {
public:
	static Map<UTF8PaddedChar, BakedGlyphBoxInfo> RasterizeGlyphs(const FontInfo& _fiInfo, const Map<UTF8PaddedChar, GlyphInfo>& _mGlyphData, Array<ImageRGB8>& _vImages, const String& _strFilePathTEMP);
private:

};