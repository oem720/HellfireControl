
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
		double xy[2];														//Array Storage
		struct {
			double x;														//X Member
			double y;														//Y Member
		};
	};
public:
	//Constructors
	inline Vec2Double();													//Init to Zero
	inline Vec2Double(double _x, double _y);								//Init to X and Y
	inline Vec2Double(const Vec2Double& _other);							//Init from Copy

	//Assignment
	inline Vec2Double& operator=(const Vec2Double& _other);					//Assignment
	inline Vec2Double& operator+=(const Vec2Double& _other);				//Addition
	inline Vec2Double& operator-=(const Vec2Double& _other);				//Subtraction
	inline Vec2Double& operator*=(const double _scale);						//Scaling
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec2Double operator+(const Vec2Double& _other) const;			//Addition
	inline Vec2Double operator-(const Vec2Double& _other) const;			//Subtraction
	inline Vec2Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec2Double& _other) const;				//Dot Product
	inline double operator&(const Vec2Double& _other) const;				//Cross Product
	inline Vec2Double operator~() const;									//Zero
	inline Vec2Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec2Double& _other) const;					//Check Equality
	inline bool operator<(const Vec2Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec2Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec2Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec2Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec2Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec2Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec2Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec2Double& _other) const;						//Dot Product
	inline double Cross(const Vec2Double& _other) const;					//Cross Product
	inline void Add(const Vec2Double& _other);								//Addition
	inline void Subtract(const Vec2Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec2Double& _other) const;						//Check Equality
	inline bool Less(const Vec2Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec2Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec2Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec2Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec2Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)

	//Swizzle Operations (Vec2Double)
	inline Vec2Double XX() const;											//Swizzle to XX Vector
	inline Vec2Double YY() const;											//Swizzle to YY Vector
	inline Vec2Double YX() const;											//Swizzle to YX Vector
	inline Vec2Double RR() const;											//Swizzle to RR Vector
	inline Vec2Double GG() const;											//Swizzle to GG Vector
	inline Vec2Double GR() const;											//Swizzle to GR Vector
};

class alignas(32) Vec3Double {
private:
	union {
		double xyz[3];														//Array Storage
		struct {
			double x;														//X Member
			double y;														//Y Member
			double z;														//Z Member
		};
	};
public:
	//Constructors
	inline Vec3Double();													//Init to Zero
	inline Vec3Double(double _x, double _y, double _z);						//Init to X, Y, and Z
	inline Vec3Double(const Vec2Double& _xy, double _z);							//Init from a Vec2 for X and Y, and from a double for Z
	inline Vec3Double(double _x, const Vec2Double& _yz);							//Init from X, and from a Vec2 for Y and Z
	inline Vec3Double(const Vec3Double& _other);							//Init from Copy

	//Assignment
	inline Vec3Double& operator=(const Vec3Double& _other);					//Assignment
	inline Vec3Double& operator+=(const Vec3Double& _other);				//Addition
	inline Vec3Double& operator-=(const Vec3Double& _other);				//Subtraction
	inline Vec3Double& operator*=(const double _scale);						//Scaling
	inline Vec3Double& operator&=(const Vec3Double& _other);				//Cross Product
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec3Double operator+(const Vec3Double& _other) const;			//Addition
	inline Vec3Double operator-(const Vec3Double& _other) const;			//Subtraction
	inline Vec3Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec3Double& _other) const;				//Dot Product
	inline Vec3Double operator&(const Vec3Double& _other) const;			//Cross Product
	inline Vec3Double operator~() const;									//Zero
	inline Vec3Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec3Double& _other) const;					//Check Equality
	inline bool operator<(const Vec3Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec3Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec3Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec3Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec3Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec3Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec3Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec3Double& _other) const;						//Dot Product
	inline void Cross(const Vec3Double& _other);							//Cross Product
	inline void Add(const Vec3Double& _other);								//Addition
	inline void Subtract(const Vec3Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec3Double& _other) const;						//Check Equality
	inline bool Less(const Vec3Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec3Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec3Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec3Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec3Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double& Z();														//Vector Z Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)
	inline double Z() const;												//Vector Z Component (Const)

	//Swizzle Operations (Vec2DoubleDouble)
	inline Vec2Double XX() const;													//Swizzle to XX Vector
	inline Vec2Double YY() const;													//Swizzle to YY Vector
	inline Vec2Double ZZ() const;													//Swizzle to ZZ Vector
	inline Vec2Double XY() const;													//Swizzle to XY Vector
	inline Vec2Double XZ() const;													//Swizzle to XZ Vector
	inline Vec2Double YX() const;													//Swizzle to YX Vector
	inline Vec2Double YZ() const;													//Swizzle to YZ Vector
	inline Vec2Double ZX() const;													//Swizzle to ZX Vector
	inline Vec2Double ZY() const;													//Swizzle to ZY Vector
	inline Vec2Double RR() const;													//Swizzle to RR Vector
	inline Vec2Double GG() const;													//Swizzle to GG Vector
	inline Vec2Double BB() const;													//Swizzle to BB Vector
	inline Vec2Double RG() const;													//Swizzle to RG Vector
	inline Vec2Double RB() const;													//Swizzle to RB Vector
	inline Vec2Double GR() const;													//Swizzle to GR Vector
	inline Vec2Double GB() const;													//Swizzle to GB Vector
	inline Vec2Double BR() const;													//Swizzle to BR Vector
	inline Vec2Double BG() const;													//Swizzle to BG Vector

	//Swizzle Operations (Vec3Double)
	inline Vec3Double XXX() const;											//Swizzle to XXX Vector
	inline Vec3Double XXY() const;											//Swizzle to XXY Vector
	inline Vec3Double XXZ() const;											//Swizzle to XXZ Vector
	inline Vec3Double XYX() const;											//Swizzle to XYX Vector
	inline Vec3Double XYY() const;											//Swizzle to XYY Vector
	inline Vec3Double XZX() const;											//Swizzle to XZX Vector
	inline Vec3Double XZY() const;											//Swizzle to XZY Vector
	inline Vec3Double XZZ() const;											//Swizzle to XZZ Vector
	inline Vec3Double YXX() const;											//Swizzle to YXX Vector
	inline Vec3Double YXY() const;											//Swizzle to YXY Vector
	inline Vec3Double YXZ() const;											//Swizzle to YXZ Vector
	inline Vec3Double YYX() const;											//Swizzle to YYX Vector
	inline Vec3Double YYY() const;											//Swizzle to YYY Vector
	inline Vec3Double YYZ() const;											//Swizzle to YYZ Vector
	inline Vec3Double YZX() const;											//Swizzle to YZX Vector
	inline Vec3Double YZY() const;											//Swizzle to YZY Vector
	inline Vec3Double YZZ() const;											//Swizzle to YZZ Vector
	inline Vec3Double ZXX() const;											//Swizzle to ZXX Vector
	inline Vec3Double ZXY() const;											//Swizzle to ZXY Vector
	inline Vec3Double ZXZ() const;											//Swizzle to ZXZ Vector
	inline Vec3Double ZYX() const;											//Swizzle to ZYX Vector
	inline Vec3Double ZYY() const;											//Swizzle to ZYY Vector
	inline Vec3Double ZYZ() const;											//Swizzle to ZYZ Vector
	inline Vec3Double ZZX() const;											//Swizzle to ZZX Vector
	inline Vec3Double ZZY() const;											//Swizzle to ZZY Vector
	inline Vec3Double ZZZ() const;											//Swizzle to ZZZ Vector
	inline Vec3Double RRR() const;											//Swizzle to RRR Vector
	inline Vec3Double RRG() const;											//Swizzle to RRG Vector
	inline Vec3Double RRB() const;											//Swizzle to RRB Vector
	inline Vec3Double RGR() const;											//Swizzle to RGR Vector
	inline Vec3Double RGG() const;											//Swizzle to RGG Vector
	inline Vec3Double RBR() const;											//Swizzle to RBR Vector
	inline Vec3Double RBG() const;											//Swizzle to RBG Vector
	inline Vec3Double RBB() const;											//Swizzle to RBB Vector
	inline Vec3Double GRR() const;											//Swizzle to GRR Vector
	inline Vec3Double GRG() const;											//Swizzle to GRG Vector
	inline Vec3Double GRB() const;											//Swizzle to GRB Vector
	inline Vec3Double GGR() const;											//Swizzle to GGR Vector
	inline Vec3Double GGG() const;											//Swizzle to GGG Vector
	inline Vec3Double GGB() const;											//Swizzle to GGB Vector
	inline Vec3Double GBR() const;											//Swizzle to GBR Vector
	inline Vec3Double GBG() const;											//Swizzle to GBG Vector
	inline Vec3Double GBB() const;											//Swizzle to GBB Vector
	inline Vec3Double BRR() const;											//Swizzle to BRR Vector
	inline Vec3Double BRG() const;											//Swizzle to BRG Vector
	inline Vec3Double BRB() const;											//Swizzle to BRB Vector
	inline Vec3Double BGR() const;											//Swizzle to BGR Vector
	inline Vec3Double BGG() const;											//Swizzle to BGG Vector
	inline Vec3Double BGB() const;											//Swizzle to BGB Vector
	inline Vec3Double BBR() const;											//Swizzle to BBR Vector
	inline Vec3Double BBG() const;											//Swizzle to BBG Vector
	inline Vec3Double BBB() const;											//Swizzle to BBB Vector
};

class alignas(32) Vec4Double {
private:
	union {
		double xyzw[4];														//Array Storage
		struct {
			double x;														//X Member
			double y;														//Y Member
			double z;														//Z Member
			double w;														//W Member
		};
	};
public:
	//Constructors
	inline Vec4Double();													//Init to Zero
	inline Vec4Double(double _x, double _y, double _z, double _w);			//Init to X, Y, Z, and W
	inline Vec4Double(const Vec2Double& _xy, double _z, double _w);			//Init from a Vec2Double for X and Y, and from a double for Z and W
	inline Vec4Double(double _x, const Vec2Double& _yz, double _w);			//Init from X, from a Vec2Double for Y and Z and a double for W
	inline Vec4Double(double _x, double _y, const Vec2Double& _zw);			//Init from X and Y, and from a Vec2Double for Z and W
	inline Vec4Double(const Vec2Double& _xy, const Vec2Double& _zw);		//Init from 2 Vec2Double's
	inline Vec4Double(const Vec3Double& _xyz, double _w);					//Init from a Vec3Double and a double for W
	inline Vec4Double(double _x, const Vec3Double& _yzw);					//Init from a double for X and a Vec3Double
	inline Vec4Double(const Vec4Double& _other);							//Init from Copy

	//Assignment
	inline Vec4Double& operator=(const Vec4Double& _other);					//Assignment
	inline Vec4Double& operator+=(const Vec4Double& _other);				//Addition
	inline Vec4Double& operator-=(const Vec4Double& _other);				//Subtraction
	inline Vec4Double& operator*=(const double _scale);						//Scaling
	inline Vec4Double& operator&=(const Vec4Double& _other);				//Cross Product
	inline double& operator[](int _ndx);									//Array access (Modifiable)
	inline double operator[](int _ndx) const;								//Array access (Const)

	//Arithmetic
	inline Vec4Double operator+(const Vec4Double& _other) const;			//Addition
	inline Vec4Double operator-(const Vec4Double& _other) const;			//Subtraction
	inline Vec4Double operator*(const double _scale) const;					//Scaling
	inline double operator*(const Vec4Double& _other) const;				//Dot Product
	inline Vec4Double operator&(const Vec4Double& _other) const;			//Cross Product
	inline Vec4Double operator~() const;									//Zero
	inline Vec4Double operator-() const;									//Negate

	//Comparison
	inline bool operator==(const Vec4Double& _other) const;					//Check Equality
	inline bool operator<(const Vec4Double& _other) const;					//Check Less Than
	inline bool operator>(const Vec4Double& _other) const;					//Check Greater Than
	inline bool operator<=(const Vec4Double& _other) const;					//Check Less Than or Equal To
	inline bool operator>=(const Vec4Double& _other) const;					//Check Greater Than or Equal To
	inline bool operator!=(const Vec4Double& _other) const;					//Check Not Equal

	//Measurement
	inline double Length() const;											//Vector Length
	inline double LengthSquared() const;									//Vector Length Squared
	inline void Normalize();												//Vector Normalize
	inline Vec4Double Normalized() const;									//Return Normalized Version of this Vector
	inline double AngleBetween(const Vec4Double& _other) const;				//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline double Dot(const Vec4Double& _other) const;						//Dot Product
	inline void Cross(const Vec4Double& _other);							//Cross Product
	inline void Add(const Vec4Double& _other);								//Addition
	inline void Subtract(const Vec4Double& _other);							//Subtraction
	inline void Scale(const double _scale);									//Scaling
	inline void Negate();													//Negate
	inline void Zero();														//Zero
	inline bool Equals(const Vec4Double& _other) const;						//Check Equality
	inline bool Less(const Vec4Double& _other) const;						//Check Less Than
	inline bool LessThanOrEquals(const Vec4Double& _other) const;			//Check Less Than or Equal To
	inline bool Greater(const Vec4Double& _other) const;					//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec4Double& _other) const;		//Check Greater Than or Equal To
	inline bool NotEquals(const Vec4Double& _other) const;					//Check Not Equal

	//Member Modification
	inline double& X();														//Vector X Component (Modifiable)
	inline double& Y();														//Vector Y Component (Modifiable)
	inline double& Z();														//Vector Z Component (Modifiable)
	inline double& W();														//Vector W Component (Modifiable)
	inline double X() const;												//Vector X Component (Const)
	inline double Y() const;												//Vector Y Component (Const)
	inline double Z() const;												//Vector Z Component (Const)
	inline double W() const;												//Vector W Component (Const)

	//Swizzle Operations (Vec2Double)
	inline Vec2Double XX() const;											//Swizzle to XX Vector
	inline Vec2Double YY() const;											//Swizzle to YY Vector
	inline Vec2Double ZZ() const;											//Swizzle to ZZ Vector
	inline Vec2Double WW() const;											//Swizzle to WW Vector
	inline Vec2Double XY() const;											//Swizzle to XY Vector
	inline Vec2Double XZ() const;											//Swizzle to XZ Vector
	inline Vec2Double XW() const;											//Swizzle to XW Vector
	inline Vec2Double YX() const;											//Swizzle to YX Vector
	inline Vec2Double YZ() const;											//Swizzle to YZ Vector
	inline Vec2Double YW() const;											//Swizzle to YW Vector
	inline Vec2Double ZX() const;											//Swizzle to ZX Vector
	inline Vec2Double ZY() const;											//Swizzle to ZY Vector
	inline Vec2Double ZW() const;											//Swizzle to ZW Vector
	inline Vec2Double WX() const;											//Swizzle to WX Vector
	inline Vec2Double WY() const;											//Swizzle to WY Vector
	inline Vec2Double WZ() const;											//Swizzle to WZ Vector
	inline Vec2Double RR() const;											//Swizzle to RR Vector
	inline Vec2Double GG() const;											//Swizzle to GG Vector
	inline Vec2Double BB() const;											//Swizzle to BB Vector
	inline Vec2Double AA() const;											//Swizzle to AA Vector
	inline Vec2Double RG() const;											//Swizzle to RG Vector
	inline Vec2Double RB() const;											//Swizzle to RB Vector
	inline Vec2Double RA() const;											//Swizzle to RA Vector
	inline Vec2Double GR() const;											//Swizzle to GR Vector
	inline Vec2Double GB() const;											//Swizzle to GB Vector
	inline Vec2Double GA() const;											//Swizzle to GA Vector
	inline Vec2Double BR() const;											//Swizzle to BR Vector
	inline Vec2Double BG() const;											//Swizzle to BG Vector
	inline Vec2Double BA() const;											//Swizzle to BA Vector
	inline Vec2Double AR() const;											//Swizzle to AR Vector
	inline Vec2Double AG() const;											//Swizzle to AG Vector
	inline Vec2Double AB() const;											//Swizzle to AB Vector

