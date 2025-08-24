#include <HellfireControl/Asset/Converters/Font/FontRasterizer.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Asset/Converters/Font/FontParser.hpp>

#define STB_TRUETYPE_IMPLEMENTATION
#include <External/stb/stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <External/stb/stb_image_write.h>

#define HC_MISSING_CHAR_GLYPH_INDEX 65535

Vec2F GetFontAtlasSize(const FontInfo& fiInfo, const std::vector<GlyphInfo>& vGlyphData)
{
	Vec2F v2GlyphSize;
	for (const auto& aGlyph : vGlyphData) {
		v2GlyphSize += (aGlyph.m_v2Max - aGlyph.m_v2Min) * fiInfo.m_fScaleFactor;
	}

	v2GlyphSize /= vGlyphData.size();

	uint32_t u32RowCount = static_cast<uint32_t>(Math::Ceiling(Math::Sqrt(static_cast<float>(vGlyphData.size()))));
	uint32_t u32ColCount = static_cast<uint32_t>(Math::Ceiling(vGlyphData.size() / static_cast<float>(u32RowCount)));

	uint32_t u32Width = static_cast<uint32_t>(Math::Ceiling(u32ColCount * v2GlyphSize.x));
	uint32_t u32Height = static_cast<uint32_t>(Math::Ceiling(u32RowCount * v2GlyphSize.y));

	if (u32Width < u32Height) {
		u32Width = u32Width ^ u32Height;
		u32Height = u32Width ^ u32Height;
		u32Width = u32Width ^ u32Height;
	}

	return Vec2F(static_cast<float>(u32Width), static_cast<float>(u32Height));
}

std::map<UTF8PaddedChar, BakedGlyphBoxInfo> FontRasterizer::RasterizeGlyphs(const FontInfo& _fiInfo, const std::map<UTF8PaddedChar, GlyphInfo>& _mGlyphData, std::vector<ImageRGB8>& _vImages, const std::string& _strFilePathTEMP) {
	//TODO: At the moment, this whole function is designed to hack in all the ASCII characters + missing char glyph.
	//This then goes into a single bitmap image using STB's truetype implementation. This is incorrect for various reasons.
	//Future implementation will require that we draw all of the glyphs given, and into pre-defined segments.
	std::vector<GlyphInfo> vGlyphsToRender;
	
	for (UTF8PaddedChar u8Char = 31; u8Char < 127; ++u8Char) {
		if (_mGlyphData.find(u8Char) == _mGlyphData.end()) {
			vGlyphsToRender.push_back(_mGlyphData.at(HC_MISSING_CHAR_GLYPH_INDEX));
		}
		else {
			vGlyphsToRender.push_back(_mGlyphData.at(u8Char));
		}
	}

	Vec2F v2ImageSize = GetFontAtlasSize(_fiInfo, vGlyphsToRender);

	//TEMPORARY SO WE CAN USE STB, VERY HORRIFYING HACKS UP AHEAD
	ImageR8 iBitmap(static_cast<uint32_t>(v2ImageSize.x), static_cast<uint32_t>(v2ImageSize.y));

	File fFile(_strFilePathTEMP, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY | FILE_OPEN_FLAG_BEGIN_AT_END);

	stbtt_bakedchar* pData = new stbtt_bakedchar[96];

	stbtt_BakeFontBitmap(fFile.ExtractFileBlob().data(), 0, _fiInfo.m_fFontSize, reinterpret_cast<unsigned char*>(iBitmap.GetPixelData().get()), iBitmap.GetWidth(), iBitmap.GetHeight(), 31, 96, pData);

	stbi_write_bmp("./Assets/Fonts/TestOutput/TestImage.bmp", iBitmap.GetWidth(), iBitmap.GetHeight(), 1, iBitmap.GetPixelData().get());

	std::map<UTF8PaddedChar, BakedGlyphBoxInfo> mBakedData;

	for (UTF8PaddedChar u8Char = 31; u8Char < 127; ++u8Char) {
		stbtt_bakedchar bcBounds = pData[u8Char - 31];

		mBakedData[u8Char] = {
			.m_v4BoundingBox = Vec4F(bcBounds.x0, bcBounds.y0, bcBounds.x1, bcBounds.y1),
			.m_fAdvanceWidth = bcBounds.xadvance,
			.m_fHorizontalShift = bcBounds.xoff,
			.m_fVerticalShift = bcBounds.yoff,
			.m_u32AtlasIndex = 0,
		};
	}

	delete[] pData;

	ImageRGB8 iFinalBitmap(static_cast<uint32_t>(v2ImageSize.x), static_cast<uint32_t>(v2ImageSize.y));

	for (int x = 0; x < iBitmap.GetWidth(); ++x) {
		for (int y = 0; y < iBitmap.GetHeight(); ++y) {
			uint8_t u8Color = iBitmap.GetPixel(x, y).m_arrChannelValues[0];

			iFinalBitmap.PlotPixel(x, y, { u8Color, u8Color, u8Color });
		}
	}

	_vImages.push_back(std::move(iFinalBitmap));
	
	return mBakedData;
}
