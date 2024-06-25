
#include <Torchlight/Util/FontProcessor.hpp>

#include <HellfireControl/Asset/Font.hpp>

void FontProcessor::ProcessFont(const std::string& _strFilepath) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY); //Open file in binary

	std::map<std::string, uint32_t> mDataBlockLocations;
	
	GetDataBlockOffsets(fFontFile, mDataBlockLocations);

	std::vector<uint32_t> vGlyphOffsets;
	uint16_t u16Resolution = 0;

	GetGlyphOffsets(fFontFile, mDataBlockLocations, vGlyphOffsets, u16Resolution);

	std::vector<TTFGlyphData> vGlyphData(vGlyphOffsets.size()); //Size of the list is the size of the number of locations

	uint32_t u32GlyphTableStart = mDataBlockLocations["glyf"];

	for (int ndx = 0; ndx < vGlyphData.size(); ++ndx) {
		fFontFile.GoToByte(u32GlyphTableStart + vGlyphOffsets[ndx]);

		ParseGlyph(fFontFile, vGlyphData[ndx]); //Parse the glyph individually
	}

	CreateGlyphBitmaps(vGlyphData, u16Resolution);
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

void FontProcessor::GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphOffsets, uint16_t& _u16OutPixelsPerEm) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["head"]);

	_fFontFile.AdvanceBytes(18);

	_u16OutPixelsPerEm = ReadTTFValue<uint16_t>(_fFontFile);

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
		.m_fYMin = ReadTTFValue<FWord>(_fFontFile),
		.m_fXMax = ReadTTFValue<FWord>(_fFontFile),
		.m_fYMax = ReadTTFValue<FWord>(_fFontFile)
	};

	if (_gdOutGlyphData.first.m_i16ContourCount < 0) {
		_gdOutGlyphData.second = ParseCompoundGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount);
	}
	else {
		_gdOutGlyphData.second = ParseSimpleGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount, _gdOutGlyphData.first.m_fXMin, _gdOutGlyphData.first.m_fYMin);
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

std::unique_ptr<FontProcessor::TTFSimpleGlyph> FontProcessor::ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, uint32_t _u32MinX, uint32_t _u32MinY) {
	auto aSimpleGlyph = std::make_unique<TTFSimpleGlyph>();

	if (_i16ContourCount == 0) {
		return aSimpleGlyph; //No data to read...
	}

	std::vector<uint16_t> vContourEndPts(_i16ContourCount);

	for (int ndx = 0; ndx < _i16ContourCount; ++ndx) {
		vContourEndPts[ndx] = ReadTTFValue<uint16_t>(_fFontFile);
	}

	//aSimpleGlyph->m_vInstructions.resize(ReadTTFValue<uint16_t>(_fFontFile));
	//
	//for (int ndx = 0; ndx < aSimpleGlyph->m_vInstructions.size(); ++ndx) {
	//	aSimpleGlyph->m_vInstructions[ndx] = ReadTTFValue<uint8_t>(_fFontFile);
	//}

	_fFontFile.AdvanceBytes(ReadTTFValue<int16_t>(_fFontFile));

	//Get the largest contour end point index and add 1 (1 based count). This will equal the count of points
	int iNumPoints = 1 + (*std::max_element(vContourEndPts.begin(), vContourEndPts.end()));

	std::vector<uint8_t> vFlags(iNumPoints);
	std::vector<TTFPoint> vPoints(iNumPoints);

	for (int ndx = 0; ndx < iNumPoints; ++ndx) {
		uint8_t u8Flag = ReadTTFValue<uint8_t>(_fFontFile);

		vFlags[ndx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = ReadTTFValue<uint8_t>(_fFontFile);

			for (int iFlagCount = 0; iFlagCount < u8RepeatCount; ++iFlagCount) {
				vFlags[++ndx] = u8Flag;
			}
		}
	}

	ParseCoordinates(_fFontFile, vFlags, true, vPoints, _u32MinX, _u32MinY);
	ParseCoordinates(_fFontFile, vFlags, false, vPoints, _u32MinX, _u32MinY);

	int iContourStart = 0;

	for (int ndx = 0; ndx < vContourEndPts.size(); ++ndx) {
		std::vector<TTFPoint> vContourPoints;
		TTFContour tContour;

		int iNumPointsInContour = vContourEndPts[ndx] - iContourStart + 1;

		vContourPoints.insert(vContourPoints.end(), vPoints.begin() + iContourStart, vPoints.begin() + iContourStart + iNumPointsInContour);

		int iPointOffset = GetPointOffset(vContourPoints);

		RecreateImpliedPoints(vContourPoints, iPointOffset);

		for (int sNdx = iPointOffset; sNdx < vContourPoints.size(); sNdx += 2) {
			tContour.m_vCurves.push_back({ vContourPoints[sNdx],
								vContourPoints[(sNdx + 1) % vContourPoints.size()],
								vContourPoints[(sNdx + 2) % vContourPoints.size()] });
		}

		MakeContourCurvesMonotonic(tContour);

		aSimpleGlyph->m_vContours.push_back(tContour);

		iContourStart = vContourEndPts[ndx] + 1;
	}

	for (int oNdx = 0; oNdx < aSimpleGlyph->m_vContours.size(); ++oNdx) {
		for (int iNdx = 0; iNdx < aSimpleGlyph->m_vContours.size(); ++iNdx) {
			if (iNdx == oNdx) continue; //If the two contours we're checking are the same, skip

			//Check if the contour is contained in another one
			CheckContourContained(aSimpleGlyph->m_vContours[oNdx], aSimpleGlyph->m_vContours[iNdx]);
		}
	}
	
	return std::move(aSimpleGlyph);
}

