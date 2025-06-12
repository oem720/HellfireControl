
#include <Torchlight/Util/FontProcessor.hpp>

#ifdef HC_TESTING_FONT_GLYPH_RASTERIZATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <External/stb/stb_image_write.h>
#define HC_TESTING_PATH(filename) (std::string("./Assets/Font/TestOutput/") + std::to_string((filename)) + std::string(".bmp")).c_str()

#define STB_TRUETYPE_IMPLEMENTATION
#include <External/stb/stb_truetype.h>
#endif

Font FontProcessor::ProcessFont(const std::string& _strFilepath, uint16_t _u16FontHeightPts, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);
	
	TTFFontInfo fiInfo;

	InitializeFont(fFontFile, static_cast<float>(_u16FontHeightPts) * (4.0f / 3.0f), fiInfo);

	TTFGlyphInfo giMissingChar = GetGlyphInfo(fFontFile, fiInfo, 0);

	for (const auto& aCodepoint : fiInfo.m_cmCMap) {
		if (aCodepoint.second == HC_MISSING_CHAR_GLYPH_INDEX) {
			continue;
		}

		TTFGlyphInfo giGlyph = GetGlyphInfo(fFontFile, fiInfo, aCodepoint.second);
	}

	return Font();
}

void FontProcessor::InitializeFont(File& _fFontFile, float _fFontHeightPixels, TTFFontInfo& _fiInfo) {
	if (!IsValidFont(_fFontFile)) {
		throw std::runtime_error("ERROR! INVALID FONT PROVIDED!");
	}

	uint16_t u16TableCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16SearchRange = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16EntrySelector = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	uint16_t u16RangeShift = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fiInfo.m_tdeLoca = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "loca");
	_fiInfo.m_tdeHead = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "head");
	_fiInfo.m_tdeGlyf = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "glyf");
	_fiInfo.m_tdeHHea = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "hhea");
	_fiInfo.m_tdeHMtx = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "hmtx");
	_fiInfo.m_tdeCMap = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "cmap");
	_fiInfo.m_tdeMaxP = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "maxp");
	_fiInfo.m_tdeKern = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "kern");
	_fiInfo.m_tdeGPos = FindTable(_fFontFile, u16TableCount, u16SearchRange, u16EntrySelector, u16RangeShift, "GPOS");

	if (!_fiInfo.m_tdeCMap.IsValid() || !_fiInfo.m_tdeHead.IsValid() || !_fiInfo.m_tdeHMtx.IsValid()) {
		throw std::runtime_error("ERROR: INVALID FONT SUPPLIED!");
	}

	if (_fiInfo.m_tdeGlyf.IsValid()) {
		if (!_fiInfo.m_tdeLoca.IsValid()) {
			throw std::runtime_error("ERROR: MALFORMED FONT SUPPLIED!");
		}
	}
	else {
		//TODO Support CFF Fonts
	}

	if (_fiInfo.m_tdeMaxP.IsValid()) {
		_fFontFile.GoToByte(_fiInfo.m_tdeMaxP.m_u32Offset + sizeof(FixedPoint));
		_fiInfo.m_u16GlyphCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	}

	_fFontFile.GoToByte(_fiInfo.m_tdeHead.m_u32Offset + sizeof(FixedPoint) * 2 + sizeof(uint32_t) * 2 + sizeof(uint16_t));
	_fiInfo.m_u16UnitsPerEm = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	_fFontFile.AdvanceBytes(sizeof(uint64_t) * 2 + sizeof(FWord) * 4 + sizeof(uint16_t) * 3);
	_fiInfo.m_i16IndexToLocFormat = FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(_fiInfo.m_tdeHHea.m_u32Offset + sizeof(FixedPoint));
	FWord ascent = FontUtil::ReadTTFValue<FWord>(_fFontFile);
	FWord descent = FontUtil::ReadTTFValue<FWord>(_fFontFile);
	_fiInfo.m_fScaleFactor = _fFontHeightPixels / static_cast<float>(ascent - descent);
	_fFontFile.AdvanceBytes(sizeof(FWord) * 6 + sizeof(int16_t) * 7);
	_fiInfo.m_u16NumOfLongHorMetrics = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_fiInfo.m_tdeCMap.m_u32Offset + sizeof(uint16_t));
	uint16_t u16CMapCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	int16_t i16UnicodeVersion = -1;
	uint32_t u32TableOffset = 0;

	for (int iterations = 0; iterations < u16CMapCount; ++iterations) {
		uint16_t u16PlatformID = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		uint16_t u16PlatformSpecificID = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		uint32_t u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		
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

	_fFontFile.GoToByte(_fiInfo.m_tdeCMap.m_u32Offset + u32TableOffset);
	uint16_t u16TableFormat = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	switch (u16TableFormat) {
	case 4:
		_fiInfo.m_cmCMap = FontUtil::ReadCMapFormat4(_fFontFile);
		break;
	case 12:
		_fiInfo.m_cmCMap = FontUtil::ReadCMapFormat12(_fFontFile);
	}
}

