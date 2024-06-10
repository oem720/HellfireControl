#pragma once

#include <Platform/OSCommon.hpp>

class PlatformFileDialog {
private:
	static std::vector<std::string> m_vUserSelections;

	static HRESULT CreateEventHandlerInstance(REFIID _rId, void** _ppVoid);
public:
	static void CreateFileDialog(uint8_t _u8Type, const std::vector<std::string>& _vAllowedExtensions, const std::string& _strDefaultPath);

	static std::vector<std::string> GetUserSelections();
};