#pragma once

#pragma warning(disable : 6201)

#include <HellfireControl/Math/Random.hpp>
#include <HellfireControl/Math/Internal/Random/Random_Common.hpp>

Random::Random() {
	m_uSeed = (uint64_t)time(NULL);

	m_uState[0] = m_uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

Random::Random(uint64_t _uSeed) {
	m_uSeed = _uSeed;

	m_uState[0] = _uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

char Random::GenerateChar(char _cMin = 0, char _cMax = CHAR_MAX) {
	if (_cMax < _cMin) return GenerateChar(_cMax, _cMin);

	uint64_t u32Range = static_cast<uint64_t>(_cMax - _cMin + 1);

	return static_cast<char>(GetNextVal() % u32Range) + _cMin;
}

short Random::GenerateShort(short _sMin = 0, short _sMax = SHRT_MAX) {
	if (_sMax < _sMin) return GenerateShort(_sMax, _sMin);

	uint64_t u32Range = static_cast<uint64_t>(_sMax - _sMin + 1);

	return static_cast<short>(GetNextVal() % u32Range) + _sMin;
}

int Random::GenerateInt(int _iMin = 0, int _iMax = INT_MAX) {
	if (_iMax < _iMin) return GenerateInt(_iMax, _iMin);

	uint64_t u32Range = static_cast<uint64_t>(_iMax - _iMin + 1);

	return static_cast<int>(GetNextVal() % u32Range) + _iMin;
}

uint32_t Random::GenerateUnsignedInt(uint32_t _uMin = 0, uint32_t _uMax = UINT_MAX) {
	if (_uMax < _uMin) return GenerateUnsignedInt(_uMax, _uMin);

	uint32_t u32Range = _uMax - _uMin;
	
	return (GetNextVal() % u32Range) + _uMin;
}

int64_t Random::GenerateLong(int64_t _lMin = 0, int64_t _lMax = LLONG_MAX) {
	if (_lMax < _lMin) return GenerateLong(_lMax, _lMin);

	uint64_t u64Val = static_cast<uint64_t>((static_cast<uint64_t>(GetNextVal()) << 32) | GetNextVal()); //Fuse two generated numbers
	uint64_t u64Range = static_cast<uint64_t>(_lMax - _lMin + 1);

	return static_cast<int64_t>(u64Val % u64Range) + _lMin;
}

float Random::GenerateFloat(float _fMin = 0.0f, float _fMax = 1.0f) {
	if (_fMax < _fMin) return GenerateFloat(_fMax, _fMin);

	float fScale = static_cast<float>(INT_MAX) / (_fMax - _fMin);

	return (static_cast<float>(GenerateInt()) / fScale) + _fMin;
}

double Random::GenerateDouble(double _dMin = 0.0f, double _dMax = 1.0f) {
	if (_dMax < _dMin) return GenerateDouble(_dMax, _dMin);

	double dScale = static_cast<double>(LLONG_MAX) / (_dMax - _dMin);

	return (static_cast<double>(GenerateLong()) / dScale) + _dMin;
}

void Random::SetSeed(uint64_t _uSeed) {
	m_iNext = 0;

	m_uState[0] = _uSeed;

	for (int i = 1; i < s_iStateSize; i++) {
		m_uState[i] = 1812433253UL * (m_uState[i - 1] ^ (m_uState[i - 1] >> 30)) + i;
	}

	Regenerate();
}

uint64_t Random::GetNextVal() {
	if (m_iNext >= s_iStateSize) {
		m_iNext = 0;
		Regenerate();
	}

	uint64_t uVal = m_uState[m_iNext++];
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
	uint64_t uBits;
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