std::unique_ptr<FontProcessor::TTFCompoundGlyph> FontProcessor::ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount) {
	auto aCompoundGlyph = std::make_unique<TTFCompoundGlyph>();

	return std::move(aCompoundGlyph);
}

void FontProcessor::ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, bool _bIsX, std::vector<TTFPoint>& _vOutCoordinates, uint32_t _u32MinX, uint32_t _u32MinY) {
	int iOffsetSizeFlagBit = _bIsX ? IS_SINGLE_BYTE_X : IS_SINGLE_BYTE_Y;
	int iOffsetSignOrSkipBit = _bIsX ? INSTRUCTION_X : INSTRUCTION_Y;

	int iCoordValue = 0;
	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		uint8_t u8Flag = _vFlags[ndx];

		if (Util::IsBitSet(u8Flag, iOffsetSizeFlagBit)) {
			int iOffset = ReadTTFValue<uint8_t>(_fFontFile);
			iCoordValue += Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit) ? iOffset : -iOffset;
		}
		else if (!Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit)) {
			iCoordValue += ReadTTFValue<int16_t>(_fFontFile);
		}

		if (_bIsX) {
			_vOutCoordinates[ndx].x = iCoordValue;
			_vOutCoordinates[ndx].x -= _u32MinX;
		}
		else {
			_vOutCoordinates[ndx].y = iCoordValue;
			_vOutCoordinates[ndx].y -= _u32MinY;
		}

		_vOutCoordinates[ndx].onCurve = Util::IsBitSet(u8Flag, ON_CURVE);

		_vOutCoordinates[ndx].pointNumber = ndx;
	}
}

int FontProcessor::GetPointOffset(const std::vector<TTFPoint>& _vPoints) {
	int iPointOffset;
	for (iPointOffset = 0; iPointOffset < _vPoints.size(); ++iPointOffset) {
		if (_vPoints[iPointOffset].onCurve) break;
	}

	return iPointOffset;
}

/// <summary>
/// Credit to Sebastian Lague: https://github.com/SebLague/Text-Rendering/tree/main
/// </summary>
void FontProcessor::RecreateImpliedPoints(std::vector<TTFPoint>& _vPoints, int _iPointOffset) {

	std::vector<TTFPoint> vNewPoints;
	for (int ndx = 0; ndx < _vPoints.size(); ++ndx) {
		TTFPoint curr = _vPoints[(ndx + _iPointOffset) % _vPoints.size()];
		TTFPoint next = _vPoints[(ndx + _iPointOffset + 1) % _vPoints.size()];
		vNewPoints.push_back(curr);

		if (curr.onCurve == next.onCurve && ndx < _vPoints.size()) {
			TTFPoint mid = { (curr.x + next.x) / 2, (curr.y + next.y) / 2 };
			mid.pointNumber = static_cast<float>(ndx) + 0.5f;
			vNewPoints.push_back(mid);
		}
	}
	_vPoints = vNewPoints;
}

