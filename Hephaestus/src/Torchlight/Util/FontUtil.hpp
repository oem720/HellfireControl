#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/File.hpp>

#include <Torchlight/Util/FontTypes.hpp>

//For testing font glyphs individually. Will only work on windows machines.
#define HC_TESTING_FONT_GLYPH_RASTERIZATION 1 

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
#include <Windows.h>
#include <gdiplus.h>
#endif

namespace FontUtil {
	template<typename T, HC_SFINAE_REQUIRE_INTEGER(T)>
	static HC_INLINE T ReadTTFValue(File& _fFile) {
		T value = 0;
		_fFile >> value;
		Util::ReverseBytes(value);

		return value;
	}

	template<typename T, HC_SFINAE_REQUIRE_FLOATING_POINT(T)>
	static HC_INLINE T ConvertToFloatingPoint(F2Dot14 _fixed) {
		return static_cast<T>(_fixed) / static_cast<T>(1 << 14);
	}

	TTFPoint QuadraticInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT);
	Vec2F QuadraticInterpolation(Vec2F _v0, Vec2F _v1, Vec2F _v2, float _fT);
	float QuadraticInterpolation(float _f0, float _f1, float _f2, float _fT);
	float GetQuadraticX(float _f0, float _f1, float _f2, float _fY);
	void QuadraticFormula(float _fA, float _fB, float _fC, Vec2F& _v2Roots);
	std::map<UTF8PaddedChar, int> ReadTTFFormat0(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat2(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat4(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat6(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat8(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat10(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat12(File& _fFontFile);
	std::map<UTF8PaddedChar, int> ReadTTFFormat13(File& _fFontFile);

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	void CreateBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	void SaveToFile(const TTFBitmap& _tBitmap, int _iGlyphNumber);
#endif
}