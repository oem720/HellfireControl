#pragma once

#include <HellfireControl/Core/Common.hpp>

#if HC_USE_SIMD

#define HC_SHUFFLE2F(_vec, _x, _y) Vec2F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3F(_vec, _x, _y, _z) Vec3F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4F(_vec, _x, _y, _z, _w) Vec4F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))
#define HC_SHUFFLE4F_2(_vec1, _vec2, _x, _y, _z, _w) Vec4F(_mm_shuffle_ps((_vec1).m_fVec, (_vec2).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))

#define HC_SHUFFLE2D(_vec, _x, _y)  Vec2D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_y, _y, _y, _x)))
#define HC_SHUFFLE3D(_vec, _x, _y, _z) Vec3D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_z, _z, _y, _x)))
#define HC_SHUFFLE4D(_vec, _x, _y, _z, _w) Vec4D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_w, _z, _y, _x)))
#define HC_SHUFFLE4D_2(_vec1, _vec2, _x, _y, _z, _w) Vec4D(_mm256_shuffle_pd((_vec1).m_dVec, (_vec2).m_dVec, _MM_SHUFFLE(_w, _z, _y, _x)))

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

	HC_INLINE HC_VECTORCALL Vec2F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit HC_VECTORCALL Vec2F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec2F(float _fX, float _fY) { m_fVec = _mm_set_ps(_fY, _fY, _fY, _fX); }
	HC_INLINE explicit HC_VECTORCALL Vec2F(int _iX, int _iY) { m_fVec = _mm_set_ps(static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec2F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 2); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float HC_VECTORCALL X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float HC_VECTORCALL R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void HC_VECTORCALL SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void HC_VECTORCALL SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void HC_VECTORCALL SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F HC_VECTORCALL XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F HC_VECTORCALL RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
};

struct Vec3F {
	__m128 m_fVec;

	HC_INLINE HC_VECTORCALL Vec3F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit HC_VECTORCALL Vec3F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec3F(float _fX, float _fY, float _fZ) { m_fVec = _mm_set_ps(_fZ, _fZ, _fY, _fX); }
	HC_INLINE explicit HC_VECTORCALL Vec3F(int _iX, int _iY, int _iZ) { m_fVec = _mm_set_ps(static_cast<float>(_iZ), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec3F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 3); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float HC_VECTORCALL X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float HC_VECTORCALL Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float HC_VECTORCALL R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float HC_VECTORCALL B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void HC_VECTORCALL SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void HC_VECTORCALL SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetZ(float _fZ) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fZ)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void HC_VECTORCALL SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetB(float _fB) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fB)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F HC_VECTORCALL XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL ZZ() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F HC_VECTORCALL XY() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F HC_VECTORCALL XZ() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F HC_VECTORCALL YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F HC_VECTORCALL YZ() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F HC_VECTORCALL ZX() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F HC_VECTORCALL ZY() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F HC_VECTORCALL RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL BB() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F HC_VECTORCALL RG() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F HC_VECTORCALL RB() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F HC_VECTORCALL GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F HC_VECTORCALL GB() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F HC_VECTORCALL BR() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F HC_VECTORCALL BG() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XXX() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XXY() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XXZ() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XYX() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XYY() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XZX() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XZY() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XZZ() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YXX() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YXY() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YXZ() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YYX() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YYY() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YYZ() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YZX() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YZY() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YZZ() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZXX() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZXY() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZYX() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZYY() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZZX() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZZY() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RRR() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RRG() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RRB() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RGR() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RGG() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RBR() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RBG() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RBB() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GRR() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GRG() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GRB() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GGR() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GGG() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GGB() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GBR() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GBG() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GBB() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BRR() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BRG() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BRB() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BGR() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BGG() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BGB() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BBR() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BBG() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BBB() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
};

struct Vec4F {
	__m128 m_fVec;

