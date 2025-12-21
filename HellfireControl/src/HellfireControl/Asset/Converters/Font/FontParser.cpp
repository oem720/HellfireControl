#include <HellfireControl/Asset/Converters/Font/FontParser.hpp>

#include <HellfireControl/Util/Util.hpp>

//TrueType Data Types
typedef int16 ShortFrac;	//Signed fraction
typedef int32 FixedPoint;	//Signed 16.16 Fixed Point
typedef int16 FWord;		//Signed integer in FUnits, smallest distance in em space
typedef uint16 UFWord;		//Unsigned FWord
typedef int16 F2Dot14;		//16 bit signed fixed point number stored as 2.14

#define HC_MISSING_CHAR_GLYPH_INDEX 65535

enum TTFVertexFlags : uint8 {
	ON_CURVE = 0,
	X_SHORT_VECTOR = 1,
	Y_SHORT_VECTOR = 2,
	REPEAT = 3,
	X_SIGN_OR_SKIP = 4,
	Y_SIGN_OR_SKIP = 5
};

enum TTFCompoundGlyphFlags : uint8 {
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
		uint32 m_u32TagInt;
		char m_pTagStr[5] = { 0, 0, 0, 0, 0 };
	};

	TTFTag() : m_pTagStr{ 0, 0, 0, 0, 0 } {}

	TTFTag(const char* _pTag) {
		memcpy_s(m_pTagStr, 4, _pTag, 4);
	}

	TTFTag(uint32 _u32Tag) :
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
TTFTableDirectoryEntry FindTable(File& _fFontFile, uint16 _u16TableCount, uint16 _u16SearchRange, uint16 _u16EntrySelector, uint16 _u16RangeShift, TTFTag _tTag);
CharacterMap ReadCMapFormat4(File& _fFontFile);
CharacterMap ReadCMapFormat12(File& _fFontFile);

FontInfo FontTTFParser::InitializeFont(File& _fFontFile, float _fFontHeightPoints) {
	if (!IsValidFont(_fFontFile)) {
		throw std::runtime_error("ERROR! INVALID FONT PROVIDED!");
	}

	FontInfo fiInfo;
	fiInfo.m_fFontSize = _fFontHeightPoints;

	uint16 u16TableCount = ReadTTFValue<uint16>(_fFontFile);
	uint16 u16SearchRange = ReadTTFValue<uint16>(_fFontFile);
	uint16 u16EntrySelector = ReadTTFValue<uint16>(_fFontFile);
	uint16 u16RangeShift = ReadTTFValue<uint16>(_fFontFile);

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
		fiInfo.m_u16GlyphCount = ReadTTFValue<uint16>(_fFontFile);
	}

	_fFontFile.GoToByte(fiInfo.m_tdeHead.m_u32Offset + sizeof(FixedPoint) * 2 + sizeof(uint32) * 2 + sizeof(uint16));
	fiInfo.m_u16UnitsPerEm = ReadTTFValue<uint16>(_fFontFile);
	fiInfo.m_fScaleFactor = (_fFontHeightPoints * 96) / (72 * fiInfo.m_u16UnitsPerEm);

	_fFontFile.AdvanceBytes(sizeof(uint64) * 2 + sizeof(FWord) * 4 + sizeof(uint16) * 3);
	fiInfo.m_i16IndexToLocFormat = ReadTTFValue<int16>(_fFontFile);

	_fFontFile.GoToByte(fiInfo.m_tdeHHea.m_u32Offset + sizeof(FixedPoint) + sizeof(FWord) * 8 + sizeof(int16) * 7);
	fiInfo.m_u16NumOfLongHorMetrics = ReadTTFValue<uint16>(_fFontFile);

	_fFontFile.GoToByte(fiInfo.m_tdeCMap.m_u32Offset + sizeof(uint16));
	uint16 u16CMapCount = ReadTTFValue<uint16>(_fFontFile);
	int16 i16UnicodeVersion = -1;
	uint32 u32TableOffset = 0;

	for (int iterations = 0; iterations < u16CMapCount; ++iterations) {
		uint16 u16PlatformID = ReadTTFValue<uint16>(_fFontFile);
		uint16 u16PlatformSpecificID = ReadTTFValue<uint16>(_fFontFile);
		uint32 u32Offset = ReadTTFValue<uint32>(_fFontFile);

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
	uint16 u16TableFormat = ReadTTFValue<uint16>(_fFontFile);

	switch (u16TableFormat) {
	case 4:
		fiInfo.m_cmCMap = ReadCMapFormat4(_fFontFile);
		break;
	case 12:
		fiInfo.m_cmCMap = ReadCMapFormat12(_fFontFile);
	}

    return fiInfo;
}

