
#include <HellfireControl/Asset/GUID.hpp>

#include <HellfireControl/Core/File.hpp>

//Hash numbers
constexpr uint64_t HC_HASH_PRIME_P = 0xE4BB93D3DF4F7A61U;
constexpr uint64_t HC_HASH_PRIME_Q = 0xB98DEDA5D48BCBC7U;
constexpr uint64_t HC_HASH_PRIME_R = 0xCB53E93F9CD22179U;

uint64_t HashLong(uint64_t _u64Value) {
	return (_u64Value * HC_HASH_PRIME_P) + (_u64Value * HC_HASH_PRIME_Q);
}

uint64_t HashString(const std::string& _strValue) {
	uint64_t u64Hash = 0;

	for (int ndx = 0; ndx < _strValue.size(); ++ndx) {
		u64Hash ^= ((ndx & 1) ? -1 : 1) * (static_cast<uint64_t>(_strValue[ndx]) * HC_HASH_PRIME_P) + (static_cast<uint64_t>(_strValue[ndx]) * HC_HASH_PRIME_Q);
	}

	return u64Hash;
}

GUID::GUID() {
	upper = 0;
	lower = 0;
}

bool GUID::operator==(const GUID& _gOther) const {
	return upper == _gOther.upper && lower == _gOther.lower;
}

bool GUID::operator!=(const GUID& _gOther) const {
	return upper != _gOther.upper || lower != _gOther.lower;
}

GUID::operator std::string() const {
	return AsString();
}

GUID GUID::ConstructRandom() {
	GUID gId;

	uint64_t u64Time = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

	gId.upper = HashLong(u64Time) ^ HC_HASH_PRIME_R;
	gId.lower = HashLong(gId.upper);

	return gId;
}

GUID GUID::ConstructFromFilepath(const std::string& _strFilepath) {
	GUID gId;

	gId.upper = HashString(_strFilepath);
	gId.lower = HashLong(gId.upper);

	return gId;
}

GUID GUID::ConstructFromGUIDString(const std::string& _strGUID) {
	GUID gId;

	uint32_t u32NextByte = 0;

	for (int leftNdx = 0, rightNdx = 1; rightNdx < _strGUID.length(); leftNdx += 2, rightNdx += 2) {
		if (_strGUID[leftNdx] == '-') {
			leftNdx++;
			rightNdx++; //If we hit a -, nudge one character
		}

		if (u32NextByte >= 16 || !CheckValidHexChar(_strGUID[leftNdx]) || !CheckValidHexChar(_strGUID[leftNdx])) {
			std::cerr << "WARNING: Attempted to parse bad GUID!\n";

			gId.upper = 0;
			gId.lower = 0;

			return gId;
		}

		gId.m_arrBytes[u32NextByte++] = HexPairToChar(_strGUID[leftNdx], _strGUID[rightNdx]);
	}

	if (u32NextByte < 16) {
		std::cerr << "WARNING: Attempted to parse bad GUID!\n";

		gId.upper = 0;
		gId.lower = 0;
	}

	return gId;
}

std::string GUID::AsString() const {
	std::stringstream ssString;

	ssString << *this;

	return ssString.str();
}

bool GUID::IsValid() const {
	return (upper > 0 && lower > 0) && (lower == HashLong(upper));
}

uint8_t GUID::HexDigitToChar(char _cDigit) {
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

uint8_t GUID::HexPairToChar(char _cLeft, char _cRight) {
	return HexDigitToChar(_cLeft) * 16 + HexDigitToChar(_cRight);
}

bool GUID::CheckValidHexChar(char _cDigit) {
	return (_cDigit > 47 && _cDigit < 58) ||
		   (_cDigit > 64 && _cDigit < 71) ||
		   (_cDigit > 96 && _cDigit < 103);
}

std::ostream& operator<<(std::ostream& _sStream, const GUID& _gID) {
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

File& operator<<(File& _fFile, const GUID& _gID) {
	_fFile.SignalStartOfStructure();

	//Disgusting hack to get GUIDs to print as a string.
	if (_fFile.IsBinary()) {
		_fFile << _gID.AsString();
	}
	else {
		_fFile << _gID.upper;
		_fFile << _gID.lower;
	}

	_fFile.SignalEndOfStructure();

	return _fFile;
}

File& operator>>(File& _fFile, GUID& _gID) {

	if (_fFile.IsBinary()) {
		_fFile >> _gID.upper;
		_fFile >> _gID.lower;
	}
	else {
		std::string strGUID;

		_fFile >> strGUID;

		_gID = GUID::ConstructFromGUIDString(strGUID);
	}

	return _fFile;
}

bool operator<(const GUID& _gLeft, const GUID& _gRight) {
	return _gLeft.upper < _gRight.upper && _gLeft.lower < _gRight.lower;
}