	//Swizzle Operations (Vec3Double)
	inline Vec3Double XXX() const;											//Swizzle to XXX Vector
	inline Vec3Double XXY() const;											//Swizzle to XXY Vector
	inline Vec3Double XXZ() const;											//Swizzle to XXZ Vector
	inline Vec3Double XXW() const;											//Swizzle to XXW Vector
	inline Vec3Double XYX() const;											//Swizzle to XYX Vector
	inline Vec3Double XYY() const;											//Swizzle to XYY Vector
	inline Vec3Double XYZ() const;											//Swizzle to XYZ Vector
	inline Vec3Double XYW() const;											//Swizzle to XYW Vector
	inline Vec3Double XZX() const;											//Swizzle to XZX Vector
	inline Vec3Double XZY() const;											//Swizzle to XZY Vector
	inline Vec3Double XZZ() const;											//Swizzle to XZZ Vector
	inline Vec3Double XZW() const;											//Swizzle to XZW Vector
	inline Vec3Double XWX() const;											//Swizzle to XWX Vector
	inline Vec3Double XWY() const;											//Swizzle to XWY Vector
	inline Vec3Double XWZ() const;											//Swizzle to XWZ Vector
	inline Vec3Double XWW() const;											//Swizzle to XWW Vector
	inline Vec3Double YXX() const;											//Swizzle to YXX Vector
	inline Vec3Double YXY() const;											//Swizzle to YXY Vector
	inline Vec3Double YXZ() const;											//Swizzle to YXZ Vector
	inline Vec3Double YXW() const;											//Swizzle to YXW Vector
	inline Vec3Double YYX() const;											//Swizzle to YYX Vector
	inline Vec3Double YYY() const;											//Swizzle to YYY Vector
	inline Vec3Double YYZ() const;											//Swizzle to YYZ Vector
	inline Vec3Double YYW() const;											//Swizzle to YYW Vector
	inline Vec3Double YZX() const;											//Swizzle to YZX Vector
	inline Vec3Double YZY() const;											//Swizzle to YZY Vector
	inline Vec3Double YZZ() const;											//Swizzle to YZZ Vector
	inline Vec3Double YZW() const;											//Swizzle to YZW Vector
	inline Vec3Double YWX() const;											//Swizzle to YWX Vector
	inline Vec3Double YWY() const;											//Swizzle to YWY Vector
	inline Vec3Double YWZ() const;											//Swizzle to YWZ Vector
	inline Vec3Double YWW() const;											//Swizzle to YWW Vector
	inline Vec3Double ZXX() const;											//Swizzle to ZXX Vector
	inline Vec3Double ZXY() const;											//Swizzle to ZXY Vector
	inline Vec3Double ZXZ() const;											//Swizzle to ZXZ Vector
	inline Vec3Double ZXW() const;											//Swizzle to ZXW Vector
	inline Vec3Double ZYX() const;											//Swizzle to ZYX Vector
	inline Vec3Double ZYY() const;											//Swizzle to ZYY Vector
	inline Vec3Double ZYZ() const;											//Swizzle to ZYZ Vector
	inline Vec3Double ZYW() const;											//Swizzle to ZYW Vector
	inline Vec3Double ZZX() const;											//Swizzle to ZZX Vector
	inline Vec3Double ZZY() const;											//Swizzle to ZZY Vector
	inline Vec3Double ZZZ() const;											//Swizzle to ZZZ Vector
	inline Vec3Double ZZW() const;											//Swizzle to ZZW Vector
	inline Vec3Double ZWX() const;											//Swizzle to ZWX Vector
	inline Vec3Double ZWY() const;											//Swizzle to ZWY Vector
	inline Vec3Double ZWZ() const;											//Swizzle to ZWZ Vector
	inline Vec3Double ZWW() const;											//Swizzle to ZWW Vector
	inline Vec3Double WXX() const;											//Swizzle to WXX Vector
	inline Vec3Double WXY() const;											//Swizzle to WXY Vector
	inline Vec3Double WXZ() const;											//Swizzle to WXZ Vector
	inline Vec3Double WXW() const;											//Swizzle to WXW Vector
	inline Vec3Double WYX() const;											//Swizzle to WYX Vector
	inline Vec3Double WYY() const;											//Swizzle to WYY Vector
	inline Vec3Double WYZ() const;											//Swizzle to WYZ Vector
	inline Vec3Double WYW() const;											//Swizzle to WYW Vector
	inline Vec3Double WZX() const;											//Swizzle to WZX Vector
	inline Vec3Double WZY() const;											//Swizzle to WZY Vector
	inline Vec3Double WZZ() const;											//Swizzle to WZZ Vector
	inline Vec3Double WZW() const;											//Swizzle to WZW Vector
	inline Vec3Double WWX() const;											//Swizzle to WWX Vector
	inline Vec3Double WWY() const;											//Swizzle to WWY Vector
	inline Vec3Double WWZ() const;											//Swizzle to WWZ Vector
	inline Vec3Double WWW() const;											//Swizzle to WWW Vector
	inline Vec3Double RRR() const;											//Swizzle to RRR Vector
	inline Vec3Double RRG() const;											//Swizzle to RRG Vector
	inline Vec3Double RRB() const;											//Swizzle to RRB Vector
	inline Vec3Double RRA() const;											//Swizzle to RRA Vector
	inline Vec3Double RGR() const;											//Swizzle to RGR Vector
	inline Vec3Double RGG() const;											//Swizzle to RGG Vector
	inline Vec3Double RGA() const;											//Swizzle to RGA Vector
	inline Vec3Double RGB() const;											//Swizzle to RGB Vector
	inline Vec3Double RBR() const;											//Swizzle to RBR Vector
	inline Vec3Double RBG() const;											//Swizzle to RBG Vector
	inline Vec3Double RBB() const;											//Swizzle to RBB Vector
	inline Vec3Double RBA() const;											//Swizzle to RBA Vector
	inline Vec3Double RAR() const;											//Swizzle to RAR Vector
	inline Vec3Double RAG() const;											//Swizzle to RAG Vector
	inline Vec3Double RAB() const;											//Swizzle to RAB Vector
	inline Vec3Double RAA() const;											//Swizzle to RAA Vector
	inline Vec3Double GRR() const;											//Swizzle to GRR Vector
	inline Vec3Double GRG() const;											//Swizzle to GRG Vector
	inline Vec3Double GRB() const;											//Swizzle to GRB Vector
	inline Vec3Double GRA() const;											//Swizzle to GRA Vector
	inline Vec3Double GGR() const;											//Swizzle to GGR Vector
	inline Vec3Double GGG() const;											//Swizzle to GGG Vector
	inline Vec3Double GGB() const;											//Swizzle to GGB Vector
	inline Vec3Double GGA() const;											//Swizzle to GGA Vector
	inline Vec3Double GBR() const;											//Swizzle to GBR Vector
	inline Vec3Double GBG() const;											//Swizzle to GBG Vector
	inline Vec3Double GBB() const;											//Swizzle to GBB Vector
	inline Vec3Double GBA() const;											//Swizzle to GBA Vector
	inline Vec3Double GAR() const;											//Swizzle to GAR Vector
	inline Vec3Double GAG() const;											//Swizzle to GAG Vector
	inline Vec3Double GAB() const;											//Swizzle to GAB Vector
	inline Vec3Double GAA() const;											//Swizzle to GAA Vector
	inline Vec3Double BRR() const;											//Swizzle to BRR Vector
	inline Vec3Double BRG() const;											//Swizzle to BRG Vector
	inline Vec3Double BRB() const;											//Swizzle to BRB Vector
	inline Vec3Double BRA() const;											//Swizzle to BRA Vector
	inline Vec3Double BGR() const;											//Swizzle to BGR Vector
	inline Vec3Double BGG() const;											//Swizzle to BGG Vector
	inline Vec3Double BGB() const;											//Swizzle to BGB Vector
	inline Vec3Double BGA() const;											//Swizzle to BGA Vector
	inline Vec3Double BBR() const;											//Swizzle to BBR Vector
	inline Vec3Double BBG() const;											//Swizzle to BBG Vector
	inline Vec3Double BBB() const;											//Swizzle to BBB Vector
	inline Vec3Double BBA() const;											//Swizzle to BBA Vector
	inline Vec3Double BAR() const;											//Swizzle to BAR Vector
	inline Vec3Double BAG() const;											//Swizzle to BAG Vector
	inline Vec3Double BAB() const;											//Swizzle to BAB Vector
	inline Vec3Double BAA() const;											//Swizzle to BAA Vector
	inline Vec3Double ARR() const;											//Swizzle to ARR Vector
	inline Vec3Double ARG() const;											//Swizzle to ARG Vector
	inline Vec3Double ARB() const;											//Swizzle to ARB Vector
	inline Vec3Double ARA() const;											//Swizzle to ARA Vector
	inline Vec3Double AGR() const;											//Swizzle to AGR Vector
	inline Vec3Double AGG() const;											//Swizzle to AGG Vector
	inline Vec3Double AGB() const;											//Swizzle to AGB Vector
	inline Vec3Double AGA() const;											//Swizzle to AGA Vector
	inline Vec3Double ABR() const;											//Swizzle to ABR Vector
	inline Vec3Double ABG() const;											//Swizzle to ABG Vector
	inline Vec3Double ABB() const;											//Swizzle to ABB Vector
	inline Vec3Double ABA() const;											//Swizzle to ABA Vector
	inline Vec3Double AAR() const;											//Swizzle to AAR Vector
	inline Vec3Double AAG() const;											//Swizzle to AAG Vector
	inline Vec3Double AAB() const;											//Swizzle to AAB Vector
	inline Vec3Double AAA() const;											//Swizzle to AAA Vector

