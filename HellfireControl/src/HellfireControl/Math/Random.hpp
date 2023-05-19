#pragma once

#include <HellfireControl/Core/Common.hpp>

class Random {
private:
	const static int s_iStateSize = 624;

	uint32_t m_uState[s_iStateSize];

	int m_iNext;

	uint32_t m_uSeed;
public:
	explicit Random(uint32_t _uSeed);

	[[nodiscard]] char GenerateChar(char _cMin, char _cMax);
	[[nodiscard]] short GenerateShort(short _sMin, short _sMax);
	[[nodiscard]] int GenerateInt(int _iMin, int _iMax);
	[[nodiscard]] uint32_t GenerateUnsignedInt(uint32_t _uMin, uint32_t _uMax);
	[[nodiscard]] long GenerateLong(long _lMin, long _lMax);
	[[nodiscard]] float GenerateFloat(float _fMin, float _fMax);
	[[nodiscard]] double GenerateDouble(double _dMin, double _dMax);

	[[nodiscard]] HC_INLINE uint32_t GetSeed() const { return m_uSeed; }
	void SetSeed(uint32_t _uSeed);

private:
	[[nodiscard]] uint32_t GetNextVal();

	void Regenerate();
};