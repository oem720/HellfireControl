#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
#define HC_SHUFFLE3D(_vec, _x, _y, _z) Vec3D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_z, _z, _y, _x)))

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

#else

struct HC_ALIGNAS(32) Vec3D
{
	union
	{
		double m_dData[3];
		struct
		{
			double x;
			double y;
			double z;
		};
	};

	HC_INLINE Vec3D() { m_dData[0] = 0.0f; m_dData[1] = 0.0f; m_dData[2] = 0.0f; }
	HC_INLINE explicit Vec3D(float _fVal) { m_dData[0] = static_cast<double>(_fVal); m_dData[1] = static_cast<double>(_fVal); m_dData[2] = static_cast<double>(_fVal); }
	HC_INLINE explicit Vec3D(int _iVal) { m_dData[0] = static_cast<double>(_iVal); m_dData[1] = static_cast<double>(_iVal); m_dData[2] = static_cast<double>(_iVal); }
	HC_INLINE explicit Vec3D(double _dVal) { m_dData[0] = _dVal; m_dData[1] = _dVal; m_dData[2] = _dVal; }
	HC_INLINE explicit Vec3D(float _fX, float _fY, float _fZ) { m_dData[0] = static_cast<double>(_fX); m_dData[1] = static_cast<double>(_fY); m_dData[2] = static_cast<double>(_fZ); }
	HC_INLINE explicit Vec3D(int _iX, int _iY, int _iZ) { m_dData[0] = static_cast<double>(_iX); m_dData[1] = static_cast<double>(_iY); m_dData[2] = static_cast<double>(_iZ); }
	HC_INLINE explicit Vec3D(double _dX, double _dY, double _dZ) { m_dData[0] = _dX; m_dData[1] = _dY; m_dData[2] = _dZ; }
	HC_INLINE explicit Vec3D(Vec2D _vXY, double _fZ) { m_dData[0] = _vXY.x; m_dData[1] = _vXY.y; m_dData[2] = _fZ; }
	HC_INLINE explicit Vec3D(double _fX, Vec2D _vYZ) { m_dData[0] = _fX; m_dData[1] = _vYZ.x; m_dData[2] = _vYZ.y; }

