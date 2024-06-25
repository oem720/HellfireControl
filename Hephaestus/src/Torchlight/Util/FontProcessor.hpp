#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/File.hpp>
#include <HellfireControl/Math/Math.hpp>

#include <Windows.h>
#include <gdiplus.h>

class Font;

class FontProcessor {
public:
	static void ProcessFont(const std::string& _strFilepath);
private:
	template<typename T, HC_SFINAE_REQUIRE_INTEGER(T)>
	static T ReadTTFValue(File& _fFile) {
		T value = 0;
		_fFile >> value;
		Util::ReverseBytes(value);

		return value;
	}

	//TrueType Data Types
	typedef int16_t ShortFrac;		//Signed fraction
	typedef int32_t FixedPoint;		//Signed 16.16 Fixed Point
	typedef int16_t FWord;			//Signed integer in FUnits, smallest distance in em space
	typedef uint16_t uFWord;		//Unsigned FWord
	typedef int16_t F2Dot14;		//16 bit signed fixed point number stored as 2.14
	typedef int64_t LongDateTime;	//Date in seconds from 12:00 Midnight, January 1st 1904.
	
	struct TTFPoint {
		int16_t x = _I16_MIN;
		int16_t y = _I16_MIN;
		bool onCurve = false;
		float pointNumber = -1.0f;

		bool IsValid() const {
			return x != _I16_MIN && y != _I16_MIN;
		}
	};

	struct TTFCurve {
		union {
			TTFPoint m_arrPoints[3];

			struct {
				TTFPoint m_p0;
				TTFPoint m_p1;
				TTFPoint m_p2;
			};
		};

		bool IsValid() const {
			return m_p0.IsValid() && m_p1.IsValid() && m_p2.IsValid();
		}

		int GetMinYIndex() const {
			return m_p0.y < m_p2.y ? 0 : 2;
		}

		bool IsHorizontal() const {
			return m_p0.y == m_p1.y && m_p1.y == m_p2.y;
		}
	};
		
	struct TTFContour {
		std::vector<TTFCurve> m_vCurves;
		bool m_bIsHole = false;
	};

	struct TTFEdgeTableEntry {
		Vec2F m_vec2Min;
		Vec2F m_vec2ControlPoint;
		Vec2F m_vec2Max;

		float m_fCurrentX;

		bool m_bDownward;

		bool m_bHoleEdge;
	};

	struct TTFGlyphDescriptor {
		int16_t m_i16ContourCount;
		FWord m_fXMin;
		FWord m_fYMin;
		FWord m_fXMax;
		FWord m_fYMax;
	};

	class TTFGlyph {
		//This is a hack to have an interface for holding glyph data. This will allow
		//the function that parses glyphs to return a list of glyph data without caring
		//what kind of glyph data is contained within.
	public:
		virtual ~TTFGlyph() = 0 {};
	};

	class TTFSimpleGlyph final : public TTFGlyph {
	public:
		//std::vector<uint8_t> m_vInstructions;
		std::vector<TTFContour> m_vContours;

		virtual ~TTFSimpleGlyph() {}
	};

	class TTFCompoundGlyph final : public TTFGlyph {
	public:
		union TTFCompoundGlyphArg {
			union {
				int16_t i16;
				uint16_t u16;
			};

			union {
				int8_t i8;
				uint8_t u8;
			};
		};

		uint16_t m_u16Flags = 0;
		uint16_t m_u16GlyphIndex = 0;
		TTFCompoundGlyphArg m_cgaArgument1 = { .i16 = 0 };
		TTFCompoundGlyphArg m_cgaArgument2 = { .i16 = 0 };

		virtual ~TTFCompoundGlyph() {}
	};

	typedef std::pair<TTFGlyphDescriptor, std::unique_ptr<TTFGlyph>> TTFGlyphData; //This alias joins the two blocks of glyph data together

	static void GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations);
	static void GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations, uint16_t& _u16OutPixelsPerEm);
	static void ParseGlyph(File& _fFontFile, TTFGlyphData& _gdOutGlyphData);
	static std::unique_ptr<TTFSimpleGlyph> ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, uint32_t _u32MinX, uint32_t _u32MinY);
	static std::unique_ptr<TTFCompoundGlyph> ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount);
	static void ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, bool bIsX, std::vector<TTFPoint>& _vOutCoordinates, uint32_t _u32MinX, uint32_t _u32MinY);
	static int GetPointOffset(const std::vector<TTFPoint>& _vPoints);
	static void RecreateImpliedPoints(std::vector<TTFPoint>& _vPoints, int _iPointOffset);
	static void MakeContourCurvesMonotonic(TTFContour& _tContour);
	static std::vector<TTFPoint> SplitCurveAtTurningPoint(const TTFCurve& _tCurve);
	static void CheckContourContained(TTFContour& _tContour, const TTFContour& _tPossibleOuter);
	static bool CheckCurveOutlineIntersection(const TTFContour& _tContourA, const TTFContour& _tContourB);
	static bool CheckPointInContour(const TTFPoint& _tPoint, const TTFContour& _tPossibleOuter);
	static bool CheckLineIntersection(const TTFCurve& _tCurveA, const TTFCurve& _tCurveB);

	static void CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, uint16_t _u16PixelsPerEm);
	static void FlipImageVertically(std::vector<uint32_t>& _vBitmap, uint32_t _u32Width, uint32_t _u32Height);

	static PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	static void CreateBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	static void SaveToFile(std::vector<uint32_t>& _vBitmap, uint32_t _u32BitmapWidth, uint32_t _u32BitmapHeight, int _iGlyphNumber);

	static void PlotPixel(std::vector<uint32_t>& _vBitmap, int _iX, int _iY, uint32_t _u32Color, uint32_t _u32RowLength);
	static void DrawPoint(std::vector<uint32_t>& _vBitmap, TTFPoint _pPosition, uint32_t _u32Width, uint32_t _u32Height, uint32_t _u32Color);
	static void DrawBresenhamLine(std::vector<uint32_t>& _vBitmap, TTFPoint _pStart, TTFPoint _pEnd, uint32_t _u32Color, uint32_t _u32RowLength);
	static void DrawBezierCurve(std::vector<uint32_t>& _vBitmap, TTFPoint _pStart, TTFPoint _pControl, TTFPoint _pEnd, uint32_t _u32Color, int _iResolution, uint32_t _u32RowLength);
	static void FillGlyph(std::vector<uint32_t>& _vBitmap, uint16_t _u16Width, uint16_t _u16Height, uint32_t _u32Color, std::vector<TTFContour>& _vAllContours);
	static void RasterizeContour(std::vector<uint32_t>& _vBitmap, const TTFContour& _tContour, uint16_t _u16Width, uint16_t _u16Height, uint32_t _u32Color);

	static TTFPoint BezierInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT);
	static Vec2F BezierInterpolation(Vec2F _v0, Vec2F _v1, Vec2F _v2, float _fT);
	static float QuadraticInterpolation(float _f0, float _f1, float _f2, float _fT);
};