	//Swizzle Operations (Vec4Double)
	inline Vec4Double XXXX() const;											//Swizzle to XXXX Vector
	inline Vec4Double XXXY() const;											//Swizzle to XXXY Vector
	inline Vec4Double XXXZ() const;											//Swizzle to XXXZ Vector
	inline Vec4Double XXXW() const;											//Swizzle to XXXW Vector
	inline Vec4Double XXYX() const;											//Swizzle to XXYX Vector
	inline Vec4Double XXYY() const;											//Swizzle to XXYY Vector
	inline Vec4Double XXYZ() const;											//Swizzle to XXYZ Vector
	inline Vec4Double XXYW() const;											//Swizzle to XXYW Vector
	inline Vec4Double XXZX() const;											//Swizzle to XXZX Vector
	inline Vec4Double XXZY() const;											//Swizzle to XXZY Vector
	inline Vec4Double XXZZ() const;											//Swizzle to XXZZ Vector
	inline Vec4Double XXZW() const;											//Swizzle to XXZW Vector
	inline Vec4Double XXWX() const;											//Swizzle to XXWX Vector
	inline Vec4Double XXWY() const;											//Swizzle to XXWY Vector
	inline Vec4Double XXWZ() const;											//Swizzle to XXWZ Vector
	inline Vec4Double XXWW() const;											//Swizzle to XXWW Vector
	inline Vec4Double XYXX() const;											//Swizzle to XYXX Vector
	inline Vec4Double XYXY() const;											//Swizzle to XYXY Vector
	inline Vec4Double XYXZ() const;											//Swizzle to XYXZ Vector
	inline Vec4Double XYXW() const;											//Swizzle to XYXW Vector
	inline Vec4Double XYYX() const;											//Swizzle to XYYX Vector
	inline Vec4Double XYYY() const;											//Swizzle to XYYY Vector
	inline Vec4Double XYYZ() const;											//Swizzle to XYYZ Vector
	inline Vec4Double XYYW() const;											//Swizzle to XYYW Vector
	inline Vec4Double XYZX() const;											//Swizzle to XYZX Vector
	inline Vec4Double XYZY() const;											//Swizzle to XYZY Vector
	inline Vec4Double XYZZ() const;											//Swizzle to XYZZ Vector
	inline Vec4Double XYWX() const;											//Swizzle to XYWX Vector
	inline Vec4Double XYWY() const;											//Swizzle to XYWY Vector
	inline Vec4Double XYWZ() const;											//Swizzle to XYWZ Vector
	inline Vec4Double XYWW() const;											//Swizzle to XYWW Vector
	inline Vec4Double XZXX() const;											//Swizzle to XZXX Vector
	inline Vec4Double XZXY() const;											//Swizzle to XZXY Vector
	inline Vec4Double XZXZ() const;											//Swizzle to XZXZ Vector
	inline Vec4Double XZXW() const;											//Swizzle to XZXW Vector
	inline Vec4Double XZYX() const;											//Swizzle to XZYX Vector
	inline Vec4Double XZYY() const;											//Swizzle to XZYY Vector
	inline Vec4Double XZYZ() const;											//Swizzle to XZYZ Vector
	inline Vec4Double XZYW() const;											//Swizzle to XZYW Vector
	inline Vec4Double XZZX() const;											//Swizzle to XZZX Vector
	inline Vec4Double XZZY() const;											//Swizzle to XZZY Vector
	inline Vec4Double XZZZ() const;											//Swizzle to XZZZ Vector
	inline Vec4Double XZZW() const;											//Swizzle to XZZW Vector
	inline Vec4Double XZWX() const;											//Swizzle to XZWX Vector
	inline Vec4Double XZWY() const;											//Swizzle to XZWY Vector
	inline Vec4Double XZWZ() const;											//Swizzle to XZWZ Vector
	inline Vec4Double XZWW() const;											//Swizzle to XZWW Vector
	inline Vec4Double XWXX() const;											//Swizzle to XWXX Vector
	inline Vec4Double XWXY() const;											//Swizzle to XWXY Vector
	inline Vec4Double XWXZ() const;											//Swizzle to XWXZ Vector
	inline Vec4Double XWXW() const;											//Swizzle to XWXW Vector
	inline Vec4Double XWYX() const;											//Swizzle to XWYX Vector
	inline Vec4Double XWYY() const;											//Swizzle to XWYY Vector
	inline Vec4Double XWYZ() const;											//Swizzle to XWYZ Vector
	inline Vec4Double XWYW() const;											//Swizzle to XWYW Vector
	inline Vec4Double XWZX() const;											//Swizzle to XWZX Vector
	inline Vec4Double XWZY() const;											//Swizzle to XWZY Vector
	inline Vec4Double XWZZ() const;											//Swizzle to XWZZ Vector
	inline Vec4Double XWZW() const;											//Swizzle to XWZW Vector
	inline Vec4Double XWWX() const;											//Swizzle to XWWX Vector
	inline Vec4Double XWWY() const;											//Swizzle to XWWY Vector
	inline Vec4Double XWWZ() const;											//Swizzle to XWWZ Vector
	inline Vec4Double XWWW() const;											//Swizzle to XWWW Vector
	inline Vec4Double YXXX() const;											//Swizzle to YXXX Vector
	inline Vec4Double YXXY() const;											//Swizzle to YXXY Vector
	inline Vec4Double YXXZ() const;											//Swizzle to YXXZ Vector
	inline Vec4Double YXXW() const;											//Swizzle to YXXW Vector
	inline Vec4Double YXYX() const;											//Swizzle to YXYX Vector
	inline Vec4Double YXYY() const;											//Swizzle to YXYY Vector
	inline Vec4Double YXYZ() const;											//Swizzle to YXYZ Vector
	inline Vec4Double YXYW() const;											//Swizzle to YXYW Vector
	inline Vec4Double YXZX() const;											//Swizzle to YXZX Vector
	inline Vec4Double YXZY() const;											//Swizzle to YXZY Vector
	inline Vec4Double YXZZ() const;											//Swizzle to YXZZ Vector
	inline Vec4Double YXZW() const;											//Swizzle to YXZW Vector
	inline Vec4Double YXWX() const;											//Swizzle to YXWX Vector
	inline Vec4Double YXWY() const;											//Swizzle to YXWY Vector
	inline Vec4Double YXWZ() const;											//Swizzle to YXWZ Vector
	inline Vec4Double YXWW() const;											//Swizzle to YXWW Vector
	inline Vec4Double YYXX() const;											//Swizzle to YYXX Vector
	inline Vec4Double YYXY() const;											//Swizzle to YYXY Vector
	inline Vec4Double YYXZ() const;											//Swizzle to YYXZ Vector
	inline Vec4Double YYXW() const;											//Swizzle to YYXW Vector
	inline Vec4Double YYYX() const;											//Swizzle to YYYX Vector
	inline Vec4Double YYYY() const;											//Swizzle to YYYY Vector
	inline Vec4Double YYYZ() const;											//Swizzle to YYYZ Vector
	inline Vec4Double YYYW() const;											//Swizzle to YYYW Vector
	inline Vec4Double YYZX() const;											//Swizzle to YYZX Vector
	inline Vec4Double YYZY() const;											//Swizzle to YYZY Vector
	inline Vec4Double YYZZ() const;											//Swizzle to YYZZ Vector
	inline Vec4Double YYZW() const;											//Swizzle to YYZW Vector
	inline Vec4Double YYWX() const;											//Swizzle to YYWX Vector
	inline Vec4Double YYWY() const;											//Swizzle to YYWY Vector
	inline Vec4Double YYWZ() const;											//Swizzle to YYWZ Vector
	inline Vec4Double YYWW() const;											//Swizzle to YYWW Vector
	inline Vec4Double YZXX() const;											//Swizzle to YZXX Vector
	inline Vec4Double YZXY() const;											//Swizzle to YZXY Vector
	inline Vec4Double YZXZ() const;											//Swizzle to YZXZ Vector
	inline Vec4Double YZXW() const;											//Swizzle to YZXW Vector
	inline Vec4Double YZYX() const;											//Swizzle to YZYX Vector
	inline Vec4Double YZYY() const;											//Swizzle to YZYY Vector
	inline Vec4Double YZYZ() const;											//Swizzle to YZYZ Vector
	inline Vec4Double YZYW() const;											//Swizzle to YZYW Vector
	inline Vec4Double YZZX() const;											//Swizzle to YZZX Vector
	inline Vec4Double YZZY() const;											//Swizzle to YZZY Vector
	inline Vec4Double YZZZ() const;											//Swizzle to YZZZ Vector
	inline Vec4Double YZZW() const;											//Swizzle to YZZW Vector
	inline Vec4Double YZWX() const;											//Swizzle to YZWX Vector
	inline Vec4Double YZWY() const;											//Swizzle to YZWY Vector
	inline Vec4Double YZWZ() const;											//Swizzle to YZWZ Vector
	inline Vec4Double YZWW() const;											//Swizzle to YZWW Vector
	inline Vec4Double YWXX() const;											//Swizzle to YWXX Vector
	inline Vec4Double YWXY() const;											//Swizzle to YWXY Vector
	inline Vec4Double YWXZ() const;											//Swizzle to YWXZ Vector
	inline Vec4Double YWXW() const;											//Swizzle to YWXW Vector
	inline Vec4Double YWYX() const;											//Swizzle to YWYX Vector
	inline Vec4Double YWYY() const;											//Swizzle to YWYY Vector
	inline Vec4Double YWYZ() const;											//Swizzle to YWYZ Vector
	inline Vec4Double YWYW() const;											//Swizzle to YWYW Vector
	inline Vec4Double YWZX() const;											//Swizzle to YWZX Vector
	inline Vec4Double YWZY() const;											//Swizzle to YWZY Vector
	inline Vec4Double YWZZ() const;											//Swizzle to YWZZ Vector
	inline Vec4Double YWZW() const;											//Swizzle to YWZW Vector
	inline Vec4Double YWWX() const;											//Swizzle to YWWX Vector
	inline Vec4Double YWWY() const;											//Swizzle to YWWY Vector
	inline Vec4Double YWWZ() const;											//Swizzle to YWWZ Vector
	inline Vec4Double YWWW() const;											//Swizzle to YWWW Vector
	inline Vec4Double ZXXX() const;											//Swizzle to ZXXX Vector
	inline Vec4Double ZXXY() const;											//Swizzle to ZXXY Vector
	inline Vec4Double ZXXZ() const;											//Swizzle to ZXXZ Vector
	inline Vec4Double ZXXW() const;											//Swizzle to ZXXW Vector
	inline Vec4Double ZXYX() const;											//Swizzle to ZXYX Vector
	inline Vec4Double ZXYY() const;											//Swizzle to ZXYY Vector
	inline Vec4Double ZXYZ() const;											//Swizzle to ZXYZ Vector
	inline Vec4Double ZXYW() const;											//Swizzle to ZXYW Vector
	inline Vec4Double ZXZX() const;											//Swizzle to ZXZX Vector
	inline Vec4Double ZXZY() const;											//Swizzle to ZXZY Vector
	inline Vec4Double ZXZZ() const;											//Swizzle to ZXZZ Vector
	inline Vec4Double ZXZW() const;											//Swizzle to ZXZW Vector
	inline Vec4Double ZXWX() const;											//Swizzle to ZXWX Vector
	inline Vec4Double ZXWY() const;											//Swizzle to ZXWY Vector
	inline Vec4Double ZXWZ() const;											//Swizzle to ZXWZ Vector
	inline Vec4Double ZXWW() const;											//Swizzle to ZXWW Vector
	inline Vec4Double ZYXX() const;											//Swizzle to ZYXX Vector
	inline Vec4Double ZYXY() const;											//Swizzle to ZYXY Vector
	inline Vec4Double ZYXZ() const;											//Swizzle to ZYXZ Vector
	inline Vec4Double ZYXW() const;											//Swizzle to ZYXW Vector
	inline Vec4Double ZYYX() const;											//Swizzle to ZYYX Vector
	inline Vec4Double ZYYY() const;											//Swizzle to ZYYY Vector
	inline Vec4Double ZYYZ() const;											//Swizzle to ZYYZ Vector
	inline Vec4Double ZYYW() const;											//Swizzle to ZYYW Vector
	inline Vec4Double ZYZX() const;											//Swizzle to ZYZX Vector
	inline Vec4Double ZYZY() const;											//Swizzle to ZYZY Vector
	inline Vec4Double ZYZZ() const;											//Swizzle to ZYZZ Vector
	inline Vec4Double ZYZW() const;											//Swizzle to ZYZW Vector
	inline Vec4Double ZYWX() const;											//Swizzle to ZYWX Vector
	inline Vec4Double ZYWY() const;											//Swizzle to ZYWY Vector
	inline Vec4Double ZYWZ() const;											//Swizzle to ZYWZ Vector
	inline Vec4Double ZYWW() const;											//Swizzle to ZYWW Vector
	inline Vec4Double ZZXX() const;											//Swizzle to ZZXX Vector
	inline Vec4Double ZZXY() const;											//Swizzle to ZZXY Vector
	inline Vec4Double ZZXZ() const;											//Swizzle to ZZXZ Vector
	inline Vec4Double ZZXW() const;											//Swizzle to ZZXW Vector
	inline Vec4Double ZZYX() const;											//Swizzle to ZZYX Vector
	inline Vec4Double ZZYY() const;											//Swizzle to ZZYY Vector
	inline Vec4Double ZZYZ() const;											//Swizzle to ZZYZ Vector
	inline Vec4Double ZZYW() const;											//Swizzle to ZZYW Vector
	inline Vec4Double ZZZX() const;											//Swizzle to ZZZX Vector
	inline Vec4Double ZZZY() const;											//Swizzle to ZZZY Vector
	inline Vec4Double ZZZZ() const;											//Swizzle to ZZZZ Vector
	inline Vec4Double ZZZW() const;											//Swizzle to ZZZW Vector
	inline Vec4Double ZZWX() const;											//Swizzle to ZZWX Vector
	inline Vec4Double ZZWY() const;											//Swizzle to ZZWY Vector
	inline Vec4Double ZZWZ() const;											//Swizzle to ZZWZ Vector
	inline Vec4Double ZZWW() const;											//Swizzle to ZZWW Vector
	inline Vec4Double ZWXX() const;											//Swizzle to ZWXX Vector
	inline Vec4Double ZWXY() const;											//Swizzle to ZWXY Vector
	inline Vec4Double ZWXZ() const;											//Swizzle to ZWXZ Vector
	inline Vec4Double ZWXW() const;											//Swizzle to ZWXW Vector
	inline Vec4Double ZWYX() const;											//Swizzle to ZWYX Vector
	inline Vec4Double ZWYY() const;											//Swizzle to ZWYY Vector
	inline Vec4Double ZWYZ() const;											//Swizzle to ZWYZ Vector
	inline Vec4Double ZWYW() const;											//Swizzle to ZWYW Vector
	inline Vec4Double ZWZX() const;											//Swizzle to ZWZX Vector
	inline Vec4Double ZWZY() const;											//Swizzle to ZWZY Vector
	inline Vec4Double ZWZZ() const;											//Swizzle to ZWZZ Vector
	inline Vec4Double ZWZW() const;											//Swizzle to ZWZW Vector
	inline Vec4Double ZWWX() const;											//Swizzle to ZWWX Vector
	inline Vec4Double ZWWY() const;											//Swizzle to ZWWY Vector
	inline Vec4Double ZWWZ() const;											//Swizzle to ZWWZ Vector
	inline Vec4Double ZWWW() const;											//Swizzle to ZWWW Vector
	inline Vec4Double WXXX() const;											//Swizzle to WXXX Vector
	inline Vec4Double WXXY() const;											//Swizzle to WXXY Vector
	inline Vec4Double WXXZ() const;											//Swizzle to WXXZ Vector
	inline Vec4Double WXXW() const;											//Swizzle to WXXW Vector
	inline Vec4Double WXYX() const;											//Swizzle to WXYX Vector
	inline Vec4Double WXYY() const;											//Swizzle to WXYY Vector
	inline Vec4Double WXYZ() const;											//Swizzle to WXYZ Vector
	inline Vec4Double WXYW() const;											//Swizzle to WXYW Vector
	inline Vec4Double WXZX() const;											//Swizzle to WXZX Vector
	inline Vec4Double WXZY() const;											//Swizzle to WXZY Vector
	inline Vec4Double WXZZ() const;											//Swizzle to WXZZ Vector
	inline Vec4Double WXZW() const;											//Swizzle to WXZW Vector
	inline Vec4Double WXWX() const;											//Swizzle to WXWX Vector
	inline Vec4Double WXWY() const;											//Swizzle to WXWY Vector
	inline Vec4Double WXWZ() const;											//Swizzle to WXWZ Vector
	inline Vec4Double WXWW() const;											//Swizzle to WXWW Vector
	inline Vec4Double WYXX() const;											//Swizzle to WYXX Vector
	inline Vec4Double WYXY() const;											//Swizzle to WYXY Vector
	inline Vec4Double WYXZ() const;											//Swizzle to WYXZ Vector
	inline Vec4Double WYXW() const;											//Swizzle to WYXW Vector
	inline Vec4Double WYYX() const;											//Swizzle to WYYX Vector
	inline Vec4Double WYYY() const;											//Swizzle to WYYY Vector
	inline Vec4Double WYYZ() const;											//Swizzle to WYYZ Vector
	inline Vec4Double WYYW() const;											//Swizzle to WYYW Vector
	inline Vec4Double WYZX() const;											//Swizzle to WYZX Vector
	inline Vec4Double WYZY() const;											//Swizzle to WYZY Vector
	inline Vec4Double WYZZ() const;											//Swizzle to WYZZ Vector
	inline Vec4Double WYZW() const;											//Swizzle to WYZW Vector
	inline Vec4Double WYWX() const;											//Swizzle to WYWX Vector
	inline Vec4Double WYWY() const;											//Swizzle to WYWY Vector
	inline Vec4Double WYWZ() const;											//Swizzle to WYWZ Vector
	inline Vec4Double WYWW() const;											//Swizzle to WYWW Vector
	inline Vec4Double WZXX() const;											//Swizzle to WZXX Vector
	inline Vec4Double WZXY() const;											//Swizzle to WZXY Vector
	inline Vec4Double WZXZ() const;											//Swizzle to WZXZ Vector
	inline Vec4Double WZXW() const;											//Swizzle to WZXW Vector
	inline Vec4Double WZYX() const;											//Swizzle to WZYX Vector
	inline Vec4Double WZYY() const;											//Swizzle to WZYY Vector
	inline Vec4Double WZYZ() const;											//Swizzle to WZYZ Vector
	inline Vec4Double WZYW() const;											//Swizzle to WZYW Vector
	inline Vec4Double WZZX() const;											//Swizzle to WZZX Vector
	inline Vec4Double WZZY() const;											//Swizzle to WZZY Vector
	inline Vec4Double WZZZ() const;											//Swizzle to WZZZ Vector
	inline Vec4Double WZZW() const;											//Swizzle to WZZW Vector
	inline Vec4Double WZWX() const;											//Swizzle to WZWX Vector
	inline Vec4Double WZWY() const;											//Swizzle to WZWY Vector
	inline Vec4Double WZWZ() const;											//Swizzle to WZWZ Vector
	inline Vec4Double WZWW() const;											//Swizzle to WZWW Vector
	inline Vec4Double WWXX() const;											//Swizzle to WWXX Vector
	inline Vec4Double WWXY() const;											//Swizzle to WWXY Vector
	inline Vec4Double WWXZ() const;											//Swizzle to WWXZ Vector
	inline Vec4Double WWXW() const;											//Swizzle to WWXW Vector
	inline Vec4Double WWYX() const;											//Swizzle to WWYX Vector
	inline Vec4Double WWYY() const;											//Swizzle to WWYY Vector
	inline Vec4Double WWYZ() const;											//Swizzle to WWYZ Vector
	inline Vec4Double WWYW() const;											//Swizzle to WWYW Vector
	inline Vec4Double WWZX() const;											//Swizzle to WWZX Vector
	inline Vec4Double WWZY() const;											//Swizzle to WWZY Vector
	inline Vec4Double WWZZ() const;											//Swizzle to WWZZ Vector
	inline Vec4Double WWZW() const;											//Swizzle to WWZW Vector
	inline Vec4Double WWWX() const;											//Swizzle to WWWX Vector
	inline Vec4Double WWWY() const;											//Swizzle to WWWY Vector
	inline Vec4Double WWWZ() const;											//Swizzle to WWWZ Vector
	inline Vec4Double WWWW() const;											//Swizzle to WWWW Vector
	inline Vec4Double RRRR() const;											//Swizzle to RRRR Vector
	inline Vec4Double RRRG() const;											//Swizzle to RRRG Vector
	inline Vec4Double RRRB() const;											//Swizzle to RRRB Vector
	inline Vec4Double RRRA() const;											//Swizzle to RRRA Vector
	inline Vec4Double RRGR() const;											//Swizzle to RRGR Vector
	inline Vec4Double RRGG() const;											//Swizzle to RRGG Vector
	inline Vec4Double RRGB() const;											//Swizzle to RRGB Vector
	inline Vec4Double RRGA() const;											//Swizzle to RRGA Vector
	inline Vec4Double RRBR() const;											//Swizzle to RRBR Vector
	inline Vec4Double RRBG() const;											//Swizzle to RRBG Vector
	inline Vec4Double RRBB() const;											//Swizzle to RRBB Vector
	inline Vec4Double RRBA() const;											//Swizzle to RRBA Vector
	inline Vec4Double RRAR() const;											//Swizzle to RRAR Vector
	inline Vec4Double RRAG() const;											//Swizzle to RRAG Vector
	inline Vec4Double RRAB() const;											//Swizzle to RRAB Vector
	inline Vec4Double RRAA() const;											//Swizzle to RRAA Vector
	inline Vec4Double RGRR() const;											//Swizzle to RGRR Vector
	inline Vec4Double RGRG() const;											//Swizzle to RGRG Vector
	inline Vec4Double RGRB() const;											//Swizzle to RGRB Vector
	inline Vec4Double RGRA() const;											//Swizzle to RGRA Vector
	inline Vec4Double RGGR() const;											//Swizzle to RGGR Vector
	inline Vec4Double RGGG() const;											//Swizzle to RGGG Vector
	inline Vec4Double RGGB() const;											//Swizzle to RGGB Vector
	inline Vec4Double RGGA() const;											//Swizzle to RGGA Vector
	inline Vec4Double RGBR() const;											//Swizzle to RGBR Vector
	inline Vec4Double RGBG() const;											//Swizzle to RGBG Vector
	inline Vec4Double RGBB() const;											//Swizzle to RGBB Vector
	inline Vec4Double RGAR() const;											//Swizzle to RGAR Vector
	inline Vec4Double RGAG() const;											//Swizzle to RGAG Vector
	inline Vec4Double RGAB() const;											//Swizzle to RGAB Vector
	inline Vec4Double RGAA() const;											//Swizzle to RGAA Vector
	inline Vec4Double RBRR() const;											//Swizzle to RBRR Vector
	inline Vec4Double RBRG() const;											//Swizzle to RBRG Vector
	inline Vec4Double RBRB() const;											//Swizzle to RBRB Vector
	inline Vec4Double RBRA() const;											//Swizzle to RBRA Vector
	inline Vec4Double RBGR() const;											//Swizzle to RBGR Vector
	inline Vec4Double RBGG() const;											//Swizzle to RBGG Vector
	inline Vec4Double RBGB() const;											//Swizzle to RBGB Vector
	inline Vec4Double RBGA() const;											//Swizzle to RBGA Vector
	inline Vec4Double RBBR() const;											//Swizzle to RBBR Vector
	inline Vec4Double RBBG() const;											//Swizzle to RBBG Vector
	inline Vec4Double RBBB() const;											//Swizzle to RBBB Vector
	inline Vec4Double RBBA() const;											//Swizzle to RBBA Vector
	inline Vec4Double RBAR() const;											//Swizzle to RBAR Vector
	inline Vec4Double RBAG() const;											//Swizzle to RBAG Vector
	inline Vec4Double RBAB() const;											//Swizzle to RBAB Vector
	inline Vec4Double RBAA() const;											//Swizzle to RBAA Vector
	inline Vec4Double RARR() const;											//Swizzle to RARR Vector
	inline Vec4Double RARG() const;											//Swizzle to RARG Vector
	inline Vec4Double RARB() const;											//Swizzle to RARB Vector
	inline Vec4Double RARA() const;											//Swizzle to RARA Vector
	inline Vec4Double RAGR() const;											//Swizzle to RAGR Vector
	inline Vec4Double RAGG() const;											//Swizzle to RAGG Vector
	inline Vec4Double RAGB() const;											//Swizzle to RAGB Vector
	inline Vec4Double RAGA() const;											//Swizzle to RAGA Vector
	inline Vec4Double RABR() const;											//Swizzle to RABR Vector
	inline Vec4Double RABG() const;											//Swizzle to RABG Vector
	inline Vec4Double RABB() const;											//Swizzle to RABB Vector
	inline Vec4Double RABA() const;											//Swizzle to RABA Vector
	inline Vec4Double RAAR() const;											//Swizzle to RAAR Vector
	inline Vec4Double RAAG() const;											//Swizzle to RAAG Vector
	inline Vec4Double RAAB() const;											//Swizzle to RAAB Vector
	inline Vec4Double RAAA() const;											//Swizzle to RAAA Vector
	inline Vec4Double GRRR() const;											//Swizzle to GRRR Vector
	inline Vec4Double GRRG() const;											//Swizzle to GRRG Vector
	inline Vec4Double GRRB() const;											//Swizzle to GRRB Vector
	inline Vec4Double GRRA() const;											//Swizzle to GRRA Vector
	inline Vec4Double GRGR() const;											//Swizzle to GRGR Vector
	inline Vec4Double GRGG() const;											//Swizzle to GRGG Vector
	inline Vec4Double GRGB() const;											//Swizzle to GRGB Vector
	inline Vec4Double GRGA() const;											//Swizzle to GRGA Vector
	inline Vec4Double GRBR() const;											//Swizzle to GRBR Vector
	inline Vec4Double GRBG() const;											//Swizzle to GRBG Vector
	inline Vec4Double GRBB() const;											//Swizzle to GRBB Vector
	inline Vec4Double GRBA() const;											//Swizzle to GRBA Vector
	inline Vec4Double GRAR() const;											//Swizzle to GRAR Vector
	inline Vec4Double GRAG() const;											//Swizzle to GRAG Vector
	inline Vec4Double GRAB() const;											//Swizzle to GRAB Vector
	inline Vec4Double GRAA() const;											//Swizzle to GRAA Vector
	inline Vec4Double GGRR() const;											//Swizzle to GGRR Vector
	inline Vec4Double GGRG() const;											//Swizzle to GGRG Vector
	inline Vec4Double GGRB() const;											//Swizzle to GGRB Vector
	inline Vec4Double GGRA() const;											//Swizzle to GGRA Vector
	inline Vec4Double GGGR() const;											//Swizzle to GGGR Vector
	inline Vec4Double GGGG() const;											//Swizzle to GGGG Vector
	inline Vec4Double GGGB() const;											//Swizzle to GGGB Vector
	inline Vec4Double GGGA() const;											//Swizzle to GGGA Vector
	inline Vec4Double GGBR() const;											//Swizzle to GGBR Vector
	inline Vec4Double GGBG() const;											//Swizzle to GGBG Vector
	inline Vec4Double GGBB() const;											//Swizzle to GGBB Vector
	inline Vec4Double GGBA() const;											//Swizzle to GGBA Vector
	inline Vec4Double GGAR() const;											//Swizzle to GGAR Vector
	inline Vec4Double GGAG() const;											//Swizzle to GGAG Vector
	inline Vec4Double GGAB() const;											//Swizzle to GGAB Vector
	inline Vec4Double GGAA() const;											//Swizzle to GGAA Vector
	inline Vec4Double GBRR() const;											//Swizzle to GBRR Vector
	inline Vec4Double GBRG() const;											//Swizzle to GBRG Vector
	inline Vec4Double GBRB() const;											//Swizzle to GBRB Vector
	inline Vec4Double GBRA() const;											//Swizzle to GBRA Vector
	inline Vec4Double GBGR() const;											//Swizzle to GBGR Vector
	inline Vec4Double GBGG() const;											//Swizzle to GBGG Vector
	inline Vec4Double GBGB() const;											//Swizzle to GBGB Vector
	inline Vec4Double GBGA() const;											//Swizzle to GBGA Vector
	inline Vec4Double GBBR() const;											//Swizzle to GBBR Vector
	inline Vec4Double GBBG() const;											//Swizzle to GBBG Vector
	inline Vec4Double GBBB() const;											//Swizzle to GBBB Vector
	inline Vec4Double GBBA() const;											//Swizzle to GBBA Vector
	inline Vec4Double GBAR() const;											//Swizzle to GBAR Vector
	inline Vec4Double GBAG() const;											//Swizzle to GBAG Vector
	inline Vec4Double GBAB() const;											//Swizzle to GBAB Vector
	inline Vec4Double GBAA() const;											//Swizzle to GBAA Vector
	inline Vec4Double GARR() const;											//Swizzle to GARR Vector
	inline Vec4Double GARG() const;											//Swizzle to GARG Vector
	inline Vec4Double GARB() const;											//Swizzle to GARB Vector
	inline Vec4Double GARA() const;											//Swizzle to GARA Vector
	inline Vec4Double GAGR() const;											//Swizzle to GAGR Vector
	inline Vec4Double GAGG() const;											//Swizzle to GAGG Vector
	inline Vec4Double GAGB() const;											//Swizzle to GAGB Vector
	inline Vec4Double GAGA() const;											//Swizzle to GAGA Vector
	inline Vec4Double GABR() const;											//Swizzle to GABR Vector
	inline Vec4Double GABG() const;											//Swizzle to GABG Vector
	inline Vec4Double GABB() const;											//Swizzle to GABB Vector
	inline Vec4Double GABA() const;											//Swizzle to GABA Vector
	inline Vec4Double GAAR() const;											//Swizzle to GAAR Vector
	inline Vec4Double GAAG() const;											//Swizzle to GAAG Vector
	inline Vec4Double GAAB() const;											//Swizzle to GAAB Vector
	inline Vec4Double GAAA() const;											//Swizzle to GAAA Vector
	inline Vec4Double BRRR() const;											//Swizzle to BRRR Vector
	inline Vec4Double BRRG() const;											//Swizzle to BRRG Vector
	inline Vec4Double BRRB() const;											//Swizzle to BRRB Vector
	inline Vec4Double BRRA() const;											//Swizzle to BRRA Vector
	inline Vec4Double BRGR() const;											//Swizzle to BRGR Vector
	inline Vec4Double BRGG() const;											//Swizzle to BRGG Vector
	inline Vec4Double BRGB() const;											//Swizzle to BRGB Vector
	inline Vec4Double BRGA() const;											//Swizzle to BRGA Vector
	inline Vec4Double BRBR() const;											//Swizzle to BRBR Vector
	inline Vec4Double BRBG() const;											//Swizzle to BRBG Vector
	inline Vec4Double BRBB() const;											//Swizzle to BRBB Vector
	inline Vec4Double BRBA() const;											//Swizzle to BRBA Vector
	inline Vec4Double BRAR() const;											//Swizzle to BRAR Vector
	inline Vec4Double BRAG() const;											//Swizzle to BRAG Vector
	inline Vec4Double BRAB() const;											//Swizzle to BRAB Vector
	inline Vec4Double BRAA() const;											//Swizzle to BRAA Vector
	inline Vec4Double BGRR() const;											//Swizzle to BGRR Vector
	inline Vec4Double BGRG() const;											//Swizzle to BGRG Vector
	inline Vec4Double BGRB() const;											//Swizzle to BGRB Vector
	inline Vec4Double BGRA() const;											//Swizzle to BGRA Vector
	inline Vec4Double BGGR() const;											//Swizzle to BGGR Vector
	inline Vec4Double BGGG() const;											//Swizzle to BGGG Vector
	inline Vec4Double BGGB() const;											//Swizzle to BGGB Vector
	inline Vec4Double BGGA() const;											//Swizzle to BGGA Vector
	inline Vec4Double BGBR() const;											//Swizzle to BGBR Vector
	inline Vec4Double BGBG() const;											//Swizzle to BGBG Vector
	inline Vec4Double BGBB() const;											//Swizzle to BGBB Vector
	inline Vec4Double BGBA() const;											//Swizzle to BGBA Vector
	inline Vec4Double BGAR() const;											//Swizzle to BGAR Vector
	inline Vec4Double BGAG() const;											//Swizzle to BGAG Vector
	inline Vec4Double BGAB() const;											//Swizzle to BGAB Vector
	inline Vec4Double BGAA() const;											//Swizzle to BGAA Vector
	inline Vec4Double BBRR() const;											//Swizzle to BBRR Vector
	inline Vec4Double BBRG() const;											//Swizzle to BBRG Vector
	inline Vec4Double BBRB() const;											//Swizzle to BBRB Vector
	inline Vec4Double BBRA() const;											//Swizzle to BBRA Vector
	inline Vec4Double BBGR() const;											//Swizzle to BBGR Vector
	inline Vec4Double BBGG() const;											//Swizzle to BBGG Vector
	inline Vec4Double BBGB() const;											//Swizzle to BBGB Vector
	inline Vec4Double BBGA() const;											//Swizzle to BBGA Vector
	inline Vec4Double BBBR() const;											//Swizzle to BBBR Vector
	inline Vec4Double BBBG() const;											//Swizzle to BBBG Vector
	inline Vec4Double BBBB() const;											//Swizzle to BBBB Vector
	inline Vec4Double BBBA() const;											//Swizzle to BBBA Vector
	inline Vec4Double BBAR() const;											//Swizzle to BBAR Vector
	inline Vec4Double BBAG() const;											//Swizzle to BBAG Vector
	inline Vec4Double BBAB() const;											//Swizzle to BBAB Vector
	inline Vec4Double BBAA() const;											//Swizzle to BBAA Vector
	inline Vec4Double BARR() const;											//Swizzle to BARR Vector
	inline Vec4Double BARG() const;											//Swizzle to BARG Vector
	inline Vec4Double BARB() const;											//Swizzle to BARB Vector
	inline Vec4Double BARA() const;											//Swizzle to BARA Vector
	inline Vec4Double BAGR() const;											//Swizzle to BAGR Vector
	inline Vec4Double BAGG() const;											//Swizzle to BAGG Vector
	inline Vec4Double BAGB() const;											//Swizzle to BAGB Vector
	inline Vec4Double BAGA() const;											//Swizzle to BAGA Vector
	inline Vec4Double BABR() const;											//Swizzle to BABR Vector
	inline Vec4Double BABG() const;											//Swizzle to BABG Vector
	inline Vec4Double BABB() const;											//Swizzle to BABB Vector
	inline Vec4Double BABA() const;											//Swizzle to BABA Vector
	inline Vec4Double BAAR() const;											//Swizzle to BAAR Vector
	inline Vec4Double BAAG() const;											//Swizzle to BAAG Vector
	inline Vec4Double BAAB() const;											//Swizzle to BAAB Vector
	inline Vec4Double BAAA() const;											//Swizzle to BAAA Vector
	inline Vec4Double ARRR() const;											//Swizzle to ARRR Vector
	inline Vec4Double ARRG() const;											//Swizzle to ARRG Vector
	inline Vec4Double ARRB() const;											//Swizzle to ARRB Vector
	inline Vec4Double ARRA() const;											//Swizzle to ARRA Vector
	inline Vec4Double ARGR() const;											//Swizzle to ARGR Vector
	inline Vec4Double ARGG() const;											//Swizzle to ARGG Vector
	inline Vec4Double ARGB() const;											//Swizzle to ARGB Vector
	inline Vec4Double ARGA() const;											//Swizzle to ARGA Vector
	inline Vec4Double ARBR() const;											//Swizzle to ARBR Vector
	inline Vec4Double ARBG() const;											//Swizzle to ARBG Vector
	inline Vec4Double ARBB() const;											//Swizzle to ARBB Vector
	inline Vec4Double ARBA() const;											//Swizzle to ARBA Vector
	inline Vec4Double ARAR() const;											//Swizzle to ARAR Vector
	inline Vec4Double ARAG() const;											//Swizzle to ARAG Vector
	inline Vec4Double ARAB() const;											//Swizzle to ARAB Vector
	inline Vec4Double ARAA() const;											//Swizzle to ARAA Vector
	inline Vec4Double AGRR() const;											//Swizzle to AGRR Vector
	inline Vec4Double AGRG() const;											//Swizzle to AGRG Vector
	inline Vec4Double AGRB() const;											//Swizzle to AGRB Vector
	inline Vec4Double AGRA() const;											//Swizzle to AGRA Vector
	inline Vec4Double AGGR() const;											//Swizzle to AGGR Vector
	inline Vec4Double AGGG() const;											//Swizzle to AGGG Vector
	inline Vec4Double AGGB() const;											//Swizzle to AGGB Vector
	inline Vec4Double AGGA() const;											//Swizzle to AGGA Vector
	inline Vec4Double AGBR() const;											//Swizzle to AGBR Vector
	inline Vec4Double AGBG() const;											//Swizzle to AGBG Vector
	inline Vec4Double AGBB() const;											//Swizzle to AGBB Vector
	inline Vec4Double AGBA() const;											//Swizzle to AGBA Vector
	inline Vec4Double AGAR() const;											//Swizzle to AGAR Vector
	inline Vec4Double AGAG() const;											//Swizzle to AGAG Vector
	inline Vec4Double AGAB() const;											//Swizzle to AGAB Vector
	inline Vec4Double AGAA() const;											//Swizzle to AGAA Vector
	inline Vec4Double ABRR() const;											//Swizzle to ABRR Vector
	inline Vec4Double ABRG() const;											//Swizzle to ABRG Vector
	inline Vec4Double ABRB() const;											//Swizzle to ABRB Vector
	inline Vec4Double ABRA() const;											//Swizzle to ABRA Vector
	inline Vec4Double ABGR() const;											//Swizzle to ABGR Vector
	inline Vec4Double ABGG() const;											//Swizzle to ABGG Vector
	inline Vec4Double ABGB() const;											//Swizzle to ABGB Vector
	inline Vec4Double ABGA() const;											//Swizzle to ABGA Vector
	inline Vec4Double ABBR() const;											//Swizzle to ABBR Vector
	inline Vec4Double ABBG() const;											//Swizzle to ABBG Vector
	inline Vec4Double ABBB() const;											//Swizzle to ABBB Vector
	inline Vec4Double ABBA() const;											//Swizzle to ABBA Vector
	inline Vec4Double ABAR() const;											//Swizzle to ABAR Vector
	inline Vec4Double ABAG() const;											//Swizzle to ABAG Vector
	inline Vec4Double ABAB() const;											//Swizzle to ABAB Vector
	inline Vec4Double ABAA() const;											//Swizzle to ABAA Vector
	inline Vec4Double AARR() const;											//Swizzle to AARR Vector
	inline Vec4Double AARG() const;											//Swizzle to AARG Vector
	inline Vec4Double AARB() const;											//Swizzle to AARB Vector
	inline Vec4Double AARA() const;											//Swizzle to AARA Vector
	inline Vec4Double AAGR() const;											//Swizzle to AAGR Vector
	inline Vec4Double AAGG() const;											//Swizzle to AAGG Vector
	inline Vec4Double AAGB() const;											//Swizzle to AAGB Vector
	inline Vec4Double AAGA() const;											//Swizzle to AAGA Vector
	inline Vec4Double AABR() const;											//Swizzle to AABR Vector
	inline Vec4Double AABG() const;											//Swizzle to AABG Vector
	inline Vec4Double AABB() const;											//Swizzle to AABB Vector
	inline Vec4Double AABA() const;											//Swizzle to AABA Vector
	inline Vec4Double AAAR() const;											//Swizzle to AAAR Vector
	inline Vec4Double AAAG() const;											//Swizzle to AAAG Vector
	inline Vec4Double AAAB() const;											//Swizzle to AAAB Vector
	inline Vec4Double AAAA() const;											//Swizzle to AAAA Vector
};

