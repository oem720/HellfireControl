
#include <HellfireControl/Core/Console.hpp>

#define HC_INCLUDE_CONSOLE //Enable console include

#include <Platform/OSInclude.hpp>

namespace Console {
	void Print(const std::string& _strMessage, ConsoleColor _ccColor) {
		PlatformConsole::Print(_strMessage, _ccColor); //Call the platform specific console function
	}
}