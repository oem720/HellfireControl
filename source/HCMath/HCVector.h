#pragma once
#ifndef VECTOR_LIBRARY_HEADER
#define VECTOR_LIBRARY_HEADER

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
#define HC_MATHFUNCTION(_type) __forceinline _type __vectorcall

#define HC_SHUFFLE2F(_vec, _x, _y) Vec2(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3F(_vec, _x, _y, _z) Vec3(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4F(_vec, _x, _y, _z, _w) Vec4(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))

#define HC_SHUFFLE2D(_vec, _x, _y)
#define HC_SHUFFLE3D(_vec, _x, _y, _z) 
#define HC_SHUFFLE4D(_vec, _x, _y, _z, _w)

#define HC_SHUFFLE2I(_vec, _x, _y)
#define HC_SHUFFLE3I(_vec, _x, _y, _z)
#define HC_SHUFFLE4I(_vec, _x, _y, _z, _w)

#pragma region VectorHelperTypedefs

typedef struct {
	union {
		uint32_t m_iInts[4];
		__m128 m_fVec;
	};
} mask_t;

HC_INLINE mask_t SignBitMask() {
	static mask_t g_gmMask = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
	return g_gmMask;
}

#pragma endregion

#pragma region FloatingPointVectors

struct Vec2 {
	__m128 m_fVec;

	HC_INLINE Vec2() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE Vec2(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE Vec2(float _fX, float _fY) { m_fVec = _mm_set_ps(_fY, _fY, _fY, _fX); }
	HC_INLINE Vec2(int _iX, int _iY) { m_fVec = _mm_set_ps(static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE Vec2(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE Vec2(Vec2&& _vOther) noexcept { (*this) = std::move(_vOther); }
	HC_INLINE Vec2(const Vec2& _vOther) { (*this) = _vOther; }
	HC_MATHFUNCTION(Vec2&) operator=(const Vec2& _vOther) { if (this != &_vOther) { this->m_fVec = _vOther.m_fVec; } return *this; }
	HC_MATHFUNCTION(Vec2&) operator=(Vec2&& _vOther) noexcept { if (this != &_vOther) { this->m_fVec = std::move(_vOther.m_fVec); } return *this; }
	HC_MATHFUNCTION(Vec2&) operator+=(const Vec2 _vOther) { *this = *this + _vOther; return *this; }
	HC_MATHFUNCTION(Vec2&) operator-=(const Vec2 _vOther) { *this = *this - _vOther; return *this; }
	HC_MATHFUNCTION(Vec2&) operator*=(const Vec2 _vOther) { *this = *this * _vOther; return *this; }
	HC_MATHFUNCTION(Vec2&) operator*=(const float _fScale) { *this = *this * _fScale; return *this; }
	HC_MATHFUNCTION(Vec2&) operator/=(const float _fScale) { *this = *this / _fScale; return *this; }
	HC_MATHFUNCTION(float) operator[](int _iNdx) const { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }
	HC_MATHFUNCTION(float&) operator[](int _iNdx) { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }	
	HC_MATHFUNCTION(float&) X() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) Y() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float) X() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(float&) R() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) G() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float) R() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(Vec2) XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_MATHFUNCTION(Vec2) YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_MATHFUNCTION(Vec2) YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_MATHFUNCTION(Vec2) RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_MATHFUNCTION(Vec2) GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_MATHFUNCTION(Vec2) GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
};

struct Vec3 {
	__m128 m_fVec;

	HC_INLINE Vec3() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE Vec3(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE Vec3(float _fX, float _fY, float _fZ) { m_fVec = _mm_set_ps(_fZ, _fZ, _fY, _fX); }
	HC_INLINE Vec3(int _iX, int _iY, int _iZ) { m_fVec = _mm_set_ps(static_cast<float>(_iZ), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE Vec3(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE Vec3(Vec3&& _vOther) noexcept { (*this) = std::move(_vOther); }
	HC_INLINE Vec3(const Vec3& _vOther) { (*this) = _vOther; }
	HC_MATHFUNCTION(Vec3&) operator=(Vec3&& _vOther) noexcept { if (this != &_vOther) { this->m_fVec = std::move(_vOther.m_fVec); } return *this; }
	HC_MATHFUNCTION(Vec3&) operator=(const Vec3& _vOther) { if (this != &_vOther) { this->m_fVec = _vOther.m_fVec; } return *this; }
	HC_MATHFUNCTION(Vec3&) operator+=(const Vec3 _vOther) { *this = *this + _vOther; return *this; }
	HC_MATHFUNCTION(Vec3&) operator-=(const Vec3 _vOther) { *this = *this - _vOther; return *this; }
	HC_MATHFUNCTION(Vec3&) operator*=(const Vec3 _vOther) { *this = *this * _vOther; return *this; }
	HC_MATHFUNCTION(Vec3&) operator*=(const float _fScale) { *this = *this * _fScale; return *this; }
	HC_MATHFUNCTION(Vec3&) operator/=(const float _fScale) { *this = *this / _fScale; return *this; }
	HC_MATHFUNCTION(float) operator[](int _iNdx) const { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_MATHFUNCTION(float&) operator[](int _iNdx) { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_MATHFUNCTION(float&) X() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) Y() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float&) Z() { return m_fVec.m128_f32[2]; }
	HC_MATHFUNCTION(float) X() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(float) Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_MATHFUNCTION(float&) R() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) G() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float&) B() { return m_fVec.m128_f32[2]; }
	HC_MATHFUNCTION(float) R() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(float) B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_MATHFUNCTION(Vec2) XX() const { return Vec2(HC_SHUFFLE2F(*this, 0, 0)); }
	HC_MATHFUNCTION(Vec2) YY() const { return Vec2(HC_SHUFFLE2F(*this, 1, 1)); }
	HC_MATHFUNCTION(Vec2) ZZ() const { return Vec2(HC_SHUFFLE2F(*this, 2, 2)); }
	HC_MATHFUNCTION(Vec2) XY() const { return Vec2(HC_SHUFFLE2F(*this, 0, 1)); }
	HC_MATHFUNCTION(Vec2) XZ() const { return Vec2(HC_SHUFFLE2F(*this, 0, 2)); }
	HC_MATHFUNCTION(Vec2) YX() const { return Vec2(HC_SHUFFLE2F(*this, 1, 0)); }
	HC_MATHFUNCTION(Vec2) YZ() const { return Vec2(HC_SHUFFLE2F(*this, 1, 2)); }
	HC_MATHFUNCTION(Vec2) ZX() const { return Vec2(HC_SHUFFLE2F(*this, 2, 0)); }
	HC_MATHFUNCTION(Vec2) ZY() const { return Vec2(HC_SHUFFLE2F(*this, 2, 1)); }
	HC_MATHFUNCTION(Vec2) RR() const { return Vec2(HC_SHUFFLE2F(*this, 0, 0)); }
	HC_MATHFUNCTION(Vec2) GG() const { return Vec2(HC_SHUFFLE2F(*this, 1, 1)); }
	HC_MATHFUNCTION(Vec2) BB() const { return Vec2(HC_SHUFFLE2F(*this, 2, 2)); }
	HC_MATHFUNCTION(Vec2) RG() const { return Vec2(HC_SHUFFLE2F(*this, 0, 1)); }
	HC_MATHFUNCTION(Vec2) RB() const { return Vec2(HC_SHUFFLE2F(*this, 0, 2)); }
	HC_MATHFUNCTION(Vec2) GR() const { return Vec2(HC_SHUFFLE2F(*this, 1, 0)); }
	HC_MATHFUNCTION(Vec2) GB() const { return Vec2(HC_SHUFFLE2F(*this, 1, 2)); }
	HC_MATHFUNCTION(Vec2) BR() const { return Vec2(HC_SHUFFLE2F(*this, 2, 0)); }
	HC_MATHFUNCTION(Vec2) BG() const { return Vec2(HC_SHUFFLE2F(*this, 2, 1)); }
	HC_MATHFUNCTION(Vec3) XXX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec3) XXY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec3) XXZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec3) XYX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec3) XYY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec3) XZX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec3) XZY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec3) XZZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec3) YXX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec3) YXY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec3) YXZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec3) YYX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec3) YYY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec3) YYZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec3) YZX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec3) YZY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec3) YZZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec3) ZXX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec3) ZXY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec3) ZXZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec3) ZYX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec3) ZYY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec3) ZYZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec3) ZZX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec3) ZZY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec3) ZZZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec3) RRR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec3) RRG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec3) RRB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec3) RGR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec3) RGG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec3) RBR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec3) RBG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec3) RBB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec3) GRR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec3) GRG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec3) GRB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec3) GGR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec3) GGG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec3) GGB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec3) GBR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec3) GBG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec3) GBB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec3) BRR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec3) BRG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec3) BRB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec3) BGR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec3) BGG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec3) BGB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec3) BBR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec3) BBG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec3) BBB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 2)); }
};

struct Vec4 {
	__m128 m_fVec;

	HC_INLINE Vec4() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE Vec4(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE Vec4(float _fX, float _fY, float _fZ, float _fW) { m_fVec = _mm_set_ps(_fW, _fZ, _fY, _fX); }
	HC_INLINE Vec4(int _iX, int _iY, int _iZ, int _iW) { m_fVec = _mm_set_ps(static_cast<float>(_iW), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iZ)); }
	HC_INLINE Vec4(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE Vec4(Vec4&& _vOther) noexcept { (*this) = std::move(_vOther); }
	HC_INLINE Vec4(const Vec4& _vOther) { (*this) = _vOther; }
	HC_MATHFUNCTION(Vec4&) operator=(Vec4&& _vOther) noexcept { if (this != &_vOther) { m_fVec = std::move(_vOther.m_fVec); } return *this; }
	HC_MATHFUNCTION(Vec4&) operator=(const Vec4& _vOther) { if (this != &_vOther) { m_fVec = _vOther.m_fVec; } return *this; }
	HC_MATHFUNCTION(Vec4&) operator+=(const Vec4 _vOther) { *this = *this + _vOther; return *this; }
	HC_MATHFUNCTION(Vec4&) operator-=(const Vec4 _vOther) { *this = *this - _vOther; return *this; }
	HC_MATHFUNCTION(Vec4&) operator*=(const Vec4 _vOther) { *this = *this * _vOther; return *this; }
	HC_MATHFUNCTION(Vec4&) operator*=(const float _fScale) { *this = *this * _fScale; return *this; }
	HC_MATHFUNCTION(Vec4&) operator/=(const float _fScale) { *this = *this / _fScale; return *this; }
	HC_MATHFUNCTION(float) operator[](int _iNdx) const { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_MATHFUNCTION(float&) operator[](int _iNdx) { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_MATHFUNCTION(float&) X() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) Y() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float&) Z() { return m_fVec.m128_f32[2]; }
	HC_MATHFUNCTION(float&) W() { return m_fVec.m128_f32[3]; }
	HC_MATHFUNCTION(float) X() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(float) Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_MATHFUNCTION(float) W() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_MATHFUNCTION(float&) R() { return m_fVec.m128_f32[0]; }
	HC_MATHFUNCTION(float&) G() { return m_fVec.m128_f32[1]; }
	HC_MATHFUNCTION(float&) B() { return m_fVec.m128_f32[2]; }
	HC_MATHFUNCTION(float&) A() { return m_fVec.m128_f32[3]; }
	HC_MATHFUNCTION(float) R() const { return _mm_cvtss_f32(m_fVec); }
	HC_MATHFUNCTION(float) G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_MATHFUNCTION(float) B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_MATHFUNCTION(float) A() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_MATHFUNCTION(Vec2) XX() const { return Vec2(HC_SHUFFLE2F(*this, 0, 0)); }
	HC_MATHFUNCTION(Vec2) YY() const { return Vec2(HC_SHUFFLE2F(*this, 1, 1)); }
	HC_MATHFUNCTION(Vec2) ZZ() const { return Vec2(HC_SHUFFLE2F(*this, 2, 2)); }
	HC_MATHFUNCTION(Vec2) WW() const { return Vec2(HC_SHUFFLE2F(*this, 3, 3)); }
	HC_MATHFUNCTION(Vec2) XY() const { return Vec2(HC_SHUFFLE2F(*this, 0, 1)); }
	HC_MATHFUNCTION(Vec2) XZ() const { return Vec2(HC_SHUFFLE2F(*this, 0, 2)); }
	HC_MATHFUNCTION(Vec2) XW() const { return Vec2(HC_SHUFFLE2F(*this, 0, 3)); }
	HC_MATHFUNCTION(Vec2) YX() const { return Vec2(HC_SHUFFLE2F(*this, 1, 0)); }
	HC_MATHFUNCTION(Vec2) YZ() const { return Vec2(HC_SHUFFLE2F(*this, 1, 2)); }
	HC_MATHFUNCTION(Vec2) YW() const { return Vec2(HC_SHUFFLE2F(*this, 1, 3)); }
	HC_MATHFUNCTION(Vec2) ZX() const { return Vec2(HC_SHUFFLE2F(*this, 2, 0)); }
	HC_MATHFUNCTION(Vec2) ZY() const { return Vec2(HC_SHUFFLE2F(*this, 2, 1)); }
	HC_MATHFUNCTION(Vec2) ZW() const { return Vec2(HC_SHUFFLE2F(*this, 2, 3)); }
	HC_MATHFUNCTION(Vec2) WX() const { return Vec2(HC_SHUFFLE2F(*this, 3, 0)); }
	HC_MATHFUNCTION(Vec2) WY() const { return Vec2(HC_SHUFFLE2F(*this, 3, 1)); }
	HC_MATHFUNCTION(Vec2) WZ() const { return Vec2(HC_SHUFFLE2F(*this, 3, 2)); }
	HC_MATHFUNCTION(Vec2) RR() const { return Vec2(HC_SHUFFLE2F(*this, 0, 0)); }
	HC_MATHFUNCTION(Vec2) GG() const { return Vec2(HC_SHUFFLE2F(*this, 1, 1)); }
	HC_MATHFUNCTION(Vec2) BB() const { return Vec2(HC_SHUFFLE2F(*this, 2, 2)); }
	HC_MATHFUNCTION(Vec2) AA() const { return Vec2(HC_SHUFFLE2F(*this, 3, 3)); }
	HC_MATHFUNCTION(Vec2) RG() const { return Vec2(HC_SHUFFLE2F(*this, 0, 1)); }
	HC_MATHFUNCTION(Vec2) RB() const { return Vec2(HC_SHUFFLE2F(*this, 0, 2)); }
	HC_MATHFUNCTION(Vec2) RA() const { return Vec2(HC_SHUFFLE2F(*this, 0, 3)); }
	HC_MATHFUNCTION(Vec2) GR() const { return Vec2(HC_SHUFFLE2F(*this, 1, 0)); }
	HC_MATHFUNCTION(Vec2) GB() const { return Vec2(HC_SHUFFLE2F(*this, 1, 2)); }
	HC_MATHFUNCTION(Vec2) GA() const { return Vec2(HC_SHUFFLE2F(*this, 1, 3)); }
	HC_MATHFUNCTION(Vec2) BR() const { return Vec2(HC_SHUFFLE2F(*this, 2, 0)); }
	HC_MATHFUNCTION(Vec2) BG() const { return Vec2(HC_SHUFFLE2F(*this, 2, 1)); }
	HC_MATHFUNCTION(Vec2) BA() const { return Vec2(HC_SHUFFLE2F(*this, 2, 3)); }
	HC_MATHFUNCTION(Vec2) AR() const { return Vec2(HC_SHUFFLE2F(*this, 3, 0)); }
	HC_MATHFUNCTION(Vec2) AG() const { return Vec2(HC_SHUFFLE2F(*this, 3, 1)); }
	HC_MATHFUNCTION(Vec2) AB() const { return Vec2(HC_SHUFFLE2F(*this, 3, 2)); }
	HC_MATHFUNCTION(Vec3) XXX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec3) XXY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec3) XXZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec3) XXW() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec3) XYX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec3) XYY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec3) XYZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec3) XYW() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec3) XZX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec3) XZY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec3) XZZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec3) XZW() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec3) XWX() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec3) XWY() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec3) XWZ() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec3) XWW() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec3) YXX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec3) YXY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec3) YXZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec3) YXW() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec3) YYX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec3) YYY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec3) YYZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec3) YYW() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec3) YZX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec3) YZY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec3) YZZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec3) YZW() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec3) YWX() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec3) YWY() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec3) YWZ() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec3) YWW() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec3) ZXX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec3) ZXY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec3) ZXZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec3) ZXW() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec3) ZYX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec3) ZYY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec3) ZYZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec3) ZYW() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec3) ZZX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec3) ZZY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec3) ZZZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec3) ZZW() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec3) ZWX() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec3) ZWY() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec3) ZWZ() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec3) ZWW() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec3) WXX() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec3) WXY() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec3) WXZ() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec3) WXW() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec3) WYX() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec3) WYY() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec3) WYZ() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec3) WYW() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec3) WZX() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec3) WZY() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec3) WZZ() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec3) WZW() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec3) WWX() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec3) WWY() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec3) WWZ() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec3) WWW() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec3) RRR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec3) RRG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec3) RRB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec3) RRA() const { return Vec3(HC_SHUFFLE3F(*this, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec3) RGR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec3) RGG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec3) RGA() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec3) RGB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec3) RBR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec3) RBG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec3) RBB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec3) RBA() const { return Vec3(HC_SHUFFLE3F(*this, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec3) RAR() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec3) RAG() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec3) RAB() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec3) RAA() const { return Vec3(HC_SHUFFLE3F(*this, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec3) GRR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec3) GRG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec3) GRB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec3) GRA() const { return Vec3(HC_SHUFFLE3F(*this, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec3) GGR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec3) GGG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec3) GGB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec3) GGA() const { return Vec3(HC_SHUFFLE3F(*this, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec3) GBR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec3) GBG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec3) GBB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec3) GBA() const { return Vec3(HC_SHUFFLE3F(*this, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec3) GAR() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec3) GAG() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec3) GAB() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec3) GAA() const { return Vec3(HC_SHUFFLE3F(*this, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec3) BRR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec3) BRG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec3) BRB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec3) BRA() const { return Vec3(HC_SHUFFLE3F(*this, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec3) BGR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec3) BGG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec3) BGB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec3) BGA() const { return Vec3(HC_SHUFFLE3F(*this, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec3) BBR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec3) BBG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec3) BBB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec3) BBA() const { return Vec3(HC_SHUFFLE3F(*this, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec3) BAR() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec3) BAG() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec3) BAB() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec3) BAA() const { return Vec3(HC_SHUFFLE3F(*this, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec3) ARR() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec3) ARG() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec3) ARB() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec3) ARA() const { return Vec3(HC_SHUFFLE3F(*this, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec3) AGR() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec3) AGG() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec3) AGB() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec3) AGA() const { return Vec3(HC_SHUFFLE3F(*this, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec3) ABR() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec3) ABG() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec3) ABB() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec3) ABA() const { return Vec3(HC_SHUFFLE3F(*this, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec3) AAR() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec3) AAG() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec3) AAB() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec3) AAA() const { return Vec3(HC_SHUFFLE3F(*this, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) XXXX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) XXXY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) XXXZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) XXXW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) XXYX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) XXYY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) XXYZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) XXYW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) XXZX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) XXZY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) XXZZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) XXZW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) XXWX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) XXWY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) XXWZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) XXWW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) XYXX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) XYXY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) XYXZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) XYXW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) XYYX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) XYYY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) XYYZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) XYYW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) XYZX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) XYZY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) XYZZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) XYWX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) XYWY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) XYWZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) XYWW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) XZXX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) XZXY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) XZXZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) XZXW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) XZYX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) XZYY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) XZYZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) XZYW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) XZZX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) XZZY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) XZZZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) XZZW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) XZWX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) XZWY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) XZWZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) XZWW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) XWXX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) XWXY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) XWXZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) XWXW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) XWYX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) XWYY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) XWYZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) XWYW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) XWZX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) XWZY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) XWZZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) XWZW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) XWWX() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) XWWY() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) XWWZ() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) XWWW() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) YXXX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) YXXY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) YXXZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) YXXW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) YXYX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) YXYY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) YXYZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) YXYW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) YXZX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) YXZY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) YXZZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) YXZW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) YXWX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) YXWY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) YXWZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) YXWW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) YYXX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) YYXY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) YYXZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) YYXW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) YYYX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) YYYY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) YYYZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) YYYW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) YYZX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) YYZY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) YYZZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) YYZW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) YYWX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) YYWY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) YYWZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) YYWW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) YZXX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) YZXY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) YZXZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) YZXW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) YZYX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) YZYY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) YZYZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) YZYW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) YZZX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) YZZY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) YZZZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) YZZW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) YZWX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) YZWY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) YZWZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) YZWW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) YWXX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) YWXY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) YWXZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) YWXW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) YWYX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) YWYY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) YWYZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) YWYW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) YWZX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) YWZY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) YWZZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) YWZW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) YWWX() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) YWWY() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) YWWZ() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) YWWW() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ZXXX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ZXXY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ZXXZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ZXXW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ZXYX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ZXYY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ZXYZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ZXYW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ZXZX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ZXZY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ZXZZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ZXZW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ZXWX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ZXWY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ZXWZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ZXWW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ZYXX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ZYXY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ZYXZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ZYXW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ZYYX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ZYYY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ZYYZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ZYYW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ZYZX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ZYZY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ZYZZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ZYZW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ZYWX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ZYWY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ZYWZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ZYWW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ZZXX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ZZXY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ZZXZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ZZXW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ZZYX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ZZYY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ZZYZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ZZYW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ZZZX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ZZZY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ZZZZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ZZZW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ZZWX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ZZWY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ZZWZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ZZWW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ZWXX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ZWXY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ZWXZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ZWXW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ZWYX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ZWYY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ZWYZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ZWYW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ZWZX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ZWZY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ZWZZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ZWZW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ZWWX() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ZWWY() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ZWWZ() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ZWWW() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) WXXX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) WXXY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) WXXZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) WXXW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) WXYX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) WXYY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) WXYZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) WXYW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) WXZX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) WXZY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) WXZZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) WXZW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) WXWX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) WXWY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) WXWZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) WXWW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) WYXX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) WYXY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) WYXZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) WYXW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) WYYX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) WYYY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) WYYZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) WYYW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) WYZX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) WYZY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) WYZZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) WYZW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) WYWX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) WYWY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) WYWZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) WYWW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) WZXX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) WZXY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) WZXZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) WZXW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) WZYX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) WZYY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) WZYZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) WZYW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) WZZX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) WZZY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) WZZZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) WZZW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) WZWX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) WZWY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) WZWZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) WZWW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) WWXX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) WWXY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) WWXZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) WWXW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) WWYX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) WWYY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) WWYZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) WWYW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) WWZX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) WWZY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) WWZZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) WWZW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) WWWX() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) WWWY() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) WWWZ() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) WWWW() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) RRRR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) RRRG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) RRRB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) RRRA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) RRGR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) RRGG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) RRGB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) RRGA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) RRBR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) RRBG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) RRBB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) RRBA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) RRAR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) RRAG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) RRAB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) RRAA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) RGRR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) RGRG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) RGRB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) RGRA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) RGGR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) RGGG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) RGGB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) RGGA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) RGBR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) RGBG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) RGBB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) RGAR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) RGAG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) RGAB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) RGAA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) RBRR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) RBRG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) RBRB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) RBRA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) RBGR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) RBGG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) RBGB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) RBGA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) RBBR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) RBBG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) RBBB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) RBBA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) RBAR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) RBAG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) RBAB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) RBAA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) RARR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) RARG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) RARB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) RARA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) RAGR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) RAGG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) RAGB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) RAGA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) RABR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) RABG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) RABB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) RABA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) RAAR() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) RAAG() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) RAAB() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) RAAA() const { return Vec4(HC_SHUFFLE4F(*this, 0, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) GRRR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) GRRG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) GRRB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) GRRA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) GRGR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) GRGG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) GRGB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) GRGA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) GRBR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) GRBG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) GRBB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) GRBA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) GRAR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) GRAG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) GRAB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) GRAA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) GGRR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) GGRG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) GGRB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) GGRA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) GGGR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) GGGG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) GGGB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) GGGA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) GGBR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) GGBG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) GGBB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) GGBA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) GGAR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) GGAG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) GGAB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) GGAA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) GBRR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) GBRG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) GBRB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) GBRA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) GBGR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) GBGG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) GBGB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) GBGA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) GBBR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) GBBG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) GBBB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) GBBA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) GBAR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) GBAG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) GBAB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) GBAA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) GARR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) GARG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) GARB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) GARA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) GAGR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) GAGG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) GAGB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) GAGA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) GABR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) GABG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) GABB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) GABA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) GAAR() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) GAAG() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) GAAB() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) GAAA() const { return Vec4(HC_SHUFFLE4F(*this, 1, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) BRRR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) BRRG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) BRRB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) BRRA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) BRGR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) BRGG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) BRGB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) BRGA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) BRBR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) BRBG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) BRBB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) BRBA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) BRAR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) BRAG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) BRAB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) BRAA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) BGRR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) BGRG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) BGRB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) BGRA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) BGGR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) BGGG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) BGGB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) BGGA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) BGBR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) BGBG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) BGBB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) BGBA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) BGAR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) BGAG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) BGAB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) BGAA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) BBRR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) BBRG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) BBRB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) BBRA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) BBGR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) BBGG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) BBGB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) BBGA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) BBBR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) BBBG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) BBBB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) BBBA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) BBAR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) BBAG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) BBAB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) BBAA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) BARR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) BARG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) BARB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) BARA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) BAGR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) BAGG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) BAGB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) BAGA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) BABR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) BABG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) BABB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) BABA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) BAAR() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) BAAG() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) BAAB() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) BAAA() const { return Vec4(HC_SHUFFLE4F(*this, 2, 3, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ARRR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ARRG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ARRB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ARRA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ARGR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ARGG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ARGB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ARGA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ARBR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ARBG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ARBB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ARBA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ARAR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ARAG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ARAB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ARAA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 0, 3, 3)); }
	HC_MATHFUNCTION(Vec4) AGRR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 0)); }
	HC_MATHFUNCTION(Vec4) AGRG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 1)); }
	HC_MATHFUNCTION(Vec4) AGRB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 2)); }
	HC_MATHFUNCTION(Vec4) AGRA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 0, 3)); }
	HC_MATHFUNCTION(Vec4) AGGR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 0)); }
	HC_MATHFUNCTION(Vec4) AGGG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 1)); }
	HC_MATHFUNCTION(Vec4) AGGB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 2)); }
	HC_MATHFUNCTION(Vec4) AGGA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 1, 3)); }
	HC_MATHFUNCTION(Vec4) AGBR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 0)); }
	HC_MATHFUNCTION(Vec4) AGBG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 1)); }
	HC_MATHFUNCTION(Vec4) AGBB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 2)); }
	HC_MATHFUNCTION(Vec4) AGBA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 2, 3)); }
	HC_MATHFUNCTION(Vec4) AGAR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 0)); }
	HC_MATHFUNCTION(Vec4) AGAG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 1)); }
	HC_MATHFUNCTION(Vec4) AGAB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 2)); }
	HC_MATHFUNCTION(Vec4) AGAA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 1, 3, 3)); }
	HC_MATHFUNCTION(Vec4) ABRR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 0)); }
	HC_MATHFUNCTION(Vec4) ABRG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 1)); }
	HC_MATHFUNCTION(Vec4) ABRB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 2)); }
	HC_MATHFUNCTION(Vec4) ABRA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 0, 3)); }
	HC_MATHFUNCTION(Vec4) ABGR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 0)); }
	HC_MATHFUNCTION(Vec4) ABGG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 1)); }
	HC_MATHFUNCTION(Vec4) ABGB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 2)); }
	HC_MATHFUNCTION(Vec4) ABGA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 1, 3)); }
	HC_MATHFUNCTION(Vec4) ABBR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 0)); }
	HC_MATHFUNCTION(Vec4) ABBG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 1)); }
	HC_MATHFUNCTION(Vec4) ABBB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 2)); }
	HC_MATHFUNCTION(Vec4) ABBA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 2, 3)); }
	HC_MATHFUNCTION(Vec4) ABAR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 0)); }
	HC_MATHFUNCTION(Vec4) ABAG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 1)); }
	HC_MATHFUNCTION(Vec4) ABAB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 2)); }
	HC_MATHFUNCTION(Vec4) ABAA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 2, 3, 3)); }
	HC_MATHFUNCTION(Vec4) AARR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 0)); }
	HC_MATHFUNCTION(Vec4) AARG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 1)); }
	HC_MATHFUNCTION(Vec4) AARB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 2)); }
	HC_MATHFUNCTION(Vec4) AARA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 0, 3)); }
	HC_MATHFUNCTION(Vec4) AAGR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 0)); }
	HC_MATHFUNCTION(Vec4) AAGG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 1)); }
	HC_MATHFUNCTION(Vec4) AAGB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 2)); }
	HC_MATHFUNCTION(Vec4) AAGA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 1, 3)); }
	HC_MATHFUNCTION(Vec4) AABR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 0)); }
	HC_MATHFUNCTION(Vec4) AABG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 1)); }
	HC_MATHFUNCTION(Vec4) AABB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 2)); }
	HC_MATHFUNCTION(Vec4) AABA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 2, 3)); }
	HC_MATHFUNCTION(Vec4) AAAR() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 0)); }
	HC_MATHFUNCTION(Vec4) AAAG() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 1)); }
	HC_MATHFUNCTION(Vec4) AAAB() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 2)); }
	HC_MATHFUNCTION(Vec4) AAAA() const { return Vec4(HC_SHUFFLE4F(*this, 3, 3, 3, 3)); }
};


