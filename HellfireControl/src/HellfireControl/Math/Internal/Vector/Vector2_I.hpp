#pragma once

#include <HellfireControl/Math/Internal/Vector/Vector_Common.hpp>

struct HC_ALIGNAS(8) Vec2I
{
	union
	{
		int m_iData[2];
		struct
		{
			int x;
			int y;
		};
	};

	HC_INLINE Vec2I() { m_iData[0] = 0.0f; m_iData[1] = 0.0f; }
	HC_INLINE explicit Vec2I(float _fVal) { m_iData[0] = _fVal; m_iData[1] = _fVal; }
	HC_INLINE explicit Vec2I(int _iVal) { m_iData[0] = static_cast<int>(_iVal); m_iData[1] = static_cast<int>(_iVal); }
	HC_INLINE explicit Vec2I(double _dVal) { m_iData[0] = static_cast<int>(_dVal); m_iData[1] = static_cast<int>(_dVal); }
	HC_INLINE explicit Vec2I(float _fX, float _fY) { m_iData[0] = _fX; m_iData[1] = _fY; }
	HC_INLINE explicit Vec2I(int _iX, int _iY) { m_iData[0] = static_cast<int>(_iX); m_iData[1] = static_cast<int>(_iY); }
	HC_INLINE explicit Vec2I(double _dX, double _dY) { m_iData[0] = static_cast<int>(_dX); m_iData[1] = static_cast<int>(_dY); }

	[[nodiscard]] HC_INLINE int operator[](int _iNdx) const { assert(_iNdx < 2); return m_iData[_iNdx]; }
	[[nodiscard]] HC_INLINE int& operator[](int _iNdx) { assert(_iNdx < 2); return m_iData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2I XX() const { return Vec2I(x, x); }
	[[nodiscard]] HC_INLINE Vec2I YY() const { return Vec2I(y, y); }
	[[nodiscard]] HC_INLINE Vec2I YX() const { return Vec2I(y, x); }
};

[[nodiscard]] HC_INLINE Vec2I operator+(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y); }
[[nodiscard]] HC_INLINE Vec2I operator-(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y); }
[[nodiscard]] HC_INLINE Vec2I operator*(const Vec2I& _vLeft, float _fRight) { return Vec2I(_vLeft.x * _fRight, _vLeft.y * _fRight); }
[[nodiscard]] HC_INLINE Vec2I operator*(float _fLeft, const Vec2I& _vRight) { return Vec2I(_vRight.x * _fLeft, _vRight.y * _fLeft); }
[[nodiscard]] HC_INLINE Vec2I operator/(const Vec2I& _vLeft, float _fRight) { return Vec2I(_vLeft.x / _fRight, _vLeft.y / _fRight); }
[[nodiscard]] HC_INLINE Vec2I operator/(float _fLeft, const Vec2I& _vRight) { return Vec2I(_vRight.x / _fLeft, _vRight.y / _fLeft); }
[[nodiscard]] HC_INLINE Vec2I operator*(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y); }
[[nodiscard]] HC_INLINE Vec2I operator/(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(_vLeft.x / _vRight.x, _vLeft.y / _vRight.y); }
HC_INLINE Vec2I& operator+=(Vec2I& _vLeft, const Vec2I& _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec2I& operator-=(Vec2I& _vLeft, const Vec2I& _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec2I& operator*=(Vec2I& _vLeft, const Vec2I& _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec2I& operator/=(Vec2I& _vLeft, const Vec2I& _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec2I& operator*=(Vec2I& _vLeft, float _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec2I& operator/=(Vec2I& _vLeft, float _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec2I operator~(const Vec2I& _vVector) { return Vec2I(); }
[[nodiscard]] HC_INLINE Vec2I operator-(const Vec2I& _vVector) { return Vec2I(-_vVector.x, -_vVector.y); }
HC_INLINE bool operator==(const Vec2I& _vLeft, const Vec2I& _vRight) { return HC_FLOAT_COMPARE(_vLeft.x, _vRight.x) && HC_FLOAT_COMPARE(_vLeft.y, _vRight.y); }
HC_INLINE bool operator<(const Vec2I& _vLeft, const Vec2I& _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y; }
HC_INLINE bool operator>(const Vec2I& _vLeft, const Vec2I& _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y; }
HC_INLINE bool operator<=(const Vec2I& _vLeft, const Vec2I& _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(const Vec2I& _vLeft, const Vec2I& _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(const Vec2I& _vLeft, const Vec2I& _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec2I Min(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(HC_TERNARY(_vLeft.x, _vRight.x, <), HC_TERNARY(_vLeft.y, _vRight.y, <)); }
[[nodiscard]] HC_INLINE Vec2I Max(const Vec2I& _vLeft, const Vec2I& _vRight) { return Vec2I(HC_TERNARY(_vLeft.x, _vRight.x, >), HC_TERNARY(_vLeft.y, _vRight.y, >)); }
[[nodiscard]] HC_INLINE int Sum(const Vec2I& _vVector) { return _vVector.x + _vVector.y; }
[[nodiscard]] HC_INLINE int Dot(const Vec2I& _vLeft, const Vec2I& _vRight) { return Sum(_vLeft * _vRight); }
[[nodiscard]] HC_INLINE int Length(const Vec2I& _vVector) { return sqrtf(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE int LengthSquared(const Vec2I& _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec2I Normalize(const Vec2I& _vVector) { return _vVector * (1.0f / Length(_vVector)); }
[[nodiscard]] HC_INLINE int AngleBetween(const Vec2I& _vLeft, const Vec2I& _vRight) { return acosf(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE int Cross(const Vec2I& _vLeft, const Vec2I& _vRight) { return _vLeft.x * _vRight.y - _vLeft.y * _vRight.x; }
[[nodiscard]] HC_INLINE Vec2I Abs(const Vec2I& _vVector) { return Vec2I(abs(_vVector.x), abs(_vVector.y)); }