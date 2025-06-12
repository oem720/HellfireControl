#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/File.hpp>
#include <HellfireControl/Core/Image.hpp>

#include <Torchlight/Util/FontTypes.hpp>

#define HC_MISSING_CHAR_GLYPH_INDEX 65535

//For testing font glyphs individually.
#define HC_TESTING_FONT_GLYPH_RASTERIZATION 1 

namespace FontUtil {
	template<typename T, HC_SFINAE_REQUIRE_INTEGER(T)>
	static HC_INLINE T ReadTTFValue(File& _fFile) {
		T value = 0;
		_fFile >> value;
		Util::ReverseBytes(value);

		return value;
	}

	template<typename T, HC_SFINAE_REQUIRE_FLOATING_POINT(T)>
	static HC_INLINE T ConvertToFloatingPoint(F2Dot14 _fixed) {
		return static_cast<T>(_fixed) / static_cast<T>(1 << 14);
	}

	TTFCharacterMap ReadCMapFormat4(File& _fFontFile);
	TTFCharacterMap ReadCMapFormat12(File& _fFontFile);
}