
#include <HellfireControl/Core/Console.hpp>

void Console::Print(const std::string& _strMessage, ConsoleColor _ccColor) {
	PlatformPrint(ColorText(_strMessage, _ccColor));
}

void Console::PrintLine(const std::string& _strMessage, ConsoleColor _ccColor) {
	PlatformPrintLine(ColorText(_strMessage, _ccColor));
}

void Console::PrintDebugMessage(const std::string& _strMessage, MessageType _mtType) {
	PlatformPrint(GetMessagePrefix(_mtType));

	PlatformPrintLine(_strMessage);
}

std::string Console::GetMessagePrefix(MessageType _mtType) {
	std::string strPrefix;

	switch (_mtType) {
	case LOG: {
		strPrefix = ColorText("LOG", WHITE);
	} break;
	case INFO: {
		strPrefix = ColorText("INFO", BLUE);
	} break;
	case SUCCESS: {
		strPrefix = ColorText("SUCCESS", GREEN);
	} break;
	case FAIL: {
		strPrefix = ColorText("FAIL", RED);
	} break;
	case WARNING: {
		strPrefix = ColorText("WARNING", YELLOW);
	} break;
	case ERROR: {
		strPrefix = ColorText("ERROR", RED);
	} break;
	}

	std::stringstream ssTimeStampedId;

	std::time_t tCurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::tm* tLocalTime = std::localtime(&tCurrentTime);

	ssTimeStampedId << "[" << strPrefix << "][" << std::this_thread::get_id() << "][" << std::put_time(tLocalTime, "%H:%M:%S") << "] ";

	return ssTimeStampedId.str();
}