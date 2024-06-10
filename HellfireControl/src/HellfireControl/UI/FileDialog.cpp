
#include <HellfireControl/UI/FileDialog.hpp>

#define HC_INCLUDE_FILE_DIALOG
#include <Platform/OSInclude.hpp>

void FileDialog::InitDialogBox(DialogType _dtType, uint64_t _u64AllowedFileExtensions, const std::string& _strDefaultPath) {
	if (!PlatformFileDialog::CreateFileDialog(_dtType, _u64AllowedFileExtensions, _strDefaultPath)) {
		throw std::runtime_error("ERROR: Encountered a problem creating the file dialog!");
	}
}

std::vector<std::string> FileDialog::GetUserSelections() const {
	return PlatformFileDialog::GetUserSelections();
}
