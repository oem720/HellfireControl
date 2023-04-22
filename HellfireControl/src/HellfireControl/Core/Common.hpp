#pragma once

//Basic Includes
#include <stdint.h>
#include <utility>
#include <cassert>

//Defines for quick rad/deg conversion
#define HC_PI 3.14159265358979323846f
#define HC_RAD2DEG(_val) ((_val) * 180.0f / HC_PI)
#define HC_DEG2RAD(_val) ((_val) * HC_PI / 180.0f)

//Defines for standardized declarations
#define HC_INLINE __forceinline
#define HC_VECTORCALL __vectorcall
#define HC_ALIGNAS(_val) alignas((_val))

//Defines for engine conditionals
#define HC_USE_SIMD 0
#define HC_ENABLE_DOUBLE_PRECISION 1