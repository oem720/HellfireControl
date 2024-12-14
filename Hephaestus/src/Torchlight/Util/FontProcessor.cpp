
#include <Torchlight/Util/FontProcessor.hpp>

using namespace FontUtil;

#define HC_FONT_DPI 72
#define HC_FONT_SCREEN_RESOLUTION 96
#define HC_FONT_BASE_COLOR 0xFFFFFFFF

Font FontProcessor::ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY); //Open file in binary

	std::map<std::string, uint32_t> mDataBlockLocations;

	GetDataBlockOffsets(fFontFile, mDataBlockLocations);

	std::vector<uint32_t> vGlyphOffsets;
	uint16_t u16PixelsPerEm = 0;
	uint16_t u16MaxRecursionDepth = 0;

	GetGlyphOffsets(fFontFile, mDataBlockLocations, vGlyphOffsets, u16PixelsPerEm, u16MaxRecursionDepth);

	float fScale = static_cast<float>(_u16FontSize * HC_FONT_SCREEN_RESOLUTION) / static_cast<float>(HC_FONT_DPI * u16PixelsPerEm);

	std::vector<TTFGlyphData> vGlyphData(vGlyphOffsets.size()); //Size of the list is the size of the number of locations

	uint32_t u32GlyphTableStart = mDataBlockLocations["glyf"];

	for (int ndx = 0; ndx < vGlyphData.size(); ++ndx) {
		fFontFile.GoToByte(u32GlyphTableStart + vGlyphOffsets[ndx]);

		ParseGlyph(fFontFile, u16MaxRecursionDepth, fScale, vGlyphData[ndx]); //Parse the glyph individually
	}
		
	std::map<UTF8PaddedChar, int> mCharacterMap; //The integer corresponds to the index of the glyph as stored in the list of glyph data.

	ParseCharacterMap(fFontFile, mDataBlockLocations["cmap"], mCharacterMap);

	std::vector<TTFBitmap> vBitmaps;

	bool bIsSDF = _ftType > 0;

	CreateGlyphBitmaps(vGlyphData, bIsSDF, vBitmaps);

	if (bIsSDF) {
		ConvertGlyphsToSDF(vBitmaps, _ftType == FONT_MULTI_CHANNEL_SDF);
	}

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	for (int ndx = 0; ndx < vBitmaps.size(); ++ndx) {
		FontUtil::SaveToFile(vBitmaps[ndx], ndx);
	}
#endif

	TTFBitmap bCollatedTexture = CollateGlyphs(vBitmaps);

	return PackIntoFontAsset(bCollatedTexture, mCharacterMap, vGlyphData);
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

void FontProcessor::GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphOffsets, uint16_t& _u16OutPixelsPerEm, uint16_t& _u16OutMaxComponentDepth) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(24); //Skip over much of the table

	_u16OutMaxComponentDepth = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

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

void FontProcessor::ParseGlyph(File& _fFontFile, uint16_t _u16MaxDepth, float _fScalingFactor, TTFGlyphData& _gdOutGlyphData) {
	_gdOutGlyphData.first = {
		.m_i16ContourCount = FontUtil::ReadTTFValue<int16_t>(_fFontFile),
		.m_fXMin = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fYMin = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fXMax = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fYMax = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile))
	};

	if (_gdOutGlyphData.first.m_i16ContourCount >= 0) {
		_gdOutGlyphData.second = ParseSimpleGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount, _fScalingFactor, _gdOutGlyphData.first.m_fXMin, _gdOutGlyphData.first.m_fYMin);
	}
	else {
		_gdOutGlyphData.second = ParseCompoundGlyph(_fFontFile, _u16MaxDepth);
	}

	_gdOutGlyphData.first.m_fXMin *= _fScalingFactor;
	_gdOutGlyphData.first.m_fXMax *= _fScalingFactor;
	_gdOutGlyphData.first.m_fYMin *= _fScalingFactor;
	_gdOutGlyphData.first.m_fYMax *= _fScalingFactor;
}

