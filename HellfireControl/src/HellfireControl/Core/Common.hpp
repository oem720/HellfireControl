#pragma once

//Basic Includes
#include <stdint.h>
#include <utility>
#include <cassert>

//Defines for commonly used math functions
#define HC_PI 3.14159265358979323846f
#define HC_EPSILON 1.19209e-07
#define HC_RAD2DEG(_val) ((_val) * 180.0f / HC_PI)
#define HC_DEG2RAD(_val) ((_val) * HC_PI / 180.0f)
#define HC_FLOAT_COMPARE(_val1, _val2) fabsf(_val1 - _val2) < HC_EPSILON
#define HC_DOUBLE_COMPARE(_val1, _val2) fabs(_val1 - _val2) < HC_EPSILON

//Defines for standardized declarations
#define HC_INLINE __forceinline
#define HC_VECTORCALL __vectorcall
#define HC_ALIGNAS(_val) alignas((_val))

//Defines for engine conditionals
#define HC_USE_SIMD 0
#define HC_ENABLE_DOUBLE_PRECISION 1
#define HC_USE_ROTOR 0