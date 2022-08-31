
#include "HCVector.h"

struct MatrixF {
	Vec4F m_vRows[4];

	HC_INLINE MatrixF() {};
	HC_INLINE explicit MatrixF(Vec4F _vRow1, Vec4F _vRow2, Vec4F _vRow3, Vec4F _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE explicit MatrixF(Vec4F* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }
	HC_INLINE Vec4F operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4F& operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4F Row1() { return m_vRows[0]; }
	HC_INLINE Vec4F Row2() { return m_vRows[1]; }
	HC_INLINE Vec4F Row3() { return m_vRows[2]; }
	HC_INLINE Vec4F Row4() { return m_vRows[3]; }
	HC_INLINE void SetRow1(Vec4F _vRow) { m_vRows[0] = _vRow; }
	HC_INLINE void SetRow2(Vec4F _vRow) { m_vRows[1] = _vRow; }
	HC_INLINE void SetRow3(Vec4F _vRow) { m_vRows[2] = _vRow; }
	HC_INLINE void SetRow4(Vec4F _vRow) { m_vRows[3] = _vRow; }
};

struct MatrixD {
	Vec4D m_vRows[4];

	HC_INLINE MatrixD() {};
	HC_INLINE explicit MatrixD(Vec4D _vRow1, Vec4D _vRow2, Vec4D _vRow3, Vec4D _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE explicit MatrixD(Vec4D* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }
	HC_INLINE Vec4D operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4D& operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4D Row1() { return m_vRows[0]; }
	HC_INLINE Vec4D Row2() { return m_vRows[1]; }
	HC_INLINE Vec4D Row3() { return m_vRows[2]; }
	HC_INLINE Vec4D Row4() { return m_vRows[3]; }
	HC_INLINE void SetRow1(Vec4D _vRow) { m_vRows[0] = _vRow; }
	HC_INLINE void SetRow2(Vec4D _vRow) { m_vRows[1] = _vRow; }
	HC_INLINE void SetRow3(Vec4D _vRow) { m_vRows[2] = _vRow; }
	HC_INLINE void SetRow4(Vec4D _vRow) { m_vRows[3] = _vRow; }
};

struct MatrixI {
	Vec4I m_vRows[4];

