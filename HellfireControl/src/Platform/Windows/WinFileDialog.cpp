
#include <Platform/Windows/WinFileDialog.hpp>

#include <Platform/Windows/WinDialogEventHandler.hpp>

/// <summary>
/// THIS CODE IS NOT MINE, IT WAS PULLED FROM AND ADAPTED FROM THE MSDN
/// </summary>
 
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

std::vector<std::string> PlatformFileDialog::m_vUserSelections;

const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
	{L"Word Document (*.doc)",       L"*.doc"},
	{L"Web Page (*.htm; *.html)",    L"*.htm;*.html"},
	{L"Text Document (*.txt)",       L"*.txt"},
	{L"All Documents (*.*)",         L"*.*"}
};

HRESULT PlatformFileDialog::CreateEventHandlerInstance(REFIID _rId, void** _ppVoid) {
	*_ppVoid = NULL;

	DialogEventHandler* pEventHandler = new (std::nothrow) DialogEventHandler();

	HRESULT hRes = pEventHandler ? S_OK : E_OUTOFMEMORY;

	if (SUCCEEDED(hRes)) {
		hRes = pEventHandler->QueryInterface(_rId, _ppVoid);

		pEventHandler->Release();
	}

	return hRes;
}

void PlatformFileDialog::CreateFileDialog(uint8_t _u8Type, const std::vector<std::string>& _vAllowedExtensions, const std::string& _strDefaultPath) {
	m_vUserSelections.clear();

	IFileDialog* pFileDialog = NULL;

	CLSID clsidDialogType = _u8Type == 0 ? CLSID_FileOpenDialog : CLSID_FileSaveDialog; //If the parameter is 0, it must be open, all other values are save.

	HRESULT hRes = CoCreateInstance(clsidDialogType, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));

	if (SUCCEEDED(hRes)) {
		IFileDialogEvents* pDialogEvents = NULL;

		hRes = CreateEventHandlerInstance(IID_PPV_ARGS(&pDialogEvents));

		if (SUCCEEDED(hRes)) {
			DWORD dwCookie;

			hRes = pFileDialog->Advise(pDialogEvents, &dwCookie);

			if (SUCCEEDED(hRes)) {
				DWORD dwFlags;

				hRes = pFileDialog->GetOptions(&dwFlags);

				if (SUCCEEDED(hRes)) {
					hRes = pFileDialog->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);

					if (SUCCEEDED(hRes)) {
						hRes = pFileDialog->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes); //TODO: Replace with _vAllowedExtensions

						if (SUCCEEDED(hRes)) {
							hRes = pFileDialog->SetFileTypeIndex(INDEX_WORDDOC); //TODO: Replace with _vAllowedExtensions

							if (SUCCEEDED(hRes)) {
								hRes = pFileDialog->SetDefaultExtension(L"doc"); //TODO: Replace with the first extension in _vAllowedExtensions

								if (SUCCEEDED(hRes)) {
									hRes = pFileDialog->Show(NULL);

									if (SUCCEEDED(hRes)) {
										IShellItem* pShellItemResult;

										hRes = pFileDialog->GetResult(&pShellItemResult);

										if (SUCCEEDED(hRes)) {
											PWSTR pszFilePath = NULL;

											hRes = pShellItemResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

											if (SUCCEEDED(hRes)) {
												TaskDialog(NULL,
													NULL,
													L"Test",
													pszFilePath,
													NULL,
													TDCBF_OK_BUTTON,
													TD_INFORMATION_ICON,
													NULL);
												CoTaskMemFree(pszFilePath);
											}
											pShellItemResult->Release();
										}
									}
								}
							}
						}
					}
				}
				pFileDialog->Unadvise(dwCookie);
			}
			pDialogEvents->Release();
		}
		pFileDialog->Release();
	}
}

std::vector<std::string> PlatformFileDialog::GetUserSelections() {
	return m_vUserSelections;
}
