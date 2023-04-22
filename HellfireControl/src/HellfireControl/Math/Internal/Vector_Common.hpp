#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <math.h>

#if HC_USE_SIMD
#include <intrin.h>

typedef struct {
	union {
		uint32_t m_iInts[4];
		__m128 m_fVec;
	};
} maskf_t;

typedef struct {
	union {
		uint64_t m_iInts[4];
		__m256d m_dVec;
	};
} maskd_t;

HC_INLINE maskf_t SignBitMaskF() {
	static maskf_t g_mMask = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
	return g_mMask;
}

HC_INLINE maskd_t SignBitMaskD() {
	static maskd_t g_mMask = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000, 0x8000000000000000 };
	return g_mMask;
}
#endif