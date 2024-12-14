#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <Torchlight/Util/FontUtil.hpp>

#include <HellfireControl/Asset/Font.hpp>

class FontProcessor {
public:
	static Font ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
private:
	static void GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations);
	static void GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations, uint16_t& _u16OutPixelsPerEm, uint16_t& _u16OutMaxComponentDepth);
	static void ParseGlyph(File& _fFontFile, uint16_t _u16MaxDepth, float _fScalingFactor, TTFGlyphData& _gdOutGlyphData);
	static void ParseCharacterMap(File& _fFontFile, uint32_t _u32CMAPPosition, std::map<UTF8PaddedChar,int>& _mOutCharacterMap);
	static void CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, bool _bIsSDF, std::vector<TTFBitmap>& _vOutBitmaps);
	static void AntiAliasGlyphs(std::vector<TTFBitmap>& _vBitmaps);
	static void ConvertGlyphsToSDF(std::vector<TTFBitmap>& _vBitmaps, bool _bIsMultiChannel);
	static TTFBitmap CollateGlyphs(std::vector<TTFBitmap>& _vBitmaps);
	static Font PackIntoFontAsset(TTFBitmap& _bFontAtlas, std::map<UTF8PaddedChar,int> _mCharacterMap, std::vector<TTFGlyphData>& _vGlyphData);

	static std::unique_ptr<TTFSimpleGlyph> ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, float _fScalingFactor, uint32_t _u32MinX, uint32_t _u32MinY);
	static std::unique_ptr<TTFCompoundGlyph> ParseCompoundGlyph(File& _fFontFile, uint16_t _u16MaxDepth);
	static void ParseCoordinateFlags(File& _fFontFile, std::vector<uint8_t>& _vFlags);
	static void ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, float _fScalingFactor, uint32_t _u32MinX, uint32_t _u32MinY, std::vector<TTFPoint>& _vOutCoordinates);
	static void ParseCoordinateValue(File& _fFontFile, const uint8_t _u8Flag, const uint8_t _u8VectorSize, const uint8_t _u8SignOrSkip, uint32_t _u32Offset, int & _iCoordAcc, float & _fOutCoordinate);
	static std::vector<TTFContour> PackContours(const std::vector<TTFPoint>& _vPoints, const std::vector<uint16_t> _vContourEndPoints);
	static int GetPointOffset(const std::vector<TTFPoint>& _vPoints);
	static void RecreateImpliedPoints(std::vector<TTFPoint>& _vPoints, int _iPointOffset);
	static void MakeContourCurvesMonotonic(TTFContour& _tContour);
	static std::vector<TTFPoint> SplitCurveAtTurningPoint(const TTFCurve& _tCurve);

	static void RasterizeGlyph(TTFBitmap& _bBitmap, std::vector<TTFContour>& _vAllContours);
};