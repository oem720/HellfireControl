
#include <math.h>
#include <cassert>

#include "HCVector.h"

#pragma region FloatingPointVectors

#pragma region Vec2

inline Vec2::Vec2() : x(0.0f), y(0.0f) {}
inline Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}
inline Vec2::Vec2(const Vec2& _other) { (*this) = _other; }

inline Vec2& Vec2::operator=(const Vec2& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
	}
	return *this;
}

inline Vec2& Vec2::operator+=(const Vec2& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec2& Vec2::operator-=(const Vec2& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec2& Vec2::operator*=(const float _scale) {
	*this = *this * _scale;
	return *this;
}

inline float& Vec2::operator[](int _ndx) {
	assert(_ndx < 2);
	return xy[_ndx];
}

inline float Vec2::operator[](int _ndx) const {
	assert(_ndx < 2);
	return xy[_ndx];
}

inline Vec2 Vec2::operator+(const Vec2& _other) const {
	return Vec2(this->x + _other.x, this->y + _other.y);
}

inline Vec2 Vec2::operator-(const Vec2& _other) const {
	return Vec2(this->x - _other.x, this->y - _other.y);
}

inline Vec2 Vec2::operator*(const float _scale) const {
	return Vec2(this->x * _scale, this->y * _scale);
}

inline float Vec2::operator*(const Vec2& _other) const {
	return (this->x * _other.x) + (this->y * _other.y);
}

inline float Vec2::operator&(const Vec2& _other) const {
	return (this->x * _other.y) - (this->y * _other.x);
}

inline Vec2 Vec2::operator~() const {
	return Vec2();
}

inline Vec2 Vec2::operator-() const {
	return Vec2(-this->x, -this->y);
}

inline bool Vec2::operator==(const Vec2& _other) const {
	return this->x == _other.x && this->y == _other.y;
}

inline bool Vec2::operator<(const Vec2& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec2::operator>(const Vec2& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec2::operator<=(const Vec2& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec2::operator>=(const Vec2& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec2::operator!=(const Vec2& _other) const {
	return this->x != _other.x || this->y != _other.y;
}

inline float Vec2::Length() const {
	return sqrtf((*this) * (*this));
}

inline float Vec2::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec2::Normalize() {
	float len = Length();
	if (!len) return;

	this->x /= len;
	this->y /= len;
}

inline Vec2 Vec2::Normalized() const {
	float len = Length();
	if (!len) return Vec2();

	return Vec2(this->x / len, this->x / len);
}

inline float Vec2::AngleBetween(const Vec2& _other) const {
	return acosf(this->Normalized() * _other.Normalized());
}

inline float Vec2::Dot(const Vec2& _other) const {
	return *this * _other;
}

inline float Vec2::Cross(const Vec2& _other) const {
	return *this & _other;
}

inline void Vec2::Add(const Vec2& _other) {
	*this += _other;
}

inline void Vec2::Subtract(const Vec2& _other) {
	*this -= _other;
}

inline void Vec2::Scale(const float _scale) {
	*this *= _scale;
}

inline void Vec2::Zero() {
	*this = ~(*this);
}

inline void Vec2::Negate() {
	*this = -(*this);
}

inline bool Vec2::Equals(const Vec2& _other) const {
	return *this == _other;
}

inline bool Vec2::Less(const Vec2& _other) const {
	return *this < _other;
}

inline bool Vec2::LessThanOrEquals(const Vec2& _other) const {
	return *this <= _other;
}

inline bool Vec2::Greater(const Vec2& _other) const {
	return *this > _other;
}

inline bool Vec2::GreaterThanOrEquals(const Vec2& _other) const {
	return *this >= _other;
}

inline bool Vec2::NotEquals(const Vec2& _other) const {
	return *this != _other;
}

inline float& Vec2::X() { return this->x; }
inline float& Vec2::Y() { return this->y; }
inline float Vec2::X() const { return this->x; }
inline float Vec2::Y() const { return this->y; }

inline Vec2 Vec2::XX() const { return Vec2(this->x, this->x); }
inline Vec2 Vec2::YY() const { return Vec2(this->y, this->y); }
inline Vec2 Vec2::YX() const { return Vec2(this->y, this->x); }
inline Vec2 Vec2::RR() const { return Vec2(this->x, this->x); }
inline Vec2 Vec2::GG() const { return Vec2(this->y, this->y); }
inline Vec2 Vec2::GR() const { return Vec2(this->y, this->x); }

#pragma endregion

#pragma region Vec3

inline Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
inline Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
inline Vec3::Vec3(const Vec2& _xy, float _z) : x(_xy.X()), y(_xy.Y()), z(_z) {}
inline Vec3::Vec3(float _x, const Vec2& _yz) : x(_x), y(_yz.X()), z(_yz.Y()) {}
inline Vec3::Vec3(const Vec3& _other) { *this = _other; }

inline Vec3& Vec3::operator=(const Vec3& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
	}
	return *this;
}

inline Vec3& Vec3::operator+=(const Vec3& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec3& Vec3::operator*=(const float _scale) {
	*this = *this * _scale;
	return *this;
}

inline Vec3& Vec3::operator&=(const Vec3& _other) {
	*this = *this & _other;
	return *this;
}

inline float& Vec3::operator[](int _ndx) {
	assert(_ndx < 3);
	return xyz[_ndx];
}

inline float Vec3::operator[](int _ndx) const {
	assert(_ndx < 3);
	return xyz[_ndx];
}

inline Vec3 Vec3::operator+(const Vec3& _other) const {
	return Vec3(this->x + _other.x, this->y + _other.y, this->z + _other.z);
}

inline Vec3 Vec3::operator-(const Vec3& _other) const {
	return Vec3(this->x - _other.x, this->y - _other.y, this->z - _other.z);
}

inline Vec3 Vec3::operator*(const float _scale) const {
	return Vec3(this->x * _scale, this->y * _scale, this->z * _scale);
}

inline float Vec3::operator*(const Vec3& _other) const {
	return (this->x * _other.x) + (this->y * _other.y) + (this->z * _other.z);
}

inline Vec3 Vec3::operator&(const Vec3& _other) const {
	return Vec3((this->y * _other.z) - (this->z * _other.y), (this->x * _other.z) - (this->z * _other.x), (this->x * _other.y) - (this->y * _other.x));
}

inline Vec3 Vec3::operator~() const {
	return Vec3(0.0f, 0.0f, 0.0f);
}

inline Vec3 Vec3::operator-() const {
	return Vec3(-this->x, -this->y, -this->z);
}

inline bool Vec3::operator==(const Vec3& _other) const {
	return this->x == _other.x && this->y == _other.y && this->z == _other.z;
}

inline bool Vec3::operator<(const Vec3& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec3::operator>(const Vec3& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec3::operator<=(const Vec3& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec3::operator>=(const Vec3& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec3::operator!=(const Vec3& _other) const {
	return this->x != _other.x || this->y != _other.y || this->z != _other.z;
}

inline float Vec3::Length() const {
	return sqrtf((*this) * (*this));
}

inline float Vec3::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec3::Normalize() {
	float len = Length();
	if (!len) return;

	this->x /= len;
	this->y /= len;
	this->z /= len;
}

inline Vec3 Vec3::Normalized() const {
	float len = Length();
	if (!len) return Vec3();

	return Vec3(this->x / len, this->y / len, this->z / len);
}

inline float Vec3::AngleBetween(const Vec3& _other) const {
	return acosf(this->Normalized() * _other.Normalized());
}

inline float Vec3::Dot(const Vec3& _other) const {
	return *this * _other;
}

inline void Vec3::Cross(const Vec3& _other) {
	*this &= _other;
}

inline void Vec3::Add(const Vec3& _other) {
	*this += _other;
}

inline void Vec3::Subtract(const Vec3& _other) {
	*this -= _other;
}

inline void Vec3::Scale(const float _scale) {
	*this *= _scale;
}

inline void Vec3::Negate() {
	*this = -(*this);
}

inline void Vec3::Zero() {
	*this = ~(*this);
}

inline bool Vec3::Equals(const Vec3& _other) const {
	return *this == _other;
}

inline bool Vec3::Less(const Vec3& _other) const {
	return *this < _other;
}

inline bool Vec3::LessThanOrEquals(const Vec3& _other) const {
	return *this <= _other;
}

inline bool Vec3::Greater(const Vec3& _other) const {
	return *this > _other;
}

inline bool Vec3::GreaterThanOrEquals(const Vec3& _other) const {
	return *this >= _other;
}

inline bool Vec3::NotEquals(const Vec3& _other) const {
	return *this != _other;
}

inline float& Vec3::X() { return this->x; }
inline float& Vec3::Y() { return this->y; }
inline float& Vec3::Z() { return this->z; }
inline float Vec3::X() const { return this->x; }
inline float Vec3::Y() const { return this->y; }
inline float Vec3::Z() const { return this->z; }

//Vec2 Swizzle
inline Vec2 Vec3::XX() const { return Vec2(this->x, this->x); }
inline Vec2 Vec3::YY() const { return Vec2(this->y, this->y); }
inline Vec2 Vec3::ZZ() const { return Vec2(this->z, this->z); }
inline Vec2 Vec3::XY() const { return Vec2(this->x, this->y); }
inline Vec2 Vec3::XZ() const { return Vec2(this->x, this->z); }
inline Vec2 Vec3::YX() const { return Vec2(this->y, this->x); }
inline Vec2 Vec3::YZ() const { return Vec2(this->y, this->z); }
inline Vec2 Vec3::ZX() const { return Vec2(this->z, this->x); }
inline Vec2 Vec3::ZY() const { return Vec2(this->z, this->y); }
inline Vec2 Vec3::RR() const { return Vec2(this->x, this->x); }
inline Vec2 Vec3::GG() const { return Vec2(this->y, this->y); }
inline Vec2 Vec3::BB() const { return Vec2(this->z, this->z); }
inline Vec2 Vec3::RG() const { return Vec2(this->x, this->y); }
inline Vec2 Vec3::RB() const { return Vec2(this->x, this->z); }
inline Vec2 Vec3::GR() const { return Vec2(this->y, this->x); }
inline Vec2 Vec3::GB() const { return Vec2(this->y, this->z); }
inline Vec2 Vec3::BR() const { return Vec2(this->z, this->x); }
inline Vec2 Vec3::BG() const { return Vec2(this->z, this->y); }

//Vec3 Swizzle
inline Vec3 Vec3::XXX() const { return Vec3(this->x, this->x, this->x); }
inline Vec3 Vec3::XXY() const { return Vec3(this->x, this->x, this->y); }
inline Vec3 Vec3::XXZ() const { return Vec3(this->x, this->x, this->z); }
inline Vec3 Vec3::XYX() const { return Vec3(this->x, this->y, this->x); }
inline Vec3 Vec3::XYY() const { return Vec3(this->x, this->y, this->y); }
inline Vec3 Vec3::XZX() const { return Vec3(this->x, this->z, this->x); }
inline Vec3 Vec3::XZY() const { return Vec3(this->x, this->z, this->y); }
inline Vec3 Vec3::XZZ() const { return Vec3(this->x, this->z, this->z); }
inline Vec3 Vec3::YXX() const { return Vec3(this->y, this->x, this->x); }
inline Vec3 Vec3::YXY() const { return Vec3(this->y, this->x, this->y); }
inline Vec3 Vec3::YXZ() const { return Vec3(this->y, this->x, this->z); }
inline Vec3 Vec3::YYX() const { return Vec3(this->y, this->y, this->x); }
inline Vec3 Vec3::YYY() const { return Vec3(this->y, this->y, this->y); }
inline Vec3 Vec3::YYZ() const { return Vec3(this->y, this->y, this->z); }
inline Vec3 Vec3::YZX() const { return Vec3(this->y, this->z, this->x); }
inline Vec3 Vec3::YZY() const { return Vec3(this->y, this->z, this->y); }
inline Vec3 Vec3::YZZ() const { return Vec3(this->y, this->z, this->z); }
inline Vec3 Vec3::ZXX() const { return Vec3(this->z, this->x, this->x); }
inline Vec3 Vec3::ZXY() const { return Vec3(this->z, this->x, this->y); }
inline Vec3 Vec3::ZXZ() const { return Vec3(this->z, this->x, this->z); }
inline Vec3 Vec3::ZYX() const { return Vec3(this->z, this->y, this->x); }
inline Vec3 Vec3::ZYY() const { return Vec3(this->z, this->y, this->y); }
inline Vec3 Vec3::ZYZ() const { return Vec3(this->z, this->y, this->z); }
inline Vec3 Vec3::ZZX() const { return Vec3(this->z, this->z, this->x); }
inline Vec3 Vec3::ZZY() const { return Vec3(this->z, this->z, this->y); }
inline Vec3 Vec3::ZZZ() const { return Vec3(this->z, this->z, this->z); }
inline Vec3 Vec3::RRR() const { return Vec3(this->x, this->x, this->x); }
inline Vec3 Vec3::RRG() const { return Vec3(this->x, this->x, this->y); }
inline Vec3 Vec3::RRB() const { return Vec3(this->x, this->x, this->z); }
inline Vec3 Vec3::RGR() const { return Vec3(this->x, this->y, this->x); }
inline Vec3 Vec3::RGG() const { return Vec3(this->x, this->y, this->y); }
inline Vec3 Vec3::RBR() const { return Vec3(this->x, this->z, this->x); }
inline Vec3 Vec3::RBG() const { return Vec3(this->x, this->z, this->y); }
inline Vec3 Vec3::RBB() const { return Vec3(this->x, this->z, this->z); }
inline Vec3 Vec3::GRR() const { return Vec3(this->y, this->x, this->x); }
inline Vec3 Vec3::GRG() const { return Vec3(this->y, this->x, this->y); }
inline Vec3 Vec3::GRB() const { return Vec3(this->y, this->x, this->z); }
inline Vec3 Vec3::GGR() const { return Vec3(this->y, this->y, this->x); }
inline Vec3 Vec3::GGG() const { return Vec3(this->y, this->y, this->y); }
inline Vec3 Vec3::GGB() const { return Vec3(this->y, this->y, this->z); }
inline Vec3 Vec3::GBR() const { return Vec3(this->y, this->z, this->x); }
inline Vec3 Vec3::GBG() const { return Vec3(this->y, this->z, this->y); }
inline Vec3 Vec3::GBB() const { return Vec3(this->y, this->z, this->z); }
inline Vec3 Vec3::BRR() const { return Vec3(this->z, this->x, this->x); }
inline Vec3 Vec3::BRG() const { return Vec3(this->z, this->x, this->y); }
inline Vec3 Vec3::BRB() const { return Vec3(this->z, this->x, this->z); }
inline Vec3 Vec3::BGR() const { return Vec3(this->z, this->y, this->x); }
inline Vec3 Vec3::BGG() const { return Vec3(this->z, this->y, this->y); }
inline Vec3 Vec3::BGB() const { return Vec3(this->z, this->y, this->z); }
inline Vec3 Vec3::BBR() const { return Vec3(this->z, this->z, this->x); }
inline Vec3 Vec3::BBG() const { return Vec3(this->z, this->z, this->y); }
inline Vec3 Vec3::BBB() const { return Vec3(this->z, this->z, this->z); }

#pragma endregion

#pragma region Vec4

inline Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline Vec4::Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
inline Vec4::Vec4(const Vec2& _xy, float _z, float _w) : x(_xy.X()), y(_xy.Y()), z(_z), w(_w) {}
inline Vec4::Vec4(float _x, const Vec2& _yz, float _w) : x(_x), y(_yz.X()), z(_yz.Y()), w(_w) {}
inline Vec4::Vec4(float _x, float _y, const Vec2& _zw) : x(_x), y(_y), z(_zw.X()), w(_zw.Y()) {}
inline Vec4::Vec4(const Vec2& _xy, const Vec2& _zw) : x(_xy.X()), y(_xy.Y()), z(_zw.X()), w(_zw.Y()) {}
inline Vec4::Vec4(const Vec3& _xyz, float _w) : x(_xyz.X()), y(_xyz.Y()), z(_xyz.Z()), w(_w) {}
inline Vec4::Vec4(float _x, const Vec3& _yzw) : x(_x), y(_yzw.X()), z(_yzw.Y()), w(_yzw.Z()) {}
inline Vec4::Vec4(const Vec4& _other) { (*this) = _other; }

inline Vec4& Vec4::operator=(const Vec4& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
		this->w = _other.w;
	}
	return *this;
}

inline Vec4& Vec4::operator+=(const Vec4& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec4& Vec4::operator-=(const Vec4& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec4& Vec4::operator*=(const float _scale) {
	*this = *this * _scale;
	return *this;
}

inline Vec4& Vec4::operator&=(const Vec4& _other) {
	*this = *this & _other;
	return *this;
}

inline float& Vec4::operator[](int _ndx) {
	assert(_ndx < 4);
	return xyzw[_ndx];
}

inline float Vec4::operator[](int _ndx) const {
	assert(_ndx < 4);
	return xyzw[_ndx];
}

inline Vec4 Vec4::operator+(const Vec4& _other) const {
	return Vec4(this->x + _other.x, this->y + _other.y, this->z + _other.z, this->w + _other.w);
}

inline Vec4 Vec4::operator-(const Vec4& _other) const {
	return Vec4(this->x - _other.x, this->y - _other.y, this->z - _other.z, this->w - _other.w);
}

inline Vec4 Vec4::operator*(const float _scale) const {
	return Vec4(this->x * _scale, this->y * _scale, this->z * _scale, this->w * _scale);
}

inline float Vec4::operator*(const Vec4& _other) const {
	return (this->x * _other.x) + (this->y * _other.y) + (this->z * _other.z);
}

inline Vec4 Vec4::operator&(const Vec4& _other) const {
	return Vec4((this->y * _other.z) - (this->z * _other.y), (this->x * _other.z) - (this->z * _other.x), (this->x * _other.y) - (this->y * _other.x), 0.0f);
}

inline Vec4 Vec4::operator~() const {
	return Vec4();
}

inline Vec4 Vec4::operator-() const {
	return Vec4(-this->x, -this->y, -this->z, -this->w);
}

inline bool Vec4::operator==(const Vec4& _other) const {
	return this->x == _other.x && this->y == _other.y && this->z == _other.z && this->w == _other.w;
}

inline bool Vec4::operator<(const Vec4& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec4::operator>(const Vec4& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec4::operator<=(const Vec4& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec4::operator>=(const Vec4& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec4::operator!=(const Vec4& _other) const {
	return this->x != _other.x || this->y != _other.y || this->z != _other.z || this->w != _other.w;
}

inline float Vec4::Length() const {
	return sqrtf((*this) * (*this));
}

inline float Vec4::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec4::Normalize() {
	float len = this->Length();
	if (len == 0.0f) return;

	this->x /= len;
	this->y /= len;
	this->z /= len;
	this->w /= len;
}

inline Vec4 Vec4::Normalized() const {
	float len = this->Length();
	if (len == 0.0f) return Vec4();

	return Vec4(this->x / len, this->y / len, this->z / len, this->w / len);
}

inline float Vec4::AngleBetween(const Vec4& _other) const {
	return acosf(*this * _other);
}

inline float Vec4::Dot(const Vec4& _other) const {
	return *this * _other;
}

inline void Vec4::Cross(const Vec4& _other) {
	*this &= _other;
}

inline void Vec4::Add(const Vec4& _other) {
	*this += _other;
}

inline void Vec4::Subtract(const Vec4& _other) {
	*this -= _other;
}

inline void Vec4::Scale(const float _scale) {
	*this *= _scale;
}

inline void Vec4::Negate() {
	*this = -(*this);
}

inline void Vec4::Zero() {
	*this = ~(*this);
}

inline bool Vec4::Equals(const Vec4& _other) const {
	return *this == _other;
}

inline bool Vec4::Less(const Vec4& _other) const {
	return *this < _other;
}

inline bool Vec4::LessThanOrEquals(const Vec4& _other) const {
	return *this <= _other;
}

inline bool Vec4::Greater(const Vec4& _other) const {
	return *this > _other;
}

inline bool Vec4::GreaterThanOrEquals(const Vec4& _other) const {
	return *this >= _other;
}

inline bool Vec4::NotEquals(const Vec4& _other) const {
	return *this != _other;
}

inline float& Vec4::X() { return this->x; }
inline float& Vec4::Y() { return this->y; }
inline float& Vec4::Z() { return this->z; }
inline float& Vec4::W() { return this->w; }
inline float Vec4::X() const { return this->x; }
inline float Vec4::Y() const { return this->y; }
inline float Vec4::Z() const { return this->z; }
inline float Vec4::W() const { return this->w; }

//Vec2 Swizzle
inline Vec2 Vec4::XX() const { return Vec2(this->x, this->x); }
inline Vec2 Vec4::YY() const { return Vec2(this->y, this->y); }
inline Vec2 Vec4::ZZ() const { return Vec2(this->z, this->z); }
inline Vec2 Vec4::WW() const { return Vec2(this->w, this->w); }
inline Vec2 Vec4::XY() const { return Vec2(this->x, this->y); }
inline Vec2 Vec4::XZ() const { return Vec2(this->x, this->z); }
inline Vec2 Vec4::XW() const { return Vec2(this->x, this->w); }
inline Vec2 Vec4::YX() const { return Vec2(this->y, this->x); }
inline Vec2 Vec4::YZ() const { return Vec2(this->y, this->z); }
inline Vec2 Vec4::YW() const { return Vec2(this->y, this->w); }
inline Vec2 Vec4::ZX() const { return Vec2(this->z, this->x); }
inline Vec2 Vec4::ZY() const { return Vec2(this->z, this->y); }
inline Vec2 Vec4::ZW() const { return Vec2(this->z, this->w); }
inline Vec2 Vec4::WX() const { return Vec2(this->w, this->x); }
inline Vec2 Vec4::WY() const { return Vec2(this->w, this->y); }
inline Vec2 Vec4::WZ() const { return Vec2(this->w, this->z); }
inline Vec2 Vec4::RR() const { return Vec2(this->x, this->x); }
inline Vec2 Vec4::GG() const { return Vec2(this->y, this->y); }
inline Vec2 Vec4::BB() const { return Vec2(this->z, this->z); }
inline Vec2 Vec4::AA() const { return Vec2(this->w, this->w); }
inline Vec2 Vec4::RG() const { return Vec2(this->x, this->y); }
inline Vec2 Vec4::RB() const { return Vec2(this->x, this->z); }
inline Vec2 Vec4::RA() const { return Vec2(this->x, this->w); }
inline Vec2 Vec4::GR() const { return Vec2(this->y, this->x); }
inline Vec2 Vec4::GB() const { return Vec2(this->y, this->z); }
inline Vec2 Vec4::GA() const { return Vec2(this->y, this->w); }
inline Vec2 Vec4::BR() const { return Vec2(this->z, this->x); }
inline Vec2 Vec4::BG() const { return Vec2(this->z, this->y); }
inline Vec2 Vec4::BA() const { return Vec2(this->z, this->w); }
inline Vec2 Vec4::AR() const { return Vec2(this->w, this->x); }
inline Vec2 Vec4::AG() const { return Vec2(this->w, this->y); }
inline Vec2 Vec4::AB() const { return Vec2(this->w, this->z); }

//Vec3 Swizzle
inline Vec3 Vec4::XXX() const { return Vec3(this->x, this->x, this->x); }
inline Vec3 Vec4::XXY() const { return Vec3(this->x, this->x, this->y); }
inline Vec3 Vec4::XXZ() const { return Vec3(this->x, this->x, this->z); }
inline Vec3 Vec4::XXW() const { return Vec3(this->x, this->x, this->w); }
inline Vec3 Vec4::XYX() const { return Vec3(this->x, this->y, this->x); }
inline Vec3 Vec4::XYY() const { return Vec3(this->x, this->y, this->y); }
inline Vec3 Vec4::XYZ() const { return Vec3(this->x, this->y, this->z); }
inline Vec3 Vec4::XYW() const { return Vec3(this->x, this->y, this->w); }
inline Vec3 Vec4::XZX() const { return Vec3(this->x, this->z, this->x); }
inline Vec3 Vec4::XZY() const { return Vec3(this->x, this->z, this->y); }
inline Vec3 Vec4::XZZ() const { return Vec3(this->x, this->z, this->z); }
inline Vec3 Vec4::XZW() const { return Vec3(this->x, this->z, this->w); }
inline Vec3 Vec4::XWX() const { return Vec3(this->x, this->w, this->x); }
inline Vec3 Vec4::XWY() const { return Vec3(this->x, this->w, this->y); }
inline Vec3 Vec4::XWZ() const { return Vec3(this->x, this->w, this->z); }
inline Vec3 Vec4::XWW() const { return Vec3(this->x, this->w, this->w); }
inline Vec3 Vec4::YXX() const { return Vec3(this->y, this->x, this->x); }
inline Vec3 Vec4::YXY() const { return Vec3(this->y, this->x, this->y); }
inline Vec3 Vec4::YXZ() const { return Vec3(this->y, this->x, this->z); }
inline Vec3 Vec4::YXW() const { return Vec3(this->y, this->x, this->w); }
inline Vec3 Vec4::YYX() const { return Vec3(this->y, this->y, this->x); }
inline Vec3 Vec4::YYY() const { return Vec3(this->y, this->y, this->y); }
inline Vec3 Vec4::YYZ() const { return Vec3(this->y, this->y, this->z); }
inline Vec3 Vec4::YYW() const { return Vec3(this->y, this->y, this->w); }
inline Vec3 Vec4::YZX() const { return Vec3(this->y, this->z, this->x); }
inline Vec3 Vec4::YZY() const { return Vec3(this->y, this->z, this->y); }
inline Vec3 Vec4::YZZ() const { return Vec3(this->y, this->z, this->z); }
inline Vec3 Vec4::YZW() const { return Vec3(this->y, this->z, this->w); }
inline Vec3 Vec4::YWX() const { return Vec3(this->y, this->w, this->x); }
inline Vec3 Vec4::YWY() const { return Vec3(this->y, this->w, this->y); }
inline Vec3 Vec4::YWZ() const { return Vec3(this->y, this->w, this->z); }
inline Vec3 Vec4::YWW() const { return Vec3(this->y, this->w, this->w); }
inline Vec3 Vec4::ZXX() const { return Vec3(this->z, this->x, this->x); }
inline Vec3 Vec4::ZXY() const { return Vec3(this->z, this->x, this->y); }
inline Vec3 Vec4::ZXZ() const { return Vec3(this->z, this->x, this->z); }
inline Vec3 Vec4::ZXW() const { return Vec3(this->z, this->x, this->w); }
inline Vec3 Vec4::ZYX() const { return Vec3(this->z, this->y, this->x); }
inline Vec3 Vec4::ZYY() const { return Vec3(this->z, this->y, this->y); }
inline Vec3 Vec4::ZYZ() const { return Vec3(this->z, this->y, this->z); }
inline Vec3 Vec4::ZYW() const { return Vec3(this->z, this->y, this->w); }
inline Vec3 Vec4::ZZX() const { return Vec3(this->z, this->z, this->x); }
inline Vec3 Vec4::ZZY() const { return Vec3(this->z, this->z, this->y); }
inline Vec3 Vec4::ZZZ() const { return Vec3(this->z, this->z, this->z); }
inline Vec3 Vec4::ZZW() const { return Vec3(this->z, this->z, this->w); }
inline Vec3 Vec4::ZWX() const { return Vec3(this->z, this->w, this->x); }
inline Vec3 Vec4::ZWY() const { return Vec3(this->z, this->w, this->y); }
inline Vec3 Vec4::ZWZ() const { return Vec3(this->z, this->w, this->z); }
inline Vec3 Vec4::ZWW() const { return Vec3(this->z, this->w, this->w); }
inline Vec3 Vec4::WXX() const { return Vec3(this->w, this->x, this->x); }
inline Vec3 Vec4::WXY() const { return Vec3(this->w, this->x, this->y); }
inline Vec3 Vec4::WXZ() const { return Vec3(this->w, this->x, this->z); }
inline Vec3 Vec4::WXW() const { return Vec3(this->w, this->x, this->w); }
inline Vec3 Vec4::WYX() const { return Vec3(this->w, this->y, this->x); }
inline Vec3 Vec4::WYY() const { return Vec3(this->w, this->y, this->y); }
inline Vec3 Vec4::WYZ() const { return Vec3(this->w, this->y, this->z); }
inline Vec3 Vec4::WYW() const { return Vec3(this->w, this->y, this->w); }
inline Vec3 Vec4::WZX() const { return Vec3(this->w, this->z, this->x); }
inline Vec3 Vec4::WZY() const { return Vec3(this->w, this->z, this->y); }
inline Vec3 Vec4::WZZ() const { return Vec3(this->w, this->z, this->z); }
inline Vec3 Vec4::WZW() const { return Vec3(this->w, this->z, this->w); }
inline Vec3 Vec4::WWX() const { return Vec3(this->w, this->w, this->x); }
inline Vec3 Vec4::WWY() const { return Vec3(this->w, this->w, this->y); }
inline Vec3 Vec4::WWZ() const { return Vec3(this->w, this->w, this->z); }
inline Vec3 Vec4::WWW() const { return Vec3(this->w, this->w, this->w); }
inline Vec3 Vec4::RRR() const { return Vec3(this->x, this->x, this->x); }
inline Vec3 Vec4::RRG() const { return Vec3(this->x, this->x, this->y); }
inline Vec3 Vec4::RRB() const { return Vec3(this->x, this->x, this->z); }
inline Vec3 Vec4::RRA() const { return Vec3(this->x, this->x, this->w); }
inline Vec3 Vec4::RGR() const { return Vec3(this->x, this->y, this->x); }
inline Vec3 Vec4::RGG() const { return Vec3(this->x, this->y, this->y); }
inline Vec3 Vec4::RGA() const { return Vec3(this->x, this->y, this->w); }
inline Vec3 Vec4::RGB() const { return Vec3(this->x, this->y, this->z); }
inline Vec3 Vec4::RBR() const { return Vec3(this->x, this->z, this->x); }
inline Vec3 Vec4::RBG() const { return Vec3(this->x, this->z, this->y); }
inline Vec3 Vec4::RBB() const { return Vec3(this->x, this->z, this->z); }
inline Vec3 Vec4::RBA() const { return Vec3(this->x, this->z, this->w); }
inline Vec3 Vec4::RAR() const { return Vec3(this->x, this->w, this->x); }
inline Vec3 Vec4::RAG() const { return Vec3(this->x, this->w, this->y); }
inline Vec3 Vec4::RAB() const { return Vec3(this->x, this->w, this->z); }
inline Vec3 Vec4::RAA() const { return Vec3(this->x, this->w, this->w); }
inline Vec3 Vec4::GRR() const { return Vec3(this->y, this->x, this->x); }
inline Vec3 Vec4::GRG() const { return Vec3(this->y, this->x, this->y); }
inline Vec3 Vec4::GRB() const { return Vec3(this->y, this->x, this->z); }
inline Vec3 Vec4::GRA() const { return Vec3(this->y, this->x, this->w); }
inline Vec3 Vec4::GGR() const { return Vec3(this->y, this->y, this->x); }
inline Vec3 Vec4::GGG() const { return Vec3(this->y, this->y, this->y); }
inline Vec3 Vec4::GGB() const { return Vec3(this->y, this->y, this->z); }
inline Vec3 Vec4::GGA() const { return Vec3(this->y, this->y, this->w); }
inline Vec3 Vec4::GBR() const { return Vec3(this->y, this->z, this->x); }
inline Vec3 Vec4::GBG() const { return Vec3(this->y, this->z, this->y); }
inline Vec3 Vec4::GBB() const { return Vec3(this->y, this->z, this->z); }
inline Vec3 Vec4::GBA() const { return Vec3(this->y, this->z, this->w); }
inline Vec3 Vec4::GAR() const { return Vec3(this->y, this->w, this->x); }
inline Vec3 Vec4::GAG() const { return Vec3(this->y, this->w, this->y); }
inline Vec3 Vec4::GAB() const { return Vec3(this->y, this->w, this->z); }
inline Vec3 Vec4::GAA() const { return Vec3(this->y, this->w, this->w); }
inline Vec3 Vec4::BRR() const { return Vec3(this->z, this->x, this->x); }
inline Vec3 Vec4::BRG() const { return Vec3(this->z, this->x, this->y); }
inline Vec3 Vec4::BRB() const { return Vec3(this->z, this->x, this->z); }
inline Vec3 Vec4::BRA() const { return Vec3(this->z, this->x, this->w); }
inline Vec3 Vec4::BGR() const { return Vec3(this->z, this->y, this->x); }
inline Vec3 Vec4::BGG() const { return Vec3(this->z, this->y, this->y); }
inline Vec3 Vec4::BGB() const { return Vec3(this->z, this->y, this->z); }
inline Vec3 Vec4::BGA() const { return Vec3(this->z, this->y, this->w); }
inline Vec3 Vec4::BBR() const { return Vec3(this->z, this->z, this->x); }
inline Vec3 Vec4::BBG() const { return Vec3(this->z, this->z, this->y); }
inline Vec3 Vec4::BBB() const { return Vec3(this->z, this->z, this->z); }
inline Vec3 Vec4::BBA() const { return Vec3(this->z, this->z, this->w); }
inline Vec3 Vec4::BAR() const { return Vec3(this->z, this->w, this->x); }
inline Vec3 Vec4::BAG() const { return Vec3(this->z, this->w, this->y); }
inline Vec3 Vec4::BAB() const { return Vec3(this->z, this->w, this->z); }
inline Vec3 Vec4::BAA() const { return Vec3(this->z, this->w, this->w); }
inline Vec3 Vec4::ARR() const { return Vec3(this->w, this->x, this->x); }
inline Vec3 Vec4::ARG() const { return Vec3(this->w, this->x, this->y); }
inline Vec3 Vec4::ARB() const { return Vec3(this->w, this->x, this->z); }
inline Vec3 Vec4::ARA() const { return Vec3(this->w, this->x, this->w); }
inline Vec3 Vec4::AGR() const { return Vec3(this->w, this->y, this->x); }
inline Vec3 Vec4::AGG() const { return Vec3(this->w, this->y, this->y); }
inline Vec3 Vec4::AGB() const { return Vec3(this->w, this->y, this->z); }
inline Vec3 Vec4::AGA() const { return Vec3(this->w, this->y, this->w); }
inline Vec3 Vec4::ABR() const { return Vec3(this->w, this->z, this->x); }
inline Vec3 Vec4::ABG() const { return Vec3(this->w, this->z, this->y); }
inline Vec3 Vec4::ABB() const { return Vec3(this->w, this->z, this->z); }
inline Vec3 Vec4::ABA() const { return Vec3(this->w, this->z, this->w); }
inline Vec3 Vec4::AAR() const { return Vec3(this->w, this->w, this->x); }
inline Vec3 Vec4::AAG() const { return Vec3(this->w, this->w, this->y); }
inline Vec3 Vec4::AAB() const { return Vec3(this->w, this->w, this->z); }
inline Vec3 Vec4::AAA() const { return Vec3(this->w, this->w, this->w); }

//Vec4 Swizzle
inline Vec4 Vec4::XXXX() const { return Vec4(this->x, this->x, this->x, this->x); }
inline Vec4 Vec4::XXXY() const { return Vec4(this->x, this->x, this->x, this->y); }
inline Vec4 Vec4::XXXZ() const { return Vec4(this->x, this->x, this->x, this->z); }
inline Vec4 Vec4::XXXW() const { return Vec4(this->x, this->x, this->x, this->w); }
inline Vec4 Vec4::XXYX() const { return Vec4(this->x, this->x, this->y, this->x); }
inline Vec4 Vec4::XXYY() const { return Vec4(this->x, this->x, this->y, this->y); }
inline Vec4 Vec4::XXYZ() const { return Vec4(this->x, this->x, this->y, this->z); }
inline Vec4 Vec4::XXYW() const { return Vec4(this->x, this->x, this->y, this->w); }
inline Vec4 Vec4::XXZX() const { return Vec4(this->x, this->x, this->z, this->x); }
inline Vec4 Vec4::XXZY() const { return Vec4(this->x, this->x, this->z, this->y); }
inline Vec4 Vec4::XXZZ() const { return Vec4(this->x, this->x, this->z, this->z); }
inline Vec4 Vec4::XXZW() const { return Vec4(this->x, this->x, this->z, this->w); }
inline Vec4 Vec4::XXWX() const { return Vec4(this->x, this->x, this->w, this->x); }
inline Vec4 Vec4::XXWY() const { return Vec4(this->x, this->x, this->w, this->y); }
inline Vec4 Vec4::XXWZ() const { return Vec4(this->x, this->x, this->w, this->z); }
inline Vec4 Vec4::XXWW() const { return Vec4(this->x, this->x, this->w, this->w); }
inline Vec4 Vec4::XYXX() const { return Vec4(this->x, this->y, this->x, this->x); }
inline Vec4 Vec4::XYXY() const { return Vec4(this->x, this->y, this->x, this->y); }
inline Vec4 Vec4::XYXZ() const { return Vec4(this->x, this->y, this->x, this->z); }
inline Vec4 Vec4::XYXW() const { return Vec4(this->x, this->y, this->x, this->w); }
inline Vec4 Vec4::XYYX() const { return Vec4(this->x, this->y, this->y, this->x); }
inline Vec4 Vec4::XYYY() const { return Vec4(this->x, this->y, this->y, this->y); }
inline Vec4 Vec4::XYYZ() const { return Vec4(this->x, this->y, this->y, this->z); }
inline Vec4 Vec4::XYYW() const { return Vec4(this->x, this->y, this->y, this->w); }
inline Vec4 Vec4::XYZX() const { return Vec4(this->x, this->y, this->z, this->x); }
inline Vec4 Vec4::XYZY() const { return Vec4(this->x, this->y, this->z, this->y); }
inline Vec4 Vec4::XYZZ() const { return Vec4(this->x, this->y, this->z, this->z); }
inline Vec4 Vec4::XYWX() const { return Vec4(this->x, this->y, this->w, this->x); }
inline Vec4 Vec4::XYWY() const { return Vec4(this->x, this->y, this->w, this->y); }
inline Vec4 Vec4::XYWZ() const { return Vec4(this->x, this->y, this->w, this->z); }
inline Vec4 Vec4::XYWW() const { return Vec4(this->x, this->y, this->w, this->w); }
inline Vec4 Vec4::XZXX() const { return Vec4(this->x, this->z, this->x, this->x); }
inline Vec4 Vec4::XZXY() const { return Vec4(this->x, this->z, this->x, this->y); }
inline Vec4 Vec4::XZXZ() const { return Vec4(this->x, this->z, this->x, this->z); }
inline Vec4 Vec4::XZXW() const { return Vec4(this->x, this->z, this->x, this->w); }
inline Vec4 Vec4::XZYX() const { return Vec4(this->x, this->z, this->y, this->x); }
inline Vec4 Vec4::XZYY() const { return Vec4(this->x, this->z, this->y, this->y); }
inline Vec4 Vec4::XZYZ() const { return Vec4(this->x, this->z, this->y, this->z); }
inline Vec4 Vec4::XZYW() const { return Vec4(this->x, this->z, this->y, this->w); }
inline Vec4 Vec4::XZZX() const { return Vec4(this->x, this->z, this->z, this->x); }
inline Vec4 Vec4::XZZY() const { return Vec4(this->x, this->z, this->z, this->y); }
inline Vec4 Vec4::XZZZ() const { return Vec4(this->x, this->z, this->z, this->z); }
inline Vec4 Vec4::XZZW() const { return Vec4(this->x, this->z, this->z, this->w); }
inline Vec4 Vec4::XZWX() const { return Vec4(this->x, this->z, this->w, this->x); }
inline Vec4 Vec4::XZWY() const { return Vec4(this->x, this->z, this->w, this->y); }
inline Vec4 Vec4::XZWZ() const { return Vec4(this->x, this->z, this->w, this->z); }
inline Vec4 Vec4::XZWW() const { return Vec4(this->x, this->z, this->w, this->w); }
inline Vec4 Vec4::XWXX() const { return Vec4(this->x, this->w, this->x, this->x); }
inline Vec4 Vec4::XWXY() const { return Vec4(this->x, this->w, this->x, this->y); }
inline Vec4 Vec4::XWXZ() const { return Vec4(this->x, this->w, this->x, this->z); }
inline Vec4 Vec4::XWXW() const { return Vec4(this->x, this->w, this->x, this->w); }
inline Vec4 Vec4::XWYX() const { return Vec4(this->x, this->w, this->y, this->x); }
inline Vec4 Vec4::XWYY() const { return Vec4(this->x, this->w, this->y, this->y); }
inline Vec4 Vec4::XWYZ() const { return Vec4(this->x, this->w, this->y, this->z); }
inline Vec4 Vec4::XWYW() const { return Vec4(this->x, this->w, this->y, this->w); }
inline Vec4 Vec4::XWZX() const { return Vec4(this->x, this->w, this->z, this->x); }
inline Vec4 Vec4::XWZY() const { return Vec4(this->x, this->w, this->z, this->y); }
inline Vec4 Vec4::XWZZ() const { return Vec4(this->x, this->w, this->z, this->z); }
inline Vec4 Vec4::XWZW() const { return Vec4(this->x, this->w, this->z, this->w); }
inline Vec4 Vec4::XWWX() const { return Vec4(this->x, this->w, this->w, this->x); }
inline Vec4 Vec4::XWWY() const { return Vec4(this->x, this->w, this->w, this->y); }
inline Vec4 Vec4::XWWZ() const { return Vec4(this->x, this->w, this->w, this->z); }
inline Vec4 Vec4::XWWW() const { return Vec4(this->x, this->w, this->w, this->w); }
inline Vec4 Vec4::YXXX() const { return Vec4(this->y, this->x, this->x, this->x); }
inline Vec4 Vec4::YXXY() const { return Vec4(this->y, this->x, this->x, this->y); }
inline Vec4 Vec4::YXXZ() const { return Vec4(this->y, this->x, this->x, this->z); }
inline Vec4 Vec4::YXXW() const { return Vec4(this->y, this->x, this->x, this->w); }
inline Vec4 Vec4::YXYX() const { return Vec4(this->y, this->x, this->y, this->x); }
inline Vec4 Vec4::YXYY() const { return Vec4(this->y, this->x, this->y, this->y); }
inline Vec4 Vec4::YXYZ() const { return Vec4(this->y, this->x, this->y, this->z); }
inline Vec4 Vec4::YXYW() const { return Vec4(this->y, this->x, this->y, this->w); }
inline Vec4 Vec4::YXZX() const { return Vec4(this->y, this->x, this->z, this->x); }
inline Vec4 Vec4::YXZY() const { return Vec4(this->y, this->x, this->z, this->y); }
inline Vec4 Vec4::YXZZ() const { return Vec4(this->y, this->x, this->z, this->z); }
inline Vec4 Vec4::YXZW() const { return Vec4(this->y, this->x, this->z, this->w); }
inline Vec4 Vec4::YXWX() const { return Vec4(this->y, this->x, this->w, this->x); }
inline Vec4 Vec4::YXWY() const { return Vec4(this->y, this->x, this->w, this->y); }
inline Vec4 Vec4::YXWZ() const { return Vec4(this->y, this->x, this->w, this->z); }
inline Vec4 Vec4::YXWW() const { return Vec4(this->y, this->x, this->w, this->w); }
inline Vec4 Vec4::YYXX() const { return Vec4(this->y, this->y, this->x, this->x); }
inline Vec4 Vec4::YYXY() const { return Vec4(this->y, this->y, this->x, this->y); }
inline Vec4 Vec4::YYXZ() const { return Vec4(this->y, this->y, this->x, this->z); }
inline Vec4 Vec4::YYXW() const { return Vec4(this->y, this->y, this->x, this->w); }
inline Vec4 Vec4::YYYX() const { return Vec4(this->y, this->y, this->y, this->x); }
inline Vec4 Vec4::YYYY() const { return Vec4(this->y, this->y, this->y, this->y); }
inline Vec4 Vec4::YYYZ() const { return Vec4(this->y, this->y, this->y, this->z); }
inline Vec4 Vec4::YYYW() const { return Vec4(this->y, this->y, this->y, this->w); }
inline Vec4 Vec4::YYZX() const { return Vec4(this->y, this->y, this->z, this->x); }
inline Vec4 Vec4::YYZY() const { return Vec4(this->y, this->y, this->z, this->y); }
inline Vec4 Vec4::YYZZ() const { return Vec4(this->y, this->y, this->z, this->z); }
inline Vec4 Vec4::YYZW() const { return Vec4(this->y, this->y, this->z, this->w); }
inline Vec4 Vec4::YYWX() const { return Vec4(this->y, this->y, this->w, this->x); }
inline Vec4 Vec4::YYWY() const { return Vec4(this->y, this->y, this->w, this->y); }
inline Vec4 Vec4::YYWZ() const { return Vec4(this->y, this->y, this->w, this->z); }
inline Vec4 Vec4::YYWW() const { return Vec4(this->y, this->y, this->w, this->w); }
inline Vec4 Vec4::YZXX() const { return Vec4(this->y, this->z, this->x, this->x); }
inline Vec4 Vec4::YZXY() const { return Vec4(this->y, this->z, this->x, this->y); }
inline Vec4 Vec4::YZXZ() const { return Vec4(this->y, this->z, this->x, this->z); }
inline Vec4 Vec4::YZXW() const { return Vec4(this->y, this->z, this->x, this->w); }
inline Vec4 Vec4::YZYX() const { return Vec4(this->y, this->z, this->y, this->x); }
inline Vec4 Vec4::YZYY() const { return Vec4(this->y, this->z, this->y, this->y); }
inline Vec4 Vec4::YZYZ() const { return Vec4(this->y, this->z, this->y, this->z); }
inline Vec4 Vec4::YZYW() const { return Vec4(this->y, this->z, this->y, this->w); }
inline Vec4 Vec4::YZZX() const { return Vec4(this->y, this->z, this->z, this->x); }
inline Vec4 Vec4::YZZY() const { return Vec4(this->y, this->z, this->z, this->y); }
inline Vec4 Vec4::YZZZ() const { return Vec4(this->y, this->z, this->z, this->z); }
inline Vec4 Vec4::YZZW() const { return Vec4(this->y, this->z, this->z, this->w); }
inline Vec4 Vec4::YZWX() const { return Vec4(this->y, this->z, this->w, this->x); }
inline Vec4 Vec4::YZWY() const { return Vec4(this->y, this->z, this->w, this->y); }
inline Vec4 Vec4::YZWZ() const { return Vec4(this->y, this->z, this->w, this->z); }
inline Vec4 Vec4::YZWW() const { return Vec4(this->y, this->z, this->w, this->w); }
inline Vec4 Vec4::YWXX() const { return Vec4(this->y, this->w, this->x, this->x); }
inline Vec4 Vec4::YWXY() const { return Vec4(this->y, this->w, this->x, this->y); }
inline Vec4 Vec4::YWXZ() const { return Vec4(this->y, this->w, this->x, this->z); }
inline Vec4 Vec4::YWXW() const { return Vec4(this->y, this->w, this->x, this->w); }
inline Vec4 Vec4::YWYX() const { return Vec4(this->y, this->w, this->y, this->x); }
inline Vec4 Vec4::YWYY() const { return Vec4(this->y, this->w, this->y, this->y); }
inline Vec4 Vec4::YWYZ() const { return Vec4(this->y, this->w, this->y, this->z); }
inline Vec4 Vec4::YWYW() const { return Vec4(this->y, this->w, this->y, this->w); }
inline Vec4 Vec4::YWZX() const { return Vec4(this->y, this->w, this->z, this->x); }
inline Vec4 Vec4::YWZY() const { return Vec4(this->y, this->w, this->z, this->y); }
inline Vec4 Vec4::YWZZ() const { return Vec4(this->y, this->w, this->z, this->z); }
inline Vec4 Vec4::YWZW() const { return Vec4(this->y, this->w, this->z, this->w); }
inline Vec4 Vec4::YWWX() const { return Vec4(this->y, this->w, this->w, this->x); }
inline Vec4 Vec4::YWWY() const { return Vec4(this->y, this->w, this->w, this->y); }
inline Vec4 Vec4::YWWZ() const { return Vec4(this->y, this->w, this->w, this->z); }
inline Vec4 Vec4::YWWW() const { return Vec4(this->y, this->w, this->w, this->w); }
inline Vec4 Vec4::ZXXX() const { return Vec4(this->z, this->x, this->x, this->x); }
inline Vec4 Vec4::ZXXY() const { return Vec4(this->z, this->x, this->x, this->y); }
inline Vec4 Vec4::ZXXZ() const { return Vec4(this->z, this->x, this->x, this->z); }
inline Vec4 Vec4::ZXXW() const { return Vec4(this->z, this->x, this->x, this->w); }
inline Vec4 Vec4::ZXYX() const { return Vec4(this->z, this->x, this->y, this->x); }
inline Vec4 Vec4::ZXYY() const { return Vec4(this->z, this->x, this->y, this->y); }
inline Vec4 Vec4::ZXYZ() const { return Vec4(this->z, this->x, this->y, this->z); }
inline Vec4 Vec4::ZXYW() const { return Vec4(this->z, this->x, this->y, this->w); }
inline Vec4 Vec4::ZXZX() const { return Vec4(this->z, this->x, this->z, this->x); }
inline Vec4 Vec4::ZXZY() const { return Vec4(this->z, this->x, this->z, this->y); }
inline Vec4 Vec4::ZXZZ() const { return Vec4(this->z, this->x, this->z, this->z); }
inline Vec4 Vec4::ZXZW() const { return Vec4(this->z, this->x, this->z, this->w); }
inline Vec4 Vec4::ZXWX() const { return Vec4(this->z, this->x, this->w, this->x); }
inline Vec4 Vec4::ZXWY() const { return Vec4(this->z, this->x, this->w, this->y); }
inline Vec4 Vec4::ZXWZ() const { return Vec4(this->z, this->x, this->w, this->z); }
inline Vec4 Vec4::ZXWW() const { return Vec4(this->z, this->x, this->w, this->w); }
inline Vec4 Vec4::ZYXX() const { return Vec4(this->z, this->y, this->x, this->x); }
inline Vec4 Vec4::ZYXY() const { return Vec4(this->z, this->y, this->x, this->y); }
inline Vec4 Vec4::ZYXZ() const { return Vec4(this->z, this->y, this->x, this->z); }
inline Vec4 Vec4::ZYXW() const { return Vec4(this->z, this->y, this->x, this->w); }
inline Vec4 Vec4::ZYYX() const { return Vec4(this->z, this->y, this->y, this->x); }
inline Vec4 Vec4::ZYYY() const { return Vec4(this->z, this->y, this->y, this->y); }
inline Vec4 Vec4::ZYYZ() const { return Vec4(this->z, this->y, this->y, this->z); }
inline Vec4 Vec4::ZYYW() const { return Vec4(this->z, this->y, this->y, this->w); }
inline Vec4 Vec4::ZYZX() const { return Vec4(this->z, this->y, this->z, this->x); }
inline Vec4 Vec4::ZYZY() const { return Vec4(this->z, this->y, this->z, this->y); }
inline Vec4 Vec4::ZYZZ() const { return Vec4(this->z, this->y, this->z, this->z); }
inline Vec4 Vec4::ZYZW() const { return Vec4(this->z, this->y, this->z, this->w); }
inline Vec4 Vec4::ZYWX() const { return Vec4(this->z, this->y, this->w, this->x); }
inline Vec4 Vec4::ZYWY() const { return Vec4(this->z, this->y, this->w, this->y); }
inline Vec4 Vec4::ZYWZ() const { return Vec4(this->z, this->y, this->w, this->z); }
inline Vec4 Vec4::ZYWW() const { return Vec4(this->z, this->y, this->w, this->w); }
inline Vec4 Vec4::ZZXX() const { return Vec4(this->z, this->z, this->x, this->x); }
inline Vec4 Vec4::ZZXY() const { return Vec4(this->z, this->z, this->x, this->y); }
inline Vec4 Vec4::ZZXZ() const { return Vec4(this->z, this->z, this->x, this->z); }
inline Vec4 Vec4::ZZXW() const { return Vec4(this->z, this->z, this->x, this->w); }
inline Vec4 Vec4::ZZYX() const { return Vec4(this->z, this->z, this->y, this->x); }
inline Vec4 Vec4::ZZYY() const { return Vec4(this->z, this->z, this->y, this->y); }
inline Vec4 Vec4::ZZYZ() const { return Vec4(this->z, this->z, this->y, this->z); }
inline Vec4 Vec4::ZZYW() const { return Vec4(this->z, this->z, this->y, this->w); }
inline Vec4 Vec4::ZZZX() const { return Vec4(this->z, this->z, this->z, this->x); }
inline Vec4 Vec4::ZZZY() const { return Vec4(this->z, this->z, this->z, this->y); }
inline Vec4 Vec4::ZZZZ() const { return Vec4(this->z, this->z, this->z, this->z); }
inline Vec4 Vec4::ZZZW() const { return Vec4(this->z, this->z, this->z, this->w); }
inline Vec4 Vec4::ZZWX() const { return Vec4(this->z, this->z, this->w, this->x); }
inline Vec4 Vec4::ZZWY() const { return Vec4(this->z, this->z, this->w, this->y); }
inline Vec4 Vec4::ZZWZ() const { return Vec4(this->z, this->z, this->w, this->z); }
inline Vec4 Vec4::ZZWW() const { return Vec4(this->z, this->z, this->w, this->w); }
inline Vec4 Vec4::ZWXX() const { return Vec4(this->z, this->w, this->x, this->x); }
inline Vec4 Vec4::ZWXY() const { return Vec4(this->z, this->w, this->x, this->y); }
inline Vec4 Vec4::ZWXZ() const { return Vec4(this->z, this->w, this->x, this->z); }
inline Vec4 Vec4::ZWXW() const { return Vec4(this->z, this->w, this->x, this->w); }
inline Vec4 Vec4::ZWYX() const { return Vec4(this->z, this->w, this->y, this->x); }
inline Vec4 Vec4::ZWYY() const { return Vec4(this->z, this->w, this->y, this->y); }
inline Vec4 Vec4::ZWYZ() const { return Vec4(this->z, this->w, this->y, this->z); }
inline Vec4 Vec4::ZWYW() const { return Vec4(this->z, this->w, this->y, this->w); }
inline Vec4 Vec4::ZWZX() const { return Vec4(this->z, this->w, this->z, this->x); }
inline Vec4 Vec4::ZWZY() const { return Vec4(this->z, this->w, this->z, this->y); }
inline Vec4 Vec4::ZWZZ() const { return Vec4(this->z, this->w, this->z, this->z); }
inline Vec4 Vec4::ZWZW() const { return Vec4(this->z, this->w, this->z, this->w); }
inline Vec4 Vec4::ZWWX() const { return Vec4(this->z, this->w, this->w, this->x); }
inline Vec4 Vec4::ZWWY() const { return Vec4(this->z, this->w, this->w, this->y); }
inline Vec4 Vec4::ZWWZ() const { return Vec4(this->z, this->w, this->w, this->z); }
inline Vec4 Vec4::ZWWW() const { return Vec4(this->z, this->w, this->w, this->w); }
inline Vec4 Vec4::WXXX() const { return Vec4(this->w, this->x, this->x, this->x); }
inline Vec4 Vec4::WXXY() const { return Vec4(this->w, this->x, this->x, this->y); }
inline Vec4 Vec4::WXXZ() const { return Vec4(this->w, this->x, this->x, this->z); }
inline Vec4 Vec4::WXXW() const { return Vec4(this->w, this->x, this->x, this->w); }
inline Vec4 Vec4::WXYX() const { return Vec4(this->w, this->x, this->y, this->x); }
inline Vec4 Vec4::WXYY() const { return Vec4(this->w, this->x, this->y, this->y); }
inline Vec4 Vec4::WXYZ() const { return Vec4(this->w, this->x, this->y, this->z); }
inline Vec4 Vec4::WXYW() const { return Vec4(this->w, this->x, this->y, this->w); }
inline Vec4 Vec4::WXZX() const { return Vec4(this->w, this->x, this->z, this->x); }
inline Vec4 Vec4::WXZY() const { return Vec4(this->w, this->x, this->z, this->y); }
inline Vec4 Vec4::WXZZ() const { return Vec4(this->w, this->x, this->z, this->z); }
inline Vec4 Vec4::WXZW() const { return Vec4(this->w, this->x, this->z, this->w); }
inline Vec4 Vec4::WXWX() const { return Vec4(this->w, this->x, this->w, this->x); }
inline Vec4 Vec4::WXWY() const { return Vec4(this->w, this->x, this->w, this->y); }
inline Vec4 Vec4::WXWZ() const { return Vec4(this->w, this->x, this->w, this->z); }
inline Vec4 Vec4::WXWW() const { return Vec4(this->w, this->x, this->w, this->w); }
inline Vec4 Vec4::WYXX() const { return Vec4(this->w, this->y, this->x, this->x); }
inline Vec4 Vec4::WYXY() const { return Vec4(this->w, this->y, this->x, this->y); }
inline Vec4 Vec4::WYXZ() const { return Vec4(this->w, this->y, this->x, this->z); }
inline Vec4 Vec4::WYXW() const { return Vec4(this->w, this->y, this->x, this->w); }
inline Vec4 Vec4::WYYX() const { return Vec4(this->w, this->y, this->y, this->x); }
inline Vec4 Vec4::WYYY() const { return Vec4(this->w, this->y, this->y, this->y); }
inline Vec4 Vec4::WYYZ() const { return Vec4(this->w, this->y, this->y, this->z); }
inline Vec4 Vec4::WYYW() const { return Vec4(this->w, this->y, this->y, this->w); }
inline Vec4 Vec4::WYZX() const { return Vec4(this->w, this->y, this->z, this->x); }
inline Vec4 Vec4::WYZY() const { return Vec4(this->w, this->y, this->z, this->y); }
inline Vec4 Vec4::WYZZ() const { return Vec4(this->w, this->y, this->z, this->z); }
inline Vec4 Vec4::WYZW() const { return Vec4(this->w, this->y, this->z, this->w); }
inline Vec4 Vec4::WYWX() const { return Vec4(this->w, this->y, this->w, this->x); }
inline Vec4 Vec4::WYWY() const { return Vec4(this->w, this->y, this->w, this->y); }
inline Vec4 Vec4::WYWZ() const { return Vec4(this->w, this->y, this->w, this->z); }
inline Vec4 Vec4::WYWW() const { return Vec4(this->w, this->y, this->w, this->w); }
inline Vec4 Vec4::WZXX() const { return Vec4(this->w, this->z, this->x, this->x); }
inline Vec4 Vec4::WZXY() const { return Vec4(this->w, this->z, this->x, this->y); }
inline Vec4 Vec4::WZXZ() const { return Vec4(this->w, this->z, this->x, this->z); }
inline Vec4 Vec4::WZXW() const { return Vec4(this->w, this->z, this->x, this->w); }
inline Vec4 Vec4::WZYX() const { return Vec4(this->w, this->z, this->y, this->x); }
inline Vec4 Vec4::WZYY() const { return Vec4(this->w, this->z, this->y, this->y); }
inline Vec4 Vec4::WZYZ() const { return Vec4(this->w, this->z, this->y, this->z); }
inline Vec4 Vec4::WZYW() const { return Vec4(this->w, this->z, this->y, this->w); }
inline Vec4 Vec4::WZZX() const { return Vec4(this->w, this->z, this->z, this->x); }
inline Vec4 Vec4::WZZY() const { return Vec4(this->w, this->z, this->z, this->y); }
inline Vec4 Vec4::WZZZ() const { return Vec4(this->w, this->z, this->z, this->z); }
inline Vec4 Vec4::WZZW() const { return Vec4(this->w, this->z, this->z, this->w); }
inline Vec4 Vec4::WZWX() const { return Vec4(this->w, this->z, this->w, this->x); }
inline Vec4 Vec4::WZWY() const { return Vec4(this->w, this->z, this->w, this->y); }
inline Vec4 Vec4::WZWZ() const { return Vec4(this->w, this->z, this->w, this->z); }
inline Vec4 Vec4::WZWW() const { return Vec4(this->w, this->z, this->w, this->w); }
inline Vec4 Vec4::WWXX() const { return Vec4(this->w, this->w, this->x, this->x); }
inline Vec4 Vec4::WWXY() const { return Vec4(this->w, this->w, this->x, this->y); }
inline Vec4 Vec4::WWXZ() const { return Vec4(this->w, this->w, this->x, this->z); }
inline Vec4 Vec4::WWXW() const { return Vec4(this->w, this->w, this->x, this->w); }
inline Vec4 Vec4::WWYX() const { return Vec4(this->w, this->w, this->y, this->x); }
inline Vec4 Vec4::WWYY() const { return Vec4(this->w, this->w, this->y, this->y); }
inline Vec4 Vec4::WWYZ() const { return Vec4(this->w, this->w, this->y, this->z); }
inline Vec4 Vec4::WWYW() const { return Vec4(this->w, this->w, this->y, this->w); }
inline Vec4 Vec4::WWZX() const { return Vec4(this->w, this->w, this->z, this->x); }
inline Vec4 Vec4::WWZY() const { return Vec4(this->w, this->w, this->z, this->y); }
inline Vec4 Vec4::WWZZ() const { return Vec4(this->w, this->w, this->z, this->z); }
inline Vec4 Vec4::WWZW() const { return Vec4(this->w, this->w, this->z, this->w); }
inline Vec4 Vec4::WWWX() const { return Vec4(this->w, this->w, this->w, this->x); }
inline Vec4 Vec4::WWWY() const { return Vec4(this->w, this->w, this->w, this->y); }
inline Vec4 Vec4::WWWZ() const { return Vec4(this->w, this->w, this->w, this->z); }
inline Vec4 Vec4::WWWW() const { return Vec4(this->w, this->w, this->w, this->w); }
inline Vec4 Vec4::RRRR() const { return Vec4(this->x, this->x, this->x, this->x); }
inline Vec4 Vec4::RRRG() const { return Vec4(this->x, this->x, this->x, this->y); }
inline Vec4 Vec4::RRRB() const { return Vec4(this->x, this->x, this->x, this->z); }
inline Vec4 Vec4::RRRA() const { return Vec4(this->x, this->x, this->x, this->w); }
inline Vec4 Vec4::RRGR() const { return Vec4(this->x, this->x, this->y, this->x); }
inline Vec4 Vec4::RRGG() const { return Vec4(this->x, this->x, this->y, this->y); }
inline Vec4 Vec4::RRGB() const { return Vec4(this->x, this->x, this->y, this->z); }
inline Vec4 Vec4::RRGA() const { return Vec4(this->x, this->x, this->y, this->w); }
inline Vec4 Vec4::RRBR() const { return Vec4(this->x, this->x, this->z, this->x); }
inline Vec4 Vec4::RRBG() const { return Vec4(this->x, this->x, this->z, this->y); }
inline Vec4 Vec4::RRBB() const { return Vec4(this->x, this->x, this->z, this->z); }
inline Vec4 Vec4::RRBA() const { return Vec4(this->x, this->x, this->z, this->w); }
inline Vec4 Vec4::RRAR() const { return Vec4(this->x, this->x, this->w, this->x); }
inline Vec4 Vec4::RRAG() const { return Vec4(this->x, this->x, this->w, this->y); }
inline Vec4 Vec4::RRAB() const { return Vec4(this->x, this->x, this->w, this->z); }
inline Vec4 Vec4::RRAA() const { return Vec4(this->x, this->x, this->w, this->w); }
inline Vec4 Vec4::RGRR() const { return Vec4(this->x, this->y, this->x, this->x); }
inline Vec4 Vec4::RGRG() const { return Vec4(this->x, this->y, this->x, this->y); }
inline Vec4 Vec4::RGRB() const { return Vec4(this->x, this->y, this->x, this->z); }
inline Vec4 Vec4::RGRA() const { return Vec4(this->x, this->y, this->x, this->w); }
inline Vec4 Vec4::RGGR() const { return Vec4(this->x, this->y, this->y, this->x); }
inline Vec4 Vec4::RGGG() const { return Vec4(this->x, this->y, this->y, this->y); }
inline Vec4 Vec4::RGGB() const { return Vec4(this->x, this->y, this->y, this->z); }
inline Vec4 Vec4::RGGA() const { return Vec4(this->x, this->y, this->y, this->w); }
inline Vec4 Vec4::RGBR() const { return Vec4(this->x, this->y, this->z, this->x); }
inline Vec4 Vec4::RGBG() const { return Vec4(this->x, this->y, this->z, this->y); }
inline Vec4 Vec4::RGBB() const { return Vec4(this->x, this->y, this->z, this->z); }
inline Vec4 Vec4::RGAR() const { return Vec4(this->x, this->y, this->w, this->x); }
inline Vec4 Vec4::RGAG() const { return Vec4(this->x, this->y, this->w, this->y); }
inline Vec4 Vec4::RGAB() const { return Vec4(this->x, this->y, this->w, this->z); }
inline Vec4 Vec4::RGAA() const { return Vec4(this->x, this->y, this->w, this->w); }
inline Vec4 Vec4::RBRR() const { return Vec4(this->x, this->z, this->x, this->x); }
inline Vec4 Vec4::RBRG() const { return Vec4(this->x, this->z, this->x, this->y); }
inline Vec4 Vec4::RBRB() const { return Vec4(this->x, this->z, this->x, this->z); }
inline Vec4 Vec4::RBRA() const { return Vec4(this->x, this->z, this->x, this->w); }
inline Vec4 Vec4::RBGR() const { return Vec4(this->x, this->z, this->y, this->x); }
inline Vec4 Vec4::RBGG() const { return Vec4(this->x, this->z, this->y, this->y); }
inline Vec4 Vec4::RBGB() const { return Vec4(this->x, this->z, this->y, this->z); }
inline Vec4 Vec4::RBGA() const { return Vec4(this->x, this->z, this->y, this->w); }
inline Vec4 Vec4::RBBR() const { return Vec4(this->x, this->z, this->z, this->x); }
inline Vec4 Vec4::RBBG() const { return Vec4(this->x, this->z, this->z, this->y); }
inline Vec4 Vec4::RBBB() const { return Vec4(this->x, this->z, this->z, this->z); }
inline Vec4 Vec4::RBBA() const { return Vec4(this->x, this->z, this->z, this->w); }
inline Vec4 Vec4::RBAR() const { return Vec4(this->x, this->z, this->w, this->x); }
inline Vec4 Vec4::RBAG() const { return Vec4(this->x, this->z, this->w, this->y); }
inline Vec4 Vec4::RBAB() const { return Vec4(this->x, this->z, this->w, this->z); }
inline Vec4 Vec4::RBAA() const { return Vec4(this->x, this->z, this->w, this->w); }
inline Vec4 Vec4::RARR() const { return Vec4(this->x, this->w, this->x, this->x); }
inline Vec4 Vec4::RARG() const { return Vec4(this->x, this->w, this->x, this->y); }
inline Vec4 Vec4::RARB() const { return Vec4(this->x, this->w, this->x, this->z); }
inline Vec4 Vec4::RARA() const { return Vec4(this->x, this->w, this->x, this->w); }
inline Vec4 Vec4::RAGR() const { return Vec4(this->x, this->w, this->y, this->x); }
inline Vec4 Vec4::RAGG() const { return Vec4(this->x, this->w, this->y, this->y); }
inline Vec4 Vec4::RAGB() const { return Vec4(this->x, this->w, this->y, this->z); }
inline Vec4 Vec4::RAGA() const { return Vec4(this->x, this->w, this->y, this->w); }
inline Vec4 Vec4::RABR() const { return Vec4(this->x, this->w, this->z, this->x); }
inline Vec4 Vec4::RABG() const { return Vec4(this->x, this->w, this->z, this->y); }
inline Vec4 Vec4::RABB() const { return Vec4(this->x, this->w, this->z, this->z); }
inline Vec4 Vec4::RABA() const { return Vec4(this->x, this->w, this->z, this->w); }
inline Vec4 Vec4::RAAR() const { return Vec4(this->x, this->w, this->w, this->x); }
inline Vec4 Vec4::RAAG() const { return Vec4(this->x, this->w, this->w, this->y); }
inline Vec4 Vec4::RAAB() const { return Vec4(this->x, this->w, this->w, this->z); }
inline Vec4 Vec4::RAAA() const { return Vec4(this->x, this->w, this->w, this->w); }
inline Vec4 Vec4::GRRR() const { return Vec4(this->y, this->x, this->x, this->x); }
inline Vec4 Vec4::GRRG() const { return Vec4(this->y, this->x, this->x, this->y); }
inline Vec4 Vec4::GRRB() const { return Vec4(this->y, this->x, this->x, this->z); }
inline Vec4 Vec4::GRRA() const { return Vec4(this->y, this->x, this->x, this->w); }
inline Vec4 Vec4::GRGR() const { return Vec4(this->y, this->x, this->y, this->x); }
inline Vec4 Vec4::GRGG() const { return Vec4(this->y, this->x, this->y, this->y); }
inline Vec4 Vec4::GRGB() const { return Vec4(this->y, this->x, this->y, this->z); }
inline Vec4 Vec4::GRGA() const { return Vec4(this->y, this->x, this->y, this->w); }
inline Vec4 Vec4::GRBR() const { return Vec4(this->y, this->x, this->z, this->x); }
inline Vec4 Vec4::GRBG() const { return Vec4(this->y, this->x, this->z, this->y); }
inline Vec4 Vec4::GRBB() const { return Vec4(this->y, this->x, this->z, this->z); }
inline Vec4 Vec4::GRBA() const { return Vec4(this->y, this->x, this->z, this->w); }
inline Vec4 Vec4::GRAR() const { return Vec4(this->y, this->x, this->w, this->x); }
inline Vec4 Vec4::GRAG() const { return Vec4(this->y, this->x, this->w, this->y); }
inline Vec4 Vec4::GRAB() const { return Vec4(this->y, this->x, this->w, this->z); }
inline Vec4 Vec4::GRAA() const { return Vec4(this->y, this->x, this->w, this->w); }
inline Vec4 Vec4::GGRR() const { return Vec4(this->y, this->y, this->x, this->x); }
inline Vec4 Vec4::GGRG() const { return Vec4(this->y, this->y, this->x, this->y); }
inline Vec4 Vec4::GGRB() const { return Vec4(this->y, this->y, this->x, this->z); }
inline Vec4 Vec4::GGRA() const { return Vec4(this->y, this->y, this->x, this->w); }
inline Vec4 Vec4::GGGR() const { return Vec4(this->y, this->y, this->y, this->x); }
inline Vec4 Vec4::GGGG() const { return Vec4(this->y, this->y, this->y, this->y); }
inline Vec4 Vec4::GGGB() const { return Vec4(this->y, this->y, this->y, this->z); }
inline Vec4 Vec4::GGGA() const { return Vec4(this->y, this->y, this->y, this->w); }
inline Vec4 Vec4::GGBR() const { return Vec4(this->y, this->y, this->z, this->x); }
inline Vec4 Vec4::GGBG() const { return Vec4(this->y, this->y, this->z, this->y); }
inline Vec4 Vec4::GGBB() const { return Vec4(this->y, this->y, this->z, this->z); }
inline Vec4 Vec4::GGBA() const { return Vec4(this->y, this->y, this->z, this->w); }
inline Vec4 Vec4::GGAR() const { return Vec4(this->y, this->y, this->w, this->x); }
inline Vec4 Vec4::GGAG() const { return Vec4(this->y, this->y, this->w, this->y); }
inline Vec4 Vec4::GGAB() const { return Vec4(this->y, this->y, this->w, this->z); }
inline Vec4 Vec4::GGAA() const { return Vec4(this->y, this->y, this->w, this->w); }
inline Vec4 Vec4::GBRR() const { return Vec4(this->y, this->z, this->x, this->x); }
inline Vec4 Vec4::GBRG() const { return Vec4(this->y, this->z, this->x, this->y); }
inline Vec4 Vec4::GBRB() const { return Vec4(this->y, this->z, this->x, this->z); }
inline Vec4 Vec4::GBRA() const { return Vec4(this->y, this->z, this->x, this->w); }
inline Vec4 Vec4::GBGR() const { return Vec4(this->y, this->z, this->y, this->x); }
inline Vec4 Vec4::GBGG() const { return Vec4(this->y, this->z, this->y, this->y); }
inline Vec4 Vec4::GBGB() const { return Vec4(this->y, this->z, this->y, this->z); }
inline Vec4 Vec4::GBGA() const { return Vec4(this->y, this->z, this->y, this->w); }
inline Vec4 Vec4::GBBR() const { return Vec4(this->y, this->z, this->z, this->x); }
inline Vec4 Vec4::GBBG() const { return Vec4(this->y, this->z, this->z, this->y); }
inline Vec4 Vec4::GBBB() const { return Vec4(this->y, this->z, this->z, this->z); }
inline Vec4 Vec4::GBBA() const { return Vec4(this->y, this->z, this->z, this->w); }
inline Vec4 Vec4::GBAR() const { return Vec4(this->y, this->z, this->w, this->x); }
inline Vec4 Vec4::GBAG() const { return Vec4(this->y, this->z, this->w, this->y); }
inline Vec4 Vec4::GBAB() const { return Vec4(this->y, this->z, this->w, this->z); }
inline Vec4 Vec4::GBAA() const { return Vec4(this->y, this->z, this->w, this->w); }
inline Vec4 Vec4::GARR() const { return Vec4(this->y, this->w, this->x, this->x); }
inline Vec4 Vec4::GARG() const { return Vec4(this->y, this->w, this->x, this->y); }
inline Vec4 Vec4::GARB() const { return Vec4(this->y, this->w, this->x, this->z); }
inline Vec4 Vec4::GARA() const { return Vec4(this->y, this->w, this->x, this->w); }
inline Vec4 Vec4::GAGR() const { return Vec4(this->y, this->w, this->y, this->x); }
inline Vec4 Vec4::GAGG() const { return Vec4(this->y, this->w, this->y, this->y); }
inline Vec4 Vec4::GAGB() const { return Vec4(this->y, this->w, this->y, this->z); }
inline Vec4 Vec4::GAGA() const { return Vec4(this->y, this->w, this->y, this->w); }
inline Vec4 Vec4::GABR() const { return Vec4(this->y, this->w, this->z, this->x); }
inline Vec4 Vec4::GABG() const { return Vec4(this->y, this->w, this->z, this->y); }
inline Vec4 Vec4::GABB() const { return Vec4(this->y, this->w, this->z, this->z); }
inline Vec4 Vec4::GABA() const { return Vec4(this->y, this->w, this->z, this->w); }
inline Vec4 Vec4::GAAR() const { return Vec4(this->y, this->w, this->w, this->x); }
inline Vec4 Vec4::GAAG() const { return Vec4(this->y, this->w, this->w, this->y); }
inline Vec4 Vec4::GAAB() const { return Vec4(this->y, this->w, this->w, this->z); }
inline Vec4 Vec4::GAAA() const { return Vec4(this->y, this->w, this->w, this->w); }
inline Vec4 Vec4::BRRR() const { return Vec4(this->z, this->x, this->x, this->x); }
inline Vec4 Vec4::BRRG() const { return Vec4(this->z, this->x, this->x, this->y); }
inline Vec4 Vec4::BRRB() const { return Vec4(this->z, this->x, this->x, this->z); }
inline Vec4 Vec4::BRRA() const { return Vec4(this->z, this->x, this->x, this->w); }
inline Vec4 Vec4::BRGR() const { return Vec4(this->z, this->x, this->y, this->x); }
inline Vec4 Vec4::BRGG() const { return Vec4(this->z, this->x, this->y, this->y); }
inline Vec4 Vec4::BRGB() const { return Vec4(this->z, this->x, this->y, this->z); }
inline Vec4 Vec4::BRGA() const { return Vec4(this->z, this->x, this->y, this->w); }
inline Vec4 Vec4::BRBR() const { return Vec4(this->z, this->x, this->z, this->x); }
inline Vec4 Vec4::BRBG() const { return Vec4(this->z, this->x, this->z, this->y); }
inline Vec4 Vec4::BRBB() const { return Vec4(this->z, this->x, this->z, this->z); }
inline Vec4 Vec4::BRBA() const { return Vec4(this->z, this->x, this->z, this->w); }
inline Vec4 Vec4::BRAR() const { return Vec4(this->z, this->x, this->w, this->x); }
inline Vec4 Vec4::BRAG() const { return Vec4(this->z, this->x, this->w, this->y); }
inline Vec4 Vec4::BRAB() const { return Vec4(this->z, this->x, this->w, this->z); }
inline Vec4 Vec4::BRAA() const { return Vec4(this->z, this->x, this->w, this->w); }
inline Vec4 Vec4::BGRR() const { return Vec4(this->z, this->y, this->x, this->x); }
inline Vec4 Vec4::BGRG() const { return Vec4(this->z, this->y, this->x, this->y); }
inline Vec4 Vec4::BGRB() const { return Vec4(this->z, this->y, this->x, this->z); }
inline Vec4 Vec4::BGRA() const { return Vec4(this->z, this->y, this->x, this->w); }
inline Vec4 Vec4::BGGR() const { return Vec4(this->z, this->y, this->y, this->x); }
inline Vec4 Vec4::BGGG() const { return Vec4(this->z, this->y, this->y, this->y); }
inline Vec4 Vec4::BGGB() const { return Vec4(this->z, this->y, this->y, this->z); }
inline Vec4 Vec4::BGGA() const { return Vec4(this->z, this->y, this->y, this->w); }
inline Vec4 Vec4::BGBR() const { return Vec4(this->z, this->y, this->z, this->x); }
inline Vec4 Vec4::BGBG() const { return Vec4(this->z, this->y, this->z, this->y); }
inline Vec4 Vec4::BGBB() const { return Vec4(this->z, this->y, this->z, this->z); }
inline Vec4 Vec4::BGBA() const { return Vec4(this->z, this->y, this->z, this->w); }
inline Vec4 Vec4::BGAR() const { return Vec4(this->z, this->y, this->w, this->x); }
inline Vec4 Vec4::BGAG() const { return Vec4(this->z, this->y, this->w, this->y); }
inline Vec4 Vec4::BGAB() const { return Vec4(this->z, this->y, this->w, this->z); }
inline Vec4 Vec4::BGAA() const { return Vec4(this->z, this->y, this->w, this->w); }
inline Vec4 Vec4::BBRR() const { return Vec4(this->z, this->z, this->x, this->x); }
inline Vec4 Vec4::BBRG() const { return Vec4(this->z, this->z, this->x, this->y); }
inline Vec4 Vec4::BBRB() const { return Vec4(this->z, this->z, this->x, this->z); }
inline Vec4 Vec4::BBRA() const { return Vec4(this->z, this->z, this->x, this->w); }
inline Vec4 Vec4::BBGR() const { return Vec4(this->z, this->z, this->y, this->x); }
inline Vec4 Vec4::BBGG() const { return Vec4(this->z, this->z, this->y, this->y); }
inline Vec4 Vec4::BBGB() const { return Vec4(this->z, this->z, this->y, this->z); }
inline Vec4 Vec4::BBGA() const { return Vec4(this->z, this->z, this->y, this->w); }
inline Vec4 Vec4::BBBR() const { return Vec4(this->z, this->z, this->z, this->x); }
inline Vec4 Vec4::BBBG() const { return Vec4(this->z, this->z, this->z, this->y); }
inline Vec4 Vec4::BBBB() const { return Vec4(this->z, this->z, this->z, this->z); }
inline Vec4 Vec4::BBBA() const { return Vec4(this->z, this->z, this->z, this->w); }
inline Vec4 Vec4::BBAR() const { return Vec4(this->z, this->z, this->w, this->x); }
inline Vec4 Vec4::BBAG() const { return Vec4(this->z, this->z, this->w, this->y); }
inline Vec4 Vec4::BBAB() const { return Vec4(this->z, this->z, this->w, this->z); }
inline Vec4 Vec4::BBAA() const { return Vec4(this->z, this->z, this->w, this->w); }
inline Vec4 Vec4::BARR() const { return Vec4(this->z, this->w, this->x, this->x); }
inline Vec4 Vec4::BARG() const { return Vec4(this->z, this->w, this->x, this->y); }
inline Vec4 Vec4::BARB() const { return Vec4(this->z, this->w, this->x, this->z); }
inline Vec4 Vec4::BARA() const { return Vec4(this->z, this->w, this->x, this->w); }
inline Vec4 Vec4::BAGR() const { return Vec4(this->z, this->w, this->y, this->x); }
inline Vec4 Vec4::BAGG() const { return Vec4(this->z, this->w, this->y, this->y); }
inline Vec4 Vec4::BAGB() const { return Vec4(this->z, this->w, this->y, this->z); }
inline Vec4 Vec4::BAGA() const { return Vec4(this->z, this->w, this->y, this->w); }
inline Vec4 Vec4::BABR() const { return Vec4(this->z, this->w, this->z, this->x); }
inline Vec4 Vec4::BABG() const { return Vec4(this->z, this->w, this->z, this->y); }
inline Vec4 Vec4::BABB() const { return Vec4(this->z, this->w, this->z, this->z); }
inline Vec4 Vec4::BABA() const { return Vec4(this->z, this->w, this->z, this->w); }
inline Vec4 Vec4::BAAR() const { return Vec4(this->z, this->w, this->w, this->x); }
inline Vec4 Vec4::BAAG() const { return Vec4(this->z, this->w, this->w, this->y); }
inline Vec4 Vec4::BAAB() const { return Vec4(this->z, this->w, this->w, this->z); }
inline Vec4 Vec4::BAAA() const { return Vec4(this->z, this->w, this->w, this->w); }
inline Vec4 Vec4::ARRR() const { return Vec4(this->w, this->x, this->x, this->x); }
inline Vec4 Vec4::ARRG() const { return Vec4(this->w, this->x, this->x, this->y); }
inline Vec4 Vec4::ARRB() const { return Vec4(this->w, this->x, this->x, this->z); }
inline Vec4 Vec4::ARRA() const { return Vec4(this->w, this->x, this->x, this->w); }
inline Vec4 Vec4::ARGR() const { return Vec4(this->w, this->x, this->y, this->x); }
inline Vec4 Vec4::ARGG() const { return Vec4(this->w, this->x, this->y, this->y); }
inline Vec4 Vec4::ARGB() const { return Vec4(this->w, this->x, this->y, this->z); }
inline Vec4 Vec4::ARGA() const { return Vec4(this->w, this->x, this->y, this->w); }
inline Vec4 Vec4::ARBR() const { return Vec4(this->w, this->x, this->z, this->x); }
inline Vec4 Vec4::ARBG() const { return Vec4(this->w, this->x, this->z, this->y); }
inline Vec4 Vec4::ARBB() const { return Vec4(this->w, this->x, this->z, this->z); }
inline Vec4 Vec4::ARBA() const { return Vec4(this->w, this->x, this->z, this->w); }
inline Vec4 Vec4::ARAR() const { return Vec4(this->w, this->x, this->w, this->x); }
inline Vec4 Vec4::ARAG() const { return Vec4(this->w, this->x, this->w, this->y); }
inline Vec4 Vec4::ARAB() const { return Vec4(this->w, this->x, this->w, this->z); }
inline Vec4 Vec4::ARAA() const { return Vec4(this->w, this->x, this->w, this->w); }
inline Vec4 Vec4::AGRR() const { return Vec4(this->w, this->y, this->x, this->x); }
inline Vec4 Vec4::AGRG() const { return Vec4(this->w, this->y, this->x, this->y); }
inline Vec4 Vec4::AGRB() const { return Vec4(this->w, this->y, this->x, this->z); }
inline Vec4 Vec4::AGRA() const { return Vec4(this->w, this->y, this->x, this->w); }
inline Vec4 Vec4::AGGR() const { return Vec4(this->w, this->y, this->y, this->x); }
inline Vec4 Vec4::AGGG() const { return Vec4(this->w, this->y, this->y, this->y); }
inline Vec4 Vec4::AGGB() const { return Vec4(this->w, this->y, this->y, this->z); }
inline Vec4 Vec4::AGGA() const { return Vec4(this->w, this->y, this->y, this->w); }
inline Vec4 Vec4::AGBR() const { return Vec4(this->w, this->y, this->z, this->x); }
inline Vec4 Vec4::AGBG() const { return Vec4(this->w, this->y, this->z, this->y); }
inline Vec4 Vec4::AGBB() const { return Vec4(this->w, this->y, this->z, this->z); }
inline Vec4 Vec4::AGBA() const { return Vec4(this->w, this->y, this->z, this->w); }
inline Vec4 Vec4::AGAR() const { return Vec4(this->w, this->y, this->w, this->x); }
inline Vec4 Vec4::AGAG() const { return Vec4(this->w, this->y, this->w, this->y); }
inline Vec4 Vec4::AGAB() const { return Vec4(this->w, this->y, this->w, this->z); }
inline Vec4 Vec4::AGAA() const { return Vec4(this->w, this->y, this->w, this->w); }
inline Vec4 Vec4::ABRR() const { return Vec4(this->w, this->z, this->x, this->x); }
inline Vec4 Vec4::ABRG() const { return Vec4(this->w, this->z, this->x, this->y); }
inline Vec4 Vec4::ABRB() const { return Vec4(this->w, this->z, this->x, this->z); }
inline Vec4 Vec4::ABRA() const { return Vec4(this->w, this->z, this->x, this->w); }
inline Vec4 Vec4::ABGR() const { return Vec4(this->w, this->z, this->y, this->x); }
inline Vec4 Vec4::ABGG() const { return Vec4(this->w, this->z, this->y, this->y); }
inline Vec4 Vec4::ABGB() const { return Vec4(this->w, this->z, this->y, this->z); }
inline Vec4 Vec4::ABGA() const { return Vec4(this->w, this->z, this->y, this->w); }
inline Vec4 Vec4::ABBR() const { return Vec4(this->w, this->z, this->z, this->x); }
inline Vec4 Vec4::ABBG() const { return Vec4(this->w, this->z, this->z, this->y); }
inline Vec4 Vec4::ABBB() const { return Vec4(this->w, this->z, this->z, this->z); }
inline Vec4 Vec4::ABBA() const { return Vec4(this->w, this->z, this->z, this->w); }
inline Vec4 Vec4::ABAR() const { return Vec4(this->w, this->z, this->w, this->x); }
inline Vec4 Vec4::ABAG() const { return Vec4(this->w, this->z, this->w, this->y); }
inline Vec4 Vec4::ABAB() const { return Vec4(this->w, this->z, this->w, this->z); }
inline Vec4 Vec4::ABAA() const { return Vec4(this->w, this->z, this->w, this->w); }
inline Vec4 Vec4::AARR() const { return Vec4(this->w, this->w, this->x, this->x); }
inline Vec4 Vec4::AARG() const { return Vec4(this->w, this->w, this->x, this->y); }
inline Vec4 Vec4::AARB() const { return Vec4(this->w, this->w, this->x, this->z); }
inline Vec4 Vec4::AARA() const { return Vec4(this->w, this->w, this->x, this->w); }
inline Vec4 Vec4::AAGR() const { return Vec4(this->w, this->w, this->y, this->x); }
inline Vec4 Vec4::AAGG() const { return Vec4(this->w, this->w, this->y, this->y); }
inline Vec4 Vec4::AAGB() const { return Vec4(this->w, this->w, this->y, this->z); }
inline Vec4 Vec4::AAGA() const { return Vec4(this->w, this->w, this->y, this->w); }
inline Vec4 Vec4::AABR() const { return Vec4(this->w, this->w, this->z, this->x); }
inline Vec4 Vec4::AABG() const { return Vec4(this->w, this->w, this->z, this->y); }
inline Vec4 Vec4::AABB() const { return Vec4(this->w, this->w, this->z, this->z); }
inline Vec4 Vec4::AABA() const { return Vec4(this->w, this->w, this->z, this->w); }
inline Vec4 Vec4::AAAR() const { return Vec4(this->w, this->w, this->w, this->x); }
inline Vec4 Vec4::AAAG() const { return Vec4(this->w, this->w, this->w, this->y); }
inline Vec4 Vec4::AAAB() const { return Vec4(this->w, this->w, this->w, this->z); }
inline Vec4 Vec4::AAAA() const { return Vec4(this->w, this->w, this->w, this->w); }

#pragma endregion

#pragma endregion

#pragma region DoublePrecisionVectors

#pragma region Vec2

inline Vec2Double::Vec2Double() : x(0.0f), y(0.0f) {}
inline Vec2Double::Vec2Double(double _x, double _y) : x(_x), y(_y) {}
inline Vec2Double::Vec2Double(const Vec2Double& _other) { (*this) = _other; }

inline Vec2Double& Vec2Double::operator=(const Vec2Double& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
	}
	return *this;
}

inline Vec2Double& Vec2Double::operator+=(const Vec2Double& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec2Double& Vec2Double::operator-=(const Vec2Double& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec2Double& Vec2Double::operator*=(const double _scale) {
	*this = *this * _scale;
	return *this;
}

inline double& Vec2Double::operator[](int _ndx) {
	assert(_ndx < 2);
	return xy[_ndx];
}

inline double Vec2Double::operator[](int _ndx) const {
	assert(_ndx < 2);
	return xy[_ndx];
}

inline Vec2Double Vec2Double::operator+(const Vec2Double& _other) const {
	return Vec2Double(this->x + _other.x, this->y + _other.y);
}

inline Vec2Double Vec2Double::operator-(const Vec2Double& _other) const {
	return Vec2Double(this->x - _other.x, this->y - _other.y);
}

inline Vec2Double Vec2Double::operator*(const double _scale) const {
	return Vec2Double(this->x * _scale, this->y * _scale);
}

inline double Vec2Double::operator*(const Vec2Double& _other) const {
	return (this->x * _other.x) + (this->y * _other.y);
}

inline double Vec2Double::operator&(const Vec2Double& _other) const {
	return (this->x * _other.y) - (this->y * _other.x);
}

inline Vec2Double Vec2Double::operator~() const {
	return Vec2Double();
}

inline Vec2Double Vec2Double::operator-() const {
	return Vec2Double(-this->x, -this->y);
}

inline bool Vec2Double::operator==(const Vec2Double& _other) const {
	return this->x == _other.x && this->y == _other.y;
}

inline bool Vec2Double::operator<(const Vec2Double& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec2Double::operator>(const Vec2Double& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec2Double::operator<=(const Vec2Double& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec2Double::operator>=(const Vec2Double& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec2Double::operator!=(const Vec2Double& _other) const {
	return this->x != _other.x || this->y != _other.y;
}

inline double Vec2Double::Length() const {
	return sqrt((*this) * (*this));
}

inline double Vec2Double::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec2Double::Normalize() {
	double len = Length();
	if (!len) return;

	this->x /= len;
	this->y /= len;
}

inline Vec2Double Vec2Double::Normalized() const {
	double len = Length();
	if (!len) return Vec2Double();

	return Vec2Double(this->x / len, this->x / len);
}

inline double Vec2Double::AngleBetween(const Vec2Double& _other) const {
	return acos(this->Normalized() * _other.Normalized());
}

inline double Vec2Double::Dot(const Vec2Double& _other) const {
	return *this * _other;
}

inline double Vec2Double::Cross(const Vec2Double& _other) const {
	return *this & _other;
}

inline void Vec2Double::Add(const Vec2Double& _other) {
	*this += _other;
}

inline void Vec2Double::Subtract(const Vec2Double& _other) {
	*this -= _other;
}

inline void Vec2Double::Scale(const double _scale) {
	*this *= _scale;
}

inline void Vec2Double::Zero() {
	*this = ~(*this);
}

inline void Vec2Double::Negate() {
	*this = -(*this);
}

inline bool Vec2Double::Equals(const Vec2Double& _other) const {
	return *this == _other;
}

inline bool Vec2Double::Less(const Vec2Double& _other) const {
	return *this < _other;
}

inline bool Vec2Double::LessThanOrEquals(const Vec2Double& _other) const {
	return *this <= _other;
}

inline bool Vec2Double::Greater(const Vec2Double& _other) const {
	return *this > _other;
}

inline bool Vec2Double::GreaterThanOrEquals(const Vec2Double& _other) const {
	return *this >= _other;
}

inline bool Vec2Double::NotEquals(const Vec2Double& _other) const {
	return *this != _other;
}

inline double& Vec2Double::X() { return this->x; }
inline double& Vec2Double::Y() { return this->y; }
inline double Vec2Double::X() const { return this->x; }
inline double Vec2Double::Y() const { return this->y; }

inline Vec2Double Vec2Double::XX() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec2Double::YY() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec2Double::YX() const { return Vec2Double(this->y, this->x); }
inline Vec2Double Vec2Double::RR() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec2Double::GG() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec2Double::GR() const { return Vec2Double(this->y, this->x); }

#pragma endregion

#pragma region Vec3

inline Vec3Double::Vec3Double() : x(0.0f), y(0.0f), z(0.0f) {}
inline Vec3Double::Vec3Double(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
inline Vec3Double::Vec3Double(const Vec2Double& _xy, double _z) : x(_xy.X()), y(_xy.Y()), z(_z) {}
inline Vec3Double::Vec3Double(double _x, const Vec2Double& _yz) : x(_x), y(_yz.X()), z(_yz.Y()) {}
inline Vec3Double::Vec3Double(const Vec3Double& _other) { *this = _other; }

inline Vec3Double& Vec3Double::operator=(const Vec3Double& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
	}
	return *this;
}

inline Vec3Double& Vec3Double::operator+=(const Vec3Double& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec3Double& Vec3Double::operator-=(const Vec3Double& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec3Double& Vec3Double::operator*=(const double _scale) {
	*this = *this * _scale;
	return *this;
}

inline Vec3Double& Vec3Double::operator&=(const Vec3Double& _other) {
	*this = *this & _other;
	return *this;
}

inline double& Vec3Double::operator[](int _ndx) {
	assert(_ndx < 3);
	return xyz[_ndx];
}

inline double Vec3Double::operator[](int _ndx) const {
	assert(_ndx < 3);
	return xyz[_ndx];
}

inline Vec3Double Vec3Double::operator+(const Vec3Double& _other) const {
	return Vec3Double(this->x + _other.x, this->y + _other.y, this->z + _other.z);
}

inline Vec3Double Vec3Double::operator-(const Vec3Double& _other) const {
	return Vec3Double(this->x - _other.x, this->y - _other.y, this->z - _other.z);
}

inline Vec3Double Vec3Double::operator*(const double _scale) const {
	return Vec3Double(this->x * _scale, this->y * _scale, this->z * _scale);
}

inline double Vec3Double::operator*(const Vec3Double& _other) const {
	return (this->x * _other.x) + (this->y * _other.y) + (this->z * _other.z);
}

inline Vec3Double Vec3Double::operator&(const Vec3Double& _other) const {
	return Vec3Double((this->y * _other.z) - (this->z * _other.y), (this->x * _other.z) - (this->z * _other.x), (this->x * _other.y) - (this->y * _other.x));
}

inline Vec3Double Vec3Double::operator~() const {
	return Vec3Double(0.0f, 0.0f, 0.0f);
}

inline Vec3Double Vec3Double::operator-() const {
	return Vec3Double(-this->x, -this->y, -this->z);
}

inline bool Vec3Double::operator==(const Vec3Double& _other) const {
	return this->x == _other.x && this->y == _other.y && this->z == _other.z;
}

inline bool Vec3Double::operator<(const Vec3Double& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec3Double::operator>(const Vec3Double& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec3Double::operator<=(const Vec3Double& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec3Double::operator>=(const Vec3Double& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec3Double::operator!=(const Vec3Double& _other) const {
	return this->x != _other.x || this->y != _other.y || this->z != _other.z;
}

inline double Vec3Double::Length() const {
	return sqrt((*this) * (*this));
}

inline double Vec3Double::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec3Double::Normalize() {
	double len = Length();
	if (!len) return;

	this->x /= len;
	this->y /= len;
	this->z /= len;
}

inline Vec3Double Vec3Double::Normalized() const {
	double len = Length();
	if (!len) return Vec3Double();

	return Vec3Double(this->x / len, this->y / len, this->z / len);
}

inline double Vec3Double::AngleBetween(const Vec3Double& _other) const {
	return acos(this->Normalized() * _other.Normalized());
}

inline double Vec3Double::Dot(const Vec3Double& _other) const {
	return *this * _other;
}

inline void Vec3Double::Cross(const Vec3Double& _other) {
	*this &= _other;
}

inline void Vec3Double::Add(const Vec3Double& _other) {
	*this += _other;
}

inline void Vec3Double::Subtract(const Vec3Double& _other) {
	*this -= _other;
}

inline void Vec3Double::Scale(const double _scale) {
	*this *= _scale;
}

inline void Vec3Double::Negate() {
	*this = -(*this);
}

inline void Vec3Double::Zero() {
	*this = ~(*this);
}

inline bool Vec3Double::Equals(const Vec3Double& _other) const {
	return *this == _other;
}

inline bool Vec3Double::Less(const Vec3Double& _other) const {
	return *this < _other;
}

inline bool Vec3Double::LessThanOrEquals(const Vec3Double& _other) const {
	return *this <= _other;
}

inline bool Vec3Double::Greater(const Vec3Double& _other) const {
	return *this > _other;
}

inline bool Vec3Double::GreaterThanOrEquals(const Vec3Double& _other) const {
	return *this >= _other;
}

inline bool Vec3Double::NotEquals(const Vec3Double& _other) const {
	return *this != _other;
}

inline double& Vec3Double::X() { return this->x; }
inline double& Vec3Double::Y() { return this->y; }
inline double& Vec3Double::Z() { return this->z; }
inline double Vec3Double::X() const { return this->x; }
inline double Vec3Double::Y() const { return this->y; }
inline double Vec3Double::Z() const { return this->z; }

//Vec2Double Swizzle
inline Vec2Double Vec3Double::XX() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec3Double::YY() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec3Double::ZZ() const { return Vec2Double(this->z, this->z); }
inline Vec2Double Vec3Double::XY() const { return Vec2Double(this->x, this->y); }
inline Vec2Double Vec3Double::XZ() const { return Vec2Double(this->x, this->z); }
inline Vec2Double Vec3Double::YX() const { return Vec2Double(this->y, this->x); }
inline Vec2Double Vec3Double::YZ() const { return Vec2Double(this->y, this->z); }
inline Vec2Double Vec3Double::ZX() const { return Vec2Double(this->z, this->x); }
inline Vec2Double Vec3Double::ZY() const { return Vec2Double(this->z, this->y); }
inline Vec2Double Vec3Double::RR() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec3Double::GG() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec3Double::BB() const { return Vec2Double(this->z, this->z); }
inline Vec2Double Vec3Double::RG() const { return Vec2Double(this->x, this->y); }
inline Vec2Double Vec3Double::RB() const { return Vec2Double(this->x, this->z); }
inline Vec2Double Vec3Double::GR() const { return Vec2Double(this->y, this->x); }
inline Vec2Double Vec3Double::GB() const { return Vec2Double(this->y, this->z); }
inline Vec2Double Vec3Double::BR() const { return Vec2Double(this->z, this->x); }
inline Vec2Double Vec3Double::BG() const { return Vec2Double(this->z, this->y); }

//Vec3Double Swizzle
inline Vec3Double Vec3Double::XXX() const { return Vec3Double(this->x, this->x, this->x); }
inline Vec3Double Vec3Double::XXY() const { return Vec3Double(this->x, this->x, this->y); }
inline Vec3Double Vec3Double::XXZ() const { return Vec3Double(this->x, this->x, this->z); }
inline Vec3Double Vec3Double::XYX() const { return Vec3Double(this->x, this->y, this->x); }
inline Vec3Double Vec3Double::XYY() const { return Vec3Double(this->x, this->y, this->y); }
inline Vec3Double Vec3Double::XZX() const { return Vec3Double(this->x, this->z, this->x); }
inline Vec3Double Vec3Double::XZY() const { return Vec3Double(this->x, this->z, this->y); }
inline Vec3Double Vec3Double::XZZ() const { return Vec3Double(this->x, this->z, this->z); }
inline Vec3Double Vec3Double::YXX() const { return Vec3Double(this->y, this->x, this->x); }
inline Vec3Double Vec3Double::YXY() const { return Vec3Double(this->y, this->x, this->y); }
inline Vec3Double Vec3Double::YXZ() const { return Vec3Double(this->y, this->x, this->z); }
inline Vec3Double Vec3Double::YYX() const { return Vec3Double(this->y, this->y, this->x); }
inline Vec3Double Vec3Double::YYY() const { return Vec3Double(this->y, this->y, this->y); }
inline Vec3Double Vec3Double::YYZ() const { return Vec3Double(this->y, this->y, this->z); }
inline Vec3Double Vec3Double::YZX() const { return Vec3Double(this->y, this->z, this->x); }
inline Vec3Double Vec3Double::YZY() const { return Vec3Double(this->y, this->z, this->y); }
inline Vec3Double Vec3Double::YZZ() const { return Vec3Double(this->y, this->z, this->z); }
inline Vec3Double Vec3Double::ZXX() const { return Vec3Double(this->z, this->x, this->x); }
inline Vec3Double Vec3Double::ZXY() const { return Vec3Double(this->z, this->x, this->y); }
inline Vec3Double Vec3Double::ZXZ() const { return Vec3Double(this->z, this->x, this->z); }
inline Vec3Double Vec3Double::ZYX() const { return Vec3Double(this->z, this->y, this->x); }
inline Vec3Double Vec3Double::ZYY() const { return Vec3Double(this->z, this->y, this->y); }
inline Vec3Double Vec3Double::ZYZ() const { return Vec3Double(this->z, this->y, this->z); }
inline Vec3Double Vec3Double::ZZX() const { return Vec3Double(this->z, this->z, this->x); }
inline Vec3Double Vec3Double::ZZY() const { return Vec3Double(this->z, this->z, this->y); }
inline Vec3Double Vec3Double::ZZZ() const { return Vec3Double(this->z, this->z, this->z); }
inline Vec3Double Vec3Double::RRR() const { return Vec3Double(this->x, this->x, this->x); }
inline Vec3Double Vec3Double::RRG() const { return Vec3Double(this->x, this->x, this->y); }
inline Vec3Double Vec3Double::RRB() const { return Vec3Double(this->x, this->x, this->z); }
inline Vec3Double Vec3Double::RGR() const { return Vec3Double(this->x, this->y, this->x); }
inline Vec3Double Vec3Double::RGG() const { return Vec3Double(this->x, this->y, this->y); }
inline Vec3Double Vec3Double::RBR() const { return Vec3Double(this->x, this->z, this->x); }
inline Vec3Double Vec3Double::RBG() const { return Vec3Double(this->x, this->z, this->y); }
inline Vec3Double Vec3Double::RBB() const { return Vec3Double(this->x, this->z, this->z); }
inline Vec3Double Vec3Double::GRR() const { return Vec3Double(this->y, this->x, this->x); }
inline Vec3Double Vec3Double::GRG() const { return Vec3Double(this->y, this->x, this->y); }
inline Vec3Double Vec3Double::GRB() const { return Vec3Double(this->y, this->x, this->z); }
inline Vec3Double Vec3Double::GGR() const { return Vec3Double(this->y, this->y, this->x); }
inline Vec3Double Vec3Double::GGG() const { return Vec3Double(this->y, this->y, this->y); }
inline Vec3Double Vec3Double::GGB() const { return Vec3Double(this->y, this->y, this->z); }
inline Vec3Double Vec3Double::GBR() const { return Vec3Double(this->y, this->z, this->x); }
inline Vec3Double Vec3Double::GBG() const { return Vec3Double(this->y, this->z, this->y); }
inline Vec3Double Vec3Double::GBB() const { return Vec3Double(this->y, this->z, this->z); }
inline Vec3Double Vec3Double::BRR() const { return Vec3Double(this->z, this->x, this->x); }
inline Vec3Double Vec3Double::BRG() const { return Vec3Double(this->z, this->x, this->y); }
inline Vec3Double Vec3Double::BRB() const { return Vec3Double(this->z, this->x, this->z); }
inline Vec3Double Vec3Double::BGR() const { return Vec3Double(this->z, this->y, this->x); }
inline Vec3Double Vec3Double::BGG() const { return Vec3Double(this->z, this->y, this->y); }
inline Vec3Double Vec3Double::BGB() const { return Vec3Double(this->z, this->y, this->z); }
inline Vec3Double Vec3Double::BBR() const { return Vec3Double(this->z, this->z, this->x); }
inline Vec3Double Vec3Double::BBG() const { return Vec3Double(this->z, this->z, this->y); }
inline Vec3Double Vec3Double::BBB() const { return Vec3Double(this->z, this->z, this->z); }

#pragma endregion

#pragma region Vec4

inline Vec4Double::Vec4Double() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
inline Vec4Double::Vec4Double(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}
inline Vec4Double::Vec4Double(const Vec2Double& _xy, double _z, double _w) : x(_xy.X()), y(_xy.Y()), z(_z), w(_w) {}
inline Vec4Double::Vec4Double(double _x, const Vec2Double& _yz, double _w) : x(_x), y(_yz.X()), z(_yz.Y()), w(_w) {}
inline Vec4Double::Vec4Double(double _x, double _y, const Vec2Double& _zw) : x(_x), y(_y), z(_zw.X()), w(_zw.Y()) {}
inline Vec4Double::Vec4Double(const Vec2Double& _xy, const Vec2Double& _zw) : x(_xy.X()), y(_xy.Y()), z(_zw.X()), w(_zw.Y()) {}
inline Vec4Double::Vec4Double(const Vec3Double& _xyz, double _w) : x(_xyz.X()), y(_xyz.Y()), z(_xyz.Z()), w(_w) {}
inline Vec4Double::Vec4Double(double _x, const Vec3Double& _yzw) : x(_x), y(_yzw.X()), z(_yzw.Y()), w(_yzw.Z()) {}
inline Vec4Double::Vec4Double(const Vec4Double& _other) { (*this) = _other; }

inline Vec4Double& Vec4Double::operator=(const Vec4Double& _other) {
	if (this != &_other) {
		this->x = _other.x;
		this->y = _other.y;
		this->z = _other.z;
		this->w = _other.w;
	}
	return *this;
}

inline Vec4Double& Vec4Double::operator+=(const Vec4Double& _other) {
	*this = *this + _other;
	return *this;
}

inline Vec4Double& Vec4Double::operator-=(const Vec4Double& _other) {
	*this = *this - _other;
	return *this;
}

inline Vec4Double& Vec4Double::operator*=(const double _scale) {
	*this = *this * _scale;
	return *this;
}

inline Vec4Double& Vec4Double::operator&=(const Vec4Double& _other) {
	*this = *this & _other;
	return *this;
}

inline double& Vec4Double::operator[](int _ndx) {
	assert(_ndx < 4);
	return xyzw[_ndx];
}

inline double Vec4Double::operator[](int _ndx) const {
	assert(_ndx < 4);
	return xyzw[_ndx];
}

inline Vec4Double Vec4Double::operator+(const Vec4Double& _other) const {
	return Vec4Double(this->x + _other.x, this->y + _other.y, this->z + _other.z, this->w + _other.w);
}

inline Vec4Double Vec4Double::operator-(const Vec4Double& _other) const {
	return Vec4Double(this->x - _other.x, this->y - _other.y, this->z - _other.z, this->w - _other.w);
}

inline Vec4Double Vec4Double::operator*(const double _scale) const {
	return Vec4Double(this->x * _scale, this->y * _scale, this->z * _scale, this->w * _scale);
}

inline double Vec4Double::operator*(const Vec4Double& _other) const {
	return (this->x * _other.x) + (this->y * _other.y) + (this->z * _other.z);
}

inline Vec4Double Vec4Double::operator&(const Vec4Double& _other) const {
	return Vec4Double((this->y * _other.z) - (this->z * _other.y), (this->x * _other.z) - (this->z * _other.x), (this->x * _other.y) - (this->y * _other.x), 0.0f);
}

inline Vec4Double Vec4Double::operator~() const {
	return Vec4Double();
}

inline Vec4Double Vec4Double::operator-() const {
	return Vec4Double(-this->x, -this->y, -this->z, -this->w);
}

inline bool Vec4Double::operator==(const Vec4Double& _other) const {
	return this->x == _other.x && this->y == _other.y && this->z == _other.z && this->w == _other.w;
}

inline bool Vec4Double::operator<(const Vec4Double& _other) const {
	return this->LengthSquared() < _other.LengthSquared();
}

inline bool Vec4Double::operator>(const Vec4Double& _other) const {
	return this->LengthSquared() > _other.LengthSquared();
}

inline bool Vec4Double::operator<=(const Vec4Double& _other) const {
	return this->LengthSquared() <= _other.LengthSquared();
}

inline bool Vec4Double::operator>=(const Vec4Double& _other) const {
	return this->LengthSquared() >= _other.LengthSquared();
}

inline bool Vec4Double::operator!=(const Vec4Double& _other) const {
	return this->x != _other.x || this->y != _other.y || this->z != _other.z || this->w != _other.w;
}

inline double Vec4Double::Length() const {
	return sqrtf((*this) * (*this));
}

inline double Vec4Double::LengthSquared() const {
	return (*this) * (*this);
}

inline void Vec4Double::Normalize() {
	double len = this->Length();
	if (len == 0.0f) return;

	this->x /= len;
	this->y /= len;
	this->z /= len;
	this->w /= len;
}

inline Vec4Double Vec4Double::Normalized() const {
	double len = this->Length();
	if (len == 0.0f) return Vec4Double();

	return Vec4Double(this->x / len, this->y / len, this->z / len, this->w / len);
}

inline double Vec4Double::AngleBetween(const Vec4Double& _other) const {
	return acosf(*this * _other);
}

inline double Vec4Double::Dot(const Vec4Double& _other) const {
	return *this * _other;
}

inline void Vec4Double::Cross(const Vec4Double& _other) {
	*this &= _other;
}

inline void Vec4Double::Add(const Vec4Double& _other) {
	*this += _other;
}

inline void Vec4Double::Subtract(const Vec4Double& _other) {
	*this -= _other;
}

inline void Vec4Double::Scale(const double _scale) {
	*this *= _scale;
}

inline void Vec4Double::Negate() {
	*this = -(*this);
}

inline void Vec4Double::Zero() {
	*this = ~(*this);
}

inline bool Vec4Double::Equals(const Vec4Double& _other) const {
	return *this == _other;
}

inline bool Vec4Double::Less(const Vec4Double& _other) const {
	return *this < _other;
}

inline bool Vec4Double::LessThanOrEquals(const Vec4Double& _other) const {
	return *this <= _other;
}

inline bool Vec4Double::Greater(const Vec4Double& _other) const {
	return *this > _other;
}

inline bool Vec4Double::GreaterThanOrEquals(const Vec4Double& _other) const {
	return *this >= _other;
}

inline bool Vec4Double::NotEquals(const Vec4Double& _other) const {
	return *this != _other;
}

inline double& Vec4Double::X() { return this->x; }
inline double& Vec4Double::Y() { return this->y; }
inline double& Vec4Double::Z() { return this->z; }
inline double& Vec4Double::W() { return this->w; }
inline double Vec4Double::X() const { return this->x; }
inline double Vec4Double::Y() const { return this->y; }
inline double Vec4Double::Z() const { return this->z; }
inline double Vec4Double::W() const { return this->w; }

//Vec2Double Swizzle
inline Vec2Double Vec4Double::XX() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec4Double::YY() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec4Double::ZZ() const { return Vec2Double(this->z, this->z); }
inline Vec2Double Vec4Double::WW() const { return Vec2Double(this->w, this->w); }
inline Vec2Double Vec4Double::XY() const { return Vec2Double(this->x, this->y); }
inline Vec2Double Vec4Double::XZ() const { return Vec2Double(this->x, this->z); }
inline Vec2Double Vec4Double::XW() const { return Vec2Double(this->x, this->w); }
inline Vec2Double Vec4Double::YX() const { return Vec2Double(this->y, this->x); }
inline Vec2Double Vec4Double::YZ() const { return Vec2Double(this->y, this->z); }
inline Vec2Double Vec4Double::YW() const { return Vec2Double(this->y, this->w); }
inline Vec2Double Vec4Double::ZX() const { return Vec2Double(this->z, this->x); }
inline Vec2Double Vec4Double::ZY() const { return Vec2Double(this->z, this->y); }
inline Vec2Double Vec4Double::ZW() const { return Vec2Double(this->z, this->w); }
inline Vec2Double Vec4Double::WX() const { return Vec2Double(this->w, this->x); }
inline Vec2Double Vec4Double::WY() const { return Vec2Double(this->w, this->y); }
inline Vec2Double Vec4Double::WZ() const { return Vec2Double(this->w, this->z); }
inline Vec2Double Vec4Double::RR() const { return Vec2Double(this->x, this->x); }
inline Vec2Double Vec4Double::GG() const { return Vec2Double(this->y, this->y); }
inline Vec2Double Vec4Double::BB() const { return Vec2Double(this->z, this->z); }
inline Vec2Double Vec4Double::AA() const { return Vec2Double(this->w, this->w); }
inline Vec2Double Vec4Double::RG() const { return Vec2Double(this->x, this->y); }
inline Vec2Double Vec4Double::RB() const { return Vec2Double(this->x, this->z); }
inline Vec2Double Vec4Double::RA() const { return Vec2Double(this->x, this->w); }
inline Vec2Double Vec4Double::GR() const { return Vec2Double(this->y, this->x); }
inline Vec2Double Vec4Double::GB() const { return Vec2Double(this->y, this->z); }
inline Vec2Double Vec4Double::GA() const { return Vec2Double(this->y, this->w); }
inline Vec2Double Vec4Double::BR() const { return Vec2Double(this->z, this->x); }
inline Vec2Double Vec4Double::BG() const { return Vec2Double(this->z, this->y); }
inline Vec2Double Vec4Double::BA() const { return Vec2Double(this->z, this->w); }
inline Vec2Double Vec4Double::AR() const { return Vec2Double(this->w, this->x); }
inline Vec2Double Vec4Double::AG() const { return Vec2Double(this->w, this->y); }
inline Vec2Double Vec4Double::AB() const { return Vec2Double(this->w, this->z); }

//Vec3Double Swizzle
inline Vec3Double Vec4Double::XXX() const { return Vec3Double(this->x, this->x, this->x); }
inline Vec3Double Vec4Double::XXY() const { return Vec3Double(this->x, this->x, this->y); }
inline Vec3Double Vec4Double::XXZ() const { return Vec3Double(this->x, this->x, this->z); }
inline Vec3Double Vec4Double::XXW() const { return Vec3Double(this->x, this->x, this->w); }
inline Vec3Double Vec4Double::XYX() const { return Vec3Double(this->x, this->y, this->x); }
inline Vec3Double Vec4Double::XYY() const { return Vec3Double(this->x, this->y, this->y); }
inline Vec3Double Vec4Double::XYZ() const { return Vec3Double(this->x, this->y, this->z); }
inline Vec3Double Vec4Double::XYW() const { return Vec3Double(this->x, this->y, this->w); }
inline Vec3Double Vec4Double::XZX() const { return Vec3Double(this->x, this->z, this->x); }
inline Vec3Double Vec4Double::XZY() const { return Vec3Double(this->x, this->z, this->y); }
inline Vec3Double Vec4Double::XZZ() const { return Vec3Double(this->x, this->z, this->z); }
inline Vec3Double Vec4Double::XZW() const { return Vec3Double(this->x, this->z, this->w); }
inline Vec3Double Vec4Double::XWX() const { return Vec3Double(this->x, this->w, this->x); }
inline Vec3Double Vec4Double::XWY() const { return Vec3Double(this->x, this->w, this->y); }
inline Vec3Double Vec4Double::XWZ() const { return Vec3Double(this->x, this->w, this->z); }
inline Vec3Double Vec4Double::XWW() const { return Vec3Double(this->x, this->w, this->w); }
inline Vec3Double Vec4Double::YXX() const { return Vec3Double(this->y, this->x, this->x); }
inline Vec3Double Vec4Double::YXY() const { return Vec3Double(this->y, this->x, this->y); }
inline Vec3Double Vec4Double::YXZ() const { return Vec3Double(this->y, this->x, this->z); }
inline Vec3Double Vec4Double::YXW() const { return Vec3Double(this->y, this->x, this->w); }
inline Vec3Double Vec4Double::YYX() const { return Vec3Double(this->y, this->y, this->x); }
inline Vec3Double Vec4Double::YYY() const { return Vec3Double(this->y, this->y, this->y); }
inline Vec3Double Vec4Double::YYZ() const { return Vec3Double(this->y, this->y, this->z); }
inline Vec3Double Vec4Double::YYW() const { return Vec3Double(this->y, this->y, this->w); }
inline Vec3Double Vec4Double::YZX() const { return Vec3Double(this->y, this->z, this->x); }
inline Vec3Double Vec4Double::YZY() const { return Vec3Double(this->y, this->z, this->y); }
inline Vec3Double Vec4Double::YZZ() const { return Vec3Double(this->y, this->z, this->z); }
inline Vec3Double Vec4Double::YZW() const { return Vec3Double(this->y, this->z, this->w); }
inline Vec3Double Vec4Double::YWX() const { return Vec3Double(this->y, this->w, this->x); }
inline Vec3Double Vec4Double::YWY() const { return Vec3Double(this->y, this->w, this->y); }
inline Vec3Double Vec4Double::YWZ() const { return Vec3Double(this->y, this->w, this->z); }
inline Vec3Double Vec4Double::YWW() const { return Vec3Double(this->y, this->w, this->w); }
inline Vec3Double Vec4Double::ZXX() const { return Vec3Double(this->z, this->x, this->x); }
inline Vec3Double Vec4Double::ZXY() const { return Vec3Double(this->z, this->x, this->y); }
inline Vec3Double Vec4Double::ZXZ() const { return Vec3Double(this->z, this->x, this->z); }
inline Vec3Double Vec4Double::ZXW() const { return Vec3Double(this->z, this->x, this->w); }
inline Vec3Double Vec4Double::ZYX() const { return Vec3Double(this->z, this->y, this->x); }
inline Vec3Double Vec4Double::ZYY() const { return Vec3Double(this->z, this->y, this->y); }
inline Vec3Double Vec4Double::ZYZ() const { return Vec3Double(this->z, this->y, this->z); }
inline Vec3Double Vec4Double::ZYW() const { return Vec3Double(this->z, this->y, this->w); }
inline Vec3Double Vec4Double::ZZX() const { return Vec3Double(this->z, this->z, this->x); }
inline Vec3Double Vec4Double::ZZY() const { return Vec3Double(this->z, this->z, this->y); }
inline Vec3Double Vec4Double::ZZZ() const { return Vec3Double(this->z, this->z, this->z); }
inline Vec3Double Vec4Double::ZZW() const { return Vec3Double(this->z, this->z, this->w); }
inline Vec3Double Vec4Double::ZWX() const { return Vec3Double(this->z, this->w, this->x); }
inline Vec3Double Vec4Double::ZWY() const { return Vec3Double(this->z, this->w, this->y); }
inline Vec3Double Vec4Double::ZWZ() const { return Vec3Double(this->z, this->w, this->z); }
inline Vec3Double Vec4Double::ZWW() const { return Vec3Double(this->z, this->w, this->w); }
inline Vec3Double Vec4Double::WXX() const { return Vec3Double(this->w, this->x, this->x); }
inline Vec3Double Vec4Double::WXY() const { return Vec3Double(this->w, this->x, this->y); }
inline Vec3Double Vec4Double::WXZ() const { return Vec3Double(this->w, this->x, this->z); }
inline Vec3Double Vec4Double::WXW() const { return Vec3Double(this->w, this->x, this->w); }
inline Vec3Double Vec4Double::WYX() const { return Vec3Double(this->w, this->y, this->x); }
inline Vec3Double Vec4Double::WYY() const { return Vec3Double(this->w, this->y, this->y); }
inline Vec3Double Vec4Double::WYZ() const { return Vec3Double(this->w, this->y, this->z); }
inline Vec3Double Vec4Double::WYW() const { return Vec3Double(this->w, this->y, this->w); }
inline Vec3Double Vec4Double::WZX() const { return Vec3Double(this->w, this->z, this->x); }
inline Vec3Double Vec4Double::WZY() const { return Vec3Double(this->w, this->z, this->y); }
inline Vec3Double Vec4Double::WZZ() const { return Vec3Double(this->w, this->z, this->z); }
inline Vec3Double Vec4Double::WZW() const { return Vec3Double(this->w, this->z, this->w); }
inline Vec3Double Vec4Double::WWX() const { return Vec3Double(this->w, this->w, this->x); }
inline Vec3Double Vec4Double::WWY() const { return Vec3Double(this->w, this->w, this->y); }
inline Vec3Double Vec4Double::WWZ() const { return Vec3Double(this->w, this->w, this->z); }
inline Vec3Double Vec4Double::WWW() const { return Vec3Double(this->w, this->w, this->w); }
inline Vec3Double Vec4Double::RRR() const { return Vec3Double(this->x, this->x, this->x); }
inline Vec3Double Vec4Double::RRG() const { return Vec3Double(this->x, this->x, this->y); }
inline Vec3Double Vec4Double::RRB() const { return Vec3Double(this->x, this->x, this->z); }
inline Vec3Double Vec4Double::RRA() const { return Vec3Double(this->x, this->x, this->w); }
inline Vec3Double Vec4Double::RGR() const { return Vec3Double(this->x, this->y, this->x); }
inline Vec3Double Vec4Double::RGG() const { return Vec3Double(this->x, this->y, this->y); }
inline Vec3Double Vec4Double::RGA() const { return Vec3Double(this->x, this->y, this->w); }
inline Vec3Double Vec4Double::RGB() const { return Vec3Double(this->x, this->y, this->z); }
inline Vec3Double Vec4Double::RBR() const { return Vec3Double(this->x, this->z, this->x); }
inline Vec3Double Vec4Double::RBG() const { return Vec3Double(this->x, this->z, this->y); }
inline Vec3Double Vec4Double::RBB() const { return Vec3Double(this->x, this->z, this->z); }
inline Vec3Double Vec4Double::RBA() const { return Vec3Double(this->x, this->z, this->w); }
inline Vec3Double Vec4Double::RAR() const { return Vec3Double(this->x, this->w, this->x); }
inline Vec3Double Vec4Double::RAG() const { return Vec3Double(this->x, this->w, this->y); }
inline Vec3Double Vec4Double::RAB() const { return Vec3Double(this->x, this->w, this->z); }
inline Vec3Double Vec4Double::RAA() const { return Vec3Double(this->x, this->w, this->w); }
inline Vec3Double Vec4Double::GRR() const { return Vec3Double(this->y, this->x, this->x); }
inline Vec3Double Vec4Double::GRG() const { return Vec3Double(this->y, this->x, this->y); }
inline Vec3Double Vec4Double::GRB() const { return Vec3Double(this->y, this->x, this->z); }
inline Vec3Double Vec4Double::GRA() const { return Vec3Double(this->y, this->x, this->w); }
inline Vec3Double Vec4Double::GGR() const { return Vec3Double(this->y, this->y, this->x); }
inline Vec3Double Vec4Double::GGG() const { return Vec3Double(this->y, this->y, this->y); }
inline Vec3Double Vec4Double::GGB() const { return Vec3Double(this->y, this->y, this->z); }
inline Vec3Double Vec4Double::GGA() const { return Vec3Double(this->y, this->y, this->w); }
inline Vec3Double Vec4Double::GBR() const { return Vec3Double(this->y, this->z, this->x); }
inline Vec3Double Vec4Double::GBG() const { return Vec3Double(this->y, this->z, this->y); }
inline Vec3Double Vec4Double::GBB() const { return Vec3Double(this->y, this->z, this->z); }
inline Vec3Double Vec4Double::GBA() const { return Vec3Double(this->y, this->z, this->w); }
inline Vec3Double Vec4Double::GAR() const { return Vec3Double(this->y, this->w, this->x); }
inline Vec3Double Vec4Double::GAG() const { return Vec3Double(this->y, this->w, this->y); }
inline Vec3Double Vec4Double::GAB() const { return Vec3Double(this->y, this->w, this->z); }
inline Vec3Double Vec4Double::GAA() const { return Vec3Double(this->y, this->w, this->w); }
inline Vec3Double Vec4Double::BRR() const { return Vec3Double(this->z, this->x, this->x); }
inline Vec3Double Vec4Double::BRG() const { return Vec3Double(this->z, this->x, this->y); }
inline Vec3Double Vec4Double::BRB() const { return Vec3Double(this->z, this->x, this->z); }
inline Vec3Double Vec4Double::BRA() const { return Vec3Double(this->z, this->x, this->w); }
inline Vec3Double Vec4Double::BGR() const { return Vec3Double(this->z, this->y, this->x); }
inline Vec3Double Vec4Double::BGG() const { return Vec3Double(this->z, this->y, this->y); }
inline Vec3Double Vec4Double::BGB() const { return Vec3Double(this->z, this->y, this->z); }
inline Vec3Double Vec4Double::BGA() const { return Vec3Double(this->z, this->y, this->w); }
inline Vec3Double Vec4Double::BBR() const { return Vec3Double(this->z, this->z, this->x); }
inline Vec3Double Vec4Double::BBG() const { return Vec3Double(this->z, this->z, this->y); }
inline Vec3Double Vec4Double::BBB() const { return Vec3Double(this->z, this->z, this->z); }
inline Vec3Double Vec4Double::BBA() const { return Vec3Double(this->z, this->z, this->w); }
inline Vec3Double Vec4Double::BAR() const { return Vec3Double(this->z, this->w, this->x); }
inline Vec3Double Vec4Double::BAG() const { return Vec3Double(this->z, this->w, this->y); }
inline Vec3Double Vec4Double::BAB() const { return Vec3Double(this->z, this->w, this->z); }
inline Vec3Double Vec4Double::BAA() const { return Vec3Double(this->z, this->w, this->w); }
inline Vec3Double Vec4Double::ARR() const { return Vec3Double(this->w, this->x, this->x); }
inline Vec3Double Vec4Double::ARG() const { return Vec3Double(this->w, this->x, this->y); }
inline Vec3Double Vec4Double::ARB() const { return Vec3Double(this->w, this->x, this->z); }
inline Vec3Double Vec4Double::ARA() const { return Vec3Double(this->w, this->x, this->w); }
inline Vec3Double Vec4Double::AGR() const { return Vec3Double(this->w, this->y, this->x); }
inline Vec3Double Vec4Double::AGG() const { return Vec3Double(this->w, this->y, this->y); }
inline Vec3Double Vec4Double::AGB() const { return Vec3Double(this->w, this->y, this->z); }
inline Vec3Double Vec4Double::AGA() const { return Vec3Double(this->w, this->y, this->w); }
inline Vec3Double Vec4Double::ABR() const { return Vec3Double(this->w, this->z, this->x); }
inline Vec3Double Vec4Double::ABG() const { return Vec3Double(this->w, this->z, this->y); }
inline Vec3Double Vec4Double::ABB() const { return Vec3Double(this->w, this->z, this->z); }
inline Vec3Double Vec4Double::ABA() const { return Vec3Double(this->w, this->z, this->w); }
inline Vec3Double Vec4Double::AAR() const { return Vec3Double(this->w, this->w, this->x); }
inline Vec3Double Vec4Double::AAG() const { return Vec3Double(this->w, this->w, this->y); }
inline Vec3Double Vec4Double::AAB() const { return Vec3Double(this->w, this->w, this->z); }
inline Vec3Double Vec4Double::AAA() const { return Vec3Double(this->w, this->w, this->w); }

//Vec4Double Swizzle
inline Vec4Double Vec4Double::XXXX() const { return Vec4Double(this->x, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::XXXY() const { return Vec4Double(this->x, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::XXXZ() const { return Vec4Double(this->x, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::XXXW() const { return Vec4Double(this->x, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::XXYX() const { return Vec4Double(this->x, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::XXYY() const { return Vec4Double(this->x, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::XXYZ() const { return Vec4Double(this->x, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::XXYW() const { return Vec4Double(this->x, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::XXZX() const { return Vec4Double(this->x, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::XXZY() const { return Vec4Double(this->x, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::XXZZ() const { return Vec4Double(this->x, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::XXZW() const { return Vec4Double(this->x, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::XXWX() const { return Vec4Double(this->x, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::XXWY() const { return Vec4Double(this->x, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::XXWZ() const { return Vec4Double(this->x, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::XXWW() const { return Vec4Double(this->x, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::XYXX() const { return Vec4Double(this->x, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::XYXY() const { return Vec4Double(this->x, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::XYXZ() const { return Vec4Double(this->x, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::XYXW() const { return Vec4Double(this->x, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::XYYX() const { return Vec4Double(this->x, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::XYYY() const { return Vec4Double(this->x, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::XYYZ() const { return Vec4Double(this->x, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::XYYW() const { return Vec4Double(this->x, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::XYZX() const { return Vec4Double(this->x, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::XYZY() const { return Vec4Double(this->x, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::XYZZ() const { return Vec4Double(this->x, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::XYWX() const { return Vec4Double(this->x, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::XYWY() const { return Vec4Double(this->x, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::XYWZ() const { return Vec4Double(this->x, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::XYWW() const { return Vec4Double(this->x, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::XZXX() const { return Vec4Double(this->x, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::XZXY() const { return Vec4Double(this->x, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::XZXZ() const { return Vec4Double(this->x, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::XZXW() const { return Vec4Double(this->x, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::XZYX() const { return Vec4Double(this->x, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::XZYY() const { return Vec4Double(this->x, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::XZYZ() const { return Vec4Double(this->x, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::XZYW() const { return Vec4Double(this->x, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::XZZX() const { return Vec4Double(this->x, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::XZZY() const { return Vec4Double(this->x, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::XZZZ() const { return Vec4Double(this->x, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::XZZW() const { return Vec4Double(this->x, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::XZWX() const { return Vec4Double(this->x, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::XZWY() const { return Vec4Double(this->x, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::XZWZ() const { return Vec4Double(this->x, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::XZWW() const { return Vec4Double(this->x, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::XWXX() const { return Vec4Double(this->x, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::XWXY() const { return Vec4Double(this->x, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::XWXZ() const { return Vec4Double(this->x, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::XWXW() const { return Vec4Double(this->x, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::XWYX() const { return Vec4Double(this->x, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::XWYY() const { return Vec4Double(this->x, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::XWYZ() const { return Vec4Double(this->x, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::XWYW() const { return Vec4Double(this->x, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::XWZX() const { return Vec4Double(this->x, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::XWZY() const { return Vec4Double(this->x, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::XWZZ() const { return Vec4Double(this->x, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::XWZW() const { return Vec4Double(this->x, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::XWWX() const { return Vec4Double(this->x, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::XWWY() const { return Vec4Double(this->x, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::XWWZ() const { return Vec4Double(this->x, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::XWWW() const { return Vec4Double(this->x, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::YXXX() const { return Vec4Double(this->y, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::YXXY() const { return Vec4Double(this->y, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::YXXZ() const { return Vec4Double(this->y, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::YXXW() const { return Vec4Double(this->y, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::YXYX() const { return Vec4Double(this->y, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::YXYY() const { return Vec4Double(this->y, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::YXYZ() const { return Vec4Double(this->y, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::YXYW() const { return Vec4Double(this->y, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::YXZX() const { return Vec4Double(this->y, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::YXZY() const { return Vec4Double(this->y, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::YXZZ() const { return Vec4Double(this->y, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::YXZW() const { return Vec4Double(this->y, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::YXWX() const { return Vec4Double(this->y, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::YXWY() const { return Vec4Double(this->y, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::YXWZ() const { return Vec4Double(this->y, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::YXWW() const { return Vec4Double(this->y, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::YYXX() const { return Vec4Double(this->y, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::YYXY() const { return Vec4Double(this->y, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::YYXZ() const { return Vec4Double(this->y, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::YYXW() const { return Vec4Double(this->y, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::YYYX() const { return Vec4Double(this->y, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::YYYY() const { return Vec4Double(this->y, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::YYYZ() const { return Vec4Double(this->y, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::YYYW() const { return Vec4Double(this->y, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::YYZX() const { return Vec4Double(this->y, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::YYZY() const { return Vec4Double(this->y, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::YYZZ() const { return Vec4Double(this->y, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::YYZW() const { return Vec4Double(this->y, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::YYWX() const { return Vec4Double(this->y, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::YYWY() const { return Vec4Double(this->y, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::YYWZ() const { return Vec4Double(this->y, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::YYWW() const { return Vec4Double(this->y, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::YZXX() const { return Vec4Double(this->y, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::YZXY() const { return Vec4Double(this->y, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::YZXZ() const { return Vec4Double(this->y, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::YZXW() const { return Vec4Double(this->y, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::YZYX() const { return Vec4Double(this->y, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::YZYY() const { return Vec4Double(this->y, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::YZYZ() const { return Vec4Double(this->y, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::YZYW() const { return Vec4Double(this->y, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::YZZX() const { return Vec4Double(this->y, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::YZZY() const { return Vec4Double(this->y, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::YZZZ() const { return Vec4Double(this->y, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::YZZW() const { return Vec4Double(this->y, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::YZWX() const { return Vec4Double(this->y, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::YZWY() const { return Vec4Double(this->y, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::YZWZ() const { return Vec4Double(this->y, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::YZWW() const { return Vec4Double(this->y, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::YWXX() const { return Vec4Double(this->y, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::YWXY() const { return Vec4Double(this->y, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::YWXZ() const { return Vec4Double(this->y, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::YWXW() const { return Vec4Double(this->y, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::YWYX() const { return Vec4Double(this->y, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::YWYY() const { return Vec4Double(this->y, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::YWYZ() const { return Vec4Double(this->y, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::YWYW() const { return Vec4Double(this->y, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::YWZX() const { return Vec4Double(this->y, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::YWZY() const { return Vec4Double(this->y, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::YWZZ() const { return Vec4Double(this->y, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::YWZW() const { return Vec4Double(this->y, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::YWWX() const { return Vec4Double(this->y, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::YWWY() const { return Vec4Double(this->y, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::YWWZ() const { return Vec4Double(this->y, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::YWWW() const { return Vec4Double(this->y, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::ZXXX() const { return Vec4Double(this->z, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::ZXXY() const { return Vec4Double(this->z, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::ZXXZ() const { return Vec4Double(this->z, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::ZXXW() const { return Vec4Double(this->z, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::ZXYX() const { return Vec4Double(this->z, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::ZXYY() const { return Vec4Double(this->z, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::ZXYZ() const { return Vec4Double(this->z, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::ZXYW() const { return Vec4Double(this->z, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::ZXZX() const { return Vec4Double(this->z, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::ZXZY() const { return Vec4Double(this->z, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::ZXZZ() const { return Vec4Double(this->z, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::ZXZW() const { return Vec4Double(this->z, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::ZXWX() const { return Vec4Double(this->z, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::ZXWY() const { return Vec4Double(this->z, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::ZXWZ() const { return Vec4Double(this->z, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::ZXWW() const { return Vec4Double(this->z, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::ZYXX() const { return Vec4Double(this->z, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::ZYXY() const { return Vec4Double(this->z, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::ZYXZ() const { return Vec4Double(this->z, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::ZYXW() const { return Vec4Double(this->z, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::ZYYX() const { return Vec4Double(this->z, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::ZYYY() const { return Vec4Double(this->z, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::ZYYZ() const { return Vec4Double(this->z, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::ZYYW() const { return Vec4Double(this->z, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::ZYZX() const { return Vec4Double(this->z, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::ZYZY() const { return Vec4Double(this->z, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::ZYZZ() const { return Vec4Double(this->z, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::ZYZW() const { return Vec4Double(this->z, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::ZYWX() const { return Vec4Double(this->z, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::ZYWY() const { return Vec4Double(this->z, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::ZYWZ() const { return Vec4Double(this->z, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::ZYWW() const { return Vec4Double(this->z, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::ZZXX() const { return Vec4Double(this->z, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::ZZXY() const { return Vec4Double(this->z, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::ZZXZ() const { return Vec4Double(this->z, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::ZZXW() const { return Vec4Double(this->z, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::ZZYX() const { return Vec4Double(this->z, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::ZZYY() const { return Vec4Double(this->z, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::ZZYZ() const { return Vec4Double(this->z, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::ZZYW() const { return Vec4Double(this->z, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::ZZZX() const { return Vec4Double(this->z, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::ZZZY() const { return Vec4Double(this->z, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::ZZZZ() const { return Vec4Double(this->z, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::ZZZW() const { return Vec4Double(this->z, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::ZZWX() const { return Vec4Double(this->z, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::ZZWY() const { return Vec4Double(this->z, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::ZZWZ() const { return Vec4Double(this->z, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::ZZWW() const { return Vec4Double(this->z, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::ZWXX() const { return Vec4Double(this->z, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::ZWXY() const { return Vec4Double(this->z, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::ZWXZ() const { return Vec4Double(this->z, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::ZWXW() const { return Vec4Double(this->z, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::ZWYX() const { return Vec4Double(this->z, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::ZWYY() const { return Vec4Double(this->z, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::ZWYZ() const { return Vec4Double(this->z, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::ZWYW() const { return Vec4Double(this->z, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::ZWZX() const { return Vec4Double(this->z, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::ZWZY() const { return Vec4Double(this->z, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::ZWZZ() const { return Vec4Double(this->z, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::ZWZW() const { return Vec4Double(this->z, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::ZWWX() const { return Vec4Double(this->z, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::ZWWY() const { return Vec4Double(this->z, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::ZWWZ() const { return Vec4Double(this->z, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::ZWWW() const { return Vec4Double(this->z, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::WXXX() const { return Vec4Double(this->w, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::WXXY() const { return Vec4Double(this->w, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::WXXZ() const { return Vec4Double(this->w, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::WXXW() const { return Vec4Double(this->w, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::WXYX() const { return Vec4Double(this->w, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::WXYY() const { return Vec4Double(this->w, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::WXYZ() const { return Vec4Double(this->w, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::WXYW() const { return Vec4Double(this->w, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::WXZX() const { return Vec4Double(this->w, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::WXZY() const { return Vec4Double(this->w, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::WXZZ() const { return Vec4Double(this->w, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::WXZW() const { return Vec4Double(this->w, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::WXWX() const { return Vec4Double(this->w, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::WXWY() const { return Vec4Double(this->w, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::WXWZ() const { return Vec4Double(this->w, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::WXWW() const { return Vec4Double(this->w, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::WYXX() const { return Vec4Double(this->w, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::WYXY() const { return Vec4Double(this->w, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::WYXZ() const { return Vec4Double(this->w, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::WYXW() const { return Vec4Double(this->w, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::WYYX() const { return Vec4Double(this->w, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::WYYY() const { return Vec4Double(this->w, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::WYYZ() const { return Vec4Double(this->w, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::WYYW() const { return Vec4Double(this->w, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::WYZX() const { return Vec4Double(this->w, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::WYZY() const { return Vec4Double(this->w, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::WYZZ() const { return Vec4Double(this->w, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::WYZW() const { return Vec4Double(this->w, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::WYWX() const { return Vec4Double(this->w, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::WYWY() const { return Vec4Double(this->w, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::WYWZ() const { return Vec4Double(this->w, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::WYWW() const { return Vec4Double(this->w, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::WZXX() const { return Vec4Double(this->w, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::WZXY() const { return Vec4Double(this->w, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::WZXZ() const { return Vec4Double(this->w, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::WZXW() const { return Vec4Double(this->w, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::WZYX() const { return Vec4Double(this->w, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::WZYY() const { return Vec4Double(this->w, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::WZYZ() const { return Vec4Double(this->w, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::WZYW() const { return Vec4Double(this->w, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::WZZX() const { return Vec4Double(this->w, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::WZZY() const { return Vec4Double(this->w, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::WZZZ() const { return Vec4Double(this->w, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::WZZW() const { return Vec4Double(this->w, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::WZWX() const { return Vec4Double(this->w, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::WZWY() const { return Vec4Double(this->w, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::WZWZ() const { return Vec4Double(this->w, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::WZWW() const { return Vec4Double(this->w, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::WWXX() const { return Vec4Double(this->w, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::WWXY() const { return Vec4Double(this->w, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::WWXZ() const { return Vec4Double(this->w, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::WWXW() const { return Vec4Double(this->w, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::WWYX() const { return Vec4Double(this->w, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::WWYY() const { return Vec4Double(this->w, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::WWYZ() const { return Vec4Double(this->w, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::WWYW() const { return Vec4Double(this->w, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::WWZX() const { return Vec4Double(this->w, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::WWZY() const { return Vec4Double(this->w, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::WWZZ() const { return Vec4Double(this->w, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::WWZW() const { return Vec4Double(this->w, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::WWWX() const { return Vec4Double(this->w, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::WWWY() const { return Vec4Double(this->w, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::WWWZ() const { return Vec4Double(this->w, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::WWWW() const { return Vec4Double(this->w, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::RRRR() const { return Vec4Double(this->x, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::RRRG() const { return Vec4Double(this->x, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::RRRB() const { return Vec4Double(this->x, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::RRRA() const { return Vec4Double(this->x, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::RRGR() const { return Vec4Double(this->x, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::RRGG() const { return Vec4Double(this->x, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::RRGB() const { return Vec4Double(this->x, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::RRGA() const { return Vec4Double(this->x, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::RRBR() const { return Vec4Double(this->x, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::RRBG() const { return Vec4Double(this->x, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::RRBB() const { return Vec4Double(this->x, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::RRBA() const { return Vec4Double(this->x, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::RRAR() const { return Vec4Double(this->x, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::RRAG() const { return Vec4Double(this->x, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::RRAB() const { return Vec4Double(this->x, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::RRAA() const { return Vec4Double(this->x, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::RGRR() const { return Vec4Double(this->x, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::RGRG() const { return Vec4Double(this->x, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::RGRB() const { return Vec4Double(this->x, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::RGRA() const { return Vec4Double(this->x, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::RGGR() const { return Vec4Double(this->x, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::RGGG() const { return Vec4Double(this->x, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::RGGB() const { return Vec4Double(this->x, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::RGGA() const { return Vec4Double(this->x, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::RGBR() const { return Vec4Double(this->x, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::RGBG() const { return Vec4Double(this->x, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::RGBB() const { return Vec4Double(this->x, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::RGAR() const { return Vec4Double(this->x, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::RGAG() const { return Vec4Double(this->x, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::RGAB() const { return Vec4Double(this->x, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::RGAA() const { return Vec4Double(this->x, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::RBRR() const { return Vec4Double(this->x, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::RBRG() const { return Vec4Double(this->x, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::RBRB() const { return Vec4Double(this->x, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::RBRA() const { return Vec4Double(this->x, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::RBGR() const { return Vec4Double(this->x, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::RBGG() const { return Vec4Double(this->x, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::RBGB() const { return Vec4Double(this->x, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::RBGA() const { return Vec4Double(this->x, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::RBBR() const { return Vec4Double(this->x, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::RBBG() const { return Vec4Double(this->x, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::RBBB() const { return Vec4Double(this->x, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::RBBA() const { return Vec4Double(this->x, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::RBAR() const { return Vec4Double(this->x, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::RBAG() const { return Vec4Double(this->x, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::RBAB() const { return Vec4Double(this->x, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::RBAA() const { return Vec4Double(this->x, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::RARR() const { return Vec4Double(this->x, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::RARG() const { return Vec4Double(this->x, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::RARB() const { return Vec4Double(this->x, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::RARA() const { return Vec4Double(this->x, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::RAGR() const { return Vec4Double(this->x, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::RAGG() const { return Vec4Double(this->x, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::RAGB() const { return Vec4Double(this->x, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::RAGA() const { return Vec4Double(this->x, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::RABR() const { return Vec4Double(this->x, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::RABG() const { return Vec4Double(this->x, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::RABB() const { return Vec4Double(this->x, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::RABA() const { return Vec4Double(this->x, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::RAAR() const { return Vec4Double(this->x, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::RAAG() const { return Vec4Double(this->x, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::RAAB() const { return Vec4Double(this->x, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::RAAA() const { return Vec4Double(this->x, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::GRRR() const { return Vec4Double(this->y, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::GRRG() const { return Vec4Double(this->y, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::GRRB() const { return Vec4Double(this->y, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::GRRA() const { return Vec4Double(this->y, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::GRGR() const { return Vec4Double(this->y, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::GRGG() const { return Vec4Double(this->y, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::GRGB() const { return Vec4Double(this->y, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::GRGA() const { return Vec4Double(this->y, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::GRBR() const { return Vec4Double(this->y, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::GRBG() const { return Vec4Double(this->y, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::GRBB() const { return Vec4Double(this->y, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::GRBA() const { return Vec4Double(this->y, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::GRAR() const { return Vec4Double(this->y, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::GRAG() const { return Vec4Double(this->y, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::GRAB() const { return Vec4Double(this->y, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::GRAA() const { return Vec4Double(this->y, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::GGRR() const { return Vec4Double(this->y, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::GGRG() const { return Vec4Double(this->y, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::GGRB() const { return Vec4Double(this->y, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::GGRA() const { return Vec4Double(this->y, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::GGGR() const { return Vec4Double(this->y, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::GGGG() const { return Vec4Double(this->y, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::GGGB() const { return Vec4Double(this->y, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::GGGA() const { return Vec4Double(this->y, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::GGBR() const { return Vec4Double(this->y, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::GGBG() const { return Vec4Double(this->y, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::GGBB() const { return Vec4Double(this->y, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::GGBA() const { return Vec4Double(this->y, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::GGAR() const { return Vec4Double(this->y, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::GGAG() const { return Vec4Double(this->y, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::GGAB() const { return Vec4Double(this->y, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::GGAA() const { return Vec4Double(this->y, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::GBRR() const { return Vec4Double(this->y, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::GBRG() const { return Vec4Double(this->y, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::GBRB() const { return Vec4Double(this->y, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::GBRA() const { return Vec4Double(this->y, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::GBGR() const { return Vec4Double(this->y, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::GBGG() const { return Vec4Double(this->y, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::GBGB() const { return Vec4Double(this->y, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::GBGA() const { return Vec4Double(this->y, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::GBBR() const { return Vec4Double(this->y, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::GBBG() const { return Vec4Double(this->y, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::GBBB() const { return Vec4Double(this->y, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::GBBA() const { return Vec4Double(this->y, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::GBAR() const { return Vec4Double(this->y, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::GBAG() const { return Vec4Double(this->y, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::GBAB() const { return Vec4Double(this->y, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::GBAA() const { return Vec4Double(this->y, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::GARR() const { return Vec4Double(this->y, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::GARG() const { return Vec4Double(this->y, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::GARB() const { return Vec4Double(this->y, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::GARA() const { return Vec4Double(this->y, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::GAGR() const { return Vec4Double(this->y, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::GAGG() const { return Vec4Double(this->y, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::GAGB() const { return Vec4Double(this->y, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::GAGA() const { return Vec4Double(this->y, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::GABR() const { return Vec4Double(this->y, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::GABG() const { return Vec4Double(this->y, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::GABB() const { return Vec4Double(this->y, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::GABA() const { return Vec4Double(this->y, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::GAAR() const { return Vec4Double(this->y, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::GAAG() const { return Vec4Double(this->y, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::GAAB() const { return Vec4Double(this->y, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::GAAA() const { return Vec4Double(this->y, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::BRRR() const { return Vec4Double(this->z, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::BRRG() const { return Vec4Double(this->z, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::BRRB() const { return Vec4Double(this->z, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::BRRA() const { return Vec4Double(this->z, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::BRGR() const { return Vec4Double(this->z, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::BRGG() const { return Vec4Double(this->z, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::BRGB() const { return Vec4Double(this->z, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::BRGA() const { return Vec4Double(this->z, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::BRBR() const { return Vec4Double(this->z, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::BRBG() const { return Vec4Double(this->z, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::BRBB() const { return Vec4Double(this->z, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::BRBA() const { return Vec4Double(this->z, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::BRAR() const { return Vec4Double(this->z, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::BRAG() const { return Vec4Double(this->z, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::BRAB() const { return Vec4Double(this->z, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::BRAA() const { return Vec4Double(this->z, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::BGRR() const { return Vec4Double(this->z, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::BGRG() const { return Vec4Double(this->z, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::BGRB() const { return Vec4Double(this->z, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::BGRA() const { return Vec4Double(this->z, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::BGGR() const { return Vec4Double(this->z, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::BGGG() const { return Vec4Double(this->z, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::BGGB() const { return Vec4Double(this->z, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::BGGA() const { return Vec4Double(this->z, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::BGBR() const { return Vec4Double(this->z, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::BGBG() const { return Vec4Double(this->z, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::BGBB() const { return Vec4Double(this->z, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::BGBA() const { return Vec4Double(this->z, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::BGAR() const { return Vec4Double(this->z, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::BGAG() const { return Vec4Double(this->z, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::BGAB() const { return Vec4Double(this->z, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::BGAA() const { return Vec4Double(this->z, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::BBRR() const { return Vec4Double(this->z, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::BBRG() const { return Vec4Double(this->z, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::BBRB() const { return Vec4Double(this->z, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::BBRA() const { return Vec4Double(this->z, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::BBGR() const { return Vec4Double(this->z, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::BBGG() const { return Vec4Double(this->z, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::BBGB() const { return Vec4Double(this->z, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::BBGA() const { return Vec4Double(this->z, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::BBBR() const { return Vec4Double(this->z, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::BBBG() const { return Vec4Double(this->z, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::BBBB() const { return Vec4Double(this->z, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::BBBA() const { return Vec4Double(this->z, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::BBAR() const { return Vec4Double(this->z, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::BBAG() const { return Vec4Double(this->z, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::BBAB() const { return Vec4Double(this->z, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::BBAA() const { return Vec4Double(this->z, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::BARR() const { return Vec4Double(this->z, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::BARG() const { return Vec4Double(this->z, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::BARB() const { return Vec4Double(this->z, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::BARA() const { return Vec4Double(this->z, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::BAGR() const { return Vec4Double(this->z, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::BAGG() const { return Vec4Double(this->z, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::BAGB() const { return Vec4Double(this->z, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::BAGA() const { return Vec4Double(this->z, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::BABR() const { return Vec4Double(this->z, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::BABG() const { return Vec4Double(this->z, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::BABB() const { return Vec4Double(this->z, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::BABA() const { return Vec4Double(this->z, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::BAAR() const { return Vec4Double(this->z, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::BAAG() const { return Vec4Double(this->z, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::BAAB() const { return Vec4Double(this->z, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::BAAA() const { return Vec4Double(this->z, this->w, this->w, this->w); }
inline Vec4Double Vec4Double::ARRR() const { return Vec4Double(this->w, this->x, this->x, this->x); }
inline Vec4Double Vec4Double::ARRG() const { return Vec4Double(this->w, this->x, this->x, this->y); }
inline Vec4Double Vec4Double::ARRB() const { return Vec4Double(this->w, this->x, this->x, this->z); }
inline Vec4Double Vec4Double::ARRA() const { return Vec4Double(this->w, this->x, this->x, this->w); }
inline Vec4Double Vec4Double::ARGR() const { return Vec4Double(this->w, this->x, this->y, this->x); }
inline Vec4Double Vec4Double::ARGG() const { return Vec4Double(this->w, this->x, this->y, this->y); }
inline Vec4Double Vec4Double::ARGB() const { return Vec4Double(this->w, this->x, this->y, this->z); }
inline Vec4Double Vec4Double::ARGA() const { return Vec4Double(this->w, this->x, this->y, this->w); }
inline Vec4Double Vec4Double::ARBR() const { return Vec4Double(this->w, this->x, this->z, this->x); }
inline Vec4Double Vec4Double::ARBG() const { return Vec4Double(this->w, this->x, this->z, this->y); }
inline Vec4Double Vec4Double::ARBB() const { return Vec4Double(this->w, this->x, this->z, this->z); }
inline Vec4Double Vec4Double::ARBA() const { return Vec4Double(this->w, this->x, this->z, this->w); }
inline Vec4Double Vec4Double::ARAR() const { return Vec4Double(this->w, this->x, this->w, this->x); }
inline Vec4Double Vec4Double::ARAG() const { return Vec4Double(this->w, this->x, this->w, this->y); }
inline Vec4Double Vec4Double::ARAB() const { return Vec4Double(this->w, this->x, this->w, this->z); }
inline Vec4Double Vec4Double::ARAA() const { return Vec4Double(this->w, this->x, this->w, this->w); }
inline Vec4Double Vec4Double::AGRR() const { return Vec4Double(this->w, this->y, this->x, this->x); }
inline Vec4Double Vec4Double::AGRG() const { return Vec4Double(this->w, this->y, this->x, this->y); }
inline Vec4Double Vec4Double::AGRB() const { return Vec4Double(this->w, this->y, this->x, this->z); }
inline Vec4Double Vec4Double::AGRA() const { return Vec4Double(this->w, this->y, this->x, this->w); }
inline Vec4Double Vec4Double::AGGR() const { return Vec4Double(this->w, this->y, this->y, this->x); }
inline Vec4Double Vec4Double::AGGG() const { return Vec4Double(this->w, this->y, this->y, this->y); }
inline Vec4Double Vec4Double::AGGB() const { return Vec4Double(this->w, this->y, this->y, this->z); }
inline Vec4Double Vec4Double::AGGA() const { return Vec4Double(this->w, this->y, this->y, this->w); }
inline Vec4Double Vec4Double::AGBR() const { return Vec4Double(this->w, this->y, this->z, this->x); }
inline Vec4Double Vec4Double::AGBG() const { return Vec4Double(this->w, this->y, this->z, this->y); }
inline Vec4Double Vec4Double::AGBB() const { return Vec4Double(this->w, this->y, this->z, this->z); }
inline Vec4Double Vec4Double::AGBA() const { return Vec4Double(this->w, this->y, this->z, this->w); }
inline Vec4Double Vec4Double::AGAR() const { return Vec4Double(this->w, this->y, this->w, this->x); }
inline Vec4Double Vec4Double::AGAG() const { return Vec4Double(this->w, this->y, this->w, this->y); }
inline Vec4Double Vec4Double::AGAB() const { return Vec4Double(this->w, this->y, this->w, this->z); }
inline Vec4Double Vec4Double::AGAA() const { return Vec4Double(this->w, this->y, this->w, this->w); }
inline Vec4Double Vec4Double::ABRR() const { return Vec4Double(this->w, this->z, this->x, this->x); }
inline Vec4Double Vec4Double::ABRG() const { return Vec4Double(this->w, this->z, this->x, this->y); }
inline Vec4Double Vec4Double::ABRB() const { return Vec4Double(this->w, this->z, this->x, this->z); }
inline Vec4Double Vec4Double::ABRA() const { return Vec4Double(this->w, this->z, this->x, this->w); }
inline Vec4Double Vec4Double::ABGR() const { return Vec4Double(this->w, this->z, this->y, this->x); }
inline Vec4Double Vec4Double::ABGG() const { return Vec4Double(this->w, this->z, this->y, this->y); }
inline Vec4Double Vec4Double::ABGB() const { return Vec4Double(this->w, this->z, this->y, this->z); }
inline Vec4Double Vec4Double::ABGA() const { return Vec4Double(this->w, this->z, this->y, this->w); }
inline Vec4Double Vec4Double::ABBR() const { return Vec4Double(this->w, this->z, this->z, this->x); }
inline Vec4Double Vec4Double::ABBG() const { return Vec4Double(this->w, this->z, this->z, this->y); }
inline Vec4Double Vec4Double::ABBB() const { return Vec4Double(this->w, this->z, this->z, this->z); }
inline Vec4Double Vec4Double::ABBA() const { return Vec4Double(this->w, this->z, this->z, this->w); }
inline Vec4Double Vec4Double::ABAR() const { return Vec4Double(this->w, this->z, this->w, this->x); }
inline Vec4Double Vec4Double::ABAG() const { return Vec4Double(this->w, this->z, this->w, this->y); }
inline Vec4Double Vec4Double::ABAB() const { return Vec4Double(this->w, this->z, this->w, this->z); }
inline Vec4Double Vec4Double::ABAA() const { return Vec4Double(this->w, this->z, this->w, this->w); }
inline Vec4Double Vec4Double::AARR() const { return Vec4Double(this->w, this->w, this->x, this->x); }
inline Vec4Double Vec4Double::AARG() const { return Vec4Double(this->w, this->w, this->x, this->y); }
inline Vec4Double Vec4Double::AARB() const { return Vec4Double(this->w, this->w, this->x, this->z); }
inline Vec4Double Vec4Double::AARA() const { return Vec4Double(this->w, this->w, this->x, this->w); }
inline Vec4Double Vec4Double::AAGR() const { return Vec4Double(this->w, this->w, this->y, this->x); }
inline Vec4Double Vec4Double::AAGG() const { return Vec4Double(this->w, this->w, this->y, this->y); }
inline Vec4Double Vec4Double::AAGB() const { return Vec4Double(this->w, this->w, this->y, this->z); }
inline Vec4Double Vec4Double::AAGA() const { return Vec4Double(this->w, this->w, this->y, this->w); }
inline Vec4Double Vec4Double::AABR() const { return Vec4Double(this->w, this->w, this->z, this->x); }
inline Vec4Double Vec4Double::AABG() const { return Vec4Double(this->w, this->w, this->z, this->y); }
inline Vec4Double Vec4Double::AABB() const { return Vec4Double(this->w, this->w, this->z, this->z); }
inline Vec4Double Vec4Double::AABA() const { return Vec4Double(this->w, this->w, this->z, this->w); }
inline Vec4Double Vec4Double::AAAR() const { return Vec4Double(this->w, this->w, this->w, this->x); }
inline Vec4Double Vec4Double::AAAG() const { return Vec4Double(this->w, this->w, this->w, this->y); }
inline Vec4Double Vec4Double::AAAB() const { return Vec4Double(this->w, this->w, this->w, this->z); }
inline Vec4Double Vec4Double::AAAA() const { return Vec4Double(this->w, this->w, this->w, this->w); }

#pragma endregion

#pragma endregion

#pragma region IntegerVectors

#pragma region Vec2



#pragma endregion

#pragma region Vec3



#pragma endregion

#pragma region Vec4



#pragma endregion

#pragma endregion