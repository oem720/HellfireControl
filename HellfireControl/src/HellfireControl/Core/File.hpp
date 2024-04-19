#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/SerializableObject.hpp>

enum FileOpenFlag : uint8_t {
	FILE_OPEN_FLAG_ASCII = 1U,
	FILE_OPEN_FLAG_BINARY = 2U,
	FILE_OPEN_FLAG_READ = 4U,
	FILE_OPEN_FLAG_WRITE = 8U,
	FILE_OPEN_FLAG_BLOB = 16U,
	FILE_OPEN_FLAG_APPEND = 32U,
	FILE_OPEN_FLAG_DEFAULT = 45U
};

class File {
private:
	std::filesystem::path m_pthFilepath;

	std::fstream m_fStream;

	std::vector<char> m_vDataBlob;

	uint8_t m_fofFlags = FILE_OPEN_FLAG_DEFAULT;

	void ResolveFileFlags();

	void ExtractFileBlob();
public:
	File() = delete;

	File(const std::string& _strFilename, FileOpenFlag _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	void ChangeOpenFile(const std::string& _strFilename, FileOpenFlag _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	void Close();

	std::string GetFileExtension() const { return m_pthFilepath.extension().generic_string(); }

	std::string GetFileName() const { return m_pthFilepath.filename().generic_string(); }
};
