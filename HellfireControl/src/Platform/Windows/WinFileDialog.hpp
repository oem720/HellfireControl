#pragma once

#include <Platform/OSCommon.hpp>

class PlatformFileDialog {
private:
	static std::vector<std::string> m_vUserSelections;

	static std::vector<COMDLG_FILTERSPEC> m_vFilterNames;

	static std::vector<COMDLG_FILTERSPEC> m_vFilterCombinations;

	static HRESULT CreateEventHandlerInstance(REFIID _rId, void** _ppVoid);

	static std::vector<COMDLG_FILTERSPEC> ResolveFileExtensionFlags(uint64_t _u64FileExtensionFlags);

	static std::wstring ResolveDefaultFileExtension(const std::vector<COMDLG_FILTERSPEC> & _vFilters);
public:
	static bool CreateFileDialog(uint8_t _u8Type, uint64_t _u64FileExtensions, const std::string& _strDefaultPath);

	static std::vector<std::string> GetUserSelections();
};