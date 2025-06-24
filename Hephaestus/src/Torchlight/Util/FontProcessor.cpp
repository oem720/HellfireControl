
#include <Torchlight/Util/FontProcessor.hpp>

#ifdef HC_TESTING_FONT_GLYPH_RASTERIZATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <External/stb/stb_image_write.h>
#define HC_TESTING_PATH(filename) (std::string("./Assets/Fonts/TestOutput/") + std::string((filename)) + std::string(".bmp")).c_str()

#define STB_TRUETYPE_IMPLEMENTATION
#include <External/stb/stb_truetype.h>
#endif

Font FontProcessor::ProcessFont(const std::string& _strFilepath, uint16_t _u16FontHeightPts, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);
	
	TTFFontInfo fiInfo;

	InitializeFont(fFontFile, static_cast<float>(_u16FontHeightPts), fiInfo);

	std::vector<TTFGlyphInfo> vGlyphData;

	for (const auto& aCodepoint : fiInfo.m_cmCMap) {
		TTFGlyphInfo giInfo = GetGlyphInfo(fFontFile, fiInfo, aCodepoint.second);

		vGlyphData.push_back(giInfo);
	}

	Vec2F v2BitmapSize = GetFontAtlasSize(vGlyphData, fiInfo);

	Image iBitmap(static_cast<uint32_t>(v2BitmapSize.x), static_cast<uint32_t>(v2BitmapSize.y));

	TTFGlyphInfo missingChar = GetGlyphInfo(fFontFile, fiInfo, fiInfo.m_cmCMap[0xFFFF]);

	TTFBakedGlyphInfo missingCharInfo;
	float spacing = 0;
	for (int count = 0; count < 5; ++count) {
		missingCharInfo = DrawGlyph(iBitmap, missingChar, Vec2F(spacing, 0.0f), fiInfo.m_fScaleFactor * (1 << count));
		spacing += Math::Ceiling(missingCharInfo.m_AdvanceWidth);
	}
	
	stbi_write_bmp(HC_TESTING_PATH("HC_FONT"), iBitmap.GetWidth(), iBitmap.GetHeight(), 3, iBitmap.GetPixelData().get());

	File temp(_strFilepath, FILE_OPEN_FLAG_BINARY | FILE_OPEN_FLAG_BLOB);

	unsigned char* pixels = new unsigned char[iBitmap.GetWidth() * iBitmap.GetHeight()];
	stbtt_bakedchar* chars = new stbtt_bakedchar[vGlyphData.size()];

	stbtt_BakeFontBitmap(reinterpret_cast<const unsigned char*>(temp.GetFileBlob().data()), 0, static_cast<float>(_u16FontHeightPts) * (4.0f / 3.0f), pixels, iBitmap.GetWidth(), iBitmap.GetHeight(), 0, vGlyphData.size(), chars);

	stbi_write_bmp(HC_TESTING_PATH("STB_FONT"), iBitmap.GetWidth(), iBitmap.GetHeight(), 1, pixels);

	return Font();
}