/// <summary>
/// Credit to Sebastian Lague: https://github.com/SebLague/Text-Rendering/tree/main
/// </summary>
void FontProcessor::MakeContourCurvesMonotonic(TTFContour& _tContour) {
	TTFContour tMonotonicContour;

	for (auto& aCurve : _tContour.m_vCurves) {
		TTFCurve tMonotonicCurveA = {};
		TTFCurve tMonotonicCurveB = {};

		tMonotonicCurveA.m_p0 = aCurve.m_p0; //First point will always be valid.

		if (aCurve.m_p1.y < std::min(aCurve.m_p0.y, aCurve.m_p2.y) || aCurve.m_p1.y > std::min(aCurve.m_p0.y, aCurve.m_p2.y)) {
			auto aSplit = SplitCurveAtTurningPoint(aCurve);

			tMonotonicCurveA = { tMonotonicCurveA.m_p0, aSplit[0], aSplit[1] };
			tMonotonicCurveB = { aSplit[1], aSplit[2], aSplit[3] };
		}
		else {
			tMonotonicCurveA.m_p1 = aCurve.m_p1;
			tMonotonicCurveA.m_p2 = aCurve.m_p2;
		}

		if (tMonotonicCurveA.IsValid()) { tMonotonicContour.m_vCurves.push_back(tMonotonicCurveA); }
		if (tMonotonicCurveB.IsValid()) { tMonotonicContour.m_vCurves.push_back(tMonotonicCurveB); }
	}
}

/// <summary>
/// Credit to Sebastian Lague: https://github.com/SebLague/Text-Rendering/tree/main
/// </summary>
std::vector<FontProcessor::TTFPoint> FontProcessor::SplitCurveAtTurningPoint(const TTFCurve& _tCurve) {
	Vec2F p0(_tCurve.m_p0.x, _tCurve.m_p0.y);
	Vec2F p1(_tCurve.m_p1.x, _tCurve.m_p1.y);
	Vec2F p2(_tCurve.m_p2.x, _tCurve.m_p2.y);

	Vec2F a = p0 - (2.0f * p1) + p2;
	Vec2F b = 2 * (p1 - p0);
	Vec2F c = p0;

	float fT = -b.y / (2.0f * a.y);

	Vec2F vec2TurningPoint = (a * (fT * fT)) + (b * fT) + c;

	float fP1AX = p0.x + b.x * ((vec2TurningPoint.y - p0.y) / b.y);

	float fP1BX = p2.x + (2.0f * a.x + b.x) * ((vec2TurningPoint.y - p2.y) / (2.0f * a.y + b.y));

	std::vector<TTFPoint> vPoints(4);

	vPoints[0] = { (int16_t)fP1AX, (int16_t)vec2TurningPoint.y };
	vPoints[1] = { (int16_t)vec2TurningPoint.x, (int16_t)vec2TurningPoint.y };
	vPoints[2] = { (int16_t)fP1BX, (int16_t)vec2TurningPoint.y };
	vPoints[3] = { _tCurve.m_p2 };

	return vPoints;
}

void FontProcessor::CheckContourContained(TTFContour& _tContour, const TTFContour& _tPossibleOuter) {
	for (const auto& aCurve : _tContour.m_vCurves) {
		//Run our point check on every point in the curve against the outer contour.
		//Because p1 is a control point, and therefore is never directly hit, it can be safely skipped.
		//This may lead to an edge case below when testing for the curves to cross, but that edge case
		//is unlikely to ever be hit.
		if (!CheckPointInContour(aCurve.m_p0, _tPossibleOuter) || !CheckPointInContour(aCurve.m_p2, _tPossibleOuter)) {
			return;
		}
	}

	//It's here that the edge case may arise -- this test only checks straight line segments against
	//each other. Therefore, it may have a problem if multiple curves are close together, since the data
	//will be too granular. This is not an issue for 99.999999% of fonts, so it is not an issue to worry
	//about right now.
	if (CheckCurveOutlineIntersection(_tContour, _tPossibleOuter)) {
		return;
	}

	//If it never hits any of the early outs, flip the hole boolean.
	_tContour.m_bIsHole = !_tContour.m_bIsHole;
}

