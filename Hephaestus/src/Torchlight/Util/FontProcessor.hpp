#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/File.hpp>

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

	struct TTFGlyphDescriptor {
		int16_t m_i16ContourCount;
		FWord m_fXMin;
		FWord m_fYMIn;
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
		std::vector<uint16_t> m_vContourEndPts;
		std::vector<uint8_t> m_vInstructions;
		std::vector<uint8_t> m_vFlags;
		std::vector<int16_t> m_vXCoords;
		std::vector<int16_t> m_vYCoords;

		bool m_bOnCurve = true;;

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
	static void GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations);
	static void ParseGlyph(File& _fFontFile, TTFGlyphData& _gdOutGlyphData);
	static std::unique_ptr<TTFSimpleGlyph> ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount);
	static std::unique_ptr<TTFCompoundGlyph> ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount);
	static void ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, bool bIsX, std::vector<int16_t>& _vOutCoordinates);
};