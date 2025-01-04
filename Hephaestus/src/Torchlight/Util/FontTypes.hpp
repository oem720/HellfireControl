#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Vector.hpp>

//TrueType Data Types
typedef int16_t ShortFrac;		//Signed fraction
typedef int32_t FixedPoint;		//Signed 16.16 Fixed Point
typedef int16_t FWord;			//Signed integer in FUnits, smallest distance in em space
typedef uint16_t UFWord;		//Unsigned FWord
typedef int16_t F2Dot14;		//16 bit signed fixed point number stored as 2.14
typedef int64_t LongDateTime;	//Date in seconds from 12:00 Midnight, January 1st 1904.

typedef uint32_t UTF8PaddedChar;

struct TTFPoint {
	float x = NAN;
	float y = NAN;

	bool m_bOnCurve = false;

	bool IsValid() const {
		return x != NAN && y != NAN;
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

	TTFPoint operator[](uint8_t _u8Index) const { return m_arrPoints[_u8Index]; }
	TTFPoint& operator[](uint8_t _u8Index) { return m_arrPoints[_u8Index]; }
};

struct TTFContour {
	std::vector<TTFCurve> m_vCurves;
};

struct TTFEdge {
	TTFCurve m_cCurve;
	bool m_bDownward;
	float m_fCurrentX;
};

struct TTFGlyphDescriptor {
	int16_t m_i16ContourCount;
	float m_fXMin;
	float m_fYMin;
	float m_fXMax;
	float m_fYMax;
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
	std::vector<TTFContour> m_vContours;

	virtual ~TTFSimpleGlyph() {}
};

class TTFCompoundGlyph final : public TTFGlyph {
public:
	struct TTFCompoundGlyphArg {
		union {
			int16_t i16;
			uint16_t u16;
		};

		union {
			int8_t i8;
			uint8_t u8;
		};
	};

	struct TTFCompoundGlyphComponent {
		uint16_t m_u16GlyphIndex = 0;
		TTFCompoundGlyphArg m_cgaArgument1 = { .i16 = 0 };
		TTFCompoundGlyphArg m_cgaArgument2 = { .i16 = 0 };
		
		float m_arrTransformData[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

		uint8_t m_u8Flags = 0;
	};
	
	std::vector<TTFCompoundGlyphComponent> m_vComponents;

	virtual ~TTFCompoundGlyph() {}
};

typedef std::pair<TTFGlyphDescriptor, std::unique_ptr<TTFGlyph>> TTFGlyphData; //This alias joins the two blocks of glyph data together
																			   //Note that the unique_ptr is a TTFGlyph, utilizing the ugly hack.

struct TTFBitmap {
	uint32_t* m_pPixels;
	uint32_t m_u32Width;
	uint32_t m_u32Height;
	uint32_t m_u32ArraySize;

	TTFBitmap() = delete;

	TTFBitmap(uint32_t _u32Width, uint32_t _u32Height) : m_u32Width(_u32Width), m_u32Height(_u32Height), m_u32ArraySize(_u32Width * _u32Height) {
		m_pPixels = new uint32_t[m_u32ArraySize](0x0);
	}

	TTFBitmap(TTFBitmap&& _bOther) noexcept : m_pPixels(std::exchange(_bOther.m_pPixels, nullptr)), m_u32Width(_bOther.m_u32Width), m_u32Height(_bOther.m_u32Height), m_u32ArraySize(_bOther.m_u32ArraySize){}

	~TTFBitmap() { 
		delete[] m_pPixels;
	}

	void PlotPixel(int _iX, int _iY, uint32_t _u32Color);

	void FlipImageVertically();
};

enum TTFSimpleGlyphFlags : uint8_t {
	ON_CURVE = 0,
	IS_SINGLE_BYTE_X = 1,
	IS_SINGLE_BYTE_Y = 2,
	REPEAT = 3,
	INSTRUCTION_X = 4,
	INSTRUCTION_Y = 5
};

enum TTFComponentGlyphFlags : uint16_t {
	ARGS_1_AND_2_ARE_WORDS = 1,
	ARGS_ARE_XY_VALUES = 2,
	ROUND_XY_TO_GRID = 4,
	WE_HAVE_A_SCALE = 8,
	MORE_COMPONENTS = 32,
	WE_HAVE_AN_X_AND_Y_SCALE = 64,
	WE_HAVE_A_TWO_BY_TWO = 128,
	WE_HAVE_INSTRUCTIONS = 512,
	USE_MY_METRICS = 1024,
	OVERLAP_COMPOUND = 2048,
	SCALED_COMPONENT_OFFSET = 4096,
	UNSCALED_COMPONENT_OFFSET = 8192
};