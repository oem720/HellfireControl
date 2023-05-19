#pragma once

#include <HellfireControl/Math/Random.hpp>
#include <HellfireControl/Math/Internal/Random/Random_Common.hpp>

Random::Random() {

}

explicit Random::Random(unsigned _uSeed) {

}

char Random::GenerateChar(char _cMin = CHAR_MIN, char _cMax = CHAR_MAX) {
	return 0;
}

short Random::GenerateShort(short _sMin = SHRT_MIN, short _sMax = SHRT_MAX) {
	return 0;
}

int Random::GenerateInt(int _iMin = INT_MIN, int _iMax = INT_MAX) {
	return 0;
}

unsigned Random::GenerateUnsignedInt(unsigned _uMin = 0, unsigned _uMax = UINT_MAX) {
	return 0;
}

long Random::GenerateLong(long _lMin = LONG_MIN, long _lMax = LONG_MAX) {
	return 0;
}

float Random::GenerateFloat(float _fMin = 0.0f, float _fMax = 1.0f) {
	return 0.0f;
}

double Random::GenerateDouble(double _dMin = 0.0f, double _dMax = 1.0f) {
	return 0.0;
}

HC_INLINE unsigned Random::GetSeed() const {
	return 0;
}

void Random::SetSeed(unsigned _uSeed) {

}