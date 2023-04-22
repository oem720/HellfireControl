#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
#define HC_SHUFFLE2F(_vec, _x, _y) Vec2F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_y, _y, _y, _x)))

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

#else

struct HC_ALIGNAS(8) Vec2F
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

#endif