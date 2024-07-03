#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Vector.hpp>

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

	bool IsCollinear() const {
		return (m_p1.y - m_p0.y) * (m_p2.x - m_p1.x) == (m_p2.y - m_p1.y) * (m_p1.x - m_p0.x);
	}
};

struct TTFContour {
	std::vector<TTFCurve> m_vCurves;
};

struct TTFEdgeTableEntry {
	Vec2F m_vec2Min;
	Vec2F m_vec2ControlPoint;
	Vec2F m_vec2Max;

	float m_fCurrentX;

	bool m_bDownward;
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

struct TTFBitmap {
	uint32_t* m_pPixels;
	uint32_t m_u32Width;
	uint32_t m_u32Height;
	uint32_t m_u32ArraySize;

	TTFBitmap() = delete;

	TTFBitmap(uint32_t _u32Width, uint32_t _u32Height) : m_u32Width(_u32Width), m_u32Height(_u32Height), m_u32ArraySize(_u32Width* _u32Height) {
		m_pPixels = new uint32_t[m_u32ArraySize](0x0);
	}

	~TTFBitmap() {
		delete[] m_pPixels;
	}

	void PlotPixel(int _iX, int _iY, uint32_t _u32Color);

	void FlipImageVertically();
};