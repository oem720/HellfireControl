#pragma once

#pragma warning(disable : 4556)

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

#define HC_SHUFFLE2F(_vec, _x, _y) Vec2F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3F(_vec, _x, _y, _z) Vec3F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4F(_vec, _x, _y, _z, _w) Vec4F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))

#define HC_SHUFFLE2D(_vec, _x, _y)  Vec2D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3D(_vec, _x, _y, _z) Vec3D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4D(_vec, _x, _y, _z, _w) Vec4D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_w, _z, _y, _x)))

#define HC_SHUFFLE2I(_vec, _x, _y) Vec2I(_mm_shuffle_epi32((_vec).m_iVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3I(_vec, _x, _y, _z) Vec3I(_mm_shuffle_epi32((_vec).m_iVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4I(_vec, _x, _y, _z, _w) Vec4I(_mm_shuffle_epi32((_vec).m_iVec, _MM_SHUFFLE(_w, _z, _y, _x)))

#pragma region VectorHelperTypedefs

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

#pragma endregion

struct Vec2F {
	__m128 m_fVec;

	HC_INLINE Vec2F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit Vec2F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec2F(float _fX, float _fY) { m_fVec = _mm_set_ps(_fY, _fY, _fY, _fX); }
	HC_INLINE explicit Vec2F(int _iX, int _iY) { m_fVec = _mm_set_ps(static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE explicit Vec2F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
};

struct Vec3F {
	__m128 m_fVec;

	HC_INLINE Vec3F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit Vec3F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec3F(float _fX, float _fY, float _fZ) { m_fVec = _mm_set_ps(_fZ, _fZ, _fY, _fX); }
	HC_INLINE explicit Vec3F(int _iX, int _iY, int _iZ) { m_fVec = _mm_set_ps(static_cast<float>(_iZ), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE explicit Vec3F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetZ(float _fZ) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fZ)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetB(float _fB) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fB)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F ZZ() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F XY() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F XZ() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F YZ() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F ZX() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F ZY() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F BB() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F RG() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F RB() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F GB() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F BR() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F BG() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec3F XXX() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F XXY() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F XXZ() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F XYX() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F XYY() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F XZX() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F XZY() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F XZZ() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F YXX() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F YXY() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F YXZ() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F YYX() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F YYY() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F YYZ() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F YZX() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F YZY() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F YZZ() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F ZXX() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F ZXY() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F ZXZ() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F ZYX() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F ZYY() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F ZYZ() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F ZZX() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F ZZY() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F ZZZ() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F RRR() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F RRG() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F RRB() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F RGR() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F RGG() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F RBR() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F RBG() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F RBB() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F GRR() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F GRG() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F GRB() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F GGR() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F GGG() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F GGB() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F GBR() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F GBG() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F GBB() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F BRR() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F BRG() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F BRB() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F BGR() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F BGG() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F BGB() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F BBR() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F BBG() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F BBB() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
};

struct Vec4F {
	__m128 m_fVec;

	HC_INLINE Vec4F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit Vec4F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec4F(float _fX, float _fY, float _fZ, float _fW) { m_fVec = _mm_set_ps(_fW, _fZ, _fY, _fX); }
	HC_INLINE explicit Vec4F(int _iX, int _iY, int _iZ, int _iW) { m_fVec = _mm_set_ps(static_cast<float>(_iW), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iZ)); }
	HC_INLINE explicit Vec4F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float W() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE float R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float A() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetZ(float _fZ) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fZ)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetW(float _fW) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fW)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(0, 2, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetB(float _fB) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fB)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void SetA(float _fA) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fA)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(0, 2, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F ZZ() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F WW() const { return HC_SHUFFLE2F(*this, 3, 3); }
	HC_INLINE Vec2F XY() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F XZ() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F XW() const { return HC_SHUFFLE2F(*this, 0, 3); }
	HC_INLINE Vec2F YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F YZ() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F YW() const { return HC_SHUFFLE2F(*this, 1, 3); }
	HC_INLINE Vec2F ZX() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F ZY() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F ZW() const { return HC_SHUFFLE2F(*this, 2, 3); }
	HC_INLINE Vec2F WX() const { return HC_SHUFFLE2F(*this, 3, 0); }
	HC_INLINE Vec2F WY() const { return HC_SHUFFLE2F(*this, 3, 1); }
	HC_INLINE Vec2F WZ() const { return HC_SHUFFLE2F(*this, 3, 2); }
	HC_INLINE Vec2F RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F BB() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F AA() const { return HC_SHUFFLE2F(*this, 3, 3); }
	HC_INLINE Vec2F RG() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F RB() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F RA() const { return HC_SHUFFLE2F(*this, 0, 3); }
	HC_INLINE Vec2F GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F GB() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F GA() const { return HC_SHUFFLE2F(*this, 1, 3); }
	HC_INLINE Vec2F BR() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F BG() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F BA() const { return HC_SHUFFLE2F(*this, 2, 3); }
	HC_INLINE Vec2F AR() const { return HC_SHUFFLE2F(*this, 3, 0); }
	HC_INLINE Vec2F AG() const { return HC_SHUFFLE2F(*this, 3, 1); }
	HC_INLINE Vec2F AB() const { return HC_SHUFFLE2F(*this, 3, 2); }
	HC_INLINE Vec3F XXX() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F XXY() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F XXZ() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F XXW() const { return HC_SHUFFLE3F(*this, 0, 0, 3); }
	HC_INLINE Vec3F XYX() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F XYY() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F XYZ() const { return HC_SHUFFLE3F(*this, 0, 1, 2); }
	HC_INLINE Vec3F XYW() const { return HC_SHUFFLE3F(*this, 0, 1, 3); }
	HC_INLINE Vec3F XZX() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F XZY() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F XZZ() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F XZW() const { return HC_SHUFFLE3F(*this, 0, 2, 3); }
	HC_INLINE Vec3F XWX() const { return HC_SHUFFLE3F(*this, 0, 3, 0); }
	HC_INLINE Vec3F XWY() const { return HC_SHUFFLE3F(*this, 0, 3, 1); }
	HC_INLINE Vec3F XWZ() const { return HC_SHUFFLE3F(*this, 0, 3, 2); }
	HC_INLINE Vec3F XWW() const { return HC_SHUFFLE3F(*this, 0, 3, 3); }
	HC_INLINE Vec3F YXX() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F YXY() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F YXZ() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F YXW() const { return HC_SHUFFLE3F(*this, 1, 0, 3); }
	HC_INLINE Vec3F YYX() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F YYY() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F YYZ() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F YYW() const { return HC_SHUFFLE3F(*this, 1, 1, 3); }
	HC_INLINE Vec3F YZX() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F YZY() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F YZZ() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F YZW() const { return HC_SHUFFLE3F(*this, 1, 2, 3); }
	HC_INLINE Vec3F YWX() const { return HC_SHUFFLE3F(*this, 1, 3, 0); }
	HC_INLINE Vec3F YWY() const { return HC_SHUFFLE3F(*this, 1, 3, 1); }
	HC_INLINE Vec3F YWZ() const { return HC_SHUFFLE3F(*this, 1, 3, 2); }
	HC_INLINE Vec3F YWW() const { return HC_SHUFFLE3F(*this, 1, 3, 3); }
	HC_INLINE Vec3F ZXX() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F ZXY() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F ZXZ() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F ZXW() const { return HC_SHUFFLE3F(*this, 2, 0, 3); }
	HC_INLINE Vec3F ZYX() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F ZYY() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F ZYZ() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F ZYW() const { return HC_SHUFFLE3F(*this, 2, 1, 3); }
	HC_INLINE Vec3F ZZX() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F ZZY() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F ZZZ() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F ZZW() const { return HC_SHUFFLE3F(*this, 2, 2, 3); }
	HC_INLINE Vec3F ZWX() const { return HC_SHUFFLE3F(*this, 2, 3, 0); }
	HC_INLINE Vec3F ZWY() const { return HC_SHUFFLE3F(*this, 2, 3, 1); }
	HC_INLINE Vec3F ZWZ() const { return HC_SHUFFLE3F(*this, 2, 3, 2); }
	HC_INLINE Vec3F ZWW() const { return HC_SHUFFLE3F(*this, 2, 3, 3); }
	HC_INLINE Vec3F WXX() const { return HC_SHUFFLE3F(*this, 3, 0, 0); }
	HC_INLINE Vec3F WXY() const { return HC_SHUFFLE3F(*this, 3, 0, 1); }
	HC_INLINE Vec3F WXZ() const { return HC_SHUFFLE3F(*this, 3, 0, 2); }
	HC_INLINE Vec3F WXW() const { return HC_SHUFFLE3F(*this, 3, 0, 3); }
	HC_INLINE Vec3F WYX() const { return HC_SHUFFLE3F(*this, 3, 1, 0); }
	HC_INLINE Vec3F WYY() const { return HC_SHUFFLE3F(*this, 3, 1, 1); }
	HC_INLINE Vec3F WYZ() const { return HC_SHUFFLE3F(*this, 3, 1, 2); }
	HC_INLINE Vec3F WYW() const { return HC_SHUFFLE3F(*this, 3, 1, 3); }
	HC_INLINE Vec3F WZX() const { return HC_SHUFFLE3F(*this, 3, 2, 0); }
	HC_INLINE Vec3F WZY() const { return HC_SHUFFLE3F(*this, 3, 2, 1); }
	HC_INLINE Vec3F WZZ() const { return HC_SHUFFLE3F(*this, 3, 2, 2); }
	HC_INLINE Vec3F WZW() const { return HC_SHUFFLE3F(*this, 3, 2, 3); }
	HC_INLINE Vec3F WWX() const { return HC_SHUFFLE3F(*this, 3, 3, 0); }
	HC_INLINE Vec3F WWY() const { return HC_SHUFFLE3F(*this, 3, 3, 1); }
	HC_INLINE Vec3F WWZ() const { return HC_SHUFFLE3F(*this, 3, 3, 2); }
	HC_INLINE Vec3F WWW() const { return HC_SHUFFLE3F(*this, 3, 3, 3); }
	HC_INLINE Vec3F RRR() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F RRG() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F RRB() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F RRA() const { return HC_SHUFFLE3F(*this, 0, 0, 3); }
	HC_INLINE Vec3F RGR() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F RGG() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F RGA() const { return HC_SHUFFLE3F(*this, 0, 1, 2); }
	HC_INLINE Vec3F RGB() const { return HC_SHUFFLE3F(*this, 0, 1, 3); }
	HC_INLINE Vec3F RBR() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F RBG() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F RBB() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F RBA() const { return HC_SHUFFLE3F(*this, 0, 2, 3); }
	HC_INLINE Vec3F RAR() const { return HC_SHUFFLE3F(*this, 0, 3, 0); }
	HC_INLINE Vec3F RAG() const { return HC_SHUFFLE3F(*this, 0, 3, 1); }
	HC_INLINE Vec3F RAB() const { return HC_SHUFFLE3F(*this, 0, 3, 2); }
	HC_INLINE Vec3F RAA() const { return HC_SHUFFLE3F(*this, 0, 3, 3); }
	HC_INLINE Vec3F GRR() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F GRG() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F GRB() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F GRA() const { return HC_SHUFFLE3F(*this, 1, 0, 3); }
	HC_INLINE Vec3F GGR() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F GGG() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F GGB() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F GGA() const { return HC_SHUFFLE3F(*this, 1, 1, 3); }
	HC_INLINE Vec3F GBR() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F GBG() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F GBB() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F GBA() const { return HC_SHUFFLE3F(*this, 1, 2, 3); }
	HC_INLINE Vec3F GAR() const { return HC_SHUFFLE3F(*this, 1, 3, 0); }
	HC_INLINE Vec3F GAG() const { return HC_SHUFFLE3F(*this, 1, 3, 1); }
	HC_INLINE Vec3F GAB() const { return HC_SHUFFLE3F(*this, 1, 3, 2); }
	HC_INLINE Vec3F GAA() const { return HC_SHUFFLE3F(*this, 1, 3, 3); }
	HC_INLINE Vec3F BRR() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F BRG() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F BRB() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F BRA() const { return HC_SHUFFLE3F(*this, 2, 0, 3); }
	HC_INLINE Vec3F BGR() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F BGG() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F BGB() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F BGA() const { return HC_SHUFFLE3F(*this, 2, 1, 3); }
	HC_INLINE Vec3F BBR() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F BBG() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F BBB() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F BBA() const { return HC_SHUFFLE3F(*this, 2, 2, 3); }
	HC_INLINE Vec3F BAR() const { return HC_SHUFFLE3F(*this, 2, 3, 0); }
	HC_INLINE Vec3F BAG() const { return HC_SHUFFLE3F(*this, 2, 3, 1); }
	HC_INLINE Vec3F BAB() const { return HC_SHUFFLE3F(*this, 2, 3, 2); }
	HC_INLINE Vec3F BAA() const { return HC_SHUFFLE3F(*this, 2, 3, 3); }
	HC_INLINE Vec3F ARR() const { return HC_SHUFFLE3F(*this, 3, 0, 0); }
	HC_INLINE Vec3F ARG() const { return HC_SHUFFLE3F(*this, 3, 0, 1); }
	HC_INLINE Vec3F ARB() const { return HC_SHUFFLE3F(*this, 3, 0, 2); }
	HC_INLINE Vec3F ARA() const { return HC_SHUFFLE3F(*this, 3, 0, 3); }
	HC_INLINE Vec3F AGR() const { return HC_SHUFFLE3F(*this, 3, 1, 0); }
	HC_INLINE Vec3F AGG() const { return HC_SHUFFLE3F(*this, 3, 1, 1); }
	HC_INLINE Vec3F AGB() const { return HC_SHUFFLE3F(*this, 3, 1, 2); }
	HC_INLINE Vec3F AGA() const { return HC_SHUFFLE3F(*this, 3, 1, 3); }
	HC_INLINE Vec3F ABR() const { return HC_SHUFFLE3F(*this, 3, 2, 0); }
	HC_INLINE Vec3F ABG() const { return HC_SHUFFLE3F(*this, 3, 2, 1); }
	HC_INLINE Vec3F ABB() const { return HC_SHUFFLE3F(*this, 3, 2, 2); }
	HC_INLINE Vec3F ABA() const { return HC_SHUFFLE3F(*this, 3, 2, 3); }
	HC_INLINE Vec3F AAR() const { return HC_SHUFFLE3F(*this, 3, 3, 0); }
	HC_INLINE Vec3F AAG() const { return HC_SHUFFLE3F(*this, 3, 3, 1); }
	HC_INLINE Vec3F AAB() const { return HC_SHUFFLE3F(*this, 3, 3, 2); }
	HC_INLINE Vec3F AAA() const { return HC_SHUFFLE3F(*this, 3, 3, 3); }
	HC_INLINE Vec4F XXXX() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4F XXXY() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4F XXXZ() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4F XXXW() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4F XXYX() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4F XXYY() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4F XXYZ() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4F XXYW() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4F XXZX() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4F XXZY() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4F XXZZ() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4F XXZW() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4F XXWX() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4F XXWY() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4F XXWZ() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4F XXWW() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4F XYXX() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4F XYXY() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4F XYXZ() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4F XYXW() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4F XYYX() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4F XYYY() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4F XYYZ() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4F XYYW() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4F XYZX() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4F XYZY() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4F XYZZ() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4F XYWX() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4F XYWY() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4F XYWZ() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4F XYWW() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4F XZXX() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F XZXY() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4F XZXZ() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4F XZXW() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4F XZYX() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4F XZYY() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4F XZYZ() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4F XZYW() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4F XZZX() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4F XZZY() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4F XZZZ() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4F XZZW() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4F XZWX() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F XZWY() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4F XZWZ() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4F XZWW() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4F XWXX() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4F XWXY() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4F XWXZ() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4F XWXW() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4F XWYX() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4F XWYY() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4F XWYZ() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4F XWYW() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4F XWZX() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4F XWZY() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4F XWZZ() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4F XWZW() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4F XWWX() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4F XWWY() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4F XWWZ() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4F XWWW() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4F YXXX() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4F YXXY() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4F YXXZ() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4F YXXW() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4F YXYX() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4F YXYY() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4F YXYZ() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4F YXYW() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4F YXZX() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4F YXZY() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4F YXZZ() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4F YXZW() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4F YXWX() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4F YXWY() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4F YXWZ() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4F YXWW() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4F YYXX() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4F YYXY() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4F YYXZ() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4F YYXW() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4F YYYX() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4F YYYY() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4F YYYZ() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4F YYYW() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4F YYZX() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4F YYZY() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4F YYZZ() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4F YYZW() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4F YYWX() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4F YYWY() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4F YYWZ() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4F YYWW() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4F YZXX() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4F YZXY() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4F YZXZ() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4F YZXW() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4F YZYX() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4F YZYY() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4F YZYZ() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4F YZYW() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4F YZZX() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4F YZZY() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4F YZZZ() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4F YZZW() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4F YZWX() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4F YZWY() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4F YZWZ() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4F YZWW() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4F YWXX() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4F YWXY() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4F YWXZ() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4F YWXW() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4F YWYX() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4F YWYY() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4F YWYZ() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4F YWYW() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4F YWZX() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4F YWZY() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4F YWZZ() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4F YWZW() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4F YWWX() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4F YWWY() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4F YWWZ() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4F YWWW() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4F ZXXX() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4F ZXXY() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4F ZXXZ() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4F ZXXW() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4F ZXYX() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4F ZXYY() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4F ZXYZ() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4F ZXYW() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4F ZXZX() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4F ZXZY() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4F ZXZZ() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4F ZXZW() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4F ZXWX() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4F ZXWY() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4F ZXWZ() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4F ZXWW() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4F ZYXX() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4F ZYXY() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4F ZYXZ() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4F ZYXW() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4F ZYYX() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4F ZYYY() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4F ZYYZ() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4F ZYYW() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4F ZYZX() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4F ZYZY() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4F ZYZZ() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4F ZYZW() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4F ZYWX() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4F ZYWY() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4F ZYWZ() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4F ZYWW() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4F ZZXX() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4F ZZXY() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4F ZZXZ() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4F ZZXW() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4F ZZYX() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4F ZZYY() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4F ZZYZ() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4F ZZYW() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4F ZZZX() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4F ZZZY() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4F ZZZZ() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4F ZZZW() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4F ZZWX() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4F ZZWY() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4F ZZWZ() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4F ZZWW() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4F ZWXX() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4F ZWXY() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4F ZWXZ() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4F ZWXW() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4F ZWYX() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4F ZWYY() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4F ZWYZ() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4F ZWYW() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4F ZWZX() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4F ZWZY() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4F ZWZZ() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4F ZWZW() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4F ZWWX() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4F ZWWY() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4F ZWWZ() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4F ZWWW() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4F WXXX() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4F WXXY() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4F WXXZ() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4F WXXW() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4F WXYX() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4F WXYY() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4F WXYZ() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4F WXYW() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4F WXZX() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4F WXZY() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4F WXZZ() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4F WXZW() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4F WXWX() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4F WXWY() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4F WXWZ() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4F WXWW() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4F WYXX() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4F WYXY() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4F WYXZ() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4F WYXW() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4F WYYX() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4F WYYY() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4F WYYZ() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4F WYYW() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4F WYZX() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4F WYZY() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4F WYZZ() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4F WYZW() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4F WYWX() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4F WYWY() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4F WYWZ() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4F WYWW() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4F WZXX() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4F WZXY() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4F WZXZ() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4F WZXW() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4F WZYX() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4F WZYY() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4F WZYZ() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4F WZYW() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4F WZZX() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4F WZZY() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4F WZZZ() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4F WZZW() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4F WZWX() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4F WZWY() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4F WZWZ() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4F WZWW() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4F WWXX() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4F WWXY() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4F WWXZ() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4F WWXW() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4F WWYX() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4F WWYY() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4F WWYZ() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4F WWYW() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4F WWZX() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4F WWZY() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4F WWZZ() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4F WWZW() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4F WWWX() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4F WWWY() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4F WWWZ() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4F WWWW() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4F RRRR() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4F RRRG() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4F RRRB() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4F RRRA() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4F RRGR() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4F RRGG() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4F RRGB() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4F RRGA() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4F RRBR() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4F RRBG() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4F RRBB() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4F RRBA() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4F RRAR() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4F RRAG() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4F RRAB() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4F RRAA() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4F RGRR() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4F RGRG() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4F RGRB() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4F RGRA() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4F RGGR() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4F RGGG() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4F RGGB() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4F RGGA() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4F RGBR() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4F RGBG() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4F RGBB() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4F RGAR() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4F RGAG() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4F RGAB() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4F RGAA() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4F RBRR() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F RBRG() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4F RBRB() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4F RBRA() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4F RBGR() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4F RBGG() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4F RBGB() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4F RBGA() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4F RBBR() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4F RBBG() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4F RBBB() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4F RBBA() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4F RBAR() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F RBAG() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4F RBAB() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4F RBAA() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4F RARR() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4F RARG() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4F RARB() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4F RARA() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4F RAGR() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4F RAGG() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4F RAGB() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4F RAGA() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4F RABR() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4F RABG() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4F RABB() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4F RABA() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4F RAAR() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4F RAAG() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4F RAAB() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4F RAAA() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4F GRRR() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4F GRRG() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4F GRRB() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4F GRRA() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4F GRGR() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4F GRGG() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4F GRGB() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4F GRGA() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4F GRBR() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4F GRBG() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4F GRBB() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4F GRBA() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4F GRAR() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4F GRAG() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4F GRAB() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4F GRAA() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4F GGRR() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4F GGRG() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4F GGRB() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4F GGRA() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4F GGGR() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4F GGGG() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4F GGGB() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4F GGGA() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4F GGBR() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4F GGBG() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4F GGBB() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4F GGBA() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4F GGAR() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4F GGAG() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4F GGAB() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4F GGAA() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4F GBRR() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4F GBRG() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4F GBRB() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4F GBRA() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4F GBGR() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4F GBGG() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4F GBGB() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4F GBGA() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4F GBBR() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4F GBBG() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4F GBBB() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4F GBBA() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4F GBAR() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4F GBAG() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4F GBAB() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4F GBAA() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4F GARR() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4F GARG() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4F GARB() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4F GARA() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4F GAGR() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4F GAGG() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4F GAGB() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4F GAGA() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4F GABR() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4F GABG() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4F GABB() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4F GABA() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4F GAAR() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4F GAAG() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4F GAAB() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4F GAAA() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4F BRRR() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4F BRRG() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4F BRRB() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4F BRRA() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4F BRGR() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4F BRGG() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4F BRGB() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4F BRGA() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4F BRBR() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4F BRBG() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4F BRBB() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4F BRBA() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4F BRAR() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4F BRAG() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4F BRAB() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4F BRAA() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4F BGRR() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4F BGRG() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4F BGRB() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4F BGRA() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4F BGGR() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4F BGGG() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4F BGGB() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4F BGGA() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4F BGBR() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4F BGBG() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4F BGBB() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4F BGBA() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4F BGAR() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4F BGAG() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4F BGAB() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4F BGAA() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4F BBRR() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4F BBRG() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4F BBRB() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4F BBRA() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4F BBGR() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4F BBGG() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4F BBGB() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4F BBGA() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4F BBBR() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4F BBBG() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4F BBBB() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4F BBBA() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4F BBAR() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4F BBAG() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4F BBAB() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4F BBAA() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4F BARR() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4F BARG() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4F BARB() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4F BARA() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4F BAGR() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4F BAGG() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4F BAGB() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4F BAGA() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4F BABR() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4F BABG() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4F BABB() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4F BABA() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4F BAAR() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4F BAAG() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4F BAAB() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4F BAAA() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4F ARRR() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4F ARRG() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4F ARRB() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4F ARRA() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4F ARGR() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4F ARGG() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4F ARGB() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4F ARGA() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4F ARBR() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4F ARBG() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4F ARBB() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4F ARBA() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4F ARAR() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4F ARAG() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4F ARAB() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4F ARAA() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4F AGRR() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4F AGRG() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4F AGRB() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4F AGRA() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4F AGGR() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4F AGGG() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4F AGGB() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4F AGGA() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4F AGBR() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4F AGBG() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4F AGBB() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4F AGBA() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4F AGAR() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4F AGAG() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4F AGAB() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4F AGAA() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4F ABRR() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4F ABRG() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4F ABRB() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4F ABRA() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4F ABGR() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4F ABGG() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4F ABGB() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4F ABGA() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4F ABBR() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4F ABBG() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4F ABBB() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4F ABBA() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4F ABAR() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4F ABAG() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4F ABAB() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4F ABAA() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4F AARR() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4F AARG() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4F AARB() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4F AARA() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4F AAGR() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4F AAGG() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4F AAGB() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4F AAGA() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4F AABR() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4F AABG() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4F AABB() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4F AABA() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4F AAAR() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4F AAAG() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4F AAAB() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4F AAAA() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 3); }
};

