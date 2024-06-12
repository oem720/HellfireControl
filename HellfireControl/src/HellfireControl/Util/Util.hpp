#pragma once

#include <HellfireControl/Core/Common.hpp>

namespace Util {
	[[nodiscard]] std::wstring ConvertToWString(const std::string& _strConvert);

	[[nodiscard]] std::string ConvertFromWString(const std::wstring& _strConvert);

	[[nodiscard]] std::vector<char> ReadFile(const std::string& _strFilename);

	template<typename T, typename = HC_SFINAE_REQUIRE_INTEGER>
	bool IsBitSet(T _value, uint8_t _u8BitToCheck) {
		return ((_value >> _u8BitToCheck) & 0x1);
	}

	template<typename T, typename = HC_SFINAE_REQUIRE_INTEGER>
	void InverseBytes(T& _value) {
		union {
			T value = 0;
			char bytes[sizeof(T)];
		} ar;

		ar.value = _value;

		std::reverse(ar.bytes, ar.bytes + sizeof(T));

		_value = ar.value;
	}
}