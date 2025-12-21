#pragma once

//Basic Includes
#include <stdint.h>
#include <utility>
#include <cassert>
#include <iostream>
#include <stdexcept>

//Required Includes (will not be replaced)
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <functional>
#include <chrono>
#include <charconv>
#include <variant>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

//Borrowed from Vulkan docs
#define HC_CONVERT_TO_VERSION_NO(_variant, _major, _minor, _patch)  ((((uint64)(_variant)) << 29U) | (((uint64)(_major)) << 22U) | (((uint64)(_minor)) << 12U) | ((uint64)(_patch)))
//Engine Version No.
#define HC_ENGINE_VERSION HC_CONVERT_TO_VERSION_NO(1, 1, 0, 0)
//File Format Version No.
#define HC_FILE_FORMAT_VERSION_NUMBER(major, minor) (static_cast<uint16>((major)) << 8) | static_cast<uint16>((minor))
//Engine ref tag
#define HC_CREATE_32BIT_TAG(char1, char2, char3, char4) (static_cast<uint32>(char4) << 24) | (static_cast<uint32>(char3) << 16) | (static_cast<uint32>(char2) << 8) | static_cast<uint32>(char1)

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
#define HC_MAX(_val1, _val2) (_val1 > _val2) ? _val1 : _val2
#define HC_MIN(_val1, _val2) (_val1 < _val2) ? _val1 : _val2

//SFINAE
#define HC_SFINAE_REQUIRE_NUMERIC(_typename) typename = typename std::enable_if<std::disjunction<std::is_integral<_typename>, std::is_floating_point<_typename>>::value>::type
#define HC_SFINAE_REQUIRE_INTEGER(_typename) typename = typename std::enable_if<std::is_integral<_typename>::value>::type
#define HC_SFINAE_REQUIRE_FLOATING_POINT(_typename) typename = typename std::enable_if<std::is_floating_point<_typename>::value>::type

//Defines for standardized declarations
#define HC_INLINE inline
#define HC_VECTORCALL __vectorcall
#define HC_ALIGNAS(_val) alignas((_val))

//Engine Level Defines
#define HC_USE_SIMD 0
#define HC_ENABLE_DOUBLE_PRECISION 1
#define HC_USE_ROTOR 1
#define HC_EDITOR 1
#define HC_ABSOLUTE_THREAD_MAX 100

#define HC_USE_VULKAN 1
#define HC_USE_OPENGL 0

//Includes for STL library that will be replaced with custom implementations in the future
#include <string>
#include <vector>
#include <array>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <span>
#include <optional>
#include <map>
#include <unordered_map>
#include <limits>

//Aliasing for types that will be replaced with custom implementation.
typedef std::string String;
template<typename T> using Array = std::vector<T>;
template<typename T, size_t S> using FixedArray = std::array<T, S>;
template<typename T> using List = std::list<T>;
template<typename T> using Queue = std::queue<T>;
template<typename T> using DoubleEndedQueue = std::deque<T>;
template<typename T> using Set = std::set<T>;
template<typename T> using Optional = std::optional<T>;
template<typename T> using Span = std::span<T>;
template<typename K, typename V> using Map = std::map<K, V>;
template<typename K, typename V> using UnorderedMap = std::unordered_map<K, V>;

//Aliasing for types that will not be replaced, or may be replaced in the far future.
typedef std::thread Thread;
typedef std::mutex Mutex;
typedef std::condition_variable ConditionVariable;
typedef std::filesystem::path FilePath;
typedef std::fstream FileStream;
template<typename T> using Function = std::function<T>;
template<typename T, class D = std::default_delete<T>> using UniquePointer = std::unique_ptr<T, D>;
template<typename T> using SharedPointer = std::shared_ptr<T>;
template<typename T> using WeakPointer = std::weak_ptr<T>;

typedef uint32 UTF8PaddedChar;

//Generic Platform Handles
typedef uint64 WindowHandleGeneric;

//TODO: Move all enums to their own file!
enum DialogAllowedFileTypes : uint64 {
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