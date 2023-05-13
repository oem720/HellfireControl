#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
#define HC_SHUFFLE2D(_vec, _x, _y)  Vec2D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_y, _y, _y, _x)))

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

#else

struct HC_ALIGNAS(16) Vec2D
{
	union
	{
		double m_dData[2];
		struct
		{
			double x;
			double y;
		};
	};

	HC_INLINE Vec2D() { m_dData[0] = 0.0; m_dData[1] = 0.0; }
	HC_INLINE explicit Vec2D(float _fVal) { m_dData[0] = static_cast<double>(_fVal); m_dData[1] = static_cast<double>(_fVal); }
	HC_INLINE explicit Vec2D(int _iVal) { m_dData[0] = static_cast<double>(_iVal); m_dData[1] = static_cast<double>(_iVal); }
	HC_INLINE explicit Vec2D(double _dVal) { m_dData[0] = _dVal; m_dData[1] = _dVal; }
	HC_INLINE explicit Vec2D(float _fX, float _fY) { m_dData[0] = static_cast<double>(_fX); m_dData[1] = static_cast<double>(_fY); }
	HC_INLINE explicit Vec2D(int _iX, int _iY) { m_dData[0] = static_cast<float>(_iX); m_dData[1] = static_cast<float>(_iY); }
	HC_INLINE explicit Vec2D(double _dX, double _dY) { m_dData[0] = _dX; m_dData[1] = _dY; }

	[[nodiscard]] HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 2); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 2); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2D XX() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D YY() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D YX() const { return Vec2D(y, x); }
	[[nodiscard]] HC_INLINE Vec2D RR() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D GG() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D GR() const { return Vec2D(y, x); }
};

[[nodiscard]] HC_INLINE Vec2D operator+(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y); }
[[nodiscard]] HC_INLINE Vec2D operator-(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y); }
[[nodiscard]] HC_INLINE Vec2D operator*(const Vec2D& _vLeft, double _dRight) { return Vec2D(_vLeft.x * _dRight, _vLeft.y * _dRight); }
[[nodiscard]] HC_INLINE Vec2D operator*(double _dLeft, const Vec2D& _vRight) { return Vec2D(_vRight.x * _dLeft, _vRight.y * _dLeft); }
[[nodiscard]] HC_INLINE Vec2D operator/(const Vec2D& _vLeft, double _dRight) { return Vec2D(_vLeft.x / _dRight, _vLeft.y / _dRight); }
[[nodiscard]] HC_INLINE Vec2D operator/(double _dLeft, const Vec2D& _vRight) { return Vec2D(_dLeft / _vRight.x, _dLeft / _vRight.y); }
[[nodiscard]] HC_INLINE Vec2D operator*(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y); }
[[nodiscard]] HC_INLINE Vec2D operator/(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(_vLeft.x / _vRight.x, _vLeft.y * _vRight.y); }
HC_INLINE Vec2D& operator+=(Vec2D& _vLeft, const Vec2D& _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2D& operator-=(Vec2D& _vLeft, const Vec2D& _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2D& operator*=(Vec2D& _vLeft, const Vec2D& _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2D& operator/=(Vec2D& _vLeft, const Vec2D& _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2D& operator*=(Vec2D& _vLeft, double _dRight) { _vLeft = _vLeft * _dRight; return _vLeft; }
HC_INLINE Vec2D& operator/=(Vec2D& _vLeft, double _dRight) { _vLeft = _vLeft / _dRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec2D operator~(const Vec2D& _vVector) { return Vec2D(); }
[[nodiscard]] HC_INLINE Vec2D operator-(const Vec2D& _vVector) { return Vec2D(-_vVector.x, -_vVector.y); }
HC_INLINE bool operator==(const Vec2D& _vLeft, const Vec2D& _vRight) { return HC_DOUBLE_COMPARE(_vLeft.x, _vRight.x) && HC_DOUBLE_COMPARE(_vLeft.y, _vRight.y); }
HC_INLINE bool operator<(const Vec2D& _vLeft, const Vec2D& _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y; }
HC_INLINE bool operator>(const Vec2D& _vLeft, const Vec2D& _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y; }
HC_INLINE bool operator<=(const Vec2D& _vLeft, const Vec2D& _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(const Vec2D& _vLeft, const Vec2D& _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(const Vec2D& _vLeft, const Vec2D& _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec2D Min(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(HC_TERNARY(_vLeft.x, _vRight.x, < ), HC_TERNARY(_vLeft.y, _vRight.y, < )); }
[[nodiscard]] HC_INLINE Vec2D Max(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(HC_TERNARY(_vLeft.x, _vRight.x, > ), HC_TERNARY(_vLeft.y, _vRight.y, > )); }
[[nodiscard]] HC_INLINE double Sum(const Vec2D& _vVector) { return _vVector.x + _vVector.y; }
[[nodiscard]] HC_INLINE double Dot(const Vec2D& _vLeft, const Vec2D& _vRight) { return Sum(_vLeft * _vRight); }
[[nodiscard]] HC_INLINE double Length(const Vec2D& _vVector) { return sqrt(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE double LengthSquared(const Vec2D& _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec2D Normalize(const Vec2D& _vVector) { return _vVector * (1.0 / Length(_vVector)); }
[[nodiscard]] HC_INLINE double AngleBetween(const Vec2D& _vLeft, const Vec2D& _vRight) { return acos(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE double Cross(const Vec2D& _vLeft, const Vec2D& _vRight) { return _vLeft.x * _vRight.y - _vLeft.y * _vRight.x; }
[[nodiscard]] HC_INLINE Vec2D Abs(const Vec2D& _vVector) { return Vec2D(abs(_vVector.x), abs(_vVector.y)); }

#endif