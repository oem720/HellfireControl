
#include <HellfireControl/Core/File.hpp>

File::File(const std::string& _strFilename, uint8_t _fofFlags) {
	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	OpenFile(ResolveFileFlags());
}

File::~File() {
	if (IsOpen()) {
		Close();
	}
}

void File::ChangeOpenFile(const std::string& _strFilename, uint8_t _fofFlags) {
	Close();

	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	OpenFile(ResolveFileFlags());
}

void File::Close() {
	m_fStream.close();

	m_pthFilepath = "";
	m_fofFlags = 0;
}

void File::GoToByte(size_t _sLocation){	
	if (m_fStream.fail()) {
		//TODO: more robust error handling.
		m_fStream.clear();
	}

	m_fStream.seekg(_sLocation);
}

void File::Write(const void* _pData, size_t _sBytes) {
	m_fStream.write(reinterpret_cast<const char*>(_pData), _sBytes);
}

void File::Read(void* _pData, size_t _sBytes) {
	m_fStream.read(reinterpret_cast<char*>(_pData), _sBytes);
}

void File::WriteLine(const void* _pData, size_t _sBytes, FileDelimiter _fdDelim) {
	if (_fdDelim == FILE_DELIMITER_QUOTE) {
		m_fStream << _fdDelim; //Put a quote at the front as well, denotes a string in text files.
	}

	m_fStream.write(reinterpret_cast<const char*>(_pData), _sBytes);

	m_fStream << _fdDelim;
}

void File::ReadLine(void* _pData, size_t _sBytes, FileDelimiter _fdDelim) {
	std::string dataBuffer;

	std::getline(m_fStream, dataBuffer, static_cast<char>(_fdDelim));

	memcpy_s(_pData, _sBytes, dataBuffer.c_str(), dataBuffer.size());
}

void File::AdvanceBytes(int64_t _i64Distance) {
	if (m_fStream.fail()) {
		//TODO: more robust error handling.
		m_fStream.clear();
	}

	m_fStream.seekg(m_fStream.tellg() + _i64Distance);
}

int File::ResolveFileFlags() {
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

	if (m_fofFlags & FILE_OPEN_FLAG_BEGIN_AT_END) {
		iOpenFlags |= std::ios_base::ate;
	}

	return iOpenFlags;
}

void File::OpenFile(int _iFlags) {
	m_fStream = std::fstream(m_pthFilepath, _iFlags);

	if (!m_fStream.is_open()) {
		throw std::runtime_error("ERROR: Failed to open file! Filepath: " + m_pthFilepath.string());
	}

	//TODO: more robust error handling.
	m_fStream.exceptions(std::ios_base::badbit);
}

std::vector<uint8_t> File::ExtractFileBlob() {
	std::vector<uint8_t> vBlob;

	size_t sFileSize = static_cast<size_t>(m_fStream.tellg());
	vBlob.resize(sFileSize);

	m_fStream.seekg(0);
	m_fStream.read(reinterpret_cast<char*>(vBlob.data()), sFileSize);

	m_fStream.close();

	return vBlob;
}