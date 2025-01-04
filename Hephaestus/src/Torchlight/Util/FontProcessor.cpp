
#include <Torchlight/Util/FontProcessor.hpp>

#include <Torchlight/Util/FontHelper.hpp>

using namespace FontUtil;
using namespace FontHelper;

#define HC_FONT_DPI 72
#define HC_FONT_SCREEN_RESOLUTION 96
#define HC_FONT_BASE_COLOR 0xFFFFFFFF

Font FontProcessor::ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize, FontType _ftType) {
	File fFontFile(_strFilepath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);

	std::map<std::string, uint32_t> mDataBlockLocations;

	GetDataBlockOffsets(fFontFile, mDataBlockLocations);

	std::vector<uint32_t> vGlyphOffsets;
	uint16_t u16UnitsPerEm = 0;
	uint16_t u16MaxRecursionDepth = 0;

	GetGlyphOffsets(fFontFile, mDataBlockLocations, vGlyphOffsets, u16UnitsPerEm, u16MaxRecursionDepth);

	std::vector<TTFGlyphData> vGlyphData(vGlyphOffsets.size());

	uint32_t u32GlyphTableStart = mDataBlockLocations["glyf"];

	for (int ndx = 0; ndx < vGlyphData.size(); ++ndx) {
		fFontFile.GoToByte(u32GlyphTableStart + vGlyphOffsets[ndx]);

		ParseGlyph(fFontFile, u16MaxRecursionDepth, vGlyphData[ndx]);
	}
		
	std::map<UTF8PaddedChar, int> mCharacterMap; //The integer corresponds to the index of the glyph as stored in the list of glyph data.

	ParseCharacterMap(fFontFile, mDataBlockLocations["cmap"], mCharacterMap);

	std::vector<TTFBitmap> vBitmaps;

	float fScale = static_cast<float>(_u16FontSize * HC_FONT_SCREEN_RESOLUTION) / static_cast<float>(HC_FONT_DPI * u16UnitsPerEm);

	CreateGlyphBitmaps(vGlyphData, _ftType, fScale, vBitmaps);

#if HC_TESTING_FONT_GLYPH_RASTERIZATION
	for (int ndx = 0; ndx < vBitmaps.size(); ++ndx) {
		FontUtil::SaveToFile(vBitmaps[ndx], ndx);
	}
#endif

	TTFBitmap bCollatedTexture = CollateGlyphs(vBitmaps); //TODO: merge this whole step with rasterization to avoid needing an extra BLIT step

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

void FontProcessor::GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphOffsets, uint16_t& _u16OutUnitsPerEm, uint16_t& _u16OutMaxComponentDepth) {
	_fFontFile.GoToByte(_mDataBlockLocations["maxp"]); //Skip to the table that holds counts

	_fFontFile.AdvanceBytes(4); //Skip over version info

	uint16_t u16GlyphCount = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(24); //Skip over much of the table

	_u16OutMaxComponentDepth = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["head"]);

	_fFontFile.AdvanceBytes(18);

	_u16OutUnitsPerEm = FontUtil::ReadTTFValue<uint16_t>(_fFontFile);

	_fFontFile.AdvanceBytes(30);

	bool bIsTwoByte = !FontUtil::ReadTTFValue<int16_t>(_fFontFile);

	_fFontFile.GoToByte(_mDataBlockLocations["loca"]);
	_vOutGlyphOffsets.resize(u16GlyphCount);

	for (size_t ndx = 0; ndx < u16GlyphCount; ++ndx) {
		_vOutGlyphOffsets[ndx] = (bIsTwoByte ? (FontUtil::ReadTTFValue<uint16_t>(_fFontFile) * 2u) : FontUtil::ReadTTFValue<uint32_t>(_fFontFile));
	}
}

void FontProcessor::ParseGlyph(File& _fFontFile, uint16_t _u16MaxDepth, TTFGlyphData& _gdOutGlyphData) {
	_gdOutGlyphData.first = {
		.m_i16ContourCount = FontUtil::ReadTTFValue<int16_t>(_fFontFile),
		.m_fXMin = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fYMin = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fXMax = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile)),
		.m_fYMax = static_cast<float>(FontUtil::ReadTTFValue<FWord>(_fFontFile))
	};

	if (_gdOutGlyphData.first.m_i16ContourCount >= 0) {
		_gdOutGlyphData.second = ParseSimpleGlyph(_fFontFile, _gdOutGlyphData.first.m_i16ContourCount, _gdOutGlyphData.first.m_fXMin, _gdOutGlyphData.first.m_fYMin);
	}
	else {
		_gdOutGlyphData.second = ParseCompoundGlyph(_fFontFile, _u16MaxDepth);
	}
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

