#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
/*#define HC_SHUFFLE4F(_vec, _x, _y, _z, _w) Vec4F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))
#define HC_SHUFFLE4F_2(_vec1, _vec2, _x, _y, _z, _w) Vec4F(_mm_shuffle_ps((_vec1).m_fVec, (_vec2).m_fVec, _MM_SHUFFLE(_w, _z, _y, _x)))

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
HC_INLINE Vec4F HC_VECTORCALL Abs(Vec4F _vVector) { return Vec4F(_mm_andnot_ps(_vVector.m_fVec, SignBitMaskF().m_fVec)); }*/

#else

struct HC_ALIGNAS(16) Vec4F
{
	union
	{
		float m_fData[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

	HC_INLINE Vec4F() { m_fData[0] = 0.0f; m_fData[1] = 0.0f; m_fData[2] = 0.0f; m_fData[3] = 0.0f; }
	HC_INLINE explicit Vec4F(float _fVal) { m_fData[0] = _fVal; m_fData[1] = _fVal; m_fData[2] = _fVal; m_fData[3] = _fVal; }
	HC_INLINE explicit Vec4F(int _iVal) { m_fData[0] = static_cast<float>(_iVal); m_fData[1] = static_cast<float>(_iVal); m_fData[2] = static_cast<float>(_iVal); m_fData[3] = static_cast<float>(_iVal); }
	HC_INLINE explicit Vec4F(double _dVal) { m_fData[0] = static_cast<float>(_dVal); m_fData[1] = static_cast<float>(_dVal); m_fData[2] = static_cast<float>(_dVal); m_fData[3] = static_cast<float>(_dVal); }
	HC_INLINE explicit Vec4F(float _fX, float _fY, float _fZ, float _fW) { m_fData[0] = _fX; m_fData[1] = _fY; m_fData[2] = _fZ; m_fData[3] = _fW; }
	HC_INLINE explicit Vec4F(int _iX, int _iY, int _iZ, int _iW) { m_fData[0] = static_cast<float>(_iX); m_fData[1] = static_cast<float>(_iY); m_fData[2] = static_cast<float>(_iZ); m_fData[3] = static_cast<float>(_iW); }
	HC_INLINE explicit Vec4F(double _dX, double _dY, double _dZ, double _dW) { m_fData[0] = static_cast<float>(_dX); m_fData[1] = static_cast<float>(_dY); m_fData[2] = static_cast<float>(_dZ); m_fData[3] = static_cast<float>(_dW); }
	HC_INLINE explicit Vec4F(const Vec2F& _vXY, float _fZ, float _fW) { m_fData[0] = _vXY.x; m_fData[1] = _vXY.y; m_fData[2] = _fZ; m_fData[3] = _fW; }
	HC_INLINE explicit Vec4F(float _fX, const Vec2F& _vYZ, float _fW) { m_fData[0] = _fX; m_fData[1] = _vYZ.x; m_fData[2] = _vYZ.y; m_fData[3] = _fW; }
	HC_INLINE explicit Vec4F(float _fX, float _fY, const Vec2F& _vZW) { m_fData[0] = _fX; m_fData[1] = _fY; m_fData[2] = _vZW.x; m_fData[3] = _vZW.y; }
	HC_INLINE explicit Vec4F(const Vec2F& _vXY, const Vec2F& _vZW) { m_fData[0] = _vXY.x; m_fData[1] = _vXY.y; m_fData[2] = _vZW.x; m_fData[3] = _vZW.y; }
	HC_INLINE explicit Vec4F(const Vec3F& _vXYZ, float _fW) { m_fData[0] = _vXYZ.x; m_fData[1] = _vXYZ.y; m_fData[2] = _vXYZ.z; m_fData[3] = _fW; }
	HC_INLINE explicit Vec4F(float _fX, const Vec3F& _vYZW) { m_fData[0] = _fX; m_fData[1] = _vYZW.x; m_fData[2] = _vYZW.y; m_fData[3] = _vYZW.z; }

	[[nodiscard]] HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 4); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 4); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2F XX() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F YY() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F ZZ() const { return Vec2F(z, z); }
	[[nodiscard]] HC_INLINE Vec2F WW() const { return Vec2F(w, w); }
	[[nodiscard]] HC_INLINE Vec2F XY() const { return Vec2F(x, y); }
	[[nodiscard]] HC_INLINE Vec2F XZ() const { return Vec2F(x, z); }
	[[nodiscard]] HC_INLINE Vec2F XW() const { return Vec2F(x, w); }
	[[nodiscard]] HC_INLINE Vec2F YX() const { return Vec2F(y, x); }
	[[nodiscard]] HC_INLINE Vec2F YZ() const { return Vec2F(y, z); }
	[[nodiscard]] HC_INLINE Vec2F YW() const { return Vec2F(y, w); }
	[[nodiscard]] HC_INLINE Vec2F ZX() const { return Vec2F(z, x); }
	[[nodiscard]] HC_INLINE Vec2F ZY() const { return Vec2F(z, y); }
	[[nodiscard]] HC_INLINE Vec2F ZW() const { return Vec2F(z, w); }
	[[nodiscard]] HC_INLINE Vec2F WX() const { return Vec2F(w, x); }
	[[nodiscard]] HC_INLINE Vec2F WY() const { return Vec2F(w, y); }
	[[nodiscard]] HC_INLINE Vec2F WZ() const { return Vec2F(w, z); }
	[[nodiscard]] HC_INLINE Vec2F RR() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F GG() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F BB() const { return Vec2F(z, z); }
	[[nodiscard]] HC_INLINE Vec2F AA() const { return Vec2F(w, w); }
	[[nodiscard]] HC_INLINE Vec2F RG() const { return Vec2F(x, y); }
	[[nodiscard]] HC_INLINE Vec2F RB() const { return Vec2F(x, z); }
	[[nodiscard]] HC_INLINE Vec2F RA() const { return Vec2F(x, w); }
	[[nodiscard]] HC_INLINE Vec2F GR() const { return Vec2F(y, x); }
	[[nodiscard]] HC_INLINE Vec2F GB() const { return Vec2F(y, z); }
	[[nodiscard]] HC_INLINE Vec2F GA() const { return Vec2F(y, w); }
	[[nodiscard]] HC_INLINE Vec2F BR() const { return Vec2F(z, x); }
	[[nodiscard]] HC_INLINE Vec2F BG() const { return Vec2F(z, y); }
	[[nodiscard]] HC_INLINE Vec2F BA() const { return Vec2F(z, w); }
	[[nodiscard]] HC_INLINE Vec2F AR() const { return Vec2F(w, x); }
	[[nodiscard]] HC_INLINE Vec2F AG() const { return Vec2F(w, y); }
	[[nodiscard]] HC_INLINE Vec2F AB() const { return Vec2F(w, z); }
	[[nodiscard]] HC_INLINE Vec3F XXX() const { return Vec3F(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3F XXY() const { return Vec3F(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3F XXZ() const { return Vec3F(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3F XXW() const { return Vec3F(x, x, w); }
	[[nodiscard]] HC_INLINE Vec3F XYX() const { return Vec3F(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3F XYY() const { return Vec3F(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3F XYZ() const { return Vec3F(x, y, z); }
	[[nodiscard]] HC_INLINE Vec3F XYW() const { return Vec3F(x, y, w); }
	[[nodiscard]] HC_INLINE Vec3F XZX() const { return Vec3F(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3F XZY() const { return Vec3F(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3F XZZ() const { return Vec3F(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3F XZW() const { return Vec3F(x, z, w); }
	[[nodiscard]] HC_INLINE Vec3F XWX() const { return Vec3F(x, w, x); }
	[[nodiscard]] HC_INLINE Vec3F XWY() const { return Vec3F(x, w, y); }
	[[nodiscard]] HC_INLINE Vec3F XWZ() const { return Vec3F(x, w, z); }
	[[nodiscard]] HC_INLINE Vec3F XWW() const { return Vec3F(x, w, w); }
	[[nodiscard]] HC_INLINE Vec3F YXX() const { return Vec3F(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3F YXY() const { return Vec3F(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3F YXZ() const { return Vec3F(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3F YXW() const { return Vec3F(y, x, w); }
	[[nodiscard]] HC_INLINE Vec3F YYX() const { return Vec3F(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3F YYY() const { return Vec3F(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3F YYZ() const { return Vec3F(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3F YYW() const { return Vec3F(y, y, w); }
	[[nodiscard]] HC_INLINE Vec3F YZX() const { return Vec3F(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3F YZY() const { return Vec3F(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3F YZZ() const { return Vec3F(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3F YZW() const { return Vec3F(y, z, w); }
	[[nodiscard]] HC_INLINE Vec3F YWX() const { return Vec3F(y, w, x); }
	[[nodiscard]] HC_INLINE Vec3F YWY() const { return Vec3F(y, w, y); }
	[[nodiscard]] HC_INLINE Vec3F YWZ() const { return Vec3F(y, w, z); }
	[[nodiscard]] HC_INLINE Vec3F YWW() const { return Vec3F(y, w, w); }
	[[nodiscard]] HC_INLINE Vec3F ZXX() const { return Vec3F(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3F ZXY() const { return Vec3F(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3F ZXZ() const { return Vec3F(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3F ZXW() const { return Vec3F(z, x, w); }
	[[nodiscard]] HC_INLINE Vec3F ZYX() const { return Vec3F(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3F ZYY() const { return Vec3F(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3F ZYZ() const { return Vec3F(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3F ZYW() const { return Vec3F(z, y, w); }
	[[nodiscard]] HC_INLINE Vec3F ZZX() const { return Vec3F(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3F ZZY() const { return Vec3F(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3F ZZZ() const { return Vec3F(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3F ZZW() const { return Vec3F(z, z, w); }
	[[nodiscard]] HC_INLINE Vec3F ZWX() const { return Vec3F(z, w, x); }
	[[nodiscard]] HC_INLINE Vec3F ZWY() const { return Vec3F(z, w, y); }
	[[nodiscard]] HC_INLINE Vec3F ZWZ() const { return Vec3F(z, w, z); }
	[[nodiscard]] HC_INLINE Vec3F ZWW() const { return Vec3F(z, w, w); }
	[[nodiscard]] HC_INLINE Vec3F WXX() const { return Vec3F(w, x, x); }
	[[nodiscard]] HC_INLINE Vec3F WXY() const { return Vec3F(w, x, y); }
	[[nodiscard]] HC_INLINE Vec3F WXZ() const { return Vec3F(w, x, z); }
	[[nodiscard]] HC_INLINE Vec3F WXW() const { return Vec3F(w, x, w); }
	[[nodiscard]] HC_INLINE Vec3F WYX() const { return Vec3F(w, y, x); }
	[[nodiscard]] HC_INLINE Vec3F WYY() const { return Vec3F(w, y, y); }
	[[nodiscard]] HC_INLINE Vec3F WYZ() const { return Vec3F(w, y, z); }
	[[nodiscard]] HC_INLINE Vec3F WYW() const { return Vec3F(w, y, w); }
	[[nodiscard]] HC_INLINE Vec3F WZX() const { return Vec3F(w, z, x); }
	[[nodiscard]] HC_INLINE Vec3F WZY() const { return Vec3F(w, z, y); }
	[[nodiscard]] HC_INLINE Vec3F WZZ() const { return Vec3F(w, z, z); }
	[[nodiscard]] HC_INLINE Vec3F WZW() const { return Vec3F(w, z, w); }
	[[nodiscard]] HC_INLINE Vec3F WWX() const { return Vec3F(w, w, x); }
	[[nodiscard]] HC_INLINE Vec3F WWY() const { return Vec3F(w, w, y); }
	[[nodiscard]] HC_INLINE Vec3F WWZ() const { return Vec3F(w, w, z); }
	[[nodiscard]] HC_INLINE Vec3F WWW() const { return Vec3F(w, w, w); }
	[[nodiscard]] HC_INLINE Vec3F RRR() const { return Vec3F(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3F RRG() const { return Vec3F(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3F RRB() const { return Vec3F(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3F RRA() const { return Vec3F(x, x, w); }
	[[nodiscard]] HC_INLINE Vec3F RGR() const { return Vec3F(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3F RGG() const { return Vec3F(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3F RGA() const { return Vec3F(x, y, z); }
	[[nodiscard]] HC_INLINE Vec3F RGB() const { return Vec3F(x, y, w); }
	[[nodiscard]] HC_INLINE Vec3F RBR() const { return Vec3F(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3F RBG() const { return Vec3F(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3F RBB() const { return Vec3F(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3F RBA() const { return Vec3F(x, z, w); }
	[[nodiscard]] HC_INLINE Vec3F RAR() const { return Vec3F(x, w, x); }
	[[nodiscard]] HC_INLINE Vec3F RAG() const { return Vec3F(x, w, y); }
	[[nodiscard]] HC_INLINE Vec3F RAB() const { return Vec3F(x, w, z); }
	[[nodiscard]] HC_INLINE Vec3F RAA() const { return Vec3F(x, w, w); }
	[[nodiscard]] HC_INLINE Vec3F GRR() const { return Vec3F(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3F GRG() const { return Vec3F(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3F GRB() const { return Vec3F(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3F GRA() const { return Vec3F(y, x, w); }
	[[nodiscard]] HC_INLINE Vec3F GGR() const { return Vec3F(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3F GGG() const { return Vec3F(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3F GGB() const { return Vec3F(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3F GGA() const { return Vec3F(y, y, w); }
	[[nodiscard]] HC_INLINE Vec3F GBR() const { return Vec3F(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3F GBG() const { return Vec3F(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3F GBB() const { return Vec3F(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3F GBA() const { return Vec3F(y, z, w); }
	[[nodiscard]] HC_INLINE Vec3F GAR() const { return Vec3F(y, w, x); }
	[[nodiscard]] HC_INLINE Vec3F GAG() const { return Vec3F(y, w, y); }
	[[nodiscard]] HC_INLINE Vec3F GAB() const { return Vec3F(y, w, z); }
	[[nodiscard]] HC_INLINE Vec3F GAA() const { return Vec3F(y, w, w); }
	[[nodiscard]] HC_INLINE Vec3F BRR() const { return Vec3F(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3F BRG() const { return Vec3F(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3F BRB() const { return Vec3F(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3F BRA() const { return Vec3F(z, x, w); }
	[[nodiscard]] HC_INLINE Vec3F BGR() const { return Vec3F(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3F BGG() const { return Vec3F(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3F BGB() const { return Vec3F(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3F BGA() const { return Vec3F(z, y, w); }
	[[nodiscard]] HC_INLINE Vec3F BBR() const { return Vec3F(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3F BBG() const { return Vec3F(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3F BBB() const { return Vec3F(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3F BBA() const { return Vec3F(z, z, w); }
	[[nodiscard]] HC_INLINE Vec3F BAR() const { return Vec3F(z, w, x); }
	[[nodiscard]] HC_INLINE Vec3F BAG() const { return Vec3F(z, w, y); }
	[[nodiscard]] HC_INLINE Vec3F BAB() const { return Vec3F(z, w, z); }
	[[nodiscard]] HC_INLINE Vec3F BAA() const { return Vec3F(z, w, w); }
	[[nodiscard]] HC_INLINE Vec3F ARR() const { return Vec3F(w, x, x); }
	[[nodiscard]] HC_INLINE Vec3F ARG() const { return Vec3F(w, x, y); }
	[[nodiscard]] HC_INLINE Vec3F ARB() const { return Vec3F(w, x, z); }
	[[nodiscard]] HC_INLINE Vec3F ARA() const { return Vec3F(w, x, w); }
	[[nodiscard]] HC_INLINE Vec3F AGR() const { return Vec3F(w, y, x); }
	[[nodiscard]] HC_INLINE Vec3F AGG() const { return Vec3F(w, y, y); }
	[[nodiscard]] HC_INLINE Vec3F AGB() const { return Vec3F(w, y, z); }
	[[nodiscard]] HC_INLINE Vec3F AGA() const { return Vec3F(w, y, w); }
	[[nodiscard]] HC_INLINE Vec3F ABR() const { return Vec3F(w, z, x); }
	[[nodiscard]] HC_INLINE Vec3F ABG() const { return Vec3F(w, z, y); }
	[[nodiscard]] HC_INLINE Vec3F ABB() const { return Vec3F(w, z, z); }
	[[nodiscard]] HC_INLINE Vec3F ABA() const { return Vec3F(w, z, w); }
	[[nodiscard]] HC_INLINE Vec3F AAR() const { return Vec3F(w, w, x); }
	[[nodiscard]] HC_INLINE Vec3F AAG() const { return Vec3F(w, w, y); }
	[[nodiscard]] HC_INLINE Vec3F AAB() const { return Vec3F(w, w, z); }
	[[nodiscard]] HC_INLINE Vec3F AAA() const { return Vec3F(w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F XXXX() const { return Vec4F(x, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F XXXY() const { return Vec4F(x, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F XXXZ() const { return Vec4F(x, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F XXXW() const { return Vec4F(x, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F XXYX() const { return Vec4F(x, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F XXYY() const { return Vec4F(x, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F XXYZ() const { return Vec4F(x, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F XXYW() const { return Vec4F(x, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F XXZX() const { return Vec4F(x, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F XXZY() const { return Vec4F(x, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F XXZZ() const { return Vec4F(x, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F XXZW() const { return Vec4F(x, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F XXWX() const { return Vec4F(x, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F XXWY() const { return Vec4F(x, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F XXWZ() const { return Vec4F(x, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F XXWW() const { return Vec4F(x, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F XYXX() const { return Vec4F(x, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F XYXY() const { return Vec4F(x, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F XYXZ() const { return Vec4F(x, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F XYXW() const { return Vec4F(x, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F XYYX() const { return Vec4F(x, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F XYYY() const { return Vec4F(x, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F XYYZ() const { return Vec4F(x, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F XYYW() const { return Vec4F(x, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F XYZX() const { return Vec4F(x, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F XYZY() const { return Vec4F(x, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F XYZZ() const { return Vec4F(x, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F XYWX() const { return Vec4F(x, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F XYWY() const { return Vec4F(x, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F XYWZ() const { return Vec4F(x, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F XYWW() const { return Vec4F(x, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F XZXX() const { return Vec4F(x, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F XZXY() const { return Vec4F(x, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F XZXZ() const { return Vec4F(x, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F XZXW() const { return Vec4F(x, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F XZYX() const { return Vec4F(x, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F XZYY() const { return Vec4F(x, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F XZYZ() const { return Vec4F(x, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F XZYW() const { return Vec4F(x, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F XZZX() const { return Vec4F(x, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F XZZY() const { return Vec4F(x, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F XZZZ() const { return Vec4F(x, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F XZZW() const { return Vec4F(x, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F XZWX() const { return Vec4F(x, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F XZWY() const { return Vec4F(x, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F XZWZ() const { return Vec4F(x, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F XZWW() const { return Vec4F(x, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F XWXX() const { return Vec4F(x, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F XWXY() const { return Vec4F(x, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F XWXZ() const { return Vec4F(x, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F XWXW() const { return Vec4F(x, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F XWYX() const { return Vec4F(x, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F XWYY() const { return Vec4F(x, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F XWYZ() const { return Vec4F(x, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F XWYW() const { return Vec4F(x, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F XWZX() const { return Vec4F(x, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F XWZY() const { return Vec4F(x, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F XWZZ() const { return Vec4F(x, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F XWZW() const { return Vec4F(x, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F XWWX() const { return Vec4F(x, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F XWWY() const { return Vec4F(x, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F XWWZ() const { return Vec4F(x, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F XWWW() const { return Vec4F(x, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F YXXX() const { return Vec4F(y, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F YXXY() const { return Vec4F(y, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F YXXZ() const { return Vec4F(y, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F YXXW() const { return Vec4F(y, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F YXYX() const { return Vec4F(y, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F YXYY() const { return Vec4F(y, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F YXYZ() const { return Vec4F(y, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F YXYW() const { return Vec4F(y, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F YXZX() const { return Vec4F(y, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F YXZY() const { return Vec4F(y, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F YXZZ() const { return Vec4F(y, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F YXZW() const { return Vec4F(y, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F YXWX() const { return Vec4F(y, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F YXWY() const { return Vec4F(y, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F YXWZ() const { return Vec4F(y, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F YXWW() const { return Vec4F(y, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F YYXX() const { return Vec4F(y, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F YYXY() const { return Vec4F(y, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F YYXZ() const { return Vec4F(y, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F YYXW() const { return Vec4F(y, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F YYYX() const { return Vec4F(y, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F YYYY() const { return Vec4F(y, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F YYYZ() const { return Vec4F(y, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F YYYW() const { return Vec4F(y, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F YYZX() const { return Vec4F(y, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F YYZY() const { return Vec4F(y, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F YYZZ() const { return Vec4F(y, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F YYZW() const { return Vec4F(y, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F YYWX() const { return Vec4F(y, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F YYWY() const { return Vec4F(y, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F YYWZ() const { return Vec4F(y, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F YYWW() const { return Vec4F(y, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F YZXX() const { return Vec4F(y, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F YZXY() const { return Vec4F(y, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F YZXZ() const { return Vec4F(y, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F YZXW() const { return Vec4F(y, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F YZYX() const { return Vec4F(y, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F YZYY() const { return Vec4F(y, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F YZYZ() const { return Vec4F(y, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F YZYW() const { return Vec4F(y, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F YZZX() const { return Vec4F(y, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F YZZY() const { return Vec4F(y, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F YZZZ() const { return Vec4F(y, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F YZZW() const { return Vec4F(y, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F YZWX() const { return Vec4F(y, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F YZWY() const { return Vec4F(y, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F YZWZ() const { return Vec4F(y, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F YZWW() const { return Vec4F(y, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F YWXX() const { return Vec4F(y, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F YWXY() const { return Vec4F(y, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F YWXZ() const { return Vec4F(y, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F YWXW() const { return Vec4F(y, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F YWYX() const { return Vec4F(y, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F YWYY() const { return Vec4F(y, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F YWYZ() const { return Vec4F(y, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F YWYW() const { return Vec4F(y, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F YWZX() const { return Vec4F(y, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F YWZY() const { return Vec4F(y, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F YWZZ() const { return Vec4F(y, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F YWZW() const { return Vec4F(y, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F YWWX() const { return Vec4F(y, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F YWWY() const { return Vec4F(y, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F YWWZ() const { return Vec4F(y, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F YWWW() const { return Vec4F(y, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ZXXX() const { return Vec4F(z, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ZXXY() const { return Vec4F(z, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ZXXZ() const { return Vec4F(z, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ZXXW() const { return Vec4F(z, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ZXYX() const { return Vec4F(z, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ZXYY() const { return Vec4F(z, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ZXYZ() const { return Vec4F(z, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ZXYW() const { return Vec4F(z, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ZXZX() const { return Vec4F(z, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ZXZY() const { return Vec4F(z, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ZXZZ() const { return Vec4F(z, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ZXZW() const { return Vec4F(z, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ZXWX() const { return Vec4F(z, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ZXWY() const { return Vec4F(z, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ZXWZ() const { return Vec4F(z, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ZXWW() const { return Vec4F(z, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ZYXX() const { return Vec4F(z, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ZYXY() const { return Vec4F(z, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ZYXZ() const { return Vec4F(z, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ZYXW() const { return Vec4F(z, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ZYYX() const { return Vec4F(z, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ZYYY() const { return Vec4F(z, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ZYYZ() const { return Vec4F(z, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ZYYW() const { return Vec4F(z, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ZYZX() const { return Vec4F(z, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ZYZY() const { return Vec4F(z, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ZYZZ() const { return Vec4F(z, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ZYZW() const { return Vec4F(z, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ZYWX() const { return Vec4F(z, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ZYWY() const { return Vec4F(z, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ZYWZ() const { return Vec4F(z, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ZYWW() const { return Vec4F(z, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ZZXX() const { return Vec4F(z, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ZZXY() const { return Vec4F(z, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ZZXZ() const { return Vec4F(z, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ZZXW() const { return Vec4F(z, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ZZYX() const { return Vec4F(z, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ZZYY() const { return Vec4F(z, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ZZYZ() const { return Vec4F(z, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ZZYW() const { return Vec4F(z, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ZZZX() const { return Vec4F(z, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ZZZY() const { return Vec4F(z, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ZZZZ() const { return Vec4F(z, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ZZZW() const { return Vec4F(z, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ZZWX() const { return Vec4F(z, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ZZWY() const { return Vec4F(z, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ZZWZ() const { return Vec4F(z, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ZZWW() const { return Vec4F(z, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ZWXX() const { return Vec4F(z, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ZWXY() const { return Vec4F(z, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ZWXZ() const { return Vec4F(z, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ZWXW() const { return Vec4F(z, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ZWYX() const { return Vec4F(z, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ZWYY() const { return Vec4F(z, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ZWYZ() const { return Vec4F(z, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ZWYW() const { return Vec4F(z, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ZWZX() const { return Vec4F(z, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ZWZY() const { return Vec4F(z, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ZWZZ() const { return Vec4F(z, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ZWZW() const { return Vec4F(z, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ZWWX() const { return Vec4F(z, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ZWWY() const { return Vec4F(z, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ZWWZ() const { return Vec4F(z, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ZWWW() const { return Vec4F(z, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F WXXX() const { return Vec4F(w, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F WXXY() const { return Vec4F(w, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F WXXZ() const { return Vec4F(w, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F WXXW() const { return Vec4F(w, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F WXYX() const { return Vec4F(w, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F WXYY() const { return Vec4F(w, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F WXYZ() const { return Vec4F(w, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F WXYW() const { return Vec4F(w, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F WXZX() const { return Vec4F(w, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F WXZY() const { return Vec4F(w, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F WXZZ() const { return Vec4F(w, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F WXZW() const { return Vec4F(w, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F WXWX() const { return Vec4F(w, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F WXWY() const { return Vec4F(w, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F WXWZ() const { return Vec4F(w, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F WXWW() const { return Vec4F(w, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F WYXX() const { return Vec4F(w, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F WYXY() const { return Vec4F(w, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F WYXZ() const { return Vec4F(w, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F WYXW() const { return Vec4F(w, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F WYYX() const { return Vec4F(w, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F WYYY() const { return Vec4F(w, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F WYYZ() const { return Vec4F(w, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F WYYW() const { return Vec4F(w, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F WYZX() const { return Vec4F(w, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F WYZY() const { return Vec4F(w, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F WYZZ() const { return Vec4F(w, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F WYZW() const { return Vec4F(w, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F WYWX() const { return Vec4F(w, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F WYWY() const { return Vec4F(w, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F WYWZ() const { return Vec4F(w, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F WYWW() const { return Vec4F(w, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F WZXX() const { return Vec4F(w, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F WZXY() const { return Vec4F(w, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F WZXZ() const { return Vec4F(w, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F WZXW() const { return Vec4F(w, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F WZYX() const { return Vec4F(w, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F WZYY() const { return Vec4F(w, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F WZYZ() const { return Vec4F(w, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F WZYW() const { return Vec4F(w, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F WZZX() const { return Vec4F(w, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F WZZY() const { return Vec4F(w, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F WZZZ() const { return Vec4F(w, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F WZZW() const { return Vec4F(w, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F WZWX() const { return Vec4F(w, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F WZWY() const { return Vec4F(w, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F WZWZ() const { return Vec4F(w, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F WZWW() const { return Vec4F(w, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F WWXX() const { return Vec4F(w, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F WWXY() const { return Vec4F(w, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F WWXZ() const { return Vec4F(w, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F WWXW() const { return Vec4F(w, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F WWYX() const { return Vec4F(w, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F WWYY() const { return Vec4F(w, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F WWYZ() const { return Vec4F(w, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F WWYW() const { return Vec4F(w, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F WWZX() const { return Vec4F(w, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F WWZY() const { return Vec4F(w, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F WWZZ() const { return Vec4F(w, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F WWZW() const { return Vec4F(w, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F WWWX() const { return Vec4F(w, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F WWWY() const { return Vec4F(w, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F WWWZ() const { return Vec4F(w, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F WWWW() const { return Vec4F(w, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F RRRR() const { return Vec4F(x, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F RRRG() const { return Vec4F(x, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F RRRB() const { return Vec4F(x, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F RRRA() const { return Vec4F(x, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F RRGR() const { return Vec4F(x, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F RRGG() const { return Vec4F(x, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F RRGB() const { return Vec4F(x, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F RRGA() const { return Vec4F(x, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F RRBR() const { return Vec4F(x, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F RRBG() const { return Vec4F(x, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F RRBB() const { return Vec4F(x, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F RRBA() const { return Vec4F(x, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F RRAR() const { return Vec4F(x, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F RRAG() const { return Vec4F(x, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F RRAB() const { return Vec4F(x, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F RRAA() const { return Vec4F(x, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F RGRR() const { return Vec4F(x, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F RGRG() const { return Vec4F(x, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F RGRB() const { return Vec4F(x, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F RGRA() const { return Vec4F(x, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F RGGR() const { return Vec4F(x, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F RGGG() const { return Vec4F(x, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F RGGB() const { return Vec4F(x, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F RGGA() const { return Vec4F(x, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F RGBR() const { return Vec4F(x, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F RGBG() const { return Vec4F(x, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F RGBB() const { return Vec4F(x, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F RGAR() const { return Vec4F(x, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F RGAG() const { return Vec4F(x, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F RGAB() const { return Vec4F(x, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F RGAA() const { return Vec4F(x, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F RBRR() const { return Vec4F(x, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F RBRG() const { return Vec4F(x, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F RBRB() const { return Vec4F(x, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F RBRA() const { return Vec4F(x, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F RBGR() const { return Vec4F(x, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F RBGG() const { return Vec4F(x, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F RBGB() const { return Vec4F(x, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F RBGA() const { return Vec4F(x, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F RBBR() const { return Vec4F(x, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F RBBG() const { return Vec4F(x, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F RBBB() const { return Vec4F(x, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F RBBA() const { return Vec4F(x, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F RBAR() const { return Vec4F(x, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F RBAG() const { return Vec4F(x, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F RBAB() const { return Vec4F(x, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F RBAA() const { return Vec4F(x, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F RARR() const { return Vec4F(x, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F RARG() const { return Vec4F(x, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F RARB() const { return Vec4F(x, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F RARA() const { return Vec4F(x, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F RAGR() const { return Vec4F(x, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F RAGG() const { return Vec4F(x, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F RAGB() const { return Vec4F(x, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F RAGA() const { return Vec4F(x, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F RABR() const { return Vec4F(x, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F RABG() const { return Vec4F(x, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F RABB() const { return Vec4F(x, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F RABA() const { return Vec4F(x, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F RAAR() const { return Vec4F(x, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F RAAG() const { return Vec4F(x, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F RAAB() const { return Vec4F(x, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F RAAA() const { return Vec4F(x, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F GRRR() const { return Vec4F(y, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F GRRG() const { return Vec4F(y, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F GRRB() const { return Vec4F(y, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F GRRA() const { return Vec4F(y, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F GRGR() const { return Vec4F(y, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F GRGG() const { return Vec4F(y, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F GRGB() const { return Vec4F(y, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F GRGA() const { return Vec4F(y, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F GRBR() const { return Vec4F(y, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F GRBG() const { return Vec4F(y, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F GRBB() const { return Vec4F(y, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F GRBA() const { return Vec4F(y, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F GRAR() const { return Vec4F(y, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F GRAG() const { return Vec4F(y, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F GRAB() const { return Vec4F(y, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F GRAA() const { return Vec4F(y, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F GGRR() const { return Vec4F(y, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F GGRG() const { return Vec4F(y, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F GGRB() const { return Vec4F(y, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F GGRA() const { return Vec4F(y, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F GGGR() const { return Vec4F(y, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F GGGG() const { return Vec4F(y, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F GGGB() const { return Vec4F(y, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F GGGA() const { return Vec4F(y, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F GGBR() const { return Vec4F(y, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F GGBG() const { return Vec4F(y, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F GGBB() const { return Vec4F(y, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F GGBA() const { return Vec4F(y, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F GGAR() const { return Vec4F(y, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F GGAG() const { return Vec4F(y, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F GGAB() const { return Vec4F(y, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F GGAA() const { return Vec4F(y, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F GBRR() const { return Vec4F(y, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F GBRG() const { return Vec4F(y, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F GBRB() const { return Vec4F(y, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F GBRA() const { return Vec4F(y, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F GBGR() const { return Vec4F(y, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F GBGG() const { return Vec4F(y, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F GBGB() const { return Vec4F(y, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F GBGA() const { return Vec4F(y, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F GBBR() const { return Vec4F(y, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F GBBG() const { return Vec4F(y, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F GBBB() const { return Vec4F(y, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F GBBA() const { return Vec4F(y, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F GBAR() const { return Vec4F(y, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F GBAG() const { return Vec4F(y, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F GBAB() const { return Vec4F(y, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F GBAA() const { return Vec4F(y, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F GARR() const { return Vec4F(y, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F GARG() const { return Vec4F(y, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F GARB() const { return Vec4F(y, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F GARA() const { return Vec4F(y, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F GAGR() const { return Vec4F(y, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F GAGG() const { return Vec4F(y, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F GAGB() const { return Vec4F(y, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F GAGA() const { return Vec4F(y, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F GABR() const { return Vec4F(y, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F GABG() const { return Vec4F(y, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F GABB() const { return Vec4F(y, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F GABA() const { return Vec4F(y, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F GAAR() const { return Vec4F(y, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F GAAG() const { return Vec4F(y, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F GAAB() const { return Vec4F(y, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F GAAA() const { return Vec4F(y, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F BRRR() const { return Vec4F(z, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F BRRG() const { return Vec4F(z, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F BRRB() const { return Vec4F(z, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F BRRA() const { return Vec4F(z, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F BRGR() const { return Vec4F(z, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F BRGG() const { return Vec4F(z, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F BRGB() const { return Vec4F(z, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F BRGA() const { return Vec4F(z, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F BRBR() const { return Vec4F(z, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F BRBG() const { return Vec4F(z, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F BRBB() const { return Vec4F(z, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F BRBA() const { return Vec4F(z, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F BRAR() const { return Vec4F(z, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F BRAG() const { return Vec4F(z, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F BRAB() const { return Vec4F(z, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F BRAA() const { return Vec4F(z, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F BGRR() const { return Vec4F(z, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F BGRG() const { return Vec4F(z, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F BGRB() const { return Vec4F(z, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F BGRA() const { return Vec4F(z, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F BGGR() const { return Vec4F(z, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F BGGG() const { return Vec4F(z, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F BGGB() const { return Vec4F(z, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F BGGA() const { return Vec4F(z, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F BGBR() const { return Vec4F(z, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F BGBG() const { return Vec4F(z, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F BGBB() const { return Vec4F(z, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F BGBA() const { return Vec4F(z, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F BGAR() const { return Vec4F(z, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F BGAG() const { return Vec4F(z, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F BGAB() const { return Vec4F(z, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F BGAA() const { return Vec4F(z, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F BBRR() const { return Vec4F(z, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F BBRG() const { return Vec4F(z, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F BBRB() const { return Vec4F(z, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F BBRA() const { return Vec4F(z, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F BBGR() const { return Vec4F(z, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F BBGG() const { return Vec4F(z, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F BBGB() const { return Vec4F(z, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F BBGA() const { return Vec4F(z, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F BBBR() const { return Vec4F(z, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F BBBG() const { return Vec4F(z, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F BBBB() const { return Vec4F(z, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F BBBA() const { return Vec4F(z, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F BBAR() const { return Vec4F(z, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F BBAG() const { return Vec4F(z, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F BBAB() const { return Vec4F(z, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F BBAA() const { return Vec4F(z, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F BARR() const { return Vec4F(z, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F BARG() const { return Vec4F(z, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F BARB() const { return Vec4F(z, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F BARA() const { return Vec4F(z, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F BAGR() const { return Vec4F(z, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F BAGG() const { return Vec4F(z, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F BAGB() const { return Vec4F(z, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F BAGA() const { return Vec4F(z, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F BABR() const { return Vec4F(z, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F BABG() const { return Vec4F(z, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F BABB() const { return Vec4F(z, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F BABA() const { return Vec4F(z, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F BAAR() const { return Vec4F(z, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F BAAG() const { return Vec4F(z, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F BAAB() const { return Vec4F(z, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F BAAA() const { return Vec4F(z, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ARRR() const { return Vec4F(w, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ARRG() const { return Vec4F(w, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ARRB() const { return Vec4F(w, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ARRA() const { return Vec4F(w, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ARGR() const { return Vec4F(w, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ARGG() const { return Vec4F(w, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ARGB() const { return Vec4F(w, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ARGA() const { return Vec4F(w, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ARBR() const { return Vec4F(w, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ARBG() const { return Vec4F(w, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ARBB() const { return Vec4F(w, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ARBA() const { return Vec4F(w, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ARAR() const { return Vec4F(w, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ARAG() const { return Vec4F(w, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ARAB() const { return Vec4F(w, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ARAA() const { return Vec4F(w, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4F AGRR() const { return Vec4F(w, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4F AGRG() const { return Vec4F(w, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4F AGRB() const { return Vec4F(w, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4F AGRA() const { return Vec4F(w, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4F AGGR() const { return Vec4F(w, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4F AGGG() const { return Vec4F(w, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4F AGGB() const { return Vec4F(w, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4F AGGA() const { return Vec4F(w, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4F AGBR() const { return Vec4F(w, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4F AGBG() const { return Vec4F(w, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4F AGBB() const { return Vec4F(w, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4F AGBA() const { return Vec4F(w, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4F AGAR() const { return Vec4F(w, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4F AGAG() const { return Vec4F(w, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4F AGAB() const { return Vec4F(w, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4F AGAA() const { return Vec4F(w, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4F ABRR() const { return Vec4F(w, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4F ABRG() const { return Vec4F(w, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4F ABRB() const { return Vec4F(w, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4F ABRA() const { return Vec4F(w, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4F ABGR() const { return Vec4F(w, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4F ABGG() const { return Vec4F(w, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4F ABGB() const { return Vec4F(w, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4F ABGA() const { return Vec4F(w, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4F ABBR() const { return Vec4F(w, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4F ABBG() const { return Vec4F(w, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4F ABBB() const { return Vec4F(w, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4F ABBA() const { return Vec4F(w, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4F ABAR() const { return Vec4F(w, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4F ABAG() const { return Vec4F(w, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4F ABAB() const { return Vec4F(w, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4F ABAA() const { return Vec4F(w, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4F AARR() const { return Vec4F(w, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4F AARG() const { return Vec4F(w, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4F AARB() const { return Vec4F(w, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4F AARA() const { return Vec4F(w, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4F AAGR() const { return Vec4F(w, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4F AAGG() const { return Vec4F(w, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4F AAGB() const { return Vec4F(w, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4F AAGA() const { return Vec4F(w, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4F AABR() const { return Vec4F(w, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4F AABG() const { return Vec4F(w, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4F AABB() const { return Vec4F(w, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4F AABA() const { return Vec4F(w, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4F AAAR() const { return Vec4F(w, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4F AAAG() const { return Vec4F(w, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4F AAAB() const { return Vec4F(w, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4F AAAA() const { return Vec4F(w, w, w, w); }
};

[[nodiscard]] HC_INLINE Vec4F operator+(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y, _vLeft.z + _vRight.z, _vLeft.w + _vRight.w); }
[[nodiscard]] HC_INLINE Vec4F operator-(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y, _vLeft.z - _vRight.z, _vLeft.w - _vRight.w); }
[[nodiscard]] HC_INLINE Vec4F operator*(const Vec4F& _vLeft, float _fRight) { return Vec4F(_vLeft.x * _fRight, _vLeft.y * _fRight, _vLeft.z * _fRight, _vLeft.w * _fRight); }
[[nodiscard]] HC_INLINE Vec4F operator*(float _fLeft, const Vec4F& _vRight) { return Vec4F(_vRight.x * _fLeft, _vRight.y * _fLeft, _vRight.z * _fLeft, _vRight.w * _fLeft); }
[[nodiscard]] HC_INLINE Vec4F operator/(const Vec4F& _vLeft, float _fRight) { return Vec4F(_vLeft.x / _fRight, _vLeft.y / _fRight, _vLeft.z / _fRight, _vLeft.w / _fRight); }
[[nodiscard]] HC_INLINE Vec4F operator/(float _fLeft, const Vec4F& _vRight) { return Vec4F(_fLeft / _vRight.x, _fLeft / _vRight.y, _fLeft / _vRight.z, _fLeft / _vRight.w); }
[[nodiscard]] HC_INLINE Vec4F operator*(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y, _vLeft.z * _vRight.z, _vLeft.w * _vRight.w); }
[[nodiscard]] HC_INLINE Vec4F operator/(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(_vLeft.x / _vRight.x, _vLeft.y / _vRight.y, _vLeft.z / _vRight.z, _vLeft.w / _vRight.w); }
HC_INLINE Vec4F& operator+=(Vec4F& _vLeft, const Vec4F& _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4F& operator-=(Vec4F& _vLeft, const Vec4F& _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, const Vec4F& _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4F& operator/=(Vec4F& _vLeft, const Vec4F& _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4F& operator/=(Vec4F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec4F operator~(const Vec4F& _vVector) { return Vec4F(); }
[[nodiscard]] HC_INLINE Vec4F operator-(const Vec4F& _vVector) { return Vec4F(-_vVector.x, -_vVector.y, -_vVector.z, -_vVector.w); }
HC_INLINE bool operator==(const Vec4F& _vLeft, const Vec4F& _vRight) { return HC_FLOAT_COMPARE(_vLeft.x, _vRight.x) && HC_FLOAT_COMPARE(_vLeft.y, _vRight.y) && HC_FLOAT_COMPARE(_vLeft.z, _vRight.z) && HC_FLOAT_COMPARE(_vLeft.w, _vRight.w); }
HC_INLINE bool operator<(const Vec4F& _vLeft, const Vec4F& _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y && _vLeft.z < _vRight.z && _vLeft.w < _vRight.w; }
HC_INLINE bool operator>(const Vec4F& _vLeft, const Vec4F& _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y && _vLeft.z > _vRight.z && _vLeft.w > _vRight.w; }
HC_INLINE bool operator<=(const Vec4F& _vLeft, const Vec4F& _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(const Vec4F& _vLeft, const Vec4F& _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(const Vec4F& _vLeft, const Vec4F& _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec4F Min(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(HC_TERNARY(_vLeft.x, _vRight.x, <), HC_TERNARY(_vLeft.y, _vRight.y, <), HC_TERNARY(_vLeft.z, _vRight.z, <), HC_TERNARY(_vLeft.w, _vRight.w, <)); }
[[nodiscard]] HC_INLINE Vec4F Max(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(HC_TERNARY(_vLeft.x, _vRight.x, >), HC_TERNARY(_vLeft.y, _vRight.y, >), HC_TERNARY(_vLeft.z, _vRight.z, >), HC_TERNARY(_vLeft.w, _vRight.w, >)); }
[[nodiscard]] HC_INLINE Vec4F Clamp(const Vec4F& _vVector, const Vec4F& _vMin, Vec4F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
[[nodiscard]] HC_INLINE float Sum(const Vec4F& _vVector) { return _vVector.x + _vVector.y + _vVector.z + _vVector.w; }
[[nodiscard]] HC_INLINE float Dot(const Vec4F& _vLeft, const Vec4F& _vRight) { return Sum((_vLeft * _vRight).XYZ()); }
[[nodiscard]] HC_INLINE float Length(const Vec4F& _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE float LengthSquared(const Vec4F& _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec4F Normalize(const Vec4F& _vVector) { return _vVector * (1.0f / Length(_vVector)); }
[[nodiscard]] HC_INLINE float AngleBetween(const Vec4F& _vLeft, const Vec4F& _vRight) { return acosf(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE Vec4F Cross(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F((_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY(), _vLeft.w); }
[[nodiscard]] HC_INLINE Vec4F Abs(const Vec4F& _vVector) { return Vec4F(abs(_vVector.x), abs(_vVector.y), abs(_vVector.z), abs(_vVector.w)); }

#endif