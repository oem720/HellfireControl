#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Util/SerializableObject.hpp>

#define HC_SFINAE_REQUIRE_NUMERIC typename std::enable_if<std::disjunction<std::is_integral<T>, std::is_floating_point<T>>::value>::type

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

	template<typename T, typename = HC_SFINAE_REQUIRE_NUMERIC>
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

	[[nodiscard]] HC_INLINE std::vector<char> GetFileBlob() const { return m_vDataBlob; }

	[[nodiscard]] HC_INLINE bool IsOpen() const { return m_fStream.is_open() || m_ptrBlobPointer; }

	[[nodiscard]] HC_INLINE bool AtEOF() const { return m_fStream.eof() || m_ptrBlobPointer == m_vDataBlob.end()._Ptr; }

	[[nodiscard]] HC_INLINE bool IsBinary() const { return m_fofFlags & FILE_OPEN_FLAG_BINARY; }

public:
	template <typename T, typename = HC_SFINAE_REQUIRE_NUMERIC>
	HC_INLINE File& operator<<(const T _val) {
		if (IsOpen() && m_fofFlags & FILE_OPEN_FLAG_WRITE) {
			(m_fofFlags & FILE_OPEN_FLAG_BINARY) ? WriteBinary(&_val, sizeof(T)) : WriteASCII(std::to_string(_val));
		}
		else {
			std::cerr << "WARNING! Attempted to write to a file that is unopened or does not have write privileges!\n";
		}

		return *this;
	}

	template <typename T, typename = HC_SFINAE_REQUIRE_NUMERIC>
	HC_INLINE File& operator>>(T _val) {
		if (IsOpen() && m_fofFlags & FILE_OPEN_FLAG_READ) {
			if (m_fofFlags & FILE_OPEN_FLAG_BINARY) {
				ReadBinary(&_val, sizeof(T))
			}
			else {
				std::string strVal;

				ReadASCII(strVal);

				ConvertToNumericValue(strVal, _val);
			}
		}
		else{
			std::cerr << "WARNING! Attempted to read from a file that is unopened or does not have read privileges!\n";
		}

		return *this;
	}

	template<typename T>
	HC_INLINE File& operator<<(const std::vector<T>& _vVector) {
		if (IsOpen() && m_fofFlags & FILE_OPEN_FLAG_WRITE) {
			SignalStartOfStructure();

			//Vector length followed by data must be written
			*this << _vVector.size();

			SignalEndOfStructure();

			//Data written individually to take advantage of serializer function for object.
			for (int ndx = 0; ndx < _vVector.size(); ++ndx) {
				*this << _vVector[ndx];
			}
		}
		else {
			std::cerr << "WARNING! Attempted to write to a file that is unopened or does not have write privileges!\n";
		}

		return *this;
	}

	template<typename T>
	HC_INLINE File& operator>>(std::vector<T>& _vVector) {
		if (IsOpen() && m_fofFlags & FILE_OPEN_FLAG_READ) {
			_vVector.clear(); //Clear the vector to ensure no data is carried over.

			int iSize = 0;
			*this >> iSize; //Read the size

			_vVector.resize(iSize); //Resize our vector to allocate the memory needed.

			//Leverage Deserialize function to read in the data.
			for (int ndx = 0; ndx < _vVector.size(); ++ndx) {
				*this >> _vVector[ndx];
			}
		}
		else {
			std::cerr << "WARNING! Attempted to read from a file that is unopened or does not have read privileges!\n";
		}

		return *this;
	}

	friend File& operator<<(File& _fFile, const std::string& _strString);
	friend File& operator>>(File& _fFile, std::string& _strString);
};