void FontProcessor::CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, FontType _ftType, float _fScalingFactor, std::vector<TTFBitmap>& _vOutBitmaps) {
	for (const auto& glyph : _vGlyphs) {
		if (glyph.first.m_i16ContourCount <= 0) {
			continue; //Skip Compound Glyphs, as they are dynamically assembled when drawing text
		}

		//Here, we actually scale the bitmap before rasterization. This is because the raw unscaled size is used for rasterization
		//but the bitmap itself is scaled down, creating a downsampling effect.
		TTFBitmap bBitmap(
			static_cast<uint32_t>(std::ceilf((glyph.first.m_fXMax - glyph.first.m_fXMin) * _fScalingFactor)),
			static_cast<uint32_t>(std::ceilf((glyph.first.m_fYMax - glyph.first.m_fYMin) * _fScalingFactor))
		);

		//This grossness comes straight from my desire to "simplify" certain data types. The glyph data block that follows the descriptor
		//must be downcasted into a SimpleGlyph. It is impossible to actually get a compound glyph in this segment of code, but because of
		//setup, this downcast is required anyway. TODO: simplify the simplification.
		TTFSimpleGlyph* glyphData = (TTFSimpleGlyph*)glyph.second.get();

		if (_ftType == FONT_BITMAP) {
			RasterizeGlyphBitmap(bBitmap, Vec2F(glyph.first.m_fXMax - glyph.first.m_fXMin, glyph.first.m_fYMax - glyph.first.m_fYMin), glyphData->m_vContours, _fScalingFactor);
		}
		else {
			RasterizeGlyphSDF(bBitmap, glyphData->m_vContours, _ftType == FONT_MULTI_CHANNEL_SDF);
		}

		//We can thank Windows' flipped Y for this.
		bBitmap.FlipImageVertically();

		_vOutBitmaps.push_back(std::move(bBitmap));
	}
}

TTFBitmap FontProcessor::CollateGlyphs(std::vector<TTFBitmap>& _vBitmaps) {
	return TTFBitmap(1, 1);
}

Font FontProcessor::PackIntoFontAsset(TTFBitmap& _bFontAtlas, std::map<UTF8PaddedChar,int> _mCharacterMap, std::vector<TTFGlyphData>& _vGlyphData) {
	return Font();
}

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
	ParseCoordinateFlags(_fFontFile, vFlags);

	std::vector<TTFPoint> vPoints(iNumPoints);
	ParseCoordinates(_fFontFile, vFlags, _u32MinX, _u32MinY, vPoints);

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

void FontProcessor::ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, uint32_t _u32MinX, uint32_t _u32MinY, std::vector<TTFPoint>& _vOutCoordinates) {
	std::vector<int16_t> vXCoords(_vOutCoordinates.size());
	std::vector<int16_t> vYCoords(_vOutCoordinates.size());

	int iCoordValue = 0;
	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		ParseCoordinateValue(_fFontFile, _vFlags[ndx], IS_SINGLE_BYTE_X, INSTRUCTION_X, _u32MinX, iCoordValue, vXCoords[ndx]);

		_vOutCoordinates[ndx].m_bOnCurve = Util::IsBitSet(_vFlags[ndx], ON_CURVE);
	}

	iCoordValue = 0;
	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		ParseCoordinateValue(_fFontFile, _vFlags[ndx], IS_SINGLE_BYTE_Y, INSTRUCTION_Y, _u32MinY, iCoordValue, vYCoords[ndx]);
	}

	for (int ndx = 0; ndx < _vOutCoordinates.size(); ++ndx) {
		_vOutCoordinates[ndx].x = static_cast<float>(vXCoords[ndx]);
		_vOutCoordinates[ndx].y = static_cast<float>(vYCoords[ndx]);
	}
}