	HC_INLINE HC_VECTORCALL Vec4F() { m_fVec = _mm_setzero_ps(); }
	HC_INLINE explicit HC_VECTORCALL Vec4F(const float* _pValues) { m_fVec = _mm_set_ps(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec4F(float _fX, float _fY, float _fZ, float _fW) { m_fVec = _mm_set_ps(_fW, _fZ, _fY, _fX); }
	HC_INLINE explicit HC_VECTORCALL Vec4F(int _iX, int _iY, int _iZ, int _iW) { m_fVec = _mm_set_ps(static_cast<float>(_iW), static_cast<float>(_iZ), static_cast<float>(_iY), static_cast<float>(_iZ)); }
	HC_INLINE explicit HC_VECTORCALL Vec4F(__m128 _vData) { m_fVec = _vData; }
	HC_INLINE float HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 4); return m_fVec.m128_f32[_iNdx]; }
	HC_INLINE float HC_VECTORCALL X() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL Y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float HC_VECTORCALL Z() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float HC_VECTORCALL W() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE float HC_VECTORCALL R() const { return _mm_cvtss_f32(m_fVec); }
	HC_INLINE float HC_VECTORCALL G() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE float HC_VECTORCALL B() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE float HC_VECTORCALL A() const { return _mm_cvtss_f32(_mm_shuffle_ps(m_fVec, m_fVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void HC_VECTORCALL SetX(float _fX) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fX)); }
	HC_INLINE void HC_VECTORCALL SetY(float _fY) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fY)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetZ(float _fZ) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fZ)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetW(float _fW) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fW)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(0, 2, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetR(float _fR) { m_fVec = _mm_move_ss(m_fVec, _mm_set_ss(_fR)); }
	HC_INLINE void HC_VECTORCALL SetG(float _fG) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fG)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 2, 0, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetB(float _fB) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fB)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(3, 0, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE void HC_VECTORCALL SetA(float _fA) { __m128 fTemp = _mm_move_ss(m_fVec, _mm_set_ss(_fA)); fTemp = _mm_shuffle_ps(fTemp, fTemp, _MM_SHUFFLE(0, 2, 1, 0)); m_fVec = _mm_move_ss(fTemp, m_fVec); }
	HC_INLINE Vec2F HC_VECTORCALL XX() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL YY() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL ZZ() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F HC_VECTORCALL WW() const { return HC_SHUFFLE2F(*this, 3, 3); }
	HC_INLINE Vec2F HC_VECTORCALL XY() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F HC_VECTORCALL XZ() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F HC_VECTORCALL XW() const { return HC_SHUFFLE2F(*this, 0, 3); }
	HC_INLINE Vec2F HC_VECTORCALL YX() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F HC_VECTORCALL YZ() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F HC_VECTORCALL YW() const { return HC_SHUFFLE2F(*this, 1, 3); }
	HC_INLINE Vec2F HC_VECTORCALL ZX() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F HC_VECTORCALL ZY() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F HC_VECTORCALL ZW() const { return HC_SHUFFLE2F(*this, 2, 3); }
	HC_INLINE Vec2F HC_VECTORCALL WX() const { return HC_SHUFFLE2F(*this, 3, 0); }
	HC_INLINE Vec2F HC_VECTORCALL WY() const { return HC_SHUFFLE2F(*this, 3, 1); }
	HC_INLINE Vec2F HC_VECTORCALL WZ() const { return HC_SHUFFLE2F(*this, 3, 2); }
	HC_INLINE Vec2F HC_VECTORCALL RR() const { return HC_SHUFFLE2F(*this, 0, 0); }
	HC_INLINE Vec2F HC_VECTORCALL GG() const { return HC_SHUFFLE2F(*this, 1, 1); }
	HC_INLINE Vec2F HC_VECTORCALL BB() const { return HC_SHUFFLE2F(*this, 2, 2); }
	HC_INLINE Vec2F HC_VECTORCALL AA() const { return HC_SHUFFLE2F(*this, 3, 3); }
	HC_INLINE Vec2F HC_VECTORCALL RG() const { return HC_SHUFFLE2F(*this, 0, 1); }
	HC_INLINE Vec2F HC_VECTORCALL RB() const { return HC_SHUFFLE2F(*this, 0, 2); }
	HC_INLINE Vec2F HC_VECTORCALL RA() const { return HC_SHUFFLE2F(*this, 0, 3); }
	HC_INLINE Vec2F HC_VECTORCALL GR() const { return HC_SHUFFLE2F(*this, 1, 0); }
	HC_INLINE Vec2F HC_VECTORCALL GB() const { return HC_SHUFFLE2F(*this, 1, 2); }
	HC_INLINE Vec2F HC_VECTORCALL GA() const { return HC_SHUFFLE2F(*this, 1, 3); }
	HC_INLINE Vec2F HC_VECTORCALL BR() const { return HC_SHUFFLE2F(*this, 2, 0); }
	HC_INLINE Vec2F HC_VECTORCALL BG() const { return HC_SHUFFLE2F(*this, 2, 1); }
	HC_INLINE Vec2F HC_VECTORCALL BA() const { return HC_SHUFFLE2F(*this, 2, 3); }
	HC_INLINE Vec2F HC_VECTORCALL AR() const { return HC_SHUFFLE2F(*this, 3, 0); }
	HC_INLINE Vec2F HC_VECTORCALL AG() const { return HC_SHUFFLE2F(*this, 3, 1); }
	HC_INLINE Vec2F HC_VECTORCALL AB() const { return HC_SHUFFLE2F(*this, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XXX() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XXY() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XXZ() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XXW() const { return HC_SHUFFLE3F(*this, 0, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL XYX() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XYY() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XYZ() const { return HC_SHUFFLE3F(*this, 0, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XYW() const { return HC_SHUFFLE3F(*this, 0, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL XZX() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XZY() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XZZ() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XZW() const { return HC_SHUFFLE3F(*this, 0, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL XWX() const { return HC_SHUFFLE3F(*this, 0, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL XWY() const { return HC_SHUFFLE3F(*this, 0, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL XWZ() const { return HC_SHUFFLE3F(*this, 0, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL XWW() const { return HC_SHUFFLE3F(*this, 0, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL YXX() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YXY() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YXZ() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YXW() const { return HC_SHUFFLE3F(*this, 1, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL YYX() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YYY() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YYZ() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YYW() const { return HC_SHUFFLE3F(*this, 1, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL YZX() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YZY() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YZZ() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YZW() const { return HC_SHUFFLE3F(*this, 1, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL YWX() const { return HC_SHUFFLE3F(*this, 1, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL YWY() const { return HC_SHUFFLE3F(*this, 1, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL YWZ() const { return HC_SHUFFLE3F(*this, 1, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL YWW() const { return HC_SHUFFLE3F(*this, 1, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ZXX() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZXY() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZXW() const { return HC_SHUFFLE3F(*this, 2, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ZYX() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZYY() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZYW() const { return HC_SHUFFLE3F(*this, 2, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ZZX() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZZY() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZZW() const { return HC_SHUFFLE3F(*this, 2, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ZWX() const { return HC_SHUFFLE3F(*this, 2, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ZWY() const { return HC_SHUFFLE3F(*this, 2, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ZWZ() const { return HC_SHUFFLE3F(*this, 2, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ZWW() const { return HC_SHUFFLE3F(*this, 2, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL WXX() const { return HC_SHUFFLE3F(*this, 3, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL WXY() const { return HC_SHUFFLE3F(*this, 3, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL WXZ() const { return HC_SHUFFLE3F(*this, 3, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL WXW() const { return HC_SHUFFLE3F(*this, 3, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL WYX() const { return HC_SHUFFLE3F(*this, 3, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL WYY() const { return HC_SHUFFLE3F(*this, 3, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL WYZ() const { return HC_SHUFFLE3F(*this, 3, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL WYW() const { return HC_SHUFFLE3F(*this, 3, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL WZX() const { return HC_SHUFFLE3F(*this, 3, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL WZY() const { return HC_SHUFFLE3F(*this, 3, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL WZZ() const { return HC_SHUFFLE3F(*this, 3, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL WZW() const { return HC_SHUFFLE3F(*this, 3, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL WWX() const { return HC_SHUFFLE3F(*this, 3, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL WWY() const { return HC_SHUFFLE3F(*this, 3, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL WWZ() const { return HC_SHUFFLE3F(*this, 3, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL WWW() const { return HC_SHUFFLE3F(*this, 3, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL RRR() const { return HC_SHUFFLE3F(*this, 0, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RRG() const { return HC_SHUFFLE3F(*this, 0, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RRB() const { return HC_SHUFFLE3F(*this, 0, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RRA() const { return HC_SHUFFLE3F(*this, 0, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL RGR() const { return HC_SHUFFLE3F(*this, 0, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RGG() const { return HC_SHUFFLE3F(*this, 0, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RGA() const { return HC_SHUFFLE3F(*this, 0, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RGB() const { return HC_SHUFFLE3F(*this, 0, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL RBR() const { return HC_SHUFFLE3F(*this, 0, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RBG() const { return HC_SHUFFLE3F(*this, 0, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RBB() const { return HC_SHUFFLE3F(*this, 0, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RBA() const { return HC_SHUFFLE3F(*this, 0, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL RAR() const { return HC_SHUFFLE3F(*this, 0, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL RAG() const { return HC_SHUFFLE3F(*this, 0, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL RAB() const { return HC_SHUFFLE3F(*this, 0, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL RAA() const { return HC_SHUFFLE3F(*this, 0, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL GRR() const { return HC_SHUFFLE3F(*this, 1, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GRG() const { return HC_SHUFFLE3F(*this, 1, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GRB() const { return HC_SHUFFLE3F(*this, 1, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GRA() const { return HC_SHUFFLE3F(*this, 1, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL GGR() const { return HC_SHUFFLE3F(*this, 1, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GGG() const { return HC_SHUFFLE3F(*this, 1, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GGB() const { return HC_SHUFFLE3F(*this, 1, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GGA() const { return HC_SHUFFLE3F(*this, 1, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL GBR() const { return HC_SHUFFLE3F(*this, 1, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GBG() const { return HC_SHUFFLE3F(*this, 1, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GBB() const { return HC_SHUFFLE3F(*this, 1, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GBA() const { return HC_SHUFFLE3F(*this, 1, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL GAR() const { return HC_SHUFFLE3F(*this, 1, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL GAG() const { return HC_SHUFFLE3F(*this, 1, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL GAB() const { return HC_SHUFFLE3F(*this, 1, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL GAA() const { return HC_SHUFFLE3F(*this, 1, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL BRR() const { return HC_SHUFFLE3F(*this, 2, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BRG() const { return HC_SHUFFLE3F(*this, 2, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BRB() const { return HC_SHUFFLE3F(*this, 2, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BRA() const { return HC_SHUFFLE3F(*this, 2, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL BGR() const { return HC_SHUFFLE3F(*this, 2, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BGG() const { return HC_SHUFFLE3F(*this, 2, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BGB() const { return HC_SHUFFLE3F(*this, 2, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BGA() const { return HC_SHUFFLE3F(*this, 2, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL BBR() const { return HC_SHUFFLE3F(*this, 2, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BBG() const { return HC_SHUFFLE3F(*this, 2, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BBB() const { return HC_SHUFFLE3F(*this, 2, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BBA() const { return HC_SHUFFLE3F(*this, 2, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL BAR() const { return HC_SHUFFLE3F(*this, 2, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL BAG() const { return HC_SHUFFLE3F(*this, 2, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL BAB() const { return HC_SHUFFLE3F(*this, 2, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL BAA() const { return HC_SHUFFLE3F(*this, 2, 3, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ARR() const { return HC_SHUFFLE3F(*this, 3, 0, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ARG() const { return HC_SHUFFLE3F(*this, 3, 0, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ARB() const { return HC_SHUFFLE3F(*this, 3, 0, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ARA() const { return HC_SHUFFLE3F(*this, 3, 0, 3); }
	HC_INLINE Vec3F HC_VECTORCALL AGR() const { return HC_SHUFFLE3F(*this, 3, 1, 0); }
	HC_INLINE Vec3F HC_VECTORCALL AGG() const { return HC_SHUFFLE3F(*this, 3, 1, 1); }
	HC_INLINE Vec3F HC_VECTORCALL AGB() const { return HC_SHUFFLE3F(*this, 3, 1, 2); }
	HC_INLINE Vec3F HC_VECTORCALL AGA() const { return HC_SHUFFLE3F(*this, 3, 1, 3); }
	HC_INLINE Vec3F HC_VECTORCALL ABR() const { return HC_SHUFFLE3F(*this, 3, 2, 0); }
	HC_INLINE Vec3F HC_VECTORCALL ABG() const { return HC_SHUFFLE3F(*this, 3, 2, 1); }
	HC_INLINE Vec3F HC_VECTORCALL ABB() const { return HC_SHUFFLE3F(*this, 3, 2, 2); }
	HC_INLINE Vec3F HC_VECTORCALL ABA() const { return HC_SHUFFLE3F(*this, 3, 2, 3); }
	HC_INLINE Vec3F HC_VECTORCALL AAR() const { return HC_SHUFFLE3F(*this, 3, 3, 0); }
	HC_INLINE Vec3F HC_VECTORCALL AAG() const { return HC_SHUFFLE3F(*this, 3, 3, 1); }
	HC_INLINE Vec3F HC_VECTORCALL AAB() const { return HC_SHUFFLE3F(*this, 3, 3, 2); }
	HC_INLINE Vec3F HC_VECTORCALL AAA() const { return HC_SHUFFLE3F(*this, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XXXX() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XXXY() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XXXZ() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XXXW() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XXYX() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XXYY() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XXYZ() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XXYW() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XXZX() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XXZY() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XXZZ() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XXZW() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XXWX() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XXWY() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XXWZ() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XXWW() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XYXX() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XYXY() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XYXZ() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XYXW() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XYYX() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XYYY() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XYYZ() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XYYW() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XYZX() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XYZY() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XYZZ() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XYWX() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XYWY() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XYWZ() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XYWW() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XZXX() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XZXY() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XZXZ() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XZXW() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XZYX() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XZYY() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XZYZ() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XZYW() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XZZX() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XZZY() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XZZZ() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XZZW() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XZWX() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XZWY() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XZWZ() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XZWW() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XWXX() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XWXY() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XWXZ() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XWXW() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XWYX() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XWYY() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XWYZ() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XWYW() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XWZX() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XWZY() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XWZZ() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XWZW() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL XWWX() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL XWWY() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL XWWZ() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL XWWW() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YXXX() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YXXY() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YXXZ() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YXXW() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YXYX() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YXYY() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YXYZ() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YXYW() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YXZX() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YXZY() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YXZZ() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YXZW() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YXWX() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YXWY() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YXWZ() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YXWW() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YYXX() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YYXY() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YYXZ() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YYXW() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YYYX() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YYYY() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YYYZ() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YYYW() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YYZX() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YYZY() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YYZZ() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YYZW() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YYWX() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YYWY() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YYWZ() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YYWW() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YZXX() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YZXY() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YZXZ() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YZXW() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YZYX() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YZYY() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YZYZ() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YZYW() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YZZX() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YZZY() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YZZZ() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YZZW() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YZWX() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YZWY() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YZWZ() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YZWW() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YWXX() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YWXY() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YWXZ() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YWXW() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YWYX() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YWYY() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YWYZ() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YWYW() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YWZX() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YWZY() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YWZZ() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YWZW() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL YWWX() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL YWWY() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL YWWZ() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL YWWW() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZXXX() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZXXY() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZXXZ() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZXXW() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZXYX() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZXYY() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZXYZ() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZXYW() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZXZX() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZXZY() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZXZZ() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZXZW() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZXWX() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZXWY() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZXWZ() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZXWW() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZYXX() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZYXY() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZYXZ() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZYXW() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZYYX() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZYYY() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZYYZ() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZYYW() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZYZX() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZYZY() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZYZZ() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZYZW() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZYWX() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZYWY() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZYWZ() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZYWW() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZZXX() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZZXY() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZZXZ() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZZXW() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZZYX() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZZYY() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZZYZ() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZZYW() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZZZX() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZZZY() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZZZZ() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZZZW() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZZWX() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZZWY() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZZWZ() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZZWW() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZWXX() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZWXY() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZWXZ() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZWXW() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZWYX() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZWYY() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZWYZ() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZWYW() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZWZX() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZWZY() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZWZZ() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZWZW() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ZWWX() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ZWWY() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ZWWZ() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ZWWW() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WXXX() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WXXY() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WXXZ() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WXXW() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WXYX() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WXYY() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WXYZ() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WXYW() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WXZX() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WXZY() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WXZZ() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WXZW() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WXWX() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WXWY() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WXWZ() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WXWW() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WYXX() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WYXY() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WYXZ() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WYXW() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WYYX() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WYYY() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WYYZ() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WYYW() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WYZX() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WYZY() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WYZZ() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WYZW() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WYWX() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WYWY() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WYWZ() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WYWW() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WZXX() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WZXY() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WZXZ() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WZXW() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WZYX() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WZYY() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WZYZ() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WZYW() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WZZX() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WZZY() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WZZZ() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WZZW() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WZWX() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WZWY() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WZWZ() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WZWW() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WWXX() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WWXY() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WWXZ() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WWXW() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WWYX() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WWYY() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WWYZ() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WWYW() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WWZX() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WWZY() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WWZZ() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WWZW() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL WWWX() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL WWWY() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL WWWZ() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL WWWW() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RRRR() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RRRG() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RRRB() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RRRA() const { return HC_SHUFFLE4F(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RRGR() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RRGG() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RRGB() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RRGA() const { return HC_SHUFFLE4F(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RRBR() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RRBG() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RRBB() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RRBA() const { return HC_SHUFFLE4F(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RRAR() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RRAG() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RRAB() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RRAA() const { return HC_SHUFFLE4F(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RGRR() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RGRG() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RGRB() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RGRA() const { return HC_SHUFFLE4F(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RGGR() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RGGG() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RGGB() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RGGA() const { return HC_SHUFFLE4F(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RGBR() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RGBG() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RGBB() const { return HC_SHUFFLE4F(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RGAR() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RGAG() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RGAB() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RGAA() const { return HC_SHUFFLE4F(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RBRR() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RBRG() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RBRB() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RBRA() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RBGR() const { return HC_SHUFFLE4F(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RBGG() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RBGB() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RBGA() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RBBR() const { return HC_SHUFFLE4F(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RBBG() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RBBB() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RBBA() const { return HC_SHUFFLE4F(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RBAR() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RBAG() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RBAB() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RBAA() const { return HC_SHUFFLE4F(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RARR() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RARG() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RARB() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RARA() const { return HC_SHUFFLE4F(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RAGR() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RAGG() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RAGB() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RAGA() const { return HC_SHUFFLE4F(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RABR() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RABG() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RABB() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RABA() const { return HC_SHUFFLE4F(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL RAAR() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL RAAG() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL RAAB() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL RAAA() const { return HC_SHUFFLE4F(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GRRR() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GRRG() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GRRB() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GRRA() const { return HC_SHUFFLE4F(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GRGR() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GRGG() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GRGB() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GRGA() const { return HC_SHUFFLE4F(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GRBR() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GRBG() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GRBB() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GRBA() const { return HC_SHUFFLE4F(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GRAR() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GRAG() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GRAB() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GRAA() const { return HC_SHUFFLE4F(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GGRR() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GGRG() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GGRB() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GGRA() const { return HC_SHUFFLE4F(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GGGR() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GGGG() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GGGB() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GGGA() const { return HC_SHUFFLE4F(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GGBR() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GGBG() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GGBB() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GGBA() const { return HC_SHUFFLE4F(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GGAR() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GGAG() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GGAB() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GGAA() const { return HC_SHUFFLE4F(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GBRR() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GBRG() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GBRB() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GBRA() const { return HC_SHUFFLE4F(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GBGR() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GBGG() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GBGB() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GBGA() const { return HC_SHUFFLE4F(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GBBR() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GBBG() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GBBB() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GBBA() const { return HC_SHUFFLE4F(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GBAR() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GBAG() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GBAB() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GBAA() const { return HC_SHUFFLE4F(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GARR() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GARG() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GARB() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GARA() const { return HC_SHUFFLE4F(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GAGR() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GAGG() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GAGB() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GAGA() const { return HC_SHUFFLE4F(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GABR() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GABG() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GABB() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GABA() const { return HC_SHUFFLE4F(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL GAAR() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL GAAG() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL GAAB() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL GAAA() const { return HC_SHUFFLE4F(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BRRR() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BRRG() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BRRB() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BRRA() const { return HC_SHUFFLE4F(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BRGR() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BRGG() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BRGB() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BRGA() const { return HC_SHUFFLE4F(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BRBR() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BRBG() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BRBB() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BRBA() const { return HC_SHUFFLE4F(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BRAR() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BRAG() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BRAB() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BRAA() const { return HC_SHUFFLE4F(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BGRR() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BGRG() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BGRB() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BGRA() const { return HC_SHUFFLE4F(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BGGR() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BGGG() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BGGB() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BGGA() const { return HC_SHUFFLE4F(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BGBR() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BGBG() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BGBB() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BGBA() const { return HC_SHUFFLE4F(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BGAR() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BGAG() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BGAB() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BGAA() const { return HC_SHUFFLE4F(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BBRR() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BBRG() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BBRB() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BBRA() const { return HC_SHUFFLE4F(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BBGR() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BBGG() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BBGB() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BBGA() const { return HC_SHUFFLE4F(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BBBR() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BBBG() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BBBB() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BBBA() const { return HC_SHUFFLE4F(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BBAR() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BBAG() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BBAB() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BBAA() const { return HC_SHUFFLE4F(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BARR() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BARG() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BARB() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BARA() const { return HC_SHUFFLE4F(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BAGR() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BAGG() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BAGB() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BAGA() const { return HC_SHUFFLE4F(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BABR() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BABG() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BABB() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BABA() const { return HC_SHUFFLE4F(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL BAAR() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL BAAG() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL BAAB() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL BAAA() const { return HC_SHUFFLE4F(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ARRR() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ARRG() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ARRB() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ARRA() const { return HC_SHUFFLE4F(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ARGR() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ARGG() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ARGB() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ARGA() const { return HC_SHUFFLE4F(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ARBR() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ARBG() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ARBB() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ARBA() const { return HC_SHUFFLE4F(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ARAR() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ARAG() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ARAB() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ARAA() const { return HC_SHUFFLE4F(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AGRR() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AGRG() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AGRB() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AGRA() const { return HC_SHUFFLE4F(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AGGR() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AGGG() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AGGB() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AGGA() const { return HC_SHUFFLE4F(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AGBR() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AGBG() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AGBB() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AGBA() const { return HC_SHUFFLE4F(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AGAR() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AGAG() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AGAB() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AGAA() const { return HC_SHUFFLE4F(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ABRR() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ABRG() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ABRB() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ABRA() const { return HC_SHUFFLE4F(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ABGR() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ABGG() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ABGB() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ABGA() const { return HC_SHUFFLE4F(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ABBR() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ABBG() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ABBB() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ABBA() const { return HC_SHUFFLE4F(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL ABAR() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL ABAG() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL ABAB() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL ABAA() const { return HC_SHUFFLE4F(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AARR() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AARG() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AARB() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AARA() const { return HC_SHUFFLE4F(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AAGR() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AAGG() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AAGB() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AAGA() const { return HC_SHUFFLE4F(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AABR() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AABG() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AABB() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AABA() const { return HC_SHUFFLE4F(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4F HC_VECTORCALL AAAR() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4F HC_VECTORCALL AAAG() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4F HC_VECTORCALL AAAB() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4F HC_VECTORCALL AAAA() const { return HC_SHUFFLE4F(*this, 3, 3, 3, 3); }
};

#if HC_ENABLE_EXTRA_VECTOR_TYPES && HC_USE_SIMD

struct Vec2D {
	__m256d m_dVec;

	HC_INLINE HC_VECTORCALL Vec2D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit HC_VECTORCALL Vec2D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec2D(double _dX, double _dY) { m_dVec = _mm256_set_pd(_dY, _dY, _dY, _dX); }
	HC_INLINE explicit HC_VECTORCALL Vec2D(float _fX, float _fY) { m_dVec = _mm256_set_pd(static_cast<double>(_fY), static_cast<double>(_fY), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit HC_VECTORCALL Vec2D(int _iX, int _iY) { m_dVec = _mm256_set_pd(static_cast<double>(_iY), static_cast<double>(_iY), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec2D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 2); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 2); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void HC_VECTORCALL SetX(double _dX) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dX); }
	HC_INLINE void HC_VECTORCALL SetY(double _dY) { m_dVec = _mm256_set_pd(_dY, _dY, _dY, X()); }
	HC_INLINE void HC_VECTORCALL SetR(double _dR) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dR); }
	HC_INLINE void HC_VECTORCALL SetG(double _dG) { m_dVec = _mm256_set_pd(_dG, _dG, _dG, X()); }
	HC_INLINE Vec2D HC_VECTORCALL XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
};

struct Vec3D {
	__m256d m_dVec;

	HC_INLINE HC_VECTORCALL Vec3D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit HC_VECTORCALL Vec3D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec3D(double _dX, double _dY, double _dZ) { m_dVec = _mm256_set_pd(_dZ, _dZ, _dY, _dX); }
	HC_INLINE explicit HC_VECTORCALL Vec3D(float _fX, float _fY, float _fZ) { m_dVec = _mm256_set_pd(static_cast<double>(_fZ), static_cast<double>(_fZ), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit HC_VECTORCALL Vec3D(int _iX, int _iY, int _iZ) { m_dVec = _mm256_set_pd(static_cast<double>(_iZ), static_cast<double>(_iZ), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec3D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 3); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 3); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL Z() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double HC_VECTORCALL R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL B() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void HC_VECTORCALL SetX(double _dX) { m_dVec = _mm256_set_pd(Z(), Z(), Y(), _dX); }
	HC_INLINE void HC_VECTORCALL SetY(double _dY) { m_dVec = _mm256_set_pd(Z(), Z(), _dY, X()); }
	HC_INLINE void HC_VECTORCALL SetZ(double _dZ) { m_dVec = _mm256_set_pd(_dZ, _dZ, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetR(double _dR) { m_dVec = _mm256_set_pd(Y(), Y(), Y(), _dR); }
	HC_INLINE void HC_VECTORCALL SetG(double _dG) { m_dVec = _mm256_set_pd(Z(), Z(), _dG, X()); }
	HC_INLINE void HC_VECTORCALL SetB(double _dB) { m_dVec = _mm256_set_pd(_dB, _dB, Y(), X()); }
	HC_INLINE Vec2D HC_VECTORCALL XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL ZZ() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL XY() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL XZ() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YZ() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL ZX() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL ZY() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D HC_VECTORCALL RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL BB() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL RG() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL RB() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GB() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL BR() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL BG() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XXX() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XXY() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XXZ() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XYX() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XYY() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XZX() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XZY() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XZZ() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YXX() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YXY() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YXZ() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YYX() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YYY() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YYZ() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YZX() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YZY() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YZZ() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZXX() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZXY() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZYX() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZYY() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZZX() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZZY() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RRR() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RRG() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RRB() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RGR() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RGG() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RBR() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RBG() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RBB() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GRR() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GRG() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GRB() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GGR() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GGG() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GGB() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GBR() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GBG() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GBB() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BRR() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BRG() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BRB() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BGR() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BGG() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BGB() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BBR() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BBG() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BBB() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
};

struct Vec4D {
	__m256d m_dVec;

	HC_INLINE HC_VECTORCALL Vec4D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(double _dX, double _dY, double _dZ, double _dA) { m_dVec = _mm256_set_pd(_dA, _dZ, _dY, _dX); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(float _fX, float _fY, float _fZ, float _fA) { m_dVec = _mm256_set_pd(static_cast<double>(_fA), static_cast<double>(_fZ), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(int _iX, int _iY, int _iZ, int _iA) { m_dVec = _mm256_set_pd(static_cast<double>(_iA), static_cast<double>(_iZ), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL Z() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double HC_VECTORCALL W() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE double HC_VECTORCALL R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL B() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double HC_VECTORCALL A() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void HC_VECTORCALL SetX(double _dX) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dX); }
	HC_INLINE void HC_VECTORCALL SetY(double _dY) { m_dVec = _mm256_set_pd(W(), Z(), _dY, X()); }
	HC_INLINE void HC_VECTORCALL SetZ(double _dZ) { m_dVec = _mm256_set_pd(W(), _dZ, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetW(double _dW) { m_dVec = _mm256_set_pd(_dW, Z(), Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetR(double _dR) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dR); }
	HC_INLINE void HC_VECTORCALL SetG(double _dG) { m_dVec = _mm256_set_pd(W(), Z(), _dG, X()); }
	HC_INLINE void HC_VECTORCALL SetB(double _dB) { m_dVec = _mm256_set_pd(W(), _dB, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetA(double _dA) { m_dVec = _mm256_set_pd(_dA, Z(), Y(), X()); }
	HC_INLINE Vec2D HC_VECTORCALL XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL ZZ() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL WW() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D HC_VECTORCALL XY() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL XZ() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL XW() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D HC_VECTORCALL YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YZ() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL YW() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D HC_VECTORCALL ZX() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL ZY() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D HC_VECTORCALL ZW() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D HC_VECTORCALL WX() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D HC_VECTORCALL WY() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D HC_VECTORCALL WZ() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec2D HC_VECTORCALL RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL BB() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL AA() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D HC_VECTORCALL RG() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL RB() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL RA() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D HC_VECTORCALL GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GB() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL GA() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D HC_VECTORCALL BR() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL BG() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D HC_VECTORCALL BA() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D HC_VECTORCALL AR() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D HC_VECTORCALL AG() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D HC_VECTORCALL AB() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XXX() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XXY() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XXZ() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XXW() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XYX() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XYY() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XYZ() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XYW() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XZX() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XZY() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XZZ() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XZW() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XWX() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XWY() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XWZ() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XWW() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YXX() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YXY() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YXZ() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YXW() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YYX() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YYY() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YYZ() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YYW() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YZX() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YZY() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YZZ() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YZW() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YWX() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YWY() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YWZ() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YWW() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZXX() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZXY() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZXW() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZYX() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZYY() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZYW() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZZX() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZZY() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZZW() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZWX() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZWY() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZWZ() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZWW() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WXX() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WXY() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WXZ() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WXW() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WYX() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WYY() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WYZ() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WYW() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WZX() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WZY() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WZZ() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WZW() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WWX() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WWY() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WWZ() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WWW() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RRR() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RRG() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RRB() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RRA() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RGR() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RGG() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RGA() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RGB() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RBR() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RBG() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RBB() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RBA() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RAR() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RAG() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RAB() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RAA() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GRR() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GRG() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GRB() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GRA() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GGR() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GGG() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GGB() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GGA() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GBR() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GBG() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GBB() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GBA() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GAR() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GAG() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GAB() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GAA() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BRR() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BRG() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BRB() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BRA() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BGR() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BGG() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BGB() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BGA() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BBR() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BBG() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BBB() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BBA() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BAR() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BAG() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BAB() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BAA() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ARR() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ARG() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ARB() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ARA() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL AGR() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL AGG() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL AGB() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL AGA() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ABR() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ABG() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ABB() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ABA() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL AAR() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL AAG() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL AAB() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL AAA() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXXX() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXXY() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXXZ() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXXW() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXYX() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXYY() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXYZ() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXYW() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXZX() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXZY() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXZZ() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXZW() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXWX() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXWY() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXWZ() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXWW() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYXX() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYXY() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYXZ() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYXW() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYYX() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYYY() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYYZ() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYYW() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYZX() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYZY() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYZZ() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYWX() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYWY() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYWZ() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYWW() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZXX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZXY() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZXZ() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZXW() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZYX() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZYY() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZYZ() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZYW() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZZX() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZZY() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZZZ() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZZW() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZWX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZWY() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZWZ() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZWW() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWXX() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWXY() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWXZ() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWXW() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWYX() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWYY() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWYZ() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWYW() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWZX() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWZY() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWZZ() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWZW() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWWX() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWWY() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWWZ() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWWW() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXXX() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXXY() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXXZ() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXXW() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXYX() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXYY() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXYZ() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXYW() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXZX() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXZY() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXZZ() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXZW() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXWX() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXWY() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXWZ() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXWW() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYXX() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYXY() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYXZ() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYXW() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYYX() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYYY() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYYZ() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYYW() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYZX() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYZY() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYZZ() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYZW() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYWX() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYWY() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYWZ() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYWW() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZXX() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZXY() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZXZ() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZXW() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZYX() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZYY() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZYZ() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZYW() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZZX() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZZY() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZZZ() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZZW() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZWX() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZWY() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZWZ() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZWW() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWXX() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWXY() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWXZ() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWXW() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWYX() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWYY() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWYZ() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWYW() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWZX() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWZY() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWZZ() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWZW() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWWX() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWWY() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWWZ() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWWW() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXX() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXY() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXZ() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXW() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYX() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYY() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYZ() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYW() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZX() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZY() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZZ() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZW() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWX() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWY() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWZ() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWW() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXX() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXY() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXZ() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXW() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYX() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYY() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYZ() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYW() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZX() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZY() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZZ() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZW() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWX() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWY() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWZ() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWW() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXX() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXY() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXZ() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXW() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYX() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYY() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYZ() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYW() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZX() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZY() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZZ() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZW() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWX() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWY() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWZ() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWW() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXX() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXY() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXZ() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXW() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYX() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYY() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYZ() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYW() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZX() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZY() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZZ() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZW() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWX() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWY() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWZ() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWW() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXXX() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXXY() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXXZ() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXXW() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXYX() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXYY() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXYZ() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXYW() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXZX() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXZY() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXZZ() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXZW() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXWX() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXWY() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXWZ() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXWW() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYXX() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYXY() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYXZ() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYXW() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYYX() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYYY() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYYZ() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYYW() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYZX() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYZY() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYZZ() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYZW() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYWX() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYWY() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYWZ() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYWW() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZXX() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZXY() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZXZ() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZXW() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZYX() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZYY() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZYZ() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZYW() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZZX() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZZY() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZZZ() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZZW() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZWX() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZWY() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZWZ() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZWW() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWXX() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWXY() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWXZ() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWXW() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWYX() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWYY() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWYZ() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWYW() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWZX() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWZY() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWZZ() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWZW() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWWX() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWWY() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWWZ() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWWW() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRRR() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRRG() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRRB() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRRA() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRGR() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRGG() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRGB() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRGA() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRBR() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRBG() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRBB() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRBA() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRAR() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRAG() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRAB() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRAA() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGRR() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGRG() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGRB() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGRA() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGGR() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGGG() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGGB() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGGA() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGBR() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGBG() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGBB() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGAR() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGAG() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGAB() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGAA() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBRR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBRG() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBRB() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBRA() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBGR() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBGG() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBGB() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBGA() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBBR() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBBG() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBBB() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBBA() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBAR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBAG() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBAB() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBAA() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RARR() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RARG() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RARB() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RARA() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RAGR() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RAGG() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RAGB() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RAGA() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RABR() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RABG() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RABB() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RABA() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RAAR() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RAAG() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RAAB() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RAAA() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRRR() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRRG() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRRB() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRRA() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRGR() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRGG() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRGB() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRGA() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRBR() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRBG() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRBB() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRBA() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRAR() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRAG() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRAB() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRAA() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGRR() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGRG() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGRB() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGRA() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGGR() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGGG() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGGB() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGGA() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGBR() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGBG() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGBB() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGBA() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGAR() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGAG() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGAB() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGAA() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBRR() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBRG() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBRB() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBRA() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBGR() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBGG() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBGB() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBGA() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBBR() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBBG() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBBB() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBBA() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBAR() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBAG() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBAB() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBAA() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GARR() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GARG() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GARB() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GARA() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GAGR() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GAGG() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GAGB() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GAGA() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GABR() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GABG() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GABB() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GABA() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GAAR() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GAAG() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GAAB() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GAAA() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRRR() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRRG() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRRB() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRRA() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRGR() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRGG() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRGB() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRGA() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRBR() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRBG() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRBB() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRBA() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRAR() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRAG() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRAB() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRAA() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGRR() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGRG() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGRB() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGRA() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGGR() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGGG() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGGB() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGGA() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGBR() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGBG() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGBB() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGBA() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGAR() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGAG() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGAB() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGAA() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBRR() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBRG() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBRB() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBRA() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBGR() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBGG() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBGB() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBGA() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBBR() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBBG() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBBB() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBBA() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBAR() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBAG() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBAB() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBAA() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BARR() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BARG() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BARB() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BARA() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BAGR() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BAGG() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BAGB() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BAGA() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BABR() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BABG() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BABB() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BABA() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BAAR() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BAAG() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BAAB() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BAAA() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARRR() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARRG() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARRB() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARRA() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARGR() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARGG() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARGB() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARGA() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARBR() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARBG() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARBB() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARBA() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARAR() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARAG() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARAB() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARAA() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGRR() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGRG() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGRB() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGRA() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGGR() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGGG() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGGB() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGGA() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGBR() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGBG() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGBB() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGBA() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGAR() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGAG() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGAB() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGAA() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABRR() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABRG() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABRB() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABRA() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABGR() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABGG() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABGB() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABGA() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABBR() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABBG() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABBB() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABBA() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABAR() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABAG() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABAB() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABAA() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AARR() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AARG() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AARB() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AARA() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AAGR() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AAGG() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AAGB() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AAGA() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AABR() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AABG() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AABB() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AABA() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AAAR() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AAAG() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AAAB() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AAAA() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
};

struct Vec2I {
	__m128i m_iVec;

	HC_INLINE HC_VECTORCALL Vec2I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit HC_VECTORCALL Vec2I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[1], _pValues[1], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec2I(int _iX, int _iY) { m_iVec = _mm_set_epi32(_iY, _iY, _iY, _iX); }
	HC_INLINE explicit HC_VECTORCALL Vec2I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 2); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 2); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int HC_VECTORCALL X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int HC_VECTORCALL R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE void HC_VECTORCALL SetX(int _iX) { m_iVec = _mm_set_epi32(Y(), Y(), Y(), _iX); }
	HC_INLINE void HC_VECTORCALL SetY(int _iY) { m_iVec = _mm_set_epi32(_iY, _iY, _iY, X()); }
	HC_INLINE void HC_VECTORCALL SetR(int _iR) { m_iVec = _mm_set_epi32(Y(), Y(), Y(), _iR); }
	HC_INLINE void HC_VECTORCALL SetG(int _iG) { m_iVec = _mm_set_epi32(_iG, _iG, _iG, X()); }
	HC_INLINE Vec2I HC_VECTORCALL XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I HC_VECTORCALL RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
};

struct Vec3I {
	__m128i m_iVec;

	HC_INLINE HC_VECTORCALL Vec3I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit HC_VECTORCALL Vec3I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[2], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec3I(int _iX, int _iY, int _iZ) { m_iVec = _mm_set_epi32(_iZ, _iZ, _iY, _iX); }
	HC_INLINE explicit HC_VECTORCALL Vec3I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int HC_VECTORCALL X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int HC_VECTORCALL Z() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int HC_VECTORCALL R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int HC_VECTORCALL B() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE void HC_VECTORCALL SetX(int _iX) { m_iVec = _mm_set_epi32(Z(), Z(), Y(), _iX); }
	HC_INLINE void HC_VECTORCALL SetY(int _iY) { m_iVec = _mm_set_epi32(Z(), Z(), _iY, X()); }
	HC_INLINE void HC_VECTORCALL SetZ(int _iZ) { m_iVec = _mm_set_epi32(_iZ, _iZ, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetR(int _iR) { m_iVec = _mm_set_epi32(Z(), Z(), Y(), _iR); }
	HC_INLINE void HC_VECTORCALL SetG(int _iG) { m_iVec = _mm_set_epi32(Z(), Z(), _iG, X()); }
	HC_INLINE void HC_VECTORCALL SetB(int _iB) { m_iVec = _mm_set_epi32(_iB, _iB, Y(), X()); }
	HC_INLINE Vec2I HC_VECTORCALL XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL ZZ() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I HC_VECTORCALL XY() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I HC_VECTORCALL XZ() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I HC_VECTORCALL YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I HC_VECTORCALL YZ() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I HC_VECTORCALL ZX() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I HC_VECTORCALL ZY() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I HC_VECTORCALL RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL BB() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I HC_VECTORCALL RG() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I HC_VECTORCALL RB() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I HC_VECTORCALL GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I HC_VECTORCALL GB() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I HC_VECTORCALL BR() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I HC_VECTORCALL BG() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XXX() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XXY() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XXZ() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XYX() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XYY() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XZX() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XZY() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XZZ() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YXX() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YXY() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YXZ() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YYX() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YYY() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YYZ() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YZX() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YZY() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YZZ() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZXX() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZXY() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZYX() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZYY() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZZX() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZZY() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RRR() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RRG() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RRB() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RGR() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RGG() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RBR() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RBG() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RBB() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GRR() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GRG() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GRB() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GGR() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GGG() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GGB() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GBR() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GBG() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GBB() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BRR() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BRG() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BRB() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BGR() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BGG() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BGB() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BBR() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BBG() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BBB() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
};

struct Vec4I {
	__m128i m_iVec;

	HC_INLINE HC_VECTORCALL Vec4I() { m_iVec = _mm_setzero_si128(); }
	HC_INLINE explicit HC_VECTORCALL Vec4I(const int* _pValues) { m_iVec = _mm_set_epi32(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec4I(int _iX, int _iY, int _iZ, int _iW) { m_iVec = _mm_set_epi32(_iW, _iZ, _iY, _iX); }
	HC_INLINE explicit HC_VECTORCALL Vec4I(__m128i _vData) { m_iVec = _vData; }
	HC_INLINE int HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 3); return m_iVec.m128i_i32[_iNdx]; }
	HC_INLINE int HC_VECTORCALL X() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL Y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int HC_VECTORCALL Z() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int HC_VECTORCALL W() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE int HC_VECTORCALL R() const { return _mm_cvtsi128_si32(m_iVec); }
	HC_INLINE int HC_VECTORCALL G() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE int HC_VECTORCALL B() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE int HC_VECTORCALL A() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_iVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void HC_VECTORCALL SetX(int _iX) { m_iVec = _mm_set_epi32(W(), Z(), Y(), _iX); }
	HC_INLINE void HC_VECTORCALL SetY(int _iY) { m_iVec = _mm_set_epi32(W(), Z(), _iY, X()); }
	HC_INLINE void HC_VECTORCALL SetZ(int _iZ) { m_iVec = _mm_set_epi32(W(), _iZ, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetW(int _iW) { m_iVec = _mm_set_epi32(_iW, W(), Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetR(int _iR) { m_iVec = _mm_set_epi32(W(), Z(), Y(), _iR); }
	HC_INLINE void HC_VECTORCALL SetG(int _iG) { m_iVec = _mm_set_epi32(W(), Z(), _iG, X()); }
	HC_INLINE void HC_VECTORCALL SetB(int _iB) { m_iVec = _mm_set_epi32(W(), _iB, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetA(int _iA) { m_iVec = _mm_set_epi32(_iA, Z(), Y(), X()); }
	HC_INLINE Vec2I HC_VECTORCALL XX() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL YY() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL ZZ() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I HC_VECTORCALL WW() const { return HC_SHUFFLE2I(*this, 3, 3); }
	HC_INLINE Vec2I HC_VECTORCALL XY() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I HC_VECTORCALL XZ() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I HC_VECTORCALL XW() const { return HC_SHUFFLE2I(*this, 0, 3); }
	HC_INLINE Vec2I HC_VECTORCALL YX() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I HC_VECTORCALL YZ() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I HC_VECTORCALL YW() const { return HC_SHUFFLE2I(*this, 1, 3); }
	HC_INLINE Vec2I HC_VECTORCALL ZX() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I HC_VECTORCALL ZY() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I HC_VECTORCALL ZW() const { return HC_SHUFFLE2I(*this, 2, 3); }
	HC_INLINE Vec2I HC_VECTORCALL WX() const { return HC_SHUFFLE2I(*this, 3, 0); }
	HC_INLINE Vec2I HC_VECTORCALL WY() const { return HC_SHUFFLE2I(*this, 3, 1); }
	HC_INLINE Vec2I HC_VECTORCALL WZ() const { return HC_SHUFFLE2I(*this, 3, 2); }
	HC_INLINE Vec2I HC_VECTORCALL RR() const { return HC_SHUFFLE2I(*this, 0, 0); }
	HC_INLINE Vec2I HC_VECTORCALL GG() const { return HC_SHUFFLE2I(*this, 1, 1); }
	HC_INLINE Vec2I HC_VECTORCALL BB() const { return HC_SHUFFLE2I(*this, 2, 2); }
	HC_INLINE Vec2I HC_VECTORCALL AA() const { return HC_SHUFFLE2I(*this, 3, 3); }
	HC_INLINE Vec2I HC_VECTORCALL RG() const { return HC_SHUFFLE2I(*this, 0, 1); }
	HC_INLINE Vec2I HC_VECTORCALL RB() const { return HC_SHUFFLE2I(*this, 0, 2); }
	HC_INLINE Vec2I HC_VECTORCALL RA() const { return HC_SHUFFLE2I(*this, 0, 3); }
	HC_INLINE Vec2I HC_VECTORCALL GR() const { return HC_SHUFFLE2I(*this, 1, 0); }
	HC_INLINE Vec2I HC_VECTORCALL GB() const { return HC_SHUFFLE2I(*this, 1, 2); }
	HC_INLINE Vec2I HC_VECTORCALL GA() const { return HC_SHUFFLE2I(*this, 1, 3); }
	HC_INLINE Vec2I HC_VECTORCALL BR() const { return HC_SHUFFLE2I(*this, 2, 0); }
	HC_INLINE Vec2I HC_VECTORCALL BG() const { return HC_SHUFFLE2I(*this, 2, 1); }
	HC_INLINE Vec2I HC_VECTORCALL BA() const { return HC_SHUFFLE2I(*this, 2, 3); }
	HC_INLINE Vec2I HC_VECTORCALL AR() const { return HC_SHUFFLE2I(*this, 3, 0); }
	HC_INLINE Vec2I HC_VECTORCALL AG() const { return HC_SHUFFLE2I(*this, 3, 1); }
	HC_INLINE Vec2I HC_VECTORCALL AB() const { return HC_SHUFFLE2I(*this, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XXX() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XXY() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XXZ() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XXW() const { return HC_SHUFFLE3I(*this, 0, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL XYX() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XYY() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XYZ() const { return HC_SHUFFLE3I(*this, 0, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XYW() const { return HC_SHUFFLE3I(*this, 0, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL XZX() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XZY() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XZZ() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XZW() const { return HC_SHUFFLE3I(*this, 0, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL XWX() const { return HC_SHUFFLE3I(*this, 0, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL XWY() const { return HC_SHUFFLE3I(*this, 0, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL XWZ() const { return HC_SHUFFLE3I(*this, 0, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL XWW() const { return HC_SHUFFLE3I(*this, 0, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL YXX() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YXY() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YXZ() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YXW() const { return HC_SHUFFLE3I(*this, 1, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL YYX() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YYY() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YYZ() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YYW() const { return HC_SHUFFLE3I(*this, 1, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL YZX() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YZY() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YZZ() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YZW() const { return HC_SHUFFLE3I(*this, 1, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL YWX() const { return HC_SHUFFLE3I(*this, 1, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL YWY() const { return HC_SHUFFLE3I(*this, 1, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL YWZ() const { return HC_SHUFFLE3I(*this, 1, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL YWW() const { return HC_SHUFFLE3I(*this, 1, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ZXX() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZXY() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZXW() const { return HC_SHUFFLE3I(*this, 2, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ZYX() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZYY() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZYW() const { return HC_SHUFFLE3I(*this, 2, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ZZX() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZZY() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZZW() const { return HC_SHUFFLE3I(*this, 2, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ZWX() const { return HC_SHUFFLE3I(*this, 2, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ZWY() const { return HC_SHUFFLE3I(*this, 2, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ZWZ() const { return HC_SHUFFLE3I(*this, 2, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ZWW() const { return HC_SHUFFLE3I(*this, 2, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL WXX() const { return HC_SHUFFLE3I(*this, 3, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL WXY() const { return HC_SHUFFLE3I(*this, 3, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL WXZ() const { return HC_SHUFFLE3I(*this, 3, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL WXW() const { return HC_SHUFFLE3I(*this, 3, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL WYX() const { return HC_SHUFFLE3I(*this, 3, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL WYY() const { return HC_SHUFFLE3I(*this, 3, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL WYZ() const { return HC_SHUFFLE3I(*this, 3, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL WYW() const { return HC_SHUFFLE3I(*this, 3, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL WZX() const { return HC_SHUFFLE3I(*this, 3, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL WZY() const { return HC_SHUFFLE3I(*this, 3, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL WZZ() const { return HC_SHUFFLE3I(*this, 3, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL WZW() const { return HC_SHUFFLE3I(*this, 3, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL WWX() const { return HC_SHUFFLE3I(*this, 3, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL WWY() const { return HC_SHUFFLE3I(*this, 3, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL WWZ() const { return HC_SHUFFLE3I(*this, 3, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL WWW() const { return HC_SHUFFLE3I(*this, 3, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL RRR() const { return HC_SHUFFLE3I(*this, 0, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RRG() const { return HC_SHUFFLE3I(*this, 0, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RRB() const { return HC_SHUFFLE3I(*this, 0, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RRA() const { return HC_SHUFFLE3I(*this, 0, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL RGR() const { return HC_SHUFFLE3I(*this, 0, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RGG() const { return HC_SHUFFLE3I(*this, 0, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RGA() const { return HC_SHUFFLE3I(*this, 0, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RGB() const { return HC_SHUFFLE3I(*this, 0, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL RBR() const { return HC_SHUFFLE3I(*this, 0, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RBG() const { return HC_SHUFFLE3I(*this, 0, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RBB() const { return HC_SHUFFLE3I(*this, 0, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RBA() const { return HC_SHUFFLE3I(*this, 0, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL RAR() const { return HC_SHUFFLE3I(*this, 0, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL RAG() const { return HC_SHUFFLE3I(*this, 0, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL RAB() const { return HC_SHUFFLE3I(*this, 0, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL RAA() const { return HC_SHUFFLE3I(*this, 0, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL GRR() const { return HC_SHUFFLE3I(*this, 1, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GRG() const { return HC_SHUFFLE3I(*this, 1, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GRB() const { return HC_SHUFFLE3I(*this, 1, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GRA() const { return HC_SHUFFLE3I(*this, 1, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL GGR() const { return HC_SHUFFLE3I(*this, 1, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GGG() const { return HC_SHUFFLE3I(*this, 1, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GGB() const { return HC_SHUFFLE3I(*this, 1, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GGA() const { return HC_SHUFFLE3I(*this, 1, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL GBR() const { return HC_SHUFFLE3I(*this, 1, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GBG() const { return HC_SHUFFLE3I(*this, 1, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GBB() const { return HC_SHUFFLE3I(*this, 1, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GBA() const { return HC_SHUFFLE3I(*this, 1, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL GAR() const { return HC_SHUFFLE3I(*this, 1, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL GAG() const { return HC_SHUFFLE3I(*this, 1, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL GAB() const { return HC_SHUFFLE3I(*this, 1, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL GAA() const { return HC_SHUFFLE3I(*this, 1, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL BRR() const { return HC_SHUFFLE3I(*this, 2, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BRG() const { return HC_SHUFFLE3I(*this, 2, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BRB() const { return HC_SHUFFLE3I(*this, 2, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BRA() const { return HC_SHUFFLE3I(*this, 2, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL BGR() const { return HC_SHUFFLE3I(*this, 2, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BGG() const { return HC_SHUFFLE3I(*this, 2, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BGB() const { return HC_SHUFFLE3I(*this, 2, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BGA() const { return HC_SHUFFLE3I(*this, 2, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL BBR() const { return HC_SHUFFLE3I(*this, 2, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BBG() const { return HC_SHUFFLE3I(*this, 2, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BBB() const { return HC_SHUFFLE3I(*this, 2, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BBA() const { return HC_SHUFFLE3I(*this, 2, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL BAR() const { return HC_SHUFFLE3I(*this, 2, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL BAG() const { return HC_SHUFFLE3I(*this, 2, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL BAB() const { return HC_SHUFFLE3I(*this, 2, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL BAA() const { return HC_SHUFFLE3I(*this, 2, 3, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ARR() const { return HC_SHUFFLE3I(*this, 3, 0, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ARG() const { return HC_SHUFFLE3I(*this, 3, 0, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ARB() const { return HC_SHUFFLE3I(*this, 3, 0, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ARA() const { return HC_SHUFFLE3I(*this, 3, 0, 3); }
	HC_INLINE Vec3I HC_VECTORCALL AGR() const { return HC_SHUFFLE3I(*this, 3, 1, 0); }
	HC_INLINE Vec3I HC_VECTORCALL AGG() const { return HC_SHUFFLE3I(*this, 3, 1, 1); }
	HC_INLINE Vec3I HC_VECTORCALL AGB() const { return HC_SHUFFLE3I(*this, 3, 1, 2); }
	HC_INLINE Vec3I HC_VECTORCALL AGA() const { return HC_SHUFFLE3I(*this, 3, 1, 3); }
	HC_INLINE Vec3I HC_VECTORCALL ABR() const { return HC_SHUFFLE3I(*this, 3, 2, 0); }
	HC_INLINE Vec3I HC_VECTORCALL ABG() const { return HC_SHUFFLE3I(*this, 3, 2, 1); }
	HC_INLINE Vec3I HC_VECTORCALL ABB() const { return HC_SHUFFLE3I(*this, 3, 2, 2); }
	HC_INLINE Vec3I HC_VECTORCALL ABA() const { return HC_SHUFFLE3I(*this, 3, 2, 3); }
	HC_INLINE Vec3I HC_VECTORCALL AAR() const { return HC_SHUFFLE3I(*this, 3, 3, 0); }
	HC_INLINE Vec3I HC_VECTORCALL AAG() const { return HC_SHUFFLE3I(*this, 3, 3, 1); }
	HC_INLINE Vec3I HC_VECTORCALL AAB() const { return HC_SHUFFLE3I(*this, 3, 3, 2); }
	HC_INLINE Vec3I HC_VECTORCALL AAA() const { return HC_SHUFFLE3I(*this, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XXXX() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XXXY() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XXXZ() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XXXW() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XXYX() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XXYY() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XXYZ() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XXYW() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XXZX() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XXZY() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XXZZ() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XXZW() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XXWX() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XXWY() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XXWZ() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XXWW() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XYXX() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XYXY() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XYXZ() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XYXW() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XYYX() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XYYY() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XYYZ() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XYYW() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XYZX() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XYZY() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XYZZ() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XYWX() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XYWY() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XYWZ() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XYWW() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XZXX() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XZXY() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XZXZ() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XZXW() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XZYX() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XZYY() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XZYZ() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XZYW() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XZZX() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XZZY() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XZZZ() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XZZW() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XZWX() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XZWY() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XZWZ() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XZWW() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XWXX() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XWXY() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XWXZ() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XWXW() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XWYX() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XWYY() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XWYZ() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XWYW() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XWZX() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XWZY() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XWZZ() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XWZW() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL XWWX() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL XWWY() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL XWWZ() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL XWWW() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YXXX() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YXXY() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YXXZ() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YXXW() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YXYX() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YXYY() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YXYZ() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YXYW() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YXZX() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YXZY() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YXZZ() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YXZW() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YXWX() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YXWY() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YXWZ() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YXWW() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YYXX() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YYXY() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YYXZ() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YYXW() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YYYX() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YYYY() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YYYZ() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YYYW() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YYZX() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YYZY() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YYZZ() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YYZW() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YYWX() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YYWY() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YYWZ() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YYWW() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YZXX() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YZXY() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YZXZ() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YZXW() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YZYX() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YZYY() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YZYZ() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YZYW() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YZZX() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YZZY() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YZZZ() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YZZW() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YZWX() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YZWY() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YZWZ() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YZWW() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YWXX() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YWXY() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YWXZ() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YWXW() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YWYX() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YWYY() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YWYZ() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YWYW() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YWZX() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YWZY() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YWZZ() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YWZW() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL YWWX() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL YWWY() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL YWWZ() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL YWWW() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZXXX() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZXXY() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZXXZ() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZXXW() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZXYX() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZXYY() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZXYZ() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZXYW() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZXZX() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZXZY() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZXZZ() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZXZW() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZXWX() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZXWY() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZXWZ() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZXWW() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZYXX() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZYXY() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZYXZ() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZYXW() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZYYX() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZYYY() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZYYZ() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZYYW() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZYZX() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZYZY() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZYZZ() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZYZW() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZYWX() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZYWY() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZYWZ() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZYWW() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZZXX() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZZXY() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZZXZ() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZZXW() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZZYX() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZZYY() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZZYZ() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZZYW() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZZZX() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZZZY() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZZZZ() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZZZW() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZZWX() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZZWY() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZZWZ() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZZWW() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZWXX() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZWXY() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZWXZ() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZWXW() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZWYX() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZWYY() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZWYZ() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZWYW() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZWZX() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZWZY() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZWZZ() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZWZW() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ZWWX() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ZWWY() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ZWWZ() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ZWWW() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WXXX() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WXXY() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WXXZ() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WXXW() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WXYX() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WXYY() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WXYZ() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WXYW() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WXZX() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WXZY() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WXZZ() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WXZW() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WXWX() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WXWY() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WXWZ() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WXWW() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WYXX() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WYXY() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WYXZ() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WYXW() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WYYX() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WYYY() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WYYZ() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WYYW() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WYZX() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WYZY() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WYZZ() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WYZW() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WYWX() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WYWY() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WYWZ() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WYWW() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WZXX() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WZXY() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WZXZ() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WZXW() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WZYX() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WZYY() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WZYZ() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WZYW() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WZZX() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WZZY() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WZZZ() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WZZW() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WZWX() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WZWY() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WZWZ() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WZWW() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WWXX() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WWXY() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WWXZ() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WWXW() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WWYX() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WWYY() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WWYZ() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WWYW() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WWZX() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WWZY() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WWZZ() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WWZW() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL WWWX() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL WWWY() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL WWWZ() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL WWWW() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RRRR() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RRRG() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RRRB() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RRRA() const { return HC_SHUFFLE4I(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RRGR() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RRGG() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RRGB() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RRGA() const { return HC_SHUFFLE4I(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RRBR() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RRBG() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RRBB() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RRBA() const { return HC_SHUFFLE4I(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RRAR() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RRAG() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RRAB() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RRAA() const { return HC_SHUFFLE4I(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RGRR() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RGRG() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RGRB() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RGRA() const { return HC_SHUFFLE4I(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RGGR() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RGGG() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RGGB() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RGGA() const { return HC_SHUFFLE4I(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RGBR() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RGBG() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RGBB() const { return HC_SHUFFLE4I(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RGAR() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RGAG() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RGAB() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RGAA() const { return HC_SHUFFLE4I(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RBRR() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RBRG() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RBRB() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RBRA() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RBGR() const { return HC_SHUFFLE4I(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RBGG() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RBGB() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RBGA() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RBBR() const { return HC_SHUFFLE4I(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RBBG() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RBBB() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RBBA() const { return HC_SHUFFLE4I(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RBAR() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RBAG() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RBAB() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RBAA() const { return HC_SHUFFLE4I(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RARR() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RARG() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RARB() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RARA() const { return HC_SHUFFLE4I(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RAGR() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RAGG() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RAGB() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RAGA() const { return HC_SHUFFLE4I(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RABR() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RABG() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RABB() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RABA() const { return HC_SHUFFLE4I(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL RAAR() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL RAAG() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL RAAB() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL RAAA() const { return HC_SHUFFLE4I(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GRRR() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GRRG() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GRRB() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GRRA() const { return HC_SHUFFLE4I(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GRGR() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GRGG() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GRGB() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GRGA() const { return HC_SHUFFLE4I(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GRBR() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GRBG() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GRBB() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GRBA() const { return HC_SHUFFLE4I(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GRAR() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GRAG() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GRAB() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GRAA() const { return HC_SHUFFLE4I(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GGRR() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GGRG() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GGRB() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GGRA() const { return HC_SHUFFLE4I(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GGGR() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GGGG() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GGGB() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GGGA() const { return HC_SHUFFLE4I(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GGBR() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GGBG() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GGBB() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GGBA() const { return HC_SHUFFLE4I(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GGAR() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GGAG() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GGAB() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GGAA() const { return HC_SHUFFLE4I(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GBRR() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GBRG() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GBRB() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GBRA() const { return HC_SHUFFLE4I(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GBGR() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GBGG() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GBGB() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GBGA() const { return HC_SHUFFLE4I(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GBBR() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GBBG() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GBBB() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GBBA() const { return HC_SHUFFLE4I(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GBAR() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GBAG() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GBAB() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GBAA() const { return HC_SHUFFLE4I(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GARR() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GARG() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GARB() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GARA() const { return HC_SHUFFLE4I(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GAGR() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GAGG() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GAGB() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GAGA() const { return HC_SHUFFLE4I(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GABR() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GABG() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GABB() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GABA() const { return HC_SHUFFLE4I(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL GAAR() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL GAAG() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL GAAB() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL GAAA() const { return HC_SHUFFLE4I(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BRRR() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BRRG() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BRRB() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BRRA() const { return HC_SHUFFLE4I(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BRGR() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BRGG() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BRGB() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BRGA() const { return HC_SHUFFLE4I(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BRBR() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BRBG() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BRBB() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BRBA() const { return HC_SHUFFLE4I(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BRAR() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BRAG() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BRAB() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BRAA() const { return HC_SHUFFLE4I(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BGRR() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BGRG() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BGRB() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BGRA() const { return HC_SHUFFLE4I(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BGGR() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BGGG() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BGGB() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BGGA() const { return HC_SHUFFLE4I(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BGBR() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BGBG() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BGBB() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BGBA() const { return HC_SHUFFLE4I(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BGAR() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BGAG() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BGAB() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BGAA() const { return HC_SHUFFLE4I(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BBRR() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BBRG() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BBRB() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BBRA() const { return HC_SHUFFLE4I(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BBGR() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BBGG() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BBGB() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BBGA() const { return HC_SHUFFLE4I(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BBBR() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BBBG() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BBBB() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BBBA() const { return HC_SHUFFLE4I(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BBAR() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BBAG() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BBAB() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BBAA() const { return HC_SHUFFLE4I(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BARR() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BARG() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BARB() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BARA() const { return HC_SHUFFLE4I(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BAGR() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BAGG() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BAGB() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BAGA() const { return HC_SHUFFLE4I(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BABR() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BABG() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BABB() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BABA() const { return HC_SHUFFLE4I(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL BAAR() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL BAAG() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL BAAB() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL BAAA() const { return HC_SHUFFLE4I(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ARRR() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ARRG() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ARRB() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ARRA() const { return HC_SHUFFLE4I(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ARGR() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ARGG() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ARGB() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ARGA() const { return HC_SHUFFLE4I(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ARBR() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ARBG() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ARBB() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ARBA() const { return HC_SHUFFLE4I(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ARAR() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ARAG() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ARAB() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ARAA() const { return HC_SHUFFLE4I(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AGRR() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AGRG() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AGRB() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AGRA() const { return HC_SHUFFLE4I(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AGGR() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AGGG() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AGGB() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AGGA() const { return HC_SHUFFLE4I(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AGBR() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AGBG() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AGBB() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AGBA() const { return HC_SHUFFLE4I(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AGAR() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AGAG() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AGAB() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AGAA() const { return HC_SHUFFLE4I(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ABRR() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ABRG() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ABRB() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ABRA() const { return HC_SHUFFLE4I(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ABGR() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ABGG() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ABGB() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ABGA() const { return HC_SHUFFLE4I(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ABBR() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ABBG() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ABBB() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ABBA() const { return HC_SHUFFLE4I(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL ABAR() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL ABAG() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL ABAB() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL ABAA() const { return HC_SHUFFLE4I(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AARR() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AARG() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AARB() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AARA() const { return HC_SHUFFLE4I(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AAGR() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AAGG() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AAGB() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AAGA() const { return HC_SHUFFLE4I(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AABR() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AABG() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AABB() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AABA() const { return HC_SHUFFLE4I(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4I HC_VECTORCALL AAAR() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4I HC_VECTORCALL AAAG() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4I HC_VECTORCALL AAAB() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4I HC_VECTORCALL AAAA() const { return HC_SHUFFLE4I(*this, 3, 3, 3, 3); }
};

#endif

HC_INLINE Vec2F HC_VECTORCALL operator+(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator-(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator*(Vec2F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator*(float _fLeft, Vec2F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec2F HC_VECTORCALL operator/(Vec2F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator/(float _fLeft, Vec2F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec2F HC_VECTORCALL operator*(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator/(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator+=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator-=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator*=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator/=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator*=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2F& HC_VECTORCALL operator/=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL operator~(Vec2F _vVector) { return Vec2F(); }
HC_INLINE Vec2F HC_VECTORCALL operator-(Vec2F _vVector) { return Vec2F() - (_vVector); }
HC_INLINE bool HC_VECTORCALL operator==(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator<(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator>(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 3) != 0; }
HC_INLINE Vec2F HC_VECTORCALL Min(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL Max(Vec2F _vLeft, Vec2F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec2F HC_VECTORCALL Clamp(Vec2F _vVector, Vec2F _vMin, Vec2F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float HC_VECTORCALL Sum(const Vec2F _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE float HC_VECTORCALL Dot(Vec2F _vLeft, Vec2F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec2F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float HC_VECTORCALL LengthSquared(Vec2F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2F HC_VECTORCALL Normalize(Vec2F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec2F _vLeft, Vec2F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE float HC_VECTORCALL Cross(Vec2F _vLeft, Vec2F _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2F HC_VECTORCALL Abs(Vec2F _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec); return _vVector; }

HC_INLINE Vec3F HC_VECTORCALL operator+(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator-(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator*(Vec3F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator*(float _fLeft, Vec3F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec3F HC_VECTORCALL operator/(Vec3F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator/(float _fLeft, Vec3F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec3F HC_VECTORCALL operator*(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator/(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator+=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator-=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator*=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator/=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator*=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3F& HC_VECTORCALL operator/=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL operator~(Vec3F _vVector) { return Vec3F(); }
HC_INLINE Vec3F HC_VECTORCALL operator-(Vec3F _vVector) { return Vec3F() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator<(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator>(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 7) != 0; }
HC_INLINE Vec3F HC_VECTORCALL Min(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL Max(Vec3F _vLeft, Vec3F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec3F HC_VECTORCALL Clamp(Vec3F _vVector, Vec3F _vMin, Vec3F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float HC_VECTORCALL HorizontalMin(Vec3F _vVector) { _vVector = Min(_vVector, HC_SHUFFLE3F(_vVector, 1, 0, 2)); return Min(_vVector, HC_SHUFFLE3F(_vVector, 2, 0, 1)).X(); }
HC_INLINE float HC_VECTORCALL HorizontalMax(Vec3F _vVector) { _vVector = Max(_vVector, HC_SHUFFLE3F(_vVector, 1, 0, 2)); return Max(_vVector, HC_SHUFFLE3F(_vVector, 2, 0, 1)).X(); }
HC_INLINE float HC_VECTORCALL Sum(const Vec3F _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE float HC_VECTORCALL Dot(Vec3F _vLeft, Vec3F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec3F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float HC_VECTORCALL LengthSquared(Vec3F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3F HC_VECTORCALL Normalize(Vec3F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec3F _vLeft, Vec3F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE Vec3F HC_VECTORCALL Cross(Vec3F _vLeft, Vec3F _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3F HC_VECTORCALL Abs(Vec3F _vVector) { _vVector.m_fVec = _mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec); return _vVector; }

HC_INLINE Vec4F HC_VECTORCALL operator+(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_add_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator-(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_sub_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator*(Vec4F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator*(float _fLeft, Vec4F _vRight) { _vRight.m_fVec = _mm_mul_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec4F HC_VECTORCALL operator/(Vec4F _vLeft, float _fRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _mm_set1_ps(_fRight)); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator/(float _fLeft, Vec4F _vRight) { _vRight.m_fVec = _mm_div_ps(_mm_set1_ps(_fLeft), _vRight.m_fVec); return _vRight; }
HC_INLINE Vec4F HC_VECTORCALL operator*(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_mul_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator/(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_div_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator+=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator-=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator*=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator/=(Vec4F& _vLeft, Vec4F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator*=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator/=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL operator~(Vec4F _vVector) { return Vec4F(); }
HC_INLINE Vec4F HC_VECTORCALL operator-(Vec4F _vVector) { return Vec4F() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpeq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator<(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmplt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpgt_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmple_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpge_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_cmpneq_ps(_vLeft.m_fVec, _vRight.m_fVec); return (_mm_movemask_ps(_vLeft.m_fVec) & 15) == 15; }
HC_INLINE Vec4F HC_VECTORCALL Min(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_min_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL Max(Vec4F _vLeft, Vec4F _vRight) { _vLeft.m_fVec = _mm_max_ps(_vLeft.m_fVec, _vRight.m_fVec); return _vLeft; }
HC_INLINE Vec4F HC_VECTORCALL Clamp(Vec4F _vVector, Vec4F _vMin, Vec4F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE float HC_VECTORCALL Sum(const Vec4F _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_INLINE float HC_VECTORCALL Dot(Vec4F _vLeft, Vec4F _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec4F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
HC_INLINE float HC_VECTORCALL LengthSquared(Vec4F _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4F HC_VECTORCALL Normalize(Vec4F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec4F _vLeft, Vec4F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
HC_INLINE Vec4F HC_VECTORCALL Cross(Vec4F _vLeft, Vec4F _vRight) { _vRight.m_fVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_fVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4F HC_VECTORCALL Abs(Vec4F _vVector) { return Vec4F(_mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec)); }

#if HC_ENABLE_EXTRA_VECTOR_TYPES && HC_USE_SIMD

HC_INLINE Vec2D HC_VECTORCALL operator+(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator-(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator*(Vec2D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator*(double _fLeft, Vec2D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec2D HC_VECTORCALL operator/(Vec2D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator/(double _fLeft, Vec2D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec2D HC_VECTORCALL operator*(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator/(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator+=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator-=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator*=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator/=(Vec2D& _vLeft, Vec2D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator*=(Vec2D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2D& HC_VECTORCALL operator/=(Vec2D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL operator~(Vec2D _vVector) { return Vec2D(); }
HC_INLINE Vec2D HC_VECTORCALL operator-(Vec2D _vVector) { return Vec2D() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator<(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator>(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) == 3; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 3) != 0; }
HC_INLINE Vec2D HC_VECTORCALL Min(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL Max(Vec2D _vLeft, Vec2D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec2D HC_VECTORCALL Clamp(Vec2D _vVector, Vec2D _vMin, Vec2D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double HC_VECTORCALL Sum(const Vec2D _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE double HC_VECTORCALL Dot(Vec2D _vLeft, Vec2D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double HC_VECTORCALL Length(Vec2D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double HC_VECTORCALL LengthSquared(Vec2D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2D HC_VECTORCALL Normalize(Vec2D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double HC_VECTORCALL AngleBetween(Vec2D _vLeft, Vec2D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE double HC_VECTORCALL Cross(Vec2D _vLeft, Vec2D _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2D HC_VECTORCALL Abs(Vec2D _vVector) { _vVector.m_dVec = _mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec); return _vVector; }

HC_INLINE Vec3D HC_VECTORCALL operator+(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator-(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator*(Vec3D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator*(double _fLeft, Vec3D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec3D HC_VECTORCALL operator/(Vec3D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator/(double _fLeft, Vec3D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec3D HC_VECTORCALL operator*(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator/(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator+=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator-=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator*=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator/=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator*=(Vec3D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3D& HC_VECTORCALL operator/=(Vec3D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL operator~(Vec3D _vVector) { return Vec3D(); }
HC_INLINE Vec3D HC_VECTORCALL operator-(Vec3D _vVector) { return Vec3D() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator<(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator>(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) == 7; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 7) != 0; }
HC_INLINE Vec3D HC_VECTORCALL Min(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL Max(Vec3D _vLeft, Vec3D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec3D HC_VECTORCALL Clamp(Vec3D _vVector, Vec3D _vMin, Vec3D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double HC_VECTORCALL HorizontalMin(Vec3D _vVector) { _vVector = Min(_vVector, HC_SHUFFLE3D(_vVector, 1, 0, 2)); return Min(_vVector, HC_SHUFFLE3D(_vVector, 2, 0, 1)).X(); }
HC_INLINE double HC_VECTORCALL HorizontalMax(Vec3D _vVector) { _vVector = Max(_vVector, HC_SHUFFLE3D(_vVector, 1, 0, 2)); return Max(_vVector, HC_SHUFFLE3D(_vVector, 2, 0, 1)).X(); }
HC_INLINE double HC_VECTORCALL Sum(const Vec3D _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE double HC_VECTORCALL Dot(Vec3D _vLeft, Vec3D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double HC_VECTORCALL Length(Vec3D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double HC_VECTORCALL LengthSquared(Vec3D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3D HC_VECTORCALL Normalize(Vec3D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double HC_VECTORCALL AngleBetween(Vec3D _vLeft, Vec3D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE Vec3D HC_VECTORCALL Cross(Vec3D _vLeft, Vec3D _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3D HC_VECTORCALL Abs(Vec3D _vVector) { _vVector.m_dVec = _mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec); return _vVector; }

HC_INLINE Vec4D HC_VECTORCALL operator+(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator-(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator*(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator*(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL operator/(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator/(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL operator*(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator/(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator+=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator-=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator*=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator/=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator*=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator/=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator~(Vec4D _vVector) { return Vec4D(); }
HC_INLINE Vec4D HC_VECTORCALL operator-(Vec4D _vVector) { return Vec4D() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15;}
HC_INLINE bool HC_VECTORCALL operator<(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) != 0; }
HC_INLINE Vec4D HC_VECTORCALL Min(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL Max(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL Clamp(Vec4D _vVector, Vec4D _vMin, Vec4D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double HC_VECTORCALL Sum(const Vec4D _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_INLINE double HC_VECTORCALL Dot(Vec4D _vLeft, Vec4D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double HC_VECTORCALL Length(Vec4D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double HC_VECTORCALL LengthSquared(Vec4D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4D HC_VECTORCALL Normalize(Vec4D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double HC_VECTORCALL AngleBetween(Vec4D _vLeft, Vec4D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE Vec4D HC_VECTORCALL Cross(Vec4D _vLeft, Vec4D _vRight) { _vRight.m_dVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_dVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL Abs(Vec4D _vVector) { return Vec4D(_mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec)); }

HC_INLINE Vec2I HC_VECTORCALL operator+(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator-(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator*(Vec2I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator*(int _fLeft, Vec2I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec2I HC_VECTORCALL operator/(Vec2I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator/(int _fLeft, Vec2I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec2I HC_VECTORCALL operator*(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator/(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator+=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator-=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator*=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator/=(Vec2I& _vLeft, Vec2I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator*=(Vec2I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2I& HC_VECTORCALL operator/=(Vec2I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL operator~(Vec2I _vVector) { return Vec2I(); }
HC_INLINE Vec2I HC_VECTORCALL operator-(Vec2I _vVector) { return Vec2I() - (_vVector); }
HC_INLINE bool HC_VECTORCALL operator==(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator>(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec2I _vLeft, Vec2I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator>=(Vec2I _vLeft, Vec2I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator!=(Vec2I _vLeft, Vec2I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec2I HC_VECTORCALL Min(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL Max(Vec2I _vLeft, Vec2I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec2I HC_VECTORCALL Clamp(Vec2I _vVector, Vec2I _vMin, Vec2I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int HC_VECTORCALL Sum(const Vec2I _vVector) { return _vVector.X() + _vVector.Y(); }
HC_INLINE int HC_VECTORCALL Dot(Vec2I _vLeft, Vec2I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec2I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int HC_VECTORCALL LengthSquared(Vec2I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec2I HC_VECTORCALL Normalize(Vec2I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec2I _vLeft, Vec2I _vRight) { return acosf(static_cast<float>(Dot(_vLeft, _vRight))); }
HC_INLINE int HC_VECTORCALL Cross(Vec2I _vLeft, Vec2I _vRight) { return _vLeft.X() * _vRight.Y() - _vLeft.Y() * _vRight.X(); }
HC_INLINE Vec2I HC_VECTORCALL Abs(Vec2I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }

HC_INLINE Vec3I HC_VECTORCALL operator+(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator-(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator*(Vec3I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator*(int _fLeft, Vec3I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec3I HC_VECTORCALL operator/(Vec3I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator/(int _fLeft, Vec3I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec3I HC_VECTORCALL operator*(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator/(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator+=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator-=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator*=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator/=(Vec3I& _vLeft, Vec3I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator*=(Vec3I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3I& HC_VECTORCALL operator/=(Vec3I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL operator~(Vec3I _vVector) { return Vec3I(); }
HC_INLINE Vec3I HC_VECTORCALL operator-(Vec3I _vVector) { return Vec3I() - (_vVector); }
HC_INLINE bool HC_VECTORCALL operator==(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator>(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator>=(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator!=(Vec3I _vLeft, Vec3I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec3I HC_VECTORCALL Min(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL Max(Vec3I _vLeft, Vec3I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec3I HC_VECTORCALL Clamp(Vec3I _vVector, Vec3I _vMin, Vec3I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int HC_VECTORCALL Sum(const Vec3I _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE int HC_VECTORCALL Dot(Vec3I _vLeft, Vec3I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec3I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int HC_VECTORCALL LengthSquared(Vec3I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec3I HC_VECTORCALL Normalize(Vec3I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec3I _vLeft, Vec3I _vRight) { return acosf(static_cast<float>(Dot(_vLeft, _vRight))); }
HC_INLINE Vec3I HC_VECTORCALL Cross(Vec3I _vLeft, Vec3I _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
HC_INLINE Vec3I HC_VECTORCALL Abs(Vec3I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }

HC_INLINE Vec4I HC_VECTORCALL operator+(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_add_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator-(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_sub_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator*(Vec4I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator*(int _fLeft, Vec4I _vRight) { _vRight.m_iVec = _mm_mul_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec4I HC_VECTORCALL operator/(Vec4I _vLeft, int _fRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _mm_set1_epi32(_fRight)); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator/(int _fLeft, Vec4I _vRight) { _vRight.m_iVec = _mm_div_epi32(_mm_set1_epi32(_fLeft), _vRight.m_iVec); return _vRight; }
HC_INLINE Vec4I HC_VECTORCALL operator*(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_mul_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator/(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_div_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator+=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator-=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator*=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator/=(Vec4I& _vLeft, Vec4I _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator*=(Vec4I& _vLeft, int _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4I& HC_VECTORCALL operator/=(Vec4I& _vLeft, int _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL operator~(Vec4I _vVector) { return Vec4I(); }
HC_INLINE Vec4I HC_VECTORCALL operator-(Vec4I _vVector) { return Vec4I() - (_vVector); }
HC_INLINE bool HC_VECTORCALL operator==(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmpeq_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmplt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator>(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_cmpgt_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _mm_test_all_ones(_vLeft.m_iVec) == 1; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec4I _vLeft, Vec4I _vRight) { return (_vLeft < _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator>=(Vec4I _vLeft, Vec4I _vRight) { return (_vLeft > _vRight) || (_vLeft == _vRight); }
HC_INLINE bool HC_VECTORCALL operator!=(Vec4I _vLeft, Vec4I _vRight) { return !(_vLeft == _vRight); }
HC_INLINE Vec4I HC_VECTORCALL Min(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_min_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL Max(Vec4I _vLeft, Vec4I _vRight) { _vLeft.m_iVec = _mm_max_epi32(_vLeft.m_iVec, _vRight.m_iVec); return _vLeft; }
HC_INLINE Vec4I HC_VECTORCALL Clamp(Vec4I _vVector, Vec4I _vMin, Vec4I _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE int HC_VECTORCALL Sum(const Vec4I _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z(); }
HC_INLINE int HC_VECTORCALL Dot(Vec4I _vLeft, Vec4I _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE float HC_VECTORCALL Length(Vec4I _vVector) { return sqrtf(static_cast<float>(Dot(_vVector, _vVector))); }
HC_INLINE int HC_VECTORCALL LengthSquared(Vec4I _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4I HC_VECTORCALL Normalize(Vec4I _vVector) { return _vVector * static_cast<int>((1.0f / Length(_vVector))); }
HC_INLINE float HC_VECTORCALL AngleBetween(Vec4I _vLeft, Vec4I _vRight) { return acosf(static_cast<float>(Dot(_vLeft, _vRight))); }
HC_INLINE Vec4I HC_VECTORCALL Cross(Vec4I _vLeft, Vec4I _vRight) { _vRight.m_iVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_iVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4I HC_VECTORCALL Abs(Vec4I _vVector) { _vVector.m_iVec = _mm_abs_epi32(_vVector.m_iVec); return _vVector; }

#endif

#else

struct Vec2F
{
	union
	{
		float data[2];
		struct
		{
			float x;
			float y;
		};
	};
};

struct Vec3F
{
	union
	{
		float data[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};
};

struct Vec4F
{
	union
	{
		float data[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#if HC_ENABLE_EXTRA_VECTOR_TYPES

struct Vec2D
{
	union
	{
		double data[2];
		struct
		{
			double x;
			double y;
		};
	};
};

struct Vec3D
{
	union
	{
		double data[3];
		struct
		{
			double x;
			double y;
			double z;
		};
	};
};

struct Vec4D
{
	union
	{
		double data[4];
		struct
		{
			double x;
			double y;
			double z;
			double w;
		};
	};
};

struct Vec2I
{
	union
	{
		int data[2];
		struct
		{
			int x;
			int y;
		};
	};
};

struct Vec3I
{
	union
	{
		int data[3];
		struct
		{
			int x;
			int y;
			int z;
		};
	};
};

struct Vec4I
{
	union
	{
		int data[4];
		struct
		{
			int x;
			int y;
			int z;
			int w;
		};
	};
};

#endif

#endif