void FontProcessor::ParseCharacterMap(File& _fFontFile, uint32_t _u32CMAPPosition, std::map<UTF8PaddedChar,int>& _mOutCharacterMap) {
	_fFontFile.GoToByte(_u32CMAPPosition);

	_fFontFile.AdvanceBytes(2); //Skip over the version

	uint16_t u16SubtableCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	int16_t i16UnicodeVersion = -1;
	uint32_t u32TableOffset = 0;

	for (int iCount = 0; iCount < u16SubtableCount; ++iCount) {
		uint16_t u16PlatformID = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		uint16_t u16PlatformSpecificID = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		uint32_t u32Offset = FontUtil::ReadTTFValue<uint32_t>(_fFontFile);

		if (u16PlatformID == 0) { //Base Unicode
			if (u16PlatformSpecificID > i16UnicodeVersion) {
				i16UnicodeVersion = u16PlatformSpecificID;
				u32TableOffset = u32Offset;
			}
		}
		else if (u16PlatformID == 3 && i16UnicodeVersion < 0) { //Windows (only use if no unicode found)
			u32TableOffset = u32Offset;
		}
	}

	if (u32TableOffset == 0) {
		throw std::runtime_error("ERROR: Font unsupported! Font must support Unicode or Windows encoding!");
	}

	_fFontFile.GoToByte(_u32CMAPPosition + u32TableOffset); //Skip to the correct table

	uint16_t u16Format = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	switch (u16Format) {
	case 4:
		_mOutCharacterMap = FontUtil::ReadTTFFormat4(_fFontFile);
		break;
	case 12:
		_mOutCharacterMap = FontUtil::ReadTTFFormat12(_fFontFile);
		break;
	default:
		throw std::runtime_error("ERROR: Not Implemented. Format: " + std::to_string(u16Format));
		break;
	}
}

void FontProcessor::CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, bool _bIsSDF, std::vector<TTFBitmap>& _vOutBitmaps) {
	for (const auto& glyph : _vGlyphs) {
		if (glyph.first.m_i16ContourCount <= 0) {
			continue; //Skip Compound Glyphs, as they are dynamically assembled when drawing text
		}

		TTFBitmap bBitmap(
			static_cast<uint32_t>(std::roundf(glyph.first.m_fXMax - glyph.first.m_fXMin)),
			static_cast<uint32_t>(std::roundf(glyph.first.m_fYMax - glyph.first.m_fYMin))
		);

		//This grossness comes straight from my desire to "simplify" certain data types. The glyph data block that follows the descriptor
		//must be downcasted into a SimpleGlyph. It is impossible to actually get a compound glyph in this segment of code, but because of
		//setup, this downcast is required anyway. TODO: simplify the simplification.
		TTFSimpleGlyph* glyphData = (TTFSimpleGlyph*)glyph.second.get();
		RasterizeGlyph(bBitmap, glyphData->m_vContours);

		bBitmap.FlipImageVertically();

		_vOutBitmaps.push_back(std::move(bBitmap));
	}
}

void FontProcessor::AntiAliasGlyphs(std::vector<TTFBitmap>& _vBitmaps) {
	
}

void FontProcessor::ConvertGlyphsToSDF(std::vector<TTFBitmap>& _vBitmaps, bool _bIsMultiChannel) {
}

TTFBitmap FontProcessor::CollateGlyphs(std::vector<TTFBitmap>& _vBitmaps) {
	return TTFBitmap(1, 1);
}

Font FontProcessor::PackIntoFontAsset(TTFBitmap& _bFontAtlas, std::map<UTF8PaddedChar,int> _mCharacterMap, std::vector<TTFGlyphData>& _vGlyphData) {
	return Font();
}

std::unique_ptr<TTFSimpleGlyph> FontProcessor::ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, float _fScalingFactor, uint32_t _u32MinX, uint32_t _u32MinY) {
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
	ParseCoordinateFlags(_fFontFile, vFlags);

	std::vector<TTFPoint> vPoints(iNumPoints);
	ParseCoordinates(_fFontFile, vFlags, _fScalingFactor, _u32MinX, _u32MinY, vPoints);

	aSimpleGlyph->m_vContours = PackContours(vPoints, vContourEndPts);

	return std::move(aSimpleGlyph);
}

