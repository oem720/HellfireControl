
#ifndef VECTOR_LIBRARY_HEADER
#define VECTOR_LIBRARY_HEADER

#pragma region FloatingPointVectors

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
	inline float& Y();											//Vector Y Component (Modifiable)
	inline float X() const;										//Vector X Component (Const)
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
	inline float& Y();											//Vector Y Component (Modifiable)
	inline float& Z();											//Vector Z Component (Modifiable)
	inline float X() const;										//Vector X Component (Const)
	inline float Y() const;										//Vector Y Component (Const)
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
	//Constructors
	inline Vec4();												//Init to Zero
	inline Vec4(float _x, float _y, float _z, float _w);		//Init to X, Y, Z, and W
	inline Vec4(const Vec2& _xy, float _z, float _w);			//Init from a Vec2 for X and Y, and from a float for Z and W
	inline Vec4(float _x, const Vec2& _yz, float _w);			//Init from X, from a Vec2 for Y and Z and a float for W
	inline Vec4(float _x, float _y, const Vec2& _zw);			//Init from X and Y, and from a Vec2 for Z and W
	inline Vec4(const Vec2& _xy, const Vec2& _zw);				//Init from 2 Vec2's
	inline Vec4(const Vec3& _xyz, float _w);					//Init from a Vec3 and a float for W
	inline Vec4(float _x, const Vec3& _yzw);					//Init from a float for X and a Vec3
	inline Vec4(const Vec4& _other);							//Init from Copy

	//Assignment
	inline Vec4& operator=(const Vec4& _other);					//Assignment
	inline Vec4& operator+=(const Vec4& _other);				//Addition
	inline Vec4& operator-=(const Vec4& _other);				//Subtraction
	inline Vec4& operator*=(const float _scale);				//Scaling
	inline Vec4& operator&=(const Vec4& _other);				//Cross Product
	inline float& operator[](int _ndx);							//Array access (Modifiable)
	inline float operator[](int _ndx) const;					//Array access (Const)

	//Arithmetic
	inline Vec4 operator+(const Vec4& _other) const;			//Addition
	inline Vec4 operator-(const Vec4& _other) const;			//Subtraction
	inline Vec4 operator*(const float _scale) const;			//Scaling
	inline float operator*(const Vec4& _other) const;			//Dot Product
	inline Vec4 operator&(const Vec4& _other) const;			//Cross Product
	inline Vec4 operator~() const;								//Zero
	inline Vec4 operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec4& _other) const;			//Check Equality
	inline bool operator<(const Vec4& _other) const;			//Check Less Than
	inline bool operator>(const Vec4& _other) const;			//Check Greater Than
	inline bool operator<=(const Vec4& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec4& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec4& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;								//Vector Length
	inline float LengthSquared() const;							//Vector Length Squared
	inline void Normalize();									//Vector Normalize
	inline Vec4 Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec4& _other) const;		//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline float Dot(const Vec4& _other) const;					//Dot Product
	inline void Cross(const Vec4& _other);						//Cross Product
	inline void Add(const Vec4& _other);						//Addition
	inline void Subtract(const Vec4& _other);					//Subtraction
	inline void Scale(const float _scale);						//Scaling
	inline void Negate();										//Negate
	inline void Zero();											//Zero
	inline bool Equals(const Vec4& _other) const;				//Check Equality
	inline bool Less(const Vec4& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec4& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec4& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec4& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec4& _other) const;			//Check Not Equal

	//Member Modification
	inline float& X();											//Vector X Component (Modifiable)
	inline float& Y();											//Vector Y Component (Modifiable)
	inline float& Z();											//Vector Z Component (Modifiable)
	inline float& W();											//Vector W Component (Modifiable)
	inline float X() const;										//Vector X Component (Const)
	inline float Y() const;										//Vector Y Component (Const)
	inline float Z() const;										//Vector Z Component (Const)
	inline float W() const;										//Vector W Component (Const)

	//Swizzle Operations (Vec2)
	inline Vec2 XX() const;										//Swizzle to XX Vector
	inline Vec2 YY() const;										//Swizzle to YY Vector
	inline Vec2 ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2 WW() const;										//Swizzle to WW Vector
	inline Vec2 XY() const;										//Swizzle to XY Vector
	inline Vec2 XZ() const;										//Swizzle to XZ Vector
	inline Vec2 XW() const;										//Swizzle to XW Vector
	inline Vec2 YX() const;										//Swizzle to YX Vector
	inline Vec2 YZ() const;										//Swizzle to YZ Vector
	inline Vec2 YW() const;										//Swizzle to YW Vector
	inline Vec2 ZX() const;										//Swizzle to ZX Vector
	inline Vec2 ZY() const;										//Swizzle to ZY Vector
	inline Vec2 ZW() const;										//Swizzle to ZW Vector
	inline Vec2 WX() const;										//Swizzle to WX Vector
	inline Vec2 WY() const;										//Swizzle to WY Vector
	inline Vec2 WZ() const;										//Swizzle to WZ Vector
	inline Vec2 RR() const;										//Swizzle to RR Vector
	inline Vec2 GG() const;										//Swizzle to GG Vector
	inline Vec2 BB() const;										//Swizzle to BB Vector
	inline Vec2 AA() const;										//Swizzle to AA Vector
	inline Vec2 RG() const;										//Swizzle to RG Vector
	inline Vec2 RB() const;										//Swizzle to RB Vector
	inline Vec2 RA() const;										//Swizzle to RA Vector
	inline Vec2 GR() const;										//Swizzle to GR Vector
	inline Vec2 GB() const;										//Swizzle to GB Vector
	inline Vec2 GA() const;										//Swizzle to GA Vector
	inline Vec2 BR() const;										//Swizzle to BR Vector
	inline Vec2 BG() const;										//Swizzle to BG Vector
	inline Vec2	BA() const;										//Swizzle to BA Vector
	inline Vec2 AR() const;										//Swizzle to AR Vector
	inline Vec2 AG() const;										//Swizzle to AG Vector
	inline Vec2 AB() const;										//Swizzle to AB Vector

	//Swizzle Operations (Vec3)
	inline Vec3 XXX() const;									//Swizzle to XXX Vector
	inline Vec3 XXY() const;									//Swizzle to XXY Vector
	inline Vec3 XXZ() const;									//Swizzle to XXZ Vector
	inline Vec3 XXW() const;									//Swizzle to XXW Vector
	inline Vec3 XYX() const;									//Swizzle to XYX Vector
	inline Vec3 XYY() const;									//Swizzle to XYY Vector
	inline Vec3 XYW() const;									//Swizzle to XYW Vector
	inline Vec3 XZX() const;									//Swizzle to XZX Vector
	inline Vec3 XZY() const;									//Swizzle to XZY Vector
	inline Vec3 XZZ() const;									//Swizzle to XZZ Vector
	inline Vec3 XZW() const;									//Swizzle to XZW Vector
	inline Vec3 XWX() const;									//Swizzle to XWX Vector
	inline Vec3 XWY() const;									//Swizzle to XWY Vector
	inline Vec3 XWZ() const;									//Swizzle to XWZ Vector
	inline Vec3 XWW() const;									//Swizzle to XWW Vector
	inline Vec3 YXX() const;									//Swizzle to YXX Vector
	inline Vec3 YXY() const;									//Swizzle to YXY Vector
	inline Vec3 YXZ() const;									//Swizzle to YXZ Vector
	inline Vec3 YXW() const;									//Swizzle to YXW Vector
	inline Vec3 YYX() const;									//Swizzle to YYX Vector
	inline Vec3 YYY() const;									//Swizzle to YYY Vector
	inline Vec3 YYZ() const;									//Swizzle to YYZ Vector
	inline Vec3 YYW() const;									//Swizzle to YYW Vector
	inline Vec3 YZX() const;									//Swizzle to YZX Vector
	inline Vec3 YZY() const;									//Swizzle to YZY Vector
	inline Vec3 YZZ() const;									//Swizzle to YZZ Vector
	inline Vec3 YZW() const;									//Swizzle to YZW Vector
	inline Vec3 YWX() const;									//Swizzle to YWX Vector
	inline Vec3 YWY() const;									//Swizzle to YWY Vector
	inline Vec3 YWZ() const;									//Swizzle to YWZ Vector
	inline Vec3 YWW() const;									//Swizzle to YWW Vector
	inline Vec3 ZXX() const;									//Swizzle to ZXX Vector
	inline Vec3 ZXY() const;									//Swizzle to ZXY Vector
	inline Vec3 ZXZ() const;									//Swizzle to ZXZ Vector
	inline Vec3 ZXW() const;									//Swizzle to ZXW Vector
	inline Vec3 ZYX() const;									//Swizzle to ZYX Vector
	inline Vec3 ZYY() const;									//Swizzle to ZYY Vector
	inline Vec3 ZYZ() const;									//Swizzle to ZYZ Vector
	inline Vec3 ZYW() const;									//Swizzle to ZYW Vector
	inline Vec3 ZZX() const;									//Swizzle to ZZX Vector
	inline Vec3 ZZY() const;									//Swizzle to ZZY Vector
	inline Vec3 ZZZ() const;									//Swizzle to ZZZ Vector
	inline Vec3 ZZW() const;									//Swizzle to ZZW Vector
	inline Vec3 ZWX() const;									//Swizzle to ZWX Vector
	inline Vec3 ZWY() const;									//Swizzle to ZWY Vector
	inline Vec3 ZWZ() const;									//Swizzle to ZWZ Vector
	inline Vec3 ZWW() const;									//Swizzle to ZWW Vector
	inline Vec3 WXX() const;									//Swizzle to WXX Vector
	inline Vec3 WXY() const;									//Swizzle to WXY Vector
	inline Vec3 WXZ() const;									//Swizzle to WXZ Vector
	inline Vec3 WXW() const;									//Swizzle to WXW Vector
	inline Vec3 WYX() const;									//Swizzle to WYX Vector
	inline Vec3 WYY() const;									//Swizzle to WYY Vector
	inline Vec3 WYZ() const;									//Swizzle to WYZ Vector
	inline Vec3 WYW() const;									//Swizzle to WYW Vector
	inline Vec3 WZX() const;									//Swizzle to WZX Vector
	inline Vec3 WZY() const;									//Swizzle to WZY Vector
	inline Vec3 WZZ() const;									//Swizzle to WZZ Vector
	inline Vec3 WZW() const;									//Swizzle to WZW Vector
	inline Vec3 WWX() const;									//Swizzle to WWX Vector
	inline Vec3 WWY() const;									//Swizzle to WWY Vector
	inline Vec3 WWZ() const;									//Swizzle to WWZ Vector
	inline Vec3 WWW() const;									//Swizzle to WWW Vector
	inline Vec3 RRR() const;									//Swizzle to RRR Vector
	inline Vec3 RRG() const;									//Swizzle to RRG Vector
	inline Vec3 RRB() const;									//Swizzle to RRB Vector
	inline Vec3 RRA() const;									//Swizzle to RRA Vector
	inline Vec3 RGR() const;									//Swizzle to RGR Vector
	inline Vec3 RGG() const;									//Swizzle to RGG Vector
	inline Vec3 RGA() const;									//Swizzle to RGA Vector
	inline Vec3 RBR() const;									//Swizzle to RBR Vector
	inline Vec3 RBG() const;									//Swizzle to RBG Vector
	inline Vec3 RBB() const;									//Swizzle to RBB Vector
	inline Vec3 RBA() const;									//Swizzle to RBA Vector
	inline Vec3 RAR() const;									//Swizzle to RAR Vector
	inline Vec3 RAG() const;									//Swizzle to RAG Vector
	inline Vec3 RAB() const;									//Swizzle to RAB Vector
	inline Vec3 RAA() const;									//Swizzle to RAA Vector
	inline Vec3 GRR() const;									//Swizzle to GRR Vector
	inline Vec3 GRG() const;									//Swizzle to GRG Vector
	inline Vec3 GRB() const;									//Swizzle to GRB Vector
	inline Vec3 GRA() const;									//Swizzle to GRA Vector
	inline Vec3 GGR() const;									//Swizzle to GGR Vector
	inline Vec3 GGG() const;									//Swizzle to GGG Vector
	inline Vec3 GGB() const;									//Swizzle to GGB Vector
	inline Vec3 GGA() const;									//Swizzle to GGA Vector
	inline Vec3 GBR() const;									//Swizzle to GBR Vector
	inline Vec3 GBG() const;									//Swizzle to GBG Vector
	inline Vec3 GBB() const;									//Swizzle to GBB Vector
	inline Vec3 GBA() const;									//Swizzle to GBA Vector
	inline Vec3 GAR() const;									//Swizzle to GAR Vector
	inline Vec3 GAG() const;									//Swizzle to GAG Vector
	inline Vec3 GAB() const;									//Swizzle to GAB Vector
	inline Vec3 GAA() const;									//Swizzle to GAA Vector
	inline Vec3 BRR() const;									//Swizzle to BRR Vector
	inline Vec3 BRG() const;									//Swizzle to BRG Vector
	inline Vec3 BRB() const;									//Swizzle to BRB Vector
	inline Vec3 BRA() const;									//Swizzle to BRA Vector
	inline Vec3 BGR() const;									//Swizzle to BGR Vector
	inline Vec3 BGG() const;									//Swizzle to BGG Vector
	inline Vec3 BGB() const;									//Swizzle to BGB Vector
	inline Vec3 BGA() const;									//Swizzle to BGA Vector
	inline Vec3 BBR() const;									//Swizzle to BBR Vector
	inline Vec3 BBG() const;									//Swizzle to BBG Vector
	inline Vec3 BBB() const;									//Swizzle to BBB Vector
	inline Vec3 BBA() const;									//Swizzle to BBA Vector
	inline Vec3 BAR() const;									//Swizzle to BAR Vector
	inline Vec3 BAG() const;									//Swizzle to BAG Vector
	inline Vec3 BAB() const;									//Swizzle to BAB Vector
	inline Vec3 BAA() const;									//Swizzle to BAA Vector
	inline Vec3 ARR() const;									//Swizzle to ARR Vector
	inline Vec3 ARG() const;									//Swizzle to ARG Vector
	inline Vec3 ARB() const;									//Swizzle to ARB Vector
	inline Vec3 ARA() const;									//Swizzle to ARA Vector
	inline Vec3 AGR() const;									//Swizzle to AGR Vector
	inline Vec3 AGG() const;									//Swizzle to AGG Vector
	inline Vec3 AGB() const;									//Swizzle to AGB Vector
	inline Vec3 AGA() const;									//Swizzle to AGA Vector
	inline Vec3 ABR() const;									//Swizzle to ABR Vector
	inline Vec3 ABG() const;									//Swizzle to ABG Vector
	inline Vec3 ABB() const;									//Swizzle to ABB Vector
	inline Vec3 ABA() const;									//Swizzle to ABA Vector
	inline Vec3 AAR() const;									//Swizzle to AAR Vector
	inline Vec3 AAG() const;									//Swizzle to AAG Vector
	inline Vec3 AAB() const;									//Swizzle to AAB Vector
	inline Vec3 AAA() const;									//Swizzle to AAA Vector
	
	//Swizzle Operations (Vec4)


};

