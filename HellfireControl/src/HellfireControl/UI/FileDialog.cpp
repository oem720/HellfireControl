
#include <HellfireControl/UI/FileDialog.hpp>

#define HC_INCLUDE_FILE_DIALOG
#include <Platform/OSInclude.hpp>

FileDialog::FileDialog() {
	if (!PlatformFileDialog::CreateFileDialog(FILE_DIALOG_OPEN, ALL_SUPPORTED_FILE_FORMATS, "./")) {
		throw std::runtime_error("ERROR: Encountered a problem creating the file dialog!");
	}
}

FileDialog::FileDialog(DialogType _dtType, uint64_t _u64AllowedFileExtensions, const std::string& _strDefaultPath) {
	if (!PlatformFileDialog::CreateFileDialog(_dtType, _u64AllowedFileExtensions, _strDefaultPath)) {
		throw std::runtime_error("ERROR: Encountered a problem creating the file dialog!");
	}
}

std::vector<std::string> FileDialog::GetUserSelections() const {
	return PlatformFileDialog::GetUserSelections();
}
