#pragma once

#include <HellfireControl/Math/Internal/Rotor/Rotor_Common.hpp>

#if HC_USE_SIMD

struct RotorD {
	//TODO: Implement SIMD (requires new SIMD backend)
};

#else

struct HC_ALIGNAS(32) RotorD {
	union {
		Vec4D m_vRot = Vec4D();

		struct {
			double b01;
			double b02;
			double b12;
			double a;
		};
	};

	HC_INLINE RotorD() : m_vRot(0.0f, 0.0f, 0.0f, 1.0f) {}
	HC_INLINE RotorD(const Vec4D & _vRot) : m_vRot(_vRot) {}
	HC_INLINE RotorD(const RotorD& _rRot) : m_vRot(_rRot.m_vRot) {}
	HC_INLINE explicit RotorD(double _dA, const Vec3D & _vBV) : m_vRot(_vBV, _dA) {}
	HC_INLINE explicit RotorD(float _fB01, float _fB02, float _fB12, float _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorD(int _fB01, int _fB02, int _fB12, int _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorD(double _fB01, double _fB02, double _fB12, double _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}

	HC_INLINE explicit RotorD(double _fRoll, double _fPitch, double _fYaw) {
		double dCosRoll = cos(_fRoll * 0.5);
		double dSinRoll = sin(_fRoll * 0.5);
		double dCosPitch = cos(_fPitch * 0.5);
		double dSinPitch = sin(_fPitch * 0.5);
		double dCosYaw = cos(_fYaw * 0.5);
		double dSinYaw = sin(_fYaw * 0.5);

		m_vRot = Vec4D(-(dCosRoll * dCosPitch * dSinYaw - dSinRoll * dSinPitch * dCosYaw),
					   -(dCosRoll * dSinPitch * dCosYaw + dSinRoll * dCosPitch * dSinYaw),
					   -(dSinRoll * dCosPitch * dCosYaw - dCosRoll * dSinPitch * dSinYaw),
					   dCosRoll * dCosPitch * dCosYaw + dSinRoll * dSinPitch * dSinYaw);
	}

	HC_INLINE explicit RotorD(const Vec3D & _vEulerAngles) {
		double dCosRoll = cos(_vEulerAngles.x * 0.5);
		double dSinRoll = sin(_vEulerAngles.x * 0.5);
		double dCosPitch = cos(_vEulerAngles.y * 0.5);
		double dSinPitch = sin(_vEulerAngles.y * 0.5);
		double dCosYaw = cos(_vEulerAngles.z * 0.5);
		double dSinYaw = sin(_vEulerAngles.z * 0.5);

		m_vRot = Vec4D(-(dCosRoll * dCosPitch * dSinYaw - dSinRoll * dSinPitch * dCosYaw),
					   -(dCosRoll * dSinPitch * dCosYaw + dSinRoll * dCosPitch * dSinYaw),
					   -(dSinRoll * dCosPitch * dCosYaw - dCosRoll * dSinPitch * dSinYaw),
					   dCosRoll * dCosPitch * dCosYaw + dSinRoll * dSinPitch * dSinYaw);
	}

	HC_INLINE explicit RotorD(const Vec3D& _vBiVector, double _dAngle) {
		Vec3D vVec = Normalize(_vBiVector);

		double dSin = sin(_dAngle * 0.5);
		m_vRot.w = cos(_dAngle * 0.5);
		m_vRot.x = -dSin * vVec.x;
		m_vRot.y = -dSin * vVec.y;
		m_vRot.z = -dSin * vVec.z;
	}

	HC_INLINE explicit RotorD(const Vec3D & _vFrom, const Vec3D & _vTo) {
		Vec3D v = _vTo ^ _vFrom;

		m_vRot.w = 1.0 + Dot(_vTo, _vFrom);
		m_vRot.x = v.x;
		m_vRot.y = v.y;
		m_vRot.z = v.z;

		m_vRot = Normalize(m_vRot);
	}

	HC_INLINE explicit RotorD(const Vec4D & _vFrom, const Vec4D & _vTo) {
		Vec3D v = _vTo.XYZ() ^ _vFrom.XYZ();
		v = Normalize(v);

		m_vRot.w = 1.0 + Dot(_vTo, _vFrom);
		m_vRot.x = v.x;
		m_vRot.y = v.y;
		m_vRot.z = v.z;

		m_vRot = Normalize(m_vRot);
	}
};

[[nodiscard]] HC_INLINE RotorD Reverse(const RotorD& _rRot) { return RotorD(-_rRot.b01, -_rRot.b02, -_rRot.b12, _rRot.a); }
[[nodiscard]] HC_INLINE float Length(const RotorD& _rRot) { return Length(_rRot.m_vRot); }
[[nodiscard]] HC_INLINE float LengthSquared(const RotorD& _rRot) { return LengthSquared(_rRot.m_vRot); }
[[nodiscard]] HC_INLINE RotorD Normalize(const RotorD& _rRot) { return Normalize(_rRot.m_vRot); }
[[nodiscard]] HC_INLINE float Dot(const RotorD& _rLeft, const RotorD& _rRight) { return Dot(_rLeft.m_vRot, _rRight.m_vRot); }

[[nodiscard]] HC_INLINE RotorD operator*(const RotorD& _rLeft, const RotorD& _rRight) {
	return RotorD(_rLeft.b01 * _rRight.a + _rLeft.a * _rRight.b01 + _rLeft.b12 * _rRight.b02 - _rLeft.b02 * _rRight.b12,
		_rLeft.b02 * _rRight.a + _rLeft.a * _rRight.b02 - _rLeft.b12 * _rRight.b01 + _rLeft.b01 * _rRight.b12,
		_rLeft.b12 * _rRight.a + _rLeft.a * _rRight.b12 + _rLeft.b02 * _rRight.b01 - _rLeft.b01 * _rRight.b02,
		_rLeft.a * _rRight.a - _rLeft.b01 * _rRight.b01 - _rLeft.b02 * _rRight.b02 - _rLeft.b12 * _rRight.b12);
}

[[nodiscard]] HC_INLINE Vec3D RotateByRotor(const Vec3D& _vVector, const RotorD& _rRot) {
	const double dX = _rRot.a * _vVector.x + _rRot.b01 * _vVector.y - _rRot.b02 * _vVector.z;
	const double dY = _rRot.a * _vVector.y - _rRot.b01 * _vVector.x + _rRot.b12 * _vVector.z;
	const double dZ = _rRot.a * _vVector.z - _rRot.b12 * _vVector.y + _rRot.b02 * _vVector.x;
	const double dXYZ = _rRot.b01 * _vVector.z + _rRot.b12 * _vVector.x + _rRot.b02 * _vVector.y;

	Vec3D vVec;
	vVec.x = dX * _rRot.a + dY * _rRot.b01 + dXYZ * _rRot.b12 - dZ * _rRot.b02;
	vVec.y = dY * _rRot.a - dX * _rRot.b01 + dZ * _rRot.b12 + dXYZ * _rRot.b02;
	vVec.z = dZ * _rRot.a + dXYZ * _rRot.b01 - dY * _rRot.b12 + dX * _rRot.b02;
	return vVec;
}

[[nodiscard]] HC_INLINE Vec4D RotateByRotor(const Vec4D& _vVector, const RotorD& _rRot) {
	const double dX = _rRot.a * _vVector.x + _rRot.b01 * _vVector.y - _rRot.b02 * _vVector.z;
	const double dY = _rRot.a * _vVector.y - _rRot.b01 * _vVector.x + _rRot.b12 * _vVector.z;
	const double dZ = _rRot.a * _vVector.z - _rRot.b12 * _vVector.y + _rRot.b02 * _vVector.x;
	const double dXYZ = _rRot.b01 * _vVector.z + _rRot.b12 * _vVector.x + _rRot.b02 * _vVector.y;

	Vec4D vVec;
	vVec.x = dX * _rRot.a + dY * _rRot.b01 + dXYZ * _rRot.b12 - dZ * _rRot.b02;
	vVec.y = dY * _rRot.a - dX * _rRot.b01 + dZ * _rRot.b12 + dXYZ * _rRot.b02;
	vVec.z = dZ * _rRot.a + dXYZ * _rRot.b01 - dY * _rRot.b12 + dX * _rRot.b02;
	vVec.w = _vVector.w;
	return vVec;
}

[[nodiscard]] HC_INLINE Vec3D operator*(const Vec3D& _vLeft, const RotorD& _rRight) { return RotateByRotor(_vLeft, _rRight); }
[[nodiscard]] HC_INLINE Vec3D operator*(const RotorD& _rLeft, const Vec3D& _vRight) { return RotateByRotor(_vRight, _rLeft); }
[[nodiscard]] HC_INLINE Vec4D operator*(const Vec4D& _vLeft, const RotorD& _rRight) { return RotateByRotor(_vLeft, _rRight); }
[[nodiscard]] HC_INLINE Vec4D operator*(const RotorD& _rLeft, const Vec4D& _vRight) { return RotateByRotor(_vRight, _rLeft); }
[[nodiscard]] HC_INLINE RotorD operator*(const RotorD& _rLeft, double _dRight) { return RotorD(_rLeft.m_vRot * _dRight); }
[[nodiscard]] HC_INLINE RotorD operator*(double _dLeft, const RotorD& _rRight) { return RotorD(_rRight.m_vRot * _dLeft); }
[[nodiscard]] HC_INLINE RotorD operator-(const RotorD& _rRot) { return RotorD(-_rRot.m_vRot); }
[[nodiscard]] HC_INLINE RotorD operator+(const RotorD& _rLeft, const RotorD& _rRight) { return RotorD(_rLeft.m_vRot + _rRight.m_vRot); }
[[nodiscard]] HC_INLINE RotorD operator-(const RotorD& _rLeft, const RotorD& _rRight) { return RotorD(_rLeft.m_vRot - _rRight.m_vRot); }

HC_INLINE RotorD& operator*=(RotorD& _rLeft, const RotorD& _rRight) { _rLeft = _rLeft * _rRight; return _rLeft; }
HC_INLINE RotorD& operator+=(RotorD& _rLeft, const RotorD& _rRight) { _rLeft = _rLeft + _rRight; return _rLeft; }
HC_INLINE RotorD& operator-=(RotorD& _rLeft, const RotorD& _rRight) { _rLeft = _rLeft - _rRight; return _rLeft; }
HC_INLINE RotorD& operator*=(RotorD& _rLeft, double _dRight) { _rLeft = _rLeft * _dRight; return _rLeft; }
HC_INLINE Vec3D& operator*=(Vec3D& _vLeft, const RotorD& _rRight) { _vLeft = _vLeft * _rRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, const RotorD& _rRight) { _vLeft = _vLeft * _rRight; return _vLeft; }

[[nodiscard]] HC_INLINE MatrixD ExtractMatrix(const RotorD& _rRot) {
	MatrixD mMat = IdentityD();

	mMat[0] = RotateByRotor(mMat[0], _rRot);
	mMat[1] = RotateByRotor(mMat[1], _rRot);
	mMat[2] = RotateByRotor(mMat[2], _rRot);

	return mMat;
}

[[nodiscard]] HC_INLINE Vec3D ExtractEulerAngles(const RotorD& _rRot) {
	Vec3D vEulerAngles;
	double dSin, dCos;

	//TODO: Optimize later! This is a copy of the code from Quaternion, with an extra conversion applied to use a rotor as a
	//quaternion. This would be easiest as a series of swizzles.

	Vec4D vQuat = Reverse(_rRot.m_vRot.YXZW()).m_vRot; //Quick conversion to a "quaternion" for the euler calculations

	//Roll
	dSin = 2.0 * (vQuat.w * vQuat.x + vQuat.y * vQuat.z);
	dCos = 1.0 - 2.0 * (vQuat.x * vQuat.x + vQuat.y * vQuat.y);
	vEulerAngles.x = atan2(dSin, dCos);

	//Pitch
	dSin = sqrt(1.0 + 2.0 * (vQuat.w * vQuat.y - vQuat.x * vQuat.z));
	dCos = sqrt(1.0 - 2.0 * (vQuat.w * vQuat.y - vQuat.x * vQuat.z));
	vEulerAngles.y = 2.0 * atan2(dSin, dCos) - HC_PI / 2.0;

	//Yaw
	dSin = 2.0 * (vQuat.w * vQuat.z + vQuat.x * vQuat.y);
	dCos = 1.0 - 2.0 * (vQuat.y * vQuat.y + vQuat.z * vQuat.z);
	vEulerAngles.z = atan2(dSin, dCos);

	return vEulerAngles;
}


#endif