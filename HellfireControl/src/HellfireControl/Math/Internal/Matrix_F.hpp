#pragma once

#include <HellfireControl/Math/Internal/Matrix_Common.hpp>

#if HC_USE_SIMD

struct MatrixF {
	Vec4F m_vRows[4];

	HC_INLINE HC_VECTORCALL MatrixF() {};
	HC_INLINE explicit HC_VECTORCALL MatrixF(Vec4F _vRow1, Vec4F _vRow2, Vec4F _vRow3, Vec4F _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE explicit HC_VECTORCALL MatrixF(Vec4F* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }
	HC_INLINE Vec4F HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4F& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4F HC_VECTORCALL Row1() { return m_vRows[0]; }
	HC_INLINE Vec4F HC_VECTORCALL Row2() { return m_vRows[1]; }
	HC_INLINE Vec4F HC_VECTORCALL Row3() { return m_vRows[2]; }
	HC_INLINE Vec4F HC_VECTORCALL Row4() { return m_vRows[3]; }
	HC_INLINE void HC_VECTORCALL SetRow1(Vec4F _vRow) { m_vRows[0] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow2(Vec4F _vRow) { m_vRows[1] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow3(Vec4F _vRow) { m_vRows[2] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow4(Vec4F _vRow) { m_vRows[3] = _vRow; }
};

HC_INLINE MatrixF HC_VECTORCALL Transpose(const MatrixF& _mMat) {
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
HC_INLINE float HC_VECTORCALL Determinant(const MatrixF& _mMat) {
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
HC_INLINE MatrixF HC_VECTORCALL Inverse(const MatrixF& _mMat) {

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
HC_INLINE MatrixF HC_VECTORCALL IdentityF() {
	static MatrixF mMat(Vec4F(1.0f, 0.0f, 0.0f, 0.0f),
		Vec4F(0.0f, 1.0f, 0.0f, 0.0f),
		Vec4F(0.0f, 0.0f, 1.0f, 0.0f),
		Vec4F(0.0f, 0.0f, 0.0f, 1.0f));
	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ProjectionF(float _fAspectRatio, float _fFOV, float _fNearPlane, float _fFarPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fNearPlane / (_fFarPlane - _fNearPlane), -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, (_fNearPlane * _fFarPlane) / (_fFarPlane - _fNearPlane), 0.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ProjectionFReversedInf(float _fAspectRatio, float _fFOV, float _fNearPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 0.0f, -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, _fNearPlane, 0.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL LookAtLH(Vec4F _vEye, Vec4F _vAt, Vec4F _vUp) {
	Vec4F vZAxis = Normalize(_vAt - _vEye);
	Vec4F vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4F vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixF(vXAxis, vYAxis, vZAxis, _vAt);
}
HC_INLINE MatrixF HC_VECTORCALL operator+(const MatrixF& _mLeft, const MatrixF& _mRight) {
	_mLeft[0] = _mLeft[0] + _mRight[0];
	_mLeft[1] = _mLeft[1] + _mRight[1];
	_mLeft[2] = _mLeft[2] + _mRight[2];
	_mLeft[3] = _mLeft[3] + _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixF HC_VECTORCALL operator-(const MatrixF& _mLeft, const MatrixF& _mRight) {
	_mLeft[0] = _mLeft[0] - _mRight[0];
	_mLeft[1] = _mLeft[1] - _mRight[1];
	_mLeft[2] = _mLeft[2] - _mRight[2];
	_mLeft[3] = _mLeft[3] - _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixF HC_VECTORCALL operator*(const MatrixF& _mLeft, float _fRight) {
	_mLeft[0] *= _fRight;
	_mLeft[1] *= _fRight;
	_mLeft[2] *= _fRight;
	_mLeft[3] *= _fRight;

	return _mLeft;
}
HC_INLINE MatrixF HC_VECTORCALL operator*(float _fLeft, const MatrixF& _mRight) {
	_mRight[0] *= _fLeft;
	_mRight[1] *= _fLeft;
	_mRight[2] *= _fLeft;
	_mRight[3] *= _fLeft;

	return _mRight;
}
HC_INLINE MatrixF HC_VECTORCALL operator*(const MatrixF& _mLeft, const MatrixF& _mRight) {
	_mRight = Transpose(_mRight);

	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		_mLeft[iNdx] = Vec4F(Dot(_mLeft[iNdx], _mRight[0]),
			Dot(_mLeft[iNdx], _mRight[1]),
			Dot(_mLeft[iNdx], _mRight[2]),
			Dot(_mLeft[iNdx], _mRight[3]));
	}

	return _mLeft;
}
HC_INLINE Vec4F HC_VECTORCALL operator*(const MatrixF& _mLeft, const Vec4F& _vRight) {
	_vRight = Vec4F(Dot(_mLeft[0], _vRight),
		Dot(_mLeft[1], _vRight),
		Dot(_mLeft[2], _vRight),
		Dot(_mLeft[3], _vRight));

	return _vRight;
}
HC_INLINE Vec4F HC_VECTORCALL operator*(const Vec4F& _vLeft, const MatrixF& _mRight) {
	_vLeft = Vec4F(Dot(_vLeft, _mRight[0]),
		Dot(_vLeft, _mRight[1]),
		Dot(_vLeft, _mRight[2]),
		Dot(_vLeft, _mRight[3]));

	return _vLeft;
}
HC_INLINE MatrixF HC_VECTORCALL operator/(const MatrixF& _mLeft, float _fRight) {
	_mLeft[0] /= _fRight;
	_mLeft[1] /= _fRight;
	_mLeft[2] /= _fRight;
	_mLeft[3] /= _fRight;

	return _mLeft;
}
HC_INLINE MatrixF HC_VECTORCALL operator/(float _fLeft, const MatrixF& _mRight) {
	_mRight[0] /= _fLeft;
	_mRight[1] /= _fLeft;
	_mRight[2] /= _fLeft;
	_mRight[3] /= _fLeft;

	return _mRight;
}
HC_INLINE MatrixF& HC_VECTORCALL operator+=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft + _mRight; return _mLeft; }
HC_INLINE MatrixF& HC_VECTORCALL operator-=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft - _mRight; return _mLeft; }
HC_INLINE MatrixF& HC_VECTORCALL operator*=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft * _fRight; return _mLeft; }
HC_INLINE MatrixF& HC_VECTORCALL operator*=(MatrixF& _mLeft, MatrixF _mRight) { _mLeft = _mLeft * _mRight; return _mLeft; }
HC_INLINE Vec4F& HC_VECTORCALL operator*=(Vec4F& _vLeft, MatrixF _mRight) { _vLeft = _vLeft * _mRight; return _vLeft; }
HC_INLINE MatrixF& HC_VECTORCALL operator/=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft / _fRight; return _mLeft; }
HC_INLINE MatrixF HC_VECTORCALL operator~(MatrixF _mMat) { return MatrixF(); }
HC_INLINE MatrixF HC_VECTORCALL operator-(MatrixF _mMat) { return MatrixF() - _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotationXDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fDeg), sinf(_fDeg), 0.0f);
	mMat[2] = Vec4F(0.0f, -sinf(_fDeg), cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationXRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fRad), -sinf(_fRad), 0.0f);
	mMat[2] = Vec4F(0.0f, sinf(_fRad), cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationYDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), 0.0f, sinf(_fDeg), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fDeg), 0.0f, cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationYRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), 0.0f, sinf(_fRad), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fRad), 0.0f, cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationZDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), -sinf(_fDeg), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fDeg), cosf(_fDeg), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationZRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), -sinf(_fRad), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fRad), cosf(_fRad), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationYawPitchRollDegF(Vec4F _vRotation) {
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
HC_INLINE MatrixF HC_VECTORCALL RotationYawPitchRollRadF(Vec4F _vRotation) {
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
HC_INLINE MatrixF HC_VECTORCALL TranslationXF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(_fDist, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL TranslationYF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL TranslationZF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL TranslationF(Vec4F _vTranslation) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationTranslationDegF(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationTranslationRadF(Vec4F _vRotation, Vec4F _vTranslation) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ScaleXF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_fScale, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ScaleYF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _fScale, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ScaleZF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fScale, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL ScaleXYZF(Vec4F _vScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_vScale.X(), 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _vScale.Y(), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _vScale.Z(), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationTranslationScaleDegF(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL RotationTranslationScaleRadF(Vec4F _vRotation, Vec4F _vTranslation, Vec4F _vScale) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}
HC_INLINE MatrixF HC_VECTORCALL TranslateXLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationXF(_fDist); }
HC_INLINE MatrixF HC_VECTORCALL TranslateXGlobal(float _fDist, MatrixF _mMat) { return TranslationXF(_fDist) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL TranslateYLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationYF(_fDist); }
HC_INLINE MatrixF HC_VECTORCALL TranslateYGlobal(float _fDist, MatrixF _mMat) { return TranslationYF(_fDist) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL TranslateZLocal(float _fDist, MatrixF _mMat) { return _mMat * TranslationZF(_fDist); }
HC_INLINE MatrixF HC_VECTORCALL TranslateZGlobal(float _fDist, MatrixF _mMat) { return TranslationZF(_fDist) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL TranslateLocal(Vec4F _vTranslation, MatrixF _mMat) { return _mMat * TranslationF(_vTranslation); }
HC_INLINE MatrixF HC_VECTORCALL TranslateGlobal(Vec4F _vTranslation, MatrixF _mMat) { return TranslationF(_vTranslation) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateXLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationXDegF(_fDeg); }
HC_INLINE MatrixF HC_VECTORCALL RotateXLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationXRadF(_fRad); }
HC_INLINE MatrixF HC_VECTORCALL RotateXGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationXDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateXGlobalRad(float _fDeg, MatrixF _mMat) { return RotationXRadF(_fDeg) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateYLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationYDegF(_fDeg); }
HC_INLINE MatrixF HC_VECTORCALL RotateYLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationYRadF(_fRad); }
HC_INLINE MatrixF HC_VECTORCALL RotateYGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationYDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateYGlobalRad(float _fDeg, MatrixF _mMat) { return RotationYDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateZLocalDeg(float _fDeg, MatrixF _mMat) { return _mMat * RotationZDegF(_fDeg); }
HC_INLINE MatrixF HC_VECTORCALL RotateZLocalRad(float _fRad, MatrixF _mMat) { return _mMat * RotationZRadF(_fRad); }
HC_INLINE MatrixF HC_VECTORCALL RotateZGlobalDeg(float _fDeg, MatrixF _mMat) { return RotationZDegF(_fDeg) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateZGlobalRad(float _fRad, MatrixF _mMat) { return RotationZRadF(_fRad) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateYawPitchRollLocalDeg(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollDegF(_vRotation); }
HC_INLINE MatrixF HC_VECTORCALL RotateYawPitchRollLocalRad(Vec4F _vRotation, MatrixF _mMat) { return _mMat * RotationYawPitchRollRadF(_vRotation); }
HC_INLINE MatrixF HC_VECTORCALL RotateYawPitchRollGlobalDeg(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollDegF(_vRotation) * _mMat; }
HC_INLINE MatrixF HC_VECTORCALL RotateYawPitchRollGlobalRad(Vec4F _vRotation, MatrixF _mMat) { return RotationYawPitchRollRadF(_vRotation) * _mMat; }

#else

struct HC_ALIGNAS(64) MatrixF
{
	union {
		struct {
			Vec4F m_vRow0;
			Vec4F m_vRow1;
			Vec4F m_vRow2;
			Vec4F m_vRow3;
		};

		Vec4F m_vRows[4];
		float m_fM[16];
		float m_fMat[4][4];
	};

	HC_INLINE MatrixF() { m_vRows[0] = Vec4F(); m_vRows[1] = Vec4F(); m_vRows[2] = Vec4F(); m_vRows[3] = Vec4F(); }
	HC_INLINE explicit MatrixF(const Vec4F& _vRow0, const Vec4F& _vRow1, const Vec4F& _vRow2, const Vec4F& _vRow3) { m_vRows[0] = _vRow0; m_vRows[1] = _vRow1; m_vRows[2] = _vRow2; m_vRows[3] = _vRow3; }
	HC_INLINE explicit MatrixF(float _fVal) { m_vRows[0] = Vec4F(_fVal); m_vRows[1] = Vec4F(_fVal); m_vRows[2] = Vec4F(_fVal); m_vRows[3] = Vec4F(_fVal); }
	[[nodiscard]] HC_INLINE Vec4F operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec4F& operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
};

[[nodiscard]] HC_INLINE MatrixF Transpose(const MatrixF& _mMat) {
	return MatrixF(Vec4F(_mMat[0][0], _mMat[1][0], _mMat[2][0], _mMat[3][0]),
				   Vec4F(_mMat[0][1], _mMat[1][1], _mMat[2][1], _mMat[3][1]),
				   Vec4F(_mMat[0][2], _mMat[1][2], _mMat[2][2], _mMat[3][2]),
				   Vec4F(_mMat[0][3], _mMat[1][3], _mMat[2][3], _mMat[3][3]));
}

[[nodiscard]] HC_INLINE float Determinant(const MatrixF& _mMat) {
	//Sub matrices
	Vec4F A = Vec4F(_mMat[0].XY(), _mMat[1].XY());
	Vec4F B = Vec4F(_mMat[0].ZW(), _mMat[1].ZW());
	Vec4F C = Vec4F(_mMat[2].XY(), _mMat[3].XY());
	Vec4F D = Vec4F(_mMat[2].ZW(), _mMat[3].ZW());

	//Determinants
	Vec4F dets = (Vec4F(_mMat[0].XZ(), _mMat[2].XZ()) * Vec4F(_mMat[1].YW(), _mMat[3].YW())) -
				 (Vec4F(_mMat[0].YW(), _mMat[2].YW()) * Vec4F(_mMat[1].XZ(), _mMat[3].XZ()));

	float detA = dets.x;
	float detB = dets.y;
	float detC = dets.z;
	float detD = dets.w;
	//D adjmul C
	Vec4F DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4F AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());

	return ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
}

[[nodiscard]] HC_INLINE MatrixF Inverse(const MatrixF& _mMat) {

	//Sub matrices
	Vec4F A = Vec4F(_mMat[0].XY(), _mMat[1].XY());
	Vec4F B = Vec4F(_mMat[0].ZW(), _mMat[1].ZW());
	Vec4F C = Vec4F(_mMat[2].XY(), _mMat[3].XY());
	Vec4F D = Vec4F(_mMat[2].ZW(), _mMat[3].ZW());

	//Determinants
	Vec4F dets = (Vec4F(_mMat[0].XZ(), _mMat[2].XZ()) * Vec4F(_mMat[1].YW(), _mMat[3].YW())) -
				 (Vec4F(_mMat[0].YW(), _mMat[2].YW()) * Vec4F(_mMat[1].XZ(), _mMat[3].XZ()));
	float detA = dets.x;
	float detB = dets.y;
	float detC = dets.z;
	float detD = dets.w;

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

	_mMat[0] = Vec4F(X.WY(), Y.WY());
	_mMat[1] = Vec4F(X.ZX(), Y.ZX());
	_mMat[2] = Vec4F(Z.WY(), W.WY());
	_mMat[3] = Vec4F(Z.ZX(), W.ZX());

	return _mMat;
}

[[nodiscard]] HC_INLINE MatrixF IdentityF() {
	static MatrixF mMat(Vec4F(1.0f, 0.0f, 0.0f, 0.0f),
						Vec4F(0.0f, 1.0f, 0.0f, 0.0f),
						Vec4F(0.0f, 0.0f, 1.0f, 0.0f),
						Vec4F(0.0f, 0.0f, 0.0f, 1.0f));
	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ProjectionF(float _fAspectRatio, float _fFOV, float _fNearPlane, float _fFarPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fNearPlane / (_fFarPlane - _fNearPlane), -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, (_fNearPlane * _fFarPlane) / (_fFarPlane - _fNearPlane), 0.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ProjectionFReversedInf(float _fAspectRatio, float _fFOV, float _fNearPlane) {
	float fFocal = 1.0f / tanf(_fFOV);
	MatrixF mMat;
	mMat[0] = Vec4F(fFocal / _fAspectRatio, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, -fFocal, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 0.0f, -1.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, _fNearPlane, 0.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF LookAtLH(const Vec4F& _vEye, const Vec4F& _vAt, const Vec4F& _vUp) {
	Vec4F vZAxis = Normalize(_vAt - _vEye);
	Vec4F vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4F vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixF(vXAxis, vYAxis, vZAxis, _vAt);
}

[[nodiscard]] HC_INLINE MatrixF operator+(const MatrixF& _mLeft, const MatrixF& _mRight) {
	return MatrixF(_mLeft[0] + _mRight[0], _mLeft[1] + _mRight[1], _mLeft[2] + _mRight[2], _mLeft[3] + _mRight[3]);
}

[[nodiscard]] HC_INLINE MatrixF operator-(const MatrixF& _mLeft, const MatrixF& _mRight) {
	return MatrixF(_mLeft[0] - _mRight[0], _mLeft[1] - _mRight[1], _mLeft[2] - _mRight[2], _mLeft[3] - _mRight[3]);;
}

[[nodiscard]] HC_INLINE MatrixF operator*(const MatrixF& _mLeft, float _fRight) {
	return MatrixF(_mLeft[0] * _fRight, _mLeft[1] * _fRight, _mLeft[2] * _fRight, _mLeft[3] * _fRight);
}

[[nodiscard]] HC_INLINE MatrixF operator*(float _fLeft, const MatrixF& _mRight) {
	return MatrixF(_mRight[0] * _fLeft, _mRight[1] * _fLeft, _mRight[2] * _fLeft, _mRight[3] * _fLeft);
}

[[nodiscard]] HC_INLINE MatrixF operator*(const MatrixF& _mLeft, const MatrixF& _mRight) {
	MatrixF t = Transpose(_mRight);

	MatrixF res;
	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		res[iNdx] = Vec4F(Dot(_mLeft[iNdx], t[0]),
						  Dot(_mLeft[iNdx], t[1]),
						  Dot(_mLeft[iNdx], t[2]),
						  Dot(_mLeft[iNdx], t[3]));
	}

	return res;
}

[[nodiscard]] HC_INLINE Vec4F operator*(const MatrixF& _mLeft, const Vec4F& _vRight) {
	return Vec4F(Dot(_mLeft[0], _vRight),
				 Dot(_mLeft[1], _vRight),
				 Dot(_mLeft[2], _vRight),
				 Dot(_mLeft[3], _vRight));
}

[[nodiscard]] HC_INLINE Vec4F operator*(const Vec4F& _vLeft, const MatrixF& _mRight) {
	return Vec4F(Dot(_vLeft, _mRight[0]),
				 Dot(_vLeft, _mRight[1]),
				 Dot(_vLeft, _mRight[2]),
				 Dot(_vLeft, _mRight[3]));
}

[[nodiscard]] HC_INLINE MatrixF operator/(const MatrixF& _mLeft, float _fRight) {
	return MatrixF(_mLeft[0] / _fRight, _mLeft[1] / _fRight, _mLeft[2] / _fRight, _mLeft[3] / _fRight);
}

[[nodiscard]] HC_INLINE MatrixF operator/(float _fLeft, const MatrixF& _mRight) {
	return MatrixF(_mRight[0] / _fLeft, _mRight[1] / _fLeft, _mRight[2] / _fLeft, _mRight[3] / _fLeft);
}

HC_INLINE MatrixF& operator+=(MatrixF& _mLeft, const MatrixF& _mRight) { _mLeft = _mLeft + _mRight; return _mLeft; }
HC_INLINE MatrixF& operator-=(MatrixF& _mLeft, const MatrixF& _mRight) { _mLeft = _mLeft - _mRight; return _mLeft; }
HC_INLINE MatrixF& operator*=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft * _fRight; return _mLeft; }
HC_INLINE MatrixF& operator*=(MatrixF& _mLeft, const MatrixF& _mRight) { _mLeft = _mLeft * _mRight; return _mLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, const MatrixF& _mRight) { _vLeft = _vLeft * _mRight; return _vLeft; }
HC_INLINE MatrixF& operator/=(MatrixF& _mLeft, float _fRight) { _mLeft = _mLeft / _fRight; return _mLeft; }
[[nodiscard]] HC_INLINE MatrixF operator~(const MatrixF& _mMat) { return MatrixF(); }
[[nodiscard]] HC_INLINE MatrixF operator-(const MatrixF& _mMat) { return MatrixF(-_mMat[0], -_mMat[1], -_mMat[2], -_mMat[3]); }

[[nodiscard]] HC_INLINE MatrixF RotationXDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fDeg), sinf(_fDeg), 0.0f);
	mMat[2] = Vec4F(0.0f, -sinf(_fDeg), cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationXRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, cosf(_fRad), -sinf(_fRad), 0.0f);
	mMat[2] = Vec4F(0.0f, sinf(_fRad), cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationYDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), 0.0f, sinf(_fDeg), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fDeg), 0.0f, cosf(_fDeg), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationYRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), 0.0f, sinf(_fRad), 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(-sinf(_fRad), 0.0f, cosf(_fRad), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationZDegF(float _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fDeg), -sinf(_fDeg), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fDeg), cosf(_fDeg), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationZRadF(float _fRad) {
	MatrixF mMat;
	mMat[0] = Vec4F(cosf(_fRad), -sinf(_fRad), 0.0f, 0.0f);
	mMat[1] = Vec4F(sinf(_fRad), cosf(_fRad), 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationYawPitchRollDegF(const Vec3F& _vRotation) {
	float fYaw = HC_DEG2RAD(_vRotation.x);
	float fPitch = HC_DEG2RAD(_vRotation.y);
	float fRoll = HC_DEG2RAD(_vRotation.z);

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(fYaw) * cosf(fPitch), (cosf(fYaw) * sinf(fPitch) * sinf(fRoll)) - (sinf(fYaw) * cosf(fRoll)), (cosf(fYaw) * sinf(fPitch) * cosf(fRoll)) + (sinf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[1] = Vec4F(sinf(fYaw) * cosf(fPitch), (sinf(fYaw) * sinf(fPitch) * sinf(fRoll)) + (cosf(fYaw) * cosf(fRoll)), (sinf(fYaw) * sinf(fPitch) * cosf(fRoll)) - (cosf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[2] = Vec4F(-sinf(fPitch), cosf(fPitch) * sinf(fRoll), cosf(fPitch) * cosf(fRoll), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationYawPitchRollRadF(const Vec3F& _vRotation) {
	float fYaw = _vRotation.x;
	float fPitch = _vRotation.y;
	float fRoll = _vRotation.z;

	MatrixF mMat;
	mMat[0] = Vec4F(cosf(fYaw) * cosf(fPitch), (cosf(fYaw) * sinf(fPitch) * sinf(fRoll)) - (sinf(fYaw) * cosf(fRoll)), (cosf(fYaw) * sinf(fPitch) * cosf(fRoll)) + (sinf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[1] = Vec4F(sinf(fYaw) * cosf(fPitch), (sinf(fYaw) * sinf(fPitch) * sinf(fRoll)) + (cosf(fYaw) * cosf(fRoll)), (sinf(fYaw) * sinf(fPitch) * cosf(fRoll)) - (cosf(fYaw) * sinf(fRoll)), 0.0f);
	mMat[2] = Vec4F(-sinf(fPitch), cosf(fPitch) * sinf(fRoll), cosf(fPitch) * cosf(fRoll), 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF TranslationXF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(_fDist, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF TranslationYF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF TranslationZF(float _fDist) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, _fDist, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF TranslationF(const Vec3F& _vTranslation) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(_vTranslation, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationTranslationDegF(const Vec3F& _vRotation, const Vec3F& _vTranslation) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = Vec4F(_vTranslation, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationTranslationRadF(const Vec3F& _vRotation, const Vec3F& _vTranslation) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = Vec4F(_vTranslation, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ScaleXF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_fScale, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ScaleYF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _fScale, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, 1.0f, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ScaleZF(float _fScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(1.0f, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, 1.0f, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _fScale, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF ScaleXYZF(const Vec3F& _vScale) {
	MatrixF mMat;
	mMat[0] = Vec4F(_vScale.x, 0.0f, 0.0f, 0.0f);
	mMat[1] = Vec4F(0.0f, _vScale.y, 0.0f, 0.0f);
	mMat[2] = Vec4F(0.0f, 0.0f, _vScale.z, 0.0f);
	mMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationTranslationScaleDegF(const Vec3F& _vRotation, const Vec3F& _vTranslation, const Vec3F& _vScale) {
	MatrixF mMat = RotationYawPitchRollDegF(_vRotation);
	mMat[3] = Vec4F(_vTranslation, 1.0f);
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF RotationTranslationScaleRadF(const Vec3F& _vRotation, const Vec3F& _vTranslation, const Vec3F& _vScale) {
	MatrixF mMat = RotationYawPitchRollRadF(_vRotation);
	mMat[3] = Vec4F(_vTranslation, 1.0f);
	mMat *= ScaleXYZF(_vScale);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixF TranslateXLocal(float _fDist, const MatrixF& _mMat) { return _mMat * TranslationXF(_fDist); }
[[nodiscard]] HC_INLINE MatrixF TranslateXGlobal(float _fDist, const MatrixF& _mMat) { return TranslationXF(_fDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF TranslateYLocal(float _fDist, const MatrixF& _mMat) { return _mMat * TranslationYF(_fDist); }
[[nodiscard]] HC_INLINE MatrixF TranslateYGlobal(float _fDist, const MatrixF& _mMat) { return TranslationYF(_fDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF TranslateZLocal(float _fDist, const MatrixF& _mMat) { return _mMat * TranslationZF(_fDist); }
[[nodiscard]] HC_INLINE MatrixF TranslateZGlobal(float _fDist, const MatrixF& _mMat) { return TranslationZF(_fDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF TranslateLocal(const Vec3F& _vTranslation, const MatrixF& _mMat) { return _mMat * TranslationF(_vTranslation); }
[[nodiscard]] HC_INLINE MatrixF TranslateGlobal(const Vec3F& _vTranslation, const MatrixF& _mMat) { return TranslationF(_vTranslation) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateXLocalDeg(float _fDeg, const MatrixF& _mMat) { return _mMat * RotationXDegF(_fDeg); }
[[nodiscard]] HC_INLINE MatrixF RotateXLocalRad(float _fRad, const MatrixF& _mMat) { return _mMat * RotationXRadF(_fRad); }
[[nodiscard]] HC_INLINE MatrixF RotateXGlobalDeg(float _fDeg, const MatrixF& _mMat) { return RotationXDegF(_fDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateXGlobalRad(float _fDeg, const MatrixF& _mMat) { return RotationXRadF(_fDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateYLocalDeg(float _fDeg, const MatrixF& _mMat) { return _mMat * RotationYDegF(_fDeg); }
[[nodiscard]] HC_INLINE MatrixF RotateYLocalRad(float _fRad, const MatrixF& _mMat) { return _mMat * RotationYRadF(_fRad); }
[[nodiscard]] HC_INLINE MatrixF RotateYGlobalDeg(float _fDeg, const MatrixF& _mMat) { return RotationYDegF(_fDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateYGlobalRad(float _fDeg, const MatrixF& _mMat) { return RotationYDegF(_fDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateZLocalDeg(float _fDeg, const MatrixF& _mMat) { return _mMat * RotationZDegF(_fDeg); }
[[nodiscard]] HC_INLINE MatrixF RotateZLocalRad(float _fRad, const MatrixF& _mMat) { return _mMat * RotationZRadF(_fRad); }
[[nodiscard]] HC_INLINE MatrixF RotateZGlobalDeg(float _fDeg, const MatrixF& _mMat) { return RotationZDegF(_fDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateZGlobalRad(float _fRad, const MatrixF& _mMat) { return RotationZRadF(_fRad) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateYawPitchRollLocalDeg(const Vec3F& _vRotation, const MatrixF& _mMat) { return _mMat * RotationYawPitchRollDegF(_vRotation); }
[[nodiscard]] HC_INLINE MatrixF RotateYawPitchRollLocalRad(const Vec3F& _vRotation, const MatrixF& _mMat) { return _mMat * RotationYawPitchRollRadF(_vRotation); }
[[nodiscard]] HC_INLINE MatrixF RotateYawPitchRollGlobalDeg(const Vec3F& _vRotation, const MatrixF& _mMat) { return RotationYawPitchRollDegF(_vRotation) * _mMat; }
[[nodiscard]] HC_INLINE MatrixF RotateYawPitchRollGlobalRad(const Vec3F& _vRotation, const MatrixF& _mMat) { return RotationYawPitchRollRadF(_vRotation) * _mMat; }

#endif