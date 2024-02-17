#pragma once

#include <HellfireControl/Core/Common.hpp>

/// <summary>
/// A random number generator that utilizes Mersenne Twister.
/// </summary>
class Random {
private:
	/// <summary>
	/// The current seed that was utilized to generate the state
	/// </summary>
	uint64_t m_uSeed;

	/// <summary>
	/// The size of the state of the machine. 624 by default for 32 bit MT
	/// </summary>
	const static int s_iStateSize = 624;

	/// <summary>
	/// The state of the machine. Generated every time the seed updates or the end is reached.
	/// </summary>
	uint64_t m_uState[s_iStateSize];

	/// <summary>
	/// The next value that will be used for number generation. Increments with every use.
	/// </summary>
	int m_iNext = 0;

public:
	/// <summary>
	/// Default constructor. Uses current system time at function call for seed.
	/// </summary>
	Random();

	/// <summary>
	/// Seeds the new generator with the input seed _uSeed. Value must be unsigned.
	/// </summary>
	/// <param name="_uSeed: The seed for the new generator"></param>
	explicit Random(uint64_t _uSeed);

	/// <summary>
	/// Generates a random char between _cMin and _cMax. Defaults to the full range of char.
	/// </summary>
	/// <param name="_cMin: Minimum possible generated value"></param>
	/// <param name="_cMax: Maximum possible generated value"></param>
	/// <returns>
	/// char: Randomly generated char
	/// </returns>
	[[nodiscard]] char GenerateChar(char _cMin, char _cMax);

	/// <summary>
	/// Generates a random short between _sMin and _sMax. Defaults to the full range of short.
	/// </summary>
	/// <param name="_sMin: Minimum possible generated value"></param>
	/// <param name="_sMax: Minimum possible generated value"></param>
	/// <returns>
	/// short: Randomly generated short
	/// </returns>
	[[nodiscard]] short GenerateShort(short _sMin, short _sMax);

	/// <summary>
	/// Generates a random int between _iMin and _iMax. Defaults to the full range of int.
	/// </summary>
	/// <param name="_iMin: Minimum possible generated value"></param>
	/// <param name="_iMax: Maximum possible generated value"></param>
	/// <returns>
	/// int: Randomly generated integer
	/// </returns>
	[[nodiscard]] int GenerateInt(int _iMin, int _iMax);

	/// <summary>
	/// Generates a random unsigned 32-bit int between _uMin and _uMax. Defaults to the full range of unsigned 32-bit integers.
	/// </summary>
	/// <param name="_uMin: Minimum possible generated value"></param>
	/// <param name="_uMax: Maximum possible generated value"></param>
	/// <returns>
	/// uint32_t: Randomly generated 32-bit integer
	/// </returns>
	[[nodiscard]] uint64_t GenerateUnsignedInt(uint64_t _uMin, uint64_t _uMax);

	/// <summary>
	/// Generates a random long between _lMin and _lMax. Defaults to the full range of long.
	/// </summary>
	/// <param name="_lMin: Minimum possible generated value"></param>
	/// <param name="_lMax: Maximum possible generated value"></param>
	/// <returns>
	/// long: Randomly generated long
	/// </returns>
	[[nodiscard]] int64_t GenerateLong(int64_t _lMin, int64_t _lMax);

	/// <summary>
	/// Generates a random float between _fMin and _fMax. Defaults to between 0 and 1.
	/// </summary>
	/// <param name="_fMin: Minimum possible generated value"></param>
	/// <param name="_fMax: Maximum possible generated value"></param>
	/// <returns>
	/// float: Randomly generated float
	/// </returns>
	[[nodiscard]] float GenerateFloat(float _fMin, float _fMax);

	/// <summary>
	/// Generates a random double between _dMin and _dMax. Defaults to between 0 and 1.
	/// </summary>
	/// <param name="_dMin: Minimum possible generated value"></param>
	/// <param name="_dMax: Maximum possible generated value"></param>
	/// <returns>
	/// double: Randomly generated double
	/// </returns>
	[[nodiscard]] double GenerateDouble(double _dMin, double _dMax);

	/// <summary>
	/// Returns the seed utilized in generated the current state.
	/// </summary>
	/// <returns>
	/// uint32_t: The seed used in generating the current state.
	/// </returns>
	[[nodiscard]] HC_INLINE uint64_t GetSeed() const { return m_uSeed; }

	/// <summary>
	/// Sets the seed and regenerates the random number generator.
	/// </summary>
	/// <param name="_uSeed: The new seed to utilize"></param>
	void SetSeed(uint64_t _uSeed);

private:
	/// <summary>
	/// Returns the next generated value.
	/// </summary>
	/// <returns>
	/// uint32_t: The newly generated value.
	/// </returns>
	[[nodiscard]] uint64_t GetNextVal();

	/// <summary>
	/// Resets the machine and regenerates the state register.
	/// </summary>
	void Regenerate();
};