bool FontProcessor::IsValidFont(File& _fFontFile) {
	TTFTag tTag;
	_fFontFile >> tTag.m_u32TagInt;

	return	tTag == 0x31000000U ||	//TrueType 1 (Tag: 1000)
			tTag == "OTTO" ||		//OpenType with CFF
			tTag == 256U ||			//OpenType 1 (Tag: 0100)
			tTag == "true";			//Apple TrueType
}

TTFTableDirectoryEntry FontProcessor::FindTable(File& _fFontFile, uint16_t _u16TableCount, uint16_t _u16SearchRange, uint16_t _u16EntrySelector, uint16_t _u16RangeShift, TTFTag _tTag) {
	TTFTableDirectoryEntry tdeEntry;
	TTFTag tCurrentTag;
	size_t sDirectoryStart = sizeof(uint32_t) + (sizeof(uint16_t) * 4);

	_fFontFile.GoToByte(sDirectoryStart + _u16SearchRange); //Advance to the first item at the _u16RangeShift value.

	_fFontFile >> tCurrentTag.m_u32TagInt;

	if (_tTag == tCurrentTag) {
		tdeEntry.m_u32Checksum = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		tdeEntry.m_u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		tdeEntry.m_u32Length = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		return tdeEntry;
	}

	if (_tTag < tCurrentTag) { //We can binary search, thanks to being within the defined area
		int iOffset = _u16SearchRange >> 1;
		for (int iterations = 0; iterations < _u16EntrySelector; ++iterations) {
			_fFontFile.GoToByte(sDirectoryStart + iOffset);

			_fFontFile >> tCurrentTag.m_u32TagInt;

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Length = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				break;
			}
			
			iOffset += (_tTag < tCurrentTag) ? -(_u16SearchRange >> (2 + iterations)) : (_u16SearchRange >> (2 + iterations));
		}
	}
	else if (_tTag > tCurrentTag) { //We have to linear search, since we are outside the defined area
		_fFontFile.AdvanceBytes(sizeof(uint32_t) * 3); //Skip over the first item we checked.

		int iItemCount = (_u16RangeShift / 16) - 1;

		for (int iterations = 0; iterations < iItemCount; ++iterations) {
			_fFontFile >> tCurrentTag.m_u32TagInt;

			if (_tTag == tCurrentTag) {
				tdeEntry.m_u32Checksum = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				tdeEntry.m_u32Length = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
				break;
			}
			_fFontFile.AdvanceBytes(sizeof(uint32_t) * 3);
		}
	}

	return tdeEntry;
}