bool FontProcessor::CheckCurveOutlineIntersection(const TTFContour& _tContourA, const TTFContour& _tContourB) {
	for (const auto& aInnerCurve : _tContourA.m_vCurves) {
		for (const auto& aOuterCurve : _tContourB.m_vCurves) {
			if (CheckLineIntersection(aInnerCurve, aOuterCurve)) {
				return true;
			}
		}
	}

	return false;
}

bool FontProcessor::CheckPointInContour(const TTFPoint& _tPoint, const TTFContour& _tPossibleOuter) {
	std::vector<TTFPoint> vVertices;

	//Unpack curves into a list of vertices for the contour. We do not use the control point for testing.
	for (const auto& aCurve : _tPossibleOuter.m_vCurves) {
		vVertices.push_back(aCurve.m_p0);
		vVertices.push_back(aCurve.m_p2);
	}

	bool bIsInside = false;

	for (int iLeft = 0, iRight = vVertices.size() - 1; iLeft < vVertices.size(); ++iLeft) {
		if ((vVertices[iLeft].y < _tPoint.y && vVertices[iRight].y >= _tPoint.y) ||
			(vVertices[iRight].y < _tPoint.y && vVertices[iLeft].y >= _tPoint.y)) {
			float fTest = vVertices[iLeft].x + static_cast<float>(_tPoint.y - vVertices[iLeft].y) / static_cast<float>(vVertices[iRight].y - vVertices[iLeft].y) * static_cast<float>(vVertices[iRight].x - vVertices[iLeft].x);

			if (fTest < _tPoint.x) {
				bIsInside = !bIsInside;
			}
		}
		iRight = iLeft;
	}

	return bIsInside;
}

bool FontProcessor::CheckLineIntersection(const TTFCurve& _tCurveA, const TTFCurve& _tCurveB) {
	Vec2F A = Vec2F(_tCurveA.m_p0.x, _tCurveA.m_p0.y);
	Vec2F B = Vec2F(_tCurveA.m_p2.x, _tCurveA.m_p2.y);

	Vec2F C = Vec2F(_tCurveB.m_p0.x, _tCurveB.m_p0.y);
	Vec2F D = Vec2F(_tCurveB.m_p2.x, _tCurveB.m_p2.y);

	Vec2F r = B - A;
	Vec2F s = D - C;

	float fNumerator = Cross(C - A, r);
	float fDenominator = Cross(r, s);

	if (fNumerator == 0.0f && fDenominator == 0.0f) {
		if (A == C || A == D || B == C || B == D) {
			return true;
		}

		return !((C.x - A.x < 0.0f) == (C.x - B.x < 0.0f) == (D.x - A.x < 0.0f) == (D.x - B.x < 0.0f)) ||
			   !((C.y - A.y < 0.0f) == (C.y - B.y < 0.0f) == (D.y - A.y < 0.0f) == (D.y - B.y < 0.0f));
	}

	if (fDenominator == 0.0f) {
		return false; //Parallel lines
	}

	float u = fNumerator / fDenominator;
	float t = Cross(C - A, s) / fDenominator;

	return (t >= 0.0f) && (t <= 1.0f) && (u >= 0.0f) && (u <= 1.0f); 
}