	HC_INLINE MatrixI() {};
	HC_INLINE explicit MatrixI(Vec4I _vRow1, Vec4I _vRow2, Vec4I _vRow3, Vec4I _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE explicit MatrixI(Vec4I* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }
	HC_INLINE Vec4I operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4I& operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4I Row1() { return m_vRows[0]; }
	HC_INLINE Vec4I Row2() { return m_vRows[1]; }
	HC_INLINE Vec4I Row3() { return m_vRows[2]; }
	HC_INLINE Vec4I Row4() { return m_vRows[3]; }
	HC_INLINE void SetRow1(Vec4I _vRow) { m_vRows[0] = _vRow; }
	HC_INLINE void SetRow2(Vec4I _vRow) { m_vRows[1] = _vRow; }
	HC_INLINE void SetRow3(Vec4I _vRow) { m_vRows[2] = _vRow; }
	HC_INLINE void SetRow4(Vec4I _vRow) { m_vRows[3] = _vRow; }
};


HC_INLINE MatrixF Transpose(MatrixF _mMat) {
	__m128 temp0 = _mm_unpacklo_ps(_mMat[0].m_fVec, _mMat[2].m_fVec);
	__m128 temp1 = _mm_unpacklo_ps(_mMat[1].m_fVec, _mMat[3].m_fVec);
	__m128 temp2 = _mm_unpackhi_ps(_mMat[0].m_fVec, _mMat[2].m_fVec);
	__m128 temp3 = _mm_unpackhi_ps(_mMat[1].m_fVec, _mMat[3].m_fVec);

	_mMat[0] = Vec4F(_mm_unpacklo_ps(temp0, temp1));
	_mMat[1] = Vec4F(_mm_unpackhi_ps(temp0, temp1));
	_mMat[2] = Vec4F(_mm_unpacklo_ps(temp2, temp3));
	_mMat[3] = Vec4F(_mm_unpackhi_ps(temp2, temp3));

	return _mMat;
}
HC_INLINE float Determinant(MatrixF _mMat) {
	//Sub matrices
	Vec4F A = Vec4F(_mm_movelh_ps(_mMat[0].m_fVec, _mMat[1].m_fVec));
	Vec4F B = Vec4F(_mm_movehl_ps(_mMat[1].m_fVec, _mMat[0].m_fVec));
	Vec4F C = Vec4F(_mm_movelh_ps(_mMat[2].m_fVec, _mMat[3].m_fVec));
	Vec4F D = Vec4F(_mm_movehl_ps(_mMat[3].m_fVec, _mMat[2].m_fVec));

	//Determinants
	Vec4F dets = Vec4F(_mm_sub_ps(_mm_mul_ps(HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 0, 2, 0, 2).m_fVec, HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 1, 3, 1, 3).m_fVec),
		_mm_mul_ps(HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 1, 3, 1, 3).m_fVec, HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 0, 2, 0, 2).m_fVec)));
	float detA = dets.X();
	float detB = dets.Y();
	float detC = dets.Z();
	float detD = dets.W();
	//D adjmul C
	Vec4F DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4F AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());

	return ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
}
HC_INLINE MatrixF Inverse(MatrixF _mMat) {

	//Sub matrices
	Vec4F A = Vec4F(_mm_movelh_ps(_mMat[0].m_fVec, _mMat[1].m_fVec));
	Vec4F B = Vec4F(_mm_movehl_ps(_mMat[1].m_fVec, _mMat[0].m_fVec));
	Vec4F C = Vec4F(_mm_movelh_ps(_mMat[2].m_fVec, _mMat[3].m_fVec));
	Vec4F D = Vec4F(_mm_movehl_ps(_mMat[3].m_fVec, _mMat[2].m_fVec));

	//Determinants
	Vec4F dets = Vec4F(_mm_sub_ps(_mm_mul_ps(HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 0, 2, 0, 2).m_fVec, HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 1, 3, 1, 3).m_fVec),
								  _mm_mul_ps(HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 1, 3, 1, 3).m_fVec, HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 0, 2, 0, 2).m_fVec)));
	float detA = dets.X();
	float detB = dets.Y();
	float detC = dets.Z();
	float detD = dets.W();

	//D adjmul C
	Vec4F DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4F AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());
	//DetM
	float detM = ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
	//No inverse, return 0
	if (detM == 0.0f) { return MatrixF(); }
	//Reciprocal
	Vec4F vDet = Vec4F(1.0f, -1.0f, -1.0f, 1.0f) / detM;

	//X Row
	Vec4F X = ((A * detD) - ((B * DC.XWXW()) + (B.YXWZ() * DC.ZYZY()))) * vDet;
	//W Row
	Vec4F W = ((D * detA) - ((C * AB.XWXW()) + (C.YXWZ() * AB.ZYZY()))) * vDet;
	//Y Row
	Vec4F Y = ((C * detB) - ((D * AB.WXWX()) - (D.YXWZ() * AB.ZYZY()))) * vDet;
	//Z Row
	Vec4F Z = ((B * detC) - ((A * DC.WXWX()) - (A.YXWZ() * DC.ZYZY()))) * vDet;

	_mMat[0] = HC_SHUFFLE4F_2(X, Y, 3, 1, 3, 1);
	_mMat[1] = HC_SHUFFLE4F_2(X, Y, 2, 0, 2, 0);
	_mMat[2] = HC_SHUFFLE4F_2(Z, W, 3, 1, 3, 1);
	_mMat[3] = HC_SHUFFLE4F_2(Z, W, 2, 0, 2, 0);

	return _mMat;
}
HC_INLINE MatrixF operator+(MatrixF _mLeft, MatrixF _mRight) {
	_mLeft[0] = _mLeft[0] + _mRight[0];
	_mLeft[1] = _mLeft[1] + _mRight[1];
	_mLeft[2] = _mLeft[2] + _mRight[2];
	_mLeft[3] = _mLeft[3] + _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixF operator-(MatrixF _mLeft, MatrixF _mRight) {
	_mLeft[0] = _mLeft[0] - _mRight[0];
	_mLeft[1] = _mLeft[1] - _mRight[1];
	_mLeft[2] = _mLeft[2] - _mRight[2];
	_mLeft[3] = _mLeft[3] - _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixF operator*(MatrixF _mLeft, float _fRight) {
	_mLeft[0] *= _fRight;
	_mLeft[1] *= _fRight;
	_mLeft[2] *= _fRight;
	_mLeft[3] *= _fRight;

	return _mLeft;
}
HC_INLINE MatrixF operator*(float _fLeft, MatrixF _mRight) {
	_mRight[0] *= _fLeft;
	_mRight[1] *= _fLeft;
	_mRight[2] *= _fLeft;
	_mRight[3] *= _fLeft;

	return _mRight;
}
HC_INLINE MatrixF operator*(MatrixF _mLeft, MatrixF _mRight) {
	_mRight = Transpose(_mRight);

	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		_mLeft[iNdx] = Vec4F(Dot(_mLeft[iNdx], _mRight[0]),
							 Dot(_mLeft[iNdx], _mRight[1]),
							 Dot(_mLeft[iNdx], _mRight[2]),
							 Dot(_mLeft[iNdx], _mRight[3]));
	}

	return _mLeft;
}
HC_INLINE Vec4F operator*(MatrixF _mLeft, Vec4F _vRight) {	
	_vRight = Vec4F(Dot(_mLeft[0], _vRight),
					Dot(_mLeft[1], _vRight),
					Dot(_mLeft[2], _vRight),
					Dot(_mLeft[3], _vRight));

	return _vRight;
}
HC_INLINE Vec4F operator*(Vec4F _vLeft, MatrixF _mRight) {
	_vLeft = Vec4F(Dot(_vLeft, _mRight[0]),
				   Dot(_vLeft, _mRight[1]),
				   Dot(_vLeft, _mRight[2]),
				   Dot(_vLeft, _mRight[3]));

	return _vLeft;
}
HC_INLINE MatrixF operator/(MatrixF _mLeft, float _fRight) {
	_mLeft[0] /= _fRight;
	_mLeft[1] /= _fRight;
	_mLeft[2] /= _fRight;
	_mLeft[3] /= _fRight;

	return _mLeft;
}
HC_INLINE MatrixF operator/(float _fLeft, MatrixF _mRight) {
	_mRight[0] /= _fLeft;
	_mRight[1] /= _fLeft;
	_mRight[2] /= _fLeft;
	_mRight[3] /= _fLeft;

	return _mRight;
}
HC_INLINE MatrixF& operator+=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft + _mRight; return _mLeft; }
HC_INLINE MatrixF& operator-=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft - _mRight; return _mLeft; }
HC_INLINE MatrixF& operator*=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft * _fRight; return _mLeft; }
HC_INLINE MatrixF& operator*=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft * _mRight; return _mLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, MatrixF _mRight) { _vLeft = _vLeft * _mRight; return _vLeft; }
HC_INLINE MatrixF& operator/=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft / _fRight; return _mLeft; }
HC_INLINE MatrixF operator~(MatrixF _mMat) { return MatrixF(); }
HC_INLINE MatrixF operator-(MatrixF _mMat) { return MatrixF() - _mMat; }