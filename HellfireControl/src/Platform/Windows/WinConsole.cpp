#include <HellfireControl/Core/Console.hpp>

#ifdef _WIN32
#include <Platform/Windows/WinConsole.hpp>
#include <stdexcept>

bool WinConsole::m_bInit = false;

std::string Console::ColorText(const std::string& _strText, ConsoleColor _ccColor) {
	std::stringstream ssStr;

	ssStr << "\033[" << std::to_string(_ccColor) << "m" << _strText << "\033[0m";

	return ssStr.str();
}

void Console::PlatformPrint(const std::string& _strMessage) {
	if (!WinConsole::m_bInit) {
		if (!WinConsole::InitConsole()) {
			throw std::runtime_error("ERROR: Console failed to initialize!");
			return;
		}
	}

	std::cout << _strMessage;
}

void Console::PlatformPrintLine(const std::string& _strMessage) {
	PlatformPrint(_strMessage);

	std::cout << std::endl;
}

bool WinConsole::InitConsole() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE || hIn == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD dwOutCurr = 0;
	DWORD dwInCurr = 0;

	if (!GetConsoleMode(hOut, &dwOutCurr) || !GetConsoleMode(hIn, &dwInCurr)) {
		return false;
	}

	DWORD dwOutRequested = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

	DWORD dwOut = dwOutCurr | dwOutRequested;
	DWORD dwIn = dwInCurr | ENABLE_VIRTUAL_TERMINAL_INPUT;

	if (!SetConsoleMode(hOut, dwOut)) {
		dwOutRequested = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		dwOut = dwOutCurr | dwOutRequested;

		if (!SetConsoleMode(hOut, dwOut)) {
			return false;
		}
	}

	if (!SetConsoleMode(hIn, dwIn)) {
		return false;
	}

	return true;
}
#endif