struct Vec2D {
	__m256d m_dVec;

	HC_INLINE Vec2D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit Vec2D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec2D(double _dX, double _dY) { m_dVec = _mm256_set_pd(_dY, _dY, _dY, _dX); }
	HC_INLINE explicit Vec2D(float _fX, float _fY) { m_dVec = _mm256_set_pd(static_cast<double>(_fY), static_cast<double>(_fY), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit Vec2D(int _iX, int _iY) { m_dVec = _mm256_set_pd(static_cast<double>(_iY), static_cast<double>(_iY), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit Vec2D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 2); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 2); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void SetX(double _dX) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dX); }
	HC_INLINE void SetY(double _dY) { m_dVec = _mm256_set_pd(_dY, _dY, _dY, X()); }
	HC_INLINE void SetR(double _dR) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dR); }
	HC_INLINE void SetG(double _dG) { m_dVec = _mm256_set_pd(_dG, _dG, _dG, X()); }
	HC_INLINE Vec2D XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
};

struct Vec3D {
	__m256d m_dVec;

	HC_INLINE Vec3D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit Vec3D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec3D(double _dX, double _dY, double _dZ) { m_dVec = _mm256_set_pd(_dZ, _dZ, _dY, _dX); }
	HC_INLINE explicit Vec3D(float _fX, float _fY, float _fZ) { m_dVec = _mm256_set_pd(static_cast<double>(_fZ), static_cast<double>(_fZ), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit Vec3D(int _iX, int _iY, int _iZ) { m_dVec = _mm256_set_pd(static_cast<double>(_iZ), static_cast<double>(_iZ), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit Vec3D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 3); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 3); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double Z() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double B() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void SetX(double _dX) { m_dVec = _mm256_set_pd(Z(), Z(), Y(), _dX); }
	HC_INLINE void SetY(double _dY) { m_dVec = _mm256_set_pd(Z(), Z(), _dY, X()); }
	HC_INLINE void SetZ(double _dZ) { m_dVec = _mm256_set_pd(_dZ, _dZ, Y(), X()); }
	HC_INLINE void SetR(double _dR) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dR); }
	HC_INLINE void SetG(double _dG) { m_dVec = _mm256_set_pd(Z(), Z(), _dG, X()); }
	HC_INLINE void SetB(double _dB) { m_dVec = _mm256_set_pd(_dB, _dB, Y(), X()); }
	HC_INLINE Vec2D XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D ZZ() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D XY() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D XZ() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D YZ() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D ZX() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D ZY() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D BB() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D RG() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D RB() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D GB() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D BR() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D BG() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec3D XXX() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D XXY() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D XXZ() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D XYX() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D XYY() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D XZX() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D XZY() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D XZZ() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D YXX() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D YXY() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D YXZ() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D YYX() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D YYY() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D YYZ() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D YZX() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D YZY() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D YZZ() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D ZXX() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D ZXY() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D ZXZ() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D ZYX() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D ZYY() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D ZYZ() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D ZZX() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D ZZY() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D ZZZ() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D RRR() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D RRG() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D RRB() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D RGR() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D RGG() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D RBR() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D RBG() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D RBB() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D GRR() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D GRG() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D GRB() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D GGR() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D GGG() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D GGB() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D GBR() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D GBG() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D GBB() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D BRR() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D BRG() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D BRB() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D BGR() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D BGG() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D BGB() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D BBR() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D BBG() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D BBB() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
};

