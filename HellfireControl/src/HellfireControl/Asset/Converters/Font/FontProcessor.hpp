#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Font.hpp>

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


struct CharacterRange {
	UTF8PaddedChar m_cFirstChar;
	uint32_t m_u32Count;
};

class FontProcessor {
public:
	static Font ProcessFont(const std::string& _strFilepath, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const std::string& _strFilepath, CharacterRange _crCharactersToProcess, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const std::string& _strFilepath, std::vector<CharacterRange>& _vCharacterRanges, uint16_t _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);

	static HCUID SaveFontToDisk(const std::string& _strFilepath, const Font& _fFontData);
};