GlyphInfo FontTTFParser::GetGlyphInfo(File& _fFontFile, const FontInfo& _fiInfo, uint32 _u32GlyphIndex) {
	GlyphInfo giGlyph;

	if (_u32GlyphIndex < _fiInfo.m_u16NumOfLongHorMetrics) {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16) * 2 * _u32GlyphIndex);
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16) * 2 * (_fiInfo.m_u16NumOfLongHorMetrics - 1));
	}

	giGlyph.m_u16AdvanceWidth = ReadTTFValue<uint16>(_fFontFile);
	giGlyph.m_i16LeftSideBearing = ReadTTFValue<int16>(_fFontFile);

	uint32 u32Offset;
	uint32 u32Length;
	if (_fiInfo.m_i16IndexToLocFormat == 0) {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint16)));
		u32Offset = ReadTTFValue<uint16>(_fFontFile) * 2;
		u32Length = (ReadTTFValue<uint16>(_fFontFile) * 2) - u32Offset;
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint32)));
		u32Offset = ReadTTFValue<uint32>(_fFontFile);
		u32Length = ReadTTFValue<uint32>(_fFontFile) - u32Offset;
	}

	if (u32Length == 0) {
		return giGlyph; //If there was no data for this glyph, exit.
	}

	_fFontFile.GoToByte(_fiInfo.m_tdeGlyf.m_u32Offset + u32Offset);

	int16 i16ContourCount = ReadTTFValue<int16>(_fFontFile);

	//ShaderCompiler confusion...? The compiler evaluates these in backwards order when used in the constructor directly.
	//They have to be in separate variables to prevent this. I don't understand...?
	FWord wMinX = ReadTTFValue<FWord>(_fFontFile);
	FWord wMinY = ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxX = ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxY = ReadTTFValue<FWord>(_fFontFile);

	giGlyph.m_v2Min = Vec2F(wMinX, wMinY);
	giGlyph.m_v2Max = Vec2F(wMaxX, wMaxY);

	if (i16ContourCount > 0) {
		Array<uint16> vEndPoints(i16ContourCount);

		for (int iNdx = 0; iNdx < i16ContourCount; ++iNdx) {
			vEndPoints[iNdx] = ReadTTFValue<uint16>(_fFontFile);
		}

		//TODO: Eventually implement a proper interpreter to use the instructions in the font file. Skip for now.
		_fFontFile.AdvanceBytes(ReadTTFValue<uint16>(_fFontFile));

		size_t sVertexCount = (*std::max_element(vEndPoints.begin(), vEndPoints.end())) + 1;

		Array<uint8> vFlags = GetCoordinateFlags(_fFontFile, sVertexCount);

		Array<Vec2F> vCoords = GetCoordinates(_fFontFile, sVertexCount, vFlags);

		giGlyph.m_vVerts = PackVertices(vEndPoints, vCoords, vFlags);
	}
	else if (i16ContourCount < 0) {
		bool bMoreComponents = false;
		do {
			uint16 u16Flags = ReadTTFValue<uint16>(_fFontFile);

			bMoreComponents = Util::IsBitSet(u16Flags, MORE_COMPONENTS);

			uint16 u16GlyphIndex = ReadTTFValue<uint16>(_fFontFile);

			float pfTransform[6] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

			if (Util::IsBitSet(u16Flags, ARGS_ARE_XY_VALUES)) {
				if (Util::IsBitSet(u16Flags, ARG_1_AND_2_ARE_WORDS)) {
					pfTransform[4] = static_cast<float>(ReadTTFValue<int16>(_fFontFile));
					pfTransform[5] = static_cast<float>(ReadTTFValue<int16>(_fFontFile));
				}
				else {
					pfTransform[4] = static_cast<float>(ReadTTFValue<int8>(_fFontFile));
					pfTransform[5] = static_cast<float>(ReadTTFValue<int8>(_fFontFile));
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

Array<uint8> FontTTFParser::GetCoordinateFlags(File& _fFontFile, size_t sVertexCount)
{
	Array<uint8> vFlags(sVertexCount);

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8 u8Flag = ReadTTFValue<uint8>(_fFontFile);

		vFlags[iNdx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8 u8RepeatCount = ReadTTFValue<uint8>(_fFontFile);

			for (int iCount = 0; iCount < u8RepeatCount; ++iCount) {
				vFlags[++iNdx] = u8Flag;
			}
		}
	}

	return vFlags;
}

Array<Vec2F> FontTTFParser::GetCoordinates(File& _fFontFile, const size_t sVertexCount, const Array<uint8>& vFlags)
{
	Array<Vec2F> vVertices(sVertexCount);

	int32 i16XAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8 u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, X_SHORT_VECTOR)) {
			int16 i16Coord = ReadTTFValue<uint8>(_fFontFile);
			i16XAcc += Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP)) {
			i16XAcc += ReadTTFValue<int16>(_fFontFile);
		}
		vVertices[iNdx].x = static_cast<float>(i16XAcc);
	}

	int16 i16YAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8 u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, Y_SHORT_VECTOR)) {
			int16 i16Coord = ReadTTFValue<uint8>(_fFontFile);
			i16YAcc += Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP)) {
			i16YAcc += ReadTTFValue<int16>(_fFontFile);
		}
		vVertices[iNdx].y = static_cast<float>(i16YAcc);
	}

	return vVertices;
}

