#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

struct HCGRFHeader {
	uint32_t m_u32MagicNumber;
	uint16_t m_u16Version;
	uint8_t m_u8Flags;
	uint8_t m_u8DirectorySize;
};

struct HCGRFTableDirectoryEntry {
	char m_cTag[4];
	uint32_t m_u32Offset;
};

struct HCGRFCMapEntry {
	uint32_t m_u32StartCode;
	uint32_t m_u32CodeCount;
	uint32_t m_u32GlyphIndex;
};

struct HCGRFImageDescriptor {
	uint32_t m_u32ImageWidth;
	uint32_t m_u32ImageHeight;
	uint8_t m_u8NumChannels;
};

enum HCGRFFlags : uint8_t {
	IS_COMPRESSED = (1 << 0),
	IS_BITMAP = (1 << 1),
	IS_SINGLE_CHANNEL = (1 << 2),
	IS_MULTI_CHANNEL = (1 << 3),
	SEGMENTED_ATLAS = (1 << 4)
};

struct CharacterRange {
	UTF8PaddedChar m_cFirstChar;
	uint32_t m_u32Count;
};

//These are inspired by the STB implementation.
enum class TTFVertexType : uint8_t {
	CONTOUR_START,
	LINE_SEGMENT,
	QUADRATIC_CURVE,
	CUBIC_CURVE
};

struct TTFVertex {
	Vec2F m_v2Vert;
	uint8_t m_u8Flags = 0;
	TTFVertexType m_vtType = TTFVertexType::CONTOUR_START;
};