#pragma endregion

#pragma region DoublePrecisionVectors

class alignas(16) Vec2Double {
private:
	union {
		double xy[2];
		struct {
			double x;
			double y;
		};
	};
public:

};

class alignas(32) Vec3Double {
private:
	union {
		double xyz[3];
		struct {
			double x;
			double y;
			double z;
		};
	};
public:

};

class alignas(32) Vec4Double {
private:
	union {
		double xyzw[4];
		struct {
			double x;
			double y;
			double z;
			double w;
		};
	};
public:

};

#pragma endregion

#pragma region IntegerVectors

class alignas(8) Vec2Int {
private:
	union {
		int xy[2];
		struct {
			int x;
			int y;
		};
	};
public:

};

class alignas(16) Vec3Int {
private:
	union {
		int xyz[3];
		struct {
			int x;
			int y;
			int z;
		};
	};
public:

};

class alignas(16) Vec4Int {
private:
	union {
		int xyzw[4];
		struct {
			int x;
			int y;
			int z;
			int w;
		};
	};
public:

};

#pragma endregion

#pragma region LongVectors

class alignas(8) Vec2Long {
private:
	union {
		long xy[2];
		struct {
			long x;
			long y;
		};
	};
public:

};

class alignas(16) Vec3Long {
private:
	union {
		long xyz[3];
		struct {
			long x;
			long y;
			long z;
		};
	};
public:

};

class alignas(16) Vec4Long {
private:
	union {
		long xyzw[4];
		struct {
			long x;
			long y;
			long z;
			long w;
		};
	};
public:

};

#pragma endregion

#endif