#include <HellfireControl/Asset/Converters/Font/FontParser.hpp>

#include <HellfireControl/Util/Util.hpp>

//TrueType Data Types
typedef int16_t ShortFrac;		//Signed fraction
typedef int32_t FixedPoint;		//Signed 16.16 Fixed Point
typedef int16_t FWord;			//Signed integer in FUnits, smallest distance in em space
typedef uint16_t UFWord;		//Unsigned FWord
typedef int16_t F2Dot14;		//16 bit signed fixed point number stored as 2.14

#define HC_MISSING_CHAR_GLYPH_INDEX 65535

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
		m_u32TagInt(_u32Tag) {
	}

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

template<typename T, HC_SFINAE_REQUIRE_INTEGER(T)>
static HC_INLINE T ReadTTFValue(File& _fFile) {
	T value = 0;
	_fFile.Read(&value, sizeof(T));
	Util::ReverseBytes(value);

	return value;
}

template<typename T, HC_SFINAE_REQUIRE_INTEGER(T)>
static HC_INLINE T ReadTTFValue(File& _fFile, size_t _sByte) {
	_fFile.GoToByte(_sByte);
	T value = 0;
	_fFile.Read(&value, sizeof(T));
	Util::ReverseBytes(value);

	return value;
}

template<typename T, HC_SFINAE_REQUIRE_FLOATING_POINT(T)>
static HC_INLINE T ConvertToFloatingPoint(F2Dot14 _fixed) {
	return static_cast<T>(_fixed) / static_cast<T>(1 << 14);
}

bool IsValidFont(File& _fFontFile);
TTFTableDirectoryEntry FindTable(File& _fFontFile, uint16_t _u16TableCount, uint16_t _u16SearchRange, uint16_t _u16EntrySelector, uint16_t _u16RangeShift, TTFTag _tTag);
CharacterMap ReadCMapFormat4(File& _fFontFile);
CharacterMap ReadCMapFormat12(File& _fFontFile);

FontInfo FontTTFParser::InitializeFont(File& _fFontFile, float _fFontHeightPoints) {
	if (!IsValidFont(_fFontFile)) {
		throw std::runtime_error("ERROR! INVALID FONT PROVIDED!");
	}

	FontInfo fiInfo;
	fiInfo.m_fFontSize = _fFontHeightPoints;

	uint16_t u16TableCount = ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16SearchRange = ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16EntrySelector = ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16RangeShift = ReadTTFValue<uint16_t>(_fFontFile);

	fiInfo.m_tdeLoca = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "loca");
	fiInfo.m_tdeHead = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "head");
	fiInfo.m_tdeGlyf = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "glyf");
	fiInfo.m_tdeHHea = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "hhea");
	fiInfo.m_tdeHMtx = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "hmtx");
	fiInfo.m_tdeCMap = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "cmap");
	fiInfo.m_tdeMaxP = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "maxp");
	fiInfo.m_tdeKern = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "kern");
	fiInfo.m_tdeGPos = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "GPOS");

	if (!fiInfo.m_tdeCMap.IsValid() || !fiInfo.m_tdeHead.IsValid() || !fiInfo.m_tdeHMtx.IsValid()) {
		throw std::runtime_error("ERROR: INVALID FONT SUPPLIED!");
	}

	if (fiInfo.m_tdeGlyf.IsValid()) {
		if (!fiInfo.m_tdeLoca.IsValid()) {
			throw std::runtime_error("ERROR: MALFORMED FONT SUPPLIED!");
		}
	}
	else {
		//TODO Support CFF Fonts
	}

	if (fiInfo.m_tdeMaxP.IsValid()) {
		_fFontFile.GoToByte(fiInfo.m_tdeMaxP.m_u32Offset + sizeof(FixedPoint));
		fiInfo.m_u16GlyphCount = ReadTTFValue<uint16_t>(_fFontFile);
	}

	_fFontFile.GoToByte(fiInfo.m_tdeHead.m_u32Offset + sizeof(FixedPoint) * 2 + sizeof(uint32_t) * 2 + sizeof(uint16_t));
	fiInfo.m_u16UnitsPerEm = ReadTTFValue<uint16_t>(_fFontFile);
	fiInfo.m_fScaleFactor = (_fFontHeightPoints * 96) / (72 * fiInfo.m_u16UnitsPerEm);

	_fFontFile.AdvanceBytes(sizeof(uint64_t) * 2 + sizeof(FWord) * 4 + sizeof(uint16_t) * 3);
	fiInfo.m_i16IndexToLocFormat = ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(fiInfo.m_tdeHHea.m_u32Offset + sizeof(FixedPoint) + sizeof(FWord) * 8 + sizeof(int16_t) * 7);
	fiInfo.m_u16NumOfLongHorMetrics = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(fiInfo.m_tdeCMap.m_u32Offset + sizeof(uint16_t));
	uint16_t u16CMapCount = ReadTTFValue<uint16_t>(_fFontFile);
	int16_t i16UnicodeVersion = -1;
	uint32_t u32TableOffset = 0;

	for (int iterations = 0; iterations < u16CMapCount; ++iterations) {
		uint16_t u16PlatformID = ReadTTFValue<uint16_t>(_fFontFile);
		uint16_t u16PlatformSpecificID = ReadTTFValue<uint16_t>(_fFontFile);
		uint32_t u32Offset = ReadTTFValue<uint32_t>(_fFontFile);

		if (u16PlatformID == 0) {
			if (u16PlatformSpecificID > i16UnicodeVersion) {
				i16UnicodeVersion = u16PlatformSpecificID;
				u32TableOffset = u32Offset;
			}
		}
		else if (u16PlatformID == 3 && i16UnicodeVersion < 0) {
			u32TableOffset = u32Offset;
		}
	}

	if (u32TableOffset == 0) {
		throw std::runtime_error("ERROR: FONT CHARACTER MAP UNSUPPORTED!");
	}

	_fFontFile.GoToByte(fiInfo.m_tdeCMap.m_u32Offset + u32TableOffset);
	uint16_t u16TableFormat = ReadTTFValue<uint16_t>(_fFontFile);

	switch (u16TableFormat) {
	case 4:
		fiInfo.m_cmCMap = ReadCMapFormat4(_fFontFile);
		break;
	case 12:
		fiInfo.m_cmCMap = ReadCMapFormat12(_fFontFile);
	}

    return fiInfo;
}

