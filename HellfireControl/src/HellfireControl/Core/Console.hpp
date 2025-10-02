#pragma once

#include <iostream>
#include <HellfireControl/Core/Common.hpp>

enum ConsoleColor : uint8_t {
	WHITE = 37,
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35
};

enum MessageType : uint8_t {
	LOG,
	INFO,
	SUCCESS,
	FAIL,
	WARNING,
	ERROR
};

class Console {
private:
	static std::string GetMessagePrefix(MessageType _mtType);

	static std::string ColorText(const std::string& _strText, ConsoleColor _ccColor);

	static void PrintDebugMessage(const std::string& _strMessage, MessageType _mtType);

	static void PlatformPrint(const std::string& _strMessage);

	static void PlatformPrintLine(const std::string& _strMessage);

public:
	static void Print(const std::string& _strMessage, ConsoleColor _ccColor = WHITE);

	static void PrintLine(const std::string & _strMessage, ConsoleColor _ccColor = WHITE);

	static void DebugLog(const std::string& _strMessage) { PrintDebugMessage(_strMessage, LOG); }

	static void DebugInfo(const std::string& _strMessage) { PrintDebugMessage(_strMessage, INFO); }

	static void DebugSuccess(const std::string& _strMessage) { PrintDebugMessage(_strMessage, SUCCESS); }

	static void DebugFail(const std::string& _strMessage) { PrintDebugMessage(_strMessage, FAIL); }

	static void DebugWarn(const std::string& _strMessage) { PrintDebugMessage(_strMessage, WARNING); }

	static void DebugError(const std::string& _strMessage) { PrintDebugMessage(_strMessage, ERROR); }
};