
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
	if (len == 0.0f) return;

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

#pragma endregion

#pragma region Vec3

#pragma endregion

#pragma region Vec4

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

#pragma region LongVectors
#pragma region Vec2

#pragma endregion

#pragma region Vec3

#pragma endregion

#pragma region Vec4

#pragma endregion
#pragma endregion