void FontProcessor::CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, uint16_t _u16PixelsPerEm) {
	int glyphCount = 0;

	for (const auto& glyph : _vGlyphs) {
		//if (glyphCount >= 10) {
		//	break; //Don't fill my file system with CRAP!
		//}

		uint32_t bitmapWidth = (glyph.first.m_fXMax - glyph.first.m_fXMin) + 1;
		uint32_t bitmapHeight = (glyph.first.m_fYMax - glyph.first.m_fYMin) + 1;

		std::vector<uint32_t> vRaster(bitmapWidth * bitmapHeight, 0);

		if (glyph.first.m_i16ContourCount > 0) {
			TTFSimpleGlyph* glyphData = (TTFSimpleGlyph*)glyph.second.get();

			FillGlyph(vRaster, bitmapWidth, bitmapHeight, 0xFFFFFFFF, glyphData->m_vContours);
		
			for (int ndx = 0; ndx < glyphData->m_vContours.size(); ++ndx) {
				for (TTFCurve& curve : glyphData->m_vContours[ndx].m_vCurves) {
					DrawBezierCurve(vRaster, curve.m_p0, curve.m_p1, curve.m_p2, 0xFFFF0000, 28, bitmapWidth);
				}				
			}
		}
		else {
			continue; //Skip Compound Glyphs, as they require a different rasterization setup.
		}

		FlipImageVertically(vRaster, bitmapWidth, bitmapHeight);

		SaveToFile(vRaster, bitmapWidth, bitmapHeight, glyphCount);

 		glyphCount++;
	}
}

void FontProcessor::FlipImageVertically(std::vector<uint32_t>& _vBitmap, uint32_t _u32Width, uint32_t _u32Height) {
	std::vector<std::vector<uint32_t>> vRows;
	for (int iRow = 0; iRow < _u32Height; ++iRow) {
		int iRowStart = iRow * _u32Width;
		int iRowEnd = iRowStart + _u32Width;

		std::vector<uint32_t> vRow;
		vRow.insert(vRow.begin(), _vBitmap.begin() + iRowStart, _vBitmap.begin() + iRowEnd);

		vRows.push_back(vRow);
	}

	std::reverse(vRows.begin(), vRows.end());

	_vBitmap.clear();

	for (auto& aRow : vRows) {
		_vBitmap.insert(_vBitmap.end(), aRow.begin(), aRow.end());
	}
}

PBITMAPINFO FontProcessor::CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp) {
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp);

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void FontProcessor::CreateBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC) {
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE* hp;                   // byte pointer  
	DWORD dwTmp;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS);

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL);

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL));


	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL);

	// Close the .BMP file.  
	CloseHandle(hf);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}

void FontProcessor::SaveToFile(std::vector<uint32_t>& _vBitmap, uint32_t _u32BitmapWidth, uint32_t _u32BitmapHeight, int _iGlyphNumber) {
	static const std::wstring path = L"./Assets/Fonts/TestOutput/";

	HBITMAP bitmap = CreateBitmap(_u32BitmapWidth, _u32BitmapHeight, 1, 32, _vBitmap.data());
	PBITMAPINFO info = CreateBitmapInfoStruct(NULL, bitmap);
	CreateBitmapFile(NULL, (path + std::to_wstring(_iGlyphNumber) + L".bmp").data(), info, bitmap, GetDC(NULL));
}

void FontProcessor::PlotPixel(std::vector<uint32_t>& _vBitmap, int _iX, int _iY, uint32_t _u32Color, uint32_t _u32RowLength) {
	int index = _iY * _u32RowLength + _iX;

	if (index > _vBitmap.size() - 1 || index < 0) return;

	_vBitmap[index] = _u32Color;
}

