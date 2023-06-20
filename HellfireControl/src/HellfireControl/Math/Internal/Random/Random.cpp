#pragma once

#include <HellfireControl/Math/Random.hpp>
#include <HellfireControl/Math/Internal/Random/Random_Common.hpp>

Random::Random() {
	m_uSeed = (uint32_t)time(NULL);

	m_uState[0] = m_uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

Random::Random(uint32_t _uSeed) {
	m_uSeed = _uSeed;

	m_uState[0] = _uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

char Random::GenerateChar(char _cMin = CHAR_MIN, char _cMax = CHAR_MAX) {
	if (_cMax < _cMin) return GenerateChar(_cMax, _cMin);

	char cVal = static_cast<char>(GetNextVal() >> 24); //Grab higher order bits
	char cRange = _cMax - _cMin + 1;

	return cVal % cRange + _cMin;
}

short Random::GenerateShort(short _sMin = SHRT_MIN, short _sMax = SHRT_MAX) {
	if (_sMax < _sMin) return GenerateShort(_sMax, _sMin);

	short sVal = static_cast<short>(GetNextVal() >> 16); //Grab higher order bits
	short sRange = _sMax - _sMin + 1;

	return sVal & sRange + _sMin;
}

int Random::GenerateInt(int _iMin = INT_MIN, int _iMax = INT_MAX) {
	if (_iMax < _iMin) return GenerateInt(_iMax, _iMin);

	int iVal = static_cast<int>(GetNextVal());
	int iRange = _iMax - _iMin + 1;

	return iVal % iRange + _iMin;
}

uint32_t Random::GenerateUnsignedInt(uint32_t _uMin = 0, uint32_t _uMax = UINT_MAX) {
	if (_uMax < _uMin) return GenerateUnsignedInt(_uMax, _uMin);

	uint32_t uVal = GetNextVal();
	uint32_t uRange = _uMax - _uMin + 1;
	
	return uVal % uRange + _uMin;
}

long Random::GenerateLong(long _lMin = LONG_MIN, long _lMax = LONG_MAX) {
	if (_lMax < _lMin) return GenerateLong(_lMax, _lMin);

	long lVal = static_cast<long>((static_cast<uint64_t>(GetNextVal()) << 32) | GetNextVal()); //Fuse two generated numbers
	long lRange = _lMax - _lMin + 1;

	return lVal % lRange + _lMin;
}

float Random::GenerateFloat(float _fMin = 0.0f, float _fMax = 1.0f) {
	if (_fMax < _fMin) return GenerateFloat(_fMax, _fMin);

	float fVal = static_cast<float>(GenerateInt());
	float fScale = static_cast<float>(INT_MAX) / (_fMax - _fMin);

	return (fVal / fScale) + _fMin;
}

double Random::GenerateDouble(double _dMin = 0.0f, double _dMax = 1.0f) {
	if (_dMax < _dMin) return GenerateDouble(_dMax, _dMin);

	double dVal = static_cast<double>(GenerateLong());
	double dScale = static_cast<double>(LONG_MAX) / (_dMax - _dMin);

	return (dVal / dScale) + _dMin;
}

void Random::SetSeed(uint32_t _uSeed) {
	m_iNext = 0;

	m_uState[0] = _uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

uint32_t Random::GetNextVal() {
	if (m_iNext >= s_iStateSize) {
		m_iNext = 0;
		Regenerate();
	}

	uint32_t uVal = m_uState[m_iNext++];
	uVal ^= uVal >> 11;
	uVal ^= (uVal << 7) & 0x9d2c5680;
	uVal ^= (uVal << 15) & 0xefc60000;
	uVal ^= uVal >> 18;

	return uVal;
}

void Random::Regenerate() {
	const int iM = 397;
	const int iFirstHalf = s_iStateSize - iM;

	int iNdx = 0;
	uint32_t uBits;
	for (; iNdx < iFirstHalf; ++iNdx) {
		uBits = (m_uState[iNdx] & 0x80000000) | (m_uState[iNdx + 1] & 0x7fffffff);
		m_uState[iNdx] = m_uState[iNdx + iM] ^ (uBits >> 1) ^ ((uBits & 1) * 0x9908b0df);
	}

	for (; iNdx < s_iStateSize - 1; ++iNdx) {
		uBits = (m_uState[iNdx] & 0x80000000) | (m_uState[iNdx + 1] & 0x7fffffff);
		m_uState[iNdx] = m_uState[iNdx - iFirstHalf] ^ (uBits >> 1) ^ ((uBits & 1) * 0x9908b0df);
	}

	uBits = (m_uState[iNdx] & 0x80000000) | (m_uState[0] & 0x7fffffff);
	m_uState[iNdx] = m_uState[iM - 1] ^ (uBits >> 1) ^ ((uBits & 1) * 0x9908b0df);
}
