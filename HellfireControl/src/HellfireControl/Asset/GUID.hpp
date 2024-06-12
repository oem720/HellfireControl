#pragma once

#include <HellfireControl/Core/Common.hpp>

class File;

class GUID {
private:
	union {
		struct {
			uint64_t upper;
			uint64_t lower;
		};
		unsigned char m_arrBytes[16];
	};

	static uint8_t HexDigitToChar(char _cDigit);

	static uint8_t HexPairToChar(char _cLeft, char _cRight);

	static bool CheckValidHexChar(char _cDigit);

	friend std::ostream& operator<<(std::ostream& _sStream, const GUID& _gID);

	friend File& operator<<(File& _fFile, const GUID& _gID);
	friend File& operator>>(File& _fFile, GUID& _gID);

	friend bool operator<(const GUID& _gLeft, const GUID& _gRight);
public:
	GUID();

	GUID(const GUID& _gOther) = default;

	GUID& operator=(const GUID& _gOther) = default;

	GUID(GUID&& _gOther) = default;

	GUID& operator=(GUID&& _gOther) = default;

	bool operator==(const GUID& _gOther) const;

	bool operator!=(const GUID& _gOther) const;

	operator std::string() const;

	static GUID ConstructRandom();

	static GUID ConstructFromFilepath(const std::string& _strFilepath);

	static GUID ConstructFromGUIDString(const std::string& _strGUID);

	std::string AsString() const;

	bool IsValid() const;
};