GlyphInfo FontTTFParser::GetGlyphInfo(File& _fFontFile, const FontInfo& _fiInfo, uint32_t _u32GlyphIndex) {
	GlyphInfo giGlyph;

	if (_u32GlyphIndex < _fiInfo.m_u16NumOfLongHorMetrics) {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16_t) * 2 * _u32GlyphIndex);
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16_t) * 2 * (_fiInfo.m_u16NumOfLongHorMetrics - 1));
	}

	giGlyph.m_u16AdvanceWidth = ReadTTFValue<uint16_t>(_fFontFile);
	giGlyph.m_i16LeftSideBearing = ReadTTFValue<int16_t>(_fFontFile);

	uint32_t u32Offset;
	uint32_t u32Length;
	if (_fiInfo.m_i16IndexToLocFormat == 0) {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint16_t)));
		u32Offset = ReadTTFValue<uint16_t>(_fFontFile) * 2;
		u32Length = (ReadTTFValue<uint16_t>(_fFontFile) * 2) - u32Offset;
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint32_t)));
		u32Offset = ReadTTFValue<uint32_t>(_fFontFile);
		u32Length = ReadTTFValue<uint32_t>(_fFontFile) - u32Offset;
	}

	if (u32Length == 0) {
		return giGlyph; //If there was no data for this glyph, exit.
	}

	_fFontFile.GoToByte(_fiInfo.m_tdeGlyf.m_u32Offset + u32Offset);

	int16_t i16ContourCount = ReadTTFValue<int16_t>(_fFontFile);

	//Compiler confusion...? The compiler evaluates these in backwards order when used in the constructor directly.
	//They have to be in separate variables to prevent this. I don't understand...?
	FWord wMinX = ReadTTFValue<FWord>(_fFontFile);
	FWord wMinY = ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxX = ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxY = ReadTTFValue<FWord>(_fFontFile);

	giGlyph.m_v2Min = Vec2F(wMinX, wMinY);
	giGlyph.m_v2Max = Vec2F(wMaxX, wMaxY);

	if (i16ContourCount > 0) {
		std::vector<uint16_t> vEndPoints(i16ContourCount);

		for (int iNdx = 0; iNdx < i16ContourCount; ++iNdx) {
			vEndPoints[iNdx] = ReadTTFValue<uint16_t>(_fFontFile);
		}

		//TODO: Eventually implement a proper interpreter to use the instructions in the font file. Skip for now.
		_fFontFile.AdvanceBytes(ReadTTFValue<uint16_t>(_fFontFile));

		size_t sVertexCount = (*std::max_element(vEndPoints.begin(), vEndPoints.end())) + 1;

		std::vector<uint8_t> vFlags = GetCoordinateFlags(_fFontFile, sVertexCount);

		std::vector<Vec2F> vCoords = GetCoordinates(_fFontFile, sVertexCount, vFlags);

		giGlyph.m_vVerts = PackVertices(vEndPoints, vCoords, vFlags);
	}
	else if (i16ContourCount < 0) {
		bool bMoreComponents = false;
		do {
			uint16_t u16Flags = ReadTTFValue<uint16_t>(_fFontFile);

			bMoreComponents = Util::IsBitSet(u16Flags, MORE_COMPONENTS);

			uint16_t u16GlyphIndex = ReadTTFValue<uint16_t>(_fFontFile);

			float pfTransform[6] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

			if (Util::IsBitSet(u16Flags, ARGS_ARE_XY_VALUES)) {
				if (Util::IsBitSet(u16Flags, ARG_1_AND_2_ARE_WORDS)) {
					pfTransform[4] = static_cast<float>(ReadTTFValue<int16_t>(_fFontFile));
					pfTransform[5] = static_cast<float>(ReadTTFValue<int16_t>(_fFontFile));
				}
				else {
					pfTransform[4] = static_cast<float>(ReadTTFValue<int8_t>(_fFontFile));
					pfTransform[5] = static_cast<float>(ReadTTFValue<int8_t>(_fFontFile));
				}
			}
			else {
				throw std::logic_error("NOT IMPLEMENTED!");
			}

			if (Util::IsBitSet(u16Flags, WE_HAVE_A_SCALE)) {
				pfTransform[0] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
				pfTransform[3] = pfTransform[0];
			}
			else if (Util::IsBitSet(u16Flags, WE_HAVE_AN_X_AND_Y_SCALE)) {
				pfTransform[0] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
				pfTransform[3] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
			}
			else if (Util::IsBitSet(u16Flags, WE_HAVE_A_TWO_BY_TWO)) {
				pfTransform[0] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
				pfTransform[1] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
				pfTransform[2] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
				pfTransform[3] = ConvertToFloatingPoint<float>(ReadTTFValue<F2Dot14>(_fFontFile));
			}

			float fXScale = Math::Sqrt(pfTransform[0] * pfTransform[0] + pfTransform[1] * pfTransform[1]);
			float fYScale = Math::Sqrt(pfTransform[2] * pfTransform[2] + pfTransform[3] * pfTransform[3]);

			size_t sCurentLocation = _fFontFile.ReaderLocation();

			//Get the sub glyph's info (maybe check for infinite recursion?)
			GlyphInfo giSubGlyph = GetGlyphInfo(_fFontFile, _fiInfo, u16GlyphIndex);

			//Return to the original location of this glyph you moron!
			_fFontFile.GoToByte(sCurentLocation);

			//Transform vertices
			if (giSubGlyph.m_vVerts.size() == 0) {
				continue;
			}

			for (auto& aVert : giSubGlyph.m_vVerts) {
				float fOriginalX = aVert.m_v2Vert.x;
				float fOriginalY = aVert.m_v2Vert.y;

				aVert.m_v2Vert = Vec2F(
					(fXScale * (pfTransform[0] * fOriginalX + pfTransform[2] * fOriginalY + pfTransform[4])),
					(fYScale * (pfTransform[1] * fOriginalX + pfTransform[3] * fOriginalY + pfTransform[5]))
				);
			}

			//Add the verts to the glyph vertex list
			giGlyph.m_vVerts.insert(giGlyph.m_vVerts.end(), giSubGlyph.m_vVerts.begin(), giSubGlyph.m_vVerts.end());
		} while (bMoreComponents);
	}

	return giGlyph;
}

