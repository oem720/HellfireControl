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

#define HC_SFINAE_REQUIRE_NUMERIC(_typename) typename = typename std::enable_if<std::disjunction<std::is_integral<_typename>, std::is_floating_point<_typename>>::value>::type
#define HC_SFINAE_REQUIRE_INTEGER(_typename) typename = typename std::enable_if<std::is_integral<_typename>::value>::type
#define HC_SFINAE_REQUIRE_FLOATING_POINT(_typename) typename = typename std::enable_if<std::is_floating_point<_typename>::value>::type

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

//TODO Move all enums to their own file!
enum DialogAllowedFileTypes : uint64_t {
	JPEG = 0x1,
	PNG = 0x2,
	GIF = 0x4,
	BMP = 0x8,
	ALL_IMAGE_FORMATS = 0xF,
	OBJ = 0x10,
	FBX = 0x20,
	GLTF = 0x40,
	ALL_MODEL_FORMATS = 0x70, //TODO: Numbering will change when Hellfire Assets are inserted!
	DDS = 0x80,
	KTX = 0x100,
	MTL = 0x200,
	ALL_TEXTURE_FORMATS = 0x380,
	WAV = 0x400,
	MP3 = 0x800,
	OGG = 0x1000,
	ALL_AUDIO_FORMATS = 0x1C00,
	MP4 = 0x2000,
	MOV = 0x4000,
	AVI = 0x8000,
	WMV = 0x10000,
	ALL_VIDEO_FORMATS = 0x1E000,
	TTF = 0x20000,
	/*TODO: Insert Hellfire Formats Here!*/
	//ALL_HELLFIRE_FORMATS,
	ALL_SUPPORTED_FILE_FORMATS = 0xFFFFFFFFFFFFFFFF
};