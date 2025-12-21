#pragma once

#include <HellfireControl/Asset/Converters/Font/FontCommon.hpp>

struct TTFTableDirectoryEntry {
	uint32 m_u32Checksum = 0;
	uint32 m_u32Offset = 0;
	uint32 m_u32Length = 0;

	bool IsValid() const {
		return !(m_u32Checksum == 0 && m_u32Offset == 0 && m_u32Length == 0);
	}
};

typedef Map<UTF8PaddedChar, uint32> CharacterMap;

struct FontInfo {
	TTFTableDirectoryEntry	m_tdeLoca,
		m_tdeHead,
		m_tdeGlyf,
		m_tdeHHea,
		m_tdeHMtx,
		m_tdeCMap,
		m_tdeMaxP,
		m_tdeKern,
		m_tdeGPos;

	uint16 m_u16GlyphCount = UINT16_MAX;
	int16 m_i16IndexToLocFormat = 0;
	uint16 m_u16UnitsPerEm = 0;
	uint16 m_u16NumOfLongHorMetrics = 0;
	float m_fFontSize = 0.0f; //TEMPORARY!!!!
	float m_fScaleFactor = 0.0f;
	CharacterMap m_cmCMap;
};

struct GlyphInfo {
	uint16 m_u16AdvanceWidth = 0;
	int16 m_i16LeftSideBearing = 0;
	Vec2F m_v2Min;
	Vec2F m_v2Max;
	Array<TTFVertex> m_vVerts;
};

class FontTTFParser {
public:
	static FontInfo InitializeFont(File& _fFontFile, float _fFontHeightPoints);
	static GlyphInfo GetGlyphInfo(File& _fFontFile, const FontInfo& _fiInfo, uint32 _u32GlyphIndex);

private:
	static Array<uint8> GetCoordinateFlags(File& _fFontFile, size_t sVertexCount);
	static Array<Vec2F> GetCoordinates(File& _fFontFile, const size_t sVertexCount, const Array<uint8>& vFlags);
	static Array<TTFVertex> PackVertices(const Array<uint16>& _vContourEndPoints, const Array<Vec2F>& _vCoordinates, const Array<uint8>& _vFlags);
	static Array<TTFVertex> PackContourVertices(const Array<Vec2F>& _vContourCoords, const Array<uint8>& _vContourFlags);
};