struct Vec4D {
	__m256d m_dVec;

	HC_INLINE Vec4D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit Vec4D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec4D(double _dX, double _dY, double _dZ, double _dA) { m_dVec = _mm256_set_pd(_dA, _dZ, _dY, _dX); }
	HC_INLINE explicit Vec4D(float _fX, float _fY, float _fZ, float _fA) { m_dVec = _mm256_set_pd(static_cast<double>(_fA), static_cast<double>(_fZ), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit Vec4D(int _iX, int _iY, int _iZ, int _iA) { m_dVec = _mm256_set_pd(static_cast<double>(_iA), static_cast<double>(_iZ), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit Vec4D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double Z() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double W() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE double R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double B() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double A() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void SetX(double _dX) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dX); }
	HC_INLINE void SetY(double _dY) { m_dVec = _mm256_set_pd(W(), Z(), _dY, X()); }
	HC_INLINE void SetZ(double _dZ) { m_dVec = _mm256_set_pd(W(), _dZ, Y(), X()); }
	HC_INLINE void SetW(double _dW) { m_dVec = _mm256_set_pd(_dW, Z(), Y(), X()); }
	HC_INLINE void SetR(double _dR) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dR); }
	HC_INLINE void SetG(double _dG) { m_dVec = _mm256_set_pd(W(), Z(), _dG, X()); }
	HC_INLINE void SetB(double _dB) { m_dVec = _mm256_set_pd(W(), _dB, Y(), X()); }
	HC_INLINE void SetA(double _dA) { m_dVec = _mm256_set_pd(_dA, Z(), Y(), X()); }
	HC_INLINE Vec2D XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D ZZ() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D WW() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D XY() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D XZ() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D XW() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D YZ() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D YW() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D ZX() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D ZY() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D ZW() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D WX() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D WY() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D WZ() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec2D RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D BB() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D AA() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D RG() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D RB() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D RA() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D GB() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D GA() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D BR() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D BG() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D BA() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D AR() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D AG() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D AB() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec3D XXX() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D XXY() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D XXZ() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D XXW() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D XYX() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D XYY() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D XYZ() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D XYW() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D XZX() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D XZY() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D XZZ() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D XZW() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D XWX() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D XWY() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D XWZ() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D XWW() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D YXX() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D YXY() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D YXZ() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D YXW() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D YYX() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D YYY() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D YYZ() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D YYW() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D YZX() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D YZY() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D YZZ() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D YZW() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D YWX() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D YWY() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D YWZ() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D YWW() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D ZXX() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D ZXY() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D ZXZ() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D ZXW() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D ZYX() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D ZYY() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D ZYZ() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D ZYW() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D ZZX() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D ZZY() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D ZZZ() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D ZZW() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D ZWX() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D ZWY() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D ZWZ() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D ZWW() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D WXX() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D WXY() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D WXZ() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D WXW() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D WYX() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D WYY() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D WYZ() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D WYW() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D WZX() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D WZY() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D WZZ() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D WZW() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D WWX() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D WWY() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D WWZ() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D WWW() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec3D RRR() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D RRG() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D RRB() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D RRA() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D RGR() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D RGG() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D RGA() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D RGB() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D RBR() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D RBG() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D RBB() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D RBA() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D RAR() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D RAG() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D RAB() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D RAA() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D GRR() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D GRG() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D GRB() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D GRA() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D GGR() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D GGG() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D GGB() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D GGA() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D GBR() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D GBG() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D GBB() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D GBA() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D GAR() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D GAG() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D GAB() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D GAA() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D BRR() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D BRG() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D BRB() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D BRA() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D BGR() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D BGG() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D BGB() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D BGA() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D BBR() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D BBG() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D BBB() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D BBA() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D BAR() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D BAG() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D BAB() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D BAA() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D ARR() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D ARG() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D ARB() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D ARA() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D AGR() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D AGG() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D AGB() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D AGA() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D ABR() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D ABG() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D ABB() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D ABA() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D AAR() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D AAG() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D AAB() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D AAA() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec4D XXXX() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D XXXY() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D XXXZ() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D XXXW() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D XXYX() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D XXYY() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D XXYZ() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D XXYW() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D XXZX() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D XXZY() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D XXZZ() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D XXZW() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D XXWX() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D XXWY() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D XXWZ() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D XXWW() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D XYXX() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D XYXY() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D XYXZ() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D XYXW() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D XYYX() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D XYYY() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D XYYZ() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D XYYW() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D XYZX() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D XYZY() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D XYZZ() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D XYWX() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D XYWY() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D XYWZ() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D XYWW() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D XZXX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D XZXY() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D XZXZ() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D XZXW() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D XZYX() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D XZYY() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D XZYZ() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D XZYW() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D XZZX() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D XZZY() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D XZZZ() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D XZZW() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D XZWX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D XZWY() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D XZWZ() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D XZWW() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D XWXX() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D XWXY() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D XWXZ() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D XWXW() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D XWYX() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D XWYY() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D XWYZ() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D XWYW() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D XWZX() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D XWZY() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D XWZZ() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D XWZW() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D XWWX() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D XWWY() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D XWWZ() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D XWWW() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D YXXX() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D YXXY() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D YXXZ() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D YXXW() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D YXYX() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D YXYY() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D YXYZ() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D YXYW() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D YXZX() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D YXZY() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D YXZZ() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D YXZW() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D YXWX() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D YXWY() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D YXWZ() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D YXWW() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D YYXX() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D YYXY() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D YYXZ() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D YYXW() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D YYYX() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D YYYY() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D YYYZ() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D YYYW() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D YYZX() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D YYZY() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D YYZZ() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D YYZW() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D YYWX() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D YYWY() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D YYWZ() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D YYWW() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D YZXX() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D YZXY() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D YZXZ() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D YZXW() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D YZYX() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D YZYY() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D YZYZ() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D YZYW() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D YZZX() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D YZZY() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D YZZZ() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D YZZW() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D YZWX() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D YZWY() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D YZWZ() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D YZWW() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D YWXX() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D YWXY() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D YWXZ() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D YWXW() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D YWYX() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D YWYY() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D YWYZ() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D YWYW() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D YWZX() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D YWZY() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D YWZZ() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D YWZW() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D YWWX() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D YWWY() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D YWWZ() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D YWWW() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D ZXXX() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D ZXXY() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D ZXXZ() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D ZXXW() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D ZXYX() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D ZXYY() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D ZXYZ() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D ZXYW() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D ZXZX() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D ZXZY() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D ZXZZ() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D ZXZW() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D ZXWX() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D ZXWY() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D ZXWZ() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D ZXWW() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D ZYXX() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D ZYXY() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D ZYXZ() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D ZYXW() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D ZYYX() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D ZYYY() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D ZYYZ() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D ZYYW() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D ZYZX() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D ZYZY() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D ZYZZ() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D ZYZW() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D ZYWX() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D ZYWY() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D ZYWZ() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D ZYWW() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D ZZXX() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D ZZXY() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D ZZXZ() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D ZZXW() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D ZZYX() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D ZZYY() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D ZZYZ() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D ZZYW() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D ZZZX() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D ZZZY() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D ZZZZ() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D ZZZW() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D ZZWX() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D ZZWY() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D ZZWZ() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D ZZWW() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D ZWXX() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D ZWXY() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D ZWXZ() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D ZWXW() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D ZWYX() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D ZWYY() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D ZWYZ() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D ZWYW() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D ZWZX() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D ZWZY() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D ZWZZ() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D ZWZW() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D ZWWX() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D ZWWY() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D ZWWZ() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D ZWWW() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D WXXX() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D WXXY() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D WXXZ() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D WXXW() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D WXYX() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D WXYY() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D WXYZ() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D WXYW() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D WXZX() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D WXZY() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D WXZZ() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D WXZW() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D WXWX() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D WXWY() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D WXWZ() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D WXWW() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D WYXX() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D WYXY() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D WYXZ() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D WYXW() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D WYYX() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D WYYY() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D WYYZ() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D WYYW() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D WYZX() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D WYZY() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D WYZZ() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D WYZW() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D WYWX() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D WYWY() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D WYWZ() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D WYWW() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D WZXX() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D WZXY() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D WZXZ() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D WZXW() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D WZYX() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D WZYY() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D WZYZ() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D WZYW() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D WZZX() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D WZZY() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D WZZZ() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D WZZW() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D WZWX() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D WZWY() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D WZWZ() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D WZWW() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D WWXX() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D WWXY() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D WWXZ() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D WWXW() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D WWYX() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D WWYY() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D WWYZ() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D WWYW() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D WWZX() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D WWZY() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D WWZZ() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D WWZW() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D WWWX() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D WWWY() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D WWWZ() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D WWWW() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4D RRRR() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D RRRG() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D RRRB() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D RRRA() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D RRGR() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D RRGG() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D RRGB() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D RRGA() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D RRBR() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D RRBG() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D RRBB() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D RRBA() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D RRAR() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D RRAG() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D RRAB() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D RRAA() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D RGRR() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D RGRG() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D RGRB() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D RGRA() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D RGGR() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D RGGG() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D RGGB() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D RGGA() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D RGBR() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D RGBG() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D RGBB() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D RGAR() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D RGAG() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D RGAB() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D RGAA() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D RBRR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D RBRG() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D RBRB() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D RBRA() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D RBGR() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D RBGG() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D RBGB() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D RBGA() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D RBBR() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D RBBG() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D RBBB() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D RBBA() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D RBAR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D RBAG() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D RBAB() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D RBAA() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D RARR() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D RARG() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D RARB() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D RARA() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D RAGR() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D RAGG() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D RAGB() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D RAGA() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D RABR() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D RABG() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D RABB() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D RABA() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D RAAR() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D RAAG() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D RAAB() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D RAAA() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D GRRR() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D GRRG() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D GRRB() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D GRRA() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D GRGR() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D GRGG() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D GRGB() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D GRGA() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D GRBR() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D GRBG() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D GRBB() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D GRBA() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D GRAR() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D GRAG() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D GRAB() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D GRAA() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D GGRR() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D GGRG() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D GGRB() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D GGRA() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D GGGR() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D GGGG() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D GGGB() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D GGGA() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D GGBR() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D GGBG() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D GGBB() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D GGBA() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D GGAR() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D GGAG() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D GGAB() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D GGAA() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D GBRR() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D GBRG() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D GBRB() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D GBRA() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D GBGR() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D GBGG() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D GBGB() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D GBGA() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D GBBR() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D GBBG() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D GBBB() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D GBBA() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D GBAR() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D GBAG() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D GBAB() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D GBAA() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D GARR() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D GARG() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D GARB() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D GARA() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D GAGR() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D GAGG() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D GAGB() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D GAGA() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D GABR() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D GABG() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D GABB() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D GABA() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D GAAR() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D GAAG() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D GAAB() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D GAAA() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D BRRR() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D BRRG() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D BRRB() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D BRRA() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D BRGR() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D BRGG() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D BRGB() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D BRGA() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D BRBR() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D BRBG() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D BRBB() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D BRBA() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D BRAR() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D BRAG() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D BRAB() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D BRAA() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D BGRR() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D BGRG() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D BGRB() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D BGRA() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D BGGR() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D BGGG() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D BGGB() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D BGGA() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D BGBR() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D BGBG() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D BGBB() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D BGBA() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D BGAR() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D BGAG() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D BGAB() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D BGAA() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D BBRR() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D BBRG() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D BBRB() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D BBRA() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D BBGR() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D BBGG() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D BBGB() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D BBGA() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D BBBR() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D BBBG() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D BBBB() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D BBBA() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D BBAR() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D BBAG() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D BBAB() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D BBAA() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D BARR() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D BARG() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D BARB() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D BARA() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D BAGR() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D BAGG() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D BAGB() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D BAGA() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D BABR() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D BABG() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D BABB() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D BABA() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D BAAR() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D BAAG() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D BAAB() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D BAAA() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D ARRR() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D ARRG() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D ARRB() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D ARRA() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D ARGR() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D ARGG() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D ARGB() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D ARGA() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D ARBR() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D ARBG() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D ARBB() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D ARBA() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D ARAR() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D ARAG() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D ARAB() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D ARAA() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D AGRR() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D AGRG() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D AGRB() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D AGRA() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D AGGR() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D AGGG() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D AGGB() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D AGGA() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D AGBR() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D AGBG() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D AGBB() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D AGBA() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D AGAR() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D AGAG() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D AGAB() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D AGAA() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D ABRR() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D ABRG() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D ABRB() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D ABRA() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D ABGR() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D ABGG() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D ABGB() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D ABGA() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D ABBR() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D ABBG() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D ABBB() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D ABBA() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D ABAR() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D ABAG() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D ABAB() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D ABAA() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D AARR() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D AARG() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D AARB() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D AARA() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D AAGR() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D AAGG() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D AAGB() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D AAGA() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D AABR() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D AABG() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D AABB() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D AABA() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D AAAR() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D AAAG() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D AAAB() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D AAAA() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
};

