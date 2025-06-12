
#include <Torchlight/Util/FontUtil.hpp>

namespace FontUtil {
	TTFCharacterMap FontUtil::ReadCMapFormat4(File& _fFontFile) {
		TTFCharacterMap mCharMap;

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
			mCharMap[HC_MISSING_CHAR_GLYPH_INDEX] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
		}

		return mCharMap;
	}

	TTFCharacterMap FontUtil::ReadCMapFormat12(File& _fFontFile) {
		TTFCharacterMap mCharMap;

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
			mCharMap[HC_MISSING_CHAR_GLYPH_INDEX] = 0; //Manually add missing char glyph (some fonts may be malformed and missing this, which is vital for display)
		}

		return mCharMap;
	}
}