std::vector<uint8_t> FontTTFParser::GetCoordinateFlags(File& _fFontFile, size_t sVertexCount)
{
	std::vector<uint8_t> vFlags(sVertexCount);

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = ReadTTFValue<uint8_t>(_fFontFile);

		vFlags[iNdx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = ReadTTFValue<uint8_t>(_fFontFile);

			for (int iCount = 0; iCount < u8RepeatCount; ++iCount) {
				vFlags[++iNdx] = u8Flag;
			}
		}
	}

	return vFlags;
}

std::vector<Vec2F> FontTTFParser::GetCoordinates(File& _fFontFile, const size_t sVertexCount, const std::vector<uint8_t>& vFlags)
{
	std::vector<Vec2F> vVertices(sVertexCount);

	int32_t i16XAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, X_SHORT_VECTOR)) {
			int16_t i16Coord = ReadTTFValue<uint8_t>(_fFontFile);
			i16XAcc += Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP)) {
			i16XAcc += ReadTTFValue<int16_t>(_fFontFile);
		}
		vVertices[iNdx].x = static_cast<float>(i16XAcc);
	}

	int16_t i16YAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, Y_SHORT_VECTOR)) {
			int16_t i16Coord = ReadTTFValue<uint8_t>(_fFontFile);
			i16YAcc += Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP)) {
			i16YAcc += ReadTTFValue<int16_t>(_fFontFile);
		}
		vVertices[iNdx].y = static_cast<float>(i16YAcc);
	}

	return vVertices;
}

