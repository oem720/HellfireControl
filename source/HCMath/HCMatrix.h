
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
HC_INLINE MatrixF Identity() {
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
HC_INLINE MatrixF RotationXDeg(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fDeg), sinf(_fDeg), 0.0f);
	mMat[2] = Vec4F(0.0f, -sinf(_fDeg), cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);
	
	return mMat;
}
HC_INLINE MatrixF RotationXRad(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fRad), -sinf(_fRad), 0.0f);
	mMat[2] = Vec4F(0.0f, sinf(_fRad), cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYDeg(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), 0.0f, sinf(_fDeg), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fDeg), 0.0f, cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYRad(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), 0.0f, sinf(_fRad), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fRad), 0.0f, cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationZDeg(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), -sinf(_fDeg), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fDeg), cosf(_fDeg), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationZRad(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), -sinf(_fRad), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fRad), cosf(_fRad), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationYawPitchRollDeg(Vec4F _vRotation) {
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
HC_INLINE MatrixF RotationYawPitchRollRad(Vec4F _vRotation) {
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
HC_INLINE MatrixF TranslationX(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(_fDist, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationY(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF TranslationZ(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF Translation(Vec4F _vTranslation) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF RotationTranslationDeg(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollDeg(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF RotationTranslationRad(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollRad(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF ScaleX(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_fScale, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);
	
	return mMat;
}
HC_INLINE MatrixF ScaleY(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _fScale, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF ScaleZ(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fScale, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF ScaleXYZ(Vec4F _vScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_vScale.X(), 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _vScale.Y(), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _vScale.Z(), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF RotationTranslationScaleDeg(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollDeg(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZ(_vScale);

	return mMat;
}
HC_INLINE MatrixF RotationTranslationScaleRad(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollRad(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZ(_vScale);

	return mMat;
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
HC_INLINE MatrixF TranslateXLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationX(_fDist); }
HC_INLINE MatrixF TranslateXGlobal(float _fDist, MatrixF _mMat) { return TranslationX(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateYLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationY(_fDist); }
HC_INLINE MatrixF TranslateYGlobal(float _fDist, MatrixF _mMat) { return TranslationY(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateZLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationZ(_fDist); }
HC_INLINE MatrixF TranslateZGlobal(float _fDist, MatrixF _mMat) { return TranslationZ(_fDist) * _mMat; }
HC_INLINE MatrixF TranslateLocal(Vec4F _vTranslation, MatrixF _mMat) { return _mMat * Translation(_vTranslation); }
HC_INLINE MatrixF TranslateGlobal(Vec4F _vTranslation, MatrixF _mMat) { return Translation(_vTranslation) * _mMat; }
HC_INLINE MatrixF RotateXLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationXDeg(_fDeg); }
HC_INLINE MatrixF RotateXLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationXRad(_fRad); }
HC_INLINE MatrixF RotateXGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationXDeg(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateXGlobalRad(float _fDeg, MatrixF _mMat) { return RotationXRad(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateYLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationYDeg(_fDeg); }
HC_INLINE MatrixF RotateYLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationYRad(_fRad); }
HC_INLINE MatrixF RotateYGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationYDeg(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateYGlobalRad(float _fDeg, MatrixF _mMat) { return RotationYDeg(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateZLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationZDeg(_fDeg); }
HC_INLINE MatrixF RotateZLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationZRad(_fRad); }
HC_INLINE MatrixF RotateZGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationZDeg(_fDeg) * _mMat; }
HC_INLINE MatrixF RotateZGlobalRad(float _fRad, MatrixF _mMat) { return RotationZRad(_fRad) * _mMat; }
HC_INLINE MatrixF RotateYawPitchRollLocalDeg(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollDeg(_vRotation); }
HC_INLINE MatrixF RotateYawPitchRollLocalRad(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollRad(_vRotation); }
HC_INLINE MatrixF RotateYawPitchRollGlobalDeg(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollDeg(_vRotation) * _mMat; }
HC_INLINE MatrixF RotateYawPitchRollGlobalRad(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollRad(_vRotation) * _mMat; }

