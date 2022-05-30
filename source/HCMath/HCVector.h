
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

	//Swizzle Operations (Vec2)
	inline Vec2 XX() const;										//Swizzle to XX Vector
	inline Vec2 YY() const;										//Swizzle to YY Vector
	inline Vec2 YX() const;										//Swizzle to YX Vector
	inline Vec2 RR() const;										//Swizzle to RR Vector
	inline Vec2 GG() const;										//Swizzle to GG Vector
	inline Vec2 GR() const;										//Swizzle to GR Vector
};

class alignas(16) Vec3 {
private:
	union {
		float xyz[3];											//Array Storage
		struct {
			float x;											//X Member
			float y;											//Y Member
			float z;											//Z Member
		};
	};
public:
	//Constructors
	inline Vec3();												//Init to Zero
	inline Vec3(float _x, float _y, float _z);					//Init to X, Y, and Z
	inline Vec3(const Vec2& _xy, float _z);						//Init from a Vec2 for X and Y, and from a float for Z
	inline Vec3(float _x, const Vec2& _yz);						//Init from X, and from a Vec2 for Y and Z
	inline Vec3(const Vec3& _other);							//Init from Copy

	//Assignment
	inline Vec3& operator=(const Vec3& _other);					//Assignment
	inline Vec3& operator+=(const Vec3& _other);				//Addition
	inline Vec3& operator-=(const Vec3& _other);				//Subtraction
	inline Vec3& operator*=(const float _scale);				//Scaling
	inline Vec3& operator&=(const Vec3& _other);				//Cross Product
	inline float& operator[](int _ndx);							//Array access (Modifiable)
	inline float operator[](int _ndx) const;					//Array access (Const)