std::vector<TTFVertex> FontTTFParser::PackVertices(const std::vector<uint16_t>& _vContourEndPoints, const std::vector<Vec2F>& _vCoordinates, const std::vector<uint8_t>& _vFlags) {
	std::vector<TTFVertex> vVertices;

	if (_vCoordinates.size() < 2) {
		return vVertices;
	}

	int iStartPoint = 0;
	for (int iNdx = 0; iNdx < _vContourEndPoints.size(); ++iNdx) {
		int iNumCoordCount = _vContourEndPoints[iNdx] - iStartPoint + 1;

		std::vector<Vec2F> vContourCoords;
		std::vector<uint8_t> vContourFlags;

		vContourCoords.insert(vContourCoords.end(), _vCoordinates.begin() + iStartPoint, _vCoordinates.begin() + iStartPoint + iNumCoordCount);
		vContourFlags.insert(vContourFlags.end(), _vFlags.begin() + iStartPoint, _vFlags.begin() + iStartPoint + iNumCoordCount);

		std::vector<TTFVertex> vPackedContourVertices = PackContourVertices(vContourCoords, vContourFlags);

		vVertices.insert(vVertices.end(), vPackedContourVertices.begin(), vPackedContourVertices.end());

		iStartPoint = _vContourEndPoints[iNdx] + 1;
	}

	return vVertices;
}

