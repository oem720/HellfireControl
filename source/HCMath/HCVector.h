
#ifndef VECTOR_LIBRARY_HEADER
#define VECTOR_LIBRARY_HEADER

class alignas(8) Vec2 {
private:
	union {
		float xy[2];											//Array Storage
		struct {
			float x;											//X Member
			float y;											//Y Member
		};
	};
public:
	//Constructors
	inline Vec2();												//Init to Zero
	inline Vec2(float _x, float _y);							//Init to X and Y
	inline Vec2(const Vec2& _other);							//Init from Copy

	//Assignment
	inline Vec2& operator=(const Vec2& _other);					//Assignment
	inline Vec2& operator+=(const Vec2& _other);				//Addition
	inline Vec2& operator-=(const Vec2& _other);				//Subtraction
	inline Vec2& operator*=(const float _scale);				//Scaling
	inline float& operator[](int _ndx);							//Array access (Modifiable)
	inline float operator[](int _ndx) const;					//Array access (Const)

	//Arithmetic
	inline Vec2 operator+(const Vec2& _other) const;			//Addition
	inline Vec2 operator-(const Vec2& _other) const;			//Subtraction
	inline Vec2 operator*(const float _scale) const;			//Scaling
	inline float operator*(const Vec2& _other) const;			//Dot Product
	inline float operator&(const Vec2& _other) const;			//Cross Product
	inline Vec2 operator~() const;								//Zero
	inline Vec2 operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec2& _other) const;			//Check Equality
	inline bool operator<(const Vec2& _other) const;			//Check Less Than
	inline bool operator>(const Vec2& _other) const;			//Check Greater Than
	inline bool operator<=(const Vec2& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec2& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec2& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;								//Vector Length
	inline float LengthSquared() const;							//Vector Length Squared
	inline void Normalize();									//Vector Normalize
	inline Vec2 Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec2& _other) const;		//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline float Dot(const Vec2& _other) const;					//Dot Product
	inline float Cross(const Vec2& _other) const;				//Cross Product
	inline void Add(const Vec2& _other);						//Addition
	inline void Subtract(const Vec2& _other);					//Subtraction
	inline void Scale(const float _scale);						//Scaling
	inline void Negate();										//Negate
	inline void Zero();											//Zero
	inline bool Equals(const Vec2& _other) const;				//Check Equality
	inline bool Less(const Vec2& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec2& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec2& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec2& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec2& _other) const;			//Check Not Equal

	//Member Modification
	inline float& X();											//Vector X Component (Modifiable)
	inline float X() const;										//Vector X Component (Const)
	inline float& Y();											//Vector Y Component (Modifiable)
	inline float Y() const;										//Vector Y Component (Const)

	//Swizzle Operations
	inline Vec2 XX() const;										//Swizzle to XX Vector
	inline Vec2 YY() const;										//Swizzle to YY Vector
	inline Vec2 RR() const;										//Swizzle to RR Vector
	inline Vec2 GG() const;										//Swizzle to GG Vector
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