void FontProcessor::DrawPoint(std::vector<uint32_t>& _vBitmap, TTFPoint _pPosition, uint32_t _u32Width, uint32_t _u32Height, uint32_t _u32Color) {
	static const uint32_t u32Color = 0x00FF0000;
	
	PlotPixel(_vBitmap, _pPosition.x, _pPosition.y, u32Color, _u32Width);

	if (_pPosition.x > 0) {
		PlotPixel(_vBitmap, _pPosition.x - 1, _pPosition.y, u32Color, _u32Width);
		if (_pPosition.y > 0) {
			PlotPixel(_vBitmap, _pPosition.x - 1, _pPosition.y - 1, u32Color, _u32Width);
		}
		if (_pPosition.y < _u32Height - 1) {
			PlotPixel(_vBitmap, _pPosition.x - 1, _pPosition.y + 1, u32Color, _u32Width);
		}
	}
	if (_pPosition.x < _u32Width - 1) {
		PlotPixel(_vBitmap, _pPosition.x + 1, _pPosition.y, u32Color, _u32Width);
		if (_pPosition.y > 0) {
			PlotPixel(_vBitmap, _pPosition.x + 1, _pPosition.y - 1, u32Color, _u32Width);
		}
		if (_pPosition.y < _u32Height - 1) {
			PlotPixel(_vBitmap, _pPosition.x + 1, _pPosition.y + 1, u32Color, _u32Width);
		}
	}
	if (_pPosition.y > 0) {
		PlotPixel(_vBitmap, _pPosition.x, _pPosition.y - 1, u32Color, _u32Width);
	}
	if (_pPosition.y < _u32Height - 1) {
		PlotPixel(_vBitmap, _pPosition.x, _pPosition.y + 1, u32Color, _u32Width);
	}
}

