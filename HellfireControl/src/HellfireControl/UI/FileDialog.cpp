
#include <HellfireControl/UI/FileDialog.hpp>

#define HC_INCLUDE_FILE_DIALOG
#include <Platform/OSInclude.hpp>

void FileDialog::InitDialogBox(DialogType _dtType, uint64 _u64AllowedFileExtensions, const String& _strDefaultPath) {
	if (!PlatformFileDialog::CreateFileDialog(_dtType, _u64AllowedFileExtensions, _strDefaultPath)) {
		throw std::runtime_error("ERROR: Encountered a problem creating the file dialog!");
	}
}

Array<String> FileDialog::GetUserSelections() const {
	return PlatformFileDialog::GetUserSelections();
}
