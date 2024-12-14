
#include <Torchlight/Util/FontUtil.hpp>

namespace FontUtil {
	TTFPoint QuadraticInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT) {
		return { QuadraticInterpolation(_p0.x, _p1.x, _p2.x, _fT), QuadraticInterpolation(_p0.y, _p1.y, _p2.y, _fT) };
	}

	Vec2F QuadraticInterpolation(Vec2F _v0, Vec2F _v1, Vec2F _v2, float _fT) {
		return Vec2F(QuadraticInterpolation(_v0.x, _v1.x, _v2.x, _fT), QuadraticInterpolation(_v0.y, _v1.y, _v2.y, _fT));
	}

	float QuadraticInterpolation(float _f0, float _f1, float _f2, float _fT) {
		float fA = (_f0 - (2.0f * _f1) + _f2);
		float fB = 2.0f * (_f1 - _f0);

		return (fA * (_fT * _fT)) + (fB * _fT) + _f0;
	}

	float GetQuadraticX(float _f0, float _f1, float _f2, float _fY) {
		float a = _f0 - 2 * _f1 + _f2;
		float b = 2 * (_f1 - _f0);
		float c = _f0;

		Vec2F v2Roots(NAN, NAN);

		QuadraticFormula(a, b, c - _fY, v2Roots);

		return v2Roots[0] > 0.0f ? v2Roots[0] : v2Roots[1];
	}

	void QuadraticFormula(float _fA, float _fB, float _fC, Vec2F& _v2Roots) {
		if (fabsf(_fA) < HC_EPSILON) {
			if (_fB != 0.0f) {
				_v2Roots[0] = -_fC / _fB;
			}
		}
		else {
			float fDisc = _fB * _fB - 4.0f * _fA * _fC;

			if (fDisc > -HC_EPSILON) {
				float fSqrt = sqrtf(std::max(0.0f, fDisc));
				_v2Roots[0] = (-_fB + fSqrt) / (2.0f * _fA);
				_v2Roots[1] = (-_fB - fSqrt) / (2.0f * _fA);
			}
		}
	}

	std::map<UTF8PaddedChar, int> ReadTTFFormat4(File& _fFontFile) {
		std::map<UTF8PaddedChar, int> mCharMap;

		_fFontFile.AdvanceBytes(4); //Skip over length and language

		uint16_t u16SegmentCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile) / 2;

		_fFontFile.AdvanceBytes(6); //Skip over Binary Search assistors

		std::vector<uint16_t> vEndCodes(u16SegmentCount);
		std::vector<uint16_t> vStartCodes(u16SegmentCount);
		std::vector<uint16_t> vIDDeltas(u16SegmentCount);
		std::vector<uint16_t> vIDRangeOffsets(u16SegmentCount);
		std::vector<uint16_t> vIDRangeOffsetPosition(u16SegmentCount);

		for (auto& aVal : vEndCodes) {
			aVal = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		_fFontFile.AdvanceBytes(2); //Pass padding

		for (auto& aVal : vEndCodes) {
			aVal = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		for (auto& aVal : vIDDeltas) {
			aVal = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		for (int ndx = 0; ndx < u16SegmentCount; ++ndx) {
			vIDRangeOffsetPosition[ndx] = static_cast<uint16_t>(_fFontFile.ReaderLocation());
			vIDRangeOffsets[ndx] = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		bool bAddedMissingChar = false;
		for (int ndx = 0; ndx < u16SegmentCount; ++ndx) {
			UTF8PaddedChar uCurrCode = vStartCodes[ndx];

			while (uCurrCode <= vEndCodes[ndx] && uCurrCode < 0xFFFF) {
				int iGlyphNdx;

				if (vIDRangeOffsets[ndx] == 0) {
					iGlyphNdx = (uCurrCode + vIDDeltas[ndx]) % 65536;
				}
				else {
					size_t sBookmarkedLocation = _fFontFile.ReaderLocation();

					uint16_t u16RangeLocation = vIDRangeOffsetPosition[ndx] + vIDRangeOffsets[ndx];
					uint32_t u32GlyphNdxArrayLocation = 2 * (uCurrCode - vStartCodes[ndx]) + u16RangeLocation;

					_fFontFile.GoToByte(u32GlyphNdxArrayLocation);

					iGlyphNdx = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

					if (iGlyphNdx != 0) {
						iGlyphNdx = (iGlyphNdx + vIDDeltas[ndx]) % 65536;
					}

					_fFontFile.GoToByte(sBookmarkedLocation);
				}

				mCharMap[uCurrCode++] = iGlyphNdx;
				bAddedMissingChar |= iGlyphNdx == 0;
			}
		}

		if (!bAddedMissingChar) {
			mCharMap[65535] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
		}

		return mCharMap;
	}

	std::map<UTF8PaddedChar, int> ReadTTFFormat12(File& _fFontFile) {
		std::map<UTF8PaddedChar, int> mCharMap;

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
			mCharMap[65535] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
		}

		return mCharMap;
	}

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp) {
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

	void CreateBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC) {
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

	void SaveToFile(const TTFBitmap& _tBitmap, int _iGlyphNumber) {
		static const std::wstring path = L"./Assets/Fonts/TestOutput/";

		HBITMAP bitmap = CreateBitmap(_tBitmap.m_u32Width, _tBitmap.m_u32Height, 1, 32, _tBitmap.m_pPixels);
		PBITMAPINFO info = CreateBitmapInfoStruct(NULL, bitmap);
		CreateBitmapFile(NULL, (path + std::to_wstring(_iGlyphNumber) + L".bmp").data(), info, bitmap, GetDC(NULL));
	}
#endif
}