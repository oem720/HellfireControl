#pragma once

#include <HellfireControl/Core/Common.hpp>

class File {
private:
	std::filesystem::path m_pthFilepath;

	std::fstream m_fStream;

	std::vector<uint8_t> m_vDataBlob;
public:
	File() = delete;

	File(const std::string& _strFilename);

	void Load();

	void Close();


};