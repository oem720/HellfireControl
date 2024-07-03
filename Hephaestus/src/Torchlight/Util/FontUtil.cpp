
#include <Torchlight/Util/FontUtil.hpp>

namespace FontUtil {
	int GetPointOffset(const std::vector<TTFPoint>& _vPoints) {
		int iPointOffset;
		for (iPointOffset = 0; iPointOffset < _vPoints.size(); ++iPointOffset) {
			if (_vPoints[iPointOffset].onCurve) break;
		}

		return iPointOffset;
	}

	/// <summary>
	/// Credit to Sebastian Lague: https://github.com/SebLague/Text-Rendering/tree/main
	/// </summary>
	void RecreateImpliedPoints(std::vector<TTFPoint>& _vPoints, int _iPointOffset) {

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
	void MakeContourCurvesMonotonic(TTFContour& _tContour) {
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
	std::vector<TTFPoint> SplitCurveAtTurningPoint(const TTFCurve& _tCurve) {
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

	TTFPoint QuadraticInterpolation(TTFPoint _p0, TTFPoint _p1, TTFPoint _p2, float _fT) {
		return { (int16_t)QuadraticInterpolation(_p0.x, _p1.x, _p2.x, _fT), (int16_t)QuadraticInterpolation(_p0.y, _p1.y, _p2.y, _fT) };
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

	void DrawPoint(TTFBitmap& _bBitmap, int _iX, int _iY, uint32_t _u32Color) {
		_bBitmap.PlotPixel(_iX, _iY, _u32Color);

		if (_iX > 0) {
			_bBitmap.PlotPixel(_iX - 1, _iY, _u32Color);
			if (_iY > 0) {
				_bBitmap.PlotPixel(_iX - 1, _iY - 1, _u32Color);
			}
			if (_iY < _bBitmap.m_u32Height - 1) {
				_bBitmap.PlotPixel(_iX - 1, _iY + 1, _u32Color);
			}
		}
		if (_iX < _bBitmap.m_u32Width - 1) {
			_bBitmap.PlotPixel(_iX + 1, _iY, _u32Color);
			if (_iY > 0) {
				_bBitmap.PlotPixel(_iX + 1, _iY - 1, _u32Color);
			}
			if (_iY < _bBitmap.m_u32Height - 1) {
				_bBitmap.PlotPixel(_iX + 1, _iY + 1, _u32Color);
			}
		}
		if (_iY > 0) {
			_bBitmap.PlotPixel(_iX, _iY - 1, _u32Color);
		}
		if (_iY < _bBitmap.m_u32Height - 1) {
			_bBitmap.PlotPixel(_iX, _iY + 1, _u32Color);
		}
	}

	/// <summary>
	/// Thanks to Alois Zingl, Vienna, Austria at this link: http://members.chello.at/~easyfilter/bresenham.html
	/// </summary>
	void DrawLine(TTFBitmap& _bBitmap, int _iX0, int _iY0, int _iX1, int _iY1, uint32_t _u32Color) {
		int dx = abs(_iX1 - _iX0), sx = _iX0 < _iX1 ? 1 : -1;
		int dy = -abs(_iY1 - _iY0), sy = _iY0 < _iY1 ? 1 : -1;
		int err = dx + dy, e2; /* error value e_xy */

		for (;;) {  /* loop */
			_bBitmap.PlotPixel(_iX0, _iY0, _u32Color);
			if (_iX0 == _iX1 && _iY0 == _iY1) break;
			e2 = 2 * err;
			if (e2 >= dy) { err += dy; _iX0 += sx; } /* e_xy+e_x > 0 */
			if (e2 <= dx) { err += dx; _iY0 += sy; } /* e_xy+e_y < 0 */
		}
	}

	void DrawBezier(TTFBitmap& _bBitmap, const TTFPoint& _p0, const TTFPoint& _p1, const TTFPoint& _p2, int _iResolution, uint32_t _u32Color) {
		TTFPoint prev = _p0;

		for (int count = 0; count < _iResolution; ++count) {
			float t = (count + 1.0f) / _iResolution;
			TTFPoint next = QuadraticInterpolation(_p0, _p1, _p2, t);
			DrawLine(_bBitmap, prev.x, prev.y, next.x, next.y, _u32Color);
			prev = next;
		}
	}

	void DrawGlyph(TTFBitmap& _bBitmap, std::vector<TTFContour>& _vAllContours, uint32_t _u32Color) {
		struct {
			bool operator()(const TTFEdgeTableEntry& _tLeft, const TTFEdgeTableEntry& _tRight) { return _tLeft.m_vec2Min.y < _tRight.m_vec2Min.y; }
		} TTFSortOnY;

		struct {
			bool operator()(const TTFEdgeTableEntry& _tLeft, const TTFEdgeTableEntry& _tRight) { return _tLeft.m_fCurrentX < _tRight.m_fCurrentX; }
		} TTFSortOnX;

		std::vector<TTFEdgeTableEntry> vEdgeTable; //Polygon Edges
		std::vector<TTFEdgeTableEntry> vActiveEdges; //Active Edges

		//Move the integer contour into the floating point contour. This is to allow accuracy when not working with glyphs scaled to be 1:1
		for (const auto& aContour : _vAllContours) {
			for (const auto& aCurve : aContour.m_vCurves) {
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
					.m_bDownward = iMinYIndex == 2
				};

				vEdgeTable.push_back(eteEntry);
			}
		}

		//Start by sorting the edges on their minimum Y
		std::sort(vEdgeTable.begin(), vEdgeTable.end(), TTFSortOnY);

		int32_t iScanline = 0;
		//Go until the y coordinate is the height of the bitmap or the edge counts are empty
		while (iScanline < _bBitmap.m_u32Height && !(vEdgeTable.empty() && vActiveEdges.empty())) {
			//Move edges from ET to AET when the minimum Y is equal to the y coordinate.
			for (int ndx = 0; ndx < vEdgeTable.size(); ++ndx) {
				if (static_cast<int32_t>(vEdgeTable[ndx].m_vec2Min.y) <= iScanline) {
					vActiveEdges.push_back(vEdgeTable[ndx]);
					vEdgeTable.erase(vEdgeTable.begin() + ndx--);
				}
			}

			//If there are no active edges, continue to the next scanline
			if (vActiveEdges.size() == 0) {
				iScanline++;
				continue;
			}

			//Sort AET on X
			std::sort(vActiveEdges.begin(), vActiveEdges.end(), TTFSortOnX);

			//Sample every point along the scanline and check the raycast count
			for (int iX = 0; iX < _bBitmap.m_u32Width; ++iX) {
				int iIntersectionCount = 0;

				for (const auto& aEdge : vActiveEdges) {
					//If the intersection is less than the current x, we can ignore it as it is to the left
					if (iX > static_cast<int>(aEdge.m_fCurrentX)) { continue; }

					//If the edge is downward with respect to the line (should be monotonic, so this is easy), then
					//subtract 1 from the intersection count. Otherwise, add 1.
					int iSign = aEdge.m_bDownward ? -1 : 1;

					iIntersectionCount += iSign;
				}

				//If the final intersection count is non-zero, plot it
				if (iIntersectionCount != 0) {
					_bBitmap.PlotPixel(iX, iScanline, _u32Color);
				}
			}

			//Increment y by 1
			iScanline++;

			//Remove edges from AET when Y = Ymax
			for (int ndx = 0; ndx < vActiveEdges.size(); ++ndx) {
				if (static_cast<int32_t>(vActiveEdges[ndx].m_vec2Max.y) == iScanline) {
					vActiveEdges.erase(vActiveEdges.begin() + ndx--);
				}
			}

			//Update all the x values for the next scanline
			for (auto& aTableEntry : vActiveEdges) {
				//Determine the T that generated the current Y (scanline)
				float fT = GetQuadraticX(aTableEntry.m_vec2Min.y, aTableEntry.m_vec2ControlPoint.y, aTableEntry.m_vec2Max.y, static_cast<float>(iScanline));

				//Interpolate curve and save current X
				aTableEntry.m_fCurrentX = QuadraticInterpolation(aTableEntry.m_vec2Min.x, aTableEntry.m_vec2ControlPoint.x, aTableEntry.m_vec2Max.x, fT);
			}
		}
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