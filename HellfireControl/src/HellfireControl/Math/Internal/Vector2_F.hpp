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
		float m_fData[2];
		struct
		{
			float x;
			float y;
		};
	};

	HC_INLINE Vec2F() { m_fData[0] = 0.0f; m_fData[1] = 0.0f; }
	HC_INLINE explicit Vec2F(float _fVal) { m_fData[0] = _fVal; m_fData[1] = _fVal; }
	HC_INLINE explicit Vec2F(int _iVal) { m_fData[0] = static_cast<float>(_iVal); m_fData[1] = static_cast<float>(_iVal); }
	HC_INLINE explicit Vec2F(double _dVal) { m_fData[0] = static_cast<float>(_dVal); m_fData[1] = static_cast<float>(_dVal); }
	HC_INLINE explicit Vec2F(float _fX, float _fY) { m_fData[0] = _fX; m_fData[1] = _fY; }
	HC_INLINE explicit Vec2F(int _iX, int _iY) { m_fData[0] = static_cast<float>(_iX); m_fData[1] = static_cast<float>(_iY); }
	HC_INLINE explicit Vec2F(double _dX, double _dY) { m_fData[0] = static_cast<float>(_dX); m_fData[1] = static_cast<float>(_dY); }

	[[nodiscard]] HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 2); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 2); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2F XX() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F YY() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F YX() const { return Vec2F(y, x); }
	[[nodiscard]] HC_INLINE Vec2F RR() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F GG() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F GR() const { return Vec2F(y, x); }
};

[[nodiscard]] HC_INLINE Vec2F operator+(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y); }
[[nodiscard]] HC_INLINE Vec2F operator-(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y); }
[[nodiscard]] HC_INLINE Vec2F operator*(Vec2F _vLeft, float _fRight) { return Vec2F(_vLeft.x * _fRight, _vLeft.y * _fRight); }
[[nodiscard]] HC_INLINE Vec2F operator*(float _fLeft, Vec2F _vRight) { return Vec2F(_vRight.x * _fLeft, _vRight.y * _fLeft); }
[[nodiscard]] HC_INLINE Vec2F operator/(Vec2F _vLeft, float _fRight) { return Vec2F(_vLeft.x / _fRight, _vLeft.y / _fRight); }
[[nodiscard]] HC_INLINE Vec2F operator/(float _fLeft, Vec2F _vRight) { return Vec2F(_fLeft / _vRight.x, _fLeft / _vRight.y); }
[[nodiscard]] HC_INLINE Vec2F operator*(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y); }
[[nodiscard]] HC_INLINE Vec2F operator/(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(_vLeft.x / _vRight.x, _vLeft.y * _vRight.y); }
HC_INLINE Vec2F& operator+=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2F& operator-=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2F& operator*=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2F& operator/=(Vec2F& _vLeft, Vec2F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2F& operator*=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2F& operator/=(Vec2F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec2F operator~(Vec2F _vVector) { return Vec2F(); }
[[nodiscard]] HC_INLINE Vec2F operator-(Vec2F _vVector) { return Vec2F(-_vVector.x, -_vVector.y); }
HC_INLINE bool operator==(Vec2F _vLeft, Vec2F _vRight) { return HC_FLOAT_COMPARE(_vLeft.x, _vRight.x) && HC_FLOAT_COMPARE(_vLeft.y, _vRight.y); }
HC_INLINE bool operator<(Vec2F _vLeft, Vec2F _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y; }
HC_INLINE bool operator>(Vec2F _vLeft, Vec2F _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y; }
HC_INLINE bool operator<=(Vec2F _vLeft, Vec2F _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(Vec2F _vLeft, Vec2F _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(Vec2F _vLeft, Vec2F _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec2F Min(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(HC_TERNARY(_vLeft.x, _vRight.x, <), HC_TERNARY(_vLeft.y, _vRight.y, <)); }
[[nodiscard]] HC_INLINE Vec2F Max(Vec2F _vLeft, Vec2F _vRight) { return Vec2F(HC_TERNARY(_vLeft.x, _vRight.x, >), HC_TERNARY(_vLeft.y, _vRight.y, >)); }
[[nodiscard]] HC_INLINE Vec2F Clamp(Vec2F _vVal, Vec2F _vMin, Vec2F _vMax) { return Min(Max(_vVal, _vMax), _vMin); }
[[nodiscard]] HC_INLINE float Sum(const Vec2F _vVector) { return _vVector.x + _vVector.y; }
[[nodiscard]] HC_INLINE float Dot(Vec2F _vLeft, Vec2F _vRight) { return Sum(_vLeft * _vRight); }
[[nodiscard]] HC_INLINE float Length(Vec2F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE float LengthSquared(Vec2F _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec2F Normalize(Vec2F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
[[nodiscard]] HC_INLINE float AngleBetween(Vec2F _vLeft, Vec2F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE float Cross(Vec2F _vLeft, Vec2F _vRight) { return _vLeft.x * _vRight.y - _vLeft.y * _vRight.x; }
[[nodiscard]] HC_INLINE Vec2F Abs(Vec2F _vVector) { return Vec2F(abs(_vVector.x), abs(_vVector.y)); }

#endif