#pragma endregion

#pragma region IntegerVectors

class alignas(8) Vec2Int {
private:
	union {
		int xy[2];													//Array Storage
		struct {
			int x;													//X Member
			int y;													//Y Member
		};
	};
public:
	//Constructors
	inline Vec2Int();												//Init to Zero
	inline Vec2Int(int _x, int _y);									//Init to X and Y
	inline Vec2Int(const Vec2Int& _other);							//Init from Copy

	//Assignment
	inline Vec2Int& operator=(const Vec2Int& _other);				//Assignment
	inline Vec2Int& operator+=(const Vec2Int& _other);				//Addition
	inline Vec2Int& operator-=(const Vec2Int& _other);				//Subtraction
	inline Vec2Int& operator*=(const int _scale);					//Scaling
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec2Int operator+(const Vec2Int& _other) const;			//Addition
	inline Vec2Int operator-(const Vec2Int& _other) const;			//Subtraction
	inline Vec2Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec2Int& _other) const;				//Dot Product
	inline int operator&(const Vec2Int& _other) const;				//Cross Product
	inline Vec2Int operator~() const;								//Zero
	inline Vec2Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec2Int& _other) const;			//Check Equality
	inline bool operator<(const Vec2Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec2Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec2Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec2Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec2Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec2Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec2Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec2Int& _other) const;					//Dot Product
	inline int Cross(const Vec2Int& _other) const;					//Cross Product
	inline void Add(const Vec2Int& _other);							//Addition
	inline void Subtract(const Vec2Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec2Int& _other) const;				//Check Equality
	inline bool Less(const Vec2Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec2Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec2Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec2Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec2Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
};