std::unique_ptr<TTFCompoundGlyph> FontProcessor::ParseCompoundGlyph(File& _fFontFile, uint16_t _u16MaxDepth) {
	auto aCompoundGlyph = std::make_unique<TTFCompoundGlyph>();

	uint16_t u16Flags = 0;
	do { //Keep looping until the flag that there are no more is found.
		u16Flags = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

		TTFCompoundGlyph::TTFCompoundGlyphComponent cgcComponent = {};

		cgcComponent.m_u16GlyphIndex = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

		bool bSigned = u16Flags & ARGS_ARE_XY_VALUES;

		if (u16Flags & ARGS_1_AND_2_ARE_WORDS) {
			bSigned ? cgcComponent.m_cgaArgument1.i16 = FontUtil::ReadTTFValue<int16_t>(_fFontFile) : cgcComponent.m_cgaArgument1.u16 = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
			bSigned ? cgcComponent.m_cgaArgument2.i16 = FontUtil::ReadTTFValue<int16_t>(_fFontFile) : cgcComponent.m_cgaArgument2.u16 = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}
		else {
			bSigned ? cgcComponent.m_cgaArgument1.i8 = FontUtil::ReadTTFValue<int16_t>(_fFontFile) : cgcComponent.m_cgaArgument1.u8 = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
			bSigned ? cgcComponent.m_cgaArgument2.i8 = FontUtil::ReadTTFValue<int16_t>(_fFontFile) : cgcComponent.m_cgaArgument2.u8 = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);
		}

		if (u16Flags & WE_HAVE_A_SCALE) {
			cgcComponent.m_arrTransformData[0] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
			cgcComponent.m_arrTransformData[3] = cgcComponent.m_arrTransformData[0];
		}
		else if (u16Flags & WE_HAVE_AN_X_AND_Y_SCALE) {
			cgcComponent.m_arrTransformData[0] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
			cgcComponent.m_arrTransformData[3] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
		}
		else if (u16Flags & WE_HAVE_A_TWO_BY_TWO) {
			cgcComponent.m_arrTransformData[0] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
			cgcComponent.m_arrTransformData[1] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
			cgcComponent.m_arrTransformData[2] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
			cgcComponent.m_arrTransformData[3] = FontUtil::ConvertToFloatingPoint<float>(FontUtil::ReadTTFValue<F2Dot14>(_fFontFile));
		}

		cgcComponent.m_u8Flags |= u16Flags & USE_MY_METRICS ? 0x1 : 0;
		cgcComponent.m_u8Flags |= u16Flags & SCALED_COMPONENT_OFFSET ? 0x2 : 0;
		cgcComponent.m_u8Flags |= u16Flags & UNSCALED_COMPONENT_OFFSET ? 0x4 : 0;
		cgcComponent.m_u8Flags |= u16Flags & ARGS_ARE_XY_VALUES ? 0x8 : 0;

		aCompoundGlyph->m_vComponents.push_back(cgcComponent);
	} while (u16Flags & MORE_COMPONENTS);

	return std::move(aCompoundGlyph);
}

void FontProcessor::ParseCoordinateFlags(File& _fFontFile, std::vector<uint8_t>& _vFlags) {
	for (int ndx = 0; ndx < _vFlags.size(); ++ndx) {
		uint8_t u8Flag = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

		_vFlags[ndx] = u8Flag;

		if (Util::IsBitSet(u8Flag, REPEAT)) {
			uint8_t u8RepeatCount = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);

			for (int iFlagCount = 0; iFlagCount < u8RepeatCount; ++iFlagCount) {
				_vFlags[++ndx] = u8Flag;
			}
		}
	}
}

void FontProcessor::ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, float _fScalingFactor, uint32_t _u32MinX, uint32_t _u32MinY, std::vector<TTFPoint>& _vOutCoordinates) {
	int iCoordValue = 0;
	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		ParseCoordinateValue(_fFontFile, _vFlags[ndx], IS_SINGLE_BYTE_X, INSTRUCTION_X, _u32MinX, iCoordValue, _vOutCoordinates[ndx].x);

		_vOutCoordinates[ndx].m_bOnCurve = Util::IsBitSet(_vFlags[ndx], ON_CURVE);
	}

	iCoordValue = 0;
	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		ParseCoordinateValue(_fFontFile, _vFlags[ndx], IS_SINGLE_BYTE_Y, INSTRUCTION_Y, _u32MinY, iCoordValue, _vOutCoordinates[ndx].y);
	}

	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		_vOutCoordinates[ndx].x *= _fScalingFactor;
		_vOutCoordinates[ndx].y *= _fScalingFactor;
	}
}

