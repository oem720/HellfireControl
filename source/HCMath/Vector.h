
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