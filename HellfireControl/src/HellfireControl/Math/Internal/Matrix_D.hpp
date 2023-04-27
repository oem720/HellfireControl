#pragma once

#include <HellfireControl/Math/Internal/Matrix_Common.hpp>

#if HC_USE_SIMD

struct MatrixD {
	Vec4D m_vRows[4];

	HC_INLINE HC_VECTORCALL MatrixD() {};
	HC_INLINE explicit HC_VECTORCALL MatrixD(Vec4D _vRow1, Vec4D _vRow2, Vec4D _vRow3, Vec4D _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE explicit HC_VECTORCALL MatrixD(Vec4D* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }
	HC_INLINE Vec4D HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4D& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4D HC_VECTORCALL Row1() { return m_vRows[0]; }
	HC_INLINE Vec4D HC_VECTORCALL Row2() { return m_vRows[1]; }
	HC_INLINE Vec4D HC_VECTORCALL Row3() { return m_vRows[2]; }
	HC_INLINE Vec4D HC_VECTORCALL Row4() { return m_vRows[3]; }
	HC_INLINE void HC_VECTORCALL SetRow1(Vec4D _vRow) { m_vRows[0] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow2(Vec4D _vRow) { m_vRows[1] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow3(Vec4D _vRow) { m_vRows[2] = _vRow; }
	HC_INLINE void HC_VECTORCALL SetRow4(Vec4D _vRow) { m_vRows[3] = _vRow; }
};

HC_INLINE MatrixD HC_VECTORCALL Transpose(MatrixD _mMat) {
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
HC_INLINE double HC_VECTORCALL Determinant(MatrixD _mMat) {
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
HC_INLINE MatrixD HC_VECTORCALL Inverse(MatrixD _mMat) {

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
HC_INLINE MatrixD HC_VECTORCALL IdentityD() {
	static MatrixD mMat(Vec4D(1.0, 0.0, 0.0, 0.0),
		Vec4D(0.0, 1.0, 0.0, 0.0),
		Vec4D(0.0, 0.0, 1.0, 0.0),
		Vec4D(0.0, 0.0, 0.0, 1.0));
	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ProjectionD(double _fAspectRatio, double _fDOV, double _fNearPlane, double _fDarPlane) {
	double fDocal = 1.0 / tan(_fDOV);
	MatrixD mMat;
	mMat[0] = Vec4D(fDocal / _fAspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -fDocal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _fNearPlane / (_fDarPlane - _fNearPlane), -1.0);
	mMat[3] = Vec4D(0.0, 0.0, (_fNearPlane * _fDarPlane) / (_fDarPlane - _fNearPlane), 0.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ProjectionDReversedInf(double _fAspectRatio, double _fDOV, double _fNearPlane) {
	double fDocal = 1.0 / tan(_fDOV);
	MatrixD mMat;
	mMat[0] = Vec4D(fDocal / _fAspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -fDocal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 0.0, -1.0);
	mMat[3] = Vec4D(0.0, 0.0, _fNearPlane, 0.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL LookAtLH(Vec4D _vEye, Vec4D _vAt, Vec4D _vUp) {
	Vec4D vZAxis = Normalize(_vAt - _vEye);
	Vec4D vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4D vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixD(vXAxis, vYAxis, vZAxis, _vAt);
}
HC_INLINE MatrixD HC_VECTORCALL operator+(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] + _mRight[0];
	_mLeft[1] = _mLeft[1] + _mRight[1];
	_mLeft[2] = _mLeft[2] + _mRight[2];
	_mLeft[3] = _mLeft[3] + _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixD HC_VECTORCALL operator-(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] - _mRight[0];
	_mLeft[1] = _mLeft[1] - _mRight[1];
	_mLeft[2] = _mLeft[2] - _mRight[2];
	_mLeft[3] = _mLeft[3] - _mRight[3];

	return _mLeft;
}
HC_INLINE MatrixD HC_VECTORCALL operator*(MatrixD _mLeft, double _fRight) {
	_mLeft[0] *= _fRight;
	_mLeft[1] *= _fRight;
	_mLeft[2] *= _fRight;
	_mLeft[3] *= _fRight;

	return _mLeft;
}
HC_INLINE MatrixD HC_VECTORCALL operator*(double _fLeft, MatrixD _mRight) {
	_mRight[0] *= _fLeft;
	_mRight[1] *= _fLeft;
	_mRight[2] *= _fLeft;
	_mRight[3] *= _fLeft;

	return _mRight;
}
HC_INLINE MatrixD HC_VECTORCALL operator*(MatrixD _mLeft, MatrixD _mRight) {
	_mRight = Transpose(_mRight);

	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		_mLeft[iNdx] = Vec4D(Dot(_mLeft[iNdx], _mRight[0]),
			Dot(_mLeft[iNdx], _mRight[1]),
			Dot(_mLeft[iNdx], _mRight[2]),
			Dot(_mLeft[iNdx], _mRight[3]));
	}

	return _mLeft;
}
HC_INLINE Vec4D HC_VECTORCALL operator*(MatrixD _mLeft, Vec4D _vRight) {
	_vRight = Vec4D(Dot(_mLeft[0], _vRight),
		Dot(_mLeft[1], _vRight),
		Dot(_mLeft[2], _vRight),
		Dot(_mLeft[3], _vRight));

	return _vRight;
}
HC_INLINE Vec4D HC_VECTORCALL operator*(Vec4D _vLeft, MatrixD _mRight) {
	_vLeft = Vec4D(Dot(_vLeft, _mRight[0]),
		Dot(_vLeft, _mRight[1]),
		Dot(_vLeft, _mRight[2]),
		Dot(_vLeft, _mRight[3]));

	return _vLeft;
}
HC_INLINE MatrixD HC_VECTORCALL operator/(MatrixD _mLeft, double _fRight) {
	_mLeft[0] /= _fRight;
	_mLeft[1] /= _fRight;
	_mLeft[2] /= _fRight;
	_mLeft[3] /= _fRight;

	return _mLeft;
}
HC_INLINE MatrixD HC_VECTORCALL operator/(double _fLeft, MatrixD _mRight) {
	_mRight[0] /= _fLeft;
	_mRight[1] /= _fLeft;
	_mRight[2] /= _fLeft;
	_mRight[3] /= _fLeft;

	return _mRight;
}
HC_INLINE MatrixD& HC_VECTORCALL operator+=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft + _mRight; return _mLeft; }
HC_INLINE MatrixD& HC_VECTORCALL operator-=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft - _mRight; return _mLeft; }
HC_INLINE MatrixD& HC_VECTORCALL operator*=(MatrixD& _mLeft, double _fRight) { _mLeft = _mLeft * _fRight; return _mLeft; }
HC_INLINE MatrixD& HC_VECTORCALL operator*=(MatrixD& _mLeft, MatrixD _mRight) { _mLeft = _mLeft * _mRight; return _mLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator*=(Vec4D& _vLeft, MatrixD _mRight) { _vLeft = _vLeft * _mRight; return _vLeft; }
HC_INLINE MatrixD& HC_VECTORCALL operator/=(MatrixD& _mLeft, double _fRight) { _mLeft = _mLeft / _fRight; return _mLeft; }
HC_INLINE MatrixD HC_VECTORCALL operator~(MatrixD _mMat) { return MatrixD(); }
HC_INLINE MatrixD HC_VECTORCALL operator-(MatrixD _mMat) { return MatrixD() - _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotationXDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_fDeg), sin(_fDeg), 0.0);
	mMat[2] = Vec4D(0.0, -sin(_fDeg), cos(_fDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationXRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_fRad), -sin(_fRad), 0.0);
	mMat[2] = Vec4D(0.0, sin(_fRad), cos(_fRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationYDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fDeg), 0.0, sin(_fDeg), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_fDeg), 0.0, cos(_fDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationYRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fRad), 0.0, sin(_fRad), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_fRad), 0.0, cos(_fRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationZDegD(double _fDeg) {
	_fDeg = HC_DEG2RAD(_fDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fDeg), -sin(_fDeg), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_fDeg), cos(_fDeg), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationZRadD(double _fRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_fRad), -sin(_fRad), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_fRad), cos(_fRad), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationYawPitchRollDegD(Vec4D _vRotation) {
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
HC_INLINE MatrixD HC_VECTORCALL RotationYawPitchRollRadD(Vec4D _vRotation) {
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
HC_INLINE MatrixD HC_VECTORCALL TranslationXD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(_fDist, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL TranslationYD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _fDist, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL TranslationZD(double _fDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _fDist, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL TranslationD(Vec4D _vTranslation) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationTranslationDegD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationTranslationRadD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ScaleXD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_fScale, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ScaleYD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _fScale, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ScaleZD(double _fScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _fScale, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL ScaleXYZD(Vec4D _vScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_vScale.X(), 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _vScale.Y(), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _vScale.Z(), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationTranslationScaleDegD(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL RotationTranslationScaleRadD(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}
HC_INLINE MatrixD HC_VECTORCALL TranslateXLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationXD(_fDist); }
HC_INLINE MatrixD HC_VECTORCALL TranslateXGlobal(double _fDist, MatrixD _mMat) { return TranslationXD(_fDist) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL TranslateYLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationYD(_fDist); }
HC_INLINE MatrixD HC_VECTORCALL TranslateYGlobal(double _fDist, MatrixD _mMat) { return TranslationYD(_fDist) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL TranslateZLocal(double _fDist, MatrixD _mMat) { return _mMat * TranslationZD(_fDist); }
HC_INLINE MatrixD HC_VECTORCALL TranslateZGlobal(double _fDist, MatrixD _mMat) { return TranslationZD(_fDist) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL TranslateLocal(Vec4D _vTranslation, MatrixD _mMat) { return _mMat * TranslationD(_vTranslation); }
HC_INLINE MatrixD HC_VECTORCALL TranslateGlobal(Vec4D _vTranslation, MatrixD _mMat) { return TranslationD(_vTranslation) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateXLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationXDegD(_fDeg); }
HC_INLINE MatrixD HC_VECTORCALL RotateXLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationXRadD(_fRad); }
HC_INLINE MatrixD HC_VECTORCALL RotateXGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationXDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateXGlobalRad(double _fDeg, MatrixD _mMat) { return RotationXRadD(_fDeg) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateYLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationYDegD(_fDeg); }
HC_INLINE MatrixD HC_VECTORCALL RotateYLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationYRadD(_fRad); }
HC_INLINE MatrixD HC_VECTORCALL RotateYGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationYDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateYGlobalRad(double _fDeg, MatrixD _mMat) { return RotationYDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateZLocalDeg(double _fDeg, MatrixD _mMat) { return _mMat * RotationZDegD(_fDeg); }
HC_INLINE MatrixD HC_VECTORCALL RotateZLocalRad(double _fRad, MatrixD _mMat) { return _mMat * RotationZRadD(_fRad); }
HC_INLINE MatrixD HC_VECTORCALL RotateZGlobalDeg(double _fDeg, MatrixD _mMat) { return RotationZDegD(_fDeg) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateZGlobalRad(double _fRad, MatrixD _mMat) { return RotationZRadD(_fRad) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateYawPitchRollLocalDeg(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollDegD(_vRotation); }
HC_INLINE MatrixD HC_VECTORCALL RotateYawPitchRollLocalRad(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollRadD(_vRotation); }
HC_INLINE MatrixD HC_VECTORCALL RotateYawPitchRollGlobalDeg(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollDegD(_vRotation) * _mMat; }
HC_INLINE MatrixD HC_VECTORCALL RotateYawPitchRollGlobalRad(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollRadD(_vRotation) * _mMat; }

#else

struct MatrixD
{
	union {
		struct {
			Vec4D m_vRow0;
			Vec4D m_vRow1;
			Vec4D m_vRow2;
			Vec4D m_vRow3;
		};

		Vec4D m_vRows[4];
		double m_dM[16];
		double m_dMat[4][4];
	};

	HC_INLINE MatrixD() { m_vRows[0] = Vec4D(); m_vRows[1] = Vec4D(); m_vRows[2] = Vec4D(); m_vRows[3] = Vec4D(); }
	HC_INLINE explicit MatrixD(Vec4D _vRow0, Vec4D _vRow1, Vec4D _vRow2, Vec4D _vRow3) { m_vRows[0] = _vRow0; m_vRows[1] = _vRow1; m_vRows[2] = _vRow2; m_vRows[3] = _vRow3; }
	HC_INLINE Vec4D operator[](int _iNdx) const { assert(_iNdx < 4); return m_vRows[_iNdx]; }
	HC_INLINE Vec4D& operator[](int _iNdx) { assert(_iNdx < 4); return m_vRows[_iNdx]; }
};

[[nodiscard]] HC_INLINE MatrixD Transpose(MatrixD _mMat) {
	return MatrixD(Vec4D(_mMat[0][0], _mMat[1][0], _mMat[2][0], _mMat[3][0]),
		Vec4D(_mMat[0][1], _mMat[1][1], _mMat[2][1], _mMat[3][1]),
		Vec4D(_mMat[0][2], _mMat[1][2], _mMat[2][2], _mMat[3][2]),
		Vec4D(_mMat[0][3], _mMat[1][3], _mMat[2][3], _mMat[3][3]));
}

[[nodiscard]] HC_INLINE double Determinant(MatrixD _mMat) {
	//Sub matrices
	Vec4D A = Vec4D(_mMat[0].XY(), _mMat[1].XY());
	Vec4D B = Vec4D(_mMat[0].ZW(), _mMat[1].ZW());
	Vec4D C = Vec4D(_mMat[2].XY(), _mMat[3].XY());
	Vec4D D = Vec4D(_mMat[2].ZW(), _mMat[3].ZW());

	//Determinants
	Vec4D dets = (Vec4D(_mMat[0].XZ(), _mMat[2].XZ()) * Vec4D(_mMat[1].YW(), _mMat[3].YW())) -
		(Vec4D(_mMat[0].YW(), _mMat[2].YW()) * Vec4D(_mMat[1].XZ(), _mMat[3].XZ()));

	double detA = dets.x;
	double detB = dets.y;
	double detC = dets.z;
	double detD = dets.w;
	//D adjmul C
	Vec4D DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4D AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());

	return ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
}

[[nodiscard]] HC_INLINE MatrixD Inverse(MatrixD _mMat) {

	//Sub matrices
	Vec4D A = Vec4D(_mMat[0].XY(), _mMat[1].XY());
	Vec4D B = Vec4D(_mMat[0].ZW(), _mMat[1].ZW());
	Vec4D C = Vec4D(_mMat[2].XY(), _mMat[3].XY());
	Vec4D D = Vec4D(_mMat[2].ZW(), _mMat[3].ZW());

	//Determinants
	Vec4D dets = (Vec4D(_mMat[0].XZ(), _mMat[2].XZ()) * Vec4D(_mMat[1].YW(), _mMat[3].YW())) -
		(Vec4D(_mMat[0].YW(), _mMat[2].YW()) * Vec4D(_mMat[1].XZ(), _mMat[3].XZ()));
	double detA = dets.x;
	double detB = dets.y;
	double detC = dets.z;
	double detD = dets.w;

	//D adjmul C
	Vec4D DC = (D.WWXX() * C) - (D.YYZZ() * C.ZWXY());
	//A adjmul B
	Vec4D AB = (A.WWXX() * B) - (A.YYZZ() * B.ZWXY());
	//DetM
	double detM = ((detA * detD) + (detB * detC)) - Sum(AB * DC.XZYW());
	//No inverse, return 0
	if (HC_DOUBLE_COMPARE(detM, 0.0)) { return MatrixD(); }
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

	_mMat[0] = Vec4D(X.WY(), Y.WY());
	_mMat[1] = Vec4D(X.ZX(), Y.ZX());
	_mMat[2] = Vec4D(Z.WY(), W.WY());
	_mMat[3] = Vec4D(Z.ZX(), W.ZX());

	return _mMat;
}

[[nodiscard]] HC_INLINE MatrixD IdentityD() {
	static MatrixD mMat(Vec4D(1.0, 0.0, 0.0, 0.0),
		Vec4D(0.0, 1.0, 0.0, 0.0),
		Vec4D(0.0, 0.0, 1.0, 0.0),
		Vec4D(0.0, 0.0, 0.0, 1.0));
	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ProjectionD(double _AspectRatio, double _FOV, double _NearPlane, double _FarPlane) {
	double Focal = 1.0 / tan(_FOV);
	MatrixD mMat;
	mMat[0] = Vec4D(Focal / _AspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -Focal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _NearPlane / (_FarPlane - _NearPlane), -1.0);
	mMat[3] = Vec4D(0.0, 0.0, (_NearPlane * _FarPlane) / (_FarPlane - _NearPlane), 0.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ProjectionDReversedIn(double _AspectRatio, double _FOV, double _NearPlane) {
	double Focal = 1.0 / tan(_FOV);
	MatrixD mMat;
	mMat[0] = Vec4D(Focal / _AspectRatio, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, -Focal, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 0.0, -1.0);
	mMat[3] = Vec4D(0.0, 0.0, _NearPlane, 0.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD LookAtLH(Vec4D _vEye, Vec4D _vAt, Vec4D _vUp) {
	Vec4D vZAxis = Normalize(_vAt - _vEye);
	Vec4D vXAxis = Normalize(Cross(_vUp, vZAxis));
	Vec4D vYAxis = Normalize(Cross(vZAxis, vXAxis));

	return MatrixD(vXAxis, vYAxis, vZAxis, _vAt);
}

[[nodiscard]] HC_INLINE MatrixD operator+(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] + _mRight[0];
	_mLeft[1] = _mLeft[1] + _mRight[1];
	_mLeft[2] = _mLeft[2] + _mRight[2];
	_mLeft[3] = _mLeft[3] + _mRight[3];

	return _mLeft;
}

[[nodiscard]] HC_INLINE MatrixD operator-(MatrixD _mLeft, MatrixD _mRight) {
	_mLeft[0] = _mLeft[0] - _mRight[0];
	_mLeft[1] = _mLeft[1] - _mRight[1];
	_mLeft[2] = _mLeft[2] - _mRight[2];
	_mLeft[3] = _mLeft[3] - _mRight[3];

	return _mLeft;
}

[[nodiscard]] HC_INLINE MatrixD operator*(MatrixD _mLeft, double _fRight) {
	_mLeft[0] *= _fRight;
	_mLeft[1] *= _fRight;
	_mLeft[2] *= _fRight;
	_mLeft[3] *= _fRight;

	return _mLeft;
}

[[nodiscard]] HC_INLINE MatrixD operator*(double _fLeft, MatrixD _mRight) {
	_mRight[0] *= _fLeft;
	_mRight[1] *= _fLeft;
	_mRight[2] *= _fLeft;
	_mRight[3] *= _fLeft;

	return _mRight;
}

[[nodiscard]] HC_INLINE MatrixD operator*(MatrixD _mLeft, MatrixD _mRight) {
	_mRight = Transpose(_mRight);

	for (int iNdx = 0; iNdx < 4; ++iNdx) {
		_mLeft[iNdx] = Vec4D(Dot(_mLeft[iNdx], _mRight[0]),
			Dot(_mLeft[iNdx], _mRight[1]),
			Dot(_mLeft[iNdx], _mRight[2]),
			Dot(_mLeft[iNdx], _mRight[3]));
	}

	return _mLeft;
}

[[nodiscard]] HC_INLINE Vec4D operator*(MatrixD _mLeft, Vec4D _vRight) {
	_vRight = Vec4D(Dot(_mLeft[0], _vRight),
		Dot(_mLeft[1], _vRight),
		Dot(_mLeft[2], _vRight),
		Dot(_mLeft[3], _vRight));

	return _vRight;
}

[[nodiscard]] HC_INLINE Vec4D operator*(Vec4D _vLeft, MatrixD _mRight) {
	_vLeft = Vec4D(Dot(_vLeft, _mRight[0]),
		Dot(_vLeft, _mRight[1]),
		Dot(_vLeft, _mRight[2]),
		Dot(_vLeft, _mRight[3]));

	return _vLeft;
}

[[nodiscard]] HC_INLINE MatrixD operator/(MatrixD _mLeft, double _fRight) {
	_mLeft[0] /= _fRight;
	_mLeft[1] /= _fRight;
	_mLeft[2] /= _fRight;
	_mLeft[3] /= _fRight;

	return _mLeft;
}

[[nodiscard]] HC_INLINE MatrixD operator/(double _fLeft, MatrixD _mRight) {
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
[[nodiscard]] HC_INLINE MatrixD operator~(MatrixD _mMat) { return MatrixD(); }
[[nodiscard]] HC_INLINE MatrixD operator-(MatrixD _mMat) { return MatrixD(-_mMat[0], -_mMat[1], -_mMat[2], -_mMat[3]); }

[[nodiscard]] HC_INLINE MatrixD RotationXDegD(double _dDeg) {
	_dDeg = HC_DEG2RAD(_dDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_dDeg), sin(_dDeg), 0.0);
	mMat[2] = Vec4D(0.0, -sin(_dDeg), cos(_dDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationXRadD(double _dRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, cos(_dRad), -sin(_dRad), 0.0);
	mMat[2] = Vec4D(0.0, sin(_dRad), cos(_dRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationYDegD(double _dDeg) {
	_dDeg = HC_DEG2RAD(_dDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_dDeg), 0.0, sin(_dDeg), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_dDeg), 0.0, cos(_dDeg), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationYRadD(double _dRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_dRad), 0.0, sin(_dRad), 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(-sin(_dRad), 0.0, cos(_dRad), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationZDegD(double _dDeg) {
	_dDeg = HC_DEG2RAD(_dDeg);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(_dDeg), -sin(_dDeg), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_dDeg), cos(_dDeg), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationZRadD(double _dRad) {
	MatrixD mMat;
	mMat[0] = Vec4D(cos(_dRad), -sin(_dRad), 0.0, 0.0);
	mMat[1] = Vec4D(sin(_dRad), cos(_dRad), 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationYawPitchRollDegD(Vec4D _vRotation) {
	double dYaw = HC_DEG2RAD(_vRotation.x);
	double dPitch = HC_DEG2RAD(_vRotation.y);
	double dRoll = HC_DEG2RAD(_vRotation.z);

	MatrixD mMat;
	mMat[0] = Vec4D(cos(dYaw) * cos(dPitch), (cos(dYaw) * sin(dPitch) * sin(dRoll)) - (sin(dYaw) * cos(dRoll)), (cos(dYaw) * sin(dPitch) * cos(dRoll)) + (sin(dYaw) * sin(dRoll)), 0.0);
	mMat[1] = Vec4D(sin(dYaw) * cos(dPitch), (sin(dYaw) * sin(dPitch) * sin(dRoll)) + (cos(dYaw) * cos(dRoll)), (sin(dYaw) * sin(dPitch) * cos(dRoll)) - (cos(dYaw) * sin(dRoll)), 0.0);
	mMat[2] = Vec4D(-sin(dPitch), cos(dPitch) * sin(dRoll), cos(dPitch) * cos(dRoll), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationYawPitchRollRadD(Vec4D _vRotation) {
	double dYaw = _vRotation.x;
	double dPitch = _vRotation.y;
	double dRoll = _vRotation.z;

	MatrixD mMat;
	mMat[0] = Vec4D(cos(dYaw) * cos(dPitch), (cos(dYaw) * sin(dPitch) * sin(dRoll)) - (sin(dYaw) * cos(dRoll)), (cos(dYaw) * sin(dPitch) * cos(dRoll)) + (sin(dYaw) * sin(dRoll)), 0.0);
	mMat[1] = Vec4D(sin(dYaw) * cos(dPitch), (sin(dYaw) * sin(dPitch) * sin(dRoll)) + (cos(dYaw) * cos(dRoll)), (sin(dYaw) * sin(dPitch) * cos(dRoll)) - (cos(dYaw) * sin(dRoll)), 0.0);
	mMat[2] = Vec4D(-sin(dPitch), cos(dPitch) * sin(dRoll), cos(dPitch) * cos(dRoll), 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD TranslationXD(double _dDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(_dDist, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD TranslationYD(double _dDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _dDist, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD TranslationZD(double _dDist) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, _dDist, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD TranslationD(Vec4D _vTranslation) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = _vTranslation;

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationTranslationDegD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationTranslationRadD(Vec4D _vRotation, Vec4D _vTranslation) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ScaleXD(double _dScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_dScale, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ScaleYD(double _dScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _dScale, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, 1.0, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ScaleZD(double _dScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(1.0, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, 1.0, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _dScale, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD ScaleXYZD(Vec4D _vScale) {
	MatrixD mMat;
	mMat[0] = Vec4D(_vScale.x, 0.0, 0.0, 0.0);
	mMat[1] = Vec4D(0.0, _vScale.y, 0.0, 0.0);
	mMat[2] = Vec4D(0.0, 0.0, _vScale.z, 0.0);
	mMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationTranslationScaleDegF(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollDegD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD RotationTranslationScaleRadF(Vec4D _vRotation, Vec4D _vTranslation, Vec4D _vScale) {
	MatrixD mMat = RotationYawPitchRollRadD(_vRotation);
	mMat[3] = _vTranslation;
	mMat *= ScaleXYZD(_vScale);

	return mMat;
}

[[nodiscard]] HC_INLINE MatrixD TranslateXLocal(double _dDist, MatrixD _mMat) { return _mMat * TranslationXD(_dDist); }
[[nodiscard]] HC_INLINE MatrixD TranslateXGlobal(double _dDist, MatrixD _mMat) { return TranslationXD(_dDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD TranslateYLocal(double _dDist, MatrixD _mMat) { return _mMat * TranslationYD(_dDist); }
[[nodiscard]] HC_INLINE MatrixD TranslateYGlobal(double _dDist, MatrixD _mMat) { return TranslationYD(_dDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD TranslateZLocal(double _dDist, MatrixD _mMat) { return _mMat * TranslationZD(_dDist); }
[[nodiscard]] HC_INLINE MatrixD TranslateZGlobal(double _dDist, MatrixD _mMat) { return TranslationZD(_dDist) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD TranslateLocal(Vec4D _vTranslation, MatrixD _mMat) { return _mMat * TranslationD(_vTranslation); }
[[nodiscard]] HC_INLINE MatrixD TranslateGlobal(Vec4D _vTranslation, MatrixD _mMat) { return TranslationD(_vTranslation) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateXLocalDeg(double _dDeg, MatrixD _mMat) { return _mMat * RotationXDegD(_dDeg); }
[[nodiscard]] HC_INLINE MatrixD RotateXLocalRad(double _dRad, MatrixD _mMat) { return _mMat * RotationXRadD(_dRad); }
[[nodiscard]] HC_INLINE MatrixD RotateXGlobalDeg(double _dDeg, MatrixD _mMat) { return RotationXDegD(_dDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateXGlobalRad(double _dDeg, MatrixD _mMat) { return RotationXRadD(_dDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateYLocalDeg(double _dDeg, MatrixD _mMat) { return _mMat * RotationYDegD(_dDeg); }
[[nodiscard]] HC_INLINE MatrixD RotateYLocalRad(double _dRad, MatrixD _mMat) { return _mMat * RotationYRadD(_dRad); }
[[nodiscard]] HC_INLINE MatrixD RotateYGlobalDeg(double _dDeg, MatrixD _mMat) { return RotationYDegD(_dDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateYGlobalRad(double _dDeg, MatrixD _mMat) { return RotationYDegD(_dDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateZLocalDeg(double _dDeg, MatrixD _mMat) { return _mMat * RotationZDegD(_dDeg); }
[[nodiscard]] HC_INLINE MatrixD RotateZLocalRad(double _dRad, MatrixD _mMat) { return _mMat * RotationZRadD(_dRad); }
[[nodiscard]] HC_INLINE MatrixD RotateZGlobalDeg(double _dDeg, MatrixD _mMat) { return RotationZDegD(_dDeg) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateZGlobalRad(double _dRad, MatrixD _mMat) { return RotationZRadD(_dRad) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateYawPitchRollLocalDeg(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollDegD(_vRotation); }
[[nodiscard]] HC_INLINE MatrixD RotateYawPitchRollLocalRad(Vec4D _vRotation, MatrixD _mMat) { return _mMat * RotationYawPitchRollRadD(_vRotation); }
[[nodiscard]] HC_INLINE MatrixD RotateYawPitchRollGlobalDeg(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollDegD(_vRotation) * _mMat; }
[[nodiscard]] HC_INLINE MatrixD RotateYawPitchRollGlobalRad(Vec4D _vRotation, MatrixD _mMat) { return RotationYawPitchRollRadD(_vRotation) * _mMat; }

#endif