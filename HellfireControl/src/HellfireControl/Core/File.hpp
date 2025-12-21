#pragma once

#include <HellfireControl/Core/Common.hpp>

enum FileOpenFlag : uint8 {
	FILE_OPEN_FLAG_ASCII = 1U,
	FILE_OPEN_FLAG_BINARY = 2U,
	FILE_OPEN_FLAG_READ = 4U,
	FILE_OPEN_FLAG_WRITE = 8U,
	FILE_OPEN_FLAG_APPEND = 16U,
	FILE_OPEN_FLAG_BEGIN_AT_END = 32U,
	FILE_OPEN_FLAG_DEFAULT = FILE_OPEN_FLAG_ASCII | FILE_OPEN_FLAG_READ,
	FILE_OPEN_FLAG_BLOB = FILE_OPEN_FLAG_BINARY | FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BEGIN_AT_END
};

enum FileDelimiter : char {
	FILE_DELIMITER_NULL_TERMINATOR = '\0',
	FILE_DELIMITER_SPACE = ' ',
	FILE_DELIMITER_NEWLINE = '\n',
	FILE_DELIMITER_TAB = '\t',
	FILE_DELIMITER_COMMA = ',',
	FILE_DELIMITER_SEMICOLON = ';',
	FILE_DELIMITER_QUOTE = '\"'
};

class File {
private:
	FilePath m_pthFilepath;

	FileStream m_fStream;

	uint8 m_fofFlags = FILE_OPEN_FLAG_DEFAULT;

	bool m_bNewFile = false;

	int ResolveFileFlags();

	void OpenFile(int _iFlags);

	template<typename T, HC_SFINAE_REQUIRE_NUMERIC(T)>
	HC_INLINE void ConvertToNumericValue(const String& _strVal, T& _output) {
		auto [ptr, error] = std::from_chars(_strVal.data(), _strVal.data() + _strVal.size(), _output);

		if (error != std::errc{}) {
			throw std::runtime_error("ERROR: Failed to convert from string to numeric type!");
		}
	}

	HC_INLINE void ConvertToNumericValue(const String& _strVal, bool& _output) {
		int iIntermediate;

		auto [ptr, error] = std::from_chars(_strVal.data(), _strVal.data() + _strVal.size(), iIntermediate);

		_output = static_cast<bool>(iIntermediate);

		if (error != std::errc{}) {
			throw std::runtime_error("ERROR: Failed to convert from string to numeric type!");
		}
	}

public:
	File() {}

	File(const String& _strFilename, uint8 _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	~File();

	void ChangeOpenFile(const String& _strFilename, uint8 _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	void Close();

	[[nodiscard]] HC_INLINE String GetFileExtension() const { return m_pthFilepath.extension().string(); }

	[[nodiscard]] HC_INLINE String GetFileName() const { return m_pthFilepath.filename().string(); }

	[[nodiscard]] HC_INLINE bool IsNewlyCreated() const { return m_bNewFile; }

	[[nodiscard]] HC_INLINE bool IsOpen() const { return m_fStream.is_open(); }

	[[nodiscard]] HC_INLINE bool AtEOF() const { return m_fStream.eof(); }

	[[nodiscard]] HC_INLINE bool IsBinary() const { return m_fofFlags & FILE_OPEN_FLAG_BINARY; }

	[[nodiscard]] HC_INLINE size_t ReaderLocation() { return static_cast<size_t>(m_fStream.tellg()); }

	[[nodiscard]] Array<uint8> ExtractFileBlob();

	void AdvanceBytes(int64 _i64Distance);

	void GoToByte(size_t _sLocation);

	HC_INLINE void GoToStart() { GoToByte(0); }

	void Write(const void* _pData, size_t _sBytes);

	void Read(void* _pData, size_t _sBytes);

	void WriteLine(const void* _pData, size_t _sBytes, FileDelimiter _fdDelim);
	
	void ReadLine(void* _pData, size_t _sBytes, FileDelimiter _fdDelim);

	void WriteLine(const String& _strData, FileDelimiter _fdDelim);

	void ReadLine(String& _strData, FileDelimiter _fdDelim);
};