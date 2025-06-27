#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Math.hpp>

//TrueType Data Types
typedef int16_t ShortFrac;		//Signed fraction
typedef int32_t FixedPoint;		//Signed 16.16 Fixed Point
typedef int16_t FWord;			//Signed integer in FUnits, smallest distance in em space
typedef uint16_t UFWord;		//Unsigned FWord
typedef int16_t F2Dot14;		//16 bit signed fixed point number stored as 2.14

enum TTFVertexFlags : uint8_t {
	ON_CURVE = 0,
	X_SHORT_VECTOR = 1,
	Y_SHORT_VECTOR = 2,
	REPEAT = 3,
	X_SIGN_OR_SKIP = 4,
	Y_SIGN_OR_SKIP = 5
};

enum TTFCompoundGlyphFlags : uint8_t {
	ARG_1_AND_2_ARE_WORDS = 0,
	ARGS_ARE_XY_VALUES = 1,
	ROUND_XY_TO_GRID = 2,
	WE_HAVE_A_SCALE = 3,
	MORE_COMPONENTS = 5,
	WE_HAVE_AN_X_AND_Y_SCALE = 6,
	WE_HAVE_A_TWO_BY_TWO = 7,
	WE_HAVE_INSTRUCTIONS = 8,
	USE_MY_METRICS = 9,
	OVERLAP_COMPOUND = 10
};

//These are inspired by the STB implementation.
enum class TTFVertexType : uint8_t {
	CONTOUR_START,
	LINE_SEGMENT,
	QUADRATIC_CURVE,
	CUBIC_CURVE
};

typedef uint32_t UTF8PaddedChar;

struct TTFCharacterRange {
	UTF8PaddedChar m_cFirstChar;
	uint32_t m_u32Count;
};

typedef std::map<UTF8PaddedChar, uint32_t> TTFCharacterMap;

struct TTFTag {
	union {
		uint32_t m_u32TagInt;
		char m_pTagStr[5] = { 0, 0, 0, 0, 0 };
	};

	TTFTag() : m_pTagStr{ 0, 0, 0, 0, 0 } {}

	TTFTag(const char* _pTag) {
		memcpy_s(m_pTagStr, 4, _pTag, 4);
	}

	TTFTag(uint32_t _u32Tag) :
		m_u32TagInt(_u32Tag) {}

	bool operator==(const TTFTag& _other) const {
		return m_u32TagInt == _other.m_u32TagInt;
	}

	bool operator<(const TTFTag& _other) const {
		return strcmp(m_pTagStr, _other.m_pTagStr) < 0;
	}

	bool operator>(const TTFTag& _other) const {
		return strcmp(m_pTagStr, _other.m_pTagStr) > 0;
	}
};

struct TTFTableDirectoryEntry {
	uint32_t m_u32Checksum = 0;
	uint32_t m_u32Offset = 0;
	uint32_t m_u32Length = 0;

	bool IsValid() const {
		return !(m_u32Checksum == 0 && m_u32Offset == 0 && m_u32Length == 0);
	}
};

struct TTFFontInfo {
	TTFTableDirectoryEntry	m_tdeLoca,
							m_tdeHead,
							m_tdeGlyf,
							m_tdeHHea,
							m_tdeHMtx,
							m_tdeCMap,
							m_tdeMaxP,
							m_tdeKern,
							m_tdeGPos;

	uint16_t m_u16GlyphCount = UINT16_MAX;
	int16_t m_i16IndexToLocFormat = 0;
	uint16_t m_u16UnitsPerEm = 0;
	uint16_t m_u16NumOfLongHorMetrics = 0;
	float m_fScaleFactor = 0.0f;
	TTFCharacterMap m_cmCMap;
};

struct TTFVertex {
	Vec2F m_v2Vert;
	uint8_t m_u8Flags = 0;
	TTFVertexType m_vtType = TTFVertexType::CONTOUR_START;
};

struct TTFGlyphInfo {
	uint16_t m_u16AdvanceWidth = 0;
	int16_t m_i16LeftSideBearing = 0;
	Vec2F m_v2Min;
	Vec2F m_v2Max;
	std::vector<TTFVertex> m_vVerts;
};

struct TTFBakedGlyphInfo {
	Vec4F m_v4BoundingBox;
	float m_fAdvanceWidth = 0.0f;
	float m_fLeftSideBearing = 0.0f;
};

struct TTFEdge {
	Vec2F m_v2Min;
	Vec2F m_v2Max;
	float m_fSlope = 0.0f;
	float m_fXCurrent = 0.0f;
	bool m_bDownward = false;
};