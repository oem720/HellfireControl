
#include <Platform/Windows/WinConsole.hpp>

#include <stdexcept>

namespace PlatformConsole {
	static bool g_bInit = false; //Used to determine if the console has been formatted properly

	bool InitConsole() {
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

	void Print(const std::string& _strMessage, uint8_t _u8Color) {
		if (!g_bInit) {
			if (!InitConsole()) {
				throw std::runtime_error("ERROR: Console failed to initialize!");
				return;
			}
		}

		printf(("\033[%um" + _strMessage + "\033[0m").c_str(), _u8Color);
	}
}