Array<TTFVertex> FontTTFParser::PackVertices(const Array<uint16>& _vContourEndPoints, const Array<Vec2F>& _vCoordinates, const Array<uint8>& _vFlags) {
	Array<TTFVertex> vVertices;

	if (_vCoordinates.size() < 2) {
		return vVertices;
	}

	int iStartPoint = 0;
	for (int iNdx = 0; iNdx < _vContourEndPoints.size(); ++iNdx) {
		int iNumCoordCount = _vContourEndPoints[iNdx] - iStartPoint + 1;

		Array<Vec2F> vContourCoords;
		Array<uint8> vContourFlags;

		vContourCoords.insert(vContourCoords.end(), _vCoordinates.begin() + iStartPoint, _vCoordinates.begin() + iStartPoint + iNumCoordCount);
		vContourFlags.insert(vContourFlags.end(), _vFlags.begin() + iStartPoint, _vFlags.begin() + iStartPoint + iNumCoordCount);

		Array<TTFVertex> vPackedContourVertices = PackContourVertices(vContourCoords, vContourFlags);

		vVertices.insert(vVertices.end(), vPackedContourVertices.begin(), vPackedContourVertices.end());

		iStartPoint = _vContourEndPoints[iNdx] + 1;
	}

	return vVertices;
}

Array<TTFVertex> FontTTFParser::PackContourVertices(const Array<Vec2F>& _vContourCoords, const Array<uint8>& _vContourFlags) {
	Array<TTFVertex> vPackedVertices;

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
	_fFontFile.Read(&tTag.m_u32TagInt, sizeof(uint32));

	return	tTag == 0x31000000U ||	//TrueType 1 (Tag: 1000)
			tTag == "OTTO" ||		//OpenType with CFF (NOT SUPPORTED YET!)
			tTag == 256U ||			//OpenType 1 (Tag: 0100)
			tTag == "true";			//Apple TrueType
}

TTFTableDirectoryEntry FindTable(File& _fFontFile, uint16 _u16TableCount, uint16 _u16SearchRange, uint16 _u16EntrySelector, uint16 _u16RangeShift, TTFTag _tTag) {
	TTFTableDirectoryEntry tdeEntry;
	TTFTag tCurrentTag;
	size_t sDirectoryStart = sizeof(uint32) + (sizeof(uint16) * 4);

	_fFontFile.GoToByte(sDirectoryStart + (_u16SearchRange - 16)); //Advance to the first item at the _u16RangeShift value.

	_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32));

	if (_tTag == tCurrentTag) {
		tdeEntry.m_u32Checksum = ReadTTFValue<uint32>(_fFontFile);
		tdeEntry.m_u32Offset = ReadTTFValue<uint32>(_fFontFile);
		tdeEntry.m_u32Length = ReadTTFValue<uint32>(_fFontFile);
		return tdeEntry;
	}

	if (_tTag < tCurrentTag) { //We can binary search, thanks to being within the defined area
		int iOffset = _u16SearchRange >> 1;
		for (int iterations = 0; iterations < _u16EntrySelector; ++iterations) {
			_fFontFile.GoToByte(sDirectoryStart + iOffset);

			_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32));

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = ReadTTFValue<uint32>(_fFontFile);
				tdeEntry.m_u32Offset = ReadTTFValue<uint32>(_fFontFile);
				tdeEntry.m_u32Length = ReadTTFValue<uint32>(_fFontFile);
				break;
			}

			iOffset += (_tTag < tCurrentTag) ? -(_u16SearchRange >> (2 + iterations)) : (_u16SearchRange >> (2 + iterations));
		}
	}
	else if (_tTag > tCurrentTag) { //We have to linear search, since we are outside the defined area
		_fFontFile.AdvanceBytes(sizeof(uint32) * 3); //Skip over the first item we checked.

		int iItemCount = (_u16RangeShift / 16);

		for (int iterations = 0; iterations < iItemCount; ++iterations) {
			_fFontFile.Read(&tCurrentTag.m_u32TagInt, sizeof(uint32));

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = ReadTTFValue<uint32>(_fFontFile);
				tdeEntry.m_u32Offset = ReadTTFValue<uint32>(_fFontFile);
				tdeEntry.m_u32Length = ReadTTFValue<uint32>(_fFontFile);
				break;
			}
			_fFontFile.AdvanceBytes(sizeof(uint32) * 3);
		}
	}

	return tdeEntry;
}