	//Arithmetic
	inline Vec3 operator+(const Vec3& _other) const;			//Addition
	inline Vec3 operator-(const Vec3& _other) const;			//Subtraction
	inline Vec3 operator*(const float _scale) const;			//Scaling
	inline float operator*(const Vec3& _other) const;			//Dot Product
	inline Vec3 operator&(const Vec3& _other) const;			//Cross Product
	inline Vec3 operator~() const;								//Zero
	inline Vec3 operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec3& _other) const;			//Check Equality
	inline bool operator<(const Vec3& _other) const;			//Check Less Than
	inline bool operator>(const Vec3& _other) const;			//Check Greater Than
	inline bool operator<=(const Vec3& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec3& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec3& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;								//Vector Length
	inline float LengthSquared() const;							//Vector Length Squared
	inline void Normalize();									//Vector Normalize
	inline Vec3 Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec3& _other) const;		//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline float Dot(const Vec3& _other) const;					//Dot Product
	inline void Cross(const Vec3& _other);						//Cross Product
	inline void Add(const Vec3& _other);						//Addition
	inline void Subtract(const Vec3& _other);					//Subtraction
	inline void Scale(const float _scale);						//Scaling
	inline void Negate();										//Negate
	inline void Zero();											//Zero
	inline bool Equals(const Vec3& _other) const;				//Check Equality
	inline bool Less(const Vec3& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec3& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec3& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec3& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec3& _other) const;			//Check Not Equal

	//Member Modification
	inline float& X();											//Vector X Component (Modifiable)
	inline float X() const;										//Vector X Component (Const)
	inline float& Y();											//Vector Y Component (Modifiable)
	inline float Y() const;										//Vector Y Component (Const)
	inline float& Z();											//Vector Z Component (Modifiable)
	inline float Z() const;										//Vector Z Component (Const)

	//Swizzle Operations (Vec2)
	inline Vec2 XX() const;										//Swizzle to XX Vector
	inline Vec2 YY() const;										//Swizzle to YY Vector
	inline Vec2 ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2 XY() const;										//Swizzle to XY Vector
	inline Vec2 XZ() const;										//Swizzle to XZ Vector
	inline Vec2 YX() const;										//Swizzle to YX Vector
	inline Vec2 YZ() const;										//Swizzle to YZ Vector
	inline Vec2 ZX() const;										//Swizzle to ZX Vector
	inline Vec2 ZY() const;										//Swizzle to ZY Vector
	inline Vec2 RR() const;										//Swizzle to RR Vector
	inline Vec2 GG() const;										//Swizzle to GG Vector
	inline Vec2 BB() const;										//Swizzle to BB Vector
	inline Vec2 RG() const;										//Swizzle to RG Vector
	inline Vec2 RB() const;										//Swizzle to RB Vector
	inline Vec2 GR() const;										//Swizzle to GR Vector
	inline Vec2 GB() const;										//Swizzle to GB Vector
	inline Vec2 BR() const;										//Swizzle to BR Vector
	inline Vec2 BG() const;										//Swizzle to BG Vector

	//Swizzle Operations (Vec3)
	inline Vec3 XXX() const;									//Swizzle to XXX Vector
	inline Vec3 XXY() const;									//Swizzle to XXY Vector
	inline Vec3 XXZ() const;									//Swizzle to XXZ Vector
	inline Vec3 XYX() const;									//Swizzle to XYX Vector
	inline Vec3 XYY() const;									//Swizzle to XYY Vector
	inline Vec3 XZX() const;									//Swizzle to XZX Vector
	inline Vec3 XZY() const;									//Swizzle to XZY Vector
	inline Vec3 XZZ() const;									//Swizzle to XZZ Vector
	inline Vec3 YXX() const;									//Swizzle to YXX Vector
	inline Vec3 YXY() const;									//Swizzle to YXY Vector
	inline Vec3 YXZ() const;									//Swizzle to YXZ Vector
	inline Vec3 YYX() const;									//Swizzle to YYX Vector
	inline Vec3 YYY() const;									//Swizzle to YYY Vector
	inline Vec3 YYZ() const;									//Swizzle to YYZ Vector
	inline Vec3 YZX() const;									//Swizzle to YZX Vector
	inline Vec3 YZY() const;									//Swizzle to YZY Vector
	inline Vec3 YZZ() const;									//Swizzle to YZZ Vector
	inline Vec3 ZXX() const;									//Swizzle to ZXX Vector
	inline Vec3 ZXY() const;									//Swizzle to ZXY Vector
	inline Vec3 ZXZ() const;									//Swizzle to ZXZ Vector
	inline Vec3 ZYX() const;									//Swizzle to ZYX Vector
	inline Vec3 ZYY() const;									//Swizzle to ZYY Vector
	inline Vec3 ZYZ() const;									//Swizzle to ZYZ Vector
	inline Vec3 ZZX() const;									//Swizzle to ZZX Vector
	inline Vec3 ZZY() const;									//Swizzle to ZZY Vector
	inline Vec3 ZZZ() const;									//Swizzle to ZZZ Vector
	inline Vec3 RRR() const;									//Swizzle to RRR Vector
	inline Vec3 RRG() const;									//Swizzle to RRG Vector
	inline Vec3 RRB() const;									//Swizzle to RRB Vector
	inline Vec3 RGR() const;									//Swizzle to RGR Vector
	inline Vec3 RGG() const;									//Swizzle to RGG Vector
	inline Vec3 RBR() const;									//Swizzle to RBR Vector
	inline Vec3 RBG() const;									//Swizzle to RBG Vector
	inline Vec3 RBB() const;									//Swizzle to RBB Vector
	inline Vec3 GRR() const;									//Swizzle to GRR Vector
	inline Vec3 GRG() const;									//Swizzle to GRG Vector
	inline Vec3 GRB() const;									//Swizzle to GRB Vector
	inline Vec3 GGR() const;									//Swizzle to GGR Vector
	inline Vec3 GGG() const;									//Swizzle to GGG Vector
	inline Vec3 GGB() const;									//Swizzle to GGB Vector
	inline Vec3 GBR() const;									//Swizzle to GBR Vector
	inline Vec3 GBG() const;									//Swizzle to GBG Vector
	inline Vec3 GBB() const;									//Swizzle to GBB Vector
	inline Vec3 BRR() const;									//Swizzle to BRR Vector
	inline Vec3 BRG() const;									//Swizzle to BRG Vector
	inline Vec3 BRB() const;									//Swizzle to BRB Vector
	inline Vec3 BGR() const;									//Swizzle to BGR Vector
	inline Vec3 BGG() const;									//Swizzle to BGG Vector
	inline Vec3 BGB() const;									//Swizzle to BGB Vector
	inline Vec3 BBR() const;									//Swizzle to BBR Vector
	inline Vec3 BBG() const;									//Swizzle to BBG Vector
	inline Vec3 BBB() const;									//Swizzle to BBB Vector
};

class alignas(16) Vec4 {
private:
	union {
		float xyzw[4];											//Array Storage
		struct {
			float x;											//X Member
			float y;											//Y Member
			float z;											//Z Member
			float w;											//W Member
		};
	};
public:

};
#endif