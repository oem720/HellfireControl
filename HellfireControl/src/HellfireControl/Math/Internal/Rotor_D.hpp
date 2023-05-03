#pragma once

#include <HellfireControl/Math/Internal/Rotor_Common.hpp>

#if HC_USE_SIMD

struct RotorD {
	//TODO: Implement SIMD (requires new SIMD backend)
};

#else

struct HC_ALIGNAS(32) RotorD {

};

#endif