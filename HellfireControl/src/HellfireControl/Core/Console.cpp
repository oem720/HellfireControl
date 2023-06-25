
#include <HellfireControl/Core/Console.hpp>

#include <Platform/OSInclude.hpp>

namespace Console {
	void Print(const std::string& _strMessage, ConsoleColor _ccColor) {
		PlatformConsole::Print(_strMessage, _ccColor); //Call the platform specific console function
	}
}