	[[nodiscard]] HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 3); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 3); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2D XX() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D YY() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D ZZ() const { return Vec2D(z, z); }
	[[nodiscard]] HC_INLINE Vec2D XY() const { return Vec2D(x, y); }
	[[nodiscard]] HC_INLINE Vec2D XZ() const { return Vec2D(x, z); }
	[[nodiscard]] HC_INLINE Vec2D YX() const { return Vec2D(y, x); }
	[[nodiscard]] HC_INLINE Vec2D YZ() const { return Vec2D(y, z); }
	[[nodiscard]] HC_INLINE Vec2D ZX() const { return Vec2D(z, x); }
	[[nodiscard]] HC_INLINE Vec2D ZY() const { return Vec2D(z, y); }
	[[nodiscard]] HC_INLINE Vec2D RR() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D GG() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D BB() const { return Vec2D(z, z); }
	[[nodiscard]] HC_INLINE Vec2D RG() const { return Vec2D(x, y); }
	[[nodiscard]] HC_INLINE Vec2D RB() const { return Vec2D(x, z); }
	[[nodiscard]] HC_INLINE Vec2D GR() const { return Vec2D(y, x); }
	[[nodiscard]] HC_INLINE Vec2D GB() const { return Vec2D(y, z); }
	[[nodiscard]] HC_INLINE Vec2D BR() const { return Vec2D(z, x); }
	[[nodiscard]] HC_INLINE Vec2D BG() const { return Vec2D(z, y); }
	[[nodiscard]] HC_INLINE Vec3D XXX() const { return Vec3D(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3D XXY() const { return Vec3D(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3D XXZ() const { return Vec3D(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3D XYX() const { return Vec3D(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3D XYY() const { return Vec3D(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3D XZX() const { return Vec3D(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3D XZY() const { return Vec3D(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3D XZZ() const { return Vec3D(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3D YXX() const { return Vec3D(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3D YXY() const { return Vec3D(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3D YXZ() const { return Vec3D(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3D YYX() const { return Vec3D(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3D YYY() const { return Vec3D(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3D YYZ() const { return Vec3D(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3D YZX() const { return Vec3D(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3D YZY() const { return Vec3D(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3D YZZ() const { return Vec3D(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3D ZXX() const { return Vec3D(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3D ZXY() const { return Vec3D(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3D ZXZ() const { return Vec3D(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3D ZYX() const { return Vec3D(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3D ZYY() const { return Vec3D(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3D ZYZ() const { return Vec3D(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3D ZZX() const { return Vec3D(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3D ZZY() const { return Vec3D(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3D ZZZ() const { return Vec3D(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3D RRR() const { return Vec3D(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3D RRG() const { return Vec3D(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3D RRB() const { return Vec3D(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3D RGR() const { return Vec3D(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3D RGG() const { return Vec3D(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3D RBR() const { return Vec3D(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3D RBG() const { return Vec3D(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3D RBB() const { return Vec3D(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3D GRR() const { return Vec3D(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3D GRG() const { return Vec3D(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3D GRB() const { return Vec3D(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3D GGR() const { return Vec3D(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3D GGG() const { return Vec3D(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3D GGB() const { return Vec3D(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3D GBR() const { return Vec3D(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3D GBG() const { return Vec3D(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3D GBB() const { return Vec3D(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3D BRR() const { return Vec3D(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3D BRG() const { return Vec3D(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3D BRB() const { return Vec3D(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3D BGR() const { return Vec3D(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3D BGG() const { return Vec3D(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3D BGB() const { return Vec3D(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3D BBR() const { return Vec3D(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3D BBG() const { return Vec3D(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3D BBB() const { return Vec3D(z, z, z); }
};

[[nodiscard]] HC_INLINE Vec3D operator+(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y, _vLeft.z + _vRight.z); }
[[nodiscard]] HC_INLINE Vec3D operator-(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y, _vLeft.z - _vRight.z); }
[[nodiscard]] HC_INLINE Vec3D operator*(Vec3D _vLeft, double _dRight) { return Vec3D(_vLeft.x * _dRight, _vLeft.y * _dRight, _vLeft.z * _dRight); }
[[nodiscard]] HC_INLINE Vec3D operator*(double _dLeft, Vec3D _vRight) { return Vec3D(_vRight.x * _dLeft, _vRight.y * _dLeft, _vRight.z * _dLeft); }
[[nodiscard]] HC_INLINE Vec3D operator/(Vec3D _vLeft, double _dRight) { return Vec3D(_vLeft.x / _dRight, _vLeft.y / _dRight, _vLeft.z / _dRight); }
[[nodiscard]] HC_INLINE Vec3D operator/(double _dLeft, Vec3D _vRight) { return Vec3D(_dLeft / _vRight.x, _dLeft / _vRight.y, _dLeft / _vRight.z); }
[[nodiscard]] HC_INLINE Vec3D operator*(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y, _vLeft.z * _vRight.z); }
[[nodiscard]] HC_INLINE Vec3D operator/(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(_vLeft.x / _vRight.x, _vLeft.y / _vRight.y, _vLeft.z / _vRight.z); }
HC_INLINE Vec3D& operator+=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3D& operator-=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3D& operator/=(Vec3D& _vLeft, Vec3D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, double _dRight) { _vLeft = _vLeft * _dRight; return _vLeft; }
HC_INLINE Vec3D& operator/=(Vec3D& _vLeft, double _dRight) { _vLeft = _vLeft / _dRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec3D operator~(Vec3D _vVector) { return Vec3D(); }
[[nodiscard]] HC_INLINE Vec3D operator-(Vec3D _vVector) { return Vec3D(-_vVector.x, -_vVector.y, -_vVector.z); }
HC_INLINE bool operator==(Vec3D _vLeft, Vec3D _vRight) { return HC_DOUBLE_COMPARE(_vLeft.x, _vRight.x) && HC_DOUBLE_COMPARE(_vLeft.y, _vRight.y) && HC_DOUBLE_COMPARE(_vLeft.z, _vRight.z); }
HC_INLINE bool operator<(Vec3D _vLeft, Vec3D _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y && _vLeft.z < _vRight.z; }
HC_INLINE bool operator>(Vec3D _vLeft, Vec3D _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y && _vLeft.z > _vRight.z; }
HC_INLINE bool operator<=(Vec3D _vLeft, Vec3D _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(Vec3D _vLeft, Vec3D _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(Vec3D _vLeft, Vec3D _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec3D Min(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(HC_TERNARY(_vLeft.x, _vRight.x, < ), HC_TERNARY(_vLeft.y, _vRight.y, < ), HC_TERNARY(_vLeft.z, _vRight.z, < )); }
[[nodiscard]] HC_INLINE Vec3D Max(Vec3D _vLeft, Vec3D _vRight) { return Vec3D(HC_TERNARY(_vLeft.x, _vRight.x, > ), HC_TERNARY(_vLeft.y, _vRight.y, > ), HC_TERNARY(_vLeft.z, _vRight.z, > )); }
[[nodiscard]] HC_INLINE Vec3D Clamp(Vec3D _vVector, Vec3D _vMin, Vec3D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
[[nodiscard]] HC_INLINE double HorizontalMin(Vec3D _vVector) { _vVector = Min(_vVector, _vVector.YXZ()); return Min(_vVector, _vVector.ZXY()).x; }
[[nodiscard]] HC_INLINE double HorizontalMax(Vec3D _vVector) { _vVector = Max(_vVector, _vVector.YXZ()); return Max(_vVector, _vVector.ZXY()).x; }
[[nodiscard]] HC_INLINE double Sum(const Vec3D _vVector) { return _vVector.x + _vVector.y + _vVector.z; }
[[nodiscard]] HC_INLINE double Dot(Vec3D _vLeft, Vec3D _vRight) { return Sum(_vLeft * _vRight); }
[[nodiscard]] HC_INLINE double Length(Vec3D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE double LengthSquared(Vec3D _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec3D Normalize(Vec3D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
[[nodiscard]] HC_INLINE double AngleBetween(Vec3D _vLeft, Vec3D _vRight) { return acos(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE Vec3D Cross(Vec3D _vLeft, Vec3D _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
[[nodiscard]] HC_INLINE Vec3D Abs(Vec3D _vVector) { return Vec3D(abs(_vVector.x), abs(_vVector.y), abs(_vVector.z)); }

#endif