void FontProcessor::InitializeFont(File& _fFontFile, float _fFontHeightPoints, TTFFontInfo& _fiInfo) {
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
	_fiInfo.m_fScaleFactor = (_fFontHeightPoints * 96) / (72 * _fiInfo.m_u16UnitsPerEm);

	_fFontFile.AdvanceBytes(sizeof(uint64_t) * 2 + sizeof(FWord) * 4 + sizeof(uint16_t) * 3);
	_fiInfo.m_i16IndexToLocFormat = FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(_fiInfo.m_tdeHHea.m_u32Offset + sizeof(FixedPoint) + sizeof(FWord) * 8 + sizeof(int16_t) * 7);
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
			tTag == "OTTO" ||		//OpenType with CFF (NOT SUPPORTED YET!)
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
		u32Offset = FontUtil::ReadTTFValue<uint16_t>(_fFontFile) * 2;
		u32Length = (FontUtil::ReadTTFValue<uint16_t>(_fFontFile) * 2)- u32Offset;
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
		bool bMoreComponents = false;
		do {
			uint16_t u16Flags = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		
			bMoreComponents = Util::IsBitSet(u16Flags, MORE_COMPONENTS);
		
		} while (bMoreComponents);
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

Vec2F FontProcessor::GetFontAtlasSize(std::vector<TTFGlyphInfo>& vGlyphData, TTFFontInfo& fiInfo)
{
	Vec2F v2GlyphSize;
	for (const auto& aGlyph : vGlyphData) {
		v2GlyphSize += (aGlyph.m_v2Max - aGlyph.m_v2Min) * fiInfo.m_fScaleFactor;
	}

	v2GlyphSize /= vGlyphData.size();

	uint32_t u32RowCount = static_cast<uint32_t>(Math::Ceiling(Math::Sqrt(static_cast<float>(vGlyphData.size()))));
	uint32_t u32ColCount = static_cast<uint32_t>(Math::Ceiling(vGlyphData.size() / static_cast<float>(u32RowCount)));

	uint32_t u32Width = static_cast<uint32_t>(Math::Ceiling(u32ColCount * v2GlyphSize.x));
	uint32_t u32Height = static_cast<uint32_t>(Math::Ceiling(u32RowCount * v2GlyphSize.y));

	if (u32Width < u32Height) {
		u32Width = u32Width ^ u32Height;
		u32Height = u32Width ^ u32Height;
		u32Width = u32Width ^ u32Height;
	}

	return Vec2F(static_cast<float>(u32Width), static_cast<float>(u32Height));
}

TTFBakedGlyphInfo FontProcessor::DrawGlyph(Image& _iBitmap, const TTFGlyphInfo& _tGlyphData, const Vec2F& _v2Location, const float _fScale) {
	Vec4F v4BoundingBox = CalculateScaledBoundingVolume(_v2Location, _tGlyphData.m_v2Min.y, _tGlyphData.m_v2Max.y, _tGlyphData.m_u16AdvanceWidth, _fScale);

	std::vector<TTFEdge> vEdges = PackAndFlattenContours(_tGlyphData, v4BoundingBox, _fScale);

	std::vector<TTFEdge> vActiveEdges;
	
	float fScanlineY = 0.5f;
	int iScanlineXStart = static_cast<int>(v4BoundingBox.x);
	int iScanlineXEnd = static_cast<int>(Math::Clamp(Math::Ceiling(v4BoundingBox.z), 0.0f, static_cast<float>(_iBitmap.GetWidth())));
	
	while (fScanlineY < v4BoundingBox.w + HC_EPSILON && (vEdges.size() > 0 || vActiveEdges.size() > 0)) {
		//First check for active edges
		for (int iNdx = 0; iNdx < vEdges.size(); ++iNdx) {
			if (vEdges[iNdx].m_v2Min.y > (fScanlineY - 0.5f)) {
				break;
			}

			vActiveEdges.push_back(vEdges[iNdx]);
			vEdges.erase(vEdges.begin() + iNdx--);
		}

		if (vActiveEdges.size() == 0) {
			fScanlineY += 1.0f;
			continue;
		}

		//Next sort the active edges on X
		std::sort(
			vActiveEdges.begin(),
			vActiveEdges.end(),
			[](const TTFEdge& _left, const TTFEdge& _right) { return _left.m_fXCurrent < _right.m_fXCurrent; }
		);

		//Fill pixels between the X values. This needs to include the antialiasing step.
		//Because we have packed the bounding box into a Vec4, to grab the bounds, use the x and z values
		//The end value is clamped to the edge of the bitmap and is always overestimated based on the bounding box.
		for (int iScanlineX = iScanlineXStart; iScanlineX <= iScanlineXEnd; ++iScanlineX) {
			int iIntersectionCount = 0;

			for (const auto& aEdge : vActiveEdges) {
				//We check for infinite slope to skip horizontal lines. Those are infinite because we have an inverted slope.
				if (iScanlineX > aEdge.m_fXCurrent || std::isinf(aEdge.m_fSlope)) {
					continue;
				}

				iIntersectionCount += aEdge.m_bDownward ? -1 : 1;
			}

			if (iIntersectionCount != 0) {
				_iBitmap.PlotPixel(iScanlineX, static_cast<int>(fScanlineY), {0xFF, 0xFF, 0xFF});
			}
		}

		fScanlineY += 1.0f;

		//Check active edge Y and remove those that are below the bottom of the pixel.
		for (int iNdx = 0; iNdx < vActiveEdges.size(); ++iNdx) {
			if (vActiveEdges[iNdx].m_v2Max.y <= (fScanlineY - 0.5f)) {
				vActiveEdges.erase(vActiveEdges.begin() + iNdx--);
				continue;
			}

			//SPECIAL CASE: Vertical lines have 0 slope (due to the fact that slope is inverted) and as such do not have any updating to do.
			if (HC_FLOAT_COMPARE(vActiveEdges[iNdx].m_fSlope, 0.0f)) {
				continue;
			}

			//vActiveEdges[iNdx].m_fXCurrent = (fScanlineY - vActiveEdges[iNdx].m_v2Min.y) / vActiveEdges[iNdx].m_fSlope;
			//vActiveEdges[iNdx].m_fXCurrent = (fScanlineY / vActiveEdges[iNdx].m_fSlope);
			vActiveEdges[iNdx].m_fXCurrent += vActiveEdges[iNdx].m_fSlope;
		}
	}

	return {
		.m_v4BoundingBox = v4BoundingBox,
		.m_AdvanceWidth = Math::Ceiling(static_cast<float>(_tGlyphData.m_u16AdvanceWidth) * _fScale)
	};
}

Vec4F FontProcessor::CalculateScaledBoundingVolume(const Vec2F& _v2Location, const float _fYMin, const float _fYMax, const uint16_t _u16AdvanceWidth, const float _fScale) {
	return Vec4F(_v2Location, Math::Ceiling(Vec2F(_v2Location.x + (static_cast<float>(_u16AdvanceWidth) * _fScale), (_fYMax - _fYMin) * _fScale)));
}

std::vector<TTFEdge> FontProcessor::PackAndFlattenContours(const TTFGlyphInfo& _tGlyphData, const Vec4F& _v4BoundingBox, const float _fScale) {
	std::vector<std::vector<TTFVertex>> vContours;

	//First we pack the contours into separate lists in preparation of subdividing curves.
	for (int iNdx = 0, iContourCount = 0; iNdx < _tGlyphData.m_vVerts.size(); ++iNdx) {
		if (_tGlyphData.m_vVerts[iNdx].m_vtType == TTFVertexType::CONTOUR_START) {
			vContours.push_back(std::vector<TTFVertex>());
			iContourCount++;
		}

		TTFVertex vVert = _tGlyphData.m_vVerts[iNdx];
		
		//First we need to flip the point over the X axis and then scale
		vVert.m_v2Vert *= Vec2F(1, -1) * _fScale;
		//This is followed by shifting it upward by the bottom Y and then left by the top X
		vVert.m_v2Vert += _v4BoundingBox.XW();


		vContours[iContourCount - 1].push_back(vVert);
	}

	//Then we flatten the contours into straight lines.
	for (auto& aContour : vContours) {
		for (int iNdx = 0; iNdx < aContour.size() - 1; ++iNdx) {
			switch (aContour[(iNdx + 1) % aContour.size()].m_vtType) {
			case TTFVertexType::CONTOUR_START:
			case TTFVertexType::LINE_SEGMENT:
				continue; //We can skip processing here.
				
			case TTFVertexType::QUADRATIC_CURVE:

				break;
			case TTFVertexType::CUBIC_CURVE:
				
				break;
			}
		}
	}

	//Finally, we pack the newly flattened contours into the edge list and sort.
	std::vector<TTFEdge> vPackedVertices;
	for (const auto& aContour : vContours) {
		for (int iNdx = 0; iNdx < aContour.size(); ++iNdx) {
			Vec2F vMin = aContour[iNdx].m_v2Vert;
			Vec2F vMax = aContour[(iNdx + 1) % aContour.size()].m_v2Vert;
			bool bDownward = false;

			if (vMin.y > vMax.y) {
				Vec2F vTemp = vMin;
				vMin = vMax;
				vMax = vTemp;
				bDownward = true;
			}

			vPackedVertices.push_back({
				.m_v2Min = vMin,
				.m_v2Max = vMax,
				.m_fSlope = (vMax.x - vMin.x) / (vMax.y - vMin.y),
				.m_fXCurrent = vMin.x,
				.m_bDownward = bDownward
			});
		}
	}

	std::sort(
		vPackedVertices.begin(),
		vPackedVertices.end(),
		[](const TTFEdge& _left, const TTFEdge& _right) { return _left.m_v2Min.y < _right.m_v2Min.y; }
	);

	return vPackedVertices;
}
