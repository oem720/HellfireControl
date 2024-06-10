#pragma once

#include <HellfireControl/Core/Common.hpp>

enum DialogType : uint8_t {
	FILE_DIALOG_OPEN,
	FILE_DIALOG_SAVE
};

class FileDialog {
public:
	FileDialog() {}

	void InitDialogBox(DialogType _dtType, uint64_t _u64AllowedFileExtensions, const std::string& _strDefaultPath);

	std::vector<std::string> GetUserSelections() const;
};