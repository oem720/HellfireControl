#pragma once

#include <HellfireControl/Core/Common.hpp>

class Random {
private:

public:
	Random();
	explicit Random(unsigned _uSeed);

	[[nodiscard]] char GenerateChar(char _cMin, char _cMax);
	[[nodiscard]] short GenerateShort(short _sMin, short _sMax);
	[[nodiscard]] int GenerateInt(int _iMin, int _iMax);
	[[nodiscard]] unsigned GenerateUnsignedInt(unsigned _uMin, unsigned _uMax);
	[[nodiscard]] long GenerateLong(long _lMin, long _lMax);
	[[nodiscard]] float GenerateFloat(float _fMin, float _fMax);
	[[nodiscard]] double GenerateDouble(double _dMin, double _dMax);

	[[nodiscard]] HC_INLINE unsigned GetSeed() const;
	void SetSeed(unsigned _uSeed);
};