struct Vec2I {
	__m128i m_iVec;

	HC_INLINE Vec2I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit Vec2I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec2I(int _iX, int _iY) { m_iVec = _mm_set_epi32(_iY, _iY, _iY, _iX); }
	HC_INLINE explicit Vec2I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int operator[](int _iNdx) const { assert(_iNdx < 2); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& operator[](int _iNdx) { assert(_iNdx < 2); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void SetX(int _iX) { m_iVec = _mm_set_epi32(Y(), Y(), Y(), _iX); }
	HC_INLINE void SetY(int _iY) { m_iVec = _mm_set_epi32(_iY, _iY, _iY, X()); }
	HC_INLINE void SetR(int _iR) { m_iVec = _mm_set_epi32(Y(), Y(), Y(), _iR); }
	HC_INLINE void SetG(int _iG) { m_iVec = _mm_set_epi32(_iG, _iG, _iG, X()); }
	HC_INLINE Vec2I XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
};

struct Vec3I {
	__m128i m_iVec;

	HC_INLINE Vec3I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit Vec3I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec3I(int _iX, int _iY, int _iZ) { m_iVec = _mm_set_epi32(_iZ, _iZ, _iY, _iX); }
	HC_INLINE explicit Vec3I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int operator[](int _iNdx) const { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& operator[](int _iNdx) { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int Z() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int B() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void SetX(int _iX) { m_iVec = _mm_set_epi32(Z(), Z(), Y(), _iX); }
	HC_INLINE void SetY(int _iY) { m_iVec = _mm_set_epi32(Z(), Z(), _iY, X()); }
	HC_INLINE void SetZ(int _iZ) { m_iVec = _mm_set_epi32(_iZ, _iZ, Y(), X()); }
	HC_INLINE void SetR(int _iR) { m_iVec = _mm_set_epi32(Z(), Z(), Y(), _iR); }
	HC_INLINE void SetG(int _iG) { m_iVec = _mm_set_epi32(Z(), Z(), _iG, X()); }
	HC_INLINE void SetB(int _iB) { m_iVec = _mm_set_epi32(_iB, _iB, Y(), X()); }
	HC_INLINE Vec2I XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I ZZ() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I XY() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I XZ() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I YZ() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I ZX() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I ZY() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I BB() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I RG() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I RB() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I GB() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I BR() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I BG() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec3I XXX() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I XXY() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I XXZ() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I XYX() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I XYY() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I XZX() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I XZY() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I XZZ() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I YXX() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I YXY() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I YXZ() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I YYX() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I YYY() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I YYZ() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I YZX() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I YZY() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I YZZ() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I ZXX() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I ZXY() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I ZXZ() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I ZYX() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I ZYY() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I ZYZ() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I ZZX() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I ZZY() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I ZZZ() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I RRR() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I RRG() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I RRB() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I RGR() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I RGG() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I RBR() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I RBG() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I RBB() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I GRR() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I GRG() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I GRB() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I GGR() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I GGG() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I GGB() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I GBR() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I GBG() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I GBB() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I BRR() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I BRG() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I BRB() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I BGR() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I BGG() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I BGB() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I BBR() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I BBG() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I BBB() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
};

struct Vec4I {
	__m128i m_iVec;

	HC_INLINE Vec4I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit Vec4I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit Vec4I(int _iX, int _iY, int _iZ, int _iW) { m_iVec = _mm_set_epi32(_iW, _iZ, _iY, _iX); }
	HC_INLINE explicit Vec4I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int operator[](int _iNdx) const { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& operator[](int _iNdx) { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int Z() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int W() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE int R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int B() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int A() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void SetX(int _iX) { m_iVec = _mm_set_epi32(W(), Z(), Y(), _iX); }
	HC_INLINE void SetY(int _iY) { m_iVec = _mm_set_epi32(W(), Z(), _iY, X()); }
	HC_INLINE void SetZ(int _iZ) { m_iVec = _mm_set_epi32(W(), _iZ, Y(), X()); }
	HC_INLINE void SetW(int _iW) { m_iVec = _mm_set_epi32(_iW, W(), Y(), X()); }
	HC_INLINE void SetR(int _iR) { m_iVec = _mm_set_epi32(W(), Z(), Y(), _iR); }
	HC_INLINE void SetG(int _iG) { m_iVec = _mm_set_epi32(W(), Z(), _iG, X()); }
	HC_INLINE void SetB(int _iB) { m_iVec = _mm_set_epi32(W(), _iB, Y(), X()); }
	HC_INLINE void SetA(int _iA) { m_iVec = _mm_set_epi32(_iA, Z(), Y(), X()); }
	HC_INLINE Vec2I XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I ZZ() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I WW() const { return HC_SHUFFLE2I(*this, 3, 3); }
	HC_INLINE Vec2I XY() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I XZ() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I XW() const { return HC_SHUFFLE2I(*this, 0, 3); }
	HC_INLINE Vec2I YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I YZ() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I YW() const { return HC_SHUFFLE2I(*this, 1, 3); }
	HC_INLINE Vec2I ZX() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I ZY() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I ZW() const { return HC_SHUFFLE2I(*this, 2, 3); }
	HC_INLINE Vec2I WX() const { return HC_SHUFFLE2I(*this, 3, 0); }
	HC_INLINE Vec2I WY() const { return HC_SHUFFLE2I(*this, 3, 1); }
	HC_INLINE Vec2I WZ() const { return HC_SHUFFLE2I(*this, 3, 2); }
	HC_INLINE Vec2I RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I BB() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I AA() const { return HC_SHUFFLE2I(*this, 3, 3); }
	HC_INLINE Vec2I RG() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I RB() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I RA() const { return HC_SHUFFLE2I(*this, 0, 3); }
	HC_INLINE Vec2I GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I GB() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I GA() const { return HC_SHUFFLE2I(*this, 1, 3); }
	HC_INLINE Vec2I BR() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I BG() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I BA() const { return HC_SHUFFLE2I(*this, 2, 3); }
	HC_INLINE Vec2I AR() const { return HC_SHUFFLE2I(*this, 3, 0); }
	HC_INLINE Vec2I AG() const { return HC_SHUFFLE2I(*this, 3, 1); }
	HC_INLINE Vec2I AB() const { return HC_SHUFFLE2I(*this, 3, 2); }
	HC_INLINE Vec3I XXX() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I XXY() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I XXZ() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I XXW() const { return HC_SHUFFLE3I(*this, 0, 0, 3); }
	HC_INLINE Vec3I XYX() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I XYY() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I XYZ() const { return HC_SHUFFLE3I(*this, 0, 1, 2); }
	HC_INLINE Vec3I XYW() const { return HC_SHUFFLE3I(*this, 0, 1, 3); }
	HC_INLINE Vec3I XZX() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I XZY() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I XZZ() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I XZW() const { return HC_SHUFFLE3I(*this, 0, 2, 3); }
	HC_INLINE Vec3I XWX() const { return HC_SHUFFLE3I(*this, 0, 3, 0); }
	HC_INLINE Vec3I XWY() const { return HC_SHUFFLE3I(*this, 0, 3, 1); }
	HC_INLINE Vec3I XWZ() const { return HC_SHUFFLE3I(*this, 0, 3, 2); }
	HC_INLINE Vec3I XWW() const { return HC_SHUFFLE3I(*this, 0, 3, 3); }
	HC_INLINE Vec3I YXX() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I YXY() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I YXZ() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I YXW() const { return HC_SHUFFLE3I(*this, 1, 0, 3); }
	HC_INLINE Vec3I YYX() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I YYY() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I YYZ() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I YYW() const { return HC_SHUFFLE3I(*this, 1, 1, 3); }
	HC_INLINE Vec3I YZX() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I YZY() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I YZZ() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I YZW() const { return HC_SHUFFLE3I(*this, 1, 2, 3); }
	HC_INLINE Vec3I YWX() const { return HC_SHUFFLE3I(*this, 1, 3, 0); }
	HC_INLINE Vec3I YWY() const { return HC_SHUFFLE3I(*this, 1, 3, 1); }
	HC_INLINE Vec3I YWZ() const { return HC_SHUFFLE3I(*this, 1, 3, 2); }
	HC_INLINE Vec3I YWW() const { return HC_SHUFFLE3I(*this, 1, 3, 3); }
	HC_INLINE Vec3I ZXX() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I ZXY() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I ZXZ() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I ZXW() const { return HC_SHUFFLE3I(*this, 2, 0, 3); }
	HC_INLINE Vec3I ZYX() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I ZYY() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I ZYZ() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I ZYW() const { return HC_SHUFFLE3I(*this, 2, 1, 3); }
	HC_INLINE Vec3I ZZX() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I ZZY() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I ZZZ() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I ZZW() const { return HC_SHUFFLE3I(*this, 2, 2, 3); }
	HC_INLINE Vec3I ZWX() const { return HC_SHUFFLE3I(*this, 2, 3, 0); }
	HC_INLINE Vec3I ZWY() const { return HC_SHUFFLE3I(*this, 2, 3, 1); }
	HC_INLINE Vec3I ZWZ() const { return HC_SHUFFLE3I(*this, 2, 3, 2); }
	HC_INLINE Vec3I ZWW() const { return HC_SHUFFLE3I(*this, 2, 3, 3); }
	HC_INLINE Vec3I WXX() const { return HC_SHUFFLE3I(*this, 3, 0, 0); }
	HC_INLINE Vec3I WXY() const { return HC_SHUFFLE3I(*this, 3, 0, 1); }
	HC_INLINE Vec3I WXZ() const { return HC_SHUFFLE3I(*this, 3, 0, 2); }
	HC_INLINE Vec3I WXW() const { return HC_SHUFFLE3I(*this, 3, 0, 3); }
	HC_INLINE Vec3I WYX() const { return HC_SHUFFLE3I(*this, 3, 1, 0); }
	HC_INLINE Vec3I WYY() const { return HC_SHUFFLE3I(*this, 3, 1, 1); }
	HC_INLINE Vec3I WYZ() const { return HC_SHUFFLE3I(*this, 3, 1, 2); }
	HC_INLINE Vec3I WYW() const { return HC_SHUFFLE3I(*this, 3, 1, 3); }
	HC_INLINE Vec3I WZX() const { return HC_SHUFFLE3I(*this, 3, 2, 0); }
	HC_INLINE Vec3I WZY() const { return HC_SHUFFLE3I(*this, 3, 2, 1); }
	HC_INLINE Vec3I WZZ() const { return HC_SHUFFLE3I(*this, 3, 2, 2); }
	HC_INLINE Vec3I WZW() const { return HC_SHUFFLE3I(*this, 3, 2, 3); }
	HC_INLINE Vec3I WWX() const { return HC_SHUFFLE3I(*this, 3, 3, 0); }
	HC_INLINE Vec3I WWY() const { return HC_SHUFFLE3I(*this, 3, 3, 1); }
	HC_INLINE Vec3I WWZ() const { return HC_SHUFFLE3I(*this, 3, 3, 2); }
	HC_INLINE Vec3I WWW() const { return HC_SHUFFLE3I(*this, 3, 3, 3); }
	HC_INLINE Vec3I RRR() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I RRG() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I RRB() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I RRA() const { return HC_SHUFFLE3I(*this, 0, 0, 3); }
	HC_INLINE Vec3I RGR() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I RGG() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I RGA() const { return HC_SHUFFLE3I(*this, 0, 1, 2); }
	HC_INLINE Vec3I RGB() const { return HC_SHUFFLE3I(*this, 0, 1, 3); }
	HC_INLINE Vec3I RBR() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I RBG() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I RBB() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I RBA() const { return HC_SHUFFLE3I(*this, 0, 2, 3); }
	HC_INLINE Vec3I RAR() const { return HC_SHUFFLE3I(*this, 0, 3, 0); }
	HC_INLINE Vec3I RAG() const { return HC_SHUFFLE3I(*this, 0, 3, 1); }
	HC_INLINE Vec3I RAB() const { return HC_SHUFFLE3I(*this, 0, 3, 2); }
	HC_INLINE Vec3I RAA() const { return HC_SHUFFLE3I(*this, 0, 3, 3); }
	HC_INLINE Vec3I GRR() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I GRG() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I GRB() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I GRA() const { return HC_SHUFFLE3I(*this, 1, 0, 3); }
	HC_INLINE Vec3I GGR() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I GGG() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I GGB() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I GGA() const { return HC_SHUFFLE3I(*this, 1, 1, 3); }
	HC_INLINE Vec3I GBR() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I GBG() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I GBB() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I GBA() const { return HC_SHUFFLE3I(*this, 1, 2, 3); }
	HC_INLINE Vec3I GAR() const { return HC_SHUFFLE3I(*this, 1, 3, 0); }
	HC_INLINE Vec3I GAG() const { return HC_SHUFFLE3I(*this, 1, 3, 1); }
	HC_INLINE Vec3I GAB() const { return HC_SHUFFLE3I(*this, 1, 3, 2); }
	HC_INLINE Vec3I GAA() const { return HC_SHUFFLE3I(*this, 1, 3, 3); }
	HC_INLINE Vec3I BRR() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I BRG() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I BRB() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I BRA() const { return HC_SHUFFLE3I(*this, 2, 0, 3); }
	HC_INLINE Vec3I BGR() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I BGG() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I BGB() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I BGA() const { return HC_SHUFFLE3I(*this, 2, 1, 3); }
	HC_INLINE Vec3I BBR() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I BBG() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I BBB() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I BBA() const { return HC_SHUFFLE3I(*this, 2, 2, 3); }
	HC_INLINE Vec3I BAR() const { return HC_SHUFFLE3I(*this, 2, 3, 0); }
	HC_INLINE Vec3I BAG() const { return HC_SHUFFLE3I(*this, 2, 3, 1); }
	HC_INLINE Vec3I BAB() const { return HC_SHUFFLE3I(*this, 2, 3, 2); }
	HC_INLINE Vec3I BAA() const { return HC_SHUFFLE3I(*this, 2, 3, 3); }
	HC_INLINE Vec3I ARR() const { return HC_SHUFFLE3I(*this, 3, 0, 0); }
	HC_INLINE Vec3I ARG() const { return HC_SHUFFLE3I(*this, 3, 0, 1); }
	HC_INLINE Vec3I ARB() const { return HC_SHUFFLE3I(*this, 3, 0, 2); }
	HC_INLINE Vec3I ARA() const { return HC_SHUFFLE3I(*this, 3, 0, 3); }
	HC_INLINE Vec3I AGR() const { return HC_SHUFFLE3I(*this, 3, 1, 0); }
	HC_INLINE Vec3I AGG() const { return HC_SHUFFLE3I(*this, 3, 1, 1); }
	HC_INLINE Vec3I AGB() const { return HC_SHUFFLE3I(*this, 3, 1, 2); }
	HC_INLINE Vec3I AGA() const { return HC_SHUFFLE3I(*this, 3, 1, 3); }
	HC_INLINE Vec3I ABR() const { return HC_SHUFFLE3I(*this, 3, 2, 0); }
	HC_INLINE Vec3I ABG() const { return HC_SHUFFLE3I(*this, 3, 2, 1); }
	HC_INLINE Vec3I ABB() const { return HC_SHUFFLE3I(*this, 3, 2, 2); }
	HC_INLINE Vec3I ABA() const { return HC_SHUFFLE3I(*this, 3, 2, 3); }
	HC_INLINE Vec3I AAR() const { return HC_SHUFFLE3I(*this, 3, 3, 0); }
	HC_INLINE Vec3I AAG() const { return HC_SHUFFLE3I(*this, 3, 3, 1); }
	HC_INLINE Vec3I AAB() const { return HC_SHUFFLE3I(*this, 3, 3, 2); }
	HC_INLINE Vec3I AAA() const { return HC_SHUFFLE3I(*this, 3, 3, 3); }
	HC_INLINE Vec4I XXXX() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4I XXXY() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4I XXXZ() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4I XXXW() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4I XXYX() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4I XXYY() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4I XXYZ() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4I XXYW() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4I XXZX() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4I XXZY() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4I XXZZ() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4I XXZW() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4I XXWX() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4I XXWY() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4I XXWZ() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4I XXWW() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4I XYXX() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4I XYXY() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4I XYXZ() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4I XYXW() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4I XYYX() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4I XYYY() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4I XYYZ() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4I XYYW() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4I XYZX() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4I XYZY() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4I XYZZ() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4I XYWX() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4I XYWY() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4I XYWZ() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4I XYWW() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4I XZXX() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I XZXY() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4I XZXZ() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4I XZXW() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4I XZYX() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4I XZYY() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4I XZYZ() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4I XZYW() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4I XZZX() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4I XZZY() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4I XZZZ() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4I XZZW() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4I XZWX() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I XZWY() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4I XZWZ() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4I XZWW() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4I XWXX() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4I XWXY() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4I XWXZ() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4I XWXW() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4I XWYX() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4I XWYY() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4I XWYZ() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4I XWYW() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4I XWZX() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4I XWZY() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4I XWZZ() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4I XWZW() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4I XWWX() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4I XWWY() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4I XWWZ() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4I XWWW() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4I YXXX() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4I YXXY() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4I YXXZ() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4I YXXW() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4I YXYX() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4I YXYY() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4I YXYZ() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4I YXYW() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4I YXZX() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4I YXZY() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4I YXZZ() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4I YXZW() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4I YXWX() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4I YXWY() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4I YXWZ() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4I YXWW() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4I YYXX() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4I YYXY() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4I YYXZ() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4I YYXW() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4I YYYX() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4I YYYY() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4I YYYZ() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4I YYYW() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4I YYZX() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4I YYZY() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4I YYZZ() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4I YYZW() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4I YYWX() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4I YYWY() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4I YYWZ() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4I YYWW() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4I YZXX() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4I YZXY() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4I YZXZ() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4I YZXW() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4I YZYX() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4I YZYY() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4I YZYZ() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4I YZYW() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4I YZZX() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4I YZZY() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4I YZZZ() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4I YZZW() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4I YZWX() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4I YZWY() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4I YZWZ() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4I YZWW() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4I YWXX() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4I YWXY() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4I YWXZ() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4I YWXW() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4I YWYX() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4I YWYY() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4I YWYZ() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4I YWYW() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4I YWZX() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4I YWZY() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4I YWZZ() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4I YWZW() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4I YWWX() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4I YWWY() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4I YWWZ() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4I YWWW() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4I ZXXX() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4I ZXXY() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4I ZXXZ() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4I ZXXW() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4I ZXYX() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4I ZXYY() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4I ZXYZ() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4I ZXYW() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4I ZXZX() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4I ZXZY() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4I ZXZZ() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4I ZXZW() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4I ZXWX() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4I ZXWY() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4I ZXWZ() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4I ZXWW() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4I ZYXX() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4I ZYXY() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4I ZYXZ() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4I ZYXW() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4I ZYYX() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4I ZYYY() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4I ZYYZ() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4I ZYYW() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4I ZYZX() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4I ZYZY() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4I ZYZZ() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4I ZYZW() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4I ZYWX() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4I ZYWY() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4I ZYWZ() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4I ZYWW() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4I ZZXX() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4I ZZXY() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4I ZZXZ() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4I ZZXW() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4I ZZYX() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4I ZZYY() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4I ZZYZ() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4I ZZYW() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4I ZZZX() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4I ZZZY() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4I ZZZZ() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4I ZZZW() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4I ZZWX() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4I ZZWY() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4I ZZWZ() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4I ZZWW() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4I ZWXX() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4I ZWXY() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4I ZWXZ() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4I ZWXW() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4I ZWYX() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4I ZWYY() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4I ZWYZ() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4I ZWYW() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4I ZWZX() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4I ZWZY() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4I ZWZZ() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4I ZWZW() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4I ZWWX() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4I ZWWY() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4I ZWWZ() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4I ZWWW() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4I WXXX() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4I WXXY() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4I WXXZ() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4I WXXW() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4I WXYX() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4I WXYY() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4I WXYZ() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4I WXYW() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4I WXZX() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4I WXZY() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4I WXZZ() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4I WXZW() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4I WXWX() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4I WXWY() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4I WXWZ() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4I WXWW() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4I WYXX() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4I WYXY() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4I WYXZ() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4I WYXW() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4I WYYX() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4I WYYY() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4I WYYZ() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4I WYYW() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4I WYZX() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4I WYZY() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4I WYZZ() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4I WYZW() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4I WYWX() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4I WYWY() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4I WYWZ() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4I WYWW() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4I WZXX() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4I WZXY() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4I WZXZ() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4I WZXW() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4I WZYX() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4I WZYY() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4I WZYZ() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4I WZYW() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4I WZZX() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4I WZZY() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4I WZZZ() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4I WZZW() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4I WZWX() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4I WZWY() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4I WZWZ() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4I WZWW() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4I WWXX() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4I WWXY() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4I WWXZ() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4I WWXW() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4I WWYX() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4I WWYY() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4I WWYZ() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4I WWYW() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4I WWZX() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4I WWZY() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4I WWZZ() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4I WWZW() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4I WWWX() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4I WWWY() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4I WWWZ() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4I WWWW() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4I RRRR() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4I RRRG() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4I RRRB() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4I RRRA() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4I RRGR() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4I RRGG() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4I RRGB() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4I RRGA() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4I RRBR() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4I RRBG() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4I RRBB() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4I RRBA() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4I RRAR() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4I RRAG() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4I RRAB() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4I RRAA() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4I RGRR() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4I RGRG() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4I RGRB() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4I RGRA() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4I RGGR() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4I RGGG() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4I RGGB() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4I RGGA() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4I RGBR() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4I RGBG() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4I RGBB() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4I RGAR() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4I RGAG() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4I RGAB() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4I RGAA() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4I RBRR() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I RBRG() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4I RBRB() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4I RBRA() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4I RBGR() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4I RBGG() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4I RBGB() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4I RBGA() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4I RBBR() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4I RBBG() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4I RBBB() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4I RBBA() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4I RBAR() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I RBAG() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4I RBAB() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4I RBAA() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4I RARR() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4I RARG() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4I RARB() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4I RARA() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4I RAGR() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4I RAGG() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4I RAGB() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4I RAGA() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4I RABR() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4I RABG() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4I RABB() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4I RABA() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4I RAAR() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4I RAAG() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4I RAAB() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4I RAAA() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4I GRRR() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4I GRRG() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4I GRRB() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4I GRRA() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4I GRGR() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4I GRGG() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4I GRGB() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4I GRGA() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4I GRBR() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4I GRBG() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4I GRBB() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4I GRBA() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4I GRAR() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4I GRAG() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4I GRAB() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4I GRAA() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4I GGRR() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4I GGRG() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4I GGRB() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4I GGRA() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4I GGGR() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4I GGGG() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4I GGGB() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4I GGGA() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4I GGBR() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4I GGBG() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4I GGBB() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4I GGBA() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4I GGAR() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4I GGAG() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4I GGAB() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4I GGAA() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4I GBRR() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4I GBRG() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4I GBRB() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4I GBRA() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4I GBGR() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4I GBGG() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4I GBGB() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4I GBGA() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4I GBBR() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4I GBBG() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4I GBBB() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4I GBBA() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4I GBAR() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4I GBAG() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4I GBAB() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4I GBAA() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4I GARR() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4I GARG() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4I GARB() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4I GARA() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4I GAGR() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4I GAGG() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4I GAGB() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4I GAGA() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4I GABR() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4I GABG() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4I GABB() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4I GABA() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4I GAAR() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4I GAAG() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4I GAAB() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4I GAAA() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4I BRRR() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4I BRRG() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4I BRRB() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4I BRRA() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4I BRGR() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4I BRGG() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4I BRGB() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4I BRGA() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4I BRBR() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4I BRBG() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4I BRBB() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4I BRBA() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4I BRAR() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4I BRAG() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4I BRAB() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4I BRAA() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4I BGRR() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4I BGRG() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4I BGRB() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4I BGRA() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4I BGGR() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4I BGGG() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4I BGGB() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4I BGGA() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4I BGBR() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4I BGBG() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4I BGBB() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4I BGBA() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4I BGAR() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4I BGAG() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4I BGAB() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4I BGAA() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4I BBRR() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4I BBRG() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4I BBRB() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4I BBRA() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4I BBGR() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4I BBGG() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4I BBGB() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4I BBGA() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4I BBBR() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4I BBBG() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4I BBBB() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4I BBBA() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4I BBAR() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4I BBAG() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4I BBAB() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4I BBAA() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4I BARR() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4I BARG() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4I BARB() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4I BARA() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4I BAGR() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4I BAGG() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4I BAGB() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4I BAGA() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4I BABR() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4I BABG() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4I BABB() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4I BABA() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4I BAAR() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4I BAAG() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4I BAAB() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4I BAAA() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4I ARRR() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4I ARRG() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4I ARRB() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4I ARRA() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4I ARGR() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4I ARGG() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4I ARGB() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4I ARGA() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4I ARBR() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4I ARBG() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4I ARBB() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4I ARBA() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4I ARAR() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4I ARAG() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4I ARAB() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4I ARAA() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4I AGRR() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4I AGRG() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4I AGRB() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4I AGRA() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4I AGGR() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4I AGGG() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4I AGGB() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4I AGGA() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4I AGBR() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4I AGBG() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4I AGBB() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4I AGBA() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4I AGAR() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4I AGAG() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4I AGAB() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4I AGAA() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4I ABRR() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4I ABRG() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4I ABRB() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4I ABRA() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4I ABGR() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4I ABGG() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4I ABGB() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4I ABGA() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4I ABBR() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4I ABBG() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4I ABBB() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4I ABBA() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4I ABAR() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4I ABAG() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4I ABAB() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4I ABAA() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4I AARR() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4I AARG() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4I AARB() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4I AARA() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4I AAGR() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4I AAGG() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4I AAGB() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4I AAGA() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4I AABR() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4I AABG() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4I AABB() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4I AABA() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4I AAAR() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4I AAAG() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4I AAAB() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4I AAAA() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 3); }
};

HC_INLINE Vec2F operator+(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F operator-(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F operator*(Vec2F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec2F operator*(float _fLeft, Vec2F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec2F operator/(Vec2F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec2F operator/(float _fLeft, Vec2F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec2F operator*(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F operator/(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F& operator+=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2F& operator-=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2F& operator*=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2F& operator/=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2F& operator*=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2F& operator/=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2F operator~(Vec2F _vVector) { return Vec2F(); }
HC_INLINE Vec2F operator-(Vec2F _vVector) { return Vec2F() - (_vVector); }
HC_INLINE bool operator==(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool operator<(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool operator>(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool operator<=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool operator>=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool operator!=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) != 0; }
HC_INLINE Vec2F Min(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F Max(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F Clamp(Vec2F _vVector, Vec2F _vMin, Vec2F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float Sum(const Vec2F _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE float Dot(Vec2F _vLeft, Vec2F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec2F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float LengthSquared(Vec2F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2F Normalize(Vec2F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float AngleBetween(Vec2F _vLeft, Vec2F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE float Cross(Vec2F _vLeft, Vec2F _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2F Abs(Vec2F _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec); return _vVector; }

HC_INLINE Vec3F operator+(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F operator-(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F operator*(Vec3F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec3F operator*(float _fLeft, Vec3F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec3F operator/(Vec3F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec3F operator/(float _fLeft, Vec3F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec3F operator*(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F operator/(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F& operator+=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3F& operator-=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3F& operator/=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3F& operator/=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3F operator~(Vec3F _vVector) { return Vec3F(); }
HC_INLINE Vec3F operator-(Vec3F _vVector) { return Vec3F() - _vVector; }
HC_INLINE bool operator==(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool operator<(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool operator>(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool operator<=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool operator>=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool operator!=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) != 0; }
HC_INLINE Vec3F Min(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F Max(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F Clamp(Vec3F _vVector, Vec3F _vMin, Vec3F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float HorizontalMin(Vec3F _vVector) { _vVector = Min(_vVector, HC_SHUFFLE3F(_vVector, 1, 0, 2)); return Min(_vVector, HC_SHUFFLE3F(_vVector, 2, 0, 1)).X(); }
HC_INLINE float HorizontalMax(Vec3F _vVector) { _vVector = Max(_vVector, HC_SHUFFLE3F(_vVector, 1, 0, 2)); return Max(_vVector, HC_SHUFFLE3F(_vVector, 2, 0, 1)).X(); }
HC_INLINE float Sum(const Vec3F _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE float Dot(Vec3F _vLeft, Vec3F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec3F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float LengthSquared(Vec3F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3F Normalize(Vec3F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float AngleBetween(Vec3F _vLeft, Vec3F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE Vec3F Cross(Vec3F _vLeft, Vec3F _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3F Abs(Vec3F _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec); return _vVector; }

HC_INLINE Vec4F operator+(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F operator-(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F operator*(Vec4F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec4F operator*(float _fLeft, Vec4F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec4F operator/(Vec4F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec4F operator/(float _fLeft, Vec4F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec4F operator*(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F operator/(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F& operator+=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4F& operator-=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4F& operator/=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4F& operator/=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4F operator~(Vec4F _vVector) { return Vec4F(); }
HC_INLINE Vec4F operator-(Vec4F _vVector) { return Vec4F() - _vVector; }
HC_INLINE bool operator==(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool operator<(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool operator>(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool operator<=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool operator>=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool operator!=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE Vec4F Min(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F Max(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F Clamp(Vec4F _vVector, Vec4F _vMin, Vec4F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float Sum(const Vec4F _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_INLINE float Dot(Vec4F _vLeft, Vec4F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec4F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float LengthSquared(Vec4F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4F Normalize(Vec4F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float AngleBetween(Vec4F _vLeft, Vec4F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE Vec4F Cross(Vec4F _vLeft, Vec4F _vRight) { _vRight.m_fVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_fVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4F Abs(Vec4F _vVector) { return Vec4F(_mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec)); }

HC_INLINE Vec2D operator+(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D operator-(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D operator*(Vec2D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec2D operator*(double _fLeft, Vec2D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec2D operator/(Vec2D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec2D operator/(double _fLeft, Vec2D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec2D operator*(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D operator/(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D& operator+=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2D& operator-=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2D& operator*=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2D& operator/=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2D& operator*=(Vec2D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2D& operator/=(Vec2D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2D operator~(Vec2D _vVector) { return Vec2D(); }
HC_INLINE Vec2D operator-(Vec2D _vVector) { return Vec2D() - _vVector; }
HC_INLINE bool operator==(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool operator<(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool operator>(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool operator<=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool operator>=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool operator!=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) != 0; }
HC_INLINE Vec2D Min(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D Max(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D Clamp(Vec2D _vVector, Vec2D _vMin, Vec2D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double Sum(const Vec2D _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE double Dot(Vec2D _vLeft, Vec2D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double Length(Vec2D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double LengthSquared(Vec2D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2D Normalize(Vec2D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double AngleBetween(Vec2D _vLeft, Vec2D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE double Cross(Vec2D _vLeft, Vec2D _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2D Abs(Vec2D _vVector) { _vVector.m_dVec = _mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec); return _vVector; }

HC_INLINE Vec3D operator+(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D operator-(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D operator*(Vec3D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec3D operator*(double _fLeft, Vec3D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec3D operator/(Vec3D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec3D operator/(double _fLeft, Vec3D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec3D operator*(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D operator/(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D& operator+=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3D& operator-=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3D& operator/=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3D& operator/=(Vec3D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3D operator~(Vec3D _vVector) { return Vec3D(); }
HC_INLINE Vec3D operator-(Vec3D _vVector) { return Vec3D() - _vVector; }
HC_INLINE bool operator==(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool operator<(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool operator>(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool operator<=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool operator>=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool operator!=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) != 0; }
HC_INLINE Vec3D Min(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D Max(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D Clamp(Vec3D _vVector, Vec3D _vMin, Vec3D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double HorizontalMin(Vec3D _vVector) { _vVector = Min(_vVector, HC_SHUFFLE3D(_vVector, 1, 0, 2)); return Min(_vVector, HC_SHUFFLE3D(_vVector, 2, 0, 1)).X(); }
HC_INLINE double HorizontalMax(Vec3D _vVector) { _vVector = Max(_vVector, HC_SHUFFLE3D(_vVector, 1, 0, 2)); return Max(_vVector, HC_SHUFFLE3D(_vVector, 2, 0, 1)).X(); }
HC_INLINE double Sum(const Vec3D _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE double Dot(Vec3D _vLeft, Vec3D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double Length(Vec3D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double LengthSquared(Vec3D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3D Normalize(Vec3D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double AngleBetween(Vec3D _vLeft, Vec3D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE Vec3D Cross(Vec3D _vLeft, Vec3D _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3D Abs(Vec3D _vVector) { _vVector.m_dVec = _mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec); return _vVector; }

HC_INLINE Vec4D operator+(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D operator-(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D operator*(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D operator*(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D operator/(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D operator/(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D operator*(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D operator/(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D& operator+=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4D& operator-=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4D& operator/=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4D& operator/=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4D operator~(Vec4D _vVector) { return Vec4D(); }
HC_INLINE Vec4D operator-(Vec4D _vVector) { return Vec4D() - _vVector; }
HC_INLINE bool operator==(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15;}
HC_INLINE bool operator<(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool operator>(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool operator<=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool operator>=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool operator!=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) != 0; }
HC_INLINE Vec4D Min(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D Max(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D Clamp(Vec4D _vVector, Vec4D _vMin, Vec4D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double Sum(const Vec4D _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_INLINE double Dot(Vec4D _vLeft, Vec4D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double Length(Vec4D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double LengthSquared(Vec4D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4D Normalize(Vec4D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double AngleBetween(Vec4D _vLeft, Vec4D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE Vec4D Cross(Vec4D _vLeft, Vec4D _vRight) { _vRight.m_dVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_dVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4D Abs(Vec4D _vVector) { return Vec4D(_mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec)); }

HC_INLINE Vec2I operator+(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I operator-(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I operator*(Vec2I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec2I operator*(int _fLeft, Vec2I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec2I operator/(Vec2I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec2I operator/(int _fLeft, Vec2I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec2I operator*(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I operator/(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I& operator+=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2I& operator-=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2I& operator*=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2I& operator/=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2I& operator*=(Vec2I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2I& operator/=(Vec2I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2I operator~(Vec2I _vVector) { return Vec2I(); }
HC_INLINE Vec2I operator-(Vec2I _vVector) { return Vec2I() - (_vVector); }
HC_INLINE bool operator==(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator>(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<=(Vec2I _vLeft, Vec2I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator>=(Vec2I _vLeft, Vec2I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator!=(Vec2I _vLeft, Vec2I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec2I Min(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I Max(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I Clamp(Vec2I _vVector, Vec2I _vMin, Vec2I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int Sum(const Vec2I _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE int Dot(Vec2I _vLeft, Vec2I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec2I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int LengthSquared(Vec2I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2I Normalize(Vec2I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float AngleBetween(Vec2I _vLeft, Vec2I _vRight) { return acosf(static_cast<int>(Dot(_vLeft, _vRight))); }
HC_INLINE int Cross(Vec2I _vLeft, Vec2I _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2I Abs(Vec2I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }

HC_INLINE Vec3I operator+(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I operator-(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I operator*(Vec3I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec3I operator*(int _fLeft, Vec3I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec3I operator/(Vec3I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec3I operator/(int _fLeft, Vec3I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec3I operator*(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I operator/(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I& operator+=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3I& operator-=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3I& operator*=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3I& operator/=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3I& operator*=(Vec3I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3I& operator/=(Vec3I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3I operator~(Vec3I _vVector) { return Vec3I(); }
HC_INLINE Vec3I operator-(Vec3I _vVector) { return Vec3I() - (_vVector); }
HC_INLINE bool operator==(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator>(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<=(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator>=(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator!=(Vec3I _vLeft, Vec3I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec3I Min(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I Max(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I Clamp(Vec3I _vVector, Vec3I _vMin, Vec3I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int Sum(const Vec3I _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE int Dot(Vec3I _vLeft, Vec3I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec3I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int LengthSquared(Vec3I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3I Normalize(Vec3I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float AngleBetween(Vec3I _vLeft, Vec3I _vRight) { return acosf(static_cast<int>(Dot(_vLeft, _vRight))); }
HC_INLINE Vec3I Cross(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3I Abs(Vec3I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }

HC_INLINE Vec4I operator+(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I operator-(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I operator*(Vec4I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec4I operator*(int _fLeft, Vec4I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec4I operator/(Vec4I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec4I operator/(int _fLeft, Vec4I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec4I operator*(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I operator/(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I& operator+=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4I& operator-=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4I& operator*=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4I& operator/=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4I& operator*=(Vec4I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4I& operator/=(Vec4I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4I operator~(Vec4I _vVector) { return Vec4I(); }
HC_INLINE Vec4I operator-(Vec4I _vVector) { return Vec4I() - (_vVector); }
HC_INLINE bool operator==(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator>(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool operator<=(Vec4I _vLeft, Vec4I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator>=(Vec4I _vLeft, Vec4I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool operator!=(Vec4I _vLeft, Vec4I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec4I Min(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I Max(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I Clamp(Vec4I _vVector, Vec4I _vMin, Vec4I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int Sum(const Vec4I _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE int Dot(Vec4I _vLeft, Vec4I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float Length(Vec4I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int LengthSquared(Vec4I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4I Normalize(Vec4I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float AngleBetween(Vec4I _vLeft, Vec4I _vRight) { return acosf(static_cast<int>(Dot(_vLeft, _vRight))); }
HC_INLINE Vec4I Cross(Vec4I _vLeft, Vec4I _vRight) { _vRight.m_iVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_iVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4I Abs(Vec4I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }