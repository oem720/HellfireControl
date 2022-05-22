
#ifndef VECTOR_LIBRARY_HEADER
#define VECTOR_LIBRARY_HEADER

class alignas(8) Vec2 {
private:
	union {
		float xy[2];
		struct {
			float x;
			float y;
		};
	};
public:
	inline Vec2();
	inline Vec2(float _x, float _y);
	inline Vec2(const Vec2& _other);
	inline Vec2& operator=(const Vec2& _other);
	inline Vec2 operator+(const Vec2& _other) const;
	inline Vec2& operator+=(const Vec2& _other);
	inline Vec2 operator-(const Vec2& _other) const;
	inline Vec2& operator-=(const Vec2& _other);
	inline Vec2 operator*(const float _scale) const;
	inline Vec2& operator*=(const float _scale);
	inline float operator*(const Vec2& _other) const;
	inline float operator*=(const Vec2& _other);
	inline float operator&(const Vec2& _other) const;
	inline float operator&=(const Vec2& _other);
	inline Vec2 operator~() const;
	inline Vec2 operator-() const;
	inline bool operator==(const Vec2& _other) const;
	inline bool operator<(const Vec2& _other) const;
	inline bool operator>(const Vec2& _other) const;
	inline bool operator<=(const Vec2& _other) const;
	inline bool operator>=(const Vec2& _other) const;
	inline bool operator!=(const Vec2& _other) const;
	inline float AngleBetween(const Vec2& _other) const;
	inline float Dot(const Vec2& _other) const;
	inline float Cross(const Vec2& _other) const;
	inline Vec2 Add(const Vec2& _other) const;
	inline Vec2 Subtract(const Vec2& _other) const;
	inline Vec2 Scale(const Vec2& _other) const;
	inline void Negate() const;
	inline bool Equals(const Vec2& _other) const;
	inline bool Less(const Vec2& _other) const;
	inline bool LessThanOrEquals(const Vec2& _other) const;
	inline bool Greater(const Vec2& _other) const;
	inline bool GreaterThanOrEquals(const Vec2& _other) const;
	inline bool NotEquals(const Vec2& _other) const;
	inline float& X();
	inline float& Y();
	inline Vec2 XX() const;
	inline Vec2 YY() const;
	inline Vec2 RR() const;
	inline Vec2 GG() const;
};

class alignas(16) Vec3 {
private:
	union {
		float xyz[3];
		struct {
			float x;
			float y;
			float z;
		};
	};
public:

};

class alignas(16) Vec4 {
private:
	union {
		float xyzw[4];
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
public:

};
#endif