#pragma once

#include <HellfireControl/Core/Common.hpp>

enum DialogType : uint8_t {
	FILE_DIALOG_OPEN,
	FILE_DIALOG_SAVE
};

class FileDialog {
public:
	FileDialog();

	FileDialog(DialogType _dtType, const std::vector<std::string>& _vAllowedExtensions, const std::string& _strDefaultPath);

	std::vector<std::string> GetUserSelections() const;
};