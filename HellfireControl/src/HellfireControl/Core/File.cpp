
#include <HellfireControl/Core/File.hpp>

#define HC_DELIMITER_WHITESPACE ' '
#define HC_DELIMITER_TAB '\t'
#define HC_DELIMITER_NEWLINE '\n'
#define HC_DELIMITER_STR_SEP '\"'

File::File(const std::string& _strFilename, uint8_t _fofFlags) {
	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	OpenFile(ResolveFileFlags());

	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) {
		ExtractFileBlob();
	}
}

File::~File(){
	if (IsOpen()) {
		Close();
	}
}

void File::ChangeOpenFile(const std::string& _strFilename, uint8_t _fofFlags) {
	Close();

	m_pthFilepath = _strFilename;

	m_fofFlags = _fofFlags;

	OpenFile(ResolveFileFlags());

	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) {
		ExtractFileBlob();
	}
}

void File::SignalStartOfStructure() {
	if (m_fofFlags & FILE_OPEN_FLAG_BINARY) {
		return; //Ignore the command when in binary mode.
	}

	for (int iCount = 0; iCount < m_u32ASCIIScopeCounter; ++iCount) {
		m_fStream << "\t"; //Add a tab for every scope currently active
	}

	m_u32ASCIIScopeCounter++; //Increment the scope counter
}

void File::SignalEndOfStructure() {
	if (m_fofFlags & FILE_OPEN_FLAG_BINARY || m_u32ASCIIScopeCounter == 0) {
		return; //Ignore the command when in binary mode or when there is no active scope.
	}

	m_fStream.seekg(-1, std::ios_base::cur); //Go back one character.

	m_fStream << "\n"; //Insert new line character

	m_u32ASCIIScopeCounter--; //Decrement the scope counter.
}

void File::Close() {
	m_fStream.close();

	m_pthFilepath = "";
	m_fofFlags = 0;
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

	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) { //Blobs require that no writing be enabled and that they must always begin at end.
		iOpenFlags &= ~(std::ios_base::out | std::ios_base::app);
		iOpenFlags |= (std::ios_base::in | std::ios_base::ate);

		m_fofFlags &= ~(FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_APPEND); //Thanks to implementaiton-defined values, this must be separate.
		m_fofFlags |= (FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BEGIN_AT_END);
	}

	return iOpenFlags;
}

void File::OpenFile(int _iFlags){
	m_fStream = std::fstream(m_pthFilepath, _iFlags);

	if (!m_fStream.is_open()) {
		throw std::runtime_error("ERROR: Failed to open file! Filepath: " + m_pthFilepath.string());
	}
}

void File::ExtractFileBlob() {
	size_t sFileSize = static_cast<size_t>(m_fStream.tellg());
	m_vDataBlob.resize(sFileSize);

	m_fStream.seekg(0);
	m_fStream.read(m_vDataBlob.data(), sFileSize);

	m_fStream.close();

	m_ptrBlobPointer = &m_vDataBlob[0];
}

std::string File::ParseLine(const std::function<const bool(char&)>& _funcCondition) {
	bool bDelimiterFound = false;
	bool bInQuotes = false;
	char cNext;

	std::string strOutput;

	while (_funcCondition(cNext) && !bDelimiterFound) {
		if (cNext == HC_DELIMITER_TAB && !bInQuotes) {
			continue;
		}

		if ((cNext == HC_DELIMITER_WHITESPACE || cNext == HC_DELIMITER_NEWLINE) && !bInQuotes) {
			bDelimiterFound = true;
			continue;
		}

		if (cNext == HC_DELIMITER_STR_SEP) {
			bInQuotes = !bInQuotes;
			continue;
		}

		strOutput.push_back(cNext);
	}

	return strOutput;
}

void File::ReadBinary(void* _ptrvDest, size_t _sNumBytes) {
	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) {
		if ((m_ptrBlobPointer + _sNumBytes < m_vDataBlob.end()._Ptr)) {
			std::cerr << "WARNING: Attempted to read past the file memory bounds!";
			return;
		}

		memcpy(_ptrvDest, m_ptrBlobPointer, _sNumBytes); //Memcpy from the blob.
		
		m_ptrBlobPointer += _sNumBytes; //Advance the read pointer
	}
	else {
		m_fStream.read(reinterpret_cast<char*>(_ptrvDest), _sNumBytes);
	}
}

void File::WriteBinary(const void* _ptrvSrc, size_t _sNumBytes) {
	m_fStream.write(reinterpret_cast<const char*>(_ptrvSrc), _sNumBytes);
}

void File::ReadASCII(std::string& _strDest) {
	std::function<const bool(char&)> funcCondition;

	if (m_fofFlags & FILE_OPEN_FLAG_BLOB) {
		funcCondition = [&](char& _cNext) -> const bool { return (_cNext = *m_ptrBlobPointer++, m_ptrBlobPointer != m_vDataBlob.end()._Ptr); };
	}
	else {		
		funcCondition = [&](char& _cNext) -> const bool {return (m_fStream.get(_cNext), !m_fStream.eof()); };
	}

	_strDest = ParseLine(funcCondition);
}

void File::WriteASCII(const std::string& _strVal) {
	m_fStream << _strVal << HC_DELIMITER_WHITESPACE;
}

File& operator<<(File& _fFile, const std::string& _strString) {
	if (_fFile.IsOpen() && _fFile.m_fofFlags & FILE_OPEN_FLAG_WRITE) {
		if (_fFile.m_fofFlags & FILE_OPEN_FLAG_BINARY) {
			_fFile << _strString.length(); //Write the length.

			_fFile.WriteBinary(_strString.data(), _strString.length());
		}
		else {
			_fFile.WriteASCII("\"" + _strString + "\""); //Surround in " to differentiate from other types.
		}
	}
	else {
		std::cerr << "WARNING! Attempted to write to a file that is unopened or does not have write privileges!\n";
	}

	return _fFile;
}

File& operator>>(File& _fFile, std::string& _strString) {
	if (_fFile.IsOpen() && _fFile.m_fofFlags & FILE_OPEN_FLAG_READ) {
		if (_fFile.m_fofFlags & FILE_OPEN_FLAG_BINARY) {
			_strString.clear(); //Reset string before processing

			size_t sLength = 0;
			_fFile >> sLength; //Read in the length

			_fFile.ReadBinary(_strString.data(), sLength);
		}
		else {
			_fFile.ReadASCII(_strString);

			_strString = _strString.substr(1, _strString.size() - 2); //Remove the surrounding quotation marks
		}
	}
	else {
		std::cerr << "WARNING! Attempted to read from a file that is unopened or does not have read privileges!\n";
	}

	return _fFile;
}
