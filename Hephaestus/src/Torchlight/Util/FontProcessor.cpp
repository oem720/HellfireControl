
#include <Torchlight/Util/FontProcessor.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Math/Math.hpp>

void FontProcessor::ProcessFont(const std::string& _strFilepath) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY); //Open file in binary

	std::map<std::string, uint32_t> mDataBlockLocations;
	
	GetDataBlockOffsets(fFontFile, mDataBlockLocations);

	std::vector<uint32_t> vGlyphOffsets;

	GetGlyphOffsets(fFontFile, mDataBlockLocations, vGlyphOffsets);

	std::vector<TTFGlyphData> vGlyphData(vGlyphOffsets.size()); //Size of the list is the size of the number of locations

	uint32_t u32GlyphTableStart = mDataBlockLocations["glyf"];

	for (int ndx = 0; ndx < vGlyphData.size(); ++ndx) {
		fFontFile.GoToByte(u32GlyphTableStart + vGlyphOffsets[ndx]);

		ParseGlyph(fFontFile, vGlyphData[ndx]); //Parse the glyph individually
	}
}

void FontProcessor::GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations) {
	_fFontFile.AdvanceBytes(4); //Skip the "scalar type" entry in the table
	uint16_t u16DirectorySize = ReadTTFValue<uint16_t>(_fFontFile); //Create our list for directory entries
	_fFontFile.AdvanceBytes(6); //Skip over the next 3 16 bit values

	for (int count = 0; count < u16DirectorySize; ++count) {
		union {
			uint32_t u32Tag;
			char arrTag[5] = { '\0', '\0', '\0', '\0', '\0' };
		} tag;

		_fFontFile >> tag.u32Tag;
		_fFontFile.AdvanceBytes(4);

		_mOutDataBlockLocations[tag.arrTag] = ReadTTFValue<uint32_t>(_fFontFile);
		_fFontFile.AdvanceBytes(4);
	}
}

void FontProcessor::GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphOffsets) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["head"]);

	_fFontFile.AdvanceBytes(18);

	uint16_t u16UnitsPerEm = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(30);

	bool bIsTwoByte = !ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["loca"]);
	_vOutGlyphOffsets.resize(u16GlyphCount);

	for (size_t ndx = 0; ndx < u16GlyphCount; ++ndx) {
		_vOutGlyphOffsets[ndx] = (bIsTwoByte ? (ReadTTFValue<uint16_t>(_fFontFile) * 2u) : ReadTTFValue<uint32_t>(_fFontFile));
	}
}

void FontProcessor::ParseGlyph(File& _fFontFile, TTFGlyphData& _gdOutGlyphData) {
	_gdOutGlyphData.first = {
		.m_i16ContourCount = ReadTTFValue<int16_t>(_fFontFile),
		.m_fXMin = ReadTTFValue<FWord>(_fFontFile),
		.m_fYMIn = ReadTTFValue<FWord>(_fFontFile),
		.m_fXMax = ReadTTFValue<FWord>(_fFontFile),
		.m_fYMax = ReadTTFValue<FWord>(_fFontFile)
	};

	if (_gdOutGlyphData.first.m_i16ContourCount < 0) {
		_gdOutGlyphData.second = ParseCompoundGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount);
	}
	else {
		_gdOutGlyphData.second = ParseSimpleGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount);
	}
}

enum TTFSimpleGlyphFlags : uint8_t {
	ON_CURVE = 0,
	IS_SINGLE_BYTE_X = 1,
	IS_SINGLE_BYTE_Y = 2,
	REPEAT = 3,
	INSTRUCTION_X = 4,
	INSTRUCTION_Y = 5
};

std::unique_ptr<FontProcessor::TTFSimpleGlyph> FontProcessor::ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount) {
	auto aSimpleGlyph = std::make_unique<TTFSimpleGlyph>();

	aSimpleGlyph->m_vContourEndPts.resize(_i16ContourCount);

	for (int ndx = 0; ndx < _i16ContourCount; ++ndx) {
		aSimpleGlyph->m_vContourEndPts[ndx] = ReadTTFValue<uint16_t>(_fFontFile);
	}

	//aSimpleGlyph->m_vInstructions.resize(ReadTTFValue<uint16_t>(_fFontFile));
	//
	//for (int ndx = 0; ndx < aSimpleGlyph->m_vInstructions.size(); ++ndx) {
	//	aSimpleGlyph->m_vInstructions[ndx] = ReadTTFValue<uint8_t>(_fFontFile);
	//}

	_fFontFile.AdvanceBytes(ReadTTFValue<int16_t>(_fFontFile));

	//Get the largest contour end point index and add 1 (1 based count). This will equal the count of points
	int iNumPoints = 1 + (*std::max_element(aSimpleGlyph->m_vContourEndPts.begin(), aSimpleGlyph->m_vContourEndPts.end()));

	aSimpleGlyph->m_vFlags.resize(iNumPoints);
	aSimpleGlyph->m_vXCoords.resize(iNumPoints);
	aSimpleGlyph->m_vYCoords.resize(iNumPoints);

	for (int ndx = 0; ndx < iNumPoints; ++ndx) {
		uint8_t u8Flag = ReadTTFValue<uint8_t>(_fFontFile);

		aSimpleGlyph->m_vFlags[ndx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = ReadTTFValue<uint8_t>(_fFontFile);

			for (int iFlagCount = 0; iFlagCount < u8RepeatCount; ++iFlagCount) {
				aSimpleGlyph->m_vFlags[++ndx] = u8Flag;
			}
		}
	}

	ParseCoordinates(_fFontFile, aSimpleGlyph->m_vFlags, true, aSimpleGlyph->m_vXCoords);
	ParseCoordinates(_fFontFile, aSimpleGlyph->m_vFlags, false, aSimpleGlyph->m_vYCoords);

	return std::move(aSimpleGlyph);
}

std::unique_ptr<FontProcessor::TTFCompoundGlyph> FontProcessor::ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount) {
	auto aCompoundGlyph = std::make_unique<TTFCompoundGlyph>();

	return std::move(aCompoundGlyph);
}

void FontProcessor::ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, bool bIsX, std::vector<int16_t>& _vOutCoordinates) {
	int iOffsetSizeFlagBit = bIsX ? IS_SINGLE_BYTE_X : IS_SINGLE_BYTE_Y;
	int iOffsetSignOrSkipBit = bIsX ? INSTRUCTION_X : INSTRUCTION_Y;

	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		_vOutCoordinates[ndx] = _vOutCoordinates[std::max(0, ndx - 1)];
		
		uint8_t u8Flag = _vFlags[ndx];

		if (Util::IsBitSet(u8Flag, iOffsetSizeFlagBit)) {
			_vOutCoordinates[ndx] += ReadTTFValue<uint8_t>(_fFontFile) * (Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit) ? 1 : -1);
		}
		else if (!Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit)) {
			_vOutCoordinates[ndx] += ReadTTFValue<uint16_t>(_fFontFile);
		}
	}
}