class alignas(16) Vec3Int {
private:
	union {
		int xyz[3];													//Array Storage
		struct {
			int x;													//X Member
			int y;													//Y Member
			int z;													//Z Member
		};
	};
public:
	//Constructors
	inline Vec3Int();												//Init to Zero
	inline Vec3Int(int _x, int _y, int _z);							//Init to X, Y, and Z
	inline Vec3Int(const Vec2Int& _xy, int _z);						//Init from a Vec2Int for X and Y, and from a int for Z
	inline Vec3Int(int _x, const Vec2Int& _yz);						//Init from X, and from a Vec2Int for Y and Z
	inline Vec3Int(const Vec3Int& _other);							//Init from Copy

	//Assignment
	inline Vec3Int& operator=(const Vec3Int& _other);				//Assignment
	inline Vec3Int& operator+=(const Vec3Int& _other);				//Addition
	inline Vec3Int& operator-=(const Vec3Int& _other);				//Subtraction
	inline Vec3Int& operator*=(const int _scale);					//Scaling
	inline Vec3Int& operator&=(const Vec3Int& _other);				//Cross Product
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec3Int operator+(const Vec3Int& _other) const;			//Addition
	inline Vec3Int operator-(const Vec3Int& _other) const;			//Subtraction
	inline Vec3Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec3Int& _other) const;				//Dot Product
	inline Vec3Int operator&(const Vec3Int& _other) const;			//Cross Product
	inline Vec3Int operator~() const;								//Zero
	inline Vec3Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec3Int& _other) const;			//Check Equality
	inline bool operator<(const Vec3Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec3Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec3Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec3Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec3Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec3Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec3Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec3Int& _other) const;					//Dot Product
	inline void Cross(const Vec3Int& _other);						//Cross Product
	inline void Add(const Vec3Int& _other);							//Addition
	inline void Subtract(const Vec3Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec3Int& _other) const;				//Check Equality
	inline bool Less(const Vec3Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec3Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec3Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec3Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec3Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int& Z();												//Vector Z Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)
	inline int Z() const;											//Vector Z Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2Int XY() const;										//Swizzle to XY Vector
	inline Vec2Int XZ() const;										//Swizzle to XZ Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int YZ() const;										//Swizzle to YZ Vector
	inline Vec2Int ZX() const;										//Swizzle to ZX Vector
	inline Vec2Int ZY() const;										//Swizzle to ZY Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int BB() const;										//Swizzle to BB Vector
	inline Vec2Int RG() const;										//Swizzle to RG Vector
	inline Vec2Int RB() const;										//Swizzle to RB Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
	inline Vec2Int GB() const;										//Swizzle to GB Vector
	inline Vec2Int BR() const;										//Swizzle to BR Vector
	inline Vec2Int BG() const;										//Swizzle to BG Vector

	//Swizzle Operations (Vec3Int)
	inline Vec3Int XXX() const;										//Swizzle to XXX Vector
	inline Vec3Int XXY() const;										//Swizzle to XXY Vector
	inline Vec3Int XXZ() const;										//Swizzle to XXZ Vector
	inline Vec3Int XYX() const;										//Swizzle to XYX Vector
	inline Vec3Int XYY() const;										//Swizzle to XYY Vector
	inline Vec3Int XZX() const;										//Swizzle to XZX Vector
	inline Vec3Int XZY() const;										//Swizzle to XZY Vector
	inline Vec3Int XZZ() const;										//Swizzle to XZZ Vector
	inline Vec3Int YXX() const;										//Swizzle to YXX Vector
	inline Vec3Int YXY() const;										//Swizzle to YXY Vector
	inline Vec3Int YXZ() const;										//Swizzle to YXZ Vector
	inline Vec3Int YYX() const;										//Swizzle to YYX Vector
	inline Vec3Int YYY() const;										//Swizzle to YYY Vector
	inline Vec3Int YYZ() const;										//Swizzle to YYZ Vector
	inline Vec3Int YZX() const;										//Swizzle to YZX Vector
	inline Vec3Int YZY() const;										//Swizzle to YZY Vector
	inline Vec3Int YZZ() const;										//Swizzle to YZZ Vector
	inline Vec3Int ZXX() const;										//Swizzle to ZXX Vector
	inline Vec3Int ZXY() const;										//Swizzle to ZXY Vector
	inline Vec3Int ZXZ() const;										//Swizzle to ZXZ Vector
	inline Vec3Int ZYX() const;										//Swizzle to ZYX Vector
	inline Vec3Int ZYY() const;										//Swizzle to ZYY Vector
	inline Vec3Int ZYZ() const;										//Swizzle to ZYZ Vector
	inline Vec3Int ZZX() const;										//Swizzle to ZZX Vector
	inline Vec3Int ZZY() const;										//Swizzle to ZZY Vector
	inline Vec3Int ZZZ() const;										//Swizzle to ZZZ Vector
	inline Vec3Int RRR() const;										//Swizzle to RRR Vector
	inline Vec3Int RRG() const;										//Swizzle to RRG Vector
	inline Vec3Int RRB() const;										//Swizzle to RRB Vector
	inline Vec3Int RGR() const;										//Swizzle to RGR Vector
	inline Vec3Int RGG() const;										//Swizzle to RGG Vector
	inline Vec3Int RBR() const;										//Swizzle to RBR Vector
	inline Vec3Int RBG() const;										//Swizzle to RBG Vector
	inline Vec3Int RBB() const;										//Swizzle to RBB Vector
	inline Vec3Int GRR() const;										//Swizzle to GRR Vector
	inline Vec3Int GRG() const;										//Swizzle to GRG Vector
	inline Vec3Int GRB() const;										//Swizzle to GRB Vector
	inline Vec3Int GGR() const;										//Swizzle to GGR Vector
	inline Vec3Int GGG() const;										//Swizzle to GGG Vector
	inline Vec3Int GGB() const;										//Swizzle to GGB Vector
	inline Vec3Int GBR() const;										//Swizzle to GBR Vector
	inline Vec3Int GBG() const;										//Swizzle to GBG Vector
	inline Vec3Int GBB() const;										//Swizzle to GBB Vector
	inline Vec3Int BRR() const;										//Swizzle to BRR Vector
	inline Vec3Int BRG() const;										//Swizzle to BRG Vector
	inline Vec3Int BRB() const;										//Swizzle to BRB Vector
	inline Vec3Int BGR() const;										//Swizzle to BGR Vector
	inline Vec3Int BGG() const;										//Swizzle to BGG Vector
	inline Vec3Int BGB() const;										//Swizzle to BGB Vector
	inline Vec3Int BBR() const;										//Swizzle to BBR Vector
	inline Vec3Int BBG() const;										//Swizzle to BBG Vector
	inline Vec3Int BBB() const;										//Swizzle to BBB Vector
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
	//Constructors
	inline Vec4Int();												//Init to Zero
	inline Vec4Int(int _x, int _y, int _z, int _w);					//Init to X, Y, Z, and W
	inline Vec4Int(const Vec2Int& _xy, int _z, int _w);				//Init from a Vec2Int for X and Y, and from a int for Z and W
	inline Vec4Int(int _x, const Vec2Int& _yz, int _w);				//Init from X, from a Vec2Int for Y and Z and a int for W
	inline Vec4Int(int _x, int _y, const Vec2Int& _zw);				//Init from X and Y, and from a Vec2Int for Z and W
	inline Vec4Int(const Vec2Int& _xy, const Vec2Int& _zw);			//Init from 2 Vec2Int's
	inline Vec4Int(const Vec3Int& _xyz, int _w);					//Init from a Vec3Int and a int for W
	inline Vec4Int(int _x, const Vec3Int& _yzw);					//Init from a int for X and a Vec3Int
	inline Vec4Int(const Vec4Int& _other);							//Init from Copy

	//Assignment
	inline Vec4Int& operator=(const Vec4Int& _other);				//Assignment
	inline Vec4Int& operator+=(const Vec4Int& _other);				//Addition
	inline Vec4Int& operator-=(const Vec4Int& _other);				//Subtraction
	inline Vec4Int& operator*=(const int _scale);					//Scaling
	inline Vec4Int& operator&=(const Vec4Int& _other);				//Cross Product
	inline int& operator[](int _ndx);								//Array access (Modifiable)
	inline int operator[](int _ndx) const;							//Array access (Const)

	//Arithmetic
	inline Vec4Int operator+(const Vec4Int& _other) const;			//Addition
	inline Vec4Int operator-(const Vec4Int& _other) const;			//Subtraction
	inline Vec4Int operator*(const int _scale) const;				//Scaling
	inline int operator*(const Vec4Int& _other) const;				//Dot Product
	inline Vec4Int operator&(const Vec4Int& _other) const;			//Cross Product
	inline Vec4Int operator~() const;								//Zero
	inline Vec4Int operator-() const;								//Negate

	//Comparison
	inline bool operator==(const Vec4Int& _other) const;			//Check Equality
	inline bool operator<(const Vec4Int& _other) const;				//Check Less Than
	inline bool operator>(const Vec4Int& _other) const;				//Check Greater Than
	inline bool operator<=(const Vec4Int& _other) const;			//Check Less Than or Equal To
	inline bool operator>=(const Vec4Int& _other) const;			//Check Greater Than or Equal To
	inline bool operator!=(const Vec4Int& _other) const;			//Check Not Equal

	//Measurement
	inline float Length() const;									//Vector Length
	inline float LengthSquared() const;								//Vector Length Squared
	inline void Normalize();										//Vector Normalize
	inline Vec4Int Normalized() const;								//Return Normalized Version of this Vector
	inline float AngleBetween(const Vec4Int& _other) const;			//Measure the angle between 2 Vectors

	//Operator Alternatives
	inline int Dot(const Vec4Int& _other) const;					//Dot Product
	inline void Cross(const Vec4Int& _other);						//Cross Product
	inline void Add(const Vec4Int& _other);							//Addition
	inline void Subtract(const Vec4Int& _other);					//Subtraction
	inline void Scale(const int _scale);							//Scaling
	inline void Negate();											//Negate
	inline void Zero();												//Zero
	inline bool Equals(const Vec4Int& _other) const;				//Check Equality
	inline bool Less(const Vec4Int& _other) const;					//Check Less Than
	inline bool LessThanOrEquals(const Vec4Int& _other) const;		//Check Less Than or Equal To
	inline bool Greater(const Vec4Int& _other) const;				//Check Greater Than
	inline bool GreaterThanOrEquals(const Vec4Int& _other) const;	//Check Greater Than or Equal To
	inline bool NotEquals(const Vec4Int& _other) const;				//Check Not Equal

	//Member Modification
	inline int& X();												//Vector X Component (Modifiable)
	inline int& Y();												//Vector Y Component (Modifiable)
	inline int& Z();												//Vector Z Component (Modifiable)
	inline int& W();												//Vector W Component (Modifiable)
	inline int X() const;											//Vector X Component (Const)
	inline int Y() const;											//Vector Y Component (Const)
	inline int Z() const;											//Vector Z Component (Const)
	inline int W() const;											//Vector W Component (Const)

	//Swizzle Operations (Vec2Int)
	inline Vec2Int XX() const;										//Swizzle to XX Vector
	inline Vec2Int YY() const;										//Swizzle to YY Vector
	inline Vec2Int ZZ() const;										//Swizzle to ZZ Vector
	inline Vec2Int WW() const;										//Swizzle to WW Vector
	inline Vec2Int XY() const;										//Swizzle to XY Vector
	inline Vec2Int XZ() const;										//Swizzle to XZ Vector
	inline Vec2Int XW() const;										//Swizzle to XW Vector
	inline Vec2Int YX() const;										//Swizzle to YX Vector
	inline Vec2Int YZ() const;										//Swizzle to YZ Vector
	inline Vec2Int YW() const;										//Swizzle to YW Vector
	inline Vec2Int ZX() const;										//Swizzle to ZX Vector
	inline Vec2Int ZY() const;										//Swizzle to ZY Vector
	inline Vec2Int ZW() const;										//Swizzle to ZW Vector
	inline Vec2Int WX() const;										//Swizzle to WX Vector
	inline Vec2Int WY() const;										//Swizzle to WY Vector
	inline Vec2Int WZ() const;										//Swizzle to WZ Vector
	inline Vec2Int RR() const;										//Swizzle to RR Vector
	inline Vec2Int GG() const;										//Swizzle to GG Vector
	inline Vec2Int BB() const;										//Swizzle to BB Vector
	inline Vec2Int AA() const;										//Swizzle to AA Vector
	inline Vec2Int RG() const;										//Swizzle to RG Vector
	inline Vec2Int RB() const;										//Swizzle to RB Vector
	inline Vec2Int RA() const;										//Swizzle to RA Vector
	inline Vec2Int GR() const;										//Swizzle to GR Vector
	inline Vec2Int GB() const;										//Swizzle to GB Vector
	inline Vec2Int GA() const;										//Swizzle to GA Vector
	inline Vec2Int BR() const;										//Swizzle to BR Vector
	inline Vec2Int BG() const;										//Swizzle to BG Vector
	inline Vec2Int	BA() const;										//Swizzle to BA Vector
	inline Vec2Int AR() const;										//Swizzle to AR Vector
	inline Vec2Int AG() const;										//Swizzle to AG Vector
	inline Vec2Int AB() const;										//Swizzle to AB Vector

	//Swizzle Operations (Vec3Int)
	inline Vec3Int XXX() const;										//Swizzle to XXX Vector
	inline Vec3Int XXY() const;										//Swizzle to XXY Vector
	inline Vec3Int XXZ() const;										//Swizzle to XXZ Vector
	inline Vec3Int XXW() const;										//Swizzle to XXW Vector
	inline Vec3Int XYX() const;										//Swizzle to XYX Vector
	inline Vec3Int XYY() const;										//Swizzle to XYY Vector
	inline Vec3Int XYZ() const;										//Swizzle to XYZ Vector
	inline Vec3Int XYW() const;										//Swizzle to XYW Vector
	inline Vec3Int XZX() const;										//Swizzle to XZX Vector
	inline Vec3Int XZY() const;										//Swizzle to XZY Vector
	inline Vec3Int XZZ() const;										//Swizzle to XZZ Vector
	inline Vec3Int XZW() const;										//Swizzle to XZW Vector
	inline Vec3Int XWX() const;										//Swizzle to XWX Vector
	inline Vec3Int XWY() const;										//Swizzle to XWY Vector
	inline Vec3Int XWZ() const;										//Swizzle to XWZ Vector
	inline Vec3Int XWW() const;										//Swizzle to XWW Vector
	inline Vec3Int YXX() const;										//Swizzle to YXX Vector
	inline Vec3Int YXY() const;										//Swizzle to YXY Vector
	inline Vec3Int YXZ() const;										//Swizzle to YXZ Vector
	inline Vec3Int YXW() const;										//Swizzle to YXW Vector
	inline Vec3Int YYX() const;										//Swizzle to YYX Vector
	inline Vec3Int YYY() const;										//Swizzle to YYY Vector
	inline Vec3Int YYZ() const;										//Swizzle to YYZ Vector
	inline Vec3Int YYW() const;										//Swizzle to YYW Vector
	inline Vec3Int YZX() const;										//Swizzle to YZX Vector
	inline Vec3Int YZY() const;										//Swizzle to YZY Vector
	inline Vec3Int YZZ() const;										//Swizzle to YZZ Vector
	inline Vec3Int YZW() const;										//Swizzle to YZW Vector
	inline Vec3Int YWX() const;										//Swizzle to YWX Vector
	inline Vec3Int YWY() const;										//Swizzle to YWY Vector
	inline Vec3Int YWZ() const;										//Swizzle to YWZ Vector
	inline Vec3Int YWW() const;										//Swizzle to YWW Vector
	inline Vec3Int ZXX() const;										//Swizzle to ZXX Vector
	inline Vec3Int ZXY() const;										//Swizzle to ZXY Vector
	inline Vec3Int ZXZ() const;										//Swizzle to ZXZ Vector
	inline Vec3Int ZXW() const;										//Swizzle to ZXW Vector
	inline Vec3Int ZYX() const;										//Swizzle to ZYX Vector
	inline Vec3Int ZYY() const;										//Swizzle to ZYY Vector
	inline Vec3Int ZYZ() const;										//Swizzle to ZYZ Vector
	inline Vec3Int ZYW() const;										//Swizzle to ZYW Vector
	inline Vec3Int ZZX() const;										//Swizzle to ZZX Vector
	inline Vec3Int ZZY() const;										//Swizzle to ZZY Vector
	inline Vec3Int ZZZ() const;										//Swizzle to ZZZ Vector
	inline Vec3Int ZZW() const;										//Swizzle to ZZW Vector
	inline Vec3Int ZWX() const;										//Swizzle to ZWX Vector
	inline Vec3Int ZWY() const;										//Swizzle to ZWY Vector
	inline Vec3Int ZWZ() const;										//Swizzle to ZWZ Vector
	inline Vec3Int ZWW() const;										//Swizzle to ZWW Vector
	inline Vec3Int WXX() const;										//Swizzle to WXX Vector
	inline Vec3Int WXY() const;										//Swizzle to WXY Vector
	inline Vec3Int WXZ() const;										//Swizzle to WXZ Vector
	inline Vec3Int WXW() const;										//Swizzle to WXW Vector
	inline Vec3Int WYX() const;										//Swizzle to WYX Vector
	inline Vec3Int WYY() const;										//Swizzle to WYY Vector
	inline Vec3Int WYZ() const;										//Swizzle to WYZ Vector
	inline Vec3Int WYW() const;										//Swizzle to WYW Vector
	inline Vec3Int WZX() const;										//Swizzle to WZX Vector
	inline Vec3Int WZY() const;										//Swizzle to WZY Vector
	inline Vec3Int WZZ() const;										//Swizzle to WZZ Vector
	inline Vec3Int WZW() const;										//Swizzle to WZW Vector
	inline Vec3Int WWX() const;										//Swizzle to WWX Vector
	inline Vec3Int WWY() const;										//Swizzle to WWY Vector
	inline Vec3Int WWZ() const;										//Swizzle to WWZ Vector
	inline Vec3Int WWW() const;										//Swizzle to WWW Vector
	inline Vec3Int RRR() const;										//Swizzle to RRR Vector
	inline Vec3Int RRG() const;										//Swizzle to RRG Vector
	inline Vec3Int RRB() const;										//Swizzle to RRB Vector
	inline Vec3Int RRA() const;										//Swizzle to RRA Vector
	inline Vec3Int RGR() const;										//Swizzle to RGR Vector
	inline Vec3Int RGG() const;										//Swizzle to RGG Vector
	inline Vec3Int RGA() const;										//Swizzle to RGA Vector
	inline Vec3Int RGB() const;										//Swizzle to RGB Vector
	inline Vec3Int RBR() const;										//Swizzle to RBR Vector
	inline Vec3Int RBG() const;										//Swizzle to RBG Vector
	inline Vec3Int RBB() const;										//Swizzle to RBB Vector
	inline Vec3Int RBA() const;										//Swizzle to RBA Vector
	inline Vec3Int RAR() const;										//Swizzle to RAR Vector
	inline Vec3Int RAG() const;										//Swizzle to RAG Vector
	inline Vec3Int RAB() const;										//Swizzle to RAB Vector
	inline Vec3Int RAA() const;										//Swizzle to RAA Vector
	inline Vec3Int GRR() const;										//Swizzle to GRR Vector
	inline Vec3Int GRG() const;										//Swizzle to GRG Vector
	inline Vec3Int GRB() const;										//Swizzle to GRB Vector
	inline Vec3Int GRA() const;										//Swizzle to GRA Vector
	inline Vec3Int GGR() const;										//Swizzle to GGR Vector
	inline Vec3Int GGG() const;										//Swizzle to GGG Vector
	inline Vec3Int GGB() const;										//Swizzle to GGB Vector
	inline Vec3Int GGA() const;										//Swizzle to GGA Vector
	inline Vec3Int GBR() const;										//Swizzle to GBR Vector
	inline Vec3Int GBG() const;										//Swizzle to GBG Vector
	inline Vec3Int GBB() const;										//Swizzle to GBB Vector
	inline Vec3Int GBA() const;										//Swizzle to GBA Vector
	inline Vec3Int GAR() const;										//Swizzle to GAR Vector
	inline Vec3Int GAG() const;										//Swizzle to GAG Vector
	inline Vec3Int GAB() const;										//Swizzle to GAB Vector
	inline Vec3Int GAA() const;										//Swizzle to GAA Vector
	inline Vec3Int BRR() const;										//Swizzle to BRR Vector
	inline Vec3Int BRG() const;										//Swizzle to BRG Vector
	inline Vec3Int BRB() const;										//Swizzle to BRB Vector
	inline Vec3Int BRA() const;										//Swizzle to BRA Vector
	inline Vec3Int BGR() const;										//Swizzle to BGR Vector
	inline Vec3Int BGG() const;										//Swizzle to BGG Vector
	inline Vec3Int BGB() const;										//Swizzle to BGB Vector
	inline Vec3Int BGA() const;										//Swizzle to BGA Vector
	inline Vec3Int BBR() const;										//Swizzle to BBR Vector
	inline Vec3Int BBG() const;										//Swizzle to BBG Vector
	inline Vec3Int BBB() const;										//Swizzle to BBB Vector
	inline Vec3Int BBA() const;										//Swizzle to BBA Vector
	inline Vec3Int BAR() const;										//Swizzle to BAR Vector
	inline Vec3Int BAG() const;										//Swizzle to BAG Vector
	inline Vec3Int BAB() const;										//Swizzle to BAB Vector
	inline Vec3Int BAA() const;										//Swizzle to BAA Vector
	inline Vec3Int ARR() const;										//Swizzle to ARR Vector
	inline Vec3Int ARG() const;										//Swizzle to ARG Vector
	inline Vec3Int ARB() const;										//Swizzle to ARB Vector
	inline Vec3Int ARA() const;										//Swizzle to ARA Vector
	inline Vec3Int AGR() const;										//Swizzle to AGR Vector
	inline Vec3Int AGG() const;										//Swizzle to AGG Vector
	inline Vec3Int AGB() const;										//Swizzle to AGB Vector
	inline Vec3Int AGA() const;										//Swizzle to AGA Vector
	inline Vec3Int ABR() const;										//Swizzle to ABR Vector
	inline Vec3Int ABG() const;										//Swizzle to ABG Vector
	inline Vec3Int ABB() const;										//Swizzle to ABB Vector
	inline Vec3Int ABA() const;										//Swizzle to ABA Vector
	inline Vec3Int AAR() const;										//Swizzle to AAR Vector
	inline Vec3Int AAG() const;										//Swizzle to AAG Vector
	inline Vec3Int AAB() const;										//Swizzle to AAB Vector
	inline Vec3Int AAA() const;										//Swizzle to AAA Vector

	//Swizzle Operations (Vec4Int)
	inline Vec4Int XXXX() const;									//Swizzle to XXXX Vector
	inline Vec4Int XXXY() const;									//Swizzle to XXXY Vector
	inline Vec4Int XXXZ() const;									//Swizzle to XXXZ Vector
	inline Vec4Int XXXW() const;									//Swizzle to XXXW Vector
	inline Vec4Int XXYX() const;									//Swizzle to XXYX Vector
	inline Vec4Int XXYY() const;									//Swizzle to XXYY Vector
	inline Vec4Int XXYZ() const;									//Swizzle to XXYZ Vector
	inline Vec4Int XXYW() const;									//Swizzle to XXYW Vector
	inline Vec4Int XXZX() const;									//Swizzle to XXZX Vector
	inline Vec4Int XXZY() const;									//Swizzle to XXZY Vector
	inline Vec4Int XXZZ() const;									//Swizzle to XXZZ Vector
	inline Vec4Int XXZW() const;									//Swizzle to XXZW Vector
	inline Vec4Int XXWX() const;									//Swizzle to XXWX Vector
	inline Vec4Int XXWY() const;									//Swizzle to XXWY Vector
	inline Vec4Int XXWZ() const;									//Swizzle to XXWZ Vector
	inline Vec4Int XXWW() const;									//Swizzle to XXWW Vector
	inline Vec4Int XYXX() const;									//Swizzle to XYXX Vector
	inline Vec4Int XYXY() const;									//Swizzle to XYXY Vector
	inline Vec4Int XYXZ() const;									//Swizzle to XYXZ Vector
	inline Vec4Int XYXW() const;									//Swizzle to XYXW Vector
	inline Vec4Int XYYX() const;									//Swizzle to XYYX Vector
	inline Vec4Int XYYY() const;									//Swizzle to XYYY Vector
	inline Vec4Int XYYZ() const;									//Swizzle to XYYZ Vector
	inline Vec4Int XYYW() const;									//Swizzle to XYYW Vector
	inline Vec4Int XYZX() const;									//Swizzle to XYZX Vector
	inline Vec4Int XYZY() const;									//Swizzle to XYZY Vector
	inline Vec4Int XYZZ() const;									//Swizzle to XYZZ Vector
	inline Vec4Int XYWX() const;									//Swizzle to XYWX Vector
	inline Vec4Int XYWY() const;									//Swizzle to XYWY Vector
	inline Vec4Int XYWZ() const;									//Swizzle to XYWZ Vector
	inline Vec4Int XYWW() const;									//Swizzle to XYWW Vector
	inline Vec4Int XZXX() const;									//Swizzle to XZXX Vector
	inline Vec4Int XZXY() const;									//Swizzle to XZXY Vector
	inline Vec4Int XZXZ() const;									//Swizzle to XZXZ Vector
	inline Vec4Int XZXW() const;									//Swizzle to XZXW Vector
	inline Vec4Int XZYX() const;									//Swizzle to XZYX Vector
	inline Vec4Int XZYY() const;									//Swizzle to XZYY Vector
	inline Vec4Int XZYZ() const;									//Swizzle to XZYZ Vector
	inline Vec4Int XZYW() const;									//Swizzle to XZYW Vector
	inline Vec4Int XZZX() const;									//Swizzle to XZZX Vector
	inline Vec4Int XZZY() const;									//Swizzle to XZZY Vector
	inline Vec4Int XZZZ() const;									//Swizzle to XZZZ Vector
	inline Vec4Int XZZW() const;									//Swizzle to XZZW Vector
	inline Vec4Int XZWX() const;									//Swizzle to XZWX Vector
	inline Vec4Int XZWY() const;									//Swizzle to XZWY Vector
	inline Vec4Int XZWZ() const;									//Swizzle to XZWZ Vector
	inline Vec4Int XZWW() const;									//Swizzle to XZWW Vector
	inline Vec4Int XWXX() const;									//Swizzle to XWXX Vector
	inline Vec4Int XWXY() const;									//Swizzle to XWXY Vector
	inline Vec4Int XWXZ() const;									//Swizzle to XWXZ Vector
	inline Vec4Int XWXW() const;									//Swizzle to XWXW Vector
	inline Vec4Int XWYX() const;									//Swizzle to XWYX Vector
	inline Vec4Int XWYY() const;									//Swizzle to XWYY Vector
	inline Vec4Int XWYZ() const;									//Swizzle to XWYZ Vector
	inline Vec4Int XWYW() const;									//Swizzle to XWYW Vector
	inline Vec4Int XWZX() const;									//Swizzle to XWZX Vector
	inline Vec4Int XWZY() const;									//Swizzle to XWZY Vector
	inline Vec4Int XWZZ() const;									//Swizzle to XWZZ Vector
	inline Vec4Int XWZW() const;									//Swizzle to XWZW Vector
	inline Vec4Int XWWX() const;									//Swizzle to XWWX Vector
	inline Vec4Int XWWY() const;									//Swizzle to XWWY Vector
	inline Vec4Int XWWZ() const;									//Swizzle to XWWZ Vector
	inline Vec4Int XWWW() const;									//Swizzle to XWWW Vector
	inline Vec4Int YXXX() const;									//Swizzle to YXXX Vector
	inline Vec4Int YXXY() const;									//Swizzle to YXXY Vector
	inline Vec4Int YXXZ() const;									//Swizzle to YXXZ Vector
	inline Vec4Int YXXW() const;									//Swizzle to YXXW Vector
	inline Vec4Int YXYX() const;									//Swizzle to YXYX Vector
	inline Vec4Int YXYY() const;									//Swizzle to YXYY Vector
	inline Vec4Int YXYZ() const;									//Swizzle to YXYZ Vector
	inline Vec4Int YXYW() const;									//Swizzle to YXYW Vector
	inline Vec4Int YXZX() const;									//Swizzle to YXZX Vector
	inline Vec4Int YXZY() const;									//Swizzle to YXZY Vector
	inline Vec4Int YXZZ() const;									//Swizzle to YXZZ Vector
	inline Vec4Int YXZW() const;									//Swizzle to YXZW Vector
	inline Vec4Int YXWX() const;									//Swizzle to YXWX Vector
	inline Vec4Int YXWY() const;									//Swizzle to YXWY Vector
	inline Vec4Int YXWZ() const;									//Swizzle to YXWZ Vector
	inline Vec4Int YXWW() const;									//Swizzle to YXWW Vector
	inline Vec4Int YYXX() const;									//Swizzle to YYXX Vector
	inline Vec4Int YYXY() const;									//Swizzle to YYXY Vector
	inline Vec4Int YYXZ() const;									//Swizzle to YYXZ Vector
	inline Vec4Int YYXW() const;									//Swizzle to YYXW Vector
	inline Vec4Int YYYX() const;									//Swizzle to YYYX Vector
	inline Vec4Int YYYY() const;									//Swizzle to YYYY Vector
	inline Vec4Int YYYZ() const;									//Swizzle to YYYZ Vector
	inline Vec4Int YYYW() const;									//Swizzle to YYYW Vector
	inline Vec4Int YYZX() const;									//Swizzle to YYZX Vector
	inline Vec4Int YYZY() const;									//Swizzle to YYZY Vector
	inline Vec4Int YYZZ() const;									//Swizzle to YYZZ Vector
	inline Vec4Int YYZW() const;									//Swizzle to YYZW Vector
	inline Vec4Int YYWX() const;									//Swizzle to YYWX Vector
	inline Vec4Int YYWY() const;									//Swizzle to YYWY Vector
	inline Vec4Int YYWZ() const;									//Swizzle to YYWZ Vector
	inline Vec4Int YYWW() const;									//Swizzle to YYWW Vector
	inline Vec4Int YZXX() const;									//Swizzle to YZXX Vector
	inline Vec4Int YZXY() const;									//Swizzle to YZXY Vector
	inline Vec4Int YZXZ() const;									//Swizzle to YZXZ Vector
	inline Vec4Int YZXW() const;									//Swizzle to YZXW Vector
	inline Vec4Int YZYX() const;									//Swizzle to YZYX Vector
	inline Vec4Int YZYY() const;									//Swizzle to YZYY Vector
	inline Vec4Int YZYZ() const;									//Swizzle to YZYZ Vector
	inline Vec4Int YZYW() const;									//Swizzle to YZYW Vector
	inline Vec4Int YZZX() const;									//Swizzle to YZZX Vector
	inline Vec4Int YZZY() const;									//Swizzle to YZZY Vector
	inline Vec4Int YZZZ() const;									//Swizzle to YZZZ Vector
	inline Vec4Int YZZW() const;									//Swizzle to YZZW Vector
	inline Vec4Int YZWX() const;									//Swizzle to YZWX Vector
	inline Vec4Int YZWY() const;									//Swizzle to YZWY Vector
	inline Vec4Int YZWZ() const;									//Swizzle to YZWZ Vector
	inline Vec4Int YZWW() const;									//Swizzle to YZWW Vector
	inline Vec4Int YWXX() const;									//Swizzle to YWXX Vector
	inline Vec4Int YWXY() const;									//Swizzle to YWXY Vector
	inline Vec4Int YWXZ() const;									//Swizzle to YWXZ Vector
	inline Vec4Int YWXW() const;									//Swizzle to YWXW Vector
	inline Vec4Int YWYX() const;									//Swizzle to YWYX Vector
	inline Vec4Int YWYY() const;									//Swizzle to YWYY Vector
	inline Vec4Int YWYZ() const;									//Swizzle to YWYZ Vector
	inline Vec4Int YWYW() const;									//Swizzle to YWYW Vector
	inline Vec4Int YWZX() const;									//Swizzle to YWZX Vector
	inline Vec4Int YWZY() const;									//Swizzle to YWZY Vector
	inline Vec4Int YWZZ() const;									//Swizzle to YWZZ Vector
	inline Vec4Int YWZW() const;									//Swizzle to YWZW Vector
	inline Vec4Int YWWX() const;									//Swizzle to YWWX Vector
	inline Vec4Int YWWY() const;									//Swizzle to YWWY Vector
	inline Vec4Int YWWZ() const;									//Swizzle to YWWZ Vector
	inline Vec4Int YWWW() const;									//Swizzle to YWWW Vector
	inline Vec4Int ZXXX() const;									//Swizzle to ZXXX Vector
	inline Vec4Int ZXXY() const;									//Swizzle to ZXXY Vector
	inline Vec4Int ZXXZ() const;									//Swizzle to ZXXZ Vector
	inline Vec4Int ZXXW() const;									//Swizzle to ZXXW Vector
	inline Vec4Int ZXYX() const;									//Swizzle to ZXYX Vector
	inline Vec4Int ZXYY() const;									//Swizzle to ZXYY Vector
	inline Vec4Int ZXYZ() const;									//Swizzle to ZXYZ Vector
	inline Vec4Int ZXYW() const;									//Swizzle to ZXYW Vector
	inline Vec4Int ZXZX() const;									//Swizzle to ZXZX Vector
	inline Vec4Int ZXZY() const;									//Swizzle to ZXZY Vector
	inline Vec4Int ZXZZ() const;									//Swizzle to ZXZZ Vector
	inline Vec4Int ZXZW() const;									//Swizzle to ZXZW Vector
	inline Vec4Int ZXWX() const;									//Swizzle to ZXWX Vector
	inline Vec4Int ZXWY() const;									//Swizzle to ZXWY Vector
	inline Vec4Int ZXWZ() const;									//Swizzle to ZXWZ Vector
	inline Vec4Int ZXWW() const;									//Swizzle to ZXWW Vector
	inline Vec4Int ZYXX() const;									//Swizzle to ZYXX Vector
	inline Vec4Int ZYXY() const;									//Swizzle to ZYXY Vector
	inline Vec4Int ZYXZ() const;									//Swizzle to ZYXZ Vector
	inline Vec4Int ZYXW() const;									//Swizzle to ZYXW Vector
	inline Vec4Int ZYYX() const;									//Swizzle to ZYYX Vector
	inline Vec4Int ZYYY() const;									//Swizzle to ZYYY Vector
	inline Vec4Int ZYYZ() const;									//Swizzle to ZYYZ Vector
	inline Vec4Int ZYYW() const;									//Swizzle to ZYYW Vector
	inline Vec4Int ZYZX() const;									//Swizzle to ZYZX Vector
	inline Vec4Int ZYZY() const;									//Swizzle to ZYZY Vector
	inline Vec4Int ZYZZ() const;									//Swizzle to ZYZZ Vector
	inline Vec4Int ZYZW() const;									//Swizzle to ZYZW Vector
	inline Vec4Int ZYWX() const;									//Swizzle to ZYWX Vector
	inline Vec4Int ZYWY() const;									//Swizzle to ZYWY Vector
	inline Vec4Int ZYWZ() const;									//Swizzle to ZYWZ Vector
	inline Vec4Int ZYWW() const;									//Swizzle to ZYWW Vector
	inline Vec4Int ZZXX() const;									//Swizzle to ZZXX Vector
	inline Vec4Int ZZXY() const;									//Swizzle to ZZXY Vector
	inline Vec4Int ZZXZ() const;									//Swizzle to ZZXZ Vector
	inline Vec4Int ZZXW() const;									//Swizzle to ZZXW Vector
	inline Vec4Int ZZYX() const;									//Swizzle to ZZYX Vector
	inline Vec4Int ZZYY() const;									//Swizzle to ZZYY Vector
	inline Vec4Int ZZYZ() const;									//Swizzle to ZZYZ Vector
	inline Vec4Int ZZYW() const;									//Swizzle to ZZYW Vector
	inline Vec4Int ZZZX() const;									//Swizzle to ZZZX Vector
	inline Vec4Int ZZZY() const;									//Swizzle to ZZZY Vector
	inline Vec4Int ZZZZ() const;									//Swizzle to ZZZZ Vector
	inline Vec4Int ZZZW() const;									//Swizzle to ZZZW Vector
	inline Vec4Int ZZWX() const;									//Swizzle to ZZWX Vector
	inline Vec4Int ZZWY() const;									//Swizzle to ZZWY Vector
	inline Vec4Int ZZWZ() const;									//Swizzle to ZZWZ Vector
	inline Vec4Int ZZWW() const;									//Swizzle to ZZWW Vector
	inline Vec4Int ZWXX() const;									//Swizzle to ZWXX Vector
	inline Vec4Int ZWXY() const;									//Swizzle to ZWXY Vector
	inline Vec4Int ZWXZ() const;									//Swizzle to ZWXZ Vector
	inline Vec4Int ZWXW() const;									//Swizzle to ZWXW Vector
	inline Vec4Int ZWYX() const;									//Swizzle to ZWYX Vector
	inline Vec4Int ZWYY() const;									//Swizzle to ZWYY Vector
	inline Vec4Int ZWYZ() const;									//Swizzle to ZWYZ Vector
	inline Vec4Int ZWYW() const;									//Swizzle to ZWYW Vector
	inline Vec4Int ZWZX() const;									//Swizzle to ZWZX Vector
	inline Vec4Int ZWZY() const;									//Swizzle to ZWZY Vector
	inline Vec4Int ZWZZ() const;									//Swizzle to ZWZZ Vector
	inline Vec4Int ZWZW() const;									//Swizzle to ZWZW Vector
	inline Vec4Int ZWWX() const;									//Swizzle to ZWWX Vector
	inline Vec4Int ZWWY() const;									//Swizzle to ZWWY Vector
	inline Vec4Int ZWWZ() const;									//Swizzle to ZWWZ Vector
	inline Vec4Int ZWWW() const;									//Swizzle to ZWWW Vector
	inline Vec4Int WXXX() const;									//Swizzle to WXXX Vector
	inline Vec4Int WXXY() const;									//Swizzle to WXXY Vector
	inline Vec4Int WXXZ() const;									//Swizzle to WXXZ Vector
	inline Vec4Int WXXW() const;									//Swizzle to WXXW Vector
	inline Vec4Int WXYX() const;									//Swizzle to WXYX Vector
	inline Vec4Int WXYY() const;									//Swizzle to WXYY Vector
	inline Vec4Int WXYZ() const;									//Swizzle to WXYZ Vector
	inline Vec4Int WXYW() const;									//Swizzle to WXYW Vector
	inline Vec4Int WXZX() const;									//Swizzle to WXZX Vector
	inline Vec4Int WXZY() const;									//Swizzle to WXZY Vector
	inline Vec4Int WXZZ() const;									//Swizzle to WXZZ Vector
	inline Vec4Int WXZW() const;									//Swizzle to WXZW Vector
	inline Vec4Int WXWX() const;									//Swizzle to WXWX Vector
	inline Vec4Int WXWY() const;									//Swizzle to WXWY Vector
	inline Vec4Int WXWZ() const;									//Swizzle to WXWZ Vector
	inline Vec4Int WXWW() const;									//Swizzle to WXWW Vector
	inline Vec4Int WYXX() const;									//Swizzle to WYXX Vector
	inline Vec4Int WYXY() const;									//Swizzle to WYXY Vector
	inline Vec4Int WYXZ() const;									//Swizzle to WYXZ Vector
	inline Vec4Int WYXW() const;									//Swizzle to WYXW Vector
	inline Vec4Int WYYX() const;									//Swizzle to WYYX Vector
	inline Vec4Int WYYY() const;									//Swizzle to WYYY Vector
	inline Vec4Int WYYZ() const;									//Swizzle to WYYZ Vector
	inline Vec4Int WYYW() const;									//Swizzle to WYYW Vector
	inline Vec4Int WYZX() const;									//Swizzle to WYZX Vector
	inline Vec4Int WYZY() const;									//Swizzle to WYZY Vector
	inline Vec4Int WYZZ() const;									//Swizzle to WYZZ Vector
	inline Vec4Int WYZW() const;									//Swizzle to WYZW Vector
	inline Vec4Int WYWX() const;									//Swizzle to WYWX Vector
	inline Vec4Int WYWY() const;									//Swizzle to WYWY Vector
	inline Vec4Int WYWZ() const;									//Swizzle to WYWZ Vector
	inline Vec4Int WYWW() const;									//Swizzle to WYWW Vector
	inline Vec4Int WZXX() const;									//Swizzle to WZXX Vector
	inline Vec4Int WZXY() const;									//Swizzle to WZXY Vector
	inline Vec4Int WZXZ() const;									//Swizzle to WZXZ Vector
	inline Vec4Int WZXW() const;									//Swizzle to WZXW Vector
	inline Vec4Int WZYX() const;									//Swizzle to WZYX Vector
	inline Vec4Int WZYY() const;									//Swizzle to WZYY Vector
	inline Vec4Int WZYZ() const;									//Swizzle to WZYZ Vector
	inline Vec4Int WZYW() const;									//Swizzle to WZYW Vector
	inline Vec4Int WZZX() const;									//Swizzle to WZZX Vector
	inline Vec4Int WZZY() const;									//Swizzle to WZZY Vector
	inline Vec4Int WZZZ() const;									//Swizzle to WZZZ Vector
	inline Vec4Int WZZW() const;									//Swizzle to WZZW Vector
	inline Vec4Int WZWX() const;									//Swizzle to WZWX Vector
	inline Vec4Int WZWY() const;									//Swizzle to WZWY Vector
	inline Vec4Int WZWZ() const;									//Swizzle to WZWZ Vector
	inline Vec4Int WZWW() const;									//Swizzle to WZWW Vector
	inline Vec4Int WWXX() const;									//Swizzle to WWXX Vector
	inline Vec4Int WWXY() const;									//Swizzle to WWXY Vector
	inline Vec4Int WWXZ() const;									//Swizzle to WWXZ Vector
	inline Vec4Int WWXW() const;									//Swizzle to WWXW Vector
	inline Vec4Int WWYX() const;									//Swizzle to WWYX Vector
	inline Vec4Int WWYY() const;									//Swizzle to WWYY Vector
	inline Vec4Int WWYZ() const;									//Swizzle to WWYZ Vector
	inline Vec4Int WWYW() const;									//Swizzle to WWYW Vector
	inline Vec4Int WWZX() const;									//Swizzle to WWZX Vector
	inline Vec4Int WWZY() const;									//Swizzle to WWZY Vector
	inline Vec4Int WWZZ() const;									//Swizzle to WWZZ Vector
	inline Vec4Int WWZW() const;									//Swizzle to WWZW Vector
	inline Vec4Int WWWX() const;									//Swizzle to WWWX Vector
	inline Vec4Int WWWY() const;									//Swizzle to WWWY Vector
	inline Vec4Int WWWZ() const;									//Swizzle to WWWZ Vector
	inline Vec4Int WWWW() const;									//Swizzle to WWWW Vector
	inline Vec4Int RRRR() const;									//Swizzle to RRRR Vector
	inline Vec4Int RRRG() const;									//Swizzle to RRRG Vector
	inline Vec4Int RRRB() const;									//Swizzle to RRRB Vector
	inline Vec4Int RRRA() const;									//Swizzle to RRRA Vector
	inline Vec4Int RRGR() const;									//Swizzle to RRGR Vector
	inline Vec4Int RRGG() const;									//Swizzle to RRGG Vector
	inline Vec4Int RRGB() const;									//Swizzle to RRGB Vector
	inline Vec4Int RRGA() const;									//Swizzle to RRGA Vector
	inline Vec4Int RRBR() const;									//Swizzle to RRBR Vector
	inline Vec4Int RRBG() const;									//Swizzle to RRBG Vector
	inline Vec4Int RRBB() const;									//Swizzle to RRBB Vector
	inline Vec4Int RRBA() const;									//Swizzle to RRBA Vector
	inline Vec4Int RRAR() const;									//Swizzle to RRAR Vector
	inline Vec4Int RRAG() const;									//Swizzle to RRAG Vector
	inline Vec4Int RRAB() const;									//Swizzle to RRAB Vector
	inline Vec4Int RRAA() const;									//Swizzle to RRAA Vector
	inline Vec4Int RGRR() const;									//Swizzle to RGRR Vector
	inline Vec4Int RGRG() const;									//Swizzle to RGRG Vector
	inline Vec4Int RGRB() const;									//Swizzle to RGRB Vector
	inline Vec4Int RGRA() const;									//Swizzle to RGRA Vector
	inline Vec4Int RGGR() const;									//Swizzle to RGGR Vector
	inline Vec4Int RGGG() const;									//Swizzle to RGGG Vector
	inline Vec4Int RGGB() const;									//Swizzle to RGGB Vector
	inline Vec4Int RGGA() const;									//Swizzle to RGGA Vector
	inline Vec4Int RGBR() const;									//Swizzle to RGBR Vector
	inline Vec4Int RGBG() const;									//Swizzle to RGBG Vector
	inline Vec4Int RGBB() const;									//Swizzle to RGBB Vector
	inline Vec4Int RGAR() const;									//Swizzle to RGAR Vector
	inline Vec4Int RGAG() const;									//Swizzle to RGAG Vector
	inline Vec4Int RGAB() const;									//Swizzle to RGAB Vector
	inline Vec4Int RGAA() const;									//Swizzle to RGAA Vector
	inline Vec4Int RBRR() const;									//Swizzle to RBRR Vector
	inline Vec4Int RBRG() const;									//Swizzle to RBRG Vector
	inline Vec4Int RBRB() const;									//Swizzle to RBRB Vector
	inline Vec4Int RBRA() const;									//Swizzle to RBRA Vector
	inline Vec4Int RBGR() const;									//Swizzle to RBGR Vector
	inline Vec4Int RBGG() const;									//Swizzle to RBGG Vector
	inline Vec4Int RBGB() const;									//Swizzle to RBGB Vector
	inline Vec4Int RBGA() const;									//Swizzle to RBGA Vector
	inline Vec4Int RBBR() const;									//Swizzle to RBBR Vector
	inline Vec4Int RBBG() const;									//Swizzle to RBBG Vector
	inline Vec4Int RBBB() const;									//Swizzle to RBBB Vector
	inline Vec4Int RBBA() const;									//Swizzle to RBBA Vector
	inline Vec4Int RBAR() const;									//Swizzle to RBAR Vector
	inline Vec4Int RBAG() const;									//Swizzle to RBAG Vector
	inline Vec4Int RBAB() const;									//Swizzle to RBAB Vector
	inline Vec4Int RBAA() const;									//Swizzle to RBAA Vector
	inline Vec4Int RARR() const;									//Swizzle to RARR Vector
	inline Vec4Int RARG() const;									//Swizzle to RARG Vector
	inline Vec4Int RARB() const;									//Swizzle to RARB Vector
	inline Vec4Int RARA() const;									//Swizzle to RARA Vector
	inline Vec4Int RAGR() const;									//Swizzle to RAGR Vector
	inline Vec4Int RAGG() const;									//Swizzle to RAGG Vector
	inline Vec4Int RAGB() const;									//Swizzle to RAGB Vector
	inline Vec4Int RAGA() const;									//Swizzle to RAGA Vector
	inline Vec4Int RABR() const;									//Swizzle to RABR Vector
	inline Vec4Int RABG() const;									//Swizzle to RABG Vector
	inline Vec4Int RABB() const;									//Swizzle to RABB Vector
	inline Vec4Int RABA() const;									//Swizzle to RABA Vector
	inline Vec4Int RAAR() const;									//Swizzle to RAAR Vector
	inline Vec4Int RAAG() const;									//Swizzle to RAAG Vector
	inline Vec4Int RAAB() const;									//Swizzle to RAAB Vector
	inline Vec4Int RAAA() const;									//Swizzle to RAAA Vector
	inline Vec4Int GRRR() const;									//Swizzle to GRRR Vector
	inline Vec4Int GRRG() const;									//Swizzle to GRRG Vector
	inline Vec4Int GRRB() const;									//Swizzle to GRRB Vector
	inline Vec4Int GRRA() const;									//Swizzle to GRRA Vector
	inline Vec4Int GRGR() const;									//Swizzle to GRGR Vector
	inline Vec4Int GRGG() const;									//Swizzle to GRGG Vector
	inline Vec4Int GRGB() const;									//Swizzle to GRGB Vector
	inline Vec4Int GRGA() const;									//Swizzle to GRGA Vector
	inline Vec4Int GRBR() const;									//Swizzle to GRBR Vector
	inline Vec4Int GRBG() const;									//Swizzle to GRBG Vector
	inline Vec4Int GRBB() const;									//Swizzle to GRBB Vector
	inline Vec4Int GRBA() const;									//Swizzle to GRBA Vector
	inline Vec4Int GRAR() const;									//Swizzle to GRAR Vector
	inline Vec4Int GRAG() const;									//Swizzle to GRAG Vector
	inline Vec4Int GRAB() const;									//Swizzle to GRAB Vector
	inline Vec4Int GRAA() const;									//Swizzle to GRAA Vector
	inline Vec4Int GGRR() const;									//Swizzle to GGRR Vector
	inline Vec4Int GGRG() const;									//Swizzle to GGRG Vector
	inline Vec4Int GGRB() const;									//Swizzle to GGRB Vector
	inline Vec4Int GGRA() const;									//Swizzle to GGRA Vector
	inline Vec4Int GGGR() const;									//Swizzle to GGGR Vector
	inline Vec4Int GGGG() const;									//Swizzle to GGGG Vector
	inline Vec4Int GGGB() const;									//Swizzle to GGGB Vector
	inline Vec4Int GGGA() const;									//Swizzle to GGGA Vector
	inline Vec4Int GGBR() const;									//Swizzle to GGBR Vector
	inline Vec4Int GGBG() const;									//Swizzle to GGBG Vector
	inline Vec4Int GGBB() const;									//Swizzle to GGBB Vector
	inline Vec4Int GGBA() const;									//Swizzle to GGBA Vector
	inline Vec4Int GGAR() const;									//Swizzle to GGAR Vector
	inline Vec4Int GGAG() const;									//Swizzle to GGAG Vector
	inline Vec4Int GGAB() const;									//Swizzle to GGAB Vector
	inline Vec4Int GGAA() const;									//Swizzle to GGAA Vector
	inline Vec4Int GBRR() const;									//Swizzle to GBRR Vector
	inline Vec4Int GBRG() const;									//Swizzle to GBRG Vector
	inline Vec4Int GBRB() const;									//Swizzle to GBRB Vector
	inline Vec4Int GBRA() const;									//Swizzle to GBRA Vector
	inline Vec4Int GBGR() const;									//Swizzle to GBGR Vector
	inline Vec4Int GBGG() const;									//Swizzle to GBGG Vector
	inline Vec4Int GBGB() const;									//Swizzle to GBGB Vector
	inline Vec4Int GBGA() const;									//Swizzle to GBGA Vector
	inline Vec4Int GBBR() const;									//Swizzle to GBBR Vector
	inline Vec4Int GBBG() const;									//Swizzle to GBBG Vector
	inline Vec4Int GBBB() const;									//Swizzle to GBBB Vector
	inline Vec4Int GBBA() const;									//Swizzle to GBBA Vector
	inline Vec4Int GBAR() const;									//Swizzle to GBAR Vector
	inline Vec4Int GBAG() const;									//Swizzle to GBAG Vector
	inline Vec4Int GBAB() const;									//Swizzle to GBAB Vector
	inline Vec4Int GBAA() const;									//Swizzle to GBAA Vector
	inline Vec4Int GARR() const;									//Swizzle to GARR Vector
	inline Vec4Int GARG() const;									//Swizzle to GARG Vector
	inline Vec4Int GARB() const;									//Swizzle to GARB Vector
	inline Vec4Int GARA() const;									//Swizzle to GARA Vector
	inline Vec4Int GAGR() const;									//Swizzle to GAGR Vector
	inline Vec4Int GAGG() const;									//Swizzle to GAGG Vector
	inline Vec4Int GAGB() const;									//Swizzle to GAGB Vector
	inline Vec4Int GAGA() const;									//Swizzle to GAGA Vector
	inline Vec4Int GABR() const;									//Swizzle to GABR Vector
	inline Vec4Int GABG() const;									//Swizzle to GABG Vector
	inline Vec4Int GABB() const;									//Swizzle to GABB Vector
	inline Vec4Int GABA() const;									//Swizzle to GABA Vector
	inline Vec4Int GAAR() const;									//Swizzle to GAAR Vector
	inline Vec4Int GAAG() const;									//Swizzle to GAAG Vector
	inline Vec4Int GAAB() const;									//Swizzle to GAAB Vector
	inline Vec4Int GAAA() const;									//Swizzle to GAAA Vector
	inline Vec4Int BRRR() const;									//Swizzle to BRRR Vector
	inline Vec4Int BRRG() const;									//Swizzle to BRRG Vector
	inline Vec4Int BRRB() const;									//Swizzle to BRRB Vector
	inline Vec4Int BRRA() const;									//Swizzle to BRRA Vector
	inline Vec4Int BRGR() const;									//Swizzle to BRGR Vector
	inline Vec4Int BRGG() const;									//Swizzle to BRGG Vector
	inline Vec4Int BRGB() const;									//Swizzle to BRGB Vector
	inline Vec4Int BRGA() const;									//Swizzle to BRGA Vector
	inline Vec4Int BRBR() const;									//Swizzle to BRBR Vector
	inline Vec4Int BRBG() const;									//Swizzle to BRBG Vector
	inline Vec4Int BRBB() const;									//Swizzle to BRBB Vector
	inline Vec4Int BRBA() const;									//Swizzle to BRBA Vector
	inline Vec4Int BRAR() const;									//Swizzle to BRAR Vector
	inline Vec4Int BRAG() const;									//Swizzle to BRAG Vector
	inline Vec4Int BRAB() const;									//Swizzle to BRAB Vector
	inline Vec4Int BRAA() const;									//Swizzle to BRAA Vector
	inline Vec4Int BGRR() const;									//Swizzle to BGRR Vector
	inline Vec4Int BGRG() const;									//Swizzle to BGRG Vector
	inline Vec4Int BGRB() const;									//Swizzle to BGRB Vector
	inline Vec4Int BGRA() const;									//Swizzle to BGRA Vector
	inline Vec4Int BGGR() const;									//Swizzle to BGGR Vector
	inline Vec4Int BGGG() const;									//Swizzle to BGGG Vector
	inline Vec4Int BGGB() const;									//Swizzle to BGGB Vector
	inline Vec4Int BGGA() const;									//Swizzle to BGGA Vector
	inline Vec4Int BGBR() const;									//Swizzle to BGBR Vector
	inline Vec4Int BGBG() const;									//Swizzle to BGBG Vector
	inline Vec4Int BGBB() const;									//Swizzle to BGBB Vector
	inline Vec4Int BGBA() const;									//Swizzle to BGBA Vector
	inline Vec4Int BGAR() const;									//Swizzle to BGAR Vector
	inline Vec4Int BGAG() const;									//Swizzle to BGAG Vector
	inline Vec4Int BGAB() const;									//Swizzle to BGAB Vector
	inline Vec4Int BGAA() const;									//Swizzle to BGAA Vector
	inline Vec4Int BBRR() const;									//Swizzle to BBRR Vector
	inline Vec4Int BBRG() const;									//Swizzle to BBRG Vector
	inline Vec4Int BBRB() const;									//Swizzle to BBRB Vector
	inline Vec4Int BBRA() const;									//Swizzle to BBRA Vector
	inline Vec4Int BBGR() const;									//Swizzle to BBGR Vector
	inline Vec4Int BBGG() const;									//Swizzle to BBGG Vector
	inline Vec4Int BBGB() const;									//Swizzle to BBGB Vector
	inline Vec4Int BBGA() const;									//Swizzle to BBGA Vector
	inline Vec4Int BBBR() const;									//Swizzle to BBBR Vector
	inline Vec4Int BBBG() const;									//Swizzle to BBBG Vector
	inline Vec4Int BBBB() const;									//Swizzle to BBBB Vector
	inline Vec4Int BBBA() const;									//Swizzle to BBBA Vector
	inline Vec4Int BBAR() const;									//Swizzle to BBAR Vector
	inline Vec4Int BBAG() const;									//Swizzle to BBAG Vector
	inline Vec4Int BBAB() const;									//Swizzle to BBAB Vector
	inline Vec4Int BBAA() const;									//Swizzle to BBAA Vector
	inline Vec4Int BARR() const;									//Swizzle to BARR Vector
	inline Vec4Int BARG() const;									//Swizzle to BARG Vector
	inline Vec4Int BARB() const;									//Swizzle to BARB Vector
	inline Vec4Int BARA() const;									//Swizzle to BARA Vector
	inline Vec4Int BAGR() const;									//Swizzle to BAGR Vector
	inline Vec4Int BAGG() const;									//Swizzle to BAGG Vector
	inline Vec4Int BAGB() const;									//Swizzle to BAGB Vector
	inline Vec4Int BAGA() const;									//Swizzle to BAGA Vector
	inline Vec4Int BABR() const;									//Swizzle to BABR Vector
	inline Vec4Int BABG() const;									//Swizzle to BABG Vector
	inline Vec4Int BABB() const;									//Swizzle to BABB Vector
	inline Vec4Int BABA() const;									//Swizzle to BABA Vector
	inline Vec4Int BAAR() const;									//Swizzle to BAAR Vector
	inline Vec4Int BAAG() const;									//Swizzle to BAAG Vector
	inline Vec4Int BAAB() const;									//Swizzle to BAAB Vector
	inline Vec4Int BAAA() const;									//Swizzle to BAAA Vector
	inline Vec4Int ARRR() const;									//Swizzle to ARRR Vector
	inline Vec4Int ARRG() const;									//Swizzle to ARRG Vector
	inline Vec4Int ARRB() const;									//Swizzle to ARRB Vector
	inline Vec4Int ARRA() const;									//Swizzle to ARRA Vector
	inline Vec4Int ARGR() const;									//Swizzle to ARGR Vector
	inline Vec4Int ARGG() const;									//Swizzle to ARGG Vector
	inline Vec4Int ARGB() const;									//Swizzle to ARGB Vector
	inline Vec4Int ARGA() const;									//Swizzle to ARGA Vector
	inline Vec4Int ARBR() const;									//Swizzle to ARBR Vector
	inline Vec4Int ARBG() const;									//Swizzle to ARBG Vector
	inline Vec4Int ARBB() const;									//Swizzle to ARBB Vector
	inline Vec4Int ARBA() const;									//Swizzle to ARBA Vector
	inline Vec4Int ARAR() const;									//Swizzle to ARAR Vector
	inline Vec4Int ARAG() const;									//Swizzle to ARAG Vector
	inline Vec4Int ARAB() const;									//Swizzle to ARAB Vector
	inline Vec4Int ARAA() const;									//Swizzle to ARAA Vector
	inline Vec4Int AGRR() const;									//Swizzle to AGRR Vector
	inline Vec4Int AGRG() const;									//Swizzle to AGRG Vector
	inline Vec4Int AGRB() const;									//Swizzle to AGRB Vector
	inline Vec4Int AGRA() const;									//Swizzle to AGRA Vector
	inline Vec4Int AGGR() const;									//Swizzle to AGGR Vector
	inline Vec4Int AGGG() const;									//Swizzle to AGGG Vector
	inline Vec4Int AGGB() const;									//Swizzle to AGGB Vector
	inline Vec4Int AGGA() const;									//Swizzle to AGGA Vector
	inline Vec4Int AGBR() const;									//Swizzle to AGBR Vector
	inline Vec4Int AGBG() const;									//Swizzle to AGBG Vector
	inline Vec4Int AGBB() const;									//Swizzle to AGBB Vector
	inline Vec4Int AGBA() const;									//Swizzle to AGBA Vector
	inline Vec4Int AGAR() const;									//Swizzle to AGAR Vector
	inline Vec4Int AGAG() const;									//Swizzle to AGAG Vector
	inline Vec4Int AGAB() const;									//Swizzle to AGAB Vector
	inline Vec4Int AGAA() const;									//Swizzle to AGAA Vector
	inline Vec4Int ABRR() const;									//Swizzle to ABRR Vector
	inline Vec4Int ABRG() const;									//Swizzle to ABRG Vector
	inline Vec4Int ABRB() const;									//Swizzle to ABRB Vector
	inline Vec4Int ABRA() const;									//Swizzle to ABRA Vector
	inline Vec4Int ABGR() const;									//Swizzle to ABGR Vector
	inline Vec4Int ABGG() const;									//Swizzle to ABGG Vector
	inline Vec4Int ABGB() const;									//Swizzle to ABGB Vector
	inline Vec4Int ABGA() const;									//Swizzle to ABGA Vector
	inline Vec4Int ABBR() const;									//Swizzle to ABBR Vector
	inline Vec4Int ABBG() const;									//Swizzle to ABBG Vector
	inline Vec4Int ABBB() const;									//Swizzle to ABBB Vector
	inline Vec4Int ABBA() const;									//Swizzle to ABBA Vector
	inline Vec4Int ABAR() const;									//Swizzle to ABAR Vector
	inline Vec4Int ABAG() const;									//Swizzle to ABAG Vector
	inline Vec4Int ABAB() const;									//Swizzle to ABAB Vector
	inline Vec4Int ABAA() const;									//Swizzle to ABAA Vector
	inline Vec4Int AARR() const;									//Swizzle to AARR Vector
	inline Vec4Int AARG() const;									//Swizzle to AARG Vector
	inline Vec4Int AARB() const;									//Swizzle to AARB Vector
	inline Vec4Int AARA() const;									//Swizzle to AARA Vector
	inline Vec4Int AAGR() const;									//Swizzle to AAGR Vector
	inline Vec4Int AAGG() const;									//Swizzle to AAGG Vector
	inline Vec4Int AAGB() const;									//Swizzle to AAGB Vector
	inline Vec4Int AAGA() const;									//Swizzle to AAGA Vector
	inline Vec4Int AABR() const;									//Swizzle to AABR Vector
	inline Vec4Int AABG() const;									//Swizzle to AABG Vector
	inline Vec4Int AABB() const;									//Swizzle to AABB Vector
	inline Vec4Int AABA() const;									//Swizzle to AABA Vector
	inline Vec4Int AAAR() const;									//Swizzle to AAAR Vector
	inline Vec4Int AAAG() const;									//Swizzle to AAAG Vector
	inline Vec4Int AAAB() const;									//Swizzle to AAAB Vector
	inline Vec4Int AAAA() const;									//Swizzle to AAAA Vector
};

#pragma endregion

#endif