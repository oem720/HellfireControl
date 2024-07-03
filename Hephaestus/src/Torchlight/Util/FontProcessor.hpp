#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <Torchlight/Util/FontUtil.hpp>

class FontProcessor {
public:
	static void ProcessFont(const std::string& _strFilepath);
private:
	static void GetDataBlockOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mOutDataBlockLocations);
	static void GetGlyphOffsets(File& _fFontFile, std::map<std::string, uint32_t>& _mDataBlockLocations, std::vector<uint32_t>& _vOutGlyphLocations, uint16_t& _u16OutPixelsPerEm);
	static void ParseGlyph(File& _fFontFile, TTFGlyphData& _gdOutGlyphData);
	static std::unique_ptr<TTFSimpleGlyph> ParseSimpleGlyph(File& _fFontFile, int16_t _i16ContourCount, uint32_t _u32MinX, uint32_t _u32MinY);
	static std::unique_ptr<TTFCompoundGlyph> ParseCompoundGlyph(File& _fFontFile, int16_t _i16ContourCount);
	static void ParseCoordinates(File& _fFontFile, const std::vector<uint8_t>& _vFlags, bool bIsX, std::vector<TTFPoint>& _vOutCoordinates, uint32_t _u32MinX, uint32_t _u32MinY);

	static void CreateGlyphBitmaps(const std::vector<TTFGlyphData>& _vGlyphs, uint16_t _u16PixelsPerEm);
};