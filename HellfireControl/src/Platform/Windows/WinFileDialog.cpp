
#include <Platform/Windows/WinFileDialog.hpp>

#include <Platform/Windows/WinDialogEventHandler.hpp>

#include <HellfireControl/Util/Util.hpp>

/// <summary>
/// THIS CODE IS NOT MINE, IT WAS PULLED FROM AND ADAPTED FROM THE MSDN
/// </summary>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

std::vector<std::string> PlatformFileDialog::m_vUserSelections;

std::vector<COMDLG_FILTERSPEC> PlatformFileDialog::m_vFilterNames = {
	{ L"JPG Images", L"*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi" },
	{ L"PNG Images", L"*.png" },
	{ L"GIF Images", L"*.gif" },
	{ L"Bitmap Images", L"*.bmp" },
	{ L"Wavefront Obj", L"*.obj" },
	{ L"FBX Models", L"*.fbx" },
	{ L"Graphics Library Transmission Format", L"*.gltf" },
	{ L"Direct Draw Surface", L"*.dds" },
	{ L"Khronos Texture", L"*.ktx" },
	{ L"Wavefront Material", L"*.mtl" },
	{ L"Waveform Audio Files", L"*.wav;*.wave" },
	{ L"MP3 Audio Files", L"*.mp3" },
	{ L"OGG Audio Files", L"*.ogg;*.ogv;*.oga;*.ogx;*.ogm;*.spx;*.opus" },
	{ L"MP4 Video File", L"*.mp4;*.m4p;*.m4b;*.m4r;*.m4v" },
	{ L"Quicktime File Format", L"*.mov" },
	{ L"Audio Video Interleave", L"*.avi" },
	{ L"Windows Media Video", L"*.wmv" },
	{ L"TrueType Font", L"*.ttf" },
	/*TODO Add new file formats here!*/
};

std::vector<COMDLG_FILTERSPEC> PlatformFileDialog::m_vFilterCombinations = {
	{ L"All Supported Formats", L"*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.png;*.gif;*.bmp;*.obj;*.fbx;*.gltf;*.dds;*.ktx;*.mtl;*.wav;*.wave;*.mp3;*.ogg;*.ogv;*.oga;*.ogx;*.ogm;*.spx;*.opus;*.mp4;*.m4p;*.m4b;*.m4r;*.m4v;*.mov;*.avi;*.wmv;" },
	{ L"All Supported Image Formats", L"*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.png;*.gif;*.bmp" },
	{ L"All Supported 3D Model Formats", L"*.obj;*.fbx;*.gltf" },
	{ L"All Supported Texture Formats", L"*.dds;*.ktx;*.mtl" },
	{ L"All Supported Audio Formats", L"*.wav;*.wave;*.mp3;*.ogg;*.ogv;*.oga;*.ogx;*.ogm;*.spx;*.opus" },
	{ L"All Supported Video Formats", L"*.mp4;*.m4p;*.m4b;*.m4r;*.m4v;*.mov;*.avi;*.wmv" },
	//{ L"All Hellfire Assets ()", L"" }
};

#define HC_ALL_FORMATS_INDEX 0
#define HC_ALL_IMAGES_INDEX 1
#define HC_ALL_MODELS_INDEX 2
#define HC_ALL_TEXTURES_INDEX 3
#define HC_ALL_AUDIO_INDEX 4
#define HC_ALL_VIDEO_INDEX 5

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

std::vector<COMDLG_FILTERSPEC> PlatformFileDialog::ResolveFileExtensionFlags(uint64_t _u64FileExtensionFlags) {
	std::vector<COMDLG_FILTERSPEC> vFilters;

	if (_u64FileExtensionFlags == ALL_SUPPORTED_FILE_FORMATS) {
		vFilters = m_vFilterCombinations;
		vFilters.insert(vFilters.end(), m_vFilterNames.begin(), m_vFilterNames.end());

		return vFilters; //Because we use all formats here, we can skip the rest of processing
	}

	if ((_u64FileExtensionFlags & ALL_IMAGE_FORMATS) == ALL_IMAGE_FORMATS) {
		vFilters.push_back(m_vFilterCombinations[HC_ALL_IMAGES_INDEX]);
	}

	if ((_u64FileExtensionFlags & ALL_MODEL_FORMATS) == ALL_MODEL_FORMATS) {
		vFilters.push_back(m_vFilterCombinations[HC_ALL_MODELS_INDEX]);
	}

	if ((_u64FileExtensionFlags & ALL_TEXTURE_FORMATS) == ALL_TEXTURE_FORMATS) {
		vFilters.push_back(m_vFilterCombinations[HC_ALL_TEXTURES_INDEX]);
	}

	if ((_u64FileExtensionFlags & ALL_AUDIO_FORMATS) == ALL_AUDIO_FORMATS) {
		vFilters.push_back(m_vFilterCombinations[HC_ALL_AUDIO_INDEX]);
	}

	if ((_u64FileExtensionFlags & ALL_VIDEO_FORMATS) == ALL_VIDEO_FORMATS) {
		vFilters.push_back(m_vFilterCombinations[HC_ALL_VIDEO_INDEX]);
	}

	int iFlagSum = 0;
	for (uint64_t ndx = 0, flag = 1; ndx < m_vFilterNames.size() && flag < 0xFFFFFFFFFFFFFFFF; ++ndx, flag <<= 1) {
		if (_u64FileExtensionFlags & flag) {
			vFilters.push_back(m_vFilterNames[ndx]);
		}
	}

	return vFilters;
}