std::vector<TTFVertex> FontTTFParser::PackContourVertices(const std::vector<Vec2F>& _vContourCoords, const std::vector<uint8_t>& _vContourFlags) {
	std::vector<TTFVertex> vPackedVertices;

	//First we find our starting point for the contour. This is equivalent to the first on-curve point,
	//which is not guaranteed to be the first point
	int iContourStart;
	for (iContourStart = 0; iContourStart < _vContourCoords.size(); ++iContourStart) {
		if (Util::IsBitSet(_vContourFlags[iContourStart], ON_CURVE)) {
			break;
		}
	}

	//Next, we add all our vertices to the list in the new order. This order is the same as before, except all points
	//before the starting point have now been shifted to the end.
	int iAddedVertexCount = 0;
	int iContourIndex = iContourStart;
	while (iAddedVertexCount != _vContourCoords.size()) {
		vPackedVertices.push_back({ _vContourCoords[iContourIndex], _vContourFlags[iContourIndex], TTFVertexType::CONTOUR_START });
		iContourIndex = (iContourIndex + 1) % _vContourCoords.size();
		iAddedVertexCount++;
	}

	//Finally, we decompress the vertices by adding back in implied points and setting line segments. The first point of every contour
	//is always set to CONTOUR_START
	bool bPrevOffCurve = false;
	for (int iNdx = 1; iNdx < vPackedVertices.size(); ++iNdx) {
		if (!Util::IsBitSet(vPackedVertices[iNdx].m_u8Flags, ON_CURVE)) {
			vPackedVertices[iNdx].m_vtType = TTFVertexType::QUADRATIC_CURVE; //TODO: When CFF fonts are supported, check whether or not it's cubic.
			if (bPrevOffCurve) {
				//TODO: When CFF fonts are supported, check whether or not it's cubic.
				vPackedVertices.insert(vPackedVertices.begin() + iNdx++, {
					Math::Lerp(vPackedVertices[iNdx - 1].m_v2Vert, vPackedVertices[iNdx].m_v2Vert, 0.5f),
					(1 << ON_CURVE),
					TTFVertexType::QUADRATIC_CURVE
					});
			}
			bPrevOffCurve = true;
		}
		else {
			if (bPrevOffCurve) {
				vPackedVertices[iNdx].m_vtType = TTFVertexType::QUADRATIC_CURVE; //TODO: When CFF fonts are supported, check whether or not it's cubic.
			}
			else {
				vPackedVertices[iNdx].m_vtType = TTFVertexType::LINE_SEGMENT;
			}
			bPrevOffCurve = false;
		}
	}

	return vPackedVertices;
}

bool IsValidFont(File& _fFontFile) {
	TTFTag tTag;
	_fFontFile.Read(&tTag.m_u32TagInt, sizeof(uint32_t));

	return	tTag == 0x31000000U ||	//TrueType 1 (Tag: 1000)
			tTag == "OTTO" ||		//OpenType with CFF (NOT SUPPORTED YET!)
			tTag == 256U ||			//OpenType 1 (Tag: 0100)
			tTag == "true";			//Apple TrueType
}

TTFTableDirectoryEntry FindTable(File& _fFontFile, uint16_t _u16TableCount, uint16_t _u16SearchRange, uint16_t _u16EntrySelector, uint16_t _u16RangeShift, TTFTag _tTag) {
	TTFTableDirectoryEntry tdeEntry;
	TTFTag tCurrentTag;
	size_t sDirectoryStart = sizeof(uint32_t) + (sizeof(uint16_t) * 4);

	_fFontFile.GoToByte(sDirectoryStart + (_u16SearchRange - 16)); //Advance to the first item at the _u16RangeShift value.

	_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32_t));

	if (_tTag == tCurrentTag) {
		tdeEntry.m_u32Checksum = ReadTTFValue<uint32_t>(_fFontFile);
		tdeEntry.m_u32Offset = ReadTTFValue<uint32_t>(_fFontFile);
		tdeEntry.m_u32Length = ReadTTFValue<uint32_t>(_fFontFile);
		return tdeEntry;
	}

	if (_tTag < tCurrentTag) { //We can binary search, thanks to being within the defined area
		int iOffset = _u16SearchRange >> 1;
		for (int iterations = 0; iterations < _u16EntrySelector; ++iterations) {
			_fFontFile.GoToByte(sDirectoryStart + iOffset);

			_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32_t));

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Offset = ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Length = ReadTTFValue<uint32_t>(_fFontFile);
				break;
			}

			iOffset += (_tTag < tCurrentTag) ? -(_u16SearchRange >> (2 + iterations)) : (_u16SearchRange >> (2 + iterations));
		}
	}
	else if (_tTag > tCurrentTag) { //We have to linear search, since we are outside the defined area
		_fFontFile.AdvanceBytes(sizeof(uint32_t) * 3); //Skip over the first item we checked.

		int iItemCount = (_u16RangeShift / 16);

		for (int iterations = 0; iterations < iItemCount; ++iterations) {
			_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32_t));

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Offset = ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Length = ReadTTFValue<uint32_t>(_fFontFile);
				break;
			}
			_fFontFile.AdvanceBytes(sizeof(uint32_t) * 3);
		}
	}

	return tdeEntry;
}

