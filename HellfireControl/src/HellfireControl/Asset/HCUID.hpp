#pragma once

#include <HellfireControl/Core/Common.hpp>

class File;

class HCUID {
private:
	union {
		struct {
			uint64 upper;
			uint64 lower;
		};
		unsigned char m_arrBytes[16];
	};

	static uint8 HexDigitToChar(char _cDigit);

	static uint8 HexPairToChar(char _cLeft, char _cRight);

	static bool CheckValidHexChar(char _cDigit);

	friend std::ostream& operator<<(std::ostream& _sStream, const HCUID& _gID);

	friend bool operator<(const HCUID& _gLeft, const HCUID& _gRight);
public:
	HCUID();

	HCUID(const HCUID& _gOther) = default;

	HCUID& operator=(const HCUID& _gOther) = default;

	HCUID(HCUID&& _gOther) = default;

	HCUID& operator=(HCUID&& _gOther) = default;

	operator String() const;

	static HCUID ConstructRandom();

	static HCUID ConstructFromFilepath(const String& _strFilepath);

	static HCUID ConstructFromGUIDString(const String& _strGUID);

	String AsString() const;

	bool IsValid() const;
};