#pragma once

#include <Platform/OSCommon.hpp>

class PlatformFileDialog {
private:
	static Array<String> m_vUserSelections;

	static Array<COMDLG_FILTERSPEC> m_vFilterNames;

	static Array<COMDLG_FILTERSPEC> m_vFilterCombinations;

	static HRESULT CreateEventHandlerInstance(REFIID _rId, void** _ppVoid);

	static Array<COMDLG_FILTERSPEC> ResolveFileExtensionFlags(uint64 _u64FileExtensionFlags);

	static std::wstring ResolveDefaultFileExtension(const Array<COMDLG_FILTERSPEC> & _vFilters);

	static void HandleOpenDialogSelection(IFileOpenDialog* _pDialog);

	static void HandleSaveDialogSelection(IFileSaveDialog* _pDialog);
public:
	static bool CreateFileDialog(uint8 _u8Type, uint64 _u64FileExtensions, const String& _strDefaultPath);

	static Array<String> GetUserSelections();
};