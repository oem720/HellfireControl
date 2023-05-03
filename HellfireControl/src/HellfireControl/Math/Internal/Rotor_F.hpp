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
	HC_INLINE explicit RotorF(const Vec4F& _vRot) : m_vRot(_vRot) {}
	HC_INLINE explicit RotorF(float _fA, const Vec3F& _vBV) : m_vRot(_vBV, _fA) {}
	HC_INLINE explicit RotorF(float _fB01, float _fB02, float _fB12, float _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorF(int _fB01, int _fB02, int _fB12, int _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}
	HC_INLINE explicit RotorF(double _fB01, double _fB02, double _fB12, double _fS) : m_vRot(_fB01, _fB02, _fB12, _fS) {}

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

		m_vRot.w = 1.0f + Dot(_vTo, _vFrom);
		m_vRot.x = v.x;
		m_vRot.y = v.y;
		m_vRot.z = v.z;

		m_vRot = Normalize(m_vRot);
	}
};

#endif