CharacterMap ReadCMapFormat4(File& _fFontFile) {
	CharacterMap mCharMap;

	uint16 u16TableLength = ReadTTFValue<uint16>(_fFontFile);

	_fFontFile.AdvanceBytes(sizeof(uint16));

	uint16 u16SegCountX2 = ReadTTFValue<uint16>(_fFontFile);

	_fFontFile.AdvanceBytes(sizeof(uint16) * 3);

	uint32 u32EndCodeArrayHead = _fFontFile.ReaderLocation();
	uint32 u32StartCodeArrayHead = u32EndCodeArrayHead + u16SegCountX2 + 2;
	uint32 u32IdDeltaArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 2) + 2;
	uint32 u32IdRangeArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 3) + 2;
	uint32 u32GlyphIdArrayHead = u32EndCodeArrayHead + (u16SegCountX2 * 4) + 2;
	uint32 u32GlyphArrayLength = (u16TableLength - (u32GlyphIdArrayHead - (u32EndCodeArrayHead - sizeof(uint16) * 7))) >> 1;
	//The 7 here refers to the 7 uint16 values in the table preceeding the start of the end code array.
	// This is so that we can use the table length to calculate the number of glyphs.

	struct Format4Segment {
		uint16 u16EndCode;
		uint16 u16StartCode;
		uint16 u16IdDelta;
		uint16 u16IdRangeOffset;
		uint32 u16IdRangeOffsetLocation;
	};

	Array<Format4Segment> vSegments(u16SegCountX2 >> 1);

	for (int iCount = 0; iCount < (u16SegCountX2 >> 1); ++iCount) {
		uint16 u16ArrayOffset = iCount * sizeof(uint16);

		Format4Segment f4Segment = {
			.u16EndCode = ReadTTFValue<uint16>(_fFontFile, u32EndCodeArrayHead + u16ArrayOffset),
			.u16StartCode = ReadTTFValue<uint16>(_fFontFile, u32StartCodeArrayHead + u16ArrayOffset),
			.u16IdDelta = ReadTTFValue<uint16>(_fFontFile, u32IdDeltaArrayHead + u16ArrayOffset),
			.u16IdRangeOffset = ReadTTFValue<uint16>(_fFontFile, u32IdRangeArrayHead + u16ArrayOffset),
			.u16IdRangeOffsetLocation = u32IdRangeArrayHead + u16ArrayOffset
		};

		vSegments[iCount] = f4Segment;
	}

	for (const auto& aSegment : vSegments) {
		for (uint32 u32GlyphCode = aSegment.u16StartCode; u32GlyphCode <= aSegment.u16EndCode; ++u32GlyphCode) {
			if (aSegment.u16IdRangeOffset == 0) {
				mCharMap[u32GlyphCode] = (aSegment.u16IdDelta + u32GlyphCode) % 65536; //Modding is required thanks to unsigned values used.
			}
			else {
				uint32 u32IndexLocation = aSegment.u16IdRangeOffset + 2 * (u32GlyphCode - aSegment.u16StartCode) + aSegment.u16IdRangeOffsetLocation;
				mCharMap[u32GlyphCode] = ReadTTFValue<uint16>(_fFontFile, u32IndexLocation);
			}
		}
	}

	return mCharMap;
}

CharacterMap ReadCMapFormat12(File& _fFontFile) {
	CharacterMap mCharMap;

	_fFontFile.AdvanceBytes(10); //Skip over Reserved, Length (unneccessary as we have the group count), and Language

	uint32 u32Groups = ReadTTFValue<uint32>(_fFontFile);

	bool bAddedMissingChar = false;
	for (uint32 u32Count = 0; u32Count < u32Groups; ++u32Count) {
		uint32 u32CharStartCode = ReadTTFValue<uint32>(_fFontFile);
		uint32 u32CharEndCode = ReadTTFValue<uint32>(_fFontFile);
		uint32 u32StartGlyphID = ReadTTFValue<uint32>(_fFontFile);

		uint32 u32CharCount = (u32CharEndCode - u32CharStartCode) + 1;

		for (uint32 u32Count = 0; u32Count < u32CharCount; ++u32Count) {
			mCharMap[u32CharStartCode + u32Count] = u32StartGlyphID + u32Count;

			bAddedMissingChar |= (u32StartGlyphID + u32Count) == 0;
		}
	}

	if (!bAddedMissingChar) {
		mCharMap[HC_MISSING_CHAR_GLYPH_INDEX] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
	}

	return mCharMap;
}