void FontProcessor::ParseCoordinateValue(File& _fFontFile, const uint8_t _u8Flag, const uint8_t _u8VectorSize, const uint8_t _u8SignOrSkip, uint32_t _u32Offset, int& _iCoordAcc, float& _fOutCoordinate) {
	if (Util::IsBitSet(_u8Flag, _u8VectorSize)) {
		int iOffset = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);
		_iCoordAcc += Util::IsBitSet(_u8Flag, _u8SignOrSkip) ? iOffset : -iOffset;
	}
	else if (!Util::IsBitSet(_u8Flag, _u8SignOrSkip)) {
		_iCoordAcc += FontUtil::ReadTTFValue<int16_t>(_fFontFile);
	}

	_fOutCoordinate = static_cast<float>(_iCoordAcc - _u32Offset);
}

std::vector<TTFContour> FontProcessor::PackContours(const std::vector<TTFPoint>& _vPoints, const std::vector<uint16_t> _vContourEndPoints) {
	std::vector<TTFContour> vContours;

	int iContourStart = 0;
	for (int ndx = 0; ndx < _vContourEndPoints.size(); ++ndx) {
		std::vector<TTFPoint> vContourPoints;
		TTFContour tContour;

		int iNumPointsInContour = _vContourEndPoints[ndx] - iContourStart + 1;

		vContourPoints.insert(vContourPoints.end(), _vPoints.begin() + iContourStart, _vPoints.begin() + iContourStart + iNumPointsInContour);

		int iPointOffset = GetPointOffset(vContourPoints);

		RecreateImpliedPoints(vContourPoints, iPointOffset);

		for (int sNdx = iPointOffset; sNdx < vContourPoints.size(); sNdx += 2) {
			tContour.m_vCurves.push_back({ vContourPoints[sNdx],
			vContourPoints[(sNdx + 1) % vContourPoints.size()],
			vContourPoints[(sNdx + 2) % vContourPoints.size()] });
		}

		MakeContourCurvesMonotonic(tContour);

		vContours.push_back(tContour);

		iContourStart = _vContourEndPoints[ndx] + 1;
	}

	return vContours;
}

int FontProcessor::GetPointOffset(const std::vector<TTFPoint>& _vPoints) {
	int iPointOffset;
	for (iPointOffset = 0; iPointOffset < _vPoints.size(); ++iPointOffset) {
		if (_vPoints[iPointOffset].m_bOnCurve) break;
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

		if (curr.m_bOnCurve == next.m_bOnCurve && ndx < _vPoints.size()) {
			TTFPoint mid = { (curr.x + next.x) / 2, (curr.y + next.y) / 2 };
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
std::vector<TTFPoint> FontProcessor::SplitCurveAtTurningPoint(const TTFCurve& _tCurve) {
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

	vPoints[0] = { fP1AX, vec2TurningPoint.y };
	vPoints[1] = { vec2TurningPoint.x, vec2TurningPoint.y };
	vPoints[2] = { fP1BX, vec2TurningPoint.y };
	vPoints[3] = { _tCurve.m_p2 };

	return vPoints;
}

void FontProcessor::RasterizeGlyph(TTFBitmap& _bBitmap, std::vector<TTFContour>& _vAllContours) {
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
				.m_fCurrentX = aCurve.m_arrPoints[iMinYIndex].x,
				.m_bDownward = iMinYIndex == 2
			};

			vEdgeTable.push_back(eteEntry);
		}
	}

	//Start by sorting the edges on their minimum Y
	std::sort(vEdgeTable.begin(), vEdgeTable.end(), TTFEdgeTableEntry::CompareYLess());

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
		std::sort(vActiveEdges.begin(), vActiveEdges.end(), TTFEdgeTableEntry::CompareXLess());

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
				_bBitmap.PlotPixel(iX, iScanline, HC_FONT_BASE_COLOR);
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
