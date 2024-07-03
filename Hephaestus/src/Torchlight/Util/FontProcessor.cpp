
#include <Torchlight/Util/FontProcessor.hpp>

#include <HellfireControl/Asset/Font.hpp>

using namespace FontUtil;

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
	uint16_t u16DirectorySize = FontUtil::ReadTTFValue<uint16_t>(_fFontFile); //Create our list for directory entries
	_fFontFile.AdvanceBytes(6); //Skip over the next 3 16 bit values

	for (int count = 0; count < u16DirectorySize; ++count) {
		union {
			uint32_t u32Tag;
			char arrTag[5] = { '\0', '\0', '\0', '\0', '\0' };
		} tag;

		_fFontFile >> tag.u32Tag;
		_fFontFile.AdvanceBytes(4);

		_mOutDataBlockLocations[tag.arrTag] = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);
		_fFontFile.AdvanceBytes(4);
	}
}

void FontProcessor::GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphOffsets, uint16_t& _u16OutPixelsPerEm) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["head"]);

	_fFontFile.AdvanceBytes(18);

	_u16OutPixelsPerEm = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(30);

	bool bIsTwoByte = !FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["loca"]);
	_vOutGlyphOffsets.resize(u16GlyphCount);

	for (size_t ndx = 0; ndx < u16GlyphCount; ++ndx) {
		_vOutGlyphOffsets[ndx] = (bIsTwoByte ? (FontUtil::ReadTTFValue<uint16_t>(_fFontFile) * 2u) : FontUtil::ReadTTFValue<uint32_t>(_fFontFile));
	}
}

void FontProcessor::ParseGlyph(File& _fFontFile, TTFGlyphData& _gdOutGlyphData) {
	_gdOutGlyphData.first = {
		.m_i16ContourCount = FontUtil::ReadTTFValue<int16_t>(_fFontFile),
		.m_fXMin = FontUtil::ReadTTFValue<FWord>(_fFontFile),
		.m_fYMin = FontUtil::ReadTTFValue<FWord>(_fFontFile),
		.m_fXMax = FontUtil::ReadTTFValue<FWord>(_fFontFile),
		.m_fYMax = FontUtil::ReadTTFValue<FWord>(_fFontFile)
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

std::unique_ptr<TTFSimpleGlyph> FontProcessor::ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, uint32_t _u32MinX, uint32_t _u32MinY) {
	auto aSimpleGlyph = std::make_unique<TTFSimpleGlyph>();

	if (_i16ContourCount == 0) {
		return aSimpleGlyph; //No data to read...
	}

	std::vector<uint16_t> vContourEndPts(_i16ContourCount);

	for (int ndx = 0; ndx < _i16ContourCount; ++ndx) {
		vContourEndPts[ndx] = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
	}

	_fFontFile.AdvanceBytes(FontUtil::ReadTTFValue<int16_t>(_fFontFile));

	//Get the largest contour end point index and add 1 (1 based count). This will equal the count of points
	int iNumPoints = 1 + (*std::max_element(vContourEndPts.begin(), vContourEndPts.end()));

	std::vector<uint8_t> vFlags(iNumPoints);
	std::vector<TTFPoint> vPoints(iNumPoints);

	for (int ndx = 0; ndx < iNumPoints; ++ndx) {
		uint8_t u8Flag = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

		vFlags[ndx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

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

	return std::move(aSimpleGlyph);
}

std::unique_ptr<TTFCompoundGlyph> FontProcessor::ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount) {
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
			int iOffset = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);
			iCoordValue += Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit) ? iOffset : -iOffset;
		}
		else if (!Util::IsBitSet(u8Flag, iOffsetSignOrSkipBit)) {
			iCoordValue += FontUtil::ReadTTFValue<int16_t>(_fFontFile);
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

void FontProcessor::CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, uint16_t _u16PixelsPerEm) {
#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	int glyphCount = 0;		
#endif

	for (const auto& glyph : _vGlyphs) {
		uint32_t bitmapWidth = (glyph.first.m_fXMax - glyph.first.m_fXMin) + 1;
		uint32_t bitmapHeight = (glyph.first.m_fYMax - glyph.first.m_fYMin);

		TTFBitmap bBitmap(bitmapWidth, bitmapHeight);

		if (glyph.first.m_i16ContourCount > 0) {
			TTFSimpleGlyph* glyphData = (TTFSimpleGlyph*)glyph.second.get();

			FontUtil::DrawGlyph(bBitmap, glyphData->m_vContours, 0xFFFFFFFF);

			for (int ndx = 0; ndx < glyphData->m_vContours.size(); ++ndx) {
				for (TTFCurve& curve : glyphData->m_vContours[ndx].m_vCurves) {
					FontUtil::DrawBezier(bBitmap, curve.m_p0, curve.m_p1, curve.m_p2, 28, 0xFFFFFFFF);
				}
			}
		}
		else {
			continue; //Skip Compound Glyphs, as they require a different rasterization setup.
		}

		bBitmap.FlipImageVertically();

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
		FontUtil::SaveToFile(bBitmap, glyphCount++);

		if (glyphCount > 10) {
			break;
		}
#endif
	}
}