
#include <HellfireControl/Core/File.hpp>

File::File(const std::string& _strFilename, FileOpenFlag _fofFlags) {
	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	ResolveFileFlags();
}

void File::ChangeOpenFile(const std::string& _strFilename, FileOpenFlag _fofFlags) {
	Close();

	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	ResolveFileFlags();
}

void File::Close() {
	m_fStream.close();

	m_pthFilepath = "";
	m_fofFlags = 0;
}

void File::ResolveFileFlags() {
	int iOpenFlags = 0;

	if (m_fofFlags & FILE_OPEN_FLAG_BINARY) {
		iOpenFlags |= std::ios_base::binary;
	}

	if (m_fofFlags & FILE_OPEN_FLAG_READ) {
		iOpenFlags |= std::ios_base::in;
	}

	if (m_fofFlags & FILE_OPEN_FLAG_WRITE) {
		iOpenFlags |= std::ios_base::out;
	}

	if (m_fofFlags & FILE_OPEN_FLAG_APPEND) {
		iOpenFlags |= std::ios_base::app;
	}

	m_fStream = std::fstream(m_pthFilepath, iOpenFlags);

	if (!m_fStream.is_open()) {
		throw std::runtime_error("ERROR: Failed to open file! Filepath: " + m_pthFilepath.string());
	}

	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) {
		ExtractFileBlob();
	}
}

void File::ExtractFileBlob() {
	size_t sFileSize = static_cast<size_t>(m_fStream.tellg());
	m_vDataBlob.resize(sFileSize);

	m_fStream.seekg(0);
	m_fStream.read(m_vDataBlob.data(), sFileSize);

	if (!(m_fofFlags & FILE_OPEN_FLAG_WRITE)) {
		m_fStream.close();
	}
}