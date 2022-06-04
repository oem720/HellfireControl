
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
	inline Vec3 XYZ() const;									//Swizzle to XYZ Vector
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
	inline Vec3 RGB() const;									//Swizzle to RGB Vector
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
	inline Vec4 XXXX() const;									//Swizzle to XXXX Vector
	inline Vec4 XXXY() const;									//Swizzle to XXXY Vector
	inline Vec4 XXXZ() const;									//Swizzle to XXXZ Vector
	inline Vec4 XXXW() const;									//Swizzle to XXXW Vector
	inline Vec4 XXYX() const;									//Swizzle to XXYX Vector
	inline Vec4 XXYY() const;									//Swizzle to XXYY Vector
	inline Vec4 XXYZ() const;									//Swizzle to XXYZ Vector
	inline Vec4 XXYW() const;									//Swizzle to XXYW Vector
	inline Vec4 XXZX() const;									//Swizzle to XXZX Vector
	inline Vec4 XXZY() const;									//Swizzle to XXZY Vector
	inline Vec4 XXZZ() const;									//Swizzle to XXZZ Vector
	inline Vec4 XXZW() const;									//Swizzle to XXZW Vector
	inline Vec4 XXWX() const;									//Swizzle to XXWX Vector
	inline Vec4 XXWY() const;									//Swizzle to XXWY Vector
	inline Vec4 XXWZ() const;									//Swizzle to XXWZ Vector
	inline Vec4 XXWW() const;									//Swizzle to XXWW Vector
	inline Vec4 XYXX() const;									//Swizzle to XYXX Vector
	inline Vec4 XYXY() const;									//Swizzle to XYXY Vector
	inline Vec4 XYXZ() const;									//Swizzle to XYXZ Vector
	inline Vec4 XYXW() const;									//Swizzle to XYXW Vector
	inline Vec4 XYYX() const;									//Swizzle to XYYX Vector
	inline Vec4 XYYY() const;									//Swizzle to XYYY Vector
	inline Vec4 XYYZ() const;									//Swizzle to XYYZ Vector
	inline Vec4 XYYW() const;									//Swizzle to XYYW Vector
	inline Vec4 XYZX() const;									//Swizzle to XYZX Vector
	inline Vec4 XYZY() const;									//Swizzle to XYZY Vector
	inline Vec4 XYZZ() const;									//Swizzle to XYZZ Vector
	inline Vec4 XYWX() const;									//Swizzle to XYWX Vector
	inline Vec4 XYWY() const;									//Swizzle to XYWY Vector
	inline Vec4 XYWZ() const;									//Swizzle to XYWZ Vector
	inline Vec4 XYWW() const;									//Swizzle to XYWW Vector
	inline Vec4 XZXX() const;									//Swizzle to XZXX Vector
	inline Vec4 XZXY() const;									//Swizzle to XZXY Vector
	inline Vec4 XZXZ() const;									//Swizzle to XZXZ Vector
	inline Vec4 XZXW() const;									//Swizzle to XZXW Vector
	inline Vec4 XZYX() const;									//Swizzle to XZYX Vector
	inline Vec4 XZYY() const;									//Swizzle to XZYY Vector
	inline Vec4 XZYZ() const;									//Swizzle to XZYZ Vector
	inline Vec4 XZYW() const;									//Swizzle to XZYW Vector
	inline Vec4 XZZX() const;									//Swizzle to XZZX Vector
	inline Vec4 XZZY() const;									//Swizzle to XZZY Vector
	inline Vec4 XZZZ() const;									//Swizzle to XZZZ Vector
	inline Vec4 XZZW() const;									//Swizzle to XZZW Vector
	inline Vec4 XZWX() const;									//Swizzle to XZWX Vector
	inline Vec4 XZWY() const;									//Swizzle to XZWY Vector
	inline Vec4 XZWZ() const;									//Swizzle to XZWZ Vector
	inline Vec4 XZWW() const;									//Swizzle to XZWW Vector
	inline Vec4 XWXX() const;									//Swizzle to XWXX Vector
	inline Vec4 XWXY() const;									//Swizzle to XWXY Vector
	inline Vec4 XWXZ() const;									//Swizzle to XWXZ Vector
	inline Vec4 XWXW() const;									//Swizzle to XWXW Vector
	inline Vec4 XWYX() const;									//Swizzle to XWYX Vector
	inline Vec4 XWYY() const;									//Swizzle to XWYY Vector
	inline Vec4 XWYZ() const;									//Swizzle to XWYZ Vector
	inline Vec4 XWYW() const;									//Swizzle to XWYW Vector
	inline Vec4 XWZX() const;									//Swizzle to XWZX Vector
	inline Vec4 XWZY() const;									//Swizzle to XWZY Vector
	inline Vec4 XWZZ() const;									//Swizzle to XWZZ Vector
	inline Vec4 XWZW() const;									//Swizzle to XWZW Vector
	inline Vec4 XWWX() const;									//Swizzle to XWWX Vector
	inline Vec4 XWWY() const;									//Swizzle to XWWY Vector
	inline Vec4 XWWZ() const;									//Swizzle to XWWZ Vector
	inline Vec4 XWWW() const;									//Swizzle to XWWW Vector
	inline Vec4 YXXX() const;									//Swizzle to YXXX Vector
	inline Vec4 YXXY() const;									//Swizzle to YXXY Vector
	inline Vec4 YXXZ() const;									//Swizzle to YXXZ Vector
	inline Vec4 YXXW() const;									//Swizzle to YXXW Vector
	inline Vec4 YXYX() const;									//Swizzle to YXYX Vector
	inline Vec4 YXYY() const;									//Swizzle to YXYY Vector
	inline Vec4 YXYZ() const;									//Swizzle to YXYZ Vector
	inline Vec4 YXYW() const;									//Swizzle to YXYW Vector
	inline Vec4 YXZX() const;									//Swizzle to YXZX Vector
	inline Vec4 YXZY() const;									//Swizzle to YXZY Vector
	inline Vec4 YXZZ() const;									//Swizzle to YXZZ Vector
	inline Vec4 YXZW() const;									//Swizzle to YXZW Vector
	inline Vec4 YXWX() const;									//Swizzle to YXWX Vector
	inline Vec4 YXWY() const;									//Swizzle to YXWY Vector
	inline Vec4 YXWZ() const;									//Swizzle to YXWZ Vector
	inline Vec4 YXWW() const;									//Swizzle to YXWW Vector
	inline Vec4 YYXX() const;									//Swizzle to YYXX Vector
	inline Vec4 YYXY() const;									//Swizzle to YYXY Vector
	inline Vec4 YYXZ() const;									//Swizzle to YYXZ Vector
	inline Vec4 YYXW() const;									//Swizzle to YYXW Vector
	inline Vec4 YYYX() const;									//Swizzle to YYYX Vector
	inline Vec4 YYYY() const;									//Swizzle to YYYY Vector
	inline Vec4 YYYZ() const;									//Swizzle to YYYZ Vector
	inline Vec4 YYYW() const;									//Swizzle to YYYW Vector
	inline Vec4 YYZX() const;									//Swizzle to YYZX Vector
	inline Vec4 YYZY() const;									//Swizzle to YYZY Vector
	inline Vec4 YYZZ() const;									//Swizzle to YYZZ Vector
	inline Vec4 YYZW() const;									//Swizzle to YYZW Vector
	inline Vec4 YYWX() const;									//Swizzle to YYWX Vector
	inline Vec4 YYWY() const;									//Swizzle to YYWY Vector
	inline Vec4 YYWZ() const;									//Swizzle to YYWZ Vector
	inline Vec4 YYWW() const;									//Swizzle to YYWW Vector
	inline Vec4 YZXX() const;									//Swizzle to YZXX Vector
	inline Vec4 YZXY() const;									//Swizzle to YZXY Vector
	inline Vec4 YZXZ() const;									//Swizzle to YZXZ Vector
	inline Vec4 YZXW() const;									//Swizzle to YZXW Vector
	inline Vec4 YZYX() const;									//Swizzle to YZYX Vector
	inline Vec4 YZYY() const;									//Swizzle to YZYY Vector
	inline Vec4 YZYZ() const;									//Swizzle to YZYZ Vector
	inline Vec4 YZYW() const;									//Swizzle to YZYW Vector
	inline Vec4 YZZX() const;									//Swizzle to YZZX Vector
	inline Vec4 YZZY() const;									//Swizzle to YZZY Vector
	inline Vec4 YZZZ() const;									//Swizzle to YZZZ Vector
	inline Vec4 YZZW() const;									//Swizzle to YZZW Vector
	inline Vec4 YZWX() const;									//Swizzle to YZWX Vector
	inline Vec4 YZWY() const;									//Swizzle to YZWY Vector
	inline Vec4 YZWZ() const;									//Swizzle to YZWZ Vector
	inline Vec4 YZWW() const;									//Swizzle to YZWW Vector
	inline Vec4 YWXX() const;									//Swizzle to YWXX Vector
	inline Vec4 YWXY() const;									//Swizzle to YWXY Vector
	inline Vec4 YWXZ() const;									//Swizzle to YWXZ Vector
	inline Vec4 YWXW() const;									//Swizzle to YWXW Vector
	inline Vec4 YWYX() const;									//Swizzle to YWYX Vector
	inline Vec4 YWYY() const;									//Swizzle to YWYY Vector
	inline Vec4 YWYZ() const;									//Swizzle to YWYZ Vector
	inline Vec4 YWYW() const;									//Swizzle to YWYW Vector
	inline Vec4 YWZX() const;									//Swizzle to YWZX Vector
	inline Vec4 YWZY() const;									//Swizzle to YWZY Vector
	inline Vec4 YWZZ() const;									//Swizzle to YWZZ Vector
	inline Vec4 YWZW() const;									//Swizzle to YWZW Vector
	inline Vec4 YWWX() const;									//Swizzle to YWWX Vector
	inline Vec4 YWWY() const;									//Swizzle to YWWY Vector
	inline Vec4 YWWZ() const;									//Swizzle to YWWZ Vector
	inline Vec4 YWWW() const;									//Swizzle to YWWW Vector
	inline Vec4 ZXXX() const;									//Swizzle to ZXXX Vector
	inline Vec4 ZXXY() const;									//Swizzle to ZXXY Vector
	inline Vec4 ZXXZ() const;									//Swizzle to ZXXZ Vector
	inline Vec4 ZXXW() const;									//Swizzle to ZXXW Vector
	inline Vec4 ZXYX() const;									//Swizzle to ZXYX Vector
	inline Vec4 ZXYY() const;									//Swizzle to ZXYY Vector
	inline Vec4 ZXYZ() const;									//Swizzle to ZXYZ Vector
	inline Vec4 ZXYW() const;									//Swizzle to ZXYW Vector
	inline Vec4 ZXZX() const;									//Swizzle to ZXZX Vector
	inline Vec4 ZXZY() const;									//Swizzle to ZXZY Vector
	inline Vec4 ZXZZ() const;									//Swizzle to ZXZZ Vector
	inline Vec4 ZXZW() const;									//Swizzle to ZXZW Vector
	inline Vec4 ZXWX() const;									//Swizzle to ZXWX Vector
	inline Vec4 ZXWY() const;									//Swizzle to ZXWY Vector
	inline Vec4 ZXWZ() const;									//Swizzle to ZXWZ Vector
	inline Vec4 ZXWW() const;									//Swizzle to ZXWW Vector
	inline Vec4 ZYXX() const;									//Swizzle to ZYXX Vector
	inline Vec4 ZYXY() const;									//Swizzle to ZYXY Vector
	inline Vec4 ZYXZ() const;									//Swizzle to ZYXZ Vector
	inline Vec4 ZYXW() const;									//Swizzle to ZYXW Vector
	inline Vec4 ZYYX() const;									//Swizzle to ZYYX Vector
	inline Vec4 ZYYY() const;									//Swizzle to ZYYY Vector
	inline Vec4 ZYYZ() const;									//Swizzle to ZYYZ Vector
	inline Vec4 ZYYW() const;									//Swizzle to ZYYW Vector
	inline Vec4 ZYZX() const;									//Swizzle to ZYZX Vector
	inline Vec4 ZYZY() const;									//Swizzle to ZYZY Vector
	inline Vec4 ZYZZ() const;									//Swizzle to ZYZZ Vector
	inline Vec4 ZYZW() const;									//Swizzle to ZYZW Vector
	inline Vec4 ZYWX() const;									//Swizzle to ZYWX Vector
	inline Vec4 ZYWY() const;									//Swizzle to ZYWY Vector
	inline Vec4 ZYWZ() const;									//Swizzle to ZYWZ Vector
	inline Vec4 ZYWW() const;									//Swizzle to ZYWW Vector
	inline Vec4 ZZXX() const;									//Swizzle to ZZXX Vector
	inline Vec4 ZZXY() const;									//Swizzle to ZZXY Vector
	inline Vec4 ZZXZ() const;									//Swizzle to ZZXZ Vector
	inline Vec4 ZZXW() const;									//Swizzle to ZZXW Vector
	inline Vec4 ZZYX() const;									//Swizzle to ZZYX Vector
	inline Vec4 ZZYY() const;									//Swizzle to ZZYY Vector
	inline Vec4 ZZYZ() const;									//Swizzle to ZZYZ Vector
	inline Vec4 ZZYW() const;									//Swizzle to ZZYW Vector
	inline Vec4 ZZZX() const;									//Swizzle to ZZZX Vector
	inline Vec4 ZZZY() const;									//Swizzle to ZZZY Vector
	inline Vec4 ZZZZ() const;									//Swizzle to ZZZZ Vector
	inline Vec4 ZZZW() const;									//Swizzle to ZZZW Vector
	inline Vec4 ZZWX() const;									//Swizzle to ZZWX Vector
	inline Vec4 ZZWY() const;									//Swizzle to ZZWY Vector
	inline Vec4 ZZWZ() const;									//Swizzle to ZZWZ Vector
	inline Vec4 ZZWW() const;									//Swizzle to ZZWW Vector
	inline Vec4 ZWXX() const;									//Swizzle to ZWXX Vector
	inline Vec4 ZWXY() const;									//Swizzle to ZWXY Vector
	inline Vec4 ZWXZ() const;									//Swizzle to ZWXZ Vector
	inline Vec4 ZWXW() const;									//Swizzle to ZWXW Vector
	inline Vec4 ZWYX() const;									//Swizzle to ZWYX Vector
	inline Vec4 ZWYY() const;									//Swizzle to ZWYY Vector
	inline Vec4 ZWYZ() const;									//Swizzle to ZWYZ Vector
	inline Vec4 ZWYW() const;									//Swizzle to ZWYW Vector
	inline Vec4 ZWZX() const;									//Swizzle to ZWZX Vector
	inline Vec4 ZWZY() const;									//Swizzle to ZWZY Vector
	inline Vec4 ZWZZ() const;									//Swizzle to ZWZZ Vector
	inline Vec4 ZWZW() const;									//Swizzle to ZWZW Vector
	inline Vec4 ZWWX() const;									//Swizzle to ZWWX Vector
	inline Vec4 ZWWY() const;									//Swizzle to ZWWY Vector
	inline Vec4 ZWWZ() const;									//Swizzle to ZWWZ Vector
	inline Vec4 ZWWW() const;									//Swizzle to ZWWW Vector
	inline Vec4 WXXX() const;									//Swizzle to WXXX Vector
	inline Vec4 WXXY() const;									//Swizzle to WXXY Vector
	inline Vec4 WXXZ() const;									//Swizzle to WXXZ Vector
	inline Vec4 WXXW() const;									//Swizzle to WXXW Vector
	inline Vec4 WXYX() const;									//Swizzle to WXYX Vector
	inline Vec4 WXYY() const;									//Swizzle to WXYY Vector
	inline Vec4 WXYZ() const;									//Swizzle to WXYZ Vector
	inline Vec4 WXYW() const;									//Swizzle to WXYW Vector
	inline Vec4 WXZX() const;									//Swizzle to WXZX Vector
	inline Vec4 WXZY() const;									//Swizzle to WXZY Vector
	inline Vec4 WXZZ() const;									//Swizzle to WXZZ Vector
	inline Vec4 WXZW() const;									//Swizzle to WXZW Vector
	inline Vec4 WXWX() const;									//Swizzle to WXWX Vector
	inline Vec4 WXWY() const;									//Swizzle to WXWY Vector
	inline Vec4 WXWZ() const;									//Swizzle to WXWZ Vector
	inline Vec4 WXWW() const;									//Swizzle to WXWW Vector
	inline Vec4 WYXX() const;									//Swizzle to WYXX Vector
	inline Vec4 WYXY() const;									//Swizzle to WYXY Vector
	inline Vec4 WYXZ() const;									//Swizzle to WYXZ Vector
	inline Vec4 WYXW() const;									//Swizzle to WYXW Vector
	inline Vec4 WYYX() const;									//Swizzle to WYYX Vector
	inline Vec4 WYYY() const;									//Swizzle to WYYY Vector
	inline Vec4 WYYZ() const;									//Swizzle to WYYZ Vector
	inline Vec4 WYYW() const;									//Swizzle to WYYW Vector
	inline Vec4 WYZX() const;									//Swizzle to WYZX Vector
	inline Vec4 WYZY() const;									//Swizzle to WYZY Vector
	inline Vec4 WYZZ() const;									//Swizzle to WYZZ Vector
	inline Vec4 WYZW() const;									//Swizzle to WYZW Vector
	inline Vec4 WYWX() const;									//Swizzle to WYWX Vector
	inline Vec4 WYWY() const;									//Swizzle to WYWY Vector
	inline Vec4 WYWZ() const;									//Swizzle to WYWZ Vector
	inline Vec4 WYWW() const;									//Swizzle to WYWW Vector
	inline Vec4 WZXX() const;									//Swizzle to WZXX Vector
	inline Vec4 WZXY() const;									//Swizzle to WZXY Vector
	inline Vec4 WZXZ() const;									//Swizzle to WZXZ Vector
	inline Vec4 WZXW() const;									//Swizzle to WZXW Vector
	inline Vec4 WZYX() const;									//Swizzle to WZYX Vector
	inline Vec4 WZYY() const;									//Swizzle to WZYY Vector
	inline Vec4 WZYZ() const;									//Swizzle to WZYZ Vector
	inline Vec4 WZYW() const;									//Swizzle to WZYW Vector
	inline Vec4 WZZX() const;									//Swizzle to WZZX Vector
	inline Vec4 WZZY() const;									//Swizzle to WZZY Vector
	inline Vec4 WZZZ() const;									//Swizzle to WZZZ Vector
	inline Vec4 WZZW() const;									//Swizzle to WZZW Vector
	inline Vec4 WZWX() const;									//Swizzle to WZWX Vector
	inline Vec4 WZWY() const;									//Swizzle to WZWY Vector
	inline Vec4 WZWZ() const;									//Swizzle to WZWZ Vector
	inline Vec4 WZWW() const;									//Swizzle to WZWW Vector
	inline Vec4 WWXX() const;									//Swizzle to WWXX Vector
	inline Vec4 WWXY() const;									//Swizzle to WWXY Vector
	inline Vec4 WWXZ() const;									//Swizzle to WWXZ Vector
	inline Vec4 WWXW() const;									//Swizzle to WWXW Vector
	inline Vec4 WWYX() const;									//Swizzle to WWYX Vector
	inline Vec4 WWYY() const;									//Swizzle to WWYY Vector
	inline Vec4 WWYZ() const;									//Swizzle to WWYZ Vector
	inline Vec4 WWYW() const;									//Swizzle to WWYW Vector
	inline Vec4 WWZX() const;									//Swizzle to WWZX Vector
	inline Vec4 WWZY() const;									//Swizzle to WWZY Vector
	inline Vec4 WWZZ() const;									//Swizzle to WWZZ Vector
	inline Vec4 WWZW() const;									//Swizzle to WWZW Vector
	inline Vec4 WWWX() const;									//Swizzle to WWWX Vector
	inline Vec4 WWWY() const;									//Swizzle to WWWY Vector
	inline Vec4 WWWZ() const;									//Swizzle to WWWZ Vector
	inline Vec4 WWWW() const;									//Swizzle to WWWW Vector
	inline Vec4 RRRR() const;									//Swizzle to RRRR Vector
	inline Vec4 RRRG() const;									//Swizzle to RRRG Vector
	inline Vec4 RRRB() const;									//Swizzle to RRRB Vector
	inline Vec4 RRRA() const;									//Swizzle to RRRA Vector
	inline Vec4 RRGR() const;									//Swizzle to RRGR Vector
	inline Vec4 RRGG() const;									//Swizzle to RRGG Vector
	inline Vec4 RRGB() const;									//Swizzle to RRGB Vector
	inline Vec4 RRGA() const;									//Swizzle to RRGA Vector
	inline Vec4 RRBR() const;									//Swizzle to RRBR Vector
	inline Vec4 RRBG() const;									//Swizzle to RRBG Vector
	inline Vec4 RRBB() const;									//Swizzle to RRBB Vector
	inline Vec4 RRBA() const;									//Swizzle to RRBA Vector
	inline Vec4 RRAR() const;									//Swizzle to RRAR Vector
	inline Vec4 RRAG() const;									//Swizzle to RRAG Vector
	inline Vec4 RRAB() const;									//Swizzle to RRAB Vector
	inline Vec4 RRAA() const;									//Swizzle to RRAA Vector
	inline Vec4 RGRR() const;									//Swizzle to RGRR Vector
	inline Vec4 RGRG() const;									//Swizzle to RGRG Vector
	inline Vec4 RGRB() const;									//Swizzle to RGRB Vector
	inline Vec4 RGRA() const;									//Swizzle to RGRA Vector
	inline Vec4 RGGR() const;									//Swizzle to RGGR Vector
	inline Vec4 RGGG() const;									//Swizzle to RGGG Vector
	inline Vec4 RGGB() const;									//Swizzle to RGGB Vector
	inline Vec4 RGGA() const;									//Swizzle to RGGA Vector
	inline Vec4 RGBR() const;									//Swizzle to RGBR Vector
	inline Vec4 RGBG() const;									//Swizzle to RGBG Vector
	inline Vec4 RGBB() const;									//Swizzle to RGBB Vector
	inline Vec4 RGAR() const;									//Swizzle to RGAR Vector
	inline Vec4 RGAG() const;									//Swizzle to RGAG Vector
	inline Vec4 RGAB() const;									//Swizzle to RGAB Vector
	inline Vec4 RGAA() const;									//Swizzle to RGAA Vector
	inline Vec4 RBRR() const;									//Swizzle to RBRR Vector
	inline Vec4 RBRG() const;									//Swizzle to RBRG Vector
	inline Vec4 RBRB() const;									//Swizzle to RBRB Vector
	inline Vec4 RBRA() const;									//Swizzle to RBRA Vector
	inline Vec4 RBGR() const;									//Swizzle to RBGR Vector
	inline Vec4 RBGG() const;									//Swizzle to RBGG Vector
	inline Vec4 RBGB() const;									//Swizzle to RBGB Vector
	inline Vec4 RBGA() const;									//Swizzle to RBGA Vector
	inline Vec4 RBBR() const;									//Swizzle to RBBR Vector
	inline Vec4 RBBG() const;									//Swizzle to RBBG Vector
	inline Vec4 RBBB() const;									//Swizzle to RBBB Vector
	inline Vec4 RBBA() const;									//Swizzle to RBBA Vector
	inline Vec4 RBAR() const;									//Swizzle to RBAR Vector
	inline Vec4 RBAG() const;									//Swizzle to RBAG Vector
	inline Vec4 RBAB() const;									//Swizzle to RBAB Vector
	inline Vec4 RBAA() const;									//Swizzle to RBAA Vector
	inline Vec4 RARR() const;									//Swizzle to RARR Vector
	inline Vec4 RARG() const;									//Swizzle to RARG Vector
	inline Vec4 RARB() const;									//Swizzle to RARB Vector
	inline Vec4 RARA() const;									//Swizzle to RARA Vector
	inline Vec4 RAGR() const;									//Swizzle to RAGR Vector
	inline Vec4 RAGG() const;									//Swizzle to RAGG Vector
	inline Vec4 RAGB() const;									//Swizzle to RAGB Vector
	inline Vec4 RAGA() const;									//Swizzle to RAGA Vector
	inline Vec4 RABR() const;									//Swizzle to RABR Vector
	inline Vec4 RABG() const;									//Swizzle to RABG Vector
	inline Vec4 RABB() const;									//Swizzle to RABB Vector
	inline Vec4 RABA() const;									//Swizzle to RABA Vector
	inline Vec4 RAAR() const;									//Swizzle to RAAR Vector
	inline Vec4 RAAG() const;									//Swizzle to RAAG Vector
	inline Vec4 RAAB() const;									//Swizzle to RAAB Vector
	inline Vec4 RAAA() const;									//Swizzle to RAAA Vector
	inline Vec4 GRRR() const;									//Swizzle to GRRR Vector
	inline Vec4 GRRG() const;									//Swizzle to GRRG Vector
	inline Vec4 GRRB() const;									//Swizzle to GRRB Vector
	inline Vec4 GRRA() const;									//Swizzle to GRRA Vector
	inline Vec4 GRGR() const;									//Swizzle to GRGR Vector
	inline Vec4 GRGG() const;									//Swizzle to GRGG Vector
	inline Vec4 GRGB() const;									//Swizzle to GRGB Vector
	inline Vec4 GRGA() const;									//Swizzle to GRGA Vector
	inline Vec4 GRBR() const;									//Swizzle to GRBR Vector
	inline Vec4 GRBG() const;									//Swizzle to GRBG Vector
	inline Vec4 GRBB() const;									//Swizzle to GRBB Vector
	inline Vec4 GRBA() const;									//Swizzle to GRBA Vector
	inline Vec4 GRAR() const;									//Swizzle to GRAR Vector
	inline Vec4 GRAG() const;									//Swizzle to GRAG Vector
	inline Vec4 GRAB() const;									//Swizzle to GRAB Vector
	inline Vec4 GRAA() const;									//Swizzle to GRAA Vector
	inline Vec4 GGRR() const;									//Swizzle to GGRR Vector
	inline Vec4 GGRG() const;									//Swizzle to GGRG Vector
	inline Vec4 GGRB() const;									//Swizzle to GGRB Vector
	inline Vec4 GGRA() const;									//Swizzle to GGRA Vector
	inline Vec4 GGGR() const;									//Swizzle to GGGR Vector
	inline Vec4 GGGG() const;									//Swizzle to GGGG Vector
	inline Vec4 GGGB() const;									//Swizzle to GGGB Vector
	inline Vec4 GGGA() const;									//Swizzle to GGGA Vector
	inline Vec4 GGBR() const;									//Swizzle to GGBR Vector
	inline Vec4 GGBG() const;									//Swizzle to GGBG Vector
	inline Vec4 GGBB() const;									//Swizzle to GGBB Vector
	inline Vec4 GGBA() const;									//Swizzle to GGBA Vector
	inline Vec4 GGAR() const;									//Swizzle to GGAR Vector
	inline Vec4 GGAG() const;									//Swizzle to GGAG Vector
	inline Vec4 GGAB() const;									//Swizzle to GGAB Vector
	inline Vec4 GGAA() const;									//Swizzle to GGAA Vector
	inline Vec4 GBRR() const;									//Swizzle to GBRR Vector
	inline Vec4 GBRG() const;									//Swizzle to GBRG Vector
	inline Vec4 GBRB() const;									//Swizzle to GBRB Vector
	inline Vec4 GBRA() const;									//Swizzle to GBRA Vector
	inline Vec4 GBGR() const;									//Swizzle to GBGR Vector
	inline Vec4 GBGG() const;									//Swizzle to GBGG Vector
	inline Vec4 GBGB() const;									//Swizzle to GBGB Vector
	inline Vec4 GBGA() const;									//Swizzle to GBGA Vector
	inline Vec4 GBBR() const;									//Swizzle to GBBR Vector
	inline Vec4 GBBG() const;									//Swizzle to GBBG Vector
	inline Vec4 GBBB() const;									//Swizzle to GBBB Vector
	inline Vec4 GBBA() const;									//Swizzle to GBBA Vector
	inline Vec4 GBAR() const;									//Swizzle to GBAR Vector
	inline Vec4 GBAG() const;									//Swizzle to GBAG Vector
	inline Vec4 GBAB() const;									//Swizzle to GBAB Vector
	inline Vec4 GBAA() const;									//Swizzle to GBAA Vector
	inline Vec4 GARR() const;									//Swizzle to GARR Vector
	inline Vec4 GARG() const;									//Swizzle to GARG Vector
	inline Vec4 GARB() const;									//Swizzle to GARB Vector
	inline Vec4 GARA() const;									//Swizzle to GARA Vector
	inline Vec4 GAGR() const;									//Swizzle to GAGR Vector
	inline Vec4 GAGG() const;									//Swizzle to GAGG Vector
	inline Vec4 GAGB() const;									//Swizzle to GAGB Vector
	inline Vec4 GAGA() const;									//Swizzle to GAGA Vector
	inline Vec4 GABR() const;									//Swizzle to GABR Vector
	inline Vec4 GABG() const;									//Swizzle to GABG Vector
	inline Vec4 GABB() const;									//Swizzle to GABB Vector
	inline Vec4 GABA() const;									//Swizzle to GABA Vector
	inline Vec4 GAAR() const;									//Swizzle to GAAR Vector
	inline Vec4 GAAG() const;									//Swizzle to GAAG Vector
	inline Vec4 GAAB() const;									//Swizzle to GAAB Vector
	inline Vec4 GAAA() const;									//Swizzle to GAAA Vector
	inline Vec4 BRRR() const;									//Swizzle to BRRR Vector
	inline Vec4 BRRG() const;									//Swizzle to BRRG Vector
	inline Vec4 BRRB() const;									//Swizzle to BRRB Vector
	inline Vec4 BRRA() const;									//Swizzle to BRRA Vector
	inline Vec4 BRGR() const;									//Swizzle to BRGR Vector
	inline Vec4 BRGG() const;									//Swizzle to BRGG Vector
	inline Vec4 BRGB() const;									//Swizzle to BRGB Vector
	inline Vec4 BRGA() const;									//Swizzle to BRGA Vector
	inline Vec4 BRBR() const;									//Swizzle to BRBR Vector
	inline Vec4 BRBG() const;									//Swizzle to BRBG Vector
	inline Vec4 BRBB() const;									//Swizzle to BRBB Vector
	inline Vec4 BRBA() const;									//Swizzle to BRBA Vector
	inline Vec4 BRAR() const;									//Swizzle to BRAR Vector
	inline Vec4 BRAG() const;									//Swizzle to BRAG Vector
	inline Vec4 BRAB() const;									//Swizzle to BRAB Vector
	inline Vec4 BRAA() const;									//Swizzle to BRAA Vector
	inline Vec4 BGRR() const;									//Swizzle to BGRR Vector
	inline Vec4 BGRG() const;									//Swizzle to BGRG Vector
	inline Vec4 BGRB() const;									//Swizzle to BGRB Vector
	inline Vec4 BGRA() const;									//Swizzle to BGRA Vector
	inline Vec4 BGGR() const;									//Swizzle to BGGR Vector
	inline Vec4 BGGG() const;									//Swizzle to BGGG Vector
	inline Vec4 BGGB() const;									//Swizzle to BGGB Vector
	inline Vec4 BGGA() const;									//Swizzle to BGGA Vector
	inline Vec4 BGBR() const;									//Swizzle to BGBR Vector
	inline Vec4 BGBG() const;									//Swizzle to BGBG Vector
	inline Vec4 BGBB() const;									//Swizzle to BGBB Vector
	inline Vec4 BGBA() const;									//Swizzle to BGBA Vector
	inline Vec4 BGAR() const;									//Swizzle to BGAR Vector
	inline Vec4 BGAG() const;									//Swizzle to BGAG Vector
	inline Vec4 BGAB() const;									//Swizzle to BGAB Vector
	inline Vec4 BGAA() const;									//Swizzle to BGAA Vector
	inline Vec4 BBRR() const;									//Swizzle to BBRR Vector
	inline Vec4 BBRG() const;									//Swizzle to BBRG Vector
	inline Vec4 BBRB() const;									//Swizzle to BBRB Vector
	inline Vec4 BBRA() const;									//Swizzle to BBRA Vector
	inline Vec4 BBGR() const;									//Swizzle to BBGR Vector
	inline Vec4 BBGG() const;									//Swizzle to BBGG Vector
	inline Vec4 BBGB() const;									//Swizzle to BBGB Vector
	inline Vec4 BBGA() const;									//Swizzle to BBGA Vector
	inline Vec4 BBBR() const;									//Swizzle to BBBR Vector
	inline Vec4 BBBG() const;									//Swizzle to BBBG Vector
	inline Vec4 BBBB() const;									//Swizzle to BBBB Vector
	inline Vec4 BBBA() const;									//Swizzle to BBBA Vector
	inline Vec4 BBAR() const;									//Swizzle to BBAR Vector
	inline Vec4 BBAG() const;									//Swizzle to BBAG Vector
	inline Vec4 BBAB() const;									//Swizzle to BBAB Vector
	inline Vec4 BBAA() const;									//Swizzle to BBAA Vector
	inline Vec4 BARR() const;									//Swizzle to BARR Vector
	inline Vec4 BARG() const;									//Swizzle to BARG Vector
	inline Vec4 BARB() const;									//Swizzle to BARB Vector
	inline Vec4 BARA() const;									//Swizzle to BARA Vector
	inline Vec4 BAGR() const;									//Swizzle to BAGR Vector
	inline Vec4 BAGG() const;									//Swizzle to BAGG Vector
	inline Vec4 BAGB() const;									//Swizzle to BAGB Vector
	inline Vec4 BAGA() const;									//Swizzle to BAGA Vector
	inline Vec4 BABR() const;									//Swizzle to BABR Vector
	inline Vec4 BABG() const;									//Swizzle to BABG Vector
	inline Vec4 BABB() const;									//Swizzle to BABB Vector
	inline Vec4 BABA() const;									//Swizzle to BABA Vector
	inline Vec4 BAAR() const;									//Swizzle to BAAR Vector
	inline Vec4 BAAG() const;									//Swizzle to BAAG Vector
	inline Vec4 BAAB() const;									//Swizzle to BAAB Vector
	inline Vec4 BAAA() const;									//Swizzle to BAAA Vector
	inline Vec4 ARRR() const;									//Swizzle to ARRR Vector
	inline Vec4 ARRG() const;									//Swizzle to ARRG Vector
	inline Vec4 ARRB() const;									//Swizzle to ARRB Vector
	inline Vec4 ARRA() const;									//Swizzle to ARRA Vector
	inline Vec4 ARGR() const;									//Swizzle to ARGR Vector
	inline Vec4 ARGG() const;									//Swizzle to ARGG Vector
	inline Vec4 ARGB() const;									//Swizzle to ARGB Vector
	inline Vec4 ARGA() const;									//Swizzle to ARGA Vector
	inline Vec4 ARBR() const;									//Swizzle to ARBR Vector
	inline Vec4 ARBG() const;									//Swizzle to ARBG Vector
	inline Vec4 ARBB() const;									//Swizzle to ARBB Vector
	inline Vec4 ARBA() const;									//Swizzle to ARBA Vector
	inline Vec4 ARAR() const;									//Swizzle to ARAR Vector
	inline Vec4 ARAG() const;									//Swizzle to ARAG Vector
	inline Vec4 ARAB() const;									//Swizzle to ARAB Vector
	inline Vec4 ARAA() const;									//Swizzle to ARAA Vector
	inline Vec4 AGRR() const;									//Swizzle to AGRR Vector
	inline Vec4 AGRG() const;									//Swizzle to AGRG Vector
	inline Vec4 AGRB() const;									//Swizzle to AGRB Vector
	inline Vec4 AGRA() const;									//Swizzle to AGRA Vector
	inline Vec4 AGGR() const;									//Swizzle to AGGR Vector
	inline Vec4 AGGG() const;									//Swizzle to AGGG Vector
	inline Vec4 AGGB() const;									//Swizzle to AGGB Vector
	inline Vec4 AGGA() const;									//Swizzle to AGGA Vector
	inline Vec4 AGBR() const;									//Swizzle to AGBR Vector
	inline Vec4 AGBG() const;									//Swizzle to AGBG Vector
	inline Vec4 AGBB() const;									//Swizzle to AGBB Vector
	inline Vec4 AGBA() const;									//Swizzle to AGBA Vector
	inline Vec4 AGAR() const;									//Swizzle to AGAR Vector
	inline Vec4 AGAG() const;									//Swizzle to AGAG Vector
	inline Vec4 AGAB() const;									//Swizzle to AGAB Vector
	inline Vec4 AGAA() const;									//Swizzle to AGAA Vector
	inline Vec4 ABRR() const;									//Swizzle to ABRR Vector
	inline Vec4 ABRG() const;									//Swizzle to ABRG Vector
	inline Vec4 ABRB() const;									//Swizzle to ABRB Vector
	inline Vec4 ABRA() const;									//Swizzle to ABRA Vector
	inline Vec4 ABGR() const;									//Swizzle to ABGR Vector
	inline Vec4 ABGG() const;									//Swizzle to ABGG Vector
	inline Vec4 ABGB() const;									//Swizzle to ABGB Vector
	inline Vec4 ABGA() const;									//Swizzle to ABGA Vector
	inline Vec4 ABBR() const;									//Swizzle to ABBR Vector
	inline Vec4 ABBG() const;									//Swizzle to ABBG Vector
	inline Vec4 ABBB() const;									//Swizzle to ABBB Vector
	inline Vec4 ABBA() const;									//Swizzle to ABBA Vector
	inline Vec4 ABAR() const;									//Swizzle to ABAR Vector
	inline Vec4 ABAG() const;									//Swizzle to ABAG Vector
	inline Vec4 ABAB() const;									//Swizzle to ABAB Vector
	inline Vec4 ABAA() const;									//Swizzle to ABAA Vector
	inline Vec4 AARR() const;									//Swizzle to AARR Vector
	inline Vec4 AARG() const;									//Swizzle to AARG Vector
	inline Vec4 AARB() const;									//Swizzle to AARB Vector
	inline Vec4 AARA() const;									//Swizzle to AARA Vector
	inline Vec4 AAGR() const;									//Swizzle to AAGR Vector
	inline Vec4 AAGG() const;									//Swizzle to AAGG Vector
	inline Vec4 AAGB() const;									//Swizzle to AAGB Vector
	inline Vec4 AAGA() const;									//Swizzle to AAGA Vector
	inline Vec4 AABR() const;									//Swizzle to AABR Vector
	inline Vec4 AABG() const;									//Swizzle to AABG Vector
	inline Vec4 AABB() const;									//Swizzle to AABB Vector
	inline Vec4 AABA() const;									//Swizzle to AABA Vector
	inline Vec4 AAAR() const;									//Swizzle to AAAR Vector
	inline Vec4 AAAG() const;									//Swizzle to AAAG Vector
	inline Vec4 AAAB() const;									//Swizzle to AAAB Vector
	inline Vec4 AAAA() const;									//Swizzle to AAAA Vector
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