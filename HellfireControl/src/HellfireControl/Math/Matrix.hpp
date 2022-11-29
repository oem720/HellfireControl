#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>

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
	Vec4F dets = (HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 0, 2, 0, 2) * HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 1, 3, 1, 3) -
				 (HC_SHUFFLE4F_2(_mMat[0], _mMat[2], 1, 3, 1, 3) * HC_SHUFFLE4F_2(_mMat[1], _mMat[3], 0, 2, 0, 2)));
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
HC_INLINE MatrixF IdentityF() {
	static MatrixF mMat(Vec4F(1.0f, 0.0f, 0.0f, 0.0f),
						Vec4F(0.0f, 1.0f, 0.0f, 0.0f),
						Vec4F(0.0f, 0.0f, 1.0f, 0.0f),
						Vec4F(0.0f, 0.0f, 0.0f, 1.0f));
	return mMat;
}
HC_INLINE MatrixF ProjectionF(float _fAspectRatio, float _fFOV, float _fNearPlane, float _fFarPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fNearPlane / (_fFarPlane - _fNearPlane), -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, (_fNearPlane * _fFarPlane) / (_fFarPlane - _fNearPlane), 0.0f);

	return mMat;
}
HC_INLINE MatrixF ProjectionFReversedInf(float _fAspectRatio, float _fFOV, float _fNearPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 0.0f, -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, _fNearPlane, 0.0f);

	return mMat;
}
HC_INLINE MatrixF LookAtLH(Vec4F _vEye, Vec4F _vAt, Vec4F _vUp) {
	Vec4F vZAxis = Normalize(_vAt - _vEye);
	Vec4F vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4F vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixF(vXAxis, vYAxis, vZAxis, _vAt);
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
HC_INLINE MatrixF RotationXDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fDeg), sinf(_fDeg), 0.0f);
	mMat[2] = Vec4F(0.0f, -sinf(_fDeg), cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationXRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fRad), -sinf(_fRad), 0.0f);
	mMat[2] = Vec4F(0.0f, sinf(_fRad), cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), 0.0f, sinf(_fDeg), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fDeg), 0.0f, cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), 0.0f, sinf(_fRad), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fRad), 0.0f, cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationZDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), -sinf(_fDeg), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fDeg), cosf(_fDeg), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationZRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), -sinf(_fRad), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fRad), cosf(_fRad), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYawPitchRollDegF(Vec4F _vRotation) {
	float fYaw = HC_DEG2RAD(_vRotation.X());
	float fPitch = HC_DEG2RAD(_vRotation.Y());
	float fRoll = HC_DEG2RAD(_vRotation.Z());

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(fYaw) * cosf(fPitch), (cosf(fYaw) * sinf(fPitch) * sinf(fRoll)) - (sinf(fYaw) * cosf(fRoll)), (cosf(fYaw) * sinf(fPitch) * cosf(fRoll)) + (sinf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[1] = Vec4F(sinf(fYaw) * cosf(fPitch), (sinf(fYaw) * sinf(fPitch) * sinf(fRoll)) + (cosf(fYaw) * cosf(fRoll)), (sinf(fYaw) * sinf(fPitch) * cosf(fRoll)) - (cosf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[2] = Vec4F(-sinf(fPitch), cosf(fPitch) * sinf(fRoll), cosf(fPitch) * cosf(fRoll), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYawPitchRollRadF(Vec4F _vRotation) {
	float fYaw = _vRotation.X();
	float fPitch = _vRotation.Y();
	float fRoll = _vRotation.Z();

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(fYaw) * cosf(fPitch), (cosf(fYaw) * sinf(fPitch) * sinf(fRoll)) - (sinf(fYaw) * cosf(fRoll)), (cosf(fYaw) * sinf(fPitch) * cosf(fRoll)) + (sinf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[1] = Vec4F(sinf(fYaw) * cosf(fPitch), (sinf(fYaw) * sinf(fPitch) * sinf(fRoll)) + (cosf(fYaw) * cosf(fRoll)), (sinf(fYaw) * sinf(fPitch) * cosf(fRoll)) - (cosf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[2] = Vec4F(-sinf(fPitch), cosf(fPitch) * sinf(fRoll), cosf(fPitch) * cosf(fRoll), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationXF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(_fDist, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationYF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationZF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationF(Vec4F _vTranslation) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF RotationTranslationDegF(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF RotationTranslationRadF(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF ScaleXF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_fScale, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF ScaleYF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _fScale, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF ScaleZF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fScale, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF ScaleXYZF(Vec4F _vScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_vScale.X(), 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _vScale.Y(), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _vScale.Z(), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationTranslationScaleDegF(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}
HC_INLINE MatrixF RotationTranslationScaleRadF(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}
HC_INLINE MatrixF TranslateXLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationXF(_fDist); }
HC_INLINE MatrixF TranslateXGlobal(float _fDist, MatrixF _mMat) { return TranslationXF(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateYLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationYF(_fDist); }
HC_INLINE MatrixF TranslateYGlobal(float _fDist, MatrixF _mMat) { return TranslationYF(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateZLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationZF(_fDist); }
HC_INLINE MatrixF TranslateZGlobal(float _fDist, MatrixF _mMat) { return TranslationZF(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateLocal(Vec4F _vTranslation, MatrixF _mMat) { return _mMat * TranslationF(_vTranslation); }
HC_INLINE MatrixF TranslateGlobal(Vec4F _vTranslation, MatrixF _mMat) { return TranslationF(_vTranslation) * _mMat; }
HC_INLINE MatrixF RotateXLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationXDegF(_fDeg); }
HC_INLINE MatrixF RotateXLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationXRadF(_fRad); }
HC_INLINE MatrixF RotateXGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationXDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateXGlobalRad(float _fDeg, MatrixF _mMat) { return RotationXRadF(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateYLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationYDegF(_fDeg); }
HC_INLINE MatrixF RotateYLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationYRadF(_fRad); }
HC_INLINE MatrixF RotateYGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationYDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateYGlobalRad(float _fDeg, MatrixF _mMat) { return RotationYDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateZLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationZDegF(_fDeg); }
HC_INLINE MatrixF RotateZLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationZRadF(_fRad); }
HC_INLINE MatrixF RotateZGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationZDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateZGlobalRad(float _fRad, MatrixF _mMat) { return RotationZRadF(_fRad) * _mMat; }
HC_INLINE MatrixF RotateYawPitchRollLocalDeg(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollDegF(_vRotation); }
HC_INLINE MatrixF RotateYawPitchRollLocalRad(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollRadF(_vRotation); }
HC_INLINE MatrixF RotateYawPitchRollGlobalDeg(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollDegF(_vRotation) * _mMat; }
HC_INLINE MatrixF RotateYawPitchRollGlobalRad(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollRadF(_vRotation) * _mMat; }

HC_INLINE MatrixD Transpose(MatrixD _mMat) {
	__m256d temp0 = _mm256_unpacklo_pd(_mMat[0].m_dVec, _mMat[2].m_dVec);
	__m256d temp1 = _mm256_unpacklo_pd(_mMat[1].m_dVec, _mMat[3].m_dVec);
	__m256d temp2 = _mm256_unpackhi_pd(_mMat[0].m_dVec, _mMat[2].m_dVec);
	__m256d temp3 = _mm256_unpackhi_pd(_mMat[1].m_dVec, _mMat[3].m_dVec);

	_mMat[0] = Vec4D(_mm256_unpacklo_pd(temp0, temp1));
	_mMat[1] = Vec4D(_mm256_unpackhi_pd(temp0, temp1));
	_mMat[2] = Vec4D(_mm256_unpacklo_pd(temp2, temp3));
	_mMat[3] = Vec4D(_mm256_unpackhi_pd(temp2, temp3));
	
	return _mMat;
}
HC_INLINE double Determinant(MatrixD _mMat) {
	//Sub matrices
	Vec4D A = Vec4D(_mMat[0][0], _mMat[0][1], _mMat[1][0], _mMat[1][1]);
	Vec4D B = Vec4D(_mMat[0][2], _mMat[0][3], _mMat[1][2], _mMat[1][3]);
	Vec4D C = Vec4D(_mMat[2][0], _mMat[2][1], _mMat[3][0], _mMat[3][1]);
	Vec4D D = Vec4D(_mMat[2][2], _mMat[2][3], _mMat[3][2], _mMat[3][3]);

	//Determinants
	Vec4D dets = Vec4D((HC_SHUFFLE4D_2(_mMat[0], _mMat[2], 0, 2, 0, 2) * HC_SHUFFLE4D_2(_mMat[1], _mMat[3], 1, 3, 1, 3)) -
					   (HC_SHUFFLE4D_2(_mMat[0], _mMat[2], 1, 3, 1, 3) * HC_SHUFFLE4D_2(_mMat[1], _mMat[3], 0, 2, 0, 2)));
	double detA = dets.X();
	double detB = dets.Y();
	double detC = dets.Z();
	double detD = dets.W();
	//D adjmul C
	Vec4D DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4D AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());

	return ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
}
HC_INLINE MatrixD Inverse(MatrixD _mMat) {

	//Sub matrices
	Vec4D A = Vec4D(_mMat[0][0], _mMat[0][1], _mMat[1][0], _mMat[1][1]);
	Vec4D B = Vec4D(_mMat[0][2], _mMat[0][3], _mMat[1][2], _mMat[1][3]);
	Vec4D C = Vec4D(_mMat[2][0], _mMat[2][1], _mMat[3][0], _mMat[3][1]);
	Vec4D D = Vec4D(_mMat[2][2], _mMat[2][3], _mMat[3][2], _mMat[3][3]);

	//Determinants
	Vec4D dets = (HC_SHUFFLE4D_2(_mMat[0], _mMat[2], 0, 2, 0, 2) * HC_SHUFFLE4D_2(_mMat[1], _mMat[3], 1, 3, 1, 3) -
				 (HC_SHUFFLE4D_2(_mMat[0], _mMat[2], 1, 3, 1, 3) * HC_SHUFFLE4D_2(_mMat[1], _mMat[3], 0, 2, 0, 2)));
	double detA = dets.X();
	double detB = dets.Y();
	double detC = dets.Z();
	double detD = dets.W();

	//D adjmul C
	Vec4D DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4D AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());
	//DetM
	double detM = ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
	//No inverse, return 0
	if (detM == 0.0) { return MatrixD(); }
	//Reciprocal
	Vec4D vDet = Vec4D(1.0, -1.0, -1.0, 1.0) / detM;

	//X Row
	Vec4D X = ((A * detD) - ((B * DC.XWXW()) + (B.YXWZ() * DC.ZYZY()))) * vDet;
	//W Row
	Vec4D W = ((D * detA) - ((C * AB.XWXW()) + (C.YXWZ() * AB.ZYZY()))) * vDet;
	//Y Row
	Vec4D Y = ((C * detB) - ((D * AB.WXWX()) - (D.YXWZ() * AB.ZYZY()))) * vDet;
	//Z Row
	Vec4D Z = ((B * detC) - ((A * DC.WXWX()) - (A.YXWZ() * DC.ZYZY()))) * vDet;

	_mMat[0] = HC_SHUFFLE4D_2(X, Y, 3, 1, 3, 1);
	_mMat[1] = HC_SHUFFLE4D_2(X, Y, 2, 0, 2, 0);
	_mMat[2] = HC_SHUFFLE4D_2(Z, W, 3, 1, 3, 1);
	_mMat[3] = HC_SHUFFLE4D_2(Z, W, 2, 0, 2, 0);

	return _mMat;
}
HC_INLINE MatrixD IdentityD() {
	static MatrixD mMat(Vec4D(1.0, 0.0, 0.0, 0.0),
						Vec4D(0.0, 1.0, 0.0, 0.0),
						Vec4D(0.0, 0.0, 1.0, 0.0),
						Vec4D(0.0, 0.0, 0.0, 1.0));
	return mMat;
}
HC_INLINE MatrixD ProjectionD(double _fAspectRatio, double _fDOV, double _fNearPlane, double _fDarPlane) {
	double fDocal = 1.0 / tan(_fDOV);
	MatrixD mMat;
	mMat[0] = Vec4D(fDocal / _fAspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -fDocal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _fNearPlane / (_fDarPlane - _fNearPlane), -1.0);
	mMat[3] = Vec4D(0.0, 0.0, (_fNearPlane * _fDarPlane) / (_fDarPlane - _fNearPlane), 0.0);

	return mMat;
}
HC_INLINE MatrixD ProjectionDReversedInf(double _fAspectRatio, double _fDOV, double _fNearPlane) {
	double fDocal = 1.0 / tan(_fDOV);
	MatrixD mMat;
	mMat[0] = Vec4D(fDocal / _fAspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -fDocal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 0.0, -1.0);
	mMat[3] = Vec4D(0.0, 0.0, _fNearPlane, 0.0);

	return mMat;
}
HC_INLINE MatrixD LookAtLH(Vec4D _vEye, Vec4D _vAt, Vec4D _vUp) {
	Vec4D vZAxis = Normalize(_vAt - _vEye);
	Vec4D vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4D vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixD(vXAxis, vYAxis, vZAxis, _vAt);
}
HC_INLINE MatrixD operator+(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] + _mRight[0];
	_mLeft[1] = _mLeft[1] + _mRight[1];
	_mLeft[2] = _mLeft[2] + _mRight[2];
	_mLeft[3] = _mLeft[3] + _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixD operator-(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] - _mRight[0];
	_mLeft[1] = _mLeft[1] - _mRight[1];
	_mLeft[2] = _mLeft[2] - _mRight[2];
	_mLeft[3] = _mLeft[3] - _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixD operator*(MatrixD _mLeft, double _fRight) {
	_mLeft[0] *= _fRight;
	_mLeft[1] *= _fRight;
	_mLeft[2] *= _fRight;
	_mLeft[3] *= _fRight;

	return _mLeft;
}
HC_INLINE MatrixD operator*(double _fLeft, MatrixD _mRight) {
	_mRight[0] *= _fLeft;
	_mRight[1] *= _fLeft;
	_mRight[2] *= _fLeft;
	_mRight[3] *= _fLeft;

	return _mRight;
}
HC_INLINE MatrixD operator*(MatrixD _mLeft, MatrixD _mRight) {
	_mRight = Transpose(_mRight);

	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		_mLeft[iNdx] = Vec4D(Dot(_mLeft[iNdx], _mRight[0]),
							 Dot(_mLeft[iNdx], _mRight[1]),
							 Dot(_mLeft[iNdx], _mRight[2]),
							 Dot(_mLeft[iNdx], _mRight[3]));
	}

	return _mLeft;
}
HC_INLINE Vec4D operator*(MatrixD _mLeft, Vec4D _vRight) {
	_vRight = Vec4D(Dot(_mLeft[0], _vRight),
					Dot(_mLeft[1], _vRight),
					Dot(_mLeft[2], _vRight),
					Dot(_mLeft[3], _vRight));

	return _vRight;
}
HC_INLINE Vec4D operator*(Vec4D _vLeft, MatrixD _mRight) {
	_vLeft = Vec4D(Dot(_vLeft, _mRight[0]),
				   Dot(_vLeft, _mRight[1]),
				   Dot(_vLeft, _mRight[2]),
				   Dot(_vLeft, _mRight[3]));

	return _vLeft;
}
HC_INLINE MatrixD operator/(MatrixD _mLeft, double _fRight) {
	_mLeft[0] /= _fRight;
	_mLeft[1] /= _fRight;
	_mLeft[2] /= _fRight;
	_mLeft[3] /= _fRight;

	return _mLeft;
}
HC_INLINE MatrixD operator/(double _fLeft, MatrixD _mRight) {
	_mRight[0] /= _fLeft;
	_mRight[1] /= _fLeft;
	_mRight[2] /= _fLeft;
	_mRight[3] /= _fLeft;

	return _mRight;
}
HC_INLINE MatrixD& operator+=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft + _mRight; return _mLeft; }
HC_INLINE MatrixD& operator-=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft - _mRight; return _mLeft; }
HC_INLINE MatrixD& operator*=(MatrixD& _mLeft, double _fRight) { _mLeft = _mLeft * _fRight; return _mLeft; }
HC_INLINE MatrixD& operator*=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft * _mRight; return _mLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, MatrixD _mRight) { _vLeft = _vLeft * _mRight; return _vLeft; }
HC_INLINE MatrixD& operator/=(MatrixD& _mLeft, double _fRight) { _mLeft = _mLeft / _fRight; return _mLeft; }
HC_INLINE MatrixD operator~(MatrixD _mMat) { return MatrixD(); }
HC_INLINE MatrixD operator-(MatrixD _mMat) { return MatrixD() - _mMat; }
HC_INLINE MatrixD RotationXDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_fDeg), sin(_fDeg), 0.0);
	mMat[2] = Vec4D(0.0, -sin(_fDeg), cos(_fDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationXRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_fRad), -sin(_fRad), 0.0);
	mMat[2] = Vec4D(0.0, sin(_fRad), cos(_fRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationYDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fDeg), 0.0, sin(_fDeg), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_fDeg), 0.0, cos(_fDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationYRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fRad), 0.0, sin(_fRad), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_fRad), 0.0, cos(_fRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationZDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fDeg), -sin(_fDeg), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_fDeg), cos(_fDeg), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationZRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fRad), -sin(_fRad), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_fRad), cos(_fRad), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationYawPitchRollDegD(Vec4D _vRotation) {
	double fYaw = HC_DEG2RAD(_vRotation.X());
	double fPitch = HC_DEG2RAD(_vRotation.Y());
	double fRoll = HC_DEG2RAD(_vRotation.Z());

	MatrixD mMat;
	mMat[0] = Vec4D(cos(fYaw) * cos(fPitch), (cos(fYaw) * sin(fPitch) * sin(fRoll)) - (sin(fYaw) * cos(fRoll)), (cos(fYaw) * sin(fPitch) * cos(fRoll)) + (sin(fYaw) * sin(fRoll)), 0.0);
	mMat[1] = Vec4D(sin(fYaw) * cos(fPitch), (sin(fYaw) * sin(fPitch) * sin(fRoll)) + (cos(fYaw) * cos(fRoll)), (sin(fYaw) * sin(fPitch) * cos(fRoll)) - (cos(fYaw) * sin(fRoll)), 0.0);
	mMat[2] = Vec4D(-sin(fPitch), cos(fPitch) * sin(fRoll), cos(fPitch) * cos(fRoll), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationYawPitchRollRadD(Vec4D _vRotation) {
	double fYaw = _vRotation.X();
	double fPitch = _vRotation.Y();
	double fRoll = _vRotation.Z();

	MatrixD mMat;
	mMat[0] = Vec4D(cos(fYaw) * cos(fPitch), (cos(fYaw) * sin(fPitch) * sin(fRoll)) - (sin(fYaw) * cos(fRoll)), (cos(fYaw) * sin(fPitch) * cos(fRoll)) + (sin(fYaw) * sin(fRoll)), 0.0);
	mMat[1] = Vec4D(sin(fYaw) * cos(fPitch), (sin(fYaw) * sin(fPitch) * sin(fRoll)) + (cos(fYaw) * cos(fRoll)), (sin(fYaw) * sin(fPitch) * cos(fRoll)) - (cos(fYaw) * sin(fRoll)), 0.0);
	mMat[2] = Vec4D(-sin(fPitch), cos(fPitch) * sin(fRoll), cos(fPitch) * cos(fRoll), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD TranslationXD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(_fDist, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD TranslationYD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _fDist, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD TranslationZD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _fDist, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD TranslationD(Vec4D _vTranslation) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD RotationTranslationDegD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD RotationTranslationRadD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD ScaleXD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_fScale, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD ScaleYD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _fScale, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD ScaleZD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _fScale, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD ScaleXYZD(Vec4D _vScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_vScale.X(), 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _vScale.Y(), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _vScale.Z(), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD RotationTranslationScaleDegD(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}
HC_INLINE MatrixD RotationTranslationScaleRadD(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}
HC_INLINE MatrixD TranslateXLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationXD(_fDist); }
HC_INLINE MatrixD TranslateXGlobal(double _fDist, MatrixD _mMat) { return TranslationXD(_fDist) * _mMat; }
HC_INLINE MatrixD TranslateYLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationYD(_fDist); }
HC_INLINE MatrixD TranslateYGlobal(double _fDist, MatrixD _mMat) { return TranslationYD(_fDist) * _mMat; }
HC_INLINE MatrixD TranslateZLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationZD(_fDist); }
HC_INLINE MatrixD TranslateZGlobal(double _fDist, MatrixD _mMat) { return TranslationZD(_fDist) * _mMat; }
HC_INLINE MatrixD TranslateLocal(Vec4D _vTranslation, MatrixD _mMat) { return _mMat * TranslationD(_vTranslation); }
HC_INLINE MatrixD TranslateGlobal(Vec4D _vTranslation, MatrixD _mMat) { return TranslationD(_vTranslation) * _mMat; }
HC_INLINE MatrixD RotateXLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationXDegD(_fDeg); }
HC_INLINE MatrixD RotateXLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationXRadD(_fRad); }
HC_INLINE MatrixD RotateXGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationXDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD RotateXGlobalRad(double _fDeg, MatrixD _mMat) { return RotationXRadD(_fDeg) * _mMat; }
HC_INLINE MatrixD RotateYLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationYDegD(_fDeg); }
HC_INLINE MatrixD RotateYLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationYRadD(_fRad); }
HC_INLINE MatrixD RotateYGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationYDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD RotateYGlobalRad(double _fDeg, MatrixD _mMat) { return RotationYDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD RotateZLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationZDegD(_fDeg); }
HC_INLINE MatrixD RotateZLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationZRadD(_fRad); }
HC_INLINE MatrixD RotateZGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationZDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD RotateZGlobalRad(double _fRad, MatrixD _mMat) { return RotationZRadD(_fRad) * _mMat; }
HC_INLINE MatrixD RotateYawPitchRollLocalDeg(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollDegD(_vRotation); }
HC_INLINE MatrixD RotateYawPitchRollLocalRad(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollRadD(_vRotation); }
HC_INLINE MatrixD RotateYawPitchRollGlobalDeg(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollDegD(_vRotation) * _mMat; }
HC_INLINE MatrixD RotateYawPitchRollGlobalRad(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollRadD(_vRotation) * _mMat; }