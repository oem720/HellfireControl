#pragma once

//Basic Includes
#include <stdint.h>
#include <utility>
#include <cassert>
#include <iostream>
#include <stdexcept>

//Required Includes (will not be replaced)
#include <thread>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <functional>
#include <chrono>
#include <charconv>

//Borrowed from Vulkan docs
#define HC_CONVERT_TO_VERSION_NO(_variant, _major, _minor, _patch)  ((((uint64_t)(_variant)) << 29U) | (((uint64_t)(_major)) << 22U) | (((uint64_t)(_minor)) << 12U) | ((uint64_t)(_patch)))
//Engine Version No.
#define HC_ENGINE_VERSION HC_CONVERT_TO_VERSION_NO(1, 1, 0, 0)

//Defines for commonly used math functions
#define HC_PI 3.14159265358979323846f
#define HC_2PI 6.28318530717958647693f
#define HC_PI_HALF 1.57079632679489661923f
#define HC_EPSILON 1.19209e-07f
#define HC_NEAR_ONE 0.99995f
#define HC_RAD2DEG(_val) ((_val) * 180.0f / HC_PI)
#define HC_DEG2RAD(_val) ((_val) * HC_PI / 180.0f)
#define HC_FLOAT_COMPARE(_val1, _val2) fabsf(_val1 - _val2) < HC_EPSILON
#define HC_DOUBLE_COMPARE(_val1, _val2) fabs(_val1 - _val2) < HC_EPSILON

//Defines for standardized declarations
#define HC_INLINE inline
#define HC_VECTORCALL __vectorcall
#define HC_ALIGNAS(_val) alignas((_val))

//Defines for engine conditionals
#define HC_USE_SIMD 0
#define HC_ENABLE_DOUBLE_PRECISION 1
#define HC_USE_ROTOR 1

#define HC_USE_VULKAN 1
#define HC_USE_OPENGL 0

//Includes for STL library that will be replaced with custom implementations in the future
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <optional>
#include <set>
#include <limits>

//Generic Platform Handles
typedef uint64_t WindowHandleGeneric;

struct HC_ALIGNAS(128) BufferHandleGeneric {
	uint64_t upper;
	uint64_t lower;

	HC_INLINE bool operator==(const BufferHandleGeneric & _bhgOther) {
		return this->upper == _bhgOther.upper && this->lower == _bhgOther.lower;
	}
};