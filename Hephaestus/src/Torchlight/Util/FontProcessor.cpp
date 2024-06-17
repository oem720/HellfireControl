
#include <Torchlight/Util/FontProcessor.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Math/Math.hpp>

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

	CreateTemporaryBitmaps(vGlyphData, u16Resolution);
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

	if (_i16ContourCount == 0) {
		return aSimpleGlyph; //No data to read...
	}

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

	std::vector<int16_t> vCoordBufferX(iNumPoints);
	std::vector<int16_t> vCoordBufferY(iNumPoints);

	ParseCoordinates(_fFontFile, aSimpleGlyph->m_vFlags, true, vCoordBufferX);
	ParseCoordinates(_fFontFile, aSimpleGlyph->m_vFlags, false, vCoordBufferY);

	for (int ndx = 0; ndx < iNumPoints; ++ndx) {
		aSimpleGlyph->m_vCoords.push_back({ vCoordBufferX[ndx], vCoordBufferY[ndx] });
	}

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

void FontProcessor::CreateTemporaryBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, uint16_t _u16PixelsPerEm) {
	int glyphCount = 0;
	for (const auto& glyph : _vGlyphs) {
		if (glyphCount == 10) break; //SCRAM BUTTON FOR FILE CREATION.

		uint32_t bitmapWidth = (glyph.first.m_fXMax - glyph.first.m_fXMin);
		uint32_t bitmapHeight = (glyph.first.m_fYMax - glyph.first.m_fYMin);

		size_t bufferSize = (((bitmapWidth * 32 + 15) >> 4) << 1) * bitmapHeight;

		std::vector<uint32_t> colors(bufferSize, 0);

		if (glyph.first.m_i16ContourCount > 0) {
			int contourStartIndex = 0;
		
			TTFSimpleGlyph* glyphData = (TTFSimpleGlyph*)glyph.second.get();
		
			for (int endIndex : glyphData->m_vContourEndPts) {
				int contourPointsCount = endIndex - contourStartIndex + 1;
				std::vector<TTFPoint> points(contourPointsCount);
		
				std::copy(glyphData->m_vCoords.begin() + contourStartIndex, glyphData->m_vCoords.begin() + endIndex, points.begin());
				
				for (int ndx = 0; ndx < points.size(); ++ndx) {
					DrawBresenhamLine(colors, points[ndx], points[(ndx + 1) % points.size()], bitmapWidth);
				}
		
				contourStartIndex = endIndex + 1;
			}			
		}

		std::wstring path = L"./Assets/Fonts/TestOutput/";

		HBITMAP bitmap = CreateBitmap(bitmapWidth, bitmapHeight, 1, 32, colors.data());
		PBITMAPINFO info = CreateBitmapInfoStruct(NULL, bitmap);
		CreateBitmapFile(NULL, (path + std::to_wstring(glyphCount) + L".bmp").data(), info, bitmap, GetDC(NULL));

		glyphCount++;
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

void FontProcessor::DrawBresenhamLine(std::vector<uint32_t>& _vBitmap, TTFPoint _pStart, TTFPoint _pEnd, uint32_t _u32RowLength) {
	int dx = abs(_pEnd.x - _pStart.x), sx = _pStart.x < _pEnd.x ? 1 : -1;
	int dy = -abs(_pEnd.y - _pStart.y), sy = _pStart.y < _pEnd.y ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	for (;;) {  /* loop */
		_vBitmap[_pStart.y * _u32RowLength + _pStart.x] = 0xFFFFFFFF;
		if (_pStart.x == _pEnd.x && _pStart.y == _pEnd.y) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; _pStart.x += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; _pStart.y += sy; } /* e_xy+e_y < 0 */
	}
}