TTFGlyphInfo FontProcessor::GetGlyphInfo(File& _fFontFile, const TTFFontInfo& _fiInfo, uint32_t _u32GlyphIndex) {
	TTFGlyphInfo giGlyph;

	if (_u32GlyphIndex < _fiInfo.m_u16NumOfLongHorMetrics) {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16_t) * 2 * _u32GlyphIndex);
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeHMtx.m_u32Offset + sizeof(uint16_t) * 2 * (_fiInfo.m_u16NumOfLongHorMetrics - 1));
	}

	giGlyph.m_u16AdvanceWidth = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	giGlyph.m_i16LeftSideBearing = FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	uint32_t u32Offset;
	uint32_t u32Length;
	if (_fiInfo.m_i16IndexToLocFormat == 0) {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint16_t)));
		u32Offset = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		u32Length = FontUtil::ReadTTFValue<uint16_t>(_fFontFile) - u32Offset;
	}
	else {
		_fFontFile.GoToByte(_fiInfo.m_tdeLoca.m_u32Offset + (_u32GlyphIndex * sizeof(uint32_t)));
		u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		u32Length = FontUtil::ReadTTFValue<uint32_t>(_fFontFile) - u32Offset;
	}

	if (u32Length == 0) {
		return giGlyph; //If there was no data for this glyph, exit.
	}

	_fFontFile.GoToByte(_fiInfo.m_tdeGlyf.m_u32Offset + u32Offset);

	int16_t i16ContourCount = FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	//Compiler confusion...? The compiler evaluates these in backwards order when used in the constructor directly.
	//They have to be in separate variables to prevent this. I don't understand...?
	FWord wMinX = FontUtil::ReadTTFValue<FWord>(_fFontFile);
	FWord wMinY = FontUtil::ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxX = FontUtil::ReadTTFValue<FWord>(_fFontFile);
	FWord wMaxY = FontUtil::ReadTTFValue<FWord>(_fFontFile);

	giGlyph.m_v2Min = Vec2F(wMinX, wMinY);
	giGlyph.m_v2Max = Vec2F(wMaxX, wMaxY);

	if (i16ContourCount > 0) {
		std::vector<uint16_t> vEndPoints(i16ContourCount);

		for (int iNdx = 0; iNdx < i16ContourCount; ++iNdx) {
			vEndPoints[iNdx] = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		//TODO: Eventually implement a proper interpreter to use the instructions in the font file. Skip for now.
		_fFontFile.AdvanceBytes(FontUtil::ReadTTFValue<uint16_t>(_fFontFile));

		size_t sVertexCount = (*std::max_element(vEndPoints.begin(), vEndPoints.end())) + 1;

		std::vector<uint8_t> vFlags = GetCoordinateFlags(_fFontFile, sVertexCount);

		std::vector<Vec2F> vCoords = GetCoordinates(_fFontFile, sVertexCount, vFlags);

		giGlyph.m_vVerts = PackVertices(vEndPoints, vCoords, vFlags);
	}
	else if (i16ContourCount < 0) {

	}

	return giGlyph;
}

std::vector<uint8_t> FontProcessor::GetCoordinateFlags(File& _fFontFile, size_t sVertexCount)
{
	std::vector<uint8_t> vFlags(sVertexCount);

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

		vFlags[iNdx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

			for (int iCount = 0; iCount < u8RepeatCount; ++iCount) {
				vFlags[++iNdx] = u8Flag;
			}
		}
	}

	return vFlags;
}

std::vector<Vec2F> FontProcessor::GetCoordinates(File& _fFontFile, const size_t sVertexCount, const std::vector<uint8_t>& vFlags)
{
	std::vector<Vec2F> vVertices(sVertexCount);

	int32_t i16XAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, X_SHORT_VECTOR)) {
			int16_t i16Coord = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);
			i16XAcc += Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, X_SIGN_OR_SKIP)) {
			i16XAcc += FontUtil::ReadTTFValue<int16_t>(_fFontFile);
		}
		vVertices[iNdx].x = static_cast<float>(i16XAcc);
	}

	int16_t i16YAcc = 0;

	for (int iNdx = 0; iNdx < sVertexCount; ++iNdx) {
		uint8_t u8Flag = vFlags[iNdx];
		if (Util::IsBitSet(u8Flag, Y_SHORT_VECTOR)) {
			int16_t i16Coord = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);
			i16YAcc += Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP) ? i16Coord : -i16Coord;
		}
		else if (!Util::IsBitSet(u8Flag, Y_SIGN_OR_SKIP)) {
			i16YAcc += FontUtil::ReadTTFValue<int16_t>(_fFontFile);
		}
		vVertices[iNdx].y = static_cast<float>(i16YAcc);
	}

	return vVertices;
}

std::vector<TTFVertex> FontProcessor::PackVertices(const std::vector<uint16_t>& _vContourEndPoints, const std::vector<Vec2F>& _vCoordinates, const std::vector<uint8_t>& _vFlags) {
	std::vector<TTFVertex> vVertices;

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

std::vector<TTFVertex> FontProcessor::PackContourVertices(const std::vector<Vec2F>& _vContourCoords, const std::vector<uint8_t>& _vContourFlags) {
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
					TTFVertexType::QUADRATIC_CURVE }
				);
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
