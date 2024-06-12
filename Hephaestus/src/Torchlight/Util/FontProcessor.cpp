
#include <Torchlight/Util/FontProcessor.hpp>

#include <HellfireControl/Core/File.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Util/Util.hpp>

template<typename T, typename = HC_SFINAE_REQUIRE_INTEGER>
T ReadValue(File& _fFile) {
	T value;
	_fFile >> value;
	Util::InverseBytes(value);

	return value;
}

void GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations);
void GetGlyphLocations(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations);

//TrueType Data Types
typedef int16_t ShortFrac;		//Signed fraction
typedef int32_t FixedPoint;		//Signed 16.16 Fixed Point
typedef int16_t FWord;			//Signed integer in FUnits, smallest distance in em space
typedef uint16_t uFWord;		//Unsigned FWord
typedef int16_t F2Dot14;		//16 bit signed fixed point number stored as 2.14
typedef int64_t LongDateTime;	//Date in seconds from 12:00 Midnight, January 1st 1904.

struct TTFDirectoryEntry {

	union {
		uint32_t m_u32Tag;
		char m_arrTag[5] = { '\0', '\0', '\0', '\0', '\0' };
	};

	uint32_t m_u32CheckSum;
	uint32_t m_u32Offset;
	uint32_t m_u32Length;

	friend File& operator>>(File& _fFile, TTFDirectoryEntry& _tEntry) {
		_fFile >> _tEntry.m_u32Tag; //Due to the fact that this tag is stored as a string, it must be read in without the endian flip.

		_tEntry.m_u32CheckSum = ReadValue<uint32_t>(_fFile);
		_tEntry.m_u32Offset = ReadValue<uint32_t>(_fFile);
		_tEntry.m_u32Length = ReadValue<uint32_t>(_fFile);

		return _fFile;
	}
};

struct TTFGlyphDescriptor {
	int16_t m_u16ContourCount;
	FWord m_fXMin;
	FWord m_fYMIn;
	FWord m_fXMax;
	FWord m_fYMax;
};

struct TTFSimpleGlyph {
	std::vector<uint16_t> m_vContourEndPts;
	std::vector<uint8_t> m_vInstructions;
	std::vector<uint8_t> m_vFlags;
	std::vector<int16_t> m_vXCoords;
	std::vector<int16_t> m_vYCoords;
};

void FontProcessor::ProcessFont(const std::string& _strFilepath) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY); //Open file in binary

	std::map<std::string, uint32_t> mDataBlockLocations;
	
	GetDataBlockOffsets(fFontFile, mDataBlockLocations);

	std::vector<uint32_t> vGlyphLocations;

	GetGlyphLocations(fFontFile, mDataBlockLocations, vGlyphLocations);
}

void GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations) {
	_fFontFile.AdvanceBytes(4); //Skip the "scalar type" entry in the table
	uint16_t u16DirectorySize = ReadValue<uint16_t>(_fFontFile); //Create our list for directory entries
	_fFontFile.AdvanceBytes(6); //Skip over the next 3 16 bit values


	for (int count = 0; count < u16DirectorySize; ++count) {
		union {
			uint32_t u32Tag;
			char arrTag[5] = { '\0', '\0', '\0', '\0', '\0' };
		} tag;

		_fFontFile >> tag.u32Tag;
		_fFontFile.AdvanceBytes(4);

		_mOutDataBlockLocations[tag.arrTag] = ReadValue<uint32_t>(_fFontFile);
		_fFontFile.AdvanceBytes(4);
	}
}

void GetGlyphLocations(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = ReadValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["head"]);

	_fFontFile.AdvanceBytes(50);

	bool bIsTwoByte = ReadValue<uint16_t>(_fFontFile);

	uint32_t u32LocTableStart = _mDataBlockLocations["loca"];
	uint32_t u32GlyphTableStart = _mDataBlockLocations["glyf"];
	_vOutGlyphLocations.resize(u16GlyphCount);

	for (int ndx = 0; ndx < u16GlyphCount; ++ndx) {
		_fFontFile.GoToByte(u32LocTableStart + u32GlyphTableStart * (bIsTwoByte ? 2 : 4));


	}
}
