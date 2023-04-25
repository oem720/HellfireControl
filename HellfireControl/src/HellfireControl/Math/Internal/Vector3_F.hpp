#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
#define HC_SHUFFLE3F(_vec, _x, _y, _z) Vec3F(_mm_shuffle_ps((_vec).m_fVec, (_vec).m_fVec, _MM_SHUFFLE(_z, _z, _y, _x)))

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

#else

struct HC_ALIGNAS(16) Vec3F
{
	union
	{
		float m_fData[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	HC_INLINE Vec3F() { m_fData[0] = 0.0f; m_fData[1] = 0.0f; m_fData[2] = 0.0f; }
	HC_INLINE explicit Vec3F(float _fVal) { m_fData[0] = _fVal; m_fData[1] = _fVal; m_fData[2] = _fVal; }
	HC_INLINE explicit Vec3F(int _iVal) { m_fData[0] = static_cast<float>(_iVal); m_fData[1] = static_cast<float>(_iVal); m_fData[2] = static_cast<float>(_iVal); }
	HC_INLINE explicit Vec3F(double _dVal) { m_fData[0] = static_cast<float>(_dVal); m_fData[1] = static_cast<float>(_dVal); m_fData[2] = static_cast<float>(_dVal); }
	HC_INLINE explicit Vec3F(float _fX, float _fY, float _fZ) { m_fData[0] = _fX; m_fData[1] = _fY; m_fData[2] = _fZ; }
	HC_INLINE explicit Vec3F(int _iX, int _iY, int _iZ) { m_fData[0] = static_cast<float>(_iX); m_fData[1] = static_cast<float>(_iY); m_fData[2] = static_cast<float>(_iZ); }
	HC_INLINE explicit Vec3F(double _dX, double _dY, double _dZ) { m_fData[0] = static_cast<float>(_dX); m_fData[1] = static_cast<float>(_dY); m_fData[2] = static_cast<float>(_dZ); }
	HC_INLINE explicit Vec3F(Vec2F _vXY, float _fZ) { m_fData[0] = _vXY.x; m_fData[1] = _vXY.y; m_fData[2] = _fZ; }
	HC_INLINE explicit Vec3F(float _fX, Vec2F _vYZ) { m_fData[0] = _fX; m_fData[1] = _vYZ.x; m_fData[2] = _vYZ.y; }

	[[nodiscard]] HC_INLINE float operator[](int _iNdx) const { assert(_iNdx < 3); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE float& operator[](int _iNdx) { assert(_iNdx < 3); return m_fData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2F XX() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F YY() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F ZZ() const { return Vec2F(z, z); }
	[[nodiscard]] HC_INLINE Vec2F XY() const { return Vec2F(x, y); }
	[[nodiscard]] HC_INLINE Vec2F XZ() const { return Vec2F(x, z); }
	[[nodiscard]] HC_INLINE Vec2F YX() const { return Vec2F(y, x); }
	[[nodiscard]] HC_INLINE Vec2F YZ() const { return Vec2F(y, z); }
	[[nodiscard]] HC_INLINE Vec2F ZX() const { return Vec2F(z, x); }
	[[nodiscard]] HC_INLINE Vec2F ZY() const { return Vec2F(z, y); }
	[[nodiscard]] HC_INLINE Vec2F RR() const { return Vec2F(x, x); }
	[[nodiscard]] HC_INLINE Vec2F GG() const { return Vec2F(y, y); }
	[[nodiscard]] HC_INLINE Vec2F BB() const { return Vec2F(z, z); }
	[[nodiscard]] HC_INLINE Vec2F RG() const { return Vec2F(x, y); }
	[[nodiscard]] HC_INLINE Vec2F RB() const { return Vec2F(x, z); }
	[[nodiscard]] HC_INLINE Vec2F GR() const { return Vec2F(y, x); }
	[[nodiscard]] HC_INLINE Vec2F GB() const { return Vec2F(y, z); }
	[[nodiscard]] HC_INLINE Vec2F BR() const { return Vec2F(z, x); }
	[[nodiscard]] HC_INLINE Vec2F BG() const { return Vec2F(z, y); }
	[[nodiscard]] HC_INLINE Vec3F XXX() const { return Vec3F(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3F XXY() const { return Vec3F(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3F XXZ() const { return Vec3F(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3F XYX() const { return Vec3F(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3F XYY() const { return Vec3F(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3F XZX() const { return Vec3F(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3F XZY() const { return Vec3F(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3F XZZ() const { return Vec3F(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3F YXX() const { return Vec3F(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3F YXY() const { return Vec3F(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3F YXZ() const { return Vec3F(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3F YYX() const { return Vec3F(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3F YYY() const { return Vec3F(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3F YYZ() const { return Vec3F(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3F YZX() const { return Vec3F(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3F YZY() const { return Vec3F(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3F YZZ() const { return Vec3F(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3F ZXX() const { return Vec3F(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3F ZXY() const { return Vec3F(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3F ZXZ() const { return Vec3F(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3F ZYX() const { return Vec3F(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3F ZYY() const { return Vec3F(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3F ZYZ() const { return Vec3F(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3F ZZX() const { return Vec3F(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3F ZZY() const { return Vec3F(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3F ZZZ() const { return Vec3F(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3F RRR() const { return Vec3F(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3F RRG() const { return Vec3F(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3F RRB() const { return Vec3F(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3F RGR() const { return Vec3F(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3F RGG() const { return Vec3F(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3F RBR() const { return Vec3F(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3F RBG() const { return Vec3F(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3F RBB() const { return Vec3F(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3F GRR() const { return Vec3F(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3F GRG() const { return Vec3F(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3F GRB() const { return Vec3F(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3F GGR() const { return Vec3F(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3F GGG() const { return Vec3F(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3F GGB() const { return Vec3F(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3F GBR() const { return Vec3F(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3F GBG() const { return Vec3F(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3F GBB() const { return Vec3F(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3F BRR() const { return Vec3F(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3F BRG() const { return Vec3F(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3F BRB() const { return Vec3F(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3F BGR() const { return Vec3F(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3F BGG() const { return Vec3F(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3F BGB() const { return Vec3F(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3F BBR() const { return Vec3F(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3F BBG() const { return Vec3F(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3F BBB() const { return Vec3F(z, z, z); }
};

[[nodiscard]] HC_INLINE Vec3F operator+(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y, _vLeft.z + _vRight.z); }
[[nodiscard]] HC_INLINE Vec3F operator-(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y, _vLeft.z - _vRight.z); }
[[nodiscard]] HC_INLINE Vec3F operator*(Vec3F _vLeft, float _fRight) { return Vec3F(_vLeft.x * _fRight, _vLeft.y * _fRight, _vLeft.z * _fRight); }
[[nodiscard]] HC_INLINE Vec3F operator*(float _fLeft, Vec3F _vRight) { return Vec3F(_vRight.x * _fLeft, _vRight.y * _fLeft, _vRight.z * _fLeft); }
[[nodiscard]] HC_INLINE Vec3F operator/(Vec3F _vLeft, float _fRight) { return Vec3F(_vLeft.x / _fRight, _vLeft.y / _fRight, _vLeft.z / _fRight); }
[[nodiscard]] HC_INLINE Vec3F operator/(float _fLeft, Vec3F _vRight) { return Vec3F(_vRight.x / _fLeft, _vRight.y / _fLeft, _vRight.z / _fLeft); }
[[nodiscard]] HC_INLINE Vec3F operator*(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y, _vLeft.z * _vRight.z); }
[[nodiscard]] HC_INLINE Vec3F operator/(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(_vLeft.x / _vRight.x, _vLeft.y / _vRight.y, _vLeft.z / _vRight.z); }
HC_INLINE Vec3F& operator+=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec3F& operator-=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec3F& operator/=(Vec3F& _vLeft, Vec3F _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec3F& operator/=(Vec3F& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec3F operator~(Vec3F _vVector) { return Vec3F(); }
[[nodiscard]] HC_INLINE Vec3F operator-(Vec3F _vVector) { return Vec3F(-_vVector.x, -_vVector.y, -_vVector.z); }
HC_INLINE bool operator==(Vec3F _vLeft, Vec3F _vRight) { return HC_FLOAT_COMPARE(_vLeft.x, _vRight.x) && HC_FLOAT_COMPARE(_vLeft.y, _vRight.y) && HC_FLOAT_COMPARE(_vLeft.z, _vRight.z); }
HC_INLINE bool operator<(Vec3F _vLeft, Vec3F _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y && _vLeft.z < _vRight.z; }
HC_INLINE bool operator>(Vec3F _vLeft, Vec3F _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y && _vLeft.z > _vRight.z; }
HC_INLINE bool operator<=(Vec3F _vLeft, Vec3F _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(Vec3F _vLeft, Vec3F _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(Vec3F _vLeft, Vec3F _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec3F Min(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(HC_TERNARY(_vLeft.x, _vRight.x, <), HC_TERNARY(_vLeft.y, _vRight.y, <), HC_TERNARY(_vLeft.z, _vRight.z, <)); }
[[nodiscard]] HC_INLINE Vec3F Max(Vec3F _vLeft, Vec3F _vRight) { return Vec3F(HC_TERNARY(_vLeft.x, _vRight.x, >), HC_TERNARY(_vLeft.y, _vRight.y, >), HC_TERNARY(_vLeft.z, _vRight.z, >)); }
[[nodiscard]] HC_INLINE Vec3F Clamp(Vec3F _vVector, Vec3F _vMin, Vec3F _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
[[nodiscard]] HC_INLINE float HorizontalMin(Vec3F _vVector) { _vVector = Min(_vVector, _vVector.YXZ()); return Min(_vVector, _vVector.ZXY()).x; }
[[nodiscard]] HC_INLINE float HorizontalMax(Vec3F _vVector) { _vVector = Max(_vVector, _vVector.YXZ()); return Max(_vVector, _vVector.ZXY()).x; }
[[nodiscard]] HC_INLINE float Sum(const Vec3F _vVector) { return _vVector.x + _vVector.y + _vVector.z; }
[[nodiscard]] HC_INLINE float Dot(Vec3F _vLeft, Vec3F _vRight) { return Sum(_vLeft * _vRight); }
[[nodiscard]] HC_INLINE float Length(Vec3F _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE float LengthSquared(Vec3F _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec3F Normalize(Vec3F _vVector) { return _vVector * (1.0f / Length(_vVector)); }
[[nodiscard]] HC_INLINE float AngleBetween(Vec3F _vLeft, Vec3F _vRight) { return acosf(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE Vec3F Cross(Vec3F _vLeft, Vec3F _vRight) { return (_vLeft.ZXY() * _vRight - _vLeft * _vRight.ZXY()).ZXY(); }
[[nodiscard]] HC_INLINE Vec3F Abs(Vec3F _vVector) { return Vec3F(abs(_vVector.x), abs(_vVector.y), abs(_vVector.z)); }

#endif