void FontProcessor::ParseCoordinateValue(File& _fFontFile, const uint8_t _u8Flag, const uint8_t _u8VectorSize, const uint8_t _u8SignOrSkip, uint32_t _u32Offset, int& _iCoordAcc, int16_t& _i16OutCoordinate) {
	if (Util::IsBitSet(_u8Flag, _u8VectorSize)) {
		int iOffset = FontUtil::ReadTTFValue<uint8_t>(_fFontFile);
		_iCoordAcc += Util::IsBitSet(_u8Flag, _u8SignOrSkip) ? iOffset : -iOffset;
	}
	else if (!Util::IsBitSet(_u8Flag, _u8SignOrSkip)) {
		_iCoordAcc += FontUtil::ReadTTFValue<int16_t>(_fFontFile);
	}

	_i16OutCoordinate = _iCoordAcc - _u32Offset;
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

void FontProcessor::RasterizeGlyphBitmap(TTFBitmap& _bBitmap, Vec2F _v2TrueDimensions, std::vector<TTFContour>& _vAllContours, float _fScalingFactor) {
	std::vector<TTFEdge> vEdges;

	for (const auto& aContour : _vAllContours) {
		for (const auto& aCurve : aContour.m_vCurves) {
			if (!aCurve.IsValid()) {
				continue;
			}

			bool bDownward = aCurve.m_p0.y > aCurve.m_p2.y;

			TTFEdge eEdge = {
				.m_cCurve = aCurve,
				.m_bDownward = bDownward,
				.m_fCurrentX = aCurve[bDownward ? 2 : 0].x
			};

			vEdges.push_back(eEdge);
		}
	}

	//Sorting on Y here makes it easier to determine when a scanline has reached each curve.
	//While not strictly necessary, it does make the algorithm much MUCH more efficient by allowing
	//an early out.
	std::sort(vEdges.begin(), vEdges.end(), 
		[](TTFEdge _left, TTFEdge _right) {
			return GetMinCurveY(_left.m_cCurve) < GetMinCurveY(_right.m_cCurve);
		}
	);

	std::vector<TTFEdge> vActiveEdges;
	//Because we don't know the exact amount of color per pixel due to our sampling technique,
	//we keep a count of the amount of times each fragment has been "hit" in order to average
	//the color out per pixel in the final image.
	std::vector<uint32_t> vFragmentHitCounts(0, _bBitmap.m_u32ArraySize);

	uint32_t u32Scanline = 0;
	while (u32Scanline < static_cast<uint32_t>(_v2TrueDimensions.y) && !(vEdges.empty() && vActiveEdges.empty())) {
		for (int ndx = 0; ndx < vEdges.size(); ++ndx) {
			//Because the list is sorted on Y, we can break out of this loop early the moment an edge fails to
			//meet qualification to join the active edges.
			if (static_cast<uint32_t>(GetMinCurveY(vEdges[ndx].m_cCurve)) > u32Scanline) {
				break;
			}

			vActiveEdges.push_back(vEdges[ndx]);
			vEdges.erase(vEdges.begin() + ndx--);
		}

		if (vActiveEdges.size() == 0) {
			++u32Scanline;
			continue;
		}

		for (int iX = 0; iX < static_cast<uint32_t>(_v2TrueDimensions.x); ++iX) {
			int iIntersectionCount = 0;

			for (const auto& aEdge : vActiveEdges) {
				//Here we cast to float to ensure that X values don't slip through the cracks.
				//This helps with precision in the smaller glyphs
				if (static_cast<float>(iX) > aEdge.m_fCurrentX) {
					continue;
				}

				iIntersectionCount += aEdge.m_bDownward ? -1 : 1;
			}

			if (iIntersectionCount != 0) {
				//Determine which *actual* pixel corresponds to the virtual pixels we're working with.
				//We're going to be incrementing the hit count for that fragment here.
			}
		}

		++u32Scanline;

		for (int ndx = 0; ndx < vActiveEdges.size(); ++ndx) {
			//Once again, we use the floats for more precision. This may or may not be a bad idea, given floating point
			//imprecision at small values, but it's better than truncating and losing some precision.
			if (GetMaxCurveY(vActiveEdges[ndx].m_cCurve) <= static_cast<float>(u32Scanline)) {
				vActiveEdges.erase(vActiveEdges.begin() + ndx--);
			}
		}

		for (auto& aEdge : vActiveEdges) {
			float fT = GetQuadraticX(GetMinCurveY(aEdge.m_cCurve), aEdge.m_cCurve.m_p1.y, GetMaxCurveY(aEdge.m_cCurve), static_cast<float>(u32Scanline));

			int iCurveMinNdx = GetCurveMinIndex(aEdge.m_cCurve);

			aEdge.m_fCurrentX = QuadraticInterpolation(aEdge.m_cCurve[iCurveMinNdx].x, aEdge.m_cCurve.m_p1.x, aEdge.m_cCurve[iCurveMinNdx == 0 ? 2 : 0].x, fT);
		}
	}

	for (int ndx = 0; ndx < vFragmentHitCounts.size(); ++ndx) {
		//Here we find the average coverage of the pixel based on the virtual pixels calculated.
		//The goal is to prevent issues in smaller glyphs by having a large virtual resolution.
	}
}

void FontProcessor::RasterizeGlyphSDF(TTFBitmap& _bBitmap, std::vector<TTFContour>& _vAllContours, bool _bIsMultiChannel) {

}
