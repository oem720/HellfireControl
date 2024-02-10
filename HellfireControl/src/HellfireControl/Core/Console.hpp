#pragma once

#include <iostream>
#include <HellfireControl/Core/Common.hpp>

namespace Console {
	enum ConsoleColor : uint8_t {
		WHITE = 37,
		BLACK = 30,
		RED = 31,
		GREEN = 32,
		YELLOW = 33,
		BLUE = 34,
		MAGENTA = 35
	};

	void Print(const std::string& _strMessage, ConsoleColor _ccColor = WHITE);
}