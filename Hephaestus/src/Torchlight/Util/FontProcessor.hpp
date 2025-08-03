#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Image.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <Torchlight/Util/FontUtil.hpp>

class FontProcessor {
public:
	static Font ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const std::string& _strFilepath, TTFCharacterRange _crCharactersToProcess, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const std::string& _strFilepath, std::vector<TTFCharacterRange>& _vCharacterRanges, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
private:
	static void InitializeFont(File& _fFontFile, float _fFontSizePixels, TTFFontInfo& _fiInfo);
	static bool IsValidFont(File& _fFontFile);
	static TTFTableDirectoryEntry FindTable(File& _fFontFile, uint16_t _u16TableCount, uint16_t _u16SearchRange, uint16_t _u16EntrySelector, uint16_t _u16RangeShift, TTFTag _tTag);
	static TTFGlyphInfo GetGlyphInfo(File& _fFontFile, const TTFFontInfo& _fiInfo, uint32_t _u32GlyphIndex);
	static std::vector<uint8_t> GetCoordinateFlags(File& _fFontFile, size_t sVertexCount);
	static std::vector<Vec2F> GetCoordinates(File& _fFontFile, const size_t sVertexCount, const std::vector<uint8_t>& vFlags);
	static std::vector<TTFVertex> PackVertices(const std::vector<uint16_t>& _vContourEndPoints, const std::vector<Vec2F>& _vCoordinates, const std::vector<uint8_t>& _vFlags);
	static std::vector<TTFVertex> PackContourVertices(const std::vector<Vec2F>& _vContourCoords, const std::vector<uint8_t>& _vContourFlags);
	static Vec2F GetFontAtlasSize(std::vector<TTFGlyphInfo>& vGlyphData, TTFFontInfo& fiInfo);
	static TTFBakedGlyphInfo DrawGlyph(ImageRGB8& _iBitmap, const TTFGlyphInfo& _tGlyphData, const Vec2F& _v2Location, const float _fScale);
	static Vec4F CalculateScaledBoundingVolume(const Vec2F& _v2Location, const Vec2F& _v2Min, const Vec2F& _v2Max, const float _fScale);
	static std::vector<TTFEdge> PackAndFlattenContours(const TTFGlyphInfo& _tGlyphData, const Vec4F& _v4BoundingBox, const float _fScale);
	static TTFEdge ConstructEdge(const Vec2F& _vMin, const Vec2F& _vMax, const Vec2F& _v2PointShift, const Vec2F& _v2GlyphMinShift, const float _fScale);
	static std::vector<TTFEdge> ConstructFlattenedEdgeList(const std::vector<Vec2F>& _vVerts, const Vec2F & _v2BoundingBoxShift, const Vec2F& _v2GlyphMinShift, const float _fScale);
	static std::vector<Vec2F> FlattenQuadraticCurve(const TTFVertex & _vP0, const TTFVertex & _vP1, const TTFVertex & _vP2, const float _fScale);
};