#pragma region Vec2Funcs
HC_MATHFUNCTION(Vec2) operator+(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec2) operator-(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec2) operator*(Vec2 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec2) operator*(float _fLeft, Vec2 _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec2) operator/(Vec2 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec2) operator/(float _fLeft, Vec2 _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec2) operator*(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec2) operator~(Vec2 _vVector) { return Vec2(_mm_setzero_ps()); }
HC_MATHFUNCTION(Vec2) operator-(Vec2 _vVector) { return Vec2(_mm_setzero_ps()) - (_vVector); }
HC_MATHFUNCTION(bool) operator==(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_MATHFUNCTION(bool) operator<(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_MATHFUNCTION(bool) operator>(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_MATHFUNCTION(bool) operator<=(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_MATHFUNCTION(bool) operator>=(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_MATHFUNCTION(bool) operator!=(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) != 0; }
HC_MATHFUNCTION(Vec2) Min(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec2) Max(Vec2 _vLeft, Vec2 _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec2) Clamp(Vec2 _vVector, Vec2 _vMin, Vec2 _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_MATHFUNCTION(float) Sum(const Vec2 _vVector) { return _vVector.X() + _vVector.Y(); }
HC_MATHFUNCTION(float) Dot(Vec2 _vLeft, Vec2 _vRight) { return Sum(_vLeft * _vRight); }
HC_MATHFUNCTION(float) Length(Vec2 _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_MATHFUNCTION(float) LengthSquared(Vec2 _vVector) { return Dot(_vVector, _vVector); }
HC_MATHFUNCTION(Vec2) Normalize(Vec2 _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_MATHFUNCTION(float) AngleBetween(Vec2 _vLeft, Vec2 _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_MATHFUNCTION(float) Cross(Vec2 _vLeft, Vec2 _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_MATHFUNCTION(Vec2) Abs(Vec2 _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMask().m_fVec); return _vVector; }
#pragma endregion

#pragma region Vec3Funcs
HC_MATHFUNCTION(Vec3) operator+(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec3) operator-(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec3) operator*(Vec3 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec3) operator*(float _fLeft, Vec3 _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec3) operator/(Vec3 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec3) operator/(float _fLeft, Vec3 _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec3) operator*(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec3) operator~(Vec3 _vVector) { return Vec3(_mm_setzero_ps()); }
HC_MATHFUNCTION(Vec3) operator-(Vec3 _vVector) { return Vec3(_mm_setzero_ps()) - _vVector; }
HC_MATHFUNCTION(bool) operator==(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_MATHFUNCTION(bool) operator<(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_MATHFUNCTION(bool) operator>(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_MATHFUNCTION(bool) operator<=(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_MATHFUNCTION(bool) operator>=(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_MATHFUNCTION(bool) operator!=(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) != 0; }
HC_MATHFUNCTION(Vec3) Min(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec3) Max(Vec3 _vLeft, Vec3 _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec3) Clamp(Vec3 _vVector, Vec3 _vMin, Vec3 _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_MATHFUNCTION(float) Sum(const Vec3 _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_MATHFUNCTION(float) Dot(Vec3 _vLeft, Vec3 _vRight) { return Sum(_vLeft * _vRight); }
HC_MATHFUNCTION(float) Length(Vec3 _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_MATHFUNCTION(float) LengthSquared(Vec3 _vVector) { return Dot(_vVector, _vVector); }
HC_MATHFUNCTION(Vec3) Normalize(Vec3 _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_MATHFUNCTION(float) AngleBetween(Vec3 _vLeft, Vec3 _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_MATHFUNCTION(Vec3) Cross(Vec3 _vLeft, Vec3 _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_MATHFUNCTION(Vec3) Abs(Vec3 _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMask().m_fVec); return _vVector; }
#pragma endregion

#pragma region Vec4Funcs
HC_MATHFUNCTION(Vec4) operator+(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec4) operator-(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec4) operator*(Vec4 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec4) operator*(float _fLeft, Vec4 _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec4) operator/(Vec4 _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_MATHFUNCTION(Vec4) operator/(float _fLeft, Vec4 _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_MATHFUNCTION(Vec4) operator*(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec4) operator~(Vec4 _vVector) { return Vec4(_mm_setzero_ps()); }
HC_MATHFUNCTION(Vec4) operator-(Vec4 _vVector) { return Vec4(_mm_setzero_ps()) - _vVector; }
HC_MATHFUNCTION(bool) operator==(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(bool) operator<(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(bool) operator>(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(bool) operator<=(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(bool) operator>=(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(bool) operator!=(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_MATHFUNCTION(Vec4) Min(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec4) Max(Vec4 _vLeft, Vec4 _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_MATHFUNCTION(Vec4) Clamp(Vec4 _vVector, Vec4 _vMin, Vec4 _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_MATHFUNCTION(float) Sum(const Vec4 _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_MATHFUNCTION(float) Dot(Vec4 _vLeft, Vec4 _vRight) { return Sum(_vLeft * _vRight); }
HC_MATHFUNCTION(float) Length(Vec4 _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_MATHFUNCTION(float) LengthSquared(Vec4 _vVector) { return Dot(_vVector, _vVector); }
HC_MATHFUNCTION(Vec4) Normalize(Vec4 _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_MATHFUNCTION(float) AngleBetween(Vec4 _vLeft, Vec4 _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_MATHFUNCTION(Vec4) Cross(Vec4 _vLeft, Vec4 _vRight) { _vRight = Vec4((_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_fVec); _vRight.W() = _vLeft.W(); return _vRight; }
HC_MATHFUNCTION(Vec4) Abs(Vec4 _vVector) { return Vec4(_mm_andnot_ps(_vVector.m_fVec, SignBitMask().m_fVec)); }
#pragma endregion

#pragma endregion

#pragma region DoublePrecisionVectors

struct Vec2Double {
private:

public:
	//Constructors
	inline Vec2Double();													//Init to Zero
	inline Vec2Double(double _x, double _y);								//Init to X and Y
	inline Vec2Double(const Vec2Double& _other);							//Init from Copy

	//Assignment
	inline Vec2Double& operator=(const Vec2Double& _other);					//Assignment
	inline Vec2Double& operator+=(const Vec2Double& _other);				//Addition
	inline Vec2Double& operator-=(const Vec2Double& _other);				//Subtraction
	inline Vec2Double& operator*=(const double _scale);						//Scaling
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec2Double operator+(const Vec2Double& _other) const;			//Addition
	inline Vec2Double operator-(const Vec2Double& _other) const;			//Subtraction
	inline Vec2Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec2Double& _other) const;				//Dot Product
	inline double operator&(const Vec2Double& _other) const;				//Cross Product
	inline Vec2Double operator~() const;									//Zero
	inline Vec2Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec2Double& _other) const;					//Check Equality
	inline bool operator<(const Vec2Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec2Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec2Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec2Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec2Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec2Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec2Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec2Double& _other) const;						//Dot Product
	inline double Cross(const Vec2Double& _other) const;					//Cross Product
	inline void Add(const Vec2Double& _other);								//Addition
	inline void Subtract(const Vec2Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec2Double& _other) const;						//Check Equality
	inline bool Less(const Vec2Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec2Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec2Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec2Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec2Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)

	//Swizzle Operations (Vec2Double)
	inline Vec2Double XX() const;											//Swizzle to XX Vector
	inline Vec2Double YY() const;											//Swizzle to YY Vector
	inline Vec2Double YX() const;											//Swizzle to YX Vector
	inline Vec2Double RR() const;											//Swizzle to RR Vector
	inline Vec2Double GG() const;											//Swizzle to GG Vector
	inline Vec2Double GR() const;											//Swizzle to GR Vector
};

struct Vec3Double {
private:

public:
	//Constructors
	inline Vec3Double();													//Init to Zero
	inline Vec3Double(double _x, double _y, double _z);						//Init to X, Y, and Z
	inline Vec3Double(const Vec2Double& _xy, double _z);							//Init from a Vec2 for X and Y, and from a double for Z
	inline Vec3Double(double _x, const Vec2Double& _yz);							//Init from X, and from a Vec2 for Y and Z
	inline Vec3Double(const Vec3Double& _other);							//Init from Copy

	//Assignment
	inline Vec3Double& operator=(const Vec3Double& _other);					//Assignment
	inline Vec3Double& operator+=(const Vec3Double& _other);				//Addition
	inline Vec3Double& operator-=(const Vec3Double& _other);				//Subtraction
	inline Vec3Double& operator*=(const double _scale);						//Scaling
	inline Vec3Double& operator&=(const Vec3Double& _other);				//Cross Product
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec3Double operator+(const Vec3Double& _other) const;			//Addition
	inline Vec3Double operator-(const Vec3Double& _other) const;			//Subtraction
	inline Vec3Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec3Double& _other) const;				//Dot Product
	inline Vec3Double operator&(const Vec3Double& _other) const;			//Cross Product
	inline Vec3Double operator~() const;									//Zero
	inline Vec3Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec3Double& _other) const;					//Check Equality
	inline bool operator<(const Vec3Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec3Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec3Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec3Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec3Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec3Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec3Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec3Double& _other) const;						//Dot Product
	inline void Cross(const Vec3Double& _other);							//Cross Product
	inline void Add(const Vec3Double& _other);								//Addition
	inline void Subtract(const Vec3Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec3Double& _other) const;						//Check Equality
	inline bool Less(const Vec3Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec3Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec3Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec3Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec3Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double& Z();														//Vector Z Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)
	inline double Z() const;												//Vector Z Component (Const)

	//Swizzle Operations (Vec2DoubleDouble)
	inline Vec2Double XX() const;													//Swizzle to XX Vector
	inline Vec2Double YY() const;													//Swizzle to YY Vector
	inline Vec2Double ZZ() const;													//Swizzle to ZZ Vector
	inline Vec2Double XY() const;													//Swizzle to XY Vector
	inline Vec2Double XZ() const;													//Swizzle to XZ Vector
	inline Vec2Double YX() const;													//Swizzle to YX Vector
	inline Vec2Double YZ() const;													//Swizzle to YZ Vector
	inline Vec2Double ZX() const;													//Swizzle to ZX Vector
	inline Vec2Double ZY() const;													//Swizzle to ZY Vector
	inline Vec2Double RR() const;													//Swizzle to RR Vector
	inline Vec2Double GG() const;													//Swizzle to GG Vector
	inline Vec2Double BB() const;													//Swizzle to BB Vector
	inline Vec2Double RG() const;													//Swizzle to RG Vector
	inline Vec2Double RB() const;													//Swizzle to RB Vector
	inline Vec2Double GR() const;													//Swizzle to GR Vector
	inline Vec2Double GB() const;													//Swizzle to GB Vector
	inline Vec2Double BR() const;													//Swizzle to BR Vector
	inline Vec2Double BG() const;													//Swizzle to BG Vector

	//Swizzle Operations (Vec3Double)
	inline Vec3Double XXX() const;											//Swizzle to XXX Vector
	inline Vec3Double XXY() const;											//Swizzle to XXY Vector
	inline Vec3Double XXZ() const;											//Swizzle to XXZ Vector
	inline Vec3Double XYX() const;											//Swizzle to XYX Vector
	inline Vec3Double XYY() const;											//Swizzle to XYY Vector
	inline Vec3Double XZX() const;											//Swizzle to XZX Vector
	inline Vec3Double XZY() const;											//Swizzle to XZY Vector
	inline Vec3Double XZZ() const;											//Swizzle to XZZ Vector
	inline Vec3Double YXX() const;											//Swizzle to YXX Vector
	inline Vec3Double YXY() const;											//Swizzle to YXY Vector
	inline Vec3Double YXZ() const;											//Swizzle to YXZ Vector
	inline Vec3Double YYX() const;											//Swizzle to YYX Vector
	inline Vec3Double YYY() const;											//Swizzle to YYY Vector
	inline Vec3Double YYZ() const;											//Swizzle to YYZ Vector
	inline Vec3Double YZX() const;											//Swizzle to YZX Vector
	inline Vec3Double YZY() const;											//Swizzle to YZY Vector
	inline Vec3Double YZZ() const;											//Swizzle to YZZ Vector
	inline Vec3Double ZXX() const;											//Swizzle to ZXX Vector
	inline Vec3Double ZXY() const;											//Swizzle to ZXY Vector
	inline Vec3Double ZXZ() const;											//Swizzle to ZXZ Vector
	inline Vec3Double ZYX() const;											//Swizzle to ZYX Vector
	inline Vec3Double ZYY() const;											//Swizzle to ZYY Vector
	inline Vec3Double ZYZ() const;											//Swizzle to ZYZ Vector
	inline Vec3Double ZZX() const;											//Swizzle to ZZX Vector
	inline Vec3Double ZZY() const;											//Swizzle to ZZY Vector
	inline Vec3Double ZZZ() const;											//Swizzle to ZZZ Vector
	inline Vec3Double RRR() const;											//Swizzle to RRR Vector
	inline Vec3Double RRG() const;											//Swizzle to RRG Vector
	inline Vec3Double RRB() const;											//Swizzle to RRB Vector
	inline Vec3Double RGR() const;											//Swizzle to RGR Vector
	inline Vec3Double RGG() const;											//Swizzle to RGG Vector
	inline Vec3Double RBR() const;											//Swizzle to RBR Vector
	inline Vec3Double RBG() const;											//Swizzle to RBG Vector
	inline Vec3Double RBB() const;											//Swizzle to RBB Vector
	inline Vec3Double GRR() const;											//Swizzle to GRR Vector
	inline Vec3Double GRG() const;											//Swizzle to GRG Vector
	inline Vec3Double GRB() const;											//Swizzle to GRB Vector
	inline Vec3Double GGR() const;											//Swizzle to GGR Vector
	inline Vec3Double GGG() const;											//Swizzle to GGG Vector
	inline Vec3Double GGB() const;											//Swizzle to GGB Vector
	inline Vec3Double GBR() const;											//Swizzle to GBR Vector
	inline Vec3Double GBG() const;											//Swizzle to GBG Vector
	inline Vec3Double GBB() const;											//Swizzle to GBB Vector
	inline Vec3Double BRR() const;											//Swizzle to BRR Vector
	inline Vec3Double BRG() const;											//Swizzle to BRG Vector
	inline Vec3Double BRB() const;											//Swizzle to BRB Vector
	inline Vec3Double BGR() const;											//Swizzle to BGR Vector
	inline Vec3Double BGG() const;											//Swizzle to BGG Vector
	inline Vec3Double BGB() const;											//Swizzle to BGB Vector
	inline Vec3Double BBR() const;											//Swizzle to BBR Vector
	inline Vec3Double BBG() const;											//Swizzle to BBG Vector
	inline Vec3Double BBB() const;											//Swizzle to BBB Vector
};

struct Vec4Double {
private:

public:
	//Constructors
	inline Vec4Double();													//Init to Zero
	inline Vec4Double(double _x, double _y, double _z, double _w);			//Init to X, Y, Z, and W
	inline Vec4Double(const Vec2Double& _xy, double _z, double _w);			//Init from a Vec2Double for X and Y, and from a double for Z and W
	inline Vec4Double(double _x, const Vec2Double& _yz, double _w);			//Init from X, from a Vec2Double for Y and Z and a double for W
	inline Vec4Double(double _x, double _y, const Vec2Double& _zw);			//Init from X and Y, and from a Vec2Double for Z and W
	inline Vec4Double(const Vec2Double& _xy, const Vec2Double& _zw);		//Init from 2 Vec2Double's
	inline Vec4Double(const Vec3Double& _xyz, double _w);					//Init from a Vec3Double and a double for W
	inline Vec4Double(double _x, const Vec3Double& _yzw);					//Init from a double for X and a Vec3Double
	inline Vec4Double(const Vec4Double& _other);							//Init from Copy

	//Assignment
	inline Vec4Double& operator=(const Vec4Double& _other);					//Assignment
	inline Vec4Double& operator+=(const Vec4Double& _other);				//Addition
	inline Vec4Double& operator-=(const Vec4Double& _other);				//Subtraction
	inline Vec4Double& operator*=(const double _scale);						//Scaling
	inline Vec4Double& operator&=(const Vec4Double& _other);				//Cross Product
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec4Double operator+(const Vec4Double& _other) const;			//Addition
	inline Vec4Double operator-(const Vec4Double& _other) const;			//Subtraction
	inline Vec4Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec4Double& _other) const;				//Dot Product
	inline Vec4Double operator&(const Vec4Double& _other) const;			//Cross Product
	inline Vec4Double operator~() const;									//Zero
	inline Vec4Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec4Double& _other) const;					//Check Equality
	inline bool operator<(const Vec4Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec4Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec4Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec4Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec4Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec4Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec4Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec4Double& _other) const;						//Dot Product
	inline void Cross(const Vec4Double& _other);							//Cross Product
	inline void Add(const Vec4Double& _other);								//Addition
	inline void Subtract(const Vec4Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec4Double& _other) const;						//Check Equality
	inline bool Less(const Vec4Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec4Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec4Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec4Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec4Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double& Z();														//Vector Z Component (Modifiable)
	inline double& W();														//Vector W Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)
	inline double Z() const;												//Vector Z Component (Const)
	inline double W() const;												//Vector W Component (Const)

	//Swizzle Operations (Vec2Double)
	inline Vec2Double XX() const;											//Swizzle to XX Vector
	inline Vec2Double YY() const;											//Swizzle to YY Vector
	inline Vec2Double ZZ() const;											//Swizzle to ZZ Vector
	inline Vec2Double WW() const;											//Swizzle to WW Vector
	inline Vec2Double XY() const;											//Swizzle to XY Vector
	inline Vec2Double XZ() const;											//Swizzle to XZ Vector
	inline Vec2Double XW() const;											//Swizzle to XW Vector
	inline Vec2Double YX() const;											//Swizzle to YX Vector
	inline Vec2Double YZ() const;											//Swizzle to YZ Vector
	inline Vec2Double YW() const;											//Swizzle to YW Vector
	inline Vec2Double ZX() const;											//Swizzle to ZX Vector
	inline Vec2Double ZY() const;											//Swizzle to ZY Vector
	inline Vec2Double ZW() const;											//Swizzle to ZW Vector
	inline Vec2Double WX() const;											//Swizzle to WX Vector
	inline Vec2Double WY() const;											//Swizzle to WY Vector
	inline Vec2Double WZ() const;											//Swizzle to WZ Vector
	inline Vec2Double RR() const;											//Swizzle to RR Vector
	inline Vec2Double GG() const;											//Swizzle to GG Vector
	inline Vec2Double BB() const;											//Swizzle to BB Vector
	inline Vec2Double AA() const;											//Swizzle to AA Vector
	inline Vec2Double RG() const;											//Swizzle to RG Vector
	inline Vec2Double RB() const;											//Swizzle to RB Vector
	inline Vec2Double RA() const;											//Swizzle to RA Vector
	inline Vec2Double GR() const;											//Swizzle to GR Vector
	inline Vec2Double GB() const;											//Swizzle to GB Vector
	inline Vec2Double GA() const;											//Swizzle to GA Vector
	inline Vec2Double BR() const;											//Swizzle to BR Vector
	inline Vec2Double BG() const;											//Swizzle to BG Vector
	inline Vec2Double BA() const;											//Swizzle to BA Vector
	inline Vec2Double AR() const;											//Swizzle to AR Vector
	inline Vec2Double AG() const;											//Swizzle to AG Vector
	inline Vec2Double AB() const;											//Swizzle to AB Vector

	//Swizzle Operations (Vec3Double)
	inline Vec3Double XXX() const;											//Swizzle to XXX Vector
	inline Vec3Double XXY() const;											//Swizzle to XXY Vector
	inline Vec3Double XXZ() const;											//Swizzle to XXZ Vector
	inline Vec3Double XXW() const;											//Swizzle to XXW Vector
	inline Vec3Double XYX() const;											//Swizzle to XYX Vector
	inline Vec3Double XYY() const;											//Swizzle to XYY Vector
	inline Vec3Double XYZ() const;											//Swizzle to XYZ Vector
	inline Vec3Double XYW() const;											//Swizzle to XYW Vector
	inline Vec3Double XZX() const;											//Swizzle to XZX Vector
	inline Vec3Double XZY() const;											//Swizzle to XZY Vector
	inline Vec3Double XZZ() const;											//Swizzle to XZZ Vector
	inline Vec3Double XZW() const;											//Swizzle to XZW Vector
	inline Vec3Double XWX() const;											//Swizzle to XWX Vector
	inline Vec3Double XWY() const;											//Swizzle to XWY Vector
	inline Vec3Double XWZ() const;											//Swizzle to XWZ Vector
	inline Vec3Double XWW() const;											//Swizzle to XWW Vector
	inline Vec3Double YXX() const;											//Swizzle to YXX Vector
	inline Vec3Double YXY() const;											//Swizzle to YXY Vector
	inline Vec3Double YXZ() const;											//Swizzle to YXZ Vector
	inline Vec3Double YXW() const;											//Swizzle to YXW Vector
	inline Vec3Double YYX() const;											//Swizzle to YYX Vector
	inline Vec3Double YYY() const;											//Swizzle to YYY Vector
	inline Vec3Double YYZ() const;											//Swizzle to YYZ Vector
	inline Vec3Double YYW() const;											//Swizzle to YYW Vector
	inline Vec3Double YZX() const;											//Swizzle to YZX Vector
	inline Vec3Double YZY() const;											//Swizzle to YZY Vector
	inline Vec3Double YZZ() const;											//Swizzle to YZZ Vector
	inline Vec3Double YZW() const;											//Swizzle to YZW Vector
	inline Vec3Double YWX() const;											//Swizzle to YWX Vector
	inline Vec3Double YWY() const;											//Swizzle to YWY Vector
	inline Vec3Double YWZ() const;											//Swizzle to YWZ Vector
	inline Vec3Double YWW() const;											//Swizzle to YWW Vector
	inline Vec3Double ZXX() const;											//Swizzle to ZXX Vector
	inline Vec3Double ZXY() const;											//Swizzle to ZXY Vector
	inline Vec3Double ZXZ() const;											//Swizzle to ZXZ Vector
	inline Vec3Double ZXW() const;											//Swizzle to ZXW Vector
	inline Vec3Double ZYX() const;											//Swizzle to ZYX Vector
	inline Vec3Double ZYY() const;											//Swizzle to ZYY Vector
	inline Vec3Double ZYZ() const;											//Swizzle to ZYZ Vector
	inline Vec3Double ZYW() const;											//Swizzle to ZYW Vector
	inline Vec3Double ZZX() const;											//Swizzle to ZZX Vector
	inline Vec3Double ZZY() const;											//Swizzle to ZZY Vector
	inline Vec3Double ZZZ() const;											//Swizzle to ZZZ Vector
	inline Vec3Double ZZW() const;											//Swizzle to ZZW Vector
	inline Vec3Double ZWX() const;											//Swizzle to ZWX Vector
	inline Vec3Double ZWY() const;											//Swizzle to ZWY Vector
	inline Vec3Double ZWZ() const;											//Swizzle to ZWZ Vector
	inline Vec3Double ZWW() const;											//Swizzle to ZWW Vector
	inline Vec3Double WXX() const;											//Swizzle to WXX Vector
	inline Vec3Double WXY() const;											//Swizzle to WXY Vector
	inline Vec3Double WXZ() const;											//Swizzle to WXZ Vector
	inline Vec3Double WXW() const;											//Swizzle to WXW Vector
	inline Vec3Double WYX() const;											//Swizzle to WYX Vector
	inline Vec3Double WYY() const;											//Swizzle to WYY Vector
	inline Vec3Double WYZ() const;											//Swizzle to WYZ Vector
	inline Vec3Double WYW() const;											//Swizzle to WYW Vector
	inline Vec3Double WZX() const;											//Swizzle to WZX Vector
	inline Vec3Double WZY() const;											//Swizzle to WZY Vector
	inline Vec3Double WZZ() const;											//Swizzle to WZZ Vector
	inline Vec3Double WZW() const;											//Swizzle to WZW Vector
	inline Vec3Double WWX() const;											//Swizzle to WWX Vector
	inline Vec3Double WWY() const;											//Swizzle to WWY Vector
	inline Vec3Double WWZ() const;											//Swizzle to WWZ Vector
	inline Vec3Double WWW() const;											//Swizzle to WWW Vector
	inline Vec3Double RRR() const;											//Swizzle to RRR Vector
	inline Vec3Double RRG() const;											//Swizzle to RRG Vector
	inline Vec3Double RRB() const;											//Swizzle to RRB Vector
	inline Vec3Double RRA() const;											//Swizzle to RRA Vector
	inline Vec3Double RGR() const;											//Swizzle to RGR Vector
	inline Vec3Double RGG() const;											//Swizzle to RGG Vector
	inline Vec3Double RGA() const;											//Swizzle to RGA Vector
	inline Vec3Double RGB() const;											//Swizzle to RGB Vector
	inline Vec3Double RBR() const;											//Swizzle to RBR Vector
	inline Vec3Double RBG() const;											//Swizzle to RBG Vector
	inline Vec3Double RBB() const;											//Swizzle to RBB Vector
	inline Vec3Double RBA() const;											//Swizzle to RBA Vector
	inline Vec3Double RAR() const;											//Swizzle to RAR Vector
	inline Vec3Double RAG() const;											//Swizzle to RAG Vector
	inline Vec3Double RAB() const;											//Swizzle to RAB Vector
	inline Vec3Double RAA() const;											//Swizzle to RAA Vector
	inline Vec3Double GRR() const;											//Swizzle to GRR Vector
	inline Vec3Double GRG() const;											//Swizzle to GRG Vector
	inline Vec3Double GRB() const;											//Swizzle to GRB Vector
	inline Vec3Double GRA() const;											//Swizzle to GRA Vector
	inline Vec3Double GGR() const;											//Swizzle to GGR Vector
	inline Vec3Double GGG() const;											//Swizzle to GGG Vector
	inline Vec3Double GGB() const;											//Swizzle to GGB Vector
	inline Vec3Double GGA() const;											//Swizzle to GGA Vector
	inline Vec3Double GBR() const;											//Swizzle to GBR Vector
	inline Vec3Double GBG() const;											//Swizzle to GBG Vector
	inline Vec3Double GBB() const;											//Swizzle to GBB Vector
	inline Vec3Double GBA() const;											//Swizzle to GBA Vector
	inline Vec3Double GAR() const;											//Swizzle to GAR Vector
	inline Vec3Double GAG() const;											//Swizzle to GAG Vector
	inline Vec3Double GAB() const;											//Swizzle to GAB Vector
	inline Vec3Double GAA() const;											//Swizzle to GAA Vector
	inline Vec3Double BRR() const;											//Swizzle to BRR Vector
	inline Vec3Double BRG() const;											//Swizzle to BRG Vector
	inline Vec3Double BRB() const;											//Swizzle to BRB Vector
	inline Vec3Double BRA() const;											//Swizzle to BRA Vector
	inline Vec3Double BGR() const;											//Swizzle to BGR Vector
	inline Vec3Double BGG() const;											//Swizzle to BGG Vector
	inline Vec3Double BGB() const;											//Swizzle to BGB Vector
	inline Vec3Double BGA() const;											//Swizzle to BGA Vector
	inline Vec3Double BBR() const;											//Swizzle to BBR Vector
	inline Vec3Double BBG() const;											//Swizzle to BBG Vector
	inline Vec3Double BBB() const;											//Swizzle to BBB Vector
	inline Vec3Double BBA() const;											//Swizzle to BBA Vector
	inline Vec3Double BAR() const;											//Swizzle to BAR Vector
	inline Vec3Double BAG() const;											//Swizzle to BAG Vector
	inline Vec3Double BAB() const;											//Swizzle to BAB Vector
	inline Vec3Double BAA() const;											//Swizzle to BAA Vector
	inline Vec3Double ARR() const;											//Swizzle to ARR Vector
	inline Vec3Double ARG() const;											//Swizzle to ARG Vector
	inline Vec3Double ARB() const;											//Swizzle to ARB Vector
	inline Vec3Double ARA() const;											//Swizzle to ARA Vector
	inline Vec3Double AGR() const;											//Swizzle to AGR Vector
	inline Vec3Double AGG() const;											//Swizzle to AGG Vector
	inline Vec3Double AGB() const;											//Swizzle to AGB Vector
	inline Vec3Double AGA() const;											//Swizzle to AGA Vector
	inline Vec3Double ABR() const;											//Swizzle to ABR Vector
	inline Vec3Double ABG() const;											//Swizzle to ABG Vector
	inline Vec3Double ABB() const;											//Swizzle to ABB Vector
	inline Vec3Double ABA() const;											//Swizzle to ABA Vector
	inline Vec3Double AAR() const;											//Swizzle to AAR Vector
	inline Vec3Double AAG() const;											//Swizzle to AAG Vector
	inline Vec3Double AAB() const;											//Swizzle to AAB Vector
	inline Vec3Double AAA() const;											//Swizzle to AAA Vector

	//Swizzle Operations (Vec4Double)
	inline Vec4Double XXXX() const;											//Swizzle to XXXX Vector
	inline Vec4Double XXXY() const;											//Swizzle to XXXY Vector
	inline Vec4Double XXXZ() const;											//Swizzle to XXXZ Vector
	inline Vec4Double XXXW() const;											//Swizzle to XXXW Vector
	inline Vec4Double XXYX() const;											//Swizzle to XXYX Vector
	inline Vec4Double XXYY() const;											//Swizzle to XXYY Vector
	inline Vec4Double XXYZ() const;											//Swizzle to XXYZ Vector
	inline Vec4Double XXYW() const;											//Swizzle to XXYW Vector
	inline Vec4Double XXZX() const;											//Swizzle to XXZX Vector
	inline Vec4Double XXZY() const;											//Swizzle to XXZY Vector
	inline Vec4Double XXZZ() const;											//Swizzle to XXZZ Vector
	inline Vec4Double XXZW() const;											//Swizzle to XXZW Vector
	inline Vec4Double XXWX() const;											//Swizzle to XXWX Vector
	inline Vec4Double XXWY() const;											//Swizzle to XXWY Vector
	inline Vec4Double XXWZ() const;											//Swizzle to XXWZ Vector
	inline Vec4Double XXWW() const;											//Swizzle to XXWW Vector
	inline Vec4Double XYXX() const;											//Swizzle to XYXX Vector
	inline Vec4Double XYXY() const;											//Swizzle to XYXY Vector
	inline Vec4Double XYXZ() const;											//Swizzle to XYXZ Vector
	inline Vec4Double XYXW() const;											//Swizzle to XYXW Vector
	inline Vec4Double XYYX() const;											//Swizzle to XYYX Vector
	inline Vec4Double XYYY() const;											//Swizzle to XYYY Vector
	inline Vec4Double XYYZ() const;											//Swizzle to XYYZ Vector
	inline Vec4Double XYYW() const;											//Swizzle to XYYW Vector
	inline Vec4Double XYZX() const;											//Swizzle to XYZX Vector
	inline Vec4Double XYZY() const;											//Swizzle to XYZY Vector
	inline Vec4Double XYZZ() const;											//Swizzle to XYZZ Vector
	inline Vec4Double XYWX() const;											//Swizzle to XYWX Vector
	inline Vec4Double XYWY() const;											//Swizzle to XYWY Vector
	inline Vec4Double XYWZ() const;											//Swizzle to XYWZ Vector
	inline Vec4Double XYWW() const;											//Swizzle to XYWW Vector
	inline Vec4Double XZXX() const;											//Swizzle to XZXX Vector
	inline Vec4Double XZXY() const;											//Swizzle to XZXY Vector
	inline Vec4Double XZXZ() const;											//Swizzle to XZXZ Vector
	inline Vec4Double XZXW() const;											//Swizzle to XZXW Vector
	inline Vec4Double XZYX() const;											//Swizzle to XZYX Vector
	inline Vec4Double XZYY() const;											//Swizzle to XZYY Vector
	inline Vec4Double XZYZ() const;											//Swizzle to XZYZ Vector
	inline Vec4Double XZYW() const;											//Swizzle to XZYW Vector
	inline Vec4Double XZZX() const;											//Swizzle to XZZX Vector
	inline Vec4Double XZZY() const;											//Swizzle to XZZY Vector
	inline Vec4Double XZZZ() const;											//Swizzle to XZZZ Vector
	inline Vec4Double XZZW() const;											//Swizzle to XZZW Vector
	inline Vec4Double XZWX() const;											//Swizzle to XZWX Vector
	inline Vec4Double XZWY() const;											//Swizzle to XZWY Vector
	inline Vec4Double XZWZ() const;											//Swizzle to XZWZ Vector
	inline Vec4Double XZWW() const;											//Swizzle to XZWW Vector
	inline Vec4Double XWXX() const;											//Swizzle to XWXX Vector
	inline Vec4Double XWXY() const;											//Swizzle to XWXY Vector
	inline Vec4Double XWXZ() const;											//Swizzle to XWXZ Vector
	inline Vec4Double XWXW() const;											//Swizzle to XWXW Vector
	inline Vec4Double XWYX() const;											//Swizzle to XWYX Vector
	inline Vec4Double XWYY() const;											//Swizzle to XWYY Vector
	inline Vec4Double XWYZ() const;											//Swizzle to XWYZ Vector
	inline Vec4Double XWYW() const;											//Swizzle to XWYW Vector
	inline Vec4Double XWZX() const;											//Swizzle to XWZX Vector
	inline Vec4Double XWZY() const;											//Swizzle to XWZY Vector
	inline Vec4Double XWZZ() const;											//Swizzle to XWZZ Vector
	inline Vec4Double XWZW() const;											//Swizzle to XWZW Vector
	inline Vec4Double XWWX() const;											//Swizzle to XWWX Vector
	inline Vec4Double XWWY() const;											//Swizzle to XWWY Vector
	inline Vec4Double XWWZ() const;											//Swizzle to XWWZ Vector
	inline Vec4Double XWWW() const;											//Swizzle to XWWW Vector
	inline Vec4Double YXXX() const;											//Swizzle to YXXX Vector
	inline Vec4Double YXXY() const;											//Swizzle to YXXY Vector
	inline Vec4Double YXXZ() const;											//Swizzle to YXXZ Vector
	inline Vec4Double YXXW() const;											//Swizzle to YXXW Vector
	inline Vec4Double YXYX() const;											//Swizzle to YXYX Vector
	inline Vec4Double YXYY() const;											//Swizzle to YXYY Vector
	inline Vec4Double YXYZ() const;											//Swizzle to YXYZ Vector
	inline Vec4Double YXYW() const;											//Swizzle to YXYW Vector
	inline Vec4Double YXZX() const;											//Swizzle to YXZX Vector
	inline Vec4Double YXZY() const;											//Swizzle to YXZY Vector
	inline Vec4Double YXZZ() const;											//Swizzle to YXZZ Vector
	inline Vec4Double YXZW() const;											//Swizzle to YXZW Vector
	inline Vec4Double YXWX() const;											//Swizzle to YXWX Vector
	inline Vec4Double YXWY() const;											//Swizzle to YXWY Vector
	inline Vec4Double YXWZ() const;											//Swizzle to YXWZ Vector
	inline Vec4Double YXWW() const;											//Swizzle to YXWW Vector
	inline Vec4Double YYXX() const;											//Swizzle to YYXX Vector
	inline Vec4Double YYXY() const;											//Swizzle to YYXY Vector
	inline Vec4Double YYXZ() const;											//Swizzle to YYXZ Vector
	inline Vec4Double YYXW() const;											//Swizzle to YYXW Vector
	inline Vec4Double YYYX() const;											//Swizzle to YYYX Vector
	inline Vec4Double YYYY() const;											//Swizzle to YYYY Vector
	inline Vec4Double YYYZ() const;											//Swizzle to YYYZ Vector
	inline Vec4Double YYYW() const;											//Swizzle to YYYW Vector
	inline Vec4Double YYZX() const;											//Swizzle to YYZX Vector
	inline Vec4Double YYZY() const;											//Swizzle to YYZY Vector
	inline Vec4Double YYZZ() const;											//Swizzle to YYZZ Vector
	inline Vec4Double YYZW() const;											//Swizzle to YYZW Vector
	inline Vec4Double YYWX() const;											//Swizzle to YYWX Vector
	inline Vec4Double YYWY() const;											//Swizzle to YYWY Vector
	inline Vec4Double YYWZ() const;											//Swizzle to YYWZ Vector
	inline Vec4Double YYWW() const;											//Swizzle to YYWW Vector
	inline Vec4Double YZXX() const;											//Swizzle to YZXX Vector
	inline Vec4Double YZXY() const;											//Swizzle to YZXY Vector
	inline Vec4Double YZXZ() const;											//Swizzle to YZXZ Vector
	inline Vec4Double YZXW() const;											//Swizzle to YZXW Vector
	inline Vec4Double YZYX() const;											//Swizzle to YZYX Vector
	inline Vec4Double YZYY() const;											//Swizzle to YZYY Vector
	inline Vec4Double YZYZ() const;											//Swizzle to YZYZ Vector
	inline Vec4Double YZYW() const;											//Swizzle to YZYW Vector
	inline Vec4Double YZZX() const;											//Swizzle to YZZX Vector
	inline Vec4Double YZZY() const;											//Swizzle to YZZY Vector
	inline Vec4Double YZZZ() const;											//Swizzle to YZZZ Vector
	inline Vec4Double YZZW() const;											//Swizzle to YZZW Vector
	inline Vec4Double YZWX() const;											//Swizzle to YZWX Vector
	inline Vec4Double YZWY() const;											//Swizzle to YZWY Vector
	inline Vec4Double YZWZ() const;											//Swizzle to YZWZ Vector
	inline Vec4Double YZWW() const;											//Swizzle to YZWW Vector
	inline Vec4Double YWXX() const;											//Swizzle to YWXX Vector
	inline Vec4Double YWXY() const;											//Swizzle to YWXY Vector
	inline Vec4Double YWXZ() const;											//Swizzle to YWXZ Vector
	inline Vec4Double YWXW() const;											//Swizzle to YWXW Vector
	inline Vec4Double YWYX() const;											//Swizzle to YWYX Vector
	inline Vec4Double YWYY() const;											//Swizzle to YWYY Vector
	inline Vec4Double YWYZ() const;											//Swizzle to YWYZ Vector
	inline Vec4Double YWYW() const;											//Swizzle to YWYW Vector
	inline Vec4Double YWZX() const;											//Swizzle to YWZX Vector
	inline Vec4Double YWZY() const;											//Swizzle to YWZY Vector
	inline Vec4Double YWZZ() const;											//Swizzle to YWZZ Vector
	inline Vec4Double YWZW() const;											//Swizzle to YWZW Vector
	inline Vec4Double YWWX() const;											//Swizzle to YWWX Vector
	inline Vec4Double YWWY() const;											//Swizzle to YWWY Vector
	inline Vec4Double YWWZ() const;											//Swizzle to YWWZ Vector
	inline Vec4Double YWWW() const;											//Swizzle to YWWW Vector
	inline Vec4Double ZXXX() const;											//Swizzle to ZXXX Vector
	inline Vec4Double ZXXY() const;											//Swizzle to ZXXY Vector
	inline Vec4Double ZXXZ() const;											//Swizzle to ZXXZ Vector
	inline Vec4Double ZXXW() const;											//Swizzle to ZXXW Vector
	inline Vec4Double ZXYX() const;											//Swizzle to ZXYX Vector
	inline Vec4Double ZXYY() const;											//Swizzle to ZXYY Vector
	inline Vec4Double ZXYZ() const;											//Swizzle to ZXYZ Vector
	inline Vec4Double ZXYW() const;											//Swizzle to ZXYW Vector
	inline Vec4Double ZXZX() const;											//Swizzle to ZXZX Vector
	inline Vec4Double ZXZY() const;											//Swizzle to ZXZY Vector
	inline Vec4Double ZXZZ() const;											//Swizzle to ZXZZ Vector
	inline Vec4Double ZXZW() const;											//Swizzle to ZXZW Vector
	inline Vec4Double ZXWX() const;											//Swizzle to ZXWX Vector
	inline Vec4Double ZXWY() const;											//Swizzle to ZXWY Vector
	inline Vec4Double ZXWZ() const;											//Swizzle to ZXWZ Vector
	inline Vec4Double ZXWW() const;											//Swizzle to ZXWW Vector
	inline Vec4Double ZYXX() const;											//Swizzle to ZYXX Vector
	inline Vec4Double ZYXY() const;											//Swizzle to ZYXY Vector
	inline Vec4Double ZYXZ() const;											//Swizzle to ZYXZ Vector
	inline Vec4Double ZYXW() const;											//Swizzle to ZYXW Vector
	inline Vec4Double ZYYX() const;											//Swizzle to ZYYX Vector
	inline Vec4Double ZYYY() const;											//Swizzle to ZYYY Vector
	inline Vec4Double ZYYZ() const;											//Swizzle to ZYYZ Vector
	inline Vec4Double ZYYW() const;											//Swizzle to ZYYW Vector
	inline Vec4Double ZYZX() const;											//Swizzle to ZYZX Vector
	inline Vec4Double ZYZY() const;											//Swizzle to ZYZY Vector
	inline Vec4Double ZYZZ() const;											//Swizzle to ZYZZ Vector
	inline Vec4Double ZYZW() const;											//Swizzle to ZYZW Vector
	inline Vec4Double ZYWX() const;											//Swizzle to ZYWX Vector
	inline Vec4Double ZYWY() const;											//Swizzle to ZYWY Vector
	inline Vec4Double ZYWZ() const;											//Swizzle to ZYWZ Vector
	inline Vec4Double ZYWW() const;											//Swizzle to ZYWW Vector
	inline Vec4Double ZZXX() const;											//Swizzle to ZZXX Vector
	inline Vec4Double ZZXY() const;											//Swizzle to ZZXY Vector
	inline Vec4Double ZZXZ() const;											//Swizzle to ZZXZ Vector
	inline Vec4Double ZZXW() const;											//Swizzle to ZZXW Vector
	inline Vec4Double ZZYX() const;											//Swizzle to ZZYX Vector
	inline Vec4Double ZZYY() const;											//Swizzle to ZZYY Vector
	inline Vec4Double ZZYZ() const;											//Swizzle to ZZYZ Vector
	inline Vec4Double ZZYW() const;											//Swizzle to ZZYW Vector
	inline Vec4Double ZZZX() const;											//Swizzle to ZZZX Vector
	inline Vec4Double ZZZY() const;											//Swizzle to ZZZY Vector
	inline Vec4Double ZZZZ() const;											//Swizzle to ZZZZ Vector
	inline Vec4Double ZZZW() const;											//Swizzle to ZZZW Vector
	inline Vec4Double ZZWX() const;											//Swizzle to ZZWX Vector
	inline Vec4Double ZZWY() const;											//Swizzle to ZZWY Vector
	inline Vec4Double ZZWZ() const;											//Swizzle to ZZWZ Vector
	inline Vec4Double ZZWW() const;											//Swizzle to ZZWW Vector
	inline Vec4Double ZWXX() const;											//Swizzle to ZWXX Vector
	inline Vec4Double ZWXY() const;											//Swizzle to ZWXY Vector
	inline Vec4Double ZWXZ() const;											//Swizzle to ZWXZ Vector
	inline Vec4Double ZWXW() const;											//Swizzle to ZWXW Vector
	inline Vec4Double ZWYX() const;											//Swizzle to ZWYX Vector
	inline Vec4Double ZWYY() const;											//Swizzle to ZWYY Vector
	inline Vec4Double ZWYZ() const;											//Swizzle to ZWYZ Vector
	inline Vec4Double ZWYW() const;											//Swizzle to ZWYW Vector
	inline Vec4Double ZWZX() const;											//Swizzle to ZWZX Vector
	inline Vec4Double ZWZY() const;											//Swizzle to ZWZY Vector
	inline Vec4Double ZWZZ() const;											//Swizzle to ZWZZ Vector
	inline Vec4Double ZWZW() const;											//Swizzle to ZWZW Vector
	inline Vec4Double ZWWX() const;											//Swizzle to ZWWX Vector
	inline Vec4Double ZWWY() const;											//Swizzle to ZWWY Vector
	inline Vec4Double ZWWZ() const;											//Swizzle to ZWWZ Vector
	inline Vec4Double ZWWW() const;											//Swizzle to ZWWW Vector
	inline Vec4Double WXXX() const;											//Swizzle to WXXX Vector
	inline Vec4Double WXXY() const;											//Swizzle to WXXY Vector
	inline Vec4Double WXXZ() const;											//Swizzle to WXXZ Vector
	inline Vec4Double WXXW() const;											//Swizzle to WXXW Vector
	inline Vec4Double WXYX() const;											//Swizzle to WXYX Vector
	inline Vec4Double WXYY() const;											//Swizzle to WXYY Vector
	inline Vec4Double WXYZ() const;											//Swizzle to WXYZ Vector
	inline Vec4Double WXYW() const;											//Swizzle to WXYW Vector
	inline Vec4Double WXZX() const;											//Swizzle to WXZX Vector
	inline Vec4Double WXZY() const;											//Swizzle to WXZY Vector
	inline Vec4Double WXZZ() const;											//Swizzle to WXZZ Vector
	inline Vec4Double WXZW() const;											//Swizzle to WXZW Vector
	inline Vec4Double WXWX() const;											//Swizzle to WXWX Vector
	inline Vec4Double WXWY() const;											//Swizzle to WXWY Vector
	inline Vec4Double WXWZ() const;											//Swizzle to WXWZ Vector
	inline Vec4Double WXWW() const;											//Swizzle to WXWW Vector
	inline Vec4Double WYXX() const;											//Swizzle to WYXX Vector
	inline Vec4Double WYXY() const;											//Swizzle to WYXY Vector
	inline Vec4Double WYXZ() const;											//Swizzle to WYXZ Vector
	inline Vec4Double WYXW() const;											//Swizzle to WYXW Vector
	inline Vec4Double WYYX() const;											//Swizzle to WYYX Vector
	inline Vec4Double WYYY() const;											//Swizzle to WYYY Vector
	inline Vec4Double WYYZ() const;											//Swizzle to WYYZ Vector
	inline Vec4Double WYYW() const;											//Swizzle to WYYW Vector
	inline Vec4Double WYZX() const;											//Swizzle to WYZX Vector
	inline Vec4Double WYZY() const;											//Swizzle to WYZY Vector
	inline Vec4Double WYZZ() const;											//Swizzle to WYZZ Vector
	inline Vec4Double WYZW() const;											//Swizzle to WYZW Vector
	inline Vec4Double WYWX() const;											//Swizzle to WYWX Vector
	inline Vec4Double WYWY() const;											//Swizzle to WYWY Vector
	inline Vec4Double WYWZ() const;											//Swizzle to WYWZ Vector
	inline Vec4Double WYWW() const;											//Swizzle to WYWW Vector
	inline Vec4Double WZXX() const;											//Swizzle to WZXX Vector
	inline Vec4Double WZXY() const;											//Swizzle to WZXY Vector
	inline Vec4Double WZXZ() const;											//Swizzle to WZXZ Vector
	inline Vec4Double WZXW() const;											//Swizzle to WZXW Vector
	inline Vec4Double WZYX() const;											//Swizzle to WZYX Vector
	inline Vec4Double WZYY() const;											//Swizzle to WZYY Vector
	inline Vec4Double WZYZ() const;											//Swizzle to WZYZ Vector
	inline Vec4Double WZYW() const;											//Swizzle to WZYW Vector
	inline Vec4Double WZZX() const;											//Swizzle to WZZX Vector
	inline Vec4Double WZZY() const;											//Swizzle to WZZY Vector
	inline Vec4Double WZZZ() const;											//Swizzle to WZZZ Vector
	inline Vec4Double WZZW() const;											//Swizzle to WZZW Vector
	inline Vec4Double WZWX() const;											//Swizzle to WZWX Vector
	inline Vec4Double WZWY() const;											//Swizzle to WZWY Vector
	inline Vec4Double WZWZ() const;											//Swizzle to WZWZ Vector
	inline Vec4Double WZWW() const;											//Swizzle to WZWW Vector
	inline Vec4Double WWXX() const;											//Swizzle to WWXX Vector
	inline Vec4Double WWXY() const;											//Swizzle to WWXY Vector
	inline Vec4Double WWXZ() const;											//Swizzle to WWXZ Vector
	inline Vec4Double WWXW() const;											//Swizzle to WWXW Vector
	inline Vec4Double WWYX() const;											//Swizzle to WWYX Vector
	inline Vec4Double WWYY() const;											//Swizzle to WWYY Vector
	inline Vec4Double WWYZ() const;											//Swizzle to WWYZ Vector
	inline Vec4Double WWYW() const;											//Swizzle to WWYW Vector
	inline Vec4Double WWZX() const;											//Swizzle to WWZX Vector
	inline Vec4Double WWZY() const;											//Swizzle to WWZY Vector
	inline Vec4Double WWZZ() const;											//Swizzle to WWZZ Vector
	inline Vec4Double WWZW() const;											//Swizzle to WWZW Vector
	inline Vec4Double WWWX() const;											//Swizzle to WWWX Vector
	inline Vec4Double WWWY() const;											//Swizzle to WWWY Vector
	inline Vec4Double WWWZ() const;											//Swizzle to WWWZ Vector
	inline Vec4Double WWWW() const;											//Swizzle to WWWW Vector
	inline Vec4Double RRRR() const;											//Swizzle to RRRR Vector
	inline Vec4Double RRRG() const;											//Swizzle to RRRG Vector
	inline Vec4Double RRRB() const;											//Swizzle to RRRB Vector
	inline Vec4Double RRRA() const;											//Swizzle to RRRA Vector
	inline Vec4Double RRGR() const;											//Swizzle to RRGR Vector
	inline Vec4Double RRGG() const;											//Swizzle to RRGG Vector
	inline Vec4Double RRGB() const;											//Swizzle to RRGB Vector
	inline Vec4Double RRGA() const;											//Swizzle to RRGA Vector
	inline Vec4Double RRBR() const;											//Swizzle to RRBR Vector
	inline Vec4Double RRBG() const;											//Swizzle to RRBG Vector
	inline Vec4Double RRBB() const;											//Swizzle to RRBB Vector
	inline Vec4Double RRBA() const;											//Swizzle to RRBA Vector
	inline Vec4Double RRAR() const;											//Swizzle to RRAR Vector
	inline Vec4Double RRAG() const;											//Swizzle to RRAG Vector
	inline Vec4Double RRAB() const;											//Swizzle to RRAB Vector
	inline Vec4Double RRAA() const;											//Swizzle to RRAA Vector
	inline Vec4Double RGRR() const;											//Swizzle to RGRR Vector
	inline Vec4Double RGRG() const;											//Swizzle to RGRG Vector
	inline Vec4Double RGRB() const;											//Swizzle to RGRB Vector
	inline Vec4Double RGRA() const;											//Swizzle to RGRA Vector
	inline Vec4Double RGGR() const;											//Swizzle to RGGR Vector
	inline Vec4Double RGGG() const;											//Swizzle to RGGG Vector
	inline Vec4Double RGGB() const;											//Swizzle to RGGB Vector
	inline Vec4Double RGGA() const;											//Swizzle to RGGA Vector
	inline Vec4Double RGBR() const;											//Swizzle to RGBR Vector
	inline Vec4Double RGBG() const;											//Swizzle to RGBG Vector
	inline Vec4Double RGBB() const;											//Swizzle to RGBB Vector
	inline Vec4Double RGAR() const;											//Swizzle to RGAR Vector
	inline Vec4Double RGAG() const;											//Swizzle to RGAG Vector
	inline Vec4Double RGAB() const;											//Swizzle to RGAB Vector
	inline Vec4Double RGAA() const;											//Swizzle to RGAA Vector
	inline Vec4Double RBRR() const;											//Swizzle to RBRR Vector
	inline Vec4Double RBRG() const;											//Swizzle to RBRG Vector
	inline Vec4Double RBRB() const;											//Swizzle to RBRB Vector
	inline Vec4Double RBRA() const;											//Swizzle to RBRA Vector
	inline Vec4Double RBGR() const;											//Swizzle to RBGR Vector
	inline Vec4Double RBGG() const;											//Swizzle to RBGG Vector
	inline Vec4Double RBGB() const;											//Swizzle to RBGB Vector
	inline Vec4Double RBGA() const;											//Swizzle to RBGA Vector
	inline Vec4Double RBBR() const;											//Swizzle to RBBR Vector
	inline Vec4Double RBBG() const;											//Swizzle to RBBG Vector
	inline Vec4Double RBBB() const;											//Swizzle to RBBB Vector
	inline Vec4Double RBBA() const;											//Swizzle to RBBA Vector
	inline Vec4Double RBAR() const;											//Swizzle to RBAR Vector
	inline Vec4Double RBAG() const;											//Swizzle to RBAG Vector
	inline Vec4Double RBAB() const;											//Swizzle to RBAB Vector
	inline Vec4Double RBAA() const;											//Swizzle to RBAA Vector
	inline Vec4Double RARR() const;											//Swizzle to RARR Vector
	inline Vec4Double RARG() const;											//Swizzle to RARG Vector
	inline Vec4Double RARB() const;											//Swizzle to RARB Vector
	inline Vec4Double RARA() const;											//Swizzle to RARA Vector
	inline Vec4Double RAGR() const;											//Swizzle to RAGR Vector
	inline Vec4Double RAGG() const;											//Swizzle to RAGG Vector
	inline Vec4Double RAGB() const;											//Swizzle to RAGB Vector
	inline Vec4Double RAGA() const;											//Swizzle to RAGA Vector
	inline Vec4Double RABR() const;											//Swizzle to RABR Vector
	inline Vec4Double RABG() const;											//Swizzle to RABG Vector
	inline Vec4Double RABB() const;											//Swizzle to RABB Vector
	inline Vec4Double RABA() const;											//Swizzle to RABA Vector
	inline Vec4Double RAAR() const;											//Swizzle to RAAR Vector
	inline Vec4Double RAAG() const;											//Swizzle to RAAG Vector
	inline Vec4Double RAAB() const;											//Swizzle to RAAB Vector
	inline Vec4Double RAAA() const;											//Swizzle to RAAA Vector
	inline Vec4Double GRRR() const;											//Swizzle to GRRR Vector
	inline Vec4Double GRRG() const;											//Swizzle to GRRG Vector
	inline Vec4Double GRRB() const;											//Swizzle to GRRB Vector
	inline Vec4Double GRRA() const;											//Swizzle to GRRA Vector
	inline Vec4Double GRGR() const;											//Swizzle to GRGR Vector
	inline Vec4Double GRGG() const;											//Swizzle to GRGG Vector
	inline Vec4Double GRGB() const;											//Swizzle to GRGB Vector
	inline Vec4Double GRGA() const;											//Swizzle to GRGA Vector
	inline Vec4Double GRBR() const;											//Swizzle to GRBR Vector
	inline Vec4Double GRBG() const;											//Swizzle to GRBG Vector
	inline Vec4Double GRBB() const;											//Swizzle to GRBB Vector
	inline Vec4Double GRBA() const;											//Swizzle to GRBA Vector
	inline Vec4Double GRAR() const;											//Swizzle to GRAR Vector
	inline Vec4Double GRAG() const;											//Swizzle to GRAG Vector
	inline Vec4Double GRAB() const;											//Swizzle to GRAB Vector
	inline Vec4Double GRAA() const;											//Swizzle to GRAA Vector
	inline Vec4Double GGRR() const;											//Swizzle to GGRR Vector
	inline Vec4Double GGRG() const;											//Swizzle to GGRG Vector
	inline Vec4Double GGRB() const;											//Swizzle to GGRB Vector
	inline Vec4Double GGRA() const;											//Swizzle to GGRA Vector
	inline Vec4Double GGGR() const;											//Swizzle to GGGR Vector
	inline Vec4Double GGGG() const;											//Swizzle to GGGG Vector
	inline Vec4Double GGGB() const;											//Swizzle to GGGB Vector
	inline Vec4Double GGGA() const;											//Swizzle to GGGA Vector
	inline Vec4Double GGBR() const;											//Swizzle to GGBR Vector
	inline Vec4Double GGBG() const;											//Swizzle to GGBG Vector
	inline Vec4Double GGBB() const;											//Swizzle to GGBB Vector
	inline Vec4Double GGBA() const;											//Swizzle to GGBA Vector
	inline Vec4Double GGAR() const;											//Swizzle to GGAR Vector
	inline Vec4Double GGAG() const;											//Swizzle to GGAG Vector
	inline Vec4Double GGAB() const;											//Swizzle to GGAB Vector
	inline Vec4Double GGAA() const;											//Swizzle to GGAA Vector
	inline Vec4Double GBRR() const;											//Swizzle to GBRR Vector
	inline Vec4Double GBRG() const;											//Swizzle to GBRG Vector
	inline Vec4Double GBRB() const;											//Swizzle to GBRB Vector
	inline Vec4Double GBRA() const;											//Swizzle to GBRA Vector
	inline Vec4Double GBGR() const;											//Swizzle to GBGR Vector
	inline Vec4Double GBGG() const;											//Swizzle to GBGG Vector
	inline Vec4Double GBGB() const;											//Swizzle to GBGB Vector
	inline Vec4Double GBGA() const;											//Swizzle to GBGA Vector
	inline Vec4Double GBBR() const;											//Swizzle to GBBR Vector
	inline Vec4Double GBBG() const;											//Swizzle to GBBG Vector
	inline Vec4Double GBBB() const;											//Swizzle to GBBB Vector
	inline Vec4Double GBBA() const;											//Swizzle to GBBA Vector
	inline Vec4Double GBAR() const;											//Swizzle to GBAR Vector
	inline Vec4Double GBAG() const;											//Swizzle to GBAG Vector
	inline Vec4Double GBAB() const;											//Swizzle to GBAB Vector
	inline Vec4Double GBAA() const;											//Swizzle to GBAA Vector
	inline Vec4Double GARR() const;											//Swizzle to GARR Vector
	inline Vec4Double GARG() const;											//Swizzle to GARG Vector
	inline Vec4Double GARB() const;											//Swizzle to GARB Vector
	inline Vec4Double GARA() const;											//Swizzle to GARA Vector
	inline Vec4Double GAGR() const;											//Swizzle to GAGR Vector
	inline Vec4Double GAGG() const;											//Swizzle to GAGG Vector
	inline Vec4Double GAGB() const;											//Swizzle to GAGB Vector
	inline Vec4Double GAGA() const;											//Swizzle to GAGA Vector
	inline Vec4Double GABR() const;											//Swizzle to GABR Vector
	inline Vec4Double GABG() const;											//Swizzle to GABG Vector
	inline Vec4Double GABB() const;											//Swizzle to GABB Vector
	inline Vec4Double GABA() const;											//Swizzle to GABA Vector
	inline Vec4Double GAAR() const;											//Swizzle to GAAR Vector
	inline Vec4Double GAAG() const;											//Swizzle to GAAG Vector
	inline Vec4Double GAAB() const;											//Swizzle to GAAB Vector
	inline Vec4Double GAAA() const;											//Swizzle to GAAA Vector
	inline Vec4Double BRRR() const;											//Swizzle to BRRR Vector
	inline Vec4Double BRRG() const;											//Swizzle to BRRG Vector
	inline Vec4Double BRRB() const;											//Swizzle to BRRB Vector
	inline Vec4Double BRRA() const;											//Swizzle to BRRA Vector
	inline Vec4Double BRGR() const;											//Swizzle to BRGR Vector
	inline Vec4Double BRGG() const;											//Swizzle to BRGG Vector
	inline Vec4Double BRGB() const;											//Swizzle to BRGB Vector
	inline Vec4Double BRGA() const;											//Swizzle to BRGA Vector
	inline Vec4Double BRBR() const;											//Swizzle to BRBR Vector
	inline Vec4Double BRBG() const;											//Swizzle to BRBG Vector
	inline Vec4Double BRBB() const;											//Swizzle to BRBB Vector
	inline Vec4Double BRBA() const;											//Swizzle to BRBA Vector
	inline Vec4Double BRAR() const;											//Swizzle to BRAR Vector
	inline Vec4Double BRAG() const;											//Swizzle to BRAG Vector
	inline Vec4Double BRAB() const;											//Swizzle to BRAB Vector
	inline Vec4Double BRAA() const;											//Swizzle to BRAA Vector
	inline Vec4Double BGRR() const;											//Swizzle to BGRR Vector
	inline Vec4Double BGRG() const;											//Swizzle to BGRG Vector
	inline Vec4Double BGRB() const;											//Swizzle to BGRB Vector
	inline Vec4Double BGRA() const;											//Swizzle to BGRA Vector
	inline Vec4Double BGGR() const;											//Swizzle to BGGR Vector
	inline Vec4Double BGGG() const;											//Swizzle to BGGG Vector
	inline Vec4Double BGGB() const;											//Swizzle to BGGB Vector
	inline Vec4Double BGGA() const;											//Swizzle to BGGA Vector
	inline Vec4Double BGBR() const;											//Swizzle to BGBR Vector
	inline Vec4Double BGBG() const;											//Swizzle to BGBG Vector
	inline Vec4Double BGBB() const;											//Swizzle to BGBB Vector
	inline Vec4Double BGBA() const;											//Swizzle to BGBA Vector
	inline Vec4Double BGAR() const;											//Swizzle to BGAR Vector
	inline Vec4Double BGAG() const;											//Swizzle to BGAG Vector
	inline Vec4Double BGAB() const;											//Swizzle to BGAB Vector
	inline Vec4Double BGAA() const;											//Swizzle to BGAA Vector
	inline Vec4Double BBRR() const;											//Swizzle to BBRR Vector
	inline Vec4Double BBRG() const;											//Swizzle to BBRG Vector
	inline Vec4Double BBRB() const;											//Swizzle to BBRB Vector
	inline Vec4Double BBRA() const;											//Swizzle to BBRA Vector
	inline Vec4Double BBGR() const;											//Swizzle to BBGR Vector
	inline Vec4Double BBGG() const;											//Swizzle to BBGG Vector
	inline Vec4Double BBGB() const;											//Swizzle to BBGB Vector
	inline Vec4Double BBGA() const;											//Swizzle to BBGA Vector
	inline Vec4Double BBBR() const;											//Swizzle to BBBR Vector
	inline Vec4Double BBBG() const;											//Swizzle to BBBG Vector
	inline Vec4Double BBBB() const;											//Swizzle to BBBB Vector
	inline Vec4Double BBBA() const;											//Swizzle to BBBA Vector
	inline Vec4Double BBAR() const;											//Swizzle to BBAR Vector
	inline Vec4Double BBAG() const;											//Swizzle to BBAG Vector
	inline Vec4Double BBAB() const;											//Swizzle to BBAB Vector
	inline Vec4Double BBAA() const;											//Swizzle to BBAA Vector
	inline Vec4Double BARR() const;											//Swizzle to BARR Vector
	inline Vec4Double BARG() const;											//Swizzle to BARG Vector
	inline Vec4Double BARB() const;											//Swizzle to BARB Vector
	inline Vec4Double BARA() const;											//Swizzle to BARA Vector
	inline Vec4Double BAGR() const;											//Swizzle to BAGR Vector
	inline Vec4Double BAGG() const;											//Swizzle to BAGG Vector
	inline Vec4Double BAGB() const;											//Swizzle to BAGB Vector
	inline Vec4Double BAGA() const;											//Swizzle to BAGA Vector
	inline Vec4Double BABR() const;											//Swizzle to BABR Vector
	inline Vec4Double BABG() const;											//Swizzle to BABG Vector
	inline Vec4Double BABB() const;											//Swizzle to BABB Vector
	inline Vec4Double BABA() const;											//Swizzle to BABA Vector
	inline Vec4Double BAAR() const;											//Swizzle to BAAR Vector
	inline Vec4Double BAAG() const;											//Swizzle to BAAG Vector
	inline Vec4Double BAAB() const;											//Swizzle to BAAB Vector
	inline Vec4Double BAAA() const;											//Swizzle to BAAA Vector
	inline Vec4Double ARRR() const;											//Swizzle to ARRR Vector
	inline Vec4Double ARRG() const;											//Swizzle to ARRG Vector
	inline Vec4Double ARRB() const;											//Swizzle to ARRB Vector
	inline Vec4Double ARRA() const;											//Swizzle to ARRA Vector
	inline Vec4Double ARGR() const;											//Swizzle to ARGR Vector
	inline Vec4Double ARGG() const;											//Swizzle to ARGG Vector
	inline Vec4Double ARGB() const;											//Swizzle to ARGB Vector
	inline Vec4Double ARGA() const;											//Swizzle to ARGA Vector
	inline Vec4Double ARBR() const;											//Swizzle to ARBR Vector
	inline Vec4Double ARBG() const;											//Swizzle to ARBG Vector
	inline Vec4Double ARBB() const;											//Swizzle to ARBB Vector
	inline Vec4Double ARBA() const;											//Swizzle to ARBA Vector
	inline Vec4Double ARAR() const;											//Swizzle to ARAR Vector
	inline Vec4Double ARAG() const;											//Swizzle to ARAG Vector
	inline Vec4Double ARAB() const;											//Swizzle to ARAB Vector
	inline Vec4Double ARAA() const;											//Swizzle to ARAA Vector
	inline Vec4Double AGRR() const;											//Swizzle to AGRR Vector
	inline Vec4Double AGRG() const;											//Swizzle to AGRG Vector
	inline Vec4Double AGRB() const;											//Swizzle to AGRB Vector
	inline Vec4Double AGRA() const;											//Swizzle to AGRA Vector
	inline Vec4Double AGGR() const;											//Swizzle to AGGR Vector
	inline Vec4Double AGGG() const;											//Swizzle to AGGG Vector
	inline Vec4Double AGGB() const;											//Swizzle to AGGB Vector
	inline Vec4Double AGGA() const;											//Swizzle to AGGA Vector
	inline Vec4Double AGBR() const;											//Swizzle to AGBR Vector
	inline Vec4Double AGBG() const;											//Swizzle to AGBG Vector
	inline Vec4Double AGBB() const;											//Swizzle to AGBB Vector
	inline Vec4Double AGBA() const;											//Swizzle to AGBA Vector
	inline Vec4Double AGAR() const;											//Swizzle to AGAR Vector
	inline Vec4Double AGAG() const;											//Swizzle to AGAG Vector
	inline Vec4Double AGAB() const;											//Swizzle to AGAB Vector
	inline Vec4Double AGAA() const;											//Swizzle to AGAA Vector
	inline Vec4Double ABRR() const;											//Swizzle to ABRR Vector
	inline Vec4Double ABRG() const;											//Swizzle to ABRG Vector
	inline Vec4Double ABRB() const;											//Swizzle to ABRB Vector
	inline Vec4Double ABRA() const;											//Swizzle to ABRA Vector
	inline Vec4Double ABGR() const;											//Swizzle to ABGR Vector
	inline Vec4Double ABGG() const;											//Swizzle to ABGG Vector
	inline Vec4Double ABGB() const;											//Swizzle to ABGB Vector
	inline Vec4Double ABGA() const;											//Swizzle to ABGA Vector
	inline Vec4Double ABBR() const;											//Swizzle to ABBR Vector
	inline Vec4Double ABBG() const;											//Swizzle to ABBG Vector
	inline Vec4Double ABBB() const;											//Swizzle to ABBB Vector
	inline Vec4Double ABBA() const;											//Swizzle to ABBA Vector
	inline Vec4Double ABAR() const;											//Swizzle to ABAR Vector
	inline Vec4Double ABAG() const;											//Swizzle to ABAG Vector
	inline Vec4Double ABAB() const;											//Swizzle to ABAB Vector
	inline Vec4Double ABAA() const;											//Swizzle to ABAA Vector
	inline Vec4Double AARR() const;											//Swizzle to AARR Vector
	inline Vec4Double AARG() const;											//Swizzle to AARG Vector
	inline Vec4Double AARB() const;											//Swizzle to AARB Vector
	inline Vec4Double AARA() const;											//Swizzle to AARA Vector
	inline Vec4Double AAGR() const;											//Swizzle to AAGR Vector
	inline Vec4Double AAGG() const;											//Swizzle to AAGG Vector
	inline Vec4Double AAGB() const;											//Swizzle to AAGB Vector
	inline Vec4Double AAGA() const;											//Swizzle to AAGA Vector
	inline Vec4Double AABR() const;											//Swizzle to AABR Vector
	inline Vec4Double AABG() const;											//Swizzle to AABG Vector
	inline Vec4Double AABB() const;											//Swizzle to AABB Vector
	inline Vec4Double AABA() const;											//Swizzle to AABA Vector
	inline Vec4Double AAAR() const;											//Swizzle to AAAR Vector
	inline Vec4Double AAAG() const;											//Swizzle to AAAG Vector
	inline Vec4Double AAAB() const;											//Swizzle to AAAB Vector
	inline Vec4Double AAAA() const;											//Swizzle to AAAA Vector
};

#pragma endregion

#pragma region IntegerVectors

struct Vec2Int {
private:

public:
	//Constructors
	inline Vec2Int();												//Init to Zero
	inline Vec2Int(int _x, int _y);									//Init to X and Y
	inline Vec2Int(const Vec2Int& _other);							//Init from Copy

	//Assignment
	inline Vec2Int& operator=(const Vec2Int& _other);				//Assignment
	inline Vec2Int& operator+=(const Vec2Int& _other);				//Addition
	inline Vec2Int& operator-=(const Vec2Int& _other);				//Subtraction
	inline Vec2Int& operator*=(const int _scale);					//Scaling
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec2Int operator+(const Vec2Int& _other) const;			//Addition
	inline Vec2Int operator-(const Vec2Int& _other) const;			//Subtraction
	inline Vec2Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec2Int& _other) const;				//Dot Product
	inline int operator&(const Vec2Int& _other) const;				//Cross Product
	inline Vec2Int operator~() const;								//Zero
	inline Vec2Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec2Int& _other) const;			//Check Equality
	inline bool operator<(const Vec2Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec2Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec2Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec2Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec2Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec2Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec2Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec2Int& _other) const;					//Dot Product
	inline int Cross(const Vec2Int& _other) const;					//Cross Product
	inline void Add(const Vec2Int& _other);							//Addition
	inline void Subtract(const Vec2Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec2Int& _other) const;				//Check Equality
	inline bool Less(const Vec2Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec2Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec2Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec2Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec2Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
};

struct Vec3Int {
private:

public:
	//Constructors
	inline Vec3Int();												//Init to Zero
	inline Vec3Int(int _x, int _y, int _z);							//Init to X, Y, and Z
	inline Vec3Int(const Vec2Int& _xy, int _z);						//Init from a Vec2Int for X and Y, and from a int for Z
	inline Vec3Int(int _x, const Vec2Int& _yz);						//Init from X, and from a Vec2Int for Y and Z
	inline Vec3Int(const Vec3Int& _other);							//Init from Copy

	//Assignment
	inline Vec3Int& operator=(const Vec3Int& _other);				//Assignment
	inline Vec3Int& operator+=(const Vec3Int& _other);				//Addition
	inline Vec3Int& operator-=(const Vec3Int& _other);				//Subtraction
	inline Vec3Int& operator*=(const int _scale);					//Scaling
	inline Vec3Int& operator&=(const Vec3Int& _other);				//Cross Product
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec3Int operator+(const Vec3Int& _other) const;			//Addition
	inline Vec3Int operator-(const Vec3Int& _other) const;			//Subtraction
	inline Vec3Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec3Int& _other) const;				//Dot Product
	inline Vec3Int operator&(const Vec3Int& _other) const;			//Cross Product
	inline Vec3Int operator~() const;								//Zero
	inline Vec3Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec3Int& _other) const;			//Check Equality
	inline bool operator<(const Vec3Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec3Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec3Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec3Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec3Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec3Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec3Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec3Int& _other) const;					//Dot Product
	inline void Cross(const Vec3Int& _other);						//Cross Product
	inline void Add(const Vec3Int& _other);							//Addition
	inline void Subtract(const Vec3Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec3Int& _other) const;				//Check Equality
	inline bool Less(const Vec3Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec3Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec3Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec3Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec3Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int& Z();												//Vector Z Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)
	inline int Z() const;											//Vector Z Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2Int XY() const;										//Swizzle to XY Vector
	inline Vec2Int XZ() const;										//Swizzle to XZ Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int YZ() const;										//Swizzle to YZ Vector
	inline Vec2Int ZX() const;										//Swizzle to ZX Vector
	inline Vec2Int ZY() const;										//Swizzle to ZY Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int BB() const;										//Swizzle to BB Vector
	inline Vec2Int RG() const;										//Swizzle to RG Vector
	inline Vec2Int RB() const;										//Swizzle to RB Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
	inline Vec2Int GB() const;										//Swizzle to GB Vector
	inline Vec2Int BR() const;										//Swizzle to BR Vector
	inline Vec2Int BG() const;										//Swizzle to BG Vector

	//Swizzle Operations (Vec3Int)
	inline Vec3Int XXX() const;										//Swizzle to XXX Vector
	inline Vec3Int XXY() const;										//Swizzle to XXY Vector
	inline Vec3Int XXZ() const;										//Swizzle to XXZ Vector
	inline Vec3Int XYX() const;										//Swizzle to XYX Vector
	inline Vec3Int XYY() const;										//Swizzle to XYY Vector
	inline Vec3Int XZX() const;										//Swizzle to XZX Vector
	inline Vec3Int XZY() const;										//Swizzle to XZY Vector
	inline Vec3Int XZZ() const;										//Swizzle to XZZ Vector
	inline Vec3Int YXX() const;										//Swizzle to YXX Vector
	inline Vec3Int YXY() const;										//Swizzle to YXY Vector
	inline Vec3Int YXZ() const;										//Swizzle to YXZ Vector
	inline Vec3Int YYX() const;										//Swizzle to YYX Vector
	inline Vec3Int YYY() const;										//Swizzle to YYY Vector
	inline Vec3Int YYZ() const;										//Swizzle to YYZ Vector
	inline Vec3Int YZX() const;										//Swizzle to YZX Vector
	inline Vec3Int YZY() const;										//Swizzle to YZY Vector
	inline Vec3Int YZZ() const;										//Swizzle to YZZ Vector
	inline Vec3Int ZXX() const;										//Swizzle to ZXX Vector
	inline Vec3Int ZXY() const;										//Swizzle to ZXY Vector
	inline Vec3Int ZXZ() const;										//Swizzle to ZXZ Vector
	inline Vec3Int ZYX() const;										//Swizzle to ZYX Vector
	inline Vec3Int ZYY() const;										//Swizzle to ZYY Vector
	inline Vec3Int ZYZ() const;										//Swizzle to ZYZ Vector
	inline Vec3Int ZZX() const;										//Swizzle to ZZX Vector
	inline Vec3Int ZZY() const;										//Swizzle to ZZY Vector
	inline Vec3Int ZZZ() const;										//Swizzle to ZZZ Vector
	inline Vec3Int RRR() const;										//Swizzle to RRR Vector
	inline Vec3Int RRG() const;										//Swizzle to RRG Vector
	inline Vec3Int RRB() const;										//Swizzle to RRB Vector
	inline Vec3Int RGR() const;										//Swizzle to RGR Vector
	inline Vec3Int RGG() const;										//Swizzle to RGG Vector
	inline Vec3Int RBR() const;										//Swizzle to RBR Vector
	inline Vec3Int RBG() const;										//Swizzle to RBG Vector
	inline Vec3Int RBB() const;										//Swizzle to RBB Vector
	inline Vec3Int GRR() const;										//Swizzle to GRR Vector
	inline Vec3Int GRG() const;										//Swizzle to GRG Vector
	inline Vec3Int GRB() const;										//Swizzle to GRB Vector
	inline Vec3Int GGR() const;										//Swizzle to GGR Vector
	inline Vec3Int GGG() const;										//Swizzle to GGG Vector
	inline Vec3Int GGB() const;										//Swizzle to GGB Vector
	inline Vec3Int GBR() const;										//Swizzle to GBR Vector
	inline Vec3Int GBG() const;										//Swizzle to GBG Vector
	inline Vec3Int GBB() const;										//Swizzle to GBB Vector
	inline Vec3Int BRR() const;										//Swizzle to BRR Vector
	inline Vec3Int BRG() const;										//Swizzle to BRG Vector
	inline Vec3Int BRB() const;										//Swizzle to BRB Vector
	inline Vec3Int BGR() const;										//Swizzle to BGR Vector
	inline Vec3Int BGG() const;										//Swizzle to BGG Vector
	inline Vec3Int BGB() const;										//Swizzle to BGB Vector
	inline Vec3Int BBR() const;										//Swizzle to BBR Vector
	inline Vec3Int BBG() const;										//Swizzle to BBG Vector
	inline Vec3Int BBB() const;										//Swizzle to BBB Vector
};

struct Vec4Int {
private:

public:
	//Constructors
	inline Vec4Int();												//Init to Zero
	inline Vec4Int(int _x, int _y, int _z, int _w);					//Init to X, Y, Z, and W
	inline Vec4Int(const Vec2Int& _xy, int _z, int _w);				//Init from a Vec2Int for X and Y, and from a int for Z and W
	inline Vec4Int(int _x, const Vec2Int& _yz, int _w);				//Init from X, from a Vec2Int for Y and Z and a int for W
	inline Vec4Int(int _x, int _y, const Vec2Int& _zw);				//Init from X and Y, and from a Vec2Int for Z and W
	inline Vec4Int(const Vec2Int& _xy, const Vec2Int& _zw);			//Init from 2 Vec2Int's
	inline Vec4Int(const Vec3Int& _xyz, int _w);					//Init from a Vec3Int and a int for W
	inline Vec4Int(int _x, const Vec3Int& _yzw);					//Init from a int for X and a Vec3Int
	inline Vec4Int(const Vec4Int& _other);							//Init from Copy

	//Assignment
	inline Vec4Int& operator=(const Vec4Int& _other);				//Assignment
	inline Vec4Int& operator+=(const Vec4Int& _other);				//Addition
	inline Vec4Int& operator-=(const Vec4Int& _other);				//Subtraction
	inline Vec4Int& operator*=(const int _scale);					//Scaling
	inline Vec4Int& operator&=(const Vec4Int& _other);				//Cross Product
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec4Int operator+(const Vec4Int& _other) const;			//Addition
	inline Vec4Int operator-(const Vec4Int& _other) const;			//Subtraction
	inline Vec4Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec4Int& _other) const;				//Dot Product
	inline Vec4Int operator&(const Vec4Int& _other) const;			//Cross Product
	inline Vec4Int operator~() const;								//Zero
	inline Vec4Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec4Int& _other) const;			//Check Equality
	inline bool operator<(const Vec4Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec4Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec4Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec4Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec4Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec4Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec4Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec4Int& _other) const;					//Dot Product
	inline void Cross(const Vec4Int& _other);						//Cross Product
	inline void Add(const Vec4Int& _other);							//Addition
	inline void Subtract(const Vec4Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec4Int& _other) const;				//Check Equality
	inline bool Less(const Vec4Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec4Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec4Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec4Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec4Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int& Z();												//Vector Z Component (Modifiable)
	inline int& W();												//Vector W Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)
	inline int Z() const;											//Vector Z Component (Const)
	inline int W() const;											//Vector W Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2Int WW() const;										//Swizzle to WW Vector
	inline Vec2Int XY() const;										//Swizzle to XY Vector
	inline Vec2Int XZ() const;										//Swizzle to XZ Vector
	inline Vec2Int XW() const;										//Swizzle to XW Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int YZ() const;										//Swizzle to YZ Vector
	inline Vec2Int YW() const;										//Swizzle to YW Vector
	inline Vec2Int ZX() const;										//Swizzle to ZX Vector
	inline Vec2Int ZY() const;										//Swizzle to ZY Vector
	inline Vec2Int ZW() const;										//Swizzle to ZW Vector
	inline Vec2Int WX() const;										//Swizzle to WX Vector
	inline Vec2Int WY() const;										//Swizzle to WY Vector
	inline Vec2Int WZ() const;										//Swizzle to WZ Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int BB() const;										//Swizzle to BB Vector
	inline Vec2Int AA() const;										//Swizzle to AA Vector
	inline Vec2Int RG() const;										//Swizzle to RG Vector
	inline Vec2Int RB() const;										//Swizzle to RB Vector
	inline Vec2Int RA() const;										//Swizzle to RA Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
	inline Vec2Int GB() const;										//Swizzle to GB Vector
	inline Vec2Int GA() const;										//Swizzle to GA Vector
	inline Vec2Int BR() const;										//Swizzle to BR Vector
	inline Vec2Int BG() const;										//Swizzle to BG Vector
	inline Vec2Int	BA() const;										//Swizzle to BA Vector
	inline Vec2Int AR() const;										//Swizzle to AR Vector
	inline Vec2Int AG() const;										//Swizzle to AG Vector
	inline Vec2Int AB() const;										//Swizzle to AB Vector

	//Swizzle Operations (Vec3Int)
	inline Vec3Int XXX() const;										//Swizzle to XXX Vector
	inline Vec3Int XXY() const;										//Swizzle to XXY Vector
	inline Vec3Int XXZ() const;										//Swizzle to XXZ Vector
	inline Vec3Int XXW() const;										//Swizzle to XXW Vector
	inline Vec3Int XYX() const;										//Swizzle to XYX Vector
	inline Vec3Int XYY() const;										//Swizzle to XYY Vector
	inline Vec3Int XYZ() const;										//Swizzle to XYZ Vector
	inline Vec3Int XYW() const;										//Swizzle to XYW Vector
	inline Vec3Int XZX() const;										//Swizzle to XZX Vector
	inline Vec3Int XZY() const;										//Swizzle to XZY Vector
	inline Vec3Int XZZ() const;										//Swizzle to XZZ Vector
	inline Vec3Int XZW() const;										//Swizzle to XZW Vector
	inline Vec3Int XWX() const;										//Swizzle to XWX Vector
	inline Vec3Int XWY() const;										//Swizzle to XWY Vector
	inline Vec3Int XWZ() const;										//Swizzle to XWZ Vector
	inline Vec3Int XWW() const;										//Swizzle to XWW Vector
	inline Vec3Int YXX() const;										//Swizzle to YXX Vector
	inline Vec3Int YXY() const;										//Swizzle to YXY Vector
	inline Vec3Int YXZ() const;										//Swizzle to YXZ Vector
	inline Vec3Int YXW() const;										//Swizzle to YXW Vector
	inline Vec3Int YYX() const;										//Swizzle to YYX Vector
	inline Vec3Int YYY() const;										//Swizzle to YYY Vector
	inline Vec3Int YYZ() const;										//Swizzle to YYZ Vector
	inline Vec3Int YYW() const;										//Swizzle to YYW Vector
	inline Vec3Int YZX() const;										//Swizzle to YZX Vector
	inline Vec3Int YZY() const;										//Swizzle to YZY Vector
	inline Vec3Int YZZ() const;										//Swizzle to YZZ Vector
	inline Vec3Int YZW() const;										//Swizzle to YZW Vector
	inline Vec3Int YWX() const;										//Swizzle to YWX Vector
	inline Vec3Int YWY() const;										//Swizzle to YWY Vector
	inline Vec3Int YWZ() const;										//Swizzle to YWZ Vector
	inline Vec3Int YWW() const;										//Swizzle to YWW Vector
	inline Vec3Int ZXX() const;										//Swizzle to ZXX Vector
	inline Vec3Int ZXY() const;										//Swizzle to ZXY Vector
	inline Vec3Int ZXZ() const;										//Swizzle to ZXZ Vector
	inline Vec3Int ZXW() const;										//Swizzle to ZXW Vector
	inline Vec3Int ZYX() const;										//Swizzle to ZYX Vector
	inline Vec3Int ZYY() const;										//Swizzle to ZYY Vector
	inline Vec3Int ZYZ() const;										//Swizzle to ZYZ Vector
	inline Vec3Int ZYW() const;										//Swizzle to ZYW Vector
	inline Vec3Int ZZX() const;										//Swizzle to ZZX Vector
	inline Vec3Int ZZY() const;										//Swizzle to ZZY Vector
	inline Vec3Int ZZZ() const;										//Swizzle to ZZZ Vector
	inline Vec3Int ZZW() const;										//Swizzle to ZZW Vector
	inline Vec3Int ZWX() const;										//Swizzle to ZWX Vector
	inline Vec3Int ZWY() const;										//Swizzle to ZWY Vector
	inline Vec3Int ZWZ() const;										//Swizzle to ZWZ Vector
	inline Vec3Int ZWW() const;										//Swizzle to ZWW Vector
	inline Vec3Int WXX() const;										//Swizzle to WXX Vector
	inline Vec3Int WXY() const;										//Swizzle to WXY Vector
	inline Vec3Int WXZ() const;										//Swizzle to WXZ Vector
	inline Vec3Int WXW() const;										//Swizzle to WXW Vector
	inline Vec3Int WYX() const;										//Swizzle to WYX Vector
	inline Vec3Int WYY() const;										//Swizzle to WYY Vector
	inline Vec3Int WYZ() const;										//Swizzle to WYZ Vector
	inline Vec3Int WYW() const;										//Swizzle to WYW Vector
	inline Vec3Int WZX() const;										//Swizzle to WZX Vector
	inline Vec3Int WZY() const;										//Swizzle to WZY Vector
	inline Vec3Int WZZ() const;										//Swizzle to WZZ Vector
	inline Vec3Int WZW() const;										//Swizzle to WZW Vector
	inline Vec3Int WWX() const;										//Swizzle to WWX Vector
	inline Vec3Int WWY() const;										//Swizzle to WWY Vector
	inline Vec3Int WWZ() const;										//Swizzle to WWZ Vector
	inline Vec3Int WWW() const;										//Swizzle to WWW Vector
	inline Vec3Int RRR() const;										//Swizzle to RRR Vector
	inline Vec3Int RRG() const;										//Swizzle to RRG Vector
	inline Vec3Int RRB() const;										//Swizzle to RRB Vector
	inline Vec3Int RRA() const;										//Swizzle to RRA Vector
	inline Vec3Int RGR() const;										//Swizzle to RGR Vector
	inline Vec3Int RGG() const;										//Swizzle to RGG Vector
	inline Vec3Int RGA() const;										//Swizzle to RGA Vector
	inline Vec3Int RGB() const;										//Swizzle to RGB Vector
	inline Vec3Int RBR() const;										//Swizzle to RBR Vector
	inline Vec3Int RBG() const;										//Swizzle to RBG Vector
	inline Vec3Int RBB() const;										//Swizzle to RBB Vector
	inline Vec3Int RBA() const;										//Swizzle to RBA Vector
	inline Vec3Int RAR() const;										//Swizzle to RAR Vector
	inline Vec3Int RAG() const;										//Swizzle to RAG Vector
	inline Vec3Int RAB() const;										//Swizzle to RAB Vector
	inline Vec3Int RAA() const;										//Swizzle to RAA Vector
	inline Vec3Int GRR() const;										//Swizzle to GRR Vector
	inline Vec3Int GRG() const;										//Swizzle to GRG Vector
	inline Vec3Int GRB() const;										//Swizzle to GRB Vector
	inline Vec3Int GRA() const;										//Swizzle to GRA Vector
	inline Vec3Int GGR() const;										//Swizzle to GGR Vector
	inline Vec3Int GGG() const;										//Swizzle to GGG Vector
	inline Vec3Int GGB() const;										//Swizzle to GGB Vector
	inline Vec3Int GGA() const;										//Swizzle to GGA Vector
	inline Vec3Int GBR() const;										//Swizzle to GBR Vector
	inline Vec3Int GBG() const;										//Swizzle to GBG Vector
	inline Vec3Int GBB() const;										//Swizzle to GBB Vector
	inline Vec3Int GBA() const;										//Swizzle to GBA Vector
	inline Vec3Int GAR() const;										//Swizzle to GAR Vector
	inline Vec3Int GAG() const;										//Swizzle to GAG Vector
	inline Vec3Int GAB() const;										//Swizzle to GAB Vector
	inline Vec3Int GAA() const;										//Swizzle to GAA Vector
	inline Vec3Int BRR() const;										//Swizzle to BRR Vector
	inline Vec3Int BRG() const;										//Swizzle to BRG Vector
	inline Vec3Int BRB() const;										//Swizzle to BRB Vector
	inline Vec3Int BRA() const;										//Swizzle to BRA Vector
	inline Vec3Int BGR() const;										//Swizzle to BGR Vector
	inline Vec3Int BGG() const;										//Swizzle to BGG Vector
	inline Vec3Int BGB() const;										//Swizzle to BGB Vector
	inline Vec3Int BGA() const;										//Swizzle to BGA Vector
	inline Vec3Int BBR() const;										//Swizzle to BBR Vector
	inline Vec3Int BBG() const;										//Swizzle to BBG Vector
	inline Vec3Int BBB() const;										//Swizzle to BBB Vector
	inline Vec3Int BBA() const;										//Swizzle to BBA Vector
	inline Vec3Int BAR() const;										//Swizzle to BAR Vector
	inline Vec3Int BAG() const;										//Swizzle to BAG Vector
	inline Vec3Int BAB() const;										//Swizzle to BAB Vector
	inline Vec3Int BAA() const;										//Swizzle to BAA Vector
	inline Vec3Int ARR() const;										//Swizzle to ARR Vector
	inline Vec3Int ARG() const;										//Swizzle to ARG Vector
	inline Vec3Int ARB() const;										//Swizzle to ARB Vector
	inline Vec3Int ARA() const;										//Swizzle to ARA Vector
	inline Vec3Int AGR() const;										//Swizzle to AGR Vector
	inline Vec3Int AGG() const;										//Swizzle to AGG Vector
	inline Vec3Int AGB() const;										//Swizzle to AGB Vector
	inline Vec3Int AGA() const;										//Swizzle to AGA Vector
	inline Vec3Int ABR() const;										//Swizzle to ABR Vector
	inline Vec3Int ABG() const;										//Swizzle to ABG Vector
	inline Vec3Int ABB() const;										//Swizzle to ABB Vector
	inline Vec3Int ABA() const;										//Swizzle to ABA Vector
	inline Vec3Int AAR() const;										//Swizzle to AAR Vector
	inline Vec3Int AAG() const;										//Swizzle to AAG Vector
	inline Vec3Int AAB() const;										//Swizzle to AAB Vector
	inline Vec3Int AAA() const;										//Swizzle to AAA Vector

	//Swizzle Operations (Vec4Int)
	inline Vec4Int XXXX() const;									//Swizzle to XXXX Vector
	inline Vec4Int XXXY() const;									//Swizzle to XXXY Vector
	inline Vec4Int XXXZ() const;									//Swizzle to XXXZ Vector
	inline Vec4Int XXXW() const;									//Swizzle to XXXW Vector
	inline Vec4Int XXYX() const;									//Swizzle to XXYX Vector
	inline Vec4Int XXYY() const;									//Swizzle to XXYY Vector
	inline Vec4Int XXYZ() const;									//Swizzle to XXYZ Vector
	inline Vec4Int XXYW() const;									//Swizzle to XXYW Vector
	inline Vec4Int XXZX() const;									//Swizzle to XXZX Vector
	inline Vec4Int XXZY() const;									//Swizzle to XXZY Vector
	inline Vec4Int XXZZ() const;									//Swizzle to XXZZ Vector
	inline Vec4Int XXZW() const;									//Swizzle to XXZW Vector
	inline Vec4Int XXWX() const;									//Swizzle to XXWX Vector
	inline Vec4Int XXWY() const;									//Swizzle to XXWY Vector
	inline Vec4Int XXWZ() const;									//Swizzle to XXWZ Vector
	inline Vec4Int XXWW() const;									//Swizzle to XXWW Vector
	inline Vec4Int XYXX() const;									//Swizzle to XYXX Vector
	inline Vec4Int XYXY() const;									//Swizzle to XYXY Vector
	inline Vec4Int XYXZ() const;									//Swizzle to XYXZ Vector
	inline Vec4Int XYXW() const;									//Swizzle to XYXW Vector
	inline Vec4Int XYYX() const;									//Swizzle to XYYX Vector
	inline Vec4Int XYYY() const;									//Swizzle to XYYY Vector
	inline Vec4Int XYYZ() const;									//Swizzle to XYYZ Vector
	inline Vec4Int XYYW() const;									//Swizzle to XYYW Vector
	inline Vec4Int XYZX() const;									//Swizzle to XYZX Vector
	inline Vec4Int XYZY() const;									//Swizzle to XYZY Vector
	inline Vec4Int XYZZ() const;									//Swizzle to XYZZ Vector
	inline Vec4Int XYWX() const;									//Swizzle to XYWX Vector
	inline Vec4Int XYWY() const;									//Swizzle to XYWY Vector
	inline Vec4Int XYWZ() const;									//Swizzle to XYWZ Vector
	inline Vec4Int XYWW() const;									//Swizzle to XYWW Vector
	inline Vec4Int XZXX() const;									//Swizzle to XZXX Vector
	inline Vec4Int XZXY() const;									//Swizzle to XZXY Vector
	inline Vec4Int XZXZ() const;									//Swizzle to XZXZ Vector
	inline Vec4Int XZXW() const;									//Swizzle to XZXW Vector
	inline Vec4Int XZYX() const;									//Swizzle to XZYX Vector
	inline Vec4Int XZYY() const;									//Swizzle to XZYY Vector
	inline Vec4Int XZYZ() const;									//Swizzle to XZYZ Vector
	inline Vec4Int XZYW() const;									//Swizzle to XZYW Vector
	inline Vec4Int XZZX() const;									//Swizzle to XZZX Vector
	inline Vec4Int XZZY() const;									//Swizzle to XZZY Vector
	inline Vec4Int XZZZ() const;									//Swizzle to XZZZ Vector
	inline Vec4Int XZZW() const;									//Swizzle to XZZW Vector
	inline Vec4Int XZWX() const;									//Swizzle to XZWX Vector
	inline Vec4Int XZWY() const;									//Swizzle to XZWY Vector
	inline Vec4Int XZWZ() const;									//Swizzle to XZWZ Vector
	inline Vec4Int XZWW() const;									//Swizzle to XZWW Vector
	inline Vec4Int XWXX() const;									//Swizzle to XWXX Vector
	inline Vec4Int XWXY() const;									//Swizzle to XWXY Vector
	inline Vec4Int XWXZ() const;									//Swizzle to XWXZ Vector
	inline Vec4Int XWXW() const;									//Swizzle to XWXW Vector
	inline Vec4Int XWYX() const;									//Swizzle to XWYX Vector
	inline Vec4Int XWYY() const;									//Swizzle to XWYY Vector
	inline Vec4Int XWYZ() const;									//Swizzle to XWYZ Vector
	inline Vec4Int XWYW() const;									//Swizzle to XWYW Vector
	inline Vec4Int XWZX() const;									//Swizzle to XWZX Vector
	inline Vec4Int XWZY() const;									//Swizzle to XWZY Vector
	inline Vec4Int XWZZ() const;									//Swizzle to XWZZ Vector
	inline Vec4Int XWZW() const;									//Swizzle to XWZW Vector
	inline Vec4Int XWWX() const;									//Swizzle to XWWX Vector
	inline Vec4Int XWWY() const;									//Swizzle to XWWY Vector
	inline Vec4Int XWWZ() const;									//Swizzle to XWWZ Vector
	inline Vec4Int XWWW() const;									//Swizzle to XWWW Vector
	inline Vec4Int YXXX() const;									//Swizzle to YXXX Vector
	inline Vec4Int YXXY() const;									//Swizzle to YXXY Vector
	inline Vec4Int YXXZ() const;									//Swizzle to YXXZ Vector
	inline Vec4Int YXXW() const;									//Swizzle to YXXW Vector
	inline Vec4Int YXYX() const;									//Swizzle to YXYX Vector
	inline Vec4Int YXYY() const;									//Swizzle to YXYY Vector
	inline Vec4Int YXYZ() const;									//Swizzle to YXYZ Vector
	inline Vec4Int YXYW() const;									//Swizzle to YXYW Vector
	inline Vec4Int YXZX() const;									//Swizzle to YXZX Vector
	inline Vec4Int YXZY() const;									//Swizzle to YXZY Vector
	inline Vec4Int YXZZ() const;									//Swizzle to YXZZ Vector
	inline Vec4Int YXZW() const;									//Swizzle to YXZW Vector
	inline Vec4Int YXWX() const;									//Swizzle to YXWX Vector
	inline Vec4Int YXWY() const;									//Swizzle to YXWY Vector
	inline Vec4Int YXWZ() const;									//Swizzle to YXWZ Vector
	inline Vec4Int YXWW() const;									//Swizzle to YXWW Vector
	inline Vec4Int YYXX() const;									//Swizzle to YYXX Vector
	inline Vec4Int YYXY() const;									//Swizzle to YYXY Vector
	inline Vec4Int YYXZ() const;									//Swizzle to YYXZ Vector
	inline Vec4Int YYXW() const;									//Swizzle to YYXW Vector
	inline Vec4Int YYYX() const;									//Swizzle to YYYX Vector
	inline Vec4Int YYYY() const;									//Swizzle to YYYY Vector
	inline Vec4Int YYYZ() const;									//Swizzle to YYYZ Vector
	inline Vec4Int YYYW() const;									//Swizzle to YYYW Vector
	inline Vec4Int YYZX() const;									//Swizzle to YYZX Vector
	inline Vec4Int YYZY() const;									//Swizzle to YYZY Vector
	inline Vec4Int YYZZ() const;									//Swizzle to YYZZ Vector
	inline Vec4Int YYZW() const;									//Swizzle to YYZW Vector
	inline Vec4Int YYWX() const;									//Swizzle to YYWX Vector
	inline Vec4Int YYWY() const;									//Swizzle to YYWY Vector
	inline Vec4Int YYWZ() const;									//Swizzle to YYWZ Vector
	inline Vec4Int YYWW() const;									//Swizzle to YYWW Vector
	inline Vec4Int YZXX() const;									//Swizzle to YZXX Vector
	inline Vec4Int YZXY() const;									//Swizzle to YZXY Vector
	inline Vec4Int YZXZ() const;									//Swizzle to YZXZ Vector
	inline Vec4Int YZXW() const;									//Swizzle to YZXW Vector
	inline Vec4Int YZYX() const;									//Swizzle to YZYX Vector
	inline Vec4Int YZYY() const;									//Swizzle to YZYY Vector
	inline Vec4Int YZYZ() const;									//Swizzle to YZYZ Vector
	inline Vec4Int YZYW() const;									//Swizzle to YZYW Vector
	inline Vec4Int YZZX() const;									//Swizzle to YZZX Vector
	inline Vec4Int YZZY() const;									//Swizzle to YZZY Vector
	inline Vec4Int YZZZ() const;									//Swizzle to YZZZ Vector
	inline Vec4Int YZZW() const;									//Swizzle to YZZW Vector
	inline Vec4Int YZWX() const;									//Swizzle to YZWX Vector
	inline Vec4Int YZWY() const;									//Swizzle to YZWY Vector
	inline Vec4Int YZWZ() const;									//Swizzle to YZWZ Vector
	inline Vec4Int YZWW() const;									//Swizzle to YZWW Vector
	inline Vec4Int YWXX() const;									//Swizzle to YWXX Vector
	inline Vec4Int YWXY() const;									//Swizzle to YWXY Vector
	inline Vec4Int YWXZ() const;									//Swizzle to YWXZ Vector
	inline Vec4Int YWXW() const;									//Swizzle to YWXW Vector
	inline Vec4Int YWYX() const;									//Swizzle to YWYX Vector
	inline Vec4Int YWYY() const;									//Swizzle to YWYY Vector
	inline Vec4Int YWYZ() const;									//Swizzle to YWYZ Vector
	inline Vec4Int YWYW() const;									//Swizzle to YWYW Vector
	inline Vec4Int YWZX() const;									//Swizzle to YWZX Vector
	inline Vec4Int YWZY() const;									//Swizzle to YWZY Vector
	inline Vec4Int YWZZ() const;									//Swizzle to YWZZ Vector
	inline Vec4Int YWZW() const;									//Swizzle to YWZW Vector
	inline Vec4Int YWWX() const;									//Swizzle to YWWX Vector
	inline Vec4Int YWWY() const;									//Swizzle to YWWY Vector
	inline Vec4Int YWWZ() const;									//Swizzle to YWWZ Vector
	inline Vec4Int YWWW() const;									//Swizzle to YWWW Vector
	inline Vec4Int ZXXX() const;									//Swizzle to ZXXX Vector
	inline Vec4Int ZXXY() const;									//Swizzle to ZXXY Vector
	inline Vec4Int ZXXZ() const;									//Swizzle to ZXXZ Vector
	inline Vec4Int ZXXW() const;									//Swizzle to ZXXW Vector
	inline Vec4Int ZXYX() const;									//Swizzle to ZXYX Vector
	inline Vec4Int ZXYY() const;									//Swizzle to ZXYY Vector
	inline Vec4Int ZXYZ() const;									//Swizzle to ZXYZ Vector
	inline Vec4Int ZXYW() const;									//Swizzle to ZXYW Vector
	inline Vec4Int ZXZX() const;									//Swizzle to ZXZX Vector
	inline Vec4Int ZXZY() const;									//Swizzle to ZXZY Vector
	inline Vec4Int ZXZZ() const;									//Swizzle to ZXZZ Vector
	inline Vec4Int ZXZW() const;									//Swizzle to ZXZW Vector
	inline Vec4Int ZXWX() const;									//Swizzle to ZXWX Vector
	inline Vec4Int ZXWY() const;									//Swizzle to ZXWY Vector
	inline Vec4Int ZXWZ() const;									//Swizzle to ZXWZ Vector
	inline Vec4Int ZXWW() const;									//Swizzle to ZXWW Vector
	inline Vec4Int ZYXX() const;									//Swizzle to ZYXX Vector
	inline Vec4Int ZYXY() const;									//Swizzle to ZYXY Vector
	inline Vec4Int ZYXZ() const;									//Swizzle to ZYXZ Vector
	inline Vec4Int ZYXW() const;									//Swizzle to ZYXW Vector
	inline Vec4Int ZYYX() const;									//Swizzle to ZYYX Vector
	inline Vec4Int ZYYY() const;									//Swizzle to ZYYY Vector
	inline Vec4Int ZYYZ() const;									//Swizzle to ZYYZ Vector
	inline Vec4Int ZYYW() const;									//Swizzle to ZYYW Vector
	inline Vec4Int ZYZX() const;									//Swizzle to ZYZX Vector
	inline Vec4Int ZYZY() const;									//Swizzle to ZYZY Vector
	inline Vec4Int ZYZZ() const;									//Swizzle to ZYZZ Vector
	inline Vec4Int ZYZW() const;									//Swizzle to ZYZW Vector
	inline Vec4Int ZYWX() const;									//Swizzle to ZYWX Vector
	inline Vec4Int ZYWY() const;									//Swizzle to ZYWY Vector
	inline Vec4Int ZYWZ() const;									//Swizzle to ZYWZ Vector
	inline Vec4Int ZYWW() const;									//Swizzle to ZYWW Vector
	inline Vec4Int ZZXX() const;									//Swizzle to ZZXX Vector
	inline Vec4Int ZZXY() const;									//Swizzle to ZZXY Vector
	inline Vec4Int ZZXZ() const;									//Swizzle to ZZXZ Vector
	inline Vec4Int ZZXW() const;									//Swizzle to ZZXW Vector
	inline Vec4Int ZZYX() const;									//Swizzle to ZZYX Vector
	inline Vec4Int ZZYY() const;									//Swizzle to ZZYY Vector
	inline Vec4Int ZZYZ() const;									//Swizzle to ZZYZ Vector
	inline Vec4Int ZZYW() const;									//Swizzle to ZZYW Vector
	inline Vec4Int ZZZX() const;									//Swizzle to ZZZX Vector
	inline Vec4Int ZZZY() const;									//Swizzle to ZZZY Vector
	inline Vec4Int ZZZZ() const;									//Swizzle to ZZZZ Vector
	inline Vec4Int ZZZW() const;									//Swizzle to ZZZW Vector
	inline Vec4Int ZZWX() const;									//Swizzle to ZZWX Vector
	inline Vec4Int ZZWY() const;									//Swizzle to ZZWY Vector
	inline Vec4Int ZZWZ() const;									//Swizzle to ZZWZ Vector
	inline Vec4Int ZZWW() const;									//Swizzle to ZZWW Vector
	inline Vec4Int ZWXX() const;									//Swizzle to ZWXX Vector
	inline Vec4Int ZWXY() const;									//Swizzle to ZWXY Vector
	inline Vec4Int ZWXZ() const;									//Swizzle to ZWXZ Vector
	inline Vec4Int ZWXW() const;									//Swizzle to ZWXW Vector
	inline Vec4Int ZWYX() const;									//Swizzle to ZWYX Vector
	inline Vec4Int ZWYY() const;									//Swizzle to ZWYY Vector
	inline Vec4Int ZWYZ() const;									//Swizzle to ZWYZ Vector
	inline Vec4Int ZWYW() const;									//Swizzle to ZWYW Vector
	inline Vec4Int ZWZX() const;									//Swizzle to ZWZX Vector
	inline Vec4Int ZWZY() const;									//Swizzle to ZWZY Vector
	inline Vec4Int ZWZZ() const;									//Swizzle to ZWZZ Vector
	inline Vec4Int ZWZW() const;									//Swizzle to ZWZW Vector
	inline Vec4Int ZWWX() const;									//Swizzle to ZWWX Vector
	inline Vec4Int ZWWY() const;									//Swizzle to ZWWY Vector
	inline Vec4Int ZWWZ() const;									//Swizzle to ZWWZ Vector
	inline Vec4Int ZWWW() const;									//Swizzle to ZWWW Vector
	inline Vec4Int WXXX() const;									//Swizzle to WXXX Vector
	inline Vec4Int WXXY() const;									//Swizzle to WXXY Vector
	inline Vec4Int WXXZ() const;									//Swizzle to WXXZ Vector
	inline Vec4Int WXXW() const;									//Swizzle to WXXW Vector
	inline Vec4Int WXYX() const;									//Swizzle to WXYX Vector
	inline Vec4Int WXYY() const;									//Swizzle to WXYY Vector
	inline Vec4Int WXYZ() const;									//Swizzle to WXYZ Vector
	inline Vec4Int WXYW() const;									//Swizzle to WXYW Vector
	inline Vec4Int WXZX() const;									//Swizzle to WXZX Vector
	inline Vec4Int WXZY() const;									//Swizzle to WXZY Vector
	inline Vec4Int WXZZ() const;									//Swizzle to WXZZ Vector
	inline Vec4Int WXZW() const;									//Swizzle to WXZW Vector
	inline Vec4Int WXWX() const;									//Swizzle to WXWX Vector
	inline Vec4Int WXWY() const;									//Swizzle to WXWY Vector
	inline Vec4Int WXWZ() const;									//Swizzle to WXWZ Vector
	inline Vec4Int WXWW() const;									//Swizzle to WXWW Vector
	inline Vec4Int WYXX() const;									//Swizzle to WYXX Vector
	inline Vec4Int WYXY() const;									//Swizzle to WYXY Vector
	inline Vec4Int WYXZ() const;									//Swizzle to WYXZ Vector
	inline Vec4Int WYXW() const;									//Swizzle to WYXW Vector
	inline Vec4Int WYYX() const;									//Swizzle to WYYX Vector
	inline Vec4Int WYYY() const;									//Swizzle to WYYY Vector
	inline Vec4Int WYYZ() const;									//Swizzle to WYYZ Vector
	inline Vec4Int WYYW() const;									//Swizzle to WYYW Vector
	inline Vec4Int WYZX() const;									//Swizzle to WYZX Vector
	inline Vec4Int WYZY() const;									//Swizzle to WYZY Vector
	inline Vec4Int WYZZ() const;									//Swizzle to WYZZ Vector
	inline Vec4Int WYZW() const;									//Swizzle to WYZW Vector
	inline Vec4Int WYWX() const;									//Swizzle to WYWX Vector
	inline Vec4Int WYWY() const;									//Swizzle to WYWY Vector
	inline Vec4Int WYWZ() const;									//Swizzle to WYWZ Vector
	inline Vec4Int WYWW() const;									//Swizzle to WYWW Vector
	inline Vec4Int WZXX() const;									//Swizzle to WZXX Vector
	inline Vec4Int WZXY() const;									//Swizzle to WZXY Vector
	inline Vec4Int WZXZ() const;									//Swizzle to WZXZ Vector
	inline Vec4Int WZXW() const;									//Swizzle to WZXW Vector
	inline Vec4Int WZYX() const;									//Swizzle to WZYX Vector
	inline Vec4Int WZYY() const;									//Swizzle to WZYY Vector
	inline Vec4Int WZYZ() const;									//Swizzle to WZYZ Vector
	inline Vec4Int WZYW() const;									//Swizzle to WZYW Vector
	inline Vec4Int WZZX() const;									//Swizzle to WZZX Vector
	inline Vec4Int WZZY() const;									//Swizzle to WZZY Vector
	inline Vec4Int WZZZ() const;									//Swizzle to WZZZ Vector
	inline Vec4Int WZZW() const;									//Swizzle to WZZW Vector
	inline Vec4Int WZWX() const;									//Swizzle to WZWX Vector
	inline Vec4Int WZWY() const;									//Swizzle to WZWY Vector
	inline Vec4Int WZWZ() const;									//Swizzle to WZWZ Vector
	inline Vec4Int WZWW() const;									//Swizzle to WZWW Vector
	inline Vec4Int WWXX() const;									//Swizzle to WWXX Vector
	inline Vec4Int WWXY() const;									//Swizzle to WWXY Vector
	inline Vec4Int WWXZ() const;									//Swizzle to WWXZ Vector
	inline Vec4Int WWXW() const;									//Swizzle to WWXW Vector
	inline Vec4Int WWYX() const;									//Swizzle to WWYX Vector
	inline Vec4Int WWYY() const;									//Swizzle to WWYY Vector
	inline Vec4Int WWYZ() const;									//Swizzle to WWYZ Vector
	inline Vec4Int WWYW() const;									//Swizzle to WWYW Vector
	inline Vec4Int WWZX() const;									//Swizzle to WWZX Vector
	inline Vec4Int WWZY() const;									//Swizzle to WWZY Vector
	inline Vec4Int WWZZ() const;									//Swizzle to WWZZ Vector
	inline Vec4Int WWZW() const;									//Swizzle to WWZW Vector
	inline Vec4Int WWWX() const;									//Swizzle to WWWX Vector
	inline Vec4Int WWWY() const;									//Swizzle to WWWY Vector
	inline Vec4Int WWWZ() const;									//Swizzle to WWWZ Vector
	inline Vec4Int WWWW() const;									//Swizzle to WWWW Vector
	inline Vec4Int RRRR() const;									//Swizzle to RRRR Vector
	inline Vec4Int RRRG() const;									//Swizzle to RRRG Vector
	inline Vec4Int RRRB() const;									//Swizzle to RRRB Vector
	inline Vec4Int RRRA() const;									//Swizzle to RRRA Vector
	inline Vec4Int RRGR() const;									//Swizzle to RRGR Vector
	inline Vec4Int RRGG() const;									//Swizzle to RRGG Vector
	inline Vec4Int RRGB() const;									//Swizzle to RRGB Vector
	inline Vec4Int RRGA() const;									//Swizzle to RRGA Vector
	inline Vec4Int RRBR() const;									//Swizzle to RRBR Vector
	inline Vec4Int RRBG() const;									//Swizzle to RRBG Vector
	inline Vec4Int RRBB() const;									//Swizzle to RRBB Vector
	inline Vec4Int RRBA() const;									//Swizzle to RRBA Vector
	inline Vec4Int RRAR() const;									//Swizzle to RRAR Vector
	inline Vec4Int RRAG() const;									//Swizzle to RRAG Vector
	inline Vec4Int RRAB() const;									//Swizzle to RRAB Vector
	inline Vec4Int RRAA() const;									//Swizzle to RRAA Vector
	inline Vec4Int RGRR() const;									//Swizzle to RGRR Vector
	inline Vec4Int RGRG() const;									//Swizzle to RGRG Vector
	inline Vec4Int RGRB() const;									//Swizzle to RGRB Vector
	inline Vec4Int RGRA() const;									//Swizzle to RGRA Vector
	inline Vec4Int RGGR() const;									//Swizzle to RGGR Vector
	inline Vec4Int RGGG() const;									//Swizzle to RGGG Vector
	inline Vec4Int RGGB() const;									//Swizzle to RGGB Vector
	inline Vec4Int RGGA() const;									//Swizzle to RGGA Vector
	inline Vec4Int RGBR() const;									//Swizzle to RGBR Vector
	inline Vec4Int RGBG() const;									//Swizzle to RGBG Vector
	inline Vec4Int RGBB() const;									//Swizzle to RGBB Vector
	inline Vec4Int RGAR() const;									//Swizzle to RGAR Vector
	inline Vec4Int RGAG() const;									//Swizzle to RGAG Vector
	inline Vec4Int RGAB() const;									//Swizzle to RGAB Vector
	inline Vec4Int RGAA() const;									//Swizzle to RGAA Vector
	inline Vec4Int RBRR() const;									//Swizzle to RBRR Vector
	inline Vec4Int RBRG() const;									//Swizzle to RBRG Vector
	inline Vec4Int RBRB() const;									//Swizzle to RBRB Vector
	inline Vec4Int RBRA() const;									//Swizzle to RBRA Vector
	inline Vec4Int RBGR() const;									//Swizzle to RBGR Vector
	inline Vec4Int RBGG() const;									//Swizzle to RBGG Vector
	inline Vec4Int RBGB() const;									//Swizzle to RBGB Vector
	inline Vec4Int RBGA() const;									//Swizzle to RBGA Vector
	inline Vec4Int RBBR() const;									//Swizzle to RBBR Vector
	inline Vec4Int RBBG() const;									//Swizzle to RBBG Vector
	inline Vec4Int RBBB() const;									//Swizzle to RBBB Vector
	inline Vec4Int RBBA() const;									//Swizzle to RBBA Vector
	inline Vec4Int RBAR() const;									//Swizzle to RBAR Vector
	inline Vec4Int RBAG() const;									//Swizzle to RBAG Vector
	inline Vec4Int RBAB() const;									//Swizzle to RBAB Vector
	inline Vec4Int RBAA() const;									//Swizzle to RBAA Vector
	inline Vec4Int RARR() const;									//Swizzle to RARR Vector
	inline Vec4Int RARG() const;									//Swizzle to RARG Vector
	inline Vec4Int RARB() const;									//Swizzle to RARB Vector
	inline Vec4Int RARA() const;									//Swizzle to RARA Vector
	inline Vec4Int RAGR() const;									//Swizzle to RAGR Vector
	inline Vec4Int RAGG() const;									//Swizzle to RAGG Vector
	inline Vec4Int RAGB() const;									//Swizzle to RAGB Vector
	inline Vec4Int RAGA() const;									//Swizzle to RAGA Vector
	inline Vec4Int RABR() const;									//Swizzle to RABR Vector
	inline Vec4Int RABG() const;									//Swizzle to RABG Vector
	inline Vec4Int RABB() const;									//Swizzle to RABB Vector
	inline Vec4Int RABA() const;									//Swizzle to RABA Vector
	inline Vec4Int RAAR() const;									//Swizzle to RAAR Vector
	inline Vec4Int RAAG() const;									//Swizzle to RAAG Vector
	inline Vec4Int RAAB() const;									//Swizzle to RAAB Vector
	inline Vec4Int RAAA() const;									//Swizzle to RAAA Vector
	inline Vec4Int GRRR() const;									//Swizzle to GRRR Vector
	inline Vec4Int GRRG() const;									//Swizzle to GRRG Vector
	inline Vec4Int GRRB() const;									//Swizzle to GRRB Vector
	inline Vec4Int GRRA() const;									//Swizzle to GRRA Vector
	inline Vec4Int GRGR() const;									//Swizzle to GRGR Vector
	inline Vec4Int GRGG() const;									//Swizzle to GRGG Vector
	inline Vec4Int GRGB() const;									//Swizzle to GRGB Vector
	inline Vec4Int GRGA() const;									//Swizzle to GRGA Vector
	inline Vec4Int GRBR() const;									//Swizzle to GRBR Vector
	inline Vec4Int GRBG() const;									//Swizzle to GRBG Vector
	inline Vec4Int GRBB() const;									//Swizzle to GRBB Vector
	inline Vec4Int GRBA() const;									//Swizzle to GRBA Vector
	inline Vec4Int GRAR() const;									//Swizzle to GRAR Vector
	inline Vec4Int GRAG() const;									//Swizzle to GRAG Vector
	inline Vec4Int GRAB() const;									//Swizzle to GRAB Vector
	inline Vec4Int GRAA() const;									//Swizzle to GRAA Vector
	inline Vec4Int GGRR() const;									//Swizzle to GGRR Vector
	inline Vec4Int GGRG() const;									//Swizzle to GGRG Vector
	inline Vec4Int GGRB() const;									//Swizzle to GGRB Vector
	inline Vec4Int GGRA() const;									//Swizzle to GGRA Vector
	inline Vec4Int GGGR() const;									//Swizzle to GGGR Vector
	inline Vec4Int GGGG() const;									//Swizzle to GGGG Vector
	inline Vec4Int GGGB() const;									//Swizzle to GGGB Vector
	inline Vec4Int GGGA() const;									//Swizzle to GGGA Vector
	inline Vec4Int GGBR() const;									//Swizzle to GGBR Vector
	inline Vec4Int GGBG() const;									//Swizzle to GGBG Vector
	inline Vec4Int GGBB() const;									//Swizzle to GGBB Vector
	inline Vec4Int GGBA() const;									//Swizzle to GGBA Vector
	inline Vec4Int GGAR() const;									//Swizzle to GGAR Vector
	inline Vec4Int GGAG() const;									//Swizzle to GGAG Vector
	inline Vec4Int GGAB() const;									//Swizzle to GGAB Vector
	inline Vec4Int GGAA() const;									//Swizzle to GGAA Vector
	inline Vec4Int GBRR() const;									//Swizzle to GBRR Vector
	inline Vec4Int GBRG() const;									//Swizzle to GBRG Vector
	inline Vec4Int GBRB() const;									//Swizzle to GBRB Vector
	inline Vec4Int GBRA() const;									//Swizzle to GBRA Vector
	inline Vec4Int GBGR() const;									//Swizzle to GBGR Vector
	inline Vec4Int GBGG() const;									//Swizzle to GBGG Vector
	inline Vec4Int GBGB() const;									//Swizzle to GBGB Vector
	inline Vec4Int GBGA() const;									//Swizzle to GBGA Vector
	inline Vec4Int GBBR() const;									//Swizzle to GBBR Vector
	inline Vec4Int GBBG() const;									//Swizzle to GBBG Vector
	inline Vec4Int GBBB() const;									//Swizzle to GBBB Vector
	inline Vec4Int GBBA() const;									//Swizzle to GBBA Vector
	inline Vec4Int GBAR() const;									//Swizzle to GBAR Vector
	inline Vec4Int GBAG() const;									//Swizzle to GBAG Vector
	inline Vec4Int GBAB() const;									//Swizzle to GBAB Vector
	inline Vec4Int GBAA() const;									//Swizzle to GBAA Vector
	inline Vec4Int GARR() const;									//Swizzle to GARR Vector
	inline Vec4Int GARG() const;									//Swizzle to GARG Vector
	inline Vec4Int GARB() const;									//Swizzle to GARB Vector
	inline Vec4Int GARA() const;									//Swizzle to GARA Vector
	inline Vec4Int GAGR() const;									//Swizzle to GAGR Vector
	inline Vec4Int GAGG() const;									//Swizzle to GAGG Vector
	inline Vec4Int GAGB() const;									//Swizzle to GAGB Vector
	inline Vec4Int GAGA() const;									//Swizzle to GAGA Vector
	inline Vec4Int GABR() const;									//Swizzle to GABR Vector
	inline Vec4Int GABG() const;									//Swizzle to GABG Vector
	inline Vec4Int GABB() const;									//Swizzle to GABB Vector
	inline Vec4Int GABA() const;									//Swizzle to GABA Vector
	inline Vec4Int GAAR() const;									//Swizzle to GAAR Vector
	inline Vec4Int GAAG() const;									//Swizzle to GAAG Vector
	inline Vec4Int GAAB() const;									//Swizzle to GAAB Vector
	inline Vec4Int GAAA() const;									//Swizzle to GAAA Vector
	inline Vec4Int BRRR() const;									//Swizzle to BRRR Vector
	inline Vec4Int BRRG() const;									//Swizzle to BRRG Vector
	inline Vec4Int BRRB() const;									//Swizzle to BRRB Vector
	inline Vec4Int BRRA() const;									//Swizzle to BRRA Vector
	inline Vec4Int BRGR() const;									//Swizzle to BRGR Vector
	inline Vec4Int BRGG() const;									//Swizzle to BRGG Vector
	inline Vec4Int BRGB() const;									//Swizzle to BRGB Vector
	inline Vec4Int BRGA() const;									//Swizzle to BRGA Vector
	inline Vec4Int BRBR() const;									//Swizzle to BRBR Vector
	inline Vec4Int BRBG() const;									//Swizzle to BRBG Vector
	inline Vec4Int BRBB() const;									//Swizzle to BRBB Vector
	inline Vec4Int BRBA() const;									//Swizzle to BRBA Vector
	inline Vec4Int BRAR() const;									//Swizzle to BRAR Vector
	inline Vec4Int BRAG() const;									//Swizzle to BRAG Vector
	inline Vec4Int BRAB() const;									//Swizzle to BRAB Vector
	inline Vec4Int BRAA() const;									//Swizzle to BRAA Vector
	inline Vec4Int BGRR() const;									//Swizzle to BGRR Vector
	inline Vec4Int BGRG() const;									//Swizzle to BGRG Vector
	inline Vec4Int BGRB() const;									//Swizzle to BGRB Vector
	inline Vec4Int BGRA() const;									//Swizzle to BGRA Vector
	inline Vec4Int BGGR() const;									//Swizzle to BGGR Vector
	inline Vec4Int BGGG() const;									//Swizzle to BGGG Vector
	inline Vec4Int BGGB() const;									//Swizzle to BGGB Vector
	inline Vec4Int BGGA() const;									//Swizzle to BGGA Vector
	inline Vec4Int BGBR() const;									//Swizzle to BGBR Vector
	inline Vec4Int BGBG() const;									//Swizzle to BGBG Vector
	inline Vec4Int BGBB() const;									//Swizzle to BGBB Vector
	inline Vec4Int BGBA() const;									//Swizzle to BGBA Vector
	inline Vec4Int BGAR() const;									//Swizzle to BGAR Vector
	inline Vec4Int BGAG() const;									//Swizzle to BGAG Vector
	inline Vec4Int BGAB() const;									//Swizzle to BGAB Vector
	inline Vec4Int BGAA() const;									//Swizzle to BGAA Vector
	inline Vec4Int BBRR() const;									//Swizzle to BBRR Vector
	inline Vec4Int BBRG() const;									//Swizzle to BBRG Vector
	inline Vec4Int BBRB() const;									//Swizzle to BBRB Vector
	inline Vec4Int BBRA() const;									//Swizzle to BBRA Vector
	inline Vec4Int BBGR() const;									//Swizzle to BBGR Vector
	inline Vec4Int BBGG() const;									//Swizzle to BBGG Vector
	inline Vec4Int BBGB() const;									//Swizzle to BBGB Vector
	inline Vec4Int BBGA() const;									//Swizzle to BBGA Vector
	inline Vec4Int BBBR() const;									//Swizzle to BBBR Vector
	inline Vec4Int BBBG() const;									//Swizzle to BBBG Vector
	inline Vec4Int BBBB() const;									//Swizzle to BBBB Vector
	inline Vec4Int BBBA() const;									//Swizzle to BBBA Vector
	inline Vec4Int BBAR() const;									//Swizzle to BBAR Vector
	inline Vec4Int BBAG() const;									//Swizzle to BBAG Vector
	inline Vec4Int BBAB() const;									//Swizzle to BBAB Vector
	inline Vec4Int BBAA() const;									//Swizzle to BBAA Vector
	inline Vec4Int BARR() const;									//Swizzle to BARR Vector
	inline Vec4Int BARG() const;									//Swizzle to BARG Vector
	inline Vec4Int BARB() const;									//Swizzle to BARB Vector
	inline Vec4Int BARA() const;									//Swizzle to BARA Vector
	inline Vec4Int BAGR() const;									//Swizzle to BAGR Vector
	inline Vec4Int BAGG() const;									//Swizzle to BAGG Vector
	inline Vec4Int BAGB() const;									//Swizzle to BAGB Vector
	inline Vec4Int BAGA() const;									//Swizzle to BAGA Vector
	inline Vec4Int BABR() const;									//Swizzle to BABR Vector
	inline Vec4Int BABG() const;									//Swizzle to BABG Vector
	inline Vec4Int BABB() const;									//Swizzle to BABB Vector
	inline Vec4Int BABA() const;									//Swizzle to BABA Vector
	inline Vec4Int BAAR() const;									//Swizzle to BAAR Vector
	inline Vec4Int BAAG() const;									//Swizzle to BAAG Vector
	inline Vec4Int BAAB() const;									//Swizzle to BAAB Vector
	inline Vec4Int BAAA() const;									//Swizzle to BAAA Vector
	inline Vec4Int ARRR() const;									//Swizzle to ARRR Vector
	inline Vec4Int ARRG() const;									//Swizzle to ARRG Vector
	inline Vec4Int ARRB() const;									//Swizzle to ARRB Vector
	inline Vec4Int ARRA() const;									//Swizzle to ARRA Vector
	inline Vec4Int ARGR() const;									//Swizzle to ARGR Vector
	inline Vec4Int ARGG() const;									//Swizzle to ARGG Vector
	inline Vec4Int ARGB() const;									//Swizzle to ARGB Vector
	inline Vec4Int ARGA() const;									//Swizzle to ARGA Vector
	inline Vec4Int ARBR() const;									//Swizzle to ARBR Vector
	inline Vec4Int ARBG() const;									//Swizzle to ARBG Vector
	inline Vec4Int ARBB() const;									//Swizzle to ARBB Vector
	inline Vec4Int ARBA() const;									//Swizzle to ARBA Vector
	inline Vec4Int ARAR() const;									//Swizzle to ARAR Vector
	inline Vec4Int ARAG() const;									//Swizzle to ARAG Vector
	inline Vec4Int ARAB() const;									//Swizzle to ARAB Vector
	inline Vec4Int ARAA() const;									//Swizzle to ARAA Vector
	inline Vec4Int AGRR() const;									//Swizzle to AGRR Vector
	inline Vec4Int AGRG() const;									//Swizzle to AGRG Vector
	inline Vec4Int AGRB() const;									//Swizzle to AGRB Vector
	inline Vec4Int AGRA() const;									//Swizzle to AGRA Vector
	inline Vec4Int AGGR() const;									//Swizzle to AGGR Vector
	inline Vec4Int AGGG() const;									//Swizzle to AGGG Vector
	inline Vec4Int AGGB() const;									//Swizzle to AGGB Vector
	inline Vec4Int AGGA() const;									//Swizzle to AGGA Vector
	inline Vec4Int AGBR() const;									//Swizzle to AGBR Vector
	inline Vec4Int AGBG() const;									//Swizzle to AGBG Vector
	inline Vec4Int AGBB() const;									//Swizzle to AGBB Vector
	inline Vec4Int AGBA() const;									//Swizzle to AGBA Vector
	inline Vec4Int AGAR() const;									//Swizzle to AGAR Vector
	inline Vec4Int AGAG() const;									//Swizzle to AGAG Vector
	inline Vec4Int AGAB() const;									//Swizzle to AGAB Vector
	inline Vec4Int AGAA() const;									//Swizzle to AGAA Vector
	inline Vec4Int ABRR() const;									//Swizzle to ABRR Vector
	inline Vec4Int ABRG() const;									//Swizzle to ABRG Vector
	inline Vec4Int ABRB() const;									//Swizzle to ABRB Vector
	inline Vec4Int ABRA() const;									//Swizzle to ABRA Vector
	inline Vec4Int ABGR() const;									//Swizzle to ABGR Vector
	inline Vec4Int ABGG() const;									//Swizzle to ABGG Vector
	inline Vec4Int ABGB() const;									//Swizzle to ABGB Vector
	inline Vec4Int ABGA() const;									//Swizzle to ABGA Vector
	inline Vec4Int ABBR() const;									//Swizzle to ABBR Vector
	inline Vec4Int ABBG() const;									//Swizzle to ABBG Vector
	inline Vec4Int ABBB() const;									//Swizzle to ABBB Vector
	inline Vec4Int ABBA() const;									//Swizzle to ABBA Vector
	inline Vec4Int ABAR() const;									//Swizzle to ABAR Vector
	inline Vec4Int ABAG() const;									//Swizzle to ABAG Vector
	inline Vec4Int ABAB() const;									//Swizzle to ABAB Vector
	inline Vec4Int ABAA() const;									//Swizzle to ABAA Vector
	inline Vec4Int AARR() const;									//Swizzle to AARR Vector
	inline Vec4Int AARG() const;									//Swizzle to AARG Vector
	inline Vec4Int AARB() const;									//Swizzle to AARB Vector
	inline Vec4Int AARA() const;									//Swizzle to AARA Vector
	inline Vec4Int AAGR() const;									//Swizzle to AAGR Vector
	inline Vec4Int AAGG() const;									//Swizzle to AAGG Vector
	inline Vec4Int AAGB() const;									//Swizzle to AAGB Vector
	inline Vec4Int AAGA() const;									//Swizzle to AAGA Vector
	inline Vec4Int AABR() const;									//Swizzle to AABR Vector
	inline Vec4Int AABG() const;									//Swizzle to AABG Vector
	inline Vec4Int AABB() const;									//Swizzle to AABB Vector
	inline Vec4Int AABA() const;									//Swizzle to AABA Vector
	inline Vec4Int AAAR() const;									//Swizzle to AAAR Vector
	inline Vec4Int AAAG() const;									//Swizzle to AAAG Vector
	inline Vec4Int AAAB() const;									//Swizzle to AAAB Vector
	inline Vec4Int AAAA() const;									//Swizzle to AAAA Vector
};

#pragma endregion

#endif