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
	static T ReadTTFValue(File& _fFile) {
		T value = 0;
		_fFile >> value;
		Util::ReverseBytes(value);

		return value;
	}

	int GetPointOffset(const std::vector<TTFPoint>& _vPoints);
	void RecreateImpliedPoints(std::vector<TTFPoint>& _vPoints, int _iPointOffset);
	void MakeContourCurvesMonotonic(TTFContour& _tContour);
	std::vector<TTFPoint> SplitCurveAtTurningPoint(const TTFCurve& _tCurve);

	TTFPoint QuadraticInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT);
	Vec2F QuadraticInterpolation(Vec2F _v0, Vec2F _v1, Vec2F _v2, float _fT);
	float QuadraticInterpolation(float _f0, float _f1, float _f2, float _fT);
	float GetQuadraticX(float _f0, float _f1, float _f2, float _fY);
	void QuadraticFormula(float _fA, float _fB, float _fC, Vec2F& _v2Roots);

	void DrawPoint(TTFBitmap& _bBitmap, int _iX, int _iY, uint32_t _u32Color);
	void DrawLine(TTFBitmap& _bBitmap, int _iX0, int _iY0, int _iX1, int _iY1, uint32_t _u32Color);
	void DrawBezier(TTFBitmap& _bBitmap, const TTFPoint& _p0, const TTFPoint& _p1, const TTFPoint& _p2, int _iResolution, uint32_t _u32Color);
	void DrawGlyph(TTFBitmap& _bBitmap, std::vector<TTFContour>& _vAllContours, uint32_t _u32Color);

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	void CreateBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	void SaveToFile(const TTFBitmap& _tBitmap, int _iGlyphNumber);
#endif
}