/// <summary>
/// Thanks to Alois Zingl, Vienna, Austria at this link: http://members.chello.at/~easyfilter/bresenham.html
/// </summary>
void FontProcessor::DrawBresenhamLine(std::vector<uint32_t>& _vBitmap, TTFPoint _pStart, TTFPoint _pEnd, uint32_t _u32Color, uint32_t _u32RowLength) {
	int x0 =_pStart.x;
	int y0 =_pStart.y;
	int x1 =_pEnd.x;
	int y1 =_pEnd.y;

	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	for (;;) {  /* loop */
		PlotPixel(_vBitmap, x0, y0, _u32Color, _u32RowLength);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void FontProcessor::DrawBezierCurve(std::vector<uint32_t>& _vBitmap, TTFPoint _pStart, TTFPoint _pControl, TTFPoint _pEnd, uint32_t _u32Color, int _iResolution, uint32_t _u32RowLength) {
	TTFPoint prev = _pStart;

	for (int count = 0; count < _iResolution; ++count) {
		float t = (count + 1.0f) / _iResolution;
		TTFPoint next = BezierInterpolation(_pStart, _pControl, _pEnd, t);
		DrawBresenhamLine(_vBitmap, prev, next, _u32Color, _u32RowLength);
		prev = next;
	}
}

void FontProcessor::FillGlyph(std::vector<uint32_t>& _vBitmap, uint16_t _u16Width, uint16_t _u16Height, uint32_t _u32Color, std::vector<TTFContour>& _vAllContours) {
	for (const auto& aContour : _vAllContours) {
		RasterizeContour(_vBitmap, aContour, _u16Width, _u16Height, _u32Color);
	}
}

void FontProcessor::RasterizeContour(std::vector<uint32_t>& _vBitmap, const TTFContour& _tContour, uint16_t _u16Width, uint16_t _u16Height, uint32_t _u32Color) {
	struct {
		bool operator()(const TTFEdgeTableEntry& _tLeft, const TTFEdgeTableEntry& _tRight) { return _tLeft.m_vec2Min.y < _tRight.m_vec2Min.y; }
	} TTFSortOnY;

	struct {
		bool operator()(const TTFEdgeTableEntry& _tLeft, const TTFEdgeTableEntry& _tRight) { return _tLeft.m_fCurrentX < _tRight.m_fCurrentX; }
	} TTFSortOnX;

	std::vector<TTFEdgeTableEntry> vEdgeTable; //Polygon Edges
	std::vector<TTFEdgeTableEntry> vActiveEdges; //Active Edges

	//Move the integer contour into the floating point contour. This is to allow accuracy when not working with glyphs scaled to be 1:1
	for (const auto& aCurve : _tContour.m_vCurves) {
		if (aCurve.IsHorizontal()) {
			continue;
		}

		int iMinYIndex = aCurve.GetMinYIndex();
		int iMaxYIndex = iMinYIndex == 2 ? 0 : 2;

		TTFEdgeTableEntry eteEntry = {
			.m_vec2Min = Vec2F(aCurve.m_arrPoints[iMinYIndex].x, aCurve.m_arrPoints[iMinYIndex].y),
			.m_vec2ControlPoint = Vec2F(aCurve.m_p1.x, aCurve.m_p1.y),
			.m_vec2Max = Vec2F(aCurve.m_arrPoints[iMaxYIndex].x, aCurve.m_arrPoints[iMaxYIndex].y),
			.m_fCurrentX = static_cast<float>(aCurve.m_arrPoints[iMinYIndex].x),
			.m_bDownward = iMinYIndex == 2,
			.m_bHoleEdge = _tContour.m_bIsHole
		};

		vEdgeTable.push_back(eteEntry);
	}

	//Start by sorting the edges on their minimum Y
	std::sort(vEdgeTable.begin(), vEdgeTable.end(), TTFSortOnY);

	int16_t y = 0;
	//Go until the y coordinate is the height of the bitmap or the edge counts are empty
	while (y < _u16Height && !(vEdgeTable.empty() && vActiveEdges.empty())) {
		//Move edges from ET to AET when the minimum Y is equal to the y coordinate.
		for (int ndx = 0; ndx < vEdgeTable.size(); ++ndx) {
			if (static_cast<int16_t>(vEdgeTable[ndx].m_vec2Min.y) == y) {
				vActiveEdges.push_back(vEdgeTable[ndx]);
				vEdgeTable.erase(vEdgeTable.begin() + ndx--);
			}
		}

		//If there are no active edges, continue to the next scanline
		if (vActiveEdges.size() == 0) {
			y++;
			continue;
		}

		//Sort AET on X
		std::sort(vActiveEdges.begin(), vActiveEdges.end(), TTFSortOnX);

		//Draw lines between each point
		int iCurrNdx = 0;
		while (iCurrNdx < vActiveEdges.size() - 1) {
			auto& aEntry1 = vActiveEdges[iCurrNdx];
			auto& aEntry2 = vActiveEdges[iCurrNdx + 1];

			DrawBresenhamLine(_vBitmap,
				{ static_cast<int16_t>(std::roundf(aEntry1.m_fCurrentX)), y },
				{ static_cast<int16_t>(std::roundf(aEntry2.m_fCurrentX)), y },
				_tContour.m_bIsHole ? 0x0 : _u32Color,
				_u16Width);

			iCurrNdx += 2;
		}

		//Increment y by 1
		y++;

		//Remove edges from AET when Y = Ymax
		for (int ndx = 0; ndx < vActiveEdges.size(); ++ndx) {
			if (static_cast<int16_t>(vActiveEdges[ndx].m_vec2Max.y) == y) {
				vActiveEdges.erase(vActiveEdges.begin() + ndx--);
			}
		}

		//Update all the x values for the next scanline
		for (auto& aTableEntry : vActiveEdges) {
			//Get distance along line between max and min
			float fProportion = (static_cast<float>(y) - aTableEntry.m_vec2Min.y) / (aTableEntry.m_vec2Max.y - aTableEntry.m_vec2Min.y);

			//Interpolate the curve
			Vec2F vec2InterpolatedPoint = BezierInterpolation(aTableEntry.m_vec2Min, aTableEntry.m_vec2ControlPoint, aTableEntry.m_vec2Max, fProportion);

			//Save the X
			aTableEntry.m_fCurrentX = vec2InterpolatedPoint.x;
		}
	}
}

FontProcessor::TTFPoint FontProcessor::BezierInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT) {
	return { (int16_t)QuadraticInterpolation(_p0.x, _p1.x, _p2.x, _fT), (int16_t)QuadraticInterpolation(_p0.y, _p1.y, _p2.y, _fT) };
}

Vec2F FontProcessor::BezierInterpolation(Vec2F _v0, Vec2F _v1, Vec2F _v2, float _fT) {
	return Vec2F(QuadraticInterpolation(_v0.x, _v1.x, _v2.x, _fT), QuadraticInterpolation(_v0.y, _v1.y, _v2.y, _fT));
}

float FontProcessor::QuadraticInterpolation(float _f0, float _f1, float _f2, float _fT) {
	float fA = (_f0 - (2.0f * _f1) + _f2);
	float fB = 2.0f * (_f1 - _f0);

	return (fA * (_fT * _fT)) + (fB * _fT) + _f0;
}