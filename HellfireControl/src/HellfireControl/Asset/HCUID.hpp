#pragma once

#include <HellfireControl/Core/Common.hpp>

class File;

class HCUID {
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

	friend std::ostream& operator<<(std::ostream& _sStream, const HCUID& _gID);

	friend bool operator<(const HCUID& _gLeft, const HCUID& _gRight);
public:
	HCUID();

	HCUID(const HCUID& _gOther) = default;

	HCUID& operator=(const HCUID& _gOther) = default;

	HCUID(HCUID&& _gOther) = default;

	HCUID& operator=(HCUID&& _gOther) = default;

	bool operator==(const HCUID& _gOther) const;

	bool operator!=(const HCUID& _gOther) const;

	operator std::string() const;

	static HCUID ConstructRandom();

	static HCUID ConstructFromFilepath(const std::string& _strFilepath);

	static HCUID ConstructFromGUIDString(const std::string& _strGUID);

	std::string AsString() const;

	bool IsValid() const;
};