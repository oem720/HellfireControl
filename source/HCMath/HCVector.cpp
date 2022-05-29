
#include <math.h>
#include <cassert>

#include "HCVector.h"

#pragma region Vec2

inline Vec2::Vec2() : x(0.0f), y(0.0f) {}

inline Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

inline Vec2::Vec2(const Vec2& _other) {
	*this = _other;
}

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
	return this->Length() < _other.Length();
}

inline bool Vec2::operator>(const Vec2& _other) const {
	return this->Length() > _other.Length();
}

inline bool Vec2::operator<=(const Vec2& _other) const {
	return this->Length() <= _other.Length();
}

inline bool Vec2::operator>=(const Vec2& _other) const {
	return this->Length() >= _other.Length();
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
	return (*this) * _other;
}

inline float Vec2::Cross(const Vec2& _other) const {
	return (*this) & _other;
}

inline void Vec2::Add(const Vec2& _other) {
	(*this) += _other;
}

inline void Vec2::Subtract(const Vec2& _other) {
	(*this) -= _other;
}

inline void Vec2::Scale(const float _scale) {
	(*this) *= _scale;
}

inline void Vec2::Zero() {
	(*this) = ~(*this);
}

inline void Vec2::Negate() {
	(*this) = -(*this);
}

inline bool Vec2::Equals(const Vec2& _other) const {
	return (*this) == _other;
}

inline bool Vec2::Less(const Vec2& _other) const {
	return (*this) < _other;
}

inline bool Vec2::LessThanOrEquals(const Vec2& _other) const {
	return (*this) <= _other;
}

inline bool Vec2::Greater(const Vec2& _other) const {
	return (*this) > _other;
}

inline bool Vec2::GreaterThanOrEquals(const Vec2& _other) const {
	return (*this) >= _other;
}

inline bool Vec2::NotEquals(const Vec2& _other) const {
	return (*this) != _other;
}

inline float& Vec2::X() {
	return x;
}

inline float Vec2::X() const {
	return x;
}

inline float& Vec2::Y() {
	return y;
}

inline float Vec2::Y() const {
	return y;
}

inline Vec2 Vec2::XX() const {
	return Vec2(x, x);
}

inline Vec2 Vec2::YY() const {
	return Vec2(y, y);
}

inline Vec2 Vec2::RR() const {
	return Vec2(x, x);
}

inline Vec2 Vec2::GG() const {
	return Vec2(y, y);
}

#pragma endregion

#pragma region Vec3

inline Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

inline Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

inline Vec3::Vec3(const Vec2& _xy, float _z) : x(_xy.X()), y(_xy.Y()), z(_z) {}

inline Vec3::Vec3(float _x, const Vec2& _yz) : x(_x), y(_yz.X()), z(_yz.Y()) {}

inline Vec3::Vec3(const Vec3& _other) {
	*this = _other;
}

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
	return this->Length() < _other.Length();
}

inline bool Vec3::operator>(const Vec3& _other) const {
	return this->Length() > _other.Length();
}

inline bool Vec3::operator<=(const Vec3& _other) const {
	return this->Length() <= _other.Length();
}

inline bool Vec3::operator>=(const Vec3& _other) const {
	return this->Length() >= _other.Length();
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
	return (*this) * _other;
}

inline void Vec3::Cross(const Vec3& _other) {
	(*this) &= _other;
}

inline void Vec3::Add(const Vec3& _other) {
	(*this) += _other;
}

inline void Vec3::Subtract(const Vec3& _other) {
	(*this) -= _other;
}

inline void Vec3::Scale(const float _scale) {
	(*this) *= _scale;
}

inline void Vec3::Negate() {
	(*this) = -(*this);
}

inline void Vec3::Zero() {
	(*this) = ~(*this);
}

inline bool Vec3::Equals(const Vec3& _other) const {
	return (*this) == _other;
}

inline bool Vec3::Less(const Vec3& _other) const {
	return (*this) < _other;
}

inline bool Vec3::LessThanOrEquals(const Vec3& _other) const {
	return (*this) <= _other;
}

inline bool Vec3::Greater(const Vec3& _other) const {
	return (*this) > _other;
}

inline bool Vec3::GreaterThanOrEquals(const Vec3& _other) const {
	return (*this) >= _other;
}

inline bool Vec3::NotEquals(const Vec3& _other) const {
	return (*this) != _other;
}

inline float& Vec3::X() {
	return this->x;
}

inline float Vec3::X() const {
	return this->x;
}

inline float& Vec3::Y() {
	return this->y;
}

inline float Vec3::Y() const {
	return this->y;
}

inline float& Vec3::Z() {
	return this->z;
}

inline float Vec3::Z() const {
	return this->z;
}

#pragma endregion

#pragma region Vec4



#pragma endregion