#pragma once

#include <HellfireControl/Asset/Converters/Font/FontCommon.hpp>

struct TTFTableDirectoryEntry {
	uint32_t m_u32Checksum = 0;
	uint32_t m_u32Offset = 0;
	uint32_t m_u32Length = 0;

	bool IsValid() const {
		return !(m_u32Checksum == 0 && m_u32Offset == 0 && m_u32Length == 0);
	}
};

typedef std::map<UTF8PaddedChar, uint32_t> CharacterMap;

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

	uint16_t m_u16GlyphCount = UINT16_MAX;
	int16_t m_i16IndexToLocFormat = 0;
	uint16_t m_u16UnitsPerEm = 0;
	uint16_t m_u16NumOfLongHorMetrics = 0;
	float m_fFontSize = 0.0f; //TEMPORARY!!!!
	float m_fScaleFactor = 0.0f;
	CharacterMap m_cmCMap;
};

struct GlyphInfo {
	uint16_t m_u16AdvanceWidth = 0;
	int16_t m_i16LeftSideBearing = 0;
	Vec2F m_v2Min;
	Vec2F m_v2Max;
	std::vector<TTFVertex> m_vVerts;
};

class FontTTFParser {
public:
	static FontInfo InitializeFont(File& _fFontFile, float _fFontHeightPoints);
	static GlyphInfo GetGlyphInfo(File& _fFontFile, const FontInfo& _fiInfo, uint32_t _u32GlyphIndex);

private:
	static std::vector<uint8_t> GetCoordinateFlags(File& _fFontFile, size_t sVertexCount);
	static std::vector<Vec2F> GetCoordinates(File& _fFontFile, const size_t sVertexCount, const std::vector<uint8_t>& vFlags);
	static std::vector<TTFVertex> PackVertices(const std::vector<uint16_t>& _vContourEndPoints, const std::vector<Vec2F>& _vCoordinates, const std::vector<uint8_t>& _vFlags);
	static std::vector<TTFVertex> PackContourVertices(const std::vector<Vec2F>& _vContourCoords, const std::vector<uint8_t>& _vContourFlags);
};