#pragma once

#include <HellfireControl/Asset/Converters/Font/FontCommon.hpp>

#include <HellfireControl/Asset/Font.hpp>

class FontProcessor {
public:
	static Font ProcessFont(const String& _strFilepath, uint16 _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const String& _strFilepath, CharacterRange _crCharactersToProcess, uint16 _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);
	static Font ProcessFont(const String& _strFilepath, Array<CharacterRange>& _vCharacterRanges, uint16 _u16FontSize = 12, FontType _ftType = FontType::FONT_BITMAP);

	static HCUID SaveFontToDisk(const String& _strFilepath, const Font& _fFontData);
};