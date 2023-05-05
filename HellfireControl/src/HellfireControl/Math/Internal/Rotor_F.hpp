#pragma once

#include <HellfireControl/Math/Internal/Rotor_Common.hpp>

#if HC_USE_SIMD

struct RotorF {
	//TODO: Implement SIMD (requires new SIMD backend)
};

#else

struct HC_ALIGNAS(16) RotorF {
	union {
		Vec4F m_vRot = Vec4F();

		struct {
			float b01;
			float b02;
			float b12;
			float a;
		};
	};

	HC_INLINE RotorF() : m_vRot(0.0f, 0.0f, 0.0f, 1.0f) {}
	HC_INLINE RotorF(const Vec4F& _vRot) : m_vRot(_vRot) {}
	HC_INLINE explicit RotorF(float _fA, const Vec3F& _vBV) : m_vRot(_vBV, _fA) {}
	HC_INLINE explicit RotorF(float _fB01, float _fB02, float _fB12, float _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorF(int _fB01, int _fB02, int _fB12, int _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorF(double _fB01, double _fB02, double _fB12, double _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}

	HC_INLINE explicit RotorF(float _fRoll, float _fPitch, float _fYaw) {
		float fCosRoll = cosf(_fRoll * 0.5f);
		float fSinRoll = sinf(_fRoll * 0.5f);
		float fCosPitch = cosf(_fPitch * 0.5f);
		float fSinPitch = sinf(_fPitch * 0.5f);
		float fCosYaw = cosf(_fYaw * 0.5f);
		float fSinYaw = sinf(_fYaw * 0.5f);

		m_vRot = Vec4F(-(fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw),
					   -(fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw),
					   -(fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw),
					   fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw);
	}
	
	HC_INLINE explicit RotorF(const Vec3F& _vEulerAngles) {
		float fCosRoll = cosf(_vEulerAngles.x * 0.5f);
		float fSinRoll = sinf(_vEulerAngles.x * 0.5f);
		float fCosPitch = cosf(_vEulerAngles.y * 0.5f);
		float fSinPitch = sinf(_vEulerAngles.y * 0.5f);
		float fCosYaw = cosf(_vEulerAngles.z * 0.5f);
		float fSinYaw = sinf(_vEulerAngles.z * 0.5f);

		m_vRot = Vec4F(-(fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw),
					   -(fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw),
					   -(fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw),
					   fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw);
	}

	HC_INLINE explicit RotorF(float _fAngle, const Vec3F& _vBiVector) {
		Vec3F vVec = Normalize(_vBiVector);

		float fSin = sinf(_fAngle * 0.5f);
		m_vRot.w = cosf(_fAngle * 0.5f);
		m_vRot.x = -fSin * vVec.x;
		m_vRot.y = -fSin * vVec.y;
		m_vRot.z = -fSin * vVec.z;
	}

	HC_INLINE explicit RotorF(const Vec3F& _vFrom, const Vec3F& _vTo) {
		Vec3F v = _vTo ^ _vFrom;

		m_vRot.w = 1.0f + Dot(_vTo, _vFrom);
		m_vRot.x = v.x;
		m_vRot.y = v.y;
		m_vRot.z = v.z;

		m_vRot = Normalize(m_vRot);
	}

	HC_INLINE explicit RotorF(const Vec4F& _vFrom, const Vec4F& _vTo) {
		Vec3F v = _vTo.XYZ() ^ _vFrom.XYZ();
		v = Normalize(v);

		m_vRot.w = 1.0f + Dot(_vTo, _vFrom);
		m_vRot.x = v.x;
		m_vRot.y = v.y;
		m_vRot.z = v.z;

		m_vRot = Normalize(m_vRot);
	}
};

[[nodiscard]] HC_INLINE RotorF Reverse(const RotorF& _rRot) { return RotorF(-_rRot.b01, -_rRot.b02, -_rRot.b12, _rRot.a); }
[[nodiscard]] HC_INLINE float Length(const RotorF& _rRot) { return Length(_rRot.m_vRot); }
[[nodiscard]] HC_INLINE float LengthSquared(const RotorF& _rRot) { return LengthSquared(_rRot.m_vRot); }
[[nodiscard]] HC_INLINE RotorF Normalize(const RotorF& _rRot) { return Normalize(_rRot.m_vRot); }

[[nodiscard]] HC_INLINE RotorF operator*(const RotorF& _rLeft, const RotorF& _rRight) {
	return RotorF(_rLeft.b01 * _rRight.a + _rLeft.a * _rRight.b01 + _rLeft.b12 * _rRight.b02 - _rLeft.b02 * _rRight.b12,
				  _rLeft.b02 * _rRight.a + _rLeft.a * _rRight.b02 - _rLeft.b12 * _rRight.b01 + _rLeft.b01 * _rRight.b12,
				  _rLeft.b12 * _rRight.a + _rLeft.a * _rRight.b12 + _rLeft.b02 * _rRight.b01 - _rLeft.b01 * _rRight.b02,
				  _rLeft.a * _rRight.a - _rLeft.b01 * _rRight.b01 - _rLeft.b02 * _rRight.b02 - _rLeft.b12 * _rRight.b12);
}

[[nodiscard]] HC_INLINE Vec3F RotateByRotor(const Vec3F& _vVector, const RotorF& _rRot) {
	const float fX = _rRot.a * _vVector.x + _rRot.b01 * _vVector.y - _rRot.b02 * _vVector.z;
	const float fY = _rRot.a * _vVector.y - _rRot.b01 * _vVector.x + _rRot.b12 * _vVector.z;
	const float fZ = _rRot.a * _vVector.z - _rRot.b12 * _vVector.y + _rRot.b02 * _vVector.x;
	const float fXYZ = _rRot.b01 * _vVector.z + _rRot.b12 * _vVector.x + _rRot.b02 * _vVector.y;

	Vec3F vVec;
	vVec.x = fX * _rRot.a + fY * _rRot.b01 + fXYZ * _rRot.b12 - fZ * _rRot.b02;
	vVec.y = fY * _rRot.a - fX * _rRot.b01 + fZ * _rRot.b12 + fXYZ * _rRot.b02;
	vVec.z = fZ * _rRot.a + fXYZ * _rRot.b01 - fY * _rRot.b12 + fX * _rRot.b02;
	return vVec;
}

[[nodiscard]] HC_INLINE Vec4F RotateByRotor(const Vec4F& _vVector, const RotorF& _rRot) {
	const float fX = _rRot.a * _vVector.x + _rRot.b01 * _vVector.y - _rRot.b02 * _vVector.z;
	const float fY = _rRot.a * _vVector.y - _rRot.b01 * _vVector.x + _rRot.b12 * _vVector.z;
	const float fZ = _rRot.a * _vVector.z - _rRot.b12 * _vVector.y + _rRot.b02 * _vVector.x;
	const float fXYZ = _rRot.b01 * _vVector.z + _rRot.b12 * _vVector.x + _rRot.b02 * _vVector.y;

	Vec4F vVec;
	vVec.x = fX * _rRot.a + fY * _rRot.b01 + fXYZ * _rRot.b12 - fZ * _rRot.b02;
	vVec.y = fY * _rRot.a - fX * _rRot.b01 + fZ * _rRot.b12 + fXYZ * _rRot.b02;
	vVec.z = fZ * _rRot.a + fXYZ * _rRot.b01 - fY * _rRot.b12 + fX * _rRot.b02;
	vVec.w = _vVector.w;
	return vVec;
}

[[nodiscard]] HC_INLINE Vec3F operator*(const Vec3F& _vLeft, const RotorF& _rRight) { return RotateByRotor(_vLeft, _rRight); }
[[nodiscard]] HC_INLINE Vec3F operator*(const RotorF& _rLeft, const Vec3F& _vRight) { return RotateByRotor(_vRight, _rLeft); }
[[nodiscard]] HC_INLINE Vec4F operator*(const Vec4F& _vLeft, const RotorF& _rRight) { return RotateByRotor(_vLeft, _rRight); }
[[nodiscard]] HC_INLINE Vec4F operator*(const RotorF& _rLeft, const Vec4F& _vRight) { return RotateByRotor(_vRight, _rLeft); }

HC_INLINE RotorF& operator*=(RotorF& _rLeft, const RotorF& _rRight) { _rLeft = _rLeft * _rRight; return _rLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, const RotorF& _rRight) { _vLeft = _vLeft * _rRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, const RotorF& _rRight) { _vLeft = _vLeft * _rRight; return _vLeft; }

[[nodiscard]] HC_INLINE MatrixF ExtractMatrix(const RotorF& _rRot) {
	MatrixF mMat = IdentityF();

	mMat[0] = RotateByRotor(mMat[0], _rRot);
	mMat[1] = RotateByRotor(mMat[1], _rRot);
	mMat[2] = RotateByRotor(mMat[2], _rRot);

	return mMat;
}

[[nodiscard]] HC_INLINE Vec3F ExtractEulerAngles(const RotorF& _rRot) {
	Vec3F vEulerAngles;
	float fSin, fCos;

	//TODO: Optimize later! This is a copy of the code from Quaternion, with an extra conversion applied to use a rotor as a
	//quaternion. This would be easiest as a series of swizzles.

	Vec4F vQuat = Reverse(_rRot.m_vRot.YXZW()).m_vRot; //Quick conversion to a "quaternion" for the euler calculations

	//Roll
	fSin = 2.0f * (vQuat.w * vQuat.x + vQuat.y * vQuat.z);
	fCos = 1.0f - 2.0f * (vQuat.x * vQuat.x + vQuat.y * vQuat.y);
	vEulerAngles.x = atan2f(fSin, fCos);

	//Pitch
	fSin = sqrtf(1.0f + 2.0f * (vQuat.w * vQuat.y - vQuat.x * vQuat.z));
	fCos = sqrtf(1.0f - 2.0f * (vQuat.w * vQuat.y - vQuat.x * vQuat.z));
	vEulerAngles.y = 2.0f * atan2f(fSin, fCos) - HC_PI / 2.0f;

	//Yaw
	fSin = 2.0f * (vQuat.w * vQuat.z + vQuat.x * vQuat.y);
	fCos = 1.0f - 2.0f * (vQuat.y * vQuat.y + vQuat.z * vQuat.z);
	vEulerAngles.z = atan2f(fSin, fCos);

	return vEulerAngles;
}

#endif