#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Font.hpp>

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