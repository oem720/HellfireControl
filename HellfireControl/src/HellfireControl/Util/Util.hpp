#pragma once

#include <HellfireControl/Core/Common.hpp>

namespace Util {
	[[nodiscard]] std::wstring ConvertToWString(const std::string& _strConvert);

	[[nodiscard]] std::string ConvertFromWString(const std::wstring& _strConvert);

	[[nodiscard]] std::vector<char> ReadFile(const std::string& _strFilename);
}