#pragma once

//Includes for SIMD operation
#include <stdint.h>
#include <utility>
#include <math.h>
#include <immintrin.h>
#include <cassert>

//Defines for quick rad/deg conversion
#define HC_PI 3.14159265358979323846f
#define HC_RAD2DEG(_val) ((_val) * 180.0f / HC_PI)
#define HC_DEG2RAD(_val) ((_val) * HC_PI / 180.0f)

//Defines for standardized function declaration
#define HC_INLINE __forceinline