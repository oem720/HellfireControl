#pragma once

#include <HellfireControl/Core/Common.hpp>

enum FileOpenFlag : uint8_t {
	FILE_OPEN_FLAG_ASCII = 1U,
	FILE_OPEN_FLAG_BINARY = 2U,
	FILE_OPEN_FLAG_READ = 4U,
	FILE_OPEN_FLAG_WRITE = 8U,
	FILE_OPEN_FLAG_BLOB = 16U,
	FILE_OPEN_FLAG_APPEND = 32U,
	FILE_OPEN_FLAG_BEGIN_AT_END = 64U,
	FILE_OPEN_FLAG_DEFAULT = 45U
};

class File {
private:
	std::filesystem::path m_pthFilepath;

	std::fstream m_fStream;

	std::vector<char> m_vDataBlob;

	char* m_ptrBlobPointer = nullptr;

	uint8_t m_fofFlags = FILE_OPEN_FLAG_DEFAULT;

	uint32_t m_u32ASCIIScopeCounter = 0U;

	int ResolveFileFlags();

	void OpenFile(int _iFlags);

	void ExtractFileBlob();

	std::string ParseLine(const std::function<const bool(char&)>& _funcCondition);

	void ReadBinary(void* _ptrvDest, size_t _sNumBytes);

	void WriteBinary(const void* _ptrvSrc, size_t _sNumBytes);

	void ReadASCII(std::string& _strDest);

	void WriteASCII(const std::string& _strVal);

	template<typename T, HC_SFINAE_REQUIRE_NUMERIC(T)>
	HC_INLINE void ConvertToNumericValue(const std::string& _strVal, T& _output) {
		auto [ptr, error] = std::from_chars(_strVal.data(), _strVal.data() + _strVal.size(), _output);

		if (error != std::errc{}) {
			throw std::runtime_error("ERROR: Failed to convert from string to numeric type!");
		}
	}

	HC_INLINE void ConvertToNumericValue(const std::string& _strVal, bool& _output) {
		int iIntermediate;

		auto [ptr, error] = std::from_chars(_strVal.data(), _strVal.data() + _strVal.size(), iIntermediate);

		_output = static_cast<bool>(iIntermediate);

		if (error != std::errc{}) {
			throw std::runtime_error("ERROR: Failed to convert from string to numeric type!");
		}
	}

public:
	File() = delete;

	File(const std::string& _strFilename, uint8_t _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	~File();

	void ChangeOpenFile(const std::string& _strFilename, uint8_t _fofFlags = FILE_OPEN_FLAG_DEFAULT);

	void SignalStartOfStructure();

	void SignalEndOfStructure();

	void Close();

	[[nodiscard]] HC_INLINE std::string GetFileExtension() const { return m_pthFilepath.extension().string(); }

	[[nodiscard]] HC_INLINE std::string GetFileName() const { return m_pthFilepath.filename().string(); }

	[[nodiscard]] HC_INLINE const std::vector<char>& GetFileBlob() { return m_vDataBlob; }

	[[nodiscard]] HC_INLINE bool IsOpen() const { return m_fStream.is_open() || m_ptrBlobPointer; }

	[[nodiscard]] HC_INLINE bool AtEOF() const { return m_fStream.eof() || m_ptrBlobPointer == m_vDataBlob.end()._Ptr; }

	[[nodiscard]] HC_INLINE bool IsBinary() const { return m_fofFlags & FILE_OPEN_FLAG_BINARY; }

	[[nodiscard]] HC_INLINE size_t ReaderLocation() { return m_fofFlags & FILE_OPEN_FLAG_BLOB ? static_cast<size_t>(m_ptrBlobPointer - &m_vDataBlob[0]) : static_cast<size_t>(m_fStream.tellg()); }

	void AdvanceBytes(int64_t _i64Distance);

	void GoToByte(size_t _sLocation);
};