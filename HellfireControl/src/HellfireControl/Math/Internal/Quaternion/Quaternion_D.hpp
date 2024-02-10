#pragma once

#include <HellfireControl/Math/Internal/Quaternion/Quaternion_Common.hpp>

#if HC_USE_SIMD

struct QuaternionD {
	Vec4D m_vQuat;

	HC_INLINE HC_VECTORCALL QuaternionD() {}
	HC_INLINE HC_VECTORCALL QuaternionD(double _fX, double _fY, double _fZ, double _fW) { m_vQuat = Vec4D(_fX, _fY, _fZ, _fW); }
	HC_INLINE HC_VECTORCALL QuaternionD(int _fX, int _fY, int _fZ, int _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionD(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionD(MatrixD _mMat) {
		//FIXME: All of this is god-awful unoptimized crap. Make into optimized SIMD code ASAP! - Owen
		double dSum = 0.0;
		if (_mMat[2][2] < 0.0) {
			if (_mMat[0][0] > _mMat[1][1]) {
				dSum = 1.0 + _mMat[0][0] - _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4D(dSum, _mMat[0][1] + _mMat[1][0], _mMat[2][0] + _mMat[0][2], _mMat[1][2] - _mMat[2][2]);
			}
			else {
				dSum = 1.0 - _mMat[0][0] + _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4D(_mMat[0][1] + _mMat[1][0], dSum, _mMat[1][2] + _mMat[2][1], _mMat[2][0] - _mMat[0][2]);
			}
		}
		else {
			if (_mMat[0][0] < _mMat[1][1]) {
				dSum = 1.0 - _mMat[0][0] - _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4D(_mMat[2][0] + _mMat[0][2], _mMat[1][2] + _mMat[2][1], dSum, _mMat[0][1] - _mMat[1][0]);
			}
			else {
				dSum = 1.0f + _mMat[0][0] + _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4D(_mMat[1][2] - _mMat[2][1], _mMat[2][0] - _mMat[0][2], _mMat[0][1] - _mMat[1][0], dSum);
			}
		}

		m_vQuat *= 0.5 / sqrt(dSum);
	}
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { return m_vQuat[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return m_vQuat.X(); }
	HC_INLINE double HC_VECTORCALL Y() const { return m_vQuat.Y(); }
	HC_INLINE double HC_VECTORCALL Z() const { return m_vQuat.Z(); }
	HC_INLINE double HC_VECTORCALL W() const { return m_vQuat.W(); }
	HC_INLINE void HC_VECTORCALL SetX(double _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void HC_VECTORCALL SetY(double _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void HC_VECTORCALL SetZ(double _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void HC_VECTORCALL SetW(double _fW) { m_vQuat.SetW(_fW); }
};

#else

struct HC_ALIGNAS(32) QuaternionD
{
	union {
		Vec4D m_vQuat;

		struct {
			double x;
			double y;
			double z;
			double w;
		};
	};

	HC_INLINE QuaternionD() { m_vQuat = Vec4D(); }
	HC_INLINE QuaternionD(const Vec4D& _vQuat) { m_vQuat = _vQuat; }
	HC_INLINE explicit QuaternionD(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4D(_fX, _fY, _fZ, _fW); }
	HC_INLINE explicit QuaternionD(int _iX, int _iY, int _iZ, int _iW) { m_vQuat = Vec4D(_iX, _iY, _iZ, _iW); }
	HC_INLINE explicit QuaternionD(double _dX, double _dY, double _dZ, double _dW) { m_vQuat = Vec4D(_dX, _dY, _dZ, _dW); }

	HC_INLINE explicit QuaternionD(double _dRoll, double _dPitch, double _dYaw) {
		double dCosRoll = cos(_dRoll * 0.5);
		double dSinRoll = sin(_dRoll * 0.5);
		double dCosPitch = cos(_dPitch * 0.5);
		double dSinPitch = sin(_dPitch * 0.5);
		double dCosYaw = cos(_dYaw * 0.5);
		double dSinYaw = sin(_dYaw * 0.5);

		m_vQuat = Vec4D(dSinRoll * dCosPitch * dCosYaw - dCosRoll * dSinPitch * dSinYaw,
						dCosRoll * dSinPitch * dCosYaw + dSinRoll * dCosPitch * dSinYaw,
						dCosRoll * dCosPitch * dSinYaw - dSinRoll * dSinPitch * dCosYaw,
						dCosRoll * dCosPitch * dCosYaw + dSinRoll * dSinPitch * dSinYaw);
	}

	HC_INLINE explicit QuaternionD(const Vec3D& _vEulerAngles) {
		double dCosRoll = cos(_vEulerAngles.x * 0.5);
		double dSinRoll = sin(_vEulerAngles.x * 0.5);
		double dCosPitch = cos(_vEulerAngles.y * 0.5);
		double dSinPitch = sin(_vEulerAngles.y * 0.5);
		double dCosYaw = cos(_vEulerAngles.z * 0.5);
		double dSinYaw = sin(_vEulerAngles.z * 0.5);

		m_vQuat = Vec4D(dSinRoll * dCosPitch * dCosYaw - dCosRoll * dSinPitch * dSinYaw,
						dCosRoll * dSinPitch * dCosYaw + dSinRoll * dCosPitch * dSinYaw,
						dCosRoll * dCosPitch * dSinYaw - dSinRoll * dSinPitch * dCosYaw,
						dCosRoll * dCosPitch * dCosYaw + dSinRoll * dSinPitch * dSinYaw);
	}

	HC_INLINE explicit QuaternionD(const MatrixD& _mRotation) {
		double dSum = 0.0;
		if (_mRotation[2][2] < 0.0) {
			if (_mRotation[0][0] > _mRotation[1][1]) {
				dSum = 1.0 + _mRotation[0][0] - _mRotation[1][1] - _mRotation[2][2];
				m_vQuat = Vec4D(dSum, _mRotation[0][1] + _mRotation[1][0], _mRotation[2][0] + _mRotation[0][2], _mRotation[1][2] - _mRotation[2][2]);
			}
			else {
				dSum = 1.0 - _mRotation[0][0] + _mRotation[1][1] - _mRotation[2][2];
				m_vQuat = Vec4D(_mRotation[0][1] + _mRotation[1][0], dSum, _mRotation[1][2] + _mRotation[2][1], _mRotation[2][0] - _mRotation[0][2]);
			}
		}
		else {
			if (_mRotation[0][0] < _mRotation[1][1]) {
				dSum = 1.0 - _mRotation[0][0] - _mRotation[1][1] + _mRotation[2][2];
				m_vQuat = Vec4D(_mRotation[2][0] + _mRotation[0][2], _mRotation[1][2] + _mRotation[2][1], dSum, _mRotation[0][1] - _mRotation[1][0]);
			}
			else {
				dSum = 1.0 + _mRotation[0][0] + _mRotation[1][1] + _mRotation[2][2];
				m_vQuat = Vec4D(_mRotation[1][2] - _mRotation[2][1], _mRotation[2][0] - _mRotation[0][2], _mRotation[0][1] - _mRotation[1][0], dSum);
			}
		}

		m_vQuat *= 0.5 / sqrt(dSum);
	}

	[[nodiscard]] HC_INLINE double operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	[[nodiscard]] HC_INLINE double& operator[](int _iNdx) { return m_vQuat[_iNdx]; }
};

[[nodiscard]] HC_INLINE QuaternionD operator+(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return QuaternionD(_qLeft.m_vQuat + _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionD operator-(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return QuaternionD(_qLeft.m_vQuat - _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionD operator*(const QuaternionD& _qLeft, double _dRight) { return QuaternionD(_qLeft.m_vQuat * _dRight); }
[[nodiscard]] HC_INLINE QuaternionD operator*(double _dLeft, const QuaternionD& _qRight) { return QuaternionD(_qRight.m_vQuat * _dLeft); }
[[nodiscard]] HC_INLINE QuaternionD operator/(const QuaternionD& _qLeft, double _dRight) { return QuaternionD(_qLeft.m_vQuat / _dRight); }
[[nodiscard]] HC_INLINE QuaternionD operator/(double _dLeft, const QuaternionD& _qRight) { return QuaternionD(_dLeft / _qRight.m_vQuat); }
HC_INLINE QuaternionD& operator+=(QuaternionD& _qLeft, const QuaternionD& _qRight) { _qLeft = _qLeft + _qRight; return _qLeft; }
HC_INLINE QuaternionD& operator-=(QuaternionD& _qLeft, const QuaternionD& _qRight) { _qLeft = _qLeft - _qRight; return _qLeft; }
HC_INLINE QuaternionD& operator*=(QuaternionD& _qLeft, double _dRight) { _qLeft = _qLeft * _dRight; return _qLeft; }
HC_INLINE QuaternionD& operator/=(QuaternionD& _qLeft, double _dRight) { _qLeft = _qLeft / _dRight; return _qLeft; }
[[nodiscard]] HC_INLINE QuaternionD operator~(const QuaternionD& _qQuat) { return QuaternionD(); }
[[nodiscard]] HC_INLINE QuaternionD operator-(const QuaternionD& _qQuat) { return QuaternionD(-_qQuat.x, -_qQuat.y, -_qQuat.z, -_qQuat.w); }
HC_INLINE bool operator==(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat == _qRight.m_vQuat; }
HC_INLINE bool operator<(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat < _qRight.m_vQuat; }
HC_INLINE bool operator>(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat > _qRight.m_vQuat; }
HC_INLINE bool operator<=(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat <= _qRight.m_vQuat; }
HC_INLINE bool operator>=(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat >= _qRight.m_vQuat; }
HC_INLINE bool operator!=(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft.m_vQuat != _qRight.m_vQuat; }
[[nodiscard]] HC_INLINE double Sum(const QuaternionD& _qQuat) { return _qQuat.x + _qQuat.y + _qQuat.z + _qQuat.w; }
[[nodiscard]] HC_INLINE double Dot(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return Sum(_qLeft + _qRight); }
[[nodiscard]] HC_INLINE double Length(const QuaternionD& _qQuat) { return Length(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE double LengthSquared(const QuaternionD& _qQuat) { return LengthSquared(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionD Normalize(const QuaternionD& _qQuat) { return Normalize(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionD Cross(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return Cross(_qLeft.m_vQuat, _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionD Conjugate(const QuaternionD& _qQuat) { return QuaternionD(-_qQuat.x, -_qQuat.y, -_qQuat.z, _qQuat.w); }

[[nodiscard]] HC_INLINE QuaternionD operator*(const QuaternionD& _qLeft, const QuaternionD& _qRight) {
	return QuaternionD(_qLeft.w * _qRight.x + _qLeft.x * _qRight.w + _qLeft.y * _qRight.z - _qLeft.z * _qRight.y,
		_qLeft.w * _qRight.y - _qLeft.x * _qRight.z + _qLeft.y * _qRight.w + _qLeft.z * _qRight.x,
		_qLeft.w * _qRight.z + _qLeft.x * _qRight.y - _qLeft.y * _qRight.x + _qLeft.z * _qRight.w,
		_qLeft.w * _qRight.w - _qLeft.x * _qRight.x - _qLeft.y * _qRight.y - _qLeft.z * _qRight.z);
}

[[nodiscard]] HC_INLINE QuaternionD operator/(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return _qLeft * (1.0f / _qRight); }
[[nodiscard]] HC_INLINE Vec3D operator*(const QuaternionD& _qLeft, const Vec3D& _vRight) { return (_qLeft * QuaternionD(Vec4D(_vRight, 0.0f)) * Conjugate(_qLeft)).m_vQuat.XYZ(); }
[[nodiscard]] HC_INLINE Vec3D operator*(const Vec3D& _vLeft, const QuaternionD& _qRight) { return (_qRight * QuaternionD(Vec4D(_vLeft, 0.0f)) * Conjugate(_qRight)).m_vQuat.XYZ(); }
[[nodiscard]] HC_INLINE Vec4D operator*(const QuaternionD& _qLeft, const Vec4D& _vRight) { return Vec4D(_qLeft * _vRight.XYZ(), _vRight.w); }
[[nodiscard]] HC_INLINE Vec4D operator*(const Vec4D& _vLeft, const QuaternionD& _qRight) { return Vec4D(_qRight * _vLeft.XYZ(), _vLeft.w); }
HC_INLINE QuaternionD& operator*=(QuaternionD& _qLeft, const QuaternionD& _qRight) { _qLeft = _qLeft * _qRight; return _qLeft; }
HC_INLINE QuaternionD& operator/=(QuaternionD& _qLeft, const QuaternionD& _qRight) { _qLeft = _qLeft / _qRight; return _qLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, const QuaternionD& _qRight) { _vLeft = _vLeft * _qRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, const QuaternionD& _qRight) { _vLeft = _vLeft * _qRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec4D RotateByQuaternion(Vec4D _vVector, const QuaternionD& _qRotation) { return _vVector * _qRotation; }

[[nodiscard]] HC_INLINE QuaternionD Inverse(const QuaternionD& _qQuat) {
	QuaternionD qConj = Conjugate(_qQuat);

	double dLen = Length(_qQuat);

	if (HC_DOUBLE_COMPARE(dLen, 0.0)) { //Zero magnitude, return a zero Quaternion. This will indicate an error pretty quick.
		return QuaternionD();
	}

	dLen *= dLen;

	return QuaternionD(qConj.x / dLen, qConj.y / dLen, qConj.z / dLen, qConj.w);
}

[[nodiscard]] HC_INLINE MatrixD ExtractMatrix(const QuaternionD& _qQuat) {
	MatrixD mRotationMat;

	mRotationMat[0] = Vec4D(1.0 - 2.0 * (_qQuat.y * _qQuat.y) - 2.0 * (_qQuat.z * _qQuat.z),
							2.0 * _qQuat.x * _qQuat.y - 2.0 * _qQuat.w * _qQuat.z,
							2.0 * _qQuat.x * _qQuat.z + 2.0 * _qQuat.w * _qQuat.y, 0.0);
	mRotationMat[1] = Vec4D(2.0 * _qQuat.x * _qQuat.y + 2.0 * _qQuat.w * _qQuat.z,
							1.0 - 2.0 * (_qQuat.x * _qQuat.x) - 2.0 * (_qQuat.z * _qQuat.z),
							2.0 * _qQuat.y * _qQuat.z - 2.0 * _qQuat.w * _qQuat.x, 0.0);
	mRotationMat[2] = Vec4D(2.0 * _qQuat.x * _qQuat.z - 2.0 * _qQuat.w * _qQuat.y,
							2.0 * _qQuat.y * _qQuat.z + 2.0 * _qQuat.w * _qQuat.x,
							1.0 - 2.0f * (_qQuat.x * _qQuat.x) - 2.0 * (_qQuat.y * _qQuat.y), 0.0);
	mRotationMat[3] = Vec4D(0.0, 0.0, 0.0, 1.0);

	return mRotationMat;
}

[[nodiscard]] HC_INLINE Vec3D ExtractEulerAngles(const QuaternionD& _qQuat) {
	Vec3D vEulerAngles;
	double dSin, dCos;

	//Roll
	dSin = 2.0 * (_qQuat.w * _qQuat.x + _qQuat.y * _qQuat.z);
	dCos = 1.0 - 2.0 * (_qQuat.x * _qQuat.x + _qQuat.y * _qQuat.y);
	vEulerAngles.x = atan2(dSin, dCos);

	//Pitch
	dSin = sqrt(1.0 + 2.0 * (_qQuat.w * _qQuat.y - _qQuat.x * _qQuat.z));
	dCos = sqrt(1.0 - 2.0 * (_qQuat.w * _qQuat.y - _qQuat.x * _qQuat.z));
	vEulerAngles.y = 2.0 * atan2(dSin, dCos) - HC_PI / 2.0;

	//Yaw
	dSin = 2.0 * (_qQuat.w * _qQuat.z + _qQuat.x * _qQuat.y);
	dCos = 1.0 - 2.0 * (_qQuat.y * _qQuat.y + _qQuat.z * _qQuat.z);
	vEulerAngles.z = atan2(dSin, dCos);

	return vEulerAngles;
}

#endif