CharacterMap ReadCMapFormat4(File& _fFontFile) {
	CharacterMap mCharMap;

	uint16_t u16TableLength = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(sizeof(uint16_t));

	uint16_t u16SegCountX2 = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(sizeof(uint16_t) * 3);

	uint32_t u32EndCodeArrayHead = _fFontFile.ReaderLocation();
	uint32_t u32StartCodeArrayHead = u32EndCodeArrayHead + u16SegCountX2 + 2;
	uint32_t u32IdDeltaArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 2) + 2;
	uint32_t u32IdRangeArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 3) + 2;
	uint32_t u32GlyphIdArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 4) + 2;
	uint32_t u32GlyphArrayLength = (u16TableLength - (u32GlyphIdArrayHead - (u32EndCodeArrayHead - sizeof(uint16_t) * 7))) >> 1;
	//The 7 here refers to the 7 uint16_t values in the table preceeding the start of the end code array.
	// This is so that we can use the table length to calculate the number of glyphs.

	struct Format4Segment {
		uint16_t u16EndCode;
		uint16_t u16StartCode;
		uint16_t u16IdDelta;
		uint16_t u16IdRangeOffset;
		uint32_t u16IdRangeOffsetLocation;
	};

	std::vector<Format4Segment> vSegments(u16SegCountX2 >> 1);

	for (int iCount = 0; iCount < (u16SegCountX2 >> 1); ++iCount) {
		uint16_t u16ArrayOffset = iCount * sizeof(uint16_t);

		Format4Segment f4Segment = {
			.u16EndCode = ReadTTFValue<uint16_t>(_fFontFile, u32EndCodeArrayHead + u16ArrayOffset),
			.u16StartCode = ReadTTFValue<uint16_t>(_fFontFile, u32StartCodeArrayHead + u16ArrayOffset),
			.u16IdDelta = ReadTTFValue<uint16_t>(_fFontFile, u32IdDeltaArrayHead + u16ArrayOffset),
			.u16IdRangeOffset = ReadTTFValue<uint16_t>(_fFontFile, u32IdRangeArrayHead + u16ArrayOffset),
			.u16IdRangeOffsetLocation = u32IdRangeArrayHead + u16ArrayOffset
		};

		vSegments[iCount] = f4Segment;
	}

	for (const auto& aSegment : vSegments) {
		for (uint32_t u32GlyphCode = aSegment.u16StartCode; u32GlyphCode <= aSegment.u16EndCode; ++u32GlyphCode) {
			if (aSegment.u16IdRangeOffset == 0) {
				mCharMap[u32GlyphCode] = (aSegment.u16IdDelta + u32GlyphCode) % 65536; //Modding is required thanks to unsigned values used.
			}
			else {
				uint32_t u32IndexLocation = aSegment.u16IdRangeOffset + 2 * (u32GlyphCode - aSegment.u16StartCode) + aSegment.u16IdRangeOffsetLocation;
				mCharMap[u32GlyphCode] = ReadTTFValue<uint16_t>(_fFontFile, u32IndexLocation);
			}
		}
	}

	return mCharMap;
}

CharacterMap ReadCMapFormat12(File& _fFontFile) {
	CharacterMap mCharMap;

	_fFontFile.AdvanceBytes(10); //Skip over Reserved, Length (unneccessary as we have the group count), and Language

	uint32_t u32Groups = ReadTTFValue<uint32_t>(_fFontFile);

	bool bAddedMissingChar = false;
	for (uint32_t u32Count = 0; u32Count < u32Groups; ++u32Count) {
		uint32_t u32CharStartCode = ReadTTFValue<uint32_t>(_fFontFile);
		uint32_t u32CharEndCode = ReadTTFValue<uint32_t>(_fFontFile);
		uint32_t u32StartGlyphID = ReadTTFValue<uint32_t>(_fFontFile);

		uint32_t u32CharCount = (u32CharEndCode - u32CharStartCode) + 1;

		for (uint32_t u32Count = 0; u32Count < u32CharCount; ++u32Count) {
			mCharMap[u32CharStartCode + u32Count] = u32StartGlyphID + u32Count;

			bAddedMissingChar |= (u32StartGlyphID + u32Count) == 0;
		}
	}

	if (!bAddedMissingChar) {
		mCharMap[HC_MISSING_CHAR_GLYPH_INDEX] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
	}

	return mCharMap;
}