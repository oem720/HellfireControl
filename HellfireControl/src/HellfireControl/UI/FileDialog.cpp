
#include <HellfireControl/UI/FileDialog.hpp>

#define HC_INCLUDE_FILE_DIALOG
#include <Platform/OSInclude.hpp>

FileDialog::FileDialog() {
	PlatformFileDialog::CreateFileDialog(FILE_DIALOG_OPEN, { "." }, "./");
}

FileDialog::FileDialog(DialogType _dtType, const std::vector<std::string>& _vAllowedExtensions, const std::string& _strDefaultPath) {
	PlatformFileDialog::CreateFileDialog(_dtType, _vAllowedExtensions, _strDefaultPath);
}

std::vector<std::string> FileDialog::GetUserSelections() const {
	return PlatformFileDialog::GetUserSelections();
}
