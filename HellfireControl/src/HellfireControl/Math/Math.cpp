
#include <HellfireControl/Math/Math.hpp>

namespace Math {
	HC_INLINE float LERP(float _fStart, float _fEnd, float _fRatio) { return (_fEnd - _fStart) * _fRatio + _fStart; }
	HC_INLINE Vec2F LERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec3F LERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec4F LERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE MatrixF LERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) { return (_mEnd - _mStart) * _fRatio + _mStart; }
	HC_INLINE QuaternionF LERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) { return (_qEnd - _qStart) * _fRatio + _qStart; }

	HC_INLINE Vec2F NLERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec3F NLERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec4F NLERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _fRatio));
	}

	HC_INLINE MatrixF NLERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(NLERP(_mStart[0], _mEnd[0], _fRatio),
					   NLERP(_mStart[1], _mEnd[1], _fRatio),
					   NLERP(_mStart[2], _mEnd[2], _fRatio),
					   NLERP(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF NLERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0f) { qEnd = -qEnd; }

		return Normalize(LERP(_qStart, qEnd, _fRatio));
	}

	HC_INLINE Vec2F SLERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vStart = Normalize(_vStart);
		Vec2F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec3F SLERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vStart = Normalize(_vStart);
		Vec3F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec4F SLERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vStart = Normalize(_vStart);
		Vec4F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE MatrixF SLERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SLERP(_mStart[0], _mEnd[0], _fRatio),
					   SLERP(_mStart[1], _mEnd[1], _fRatio),
					   SLERP(_mStart[2], _mEnd[2], _fRatio),
					   SLERP(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF SLERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qStart = Normalize(_qStart);
		QuaternionF qEnd = Normalize(_qEnd);
		float fDot = Dot(_qStart, qEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			qEnd = -qEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLERP(qStart, qEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * qStart) + (fTo * qEnd);
	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE double LERP(double _dStart, double _dEnd, double _dRatio) { return (_dEnd - _dStart) * _dRatio + _dStart; }
	HC_INLINE Vec2D LERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec3D LERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec4D LERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE MatrixD LERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) { return (_mEnd - _mStart) * _dRatio + _mStart; }
	HC_INLINE QuaternionD LERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) { return (_qEnd - _qStart) * _dRatio + _qStart; }

	HC_INLINE Vec2D NLERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec3D NLERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec4D NLERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(LERP(_vStart, vEnd, _dRatio));
	}

	HC_INLINE MatrixD NLERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(NLERP(_mStart[0], _mEnd[0], _dRatio),
					   NLERP(_mStart[1], _mEnd[1], _dRatio),
					   NLERP(_mStart[2], _mEnd[2], _dRatio),
					   NLERP(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD NLERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0) { qEnd = -qEnd; }

		return Normalize(LERP(_qStart, qEnd, _dRatio));
	}

	HC_INLINE Vec2D SLERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vStart = Normalize(_vStart);
		Vec2D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec3D SLERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vStart = Normalize(_vStart);
		Vec3D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec4D SLERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vStart = Normalize(_vStart);
		Vec4D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLERP(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE MatrixD SLERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SLERP(_mStart[0], _mEnd[0], _dRatio),
					   SLERP(_mStart[1], _mEnd[1], _dRatio),
					   SLERP(_mStart[2], _mEnd[2], _dRatio),
					   SLERP(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD SLERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qStart = Normalize(_qStart);
		QuaternionD qEnd = Normalize(_qEnd);
		double dDot = Dot(_qStart, qEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			qEnd = -qEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLERP(qStart, qEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0f - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * qStart) + (dTo * qEnd);
	}
#endif

#if HC_USE_ROTOR
	HC_INLINE RotorF LERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) { return RotorF(LERP(_rStart.m_vRot, _rEnd.m_vRot, _fRatio)); }

	HC_INLINE RotorF NLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(LERP(_rStart, rEnd, _fRatio));
	}

	HC_INLINE RotorF SLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rStart = _rStart;
		RotorF rEnd = _rEnd;
		float fDot = Dot(_rStart, _rEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			rEnd = -rEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLERP(rStart, rEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);
		return (fFrom * rStart) + (fTo * rEnd);
	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE RotorD LERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) { return RotorD(LERP(_rStart.m_vRot, _rEnd.m_vRot, _dRatio)); }

	HC_INLINE RotorD NLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(LERP(_rStart, rEnd, _dRatio));
	}

	HC_INLINE RotorD SLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rStart = _rStart;
		RotorD rEnd = _rEnd;
		double dDot = Dot(_rStart, _rEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			rEnd = -rEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLERP(rStart, rEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);
		return (dFrom * rStart) + (dTo * rEnd);
	}
#endif
#endif
}