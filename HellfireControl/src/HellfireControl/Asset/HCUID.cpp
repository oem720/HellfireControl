
#include <HellfireControl/Asset/HCUID.hpp>

#include <HellfireControl/Core/File.hpp>

//Hash numbers
constexpr uint64 HC_HASH_PRIME_P = 0xE4BB93D3DF4F7A61U;
constexpr uint64 HC_HASH_PRIME_Q = 0xB98DEDA5D48BCBC7U;
constexpr uint64 HC_HASH_PRIME_R = 0xCB53E93F9CD22179U;

uint64 HashLong(uint64 _u64Value) {
	return (_u64Value * HC_HASH_PRIME_P) + (_u64Value * HC_HASH_PRIME_Q);
}

uint64 HashString(const String& _strValue) {
	uint64 u64Hash = 0;

	for (int ndx = 0; ndx < _strValue.size(); ++ndx) {
		u64Hash ^= ((ndx & 1) ? -1 : 1) * (static_cast<uint64>(_strValue[ndx]) * HC_HASH_PRIME_P) + (static_cast<uint64>(_strValue[ndx]) * HC_HASH_PRIME_Q);
	}

	return u64Hash;
}

HCUID::HCUID() {
	upper = 0;
	lower = 0;
}

HCUID::operator String() const {
	return AsString();
}

HCUID HCUID::ConstructRandom() {
	HCUID gId;

	uint64 u64Time = static_cast<uint64>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

	gId.upper = HashLong(u64Time) ^ HC_HASH_PRIME_R;
	gId.lower = HashLong(gId.upper);

	return gId;
}

HCUID HCUID::ConstructFromFilepath(const String& _strFilepath) {
	HCUID gId;

	gId.upper = HashString(_strFilepath);
	gId.lower = HashLong(gId.upper);

	return gId;
}

HCUID HCUID::ConstructFromGUIDString(const String& _strGUID) {
	HCUID gId;

	uint32 u32NextByte = 0;

	for (int leftNdx = 0, rightNdx = 1; rightNdx < _strGUID.length(); leftNdx += 2, rightNdx += 2) {
		if (_strGUID[leftNdx] == '-') {
			leftNdx++;
			rightNdx++; //If we hit a -, nudge one character
		}

		if (u32NextByte >= 16 || !CheckValidHexChar(_strGUID[leftNdx]) || !CheckValidHexChar(_strGUID[rightNdx])) {
			std::cerr << "WARNING: Attempted to parse bad HCUID!\n";

			gId.upper = 0;
			gId.lower = 0;

			return gId;
		}

		gId.m_arrBytes[u32NextByte++] = HexPairToChar(_strGUID[leftNdx], _strGUID[rightNdx]);
	}

	if (u32NextByte < 16) {
		std::cerr << "WARNING: Attempted to parse bad HCUID!\n";

		gId.upper = 0;
		gId.lower = 0;
	}

	return gId;
}

String HCUID::AsString() const {
	std::stringstream ssString;

	ssString << *this;

	return ssString.str();
}

bool HCUID::IsValid() const {
	return (upper > 0 && lower > 0) && (lower == HashLong(upper));
}

uint8 HCUID::HexDigitToChar(char _cDigit) {
	if (_cDigit > 47 && _cDigit < 58) {
		return _cDigit - 48;
	}

	if (_cDigit > 64 && _cDigit < 71) {
		return _cDigit - 55;
	}


	if (_cDigit > 96 && _cDigit < 103) {
		return _cDigit - 87;
	}

	return 0;
}

uint8 HCUID::HexPairToChar(char _cLeft, char _cRight) {
	return HexDigitToChar(_cLeft) * 16 + HexDigitToChar(_cRight);
}

bool HCUID::CheckValidHexChar(char _cDigit) {
	return (_cDigit > 47 && _cDigit < 58) ||
		(_cDigit > 64 && _cDigit < 71) ||
		(_cDigit > 96 && _cDigit < 103);
}

std::ostream& operator<<(std::ostream& _sStream, const HCUID& _gID) {
	std::ios_base::fmtflags fFormat(_sStream.flags());

	_sStream << std::hex << std::setfill('0');

	for (int ndx = 0; ndx < 16; ++ndx) {
		_sStream << std::setw(2) << static_cast<int>(_gID.m_arrBytes[ndx]);

		if (ndx % 2 == 1 && ndx != 15) {
			_sStream << "-";
		}
	}

	_sStream.flags(fFormat);

	return _sStream;
}

bool operator<(const HCUID& _gLeft, const HCUID& _gRight) {
	return _gLeft.upper < _gRight.upper;
}