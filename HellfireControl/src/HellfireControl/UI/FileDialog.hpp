#pragma once

#include <HellfireControl/Core/Common.hpp>

enum DialogType : uint8 {
	FILE_DIALOG_OPEN,
	FILE_DIALOG_SAVE
};

class FileDialog {
public:
	FileDialog() {}

	void InitDialogBox(DialogType _dtType, uint64 _u64AllowedFileExtensions, const String& _strDefaultPath);

	Array<String> GetUserSelections() const;
};