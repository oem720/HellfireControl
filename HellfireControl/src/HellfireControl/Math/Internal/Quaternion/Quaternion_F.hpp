#pragma once

#include <HellfireControl/Math/Internal/Quaternion/Quaternion_Common.hpp>

#if HC_USE_SIMD

struct QuaternionF {
	Vec4F m_vQuat;

	HC_INLINE HC_VECTORCALL QuaternionF() {}
	HC_INLINE HC_VECTORCALL QuaternionF(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4F(_fX, _fY, _fZ, _fW); }
	HC_INLINE HC_VECTORCALL QuaternionF(int _fX, int _fY, int _fZ, int _fW) { m_vQuat = Vec4F(static_cast<float>(_fX), static_cast<float>(_fY), static_cast<float>(_fZ), static_cast<float>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionF(double _fX, double _fY, double _fZ, double _fW) { m_vQuat = Vec4F(static_cast<float>(_fX), static_cast<float>(_fY), static_cast<float>(_fZ), static_cast<float>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionF(MatrixF _mMat) {
		//FIXME: All of this is god-awful unoptimized crap. Make into optimized SIMD code ASAP! - Owen
		float fSum = 0.0f;
		if (_mMat[2][2] < 0.0f) {
			if (_mMat[0][0] > _mMat[1][1]) {
				fSum = 1.0f + _mMat[0][0] - _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4F(fSum, _mMat[0][1] + _mMat[1][0], _mMat[2][0] + _mMat[0][2], _mMat[1][2] - _mMat[2][2]);
			}
			else {
				fSum = 1.0f - _mMat[0][0] + _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4F(_mMat[0][1] + _mMat[1][0], fSum, _mMat[1][2] + _mMat[2][1], _mMat[2][0] - _mMat[0][2]);
			}
		}
		else {
			if (_mMat[0][0] < _mMat[1][1]) {
				fSum = 1.0f - _mMat[0][0] - _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4F(_mMat[2][0] + _mMat[0][2], _mMat[1][2] + _mMat[2][1], fSum, _mMat[0][1] - _mMat[1][0]);
			}
			else {
				fSum = 1.0f + _mMat[0][0] + _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4F(_mMat[1][2] - _mMat[2][1], _mMat[2][0] - _mMat[0][2], _mMat[0][1] - _mMat[1][0], fSum);
			}
		}

		m_vQuat *= 0.5f / sqrtf(fSum);
	}
	HC_INLINE float HC_VECTORCALL operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	HC_INLINE float& HC_VECTORCALL operator[](int _iNdx) { return m_vQuat[_iNdx]; }
	HC_INLINE float HC_VECTORCALL X() const { return m_vQuat.X(); }
	HC_INLINE float HC_VECTORCALL Y() const { return m_vQuat.Y(); }
	HC_INLINE float HC_VECTORCALL Z() const { return m_vQuat.Z(); }
	HC_INLINE float HC_VECTORCALL W() const { return m_vQuat.W(); }
	HC_INLINE void HC_VECTORCALL SetX(float _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void HC_VECTORCALL SetY(float _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void HC_VECTORCALL SetZ(float _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void HC_VECTORCALL SetW(float _fW) { m_vQuat.SetW(_fW); }
};

#else

struct HC_ALIGNAS(16) QuaternionF
{
	union {
		Vec4F m_vQuat;

		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};

	HC_INLINE QuaternionF() : m_vQuat() {}
	HC_INLINE QuaternionF(const Vec4F& _vQuat) : m_vQuat(_vQuat) {}
	HC_INLINE explicit QuaternionF(float _fX, float _fY, float _fZ, float _fW) : m_vQuat(_fX, _fY, _fZ, _fW) {}
	HC_INLINE explicit QuaternionF(int _iX, int _iY, int _iZ, int _iW) : m_vQuat(_iX, _iY, _iZ, _iW) {}
	HC_INLINE explicit QuaternionF(double _dX, double _dY, double _dZ, double _dW) : m_vQuat(_dX, _dY, _dZ, _dW) {}

	HC_INLINE explicit QuaternionF(float _fRoll, float _fPitch, float _fYaw) {
		float fCosRoll = cosf(_fRoll * 0.5f);
		float fSinRoll = sinf(_fRoll * 0.5f);
		float fCosPitch = cosf(_fPitch * 0.5f);
		float fSinPitch = sinf(_fPitch * 0.5f);
		float fCosYaw = cosf(_fYaw * 0.5f);
		float fSinYaw = sinf(_fYaw * 0.5f);

		m_vQuat = Vec4F(fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw,
						fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw,
						fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw,
						fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw);
	}

	HC_INLINE explicit QuaternionF(const Vec3F& _vEulerAngles) {
		float fCosRoll = cosf(_vEulerAngles.x * 0.5f);
		float fSinRoll = sinf(_vEulerAngles.x * 0.5f);
		float fCosPitch = cosf(_vEulerAngles.y * 0.5f);
		float fSinPitch = sinf(_vEulerAngles.y * 0.5f);
		float fCosYaw = cosf(_vEulerAngles.z * 0.5f);
		float fSinYaw = sinf(_vEulerAngles.z * 0.5f);

		m_vQuat = Vec4F(fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw,
						fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw,
						fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw,
						fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw);
	}

	HC_INLINE explicit QuaternionF(const Vec3F& _vAxis, float _fAngle)
	{
		float fSin = sinf(_fAngle * 0.5f);
		m_vQuat = Vec4F(fSin * _vAxis.x, fSin * _vAxis.y, fSin * _vAxis.z, cosf(_fAngle * 0.5f));
	}

	HC_INLINE explicit QuaternionF(const MatrixF& _mRotation) {
		float fSum = 0.0f;
		if (_mRotation[2][2] < 0.0f) {
			if (_mRotation[0][0] > _mRotation[1][1]) {
				fSum = 1.0f + _mRotation[0][0] - _mRotation[1][1] - _mRotation[2][2];
				m_vQuat = Vec4F(fSum, _mRotation[0][1] + _mRotation[1][0], _mRotation[2][0] + _mRotation[0][2], _mRotation[1][2] - _mRotation[2][2]);
			}
			else {
				fSum = 1.0f - _mRotation[0][0] + _mRotation[1][1] - _mRotation[2][2];
				m_vQuat = Vec4F(_mRotation[0][1] + _mRotation[1][0], fSum, _mRotation[1][2] + _mRotation[2][1], _mRotation[2][0] - _mRotation[0][2]);
			}
		}
		else {
			if (_mRotation[0][0] < _mRotation[1][1]) {
				fSum = 1.0f - _mRotation[0][0] - _mRotation[1][1] + _mRotation[2][2];
				m_vQuat = Vec4F(_mRotation[2][0] + _mRotation[0][2], _mRotation[1][2] + _mRotation[2][1], fSum, _mRotation[0][1] - _mRotation[1][0]);
			}
			else {
				fSum = 1.0f + _mRotation[0][0] + _mRotation[1][1] + _mRotation[2][2];
				m_vQuat = Vec4F(_mRotation[1][2] - _mRotation[2][1], _mRotation[2][0] - _mRotation[0][2], _mRotation[0][1] - _mRotation[1][0], fSum);
			}
		}

		m_vQuat *= 0.5f / sqrtf(fSum);
	}

	[[nodiscard]] HC_INLINE float operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	[[nodiscard]] HC_INLINE float& operator[](int _iNdx) { return m_vQuat[_iNdx]; }
};

[[nodiscard]] HC_INLINE QuaternionF operator+(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return QuaternionF(_qLeft.m_vQuat + _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionF operator-(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return QuaternionF(_qLeft.m_vQuat - _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionF operator*(const QuaternionF& _qLeft, float _fRight) { return QuaternionF(_qLeft.m_vQuat * _fRight); }
[[nodiscard]] HC_INLINE QuaternionF operator*(float _fLeft, const QuaternionF& _qRight) { return QuaternionF(_qRight.m_vQuat *  _fLeft); }
[[nodiscard]] HC_INLINE QuaternionF operator/(const QuaternionF& _qLeft, float _fRight) { return QuaternionF(_qLeft.m_vQuat / _fRight); }
[[nodiscard]] HC_INLINE QuaternionF operator/(float _fLeft, const QuaternionF& _qRight) { return QuaternionF(_fLeft / _qRight.m_vQuat); }
HC_INLINE QuaternionF& operator+=(QuaternionF& _qLeft, const QuaternionF& _qRight) { _qLeft = _qLeft + _qRight; return _qLeft; }
HC_INLINE QuaternionF& operator-=(QuaternionF& _qLeft, const QuaternionF& _qRight) { _qLeft = _qLeft - _qRight; return _qLeft; }
HC_INLINE QuaternionF& operator*=(QuaternionF& _qLeft, float _fRight) { _qLeft = _qLeft * _fRight; return _qLeft; }
HC_INLINE QuaternionF& operator/=(QuaternionF& _qLeft, float _fRight) { _qLeft = _qLeft / _fRight; return _qLeft; }
[[nodiscard]] HC_INLINE QuaternionF operator~(const QuaternionF& _qQuat) { return QuaternionF(); }
[[nodiscard]] HC_INLINE QuaternionF operator-(const QuaternionF& _qQuat) { return QuaternionF(-_qQuat.x, -_qQuat.y, -_qQuat.z, -_qQuat.w); }
HC_INLINE bool operator==(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat == _qRight.m_vQuat; }
HC_INLINE bool operator<(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat < _qRight.m_vQuat; }
HC_INLINE bool operator>(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat > _qRight.m_vQuat; }
HC_INLINE bool operator<=(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat <= _qRight.m_vQuat; }
HC_INLINE bool operator>=(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat >= _qRight.m_vQuat; }
HC_INLINE bool operator!=(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft.m_vQuat != _qRight.m_vQuat; }
[[nodiscard]] HC_INLINE float Sum(const QuaternionF& _qQuat) { return _qQuat.x + _qQuat.y + _qQuat.z + _qQuat.w; }
[[nodiscard]] HC_INLINE float Dot(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return Sum(_qLeft + _qRight); }
[[nodiscard]] HC_INLINE float Length(const QuaternionF& _qQuat) { return Length(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE float LengthSquared(const QuaternionF& _qQuat) { return LengthSquared(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionF Normalize(const QuaternionF& _qQuat) { return Normalize(_qQuat.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionF Cross(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return Cross(_qLeft.m_vQuat, _qRight.m_vQuat); }
[[nodiscard]] HC_INLINE QuaternionF Conjugate(const QuaternionF& _qQuat) { return QuaternionF(-_qQuat.x, -_qQuat.y, -_qQuat.z, _qQuat.w); }

[[nodiscard]] HC_INLINE QuaternionF operator*(const QuaternionF& _qLeft, const QuaternionF& _qRight) {
	return QuaternionF(_qLeft.w * _qRight.x + _qLeft.x * _qRight.w + _qLeft.y * _qRight.z - _qLeft.z * _qRight.y,
		_qLeft.w * _qRight.y - _qLeft.x * _qRight.z + _qLeft.y * _qRight.w + _qLeft.z * _qRight.x,
		_qLeft.w * _qRight.z + _qLeft.x * _qRight.y - _qLeft.y * _qRight.x + _qLeft.z * _qRight.w,
		_qLeft.w * _qRight.w - _qLeft.x * _qRight.x - _qLeft.y * _qRight.y - _qLeft.z * _qRight.z);
}

[[nodiscard]] HC_INLINE QuaternionF operator/(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return _qLeft * (1.0f / _qRight); }
[[nodiscard]] HC_INLINE Vec3F operator*(const QuaternionF& _qLeft, const Vec3F& _vRight) { return (_qLeft * QuaternionF(Vec4F(_vRight, 0.0f)) * Conjugate(_qLeft)).m_vQuat.XYZ(); }
[[nodiscard]] HC_INLINE Vec3F operator*(const Vec3F& _vLeft, const QuaternionF& _qRight) { return (_qRight * QuaternionF(Vec4F(_vLeft, 0.0f)) * Conjugate(_qRight)).m_vQuat.XYZ(); }
[[nodiscard]] HC_INLINE Vec4F operator*(const QuaternionF& _qLeft, const Vec4F& _vRight) { return Vec4F(_qLeft * _vRight.XYZ(), _vRight.w); }
[[nodiscard]] HC_INLINE Vec4F operator*(const Vec4F& _vLeft, const QuaternionF& _qRight) { return Vec4F(_qRight * _vLeft.XYZ(), _vLeft.w); }
HC_INLINE QuaternionF& operator*=(QuaternionF& _qLeft, const QuaternionF& _qRight) { _qLeft = _qLeft * _qRight; return _qLeft; }
HC_INLINE QuaternionF& operator/=(QuaternionF& _qLeft, const QuaternionF& _qRight) { _qLeft = _qLeft / _qRight; return _qLeft; }
HC_INLINE Vec3F& operator*=(Vec3F& _vLeft, const QuaternionF& _qRight) { _vLeft = _vLeft * _qRight; return _vLeft; }
HC_INLINE Vec4F& operator*=(Vec4F& _vLeft, const QuaternionF& _qRight) { _vLeft = _vLeft * _qRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec3F RotateByQuaternion(const Vec3F& _vVector, const QuaternionF& _qRotation) { return _vVector * _qRotation; }
[[nodiscard]] HC_INLINE Vec4F RotateByQuaternion(const Vec4F& _vVector, const QuaternionF& _qRotation) { return _vVector * _qRotation; }

[[nodiscard]] HC_INLINE QuaternionF Inverse(const QuaternionF& _qQuat) {
	QuaternionF qConj = Conjugate(_qQuat);

	float fLen = Length(_qQuat);

	if (HC_FLOAT_COMPARE(fLen, 0.0f)) { //Zero magnitude, return a zero Quaternion. This will indicate an error pretty quick.
		return QuaternionF();
	}

	fLen *= fLen;

	return QuaternionF(qConj.x / fLen, qConj.y / fLen, qConj.z / fLen, qConj.w);
}

[[nodiscard]] HC_INLINE MatrixF ExtractMatrix(const QuaternionF& _qQuat) {
	MatrixF mRotationMat;

	mRotationMat[0] = Vec4F(1.0f - 2.0f * (_qQuat.y * _qQuat.y) - 2.0f * (_qQuat.z * _qQuat.z),
							2.0f * _qQuat.x * _qQuat.y - 2.0f * _qQuat.w * _qQuat.z,
							2.0f * _qQuat.x * _qQuat.z + 2.0f * _qQuat.w * _qQuat.y, 0.0f);
	mRotationMat[1] = Vec4F(2.0f * _qQuat.x * _qQuat.y + 2.0f * _qQuat.w * _qQuat.z,
							1.0f - 2.0f * (_qQuat.x * _qQuat.x) - 2.0f * (_qQuat.z * _qQuat.z),
							2.0f * _qQuat.y * _qQuat.z - 2.0f * _qQuat.w * _qQuat.x, 0.0f);
	mRotationMat[2] = Vec4F(2.0f * _qQuat.x * _qQuat.z - 2.0f * _qQuat.w * _qQuat.y,
							2.0f * _qQuat.y * _qQuat.z + 2.0f * _qQuat.w * _qQuat.x,
							1.0f - 2.0f * (_qQuat.x * _qQuat.x) - 2.0f * (_qQuat.y * _qQuat.y), 0.0f);
	mRotationMat[3] = Vec4F(0.0f, 0.0f, 0.0f, 1.0f);

	return mRotationMat;
}

[[nodiscard]] HC_INLINE Vec3F ExtractEulerAngles(const QuaternionF& _qQuat) {
	Vec3F vEulerAngles;
	float fSin, fCos;

	//Roll
	fSin = 2.0f * (_qQuat.w * _qQuat.x + _qQuat.y * _qQuat.z);
	fCos = 1.0f - 2.0f * (_qQuat.x * _qQuat.x + _qQuat.y * _qQuat.y);
	vEulerAngles.x = atan2f(fSin, fCos);

	//Pitch
	fSin = sqrtf(1.0f + 2.0f * (_qQuat.w * _qQuat.y - _qQuat.x * _qQuat.z));
	fCos = sqrtf(1.0f - 2.0f * (_qQuat.w * _qQuat.y - _qQuat.x * _qQuat.z));
	vEulerAngles.y = 2.0f * atan2f(fSin, fCos) - HC_PI / 2.0f;

	//Yaw
	fSin = 2.0f * (_qQuat.w * _qQuat.z + _qQuat.x * _qQuat.y);
	fCos = 1.0f - 2.0f * (_qQuat.y * _qQuat.y + _qQuat.z * _qQuat.z);
	vEulerAngles.z = atan2f(fSin, fCos);
	
	return vEulerAngles;
}

#endif