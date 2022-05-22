
#include <math.h>
#include <cassert>

#include "Vector.h"

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
	return this->x < _other.x && this->y < _other.y;
}

inline bool Vec2::operator>(const Vec2& _other) const {
	return this->x > _other.x && this->y > _other.y;
}

inline bool Vec2::operator<=(const Vec2& _other) const {
	return this->x <= _other.x && this->y <= _other.y;
}

inline bool Vec2::operator>=(const Vec2& _other) const {
	return this->x >= _other.x && this->y >= _other.y;
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

	this->x /= len;
	this->y /= len;
}

inline Vec2 Vec2::Normalized() const {
	float len = Length();

	return Vec2(this->x / len, this->x / len);
}

inline float Vec2::AngleBetween(const Vec2& _other) const {
	return acosf(Normalized() * _other.Normalized());
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



#pragma endregion

#pragma region Vec4



#pragma endregion