std::wstring PlatformFileDialog::ResolveDefaultFileExtension(const std::vector<COMDLG_FILTERSPEC> & _vFilters) {
	const std::wstring HC_COMBINATION_NAME = L"All";

	for (int ndx = 0; ndx < _vFilters.size(); ++ndx) {
		std::wstring strFilterName(_vFilters[ndx].pszName);

		if (HC_COMBINATION_NAME.compare(strFilterName.substr(0, 3)) == 0) {
			continue;
		}

		std::wstring strExtNames(_vFilters[ndx].pszSpec);

		return strExtNames.substr(2, 3);
	}

	return std::wstring();
}

void PlatformFileDialog::HandleOpenDialogSelection(IFileOpenDialog* _pDialog) {
	IShellItemArray* pShellItemResultArray = NULL;

	HRESULT hRes = _pDialog->GetResults(&pShellItemResultArray);

	if (SUCCEEDED(hRes)) {
		DWORD dwCount;

		pShellItemResultArray->GetCount(&dwCount);

		for (int ndx = 0; ndx < dwCount; ++ndx) {
			IShellItem* pShellItem = NULL;

			pShellItemResultArray->GetItemAt(ndx, &pShellItem);

			PWSTR pszFilepath = NULL;

			hRes = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilepath);

			if (SUCCEEDED(hRes)) {
				m_vUserSelections.push_back(Util::ConvertFromWString(std::wstring(pszFilepath)));
			}
		}

		pShellItemResultArray->Release();
	}
}

void PlatformFileDialog::HandleSaveDialogSelection(IFileSaveDialog* _pDialog) {
	IShellItem* pShellItemResult = NULL;

	HRESULT hRes = _pDialog->GetResult(&pShellItemResult);

	if (SUCCEEDED(hRes)) {
		PWSTR pszFilePath = NULL;

		hRes = pShellItemResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

		if (SUCCEEDED(hRes)) {
			m_vUserSelections.push_back(Util::ConvertFromWString(std::wstring(pszFilePath)));
		}

		pShellItemResult->Release();
	}
}

bool PlatformFileDialog::CreateFileDialog(uint8_t _u8Type, uint64_t _u64FileExtensions, const std::string& _strDefaultPath) {
	m_vUserSelections.clear();

	auto aExtensions = ResolveFileExtensionFlags(_u64FileExtensions);

	IFileDialog* pFileDialog = NULL;

	HRESULT hRes;

	if (_u8Type == 0) {
		IFileOpenDialog* pTemp = NULL;

		hRes = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pTemp));

		if (FAILED(hRes)) { return false; }

		pFileDialog = pTemp;
	}
	else {
		IFileSaveDialog* pTemp = NULL;

		hRes = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pTemp));

		if (FAILED(hRes)) { return false; }

		pFileDialog = pTemp;
	}

	IFileDialogEvents* pDialogEvents = NULL;

	hRes = CreateEventHandlerInstance(IID_PPV_ARGS(&pDialogEvents));

	if (FAILED(hRes)) { return false; }

	DWORD dwCookie;

	hRes = pFileDialog->Advise(pDialogEvents, &dwCookie);

	if (FAILED(hRes)) { return false; }

	DWORD dwFlags;

	hRes = pFileDialog->GetOptions(&dwFlags);

	if (FAILED(hRes)) { return false; }

	hRes = pFileDialog->SetOptions(dwFlags | FOS_FORCEFILESYSTEM | (_u8Type == 0 ? FOS_ALLOWMULTISELECT : 0));

	if (FAILED(hRes)) { return false; }

	hRes = pFileDialog->SetFileTypes(aExtensions.size(), aExtensions.data()); //TODO: Replace with _vAllowedExtensions

	if (FAILED(hRes)) { return false; }

	hRes = pFileDialog->SetFileTypeIndex(1); //Default to the first one

	if (FAILED(hRes)) { return false; }

	hRes = pFileDialog->SetDefaultExtension(ResolveDefaultFileExtension(aExtensions).c_str());

	if (FAILED(hRes)) { return false; }

	std::wstring strFilepath = Util::ConvertToWString(_strDefaultPath);

	wchar_t cCanonPath[MAX_PATH];

	PathCanonicalize(cCanonPath, strFilepath.c_str());

	IShellItem* pDefaultFolder = NULL;

	hRes = SHCreateItemFromParsingName(cCanonPath, NULL, IID_PPV_ARGS(&pDefaultFolder));

	if (SUCCEEDED(hRes)) {
		pFileDialog->SetFolder(pDefaultFolder);
		pDefaultFolder->Release();
	}

	hRes = pFileDialog->Show(NULL);

	if (SUCCEEDED(hRes)) {
		_u8Type == 0 ? HandleOpenDialogSelection(static_cast<IFileOpenDialog*>(pFileDialog)) : HandleSaveDialogSelection(static_cast<IFileSaveDialog*>(pFileDialog));
	}

	pFileDialog->Unadvise(dwCookie);

	pDialogEvents->Release();

	pFileDialog->Release();

	return true;
}

std::vector<std::string> PlatformFileDialog::GetUserSelections() {
	return m_vUserSelections;
}
