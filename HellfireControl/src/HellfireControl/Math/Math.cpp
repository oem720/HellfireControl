
#include <HellfireControl/Math/Math.hpp>

namespace Math {
	HC_INLINE float Lerp(float _fStart, float _fEnd, float _fRatio) { return (_fEnd - _fStart) * _fRatio + _fStart; }
	HC_INLINE Vec2F Lerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec3F Lerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec4F Lerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE MatrixF Lerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) { return (_mEnd - _mStart) * _fRatio + _mStart; }
	HC_INLINE QuaternionF Lerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) { return (_qEnd - _qStart) * _fRatio + _qStart; }

	HC_INLINE Vec2F NLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec3F NLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec4F NLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE MatrixF NLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(NLerp(_mStart[0], _mEnd[0], _fRatio),
					   NLerp(_mStart[1], _mEnd[1], _fRatio),
					   NLerp(_mStart[2], _mEnd[2], _fRatio),
					   NLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF NLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0f) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _fRatio));
	}

	HC_INLINE Vec2F SLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vStart = Normalize(_vStart);
		Vec2F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec3F SLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vStart = Normalize(_vStart);
		Vec3F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec4F SLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vStart = Normalize(_vStart);
		Vec4F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE MatrixF SLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SLerp(_mStart[0], _mEnd[0], _fRatio),
					   SLerp(_mStart[1], _mEnd[1], _fRatio),
					   SLerp(_mStart[2], _mEnd[2], _fRatio),
					   SLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF SLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qStart = Normalize(_qStart);
		QuaternionF qEnd = Normalize(_qEnd);
		float fDot = Dot(_qStart, qEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			qEnd = -qEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(qStart, qEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * qStart) + (fTo * qEnd);
	}

	[[nodiscard]] HC_INLINE float Wrap(float _fVal, float _fLowerBound, float _fUpperBound) {
		if (_fLowerBound > _fUpperBound) return Wrap(_fVal, _fUpperBound, _fLowerBound);
		return (_fVal >= 0.0f ? _fLowerBound : _fUpperBound) + fmodf(_fVal, _fUpperBound - _fLowerBound);
	}

	[[nodiscard]] HC_INLINE Vec2F Wrap(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound) {
		return Vec2F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	[[nodiscard]] HC_INLINE Vec3F Wrap(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound){
		return Vec3F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
					 Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	[[nodiscard]] HC_INLINE Vec4F Wrap(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound) {
		return Vec4F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
					 Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
					 Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	[[nodiscard]] HC_INLINE MatrixF Wrap(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound) {
		return MatrixF(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
					   Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]), 
					   Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
					   Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	[[nodiscard]] HC_INLINE QuaternionF Wrap(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound) {
		return QuaternionF(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	[[nodiscard]] HC_INLINE float Pow(float _fBase, float _fExp) { return powf(_fBase, _fExp); }
	[[nodiscard]] HC_INLINE Vec2F Pow(const Vec2F& _vBase, float _fExp) { return Vec2F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp)); }
	[[nodiscard]] HC_INLINE Vec3F Pow(const Vec3F& _vBase, float _fExp) { return Vec3F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp)); }
	[[nodiscard]] HC_INLINE Vec4F Pow(const Vec4F& _vBase, float _fExp) { return Vec4F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[2], _fExp)); }
	[[nodiscard]] HC_INLINE MatrixF Pow(const MatrixF& _mBase, float _fExp) { return MatrixF(Pow(_mBase[0], _fExp), Pow(_mBase[1], _fExp), Pow(_mBase[2], _fExp), Pow(_mBase[3], _fExp)); }
	[[nodiscard]] HC_INLINE QuaternionF Pow(const QuaternionF& _qBase, float _fExp) { return Pow(_qBase.m_vQuat, _fExp); }

	[[nodiscard]] HC_INLINE float Log10(float _fVal) { return log10f(_fVal); }
	[[nodiscard]] HC_INLINE Vec2F Log10(const Vec2F& _vVal) { return Vec2F(Log10(_vVal[0]), Log10(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3F Log10(const Vec3F& _vVal) { return Vec3F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4F Log10(const Vec4F& _vVal) { return Vec4F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixF Log10(const MatrixF& _mVal) { return MatrixF(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionF Log10(const QuaternionF& _qVal) { return Log10(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE float Log2(float _fVal) { return log2f(_fVal); }
	[[nodiscard]] HC_INLINE Vec2F Log2(const Vec2F& _vVal) { return Vec2F(Log2(_vVal[0]), Log2(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3F Log2(const Vec3F& _vVal) { return Vec3F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4F Log2(const Vec4F& _vVal) { return Vec4F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixF Log2(const MatrixF& _mVal) { return MatrixF(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionF Log2(const QuaternionF& _qVal) { return Log2(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE float Ln(float _fVal) { return logf(_fVal); }
	[[nodiscard]] HC_INLINE Vec2F Ln(const Vec2F& _vVal) { return Vec2F(Ln(_vVal[0]), Ln(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3F Ln(const Vec3F& _vVal) { return Vec3F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4F Ln(const Vec4F& _vVal) { return Vec4F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixF Ln(const MatrixF& _mVal) { return MatrixF(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionF Ln(const QuaternionF& _qVal) { return Ln(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE float Oscillate(float _fStart, float _fEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE Vec2F Oscillate(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio, float _fPeriod, float _fTime){

	}

	[[nodiscard]] HC_INLINE Vec3F Oscillate(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio, float _fPeriod, float _fTime){

	}

	[[nodiscard]] HC_INLINE Vec4F Oscillate(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE MatrixF Oscillate(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE QuaternionF Oscillate(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE float DampedOscillate(float _fStart, float _fEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE Vec2F DampedOscillate(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE Vec3F DampedOscillate(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE Vec4F DampedOscillate(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE MatrixF DampedOscillate(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE QuaternionF DampedOscillate(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE float SmoothStep(float _fVal, float _fStart, float _fEnd) {

	}

	[[nodiscard]] HC_INLINE Vec2F SmoothStep(const Vec2F& _vVal, const Vec2F& _vStart, const Vec2F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec3F SmoothStep(const Vec3F& _vVal, const Vec3F& _vStart, const Vec3F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec4F SmoothStep(const Vec4F& _vVal, const Vec4F& _vStart, const Vec4F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE MatrixF SmoothStep(const MatrixF& _mVal, const MatrixF& _mStart, const MatrixF& _mEnd) {

	}

	[[nodiscard]] HC_INLINE QuaternionF SmoothStep(const QuaternionF& _qVal, const QuaternionF& _qStart, const QuaternionF& _qEnd) {

	}

	[[nodiscard]] HC_INLINE float DampedSmoothStep(float _fVal, float _fStart, float _fEnd) {

	}

	[[nodiscard]] HC_INLINE Vec2F DampedSmoothStep(const Vec2F& _vVal, const Vec2F& _vStart, const Vec2F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec3F DampedSmoothStep(const Vec3F& _vVal, const Vec3F& _vStart, const Vec3F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec4F DampedSmoothStep(const Vec4F& _vVal, const Vec4F& _vStart, const Vec4F& _vEnd) {

	}

	[[nodiscard]] HC_INLINE MatrixF DampedSmoothStep(const MatrixF& _mVal, const MatrixF& _mStart, const MatrixF& _mEnd) {

	}

	[[nodiscard]] HC_INLINE QuaternionF DampedSmoothStep(const QuaternionF& _qVal, const QuaternionF& _qStart, const QuaternionF& _qEnd) {

	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE double Lerp(double _dStart, double _dEnd, double _dRatio) { return (_dEnd - _dStart) * _dRatio + _dStart; }
	HC_INLINE Vec2D Lerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec3D Lerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec4D Lerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE MatrixD Lerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) { return (_mEnd - _mStart) * _dRatio + _mStart; }
	HC_INLINE QuaternionD Lerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) { return (_qEnd - _qStart) * _dRatio + _qStart; }

	HC_INLINE Vec2D NLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec3D NLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec4D NLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE MatrixD NLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(NLerp(_mStart[0], _mEnd[0], _dRatio),
					   NLerp(_mStart[1], _mEnd[1], _dRatio),
					   NLerp(_mStart[2], _mEnd[2], _dRatio),
					   NLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD NLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _dRatio));
	}

	HC_INLINE Vec2D SLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vStart = Normalize(_vStart);
		Vec2D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec3D SLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vStart = Normalize(_vStart);
		Vec3D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec4D SLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vStart = Normalize(_vStart);
		Vec4D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE MatrixD SLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SLerp(_mStart[0], _mEnd[0], _dRatio),
					   SLerp(_mStart[1], _mEnd[1], _dRatio),
					   SLerp(_mStart[2], _mEnd[2], _dRatio),
					   SLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD SLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qStart = Normalize(_qStart);
		QuaternionD qEnd = Normalize(_qEnd);
		double dDot = Dot(_qStart, qEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			qEnd = -qEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(qStart, qEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0f - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * qStart) + (dTo * qEnd);
	}

	[[nodiscard]] HC_INLINE double Wrap(double _dVal, double _dLowerBound, double _dUpperBound) {
		if (_dLowerBound > _dUpperBound) return Wrap(_dVal, _dUpperBound, _dLowerBound);
		return (_dVal >= 0.0 ? _dLowerBound : _dUpperBound) + fmod(_dVal, _dUpperBound - _dLowerBound);
	}

	[[nodiscard]] HC_INLINE Vec2D Wrap(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound) {
		return Vec2D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	[[nodiscard]] HC_INLINE Vec3D Wrap(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound) {
		return Vec3D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
					 Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	[[nodiscard]] HC_INLINE Vec4D Wrap(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound) {
		return Vec4D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
					 Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
					 Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
					 Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	[[nodiscard]] HC_INLINE MatrixD Wrap(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound) {
		return MatrixD(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
					   Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]),
					   Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
					   Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	[[nodiscard]] HC_INLINE QuaternionD Wrap(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound) {
		return QuaternionD(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	[[nodiscard]] HC_INLINE double Pow(double _dBase, double _dExp) { return pow(_dBase, _dExp); }
	[[nodiscard]] HC_INLINE Vec2D Pow(const Vec2D& _vBase, double _dExp) { return Vec2D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp)); }
	[[nodiscard]] HC_INLINE Vec3D Pow(const Vec3D& _vBase, double _dExp) { return Vec3D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp)); }
	[[nodiscard]] HC_INLINE Vec4D Pow(const Vec4D& _vBase, double _dExp) { return Vec4D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp), Pow(_vBase[3], _dExp)); }
	[[nodiscard]] HC_INLINE MatrixD Pow(const MatrixD& _mBase, double _dExp) { return MatrixD(Pow(_mBase[0], _dExp), Pow(_mBase[1], _dExp), Pow(_mBase[2], _dExp), Pow(_mBase[3], _dExp)); }
	[[nodiscard]] HC_INLINE QuaternionD Pow(const QuaternionD& _qBase, double _dExp) { return Pow(_qBase.m_vQuat, _dExp); }

	[[nodiscard]] HC_INLINE double Log10(double _dVal) { return log10(_dVal); }
	[[nodiscard]] HC_INLINE Vec2D Log10(const Vec2D& _vVal) { return Vec2D(Log10(_vVal[0]), Log10(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3D Log10(const Vec3D& _vVal) { return Vec3D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4D Log10(const Vec4D& _vVal) { return Vec4D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixD Log10(const MatrixD& _mVal) { return MatrixD(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionD Log10(const QuaternionD& _qVal) { return Log10(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE double Log2(double _dVal) { return log2(_dVal); }
	[[nodiscard]] HC_INLINE Vec2D Log2(const Vec2D& _vVal) { return Vec2D(Log2(_vVal[0]), Log2(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3D Log2(const Vec3D& _vVal) { return Vec3D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4D Log2(const Vec4D& _vVal) { return Vec4D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixD Log2(const MatrixD& _mVal) { return MatrixD(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionD Log2(const QuaternionD& _qVal) { return Log2(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE double Ln(double _dVal) { return log(_dVal); }
	[[nodiscard]] HC_INLINE Vec2D Ln(const Vec2D& _vVal) { return Vec2D(Ln(_vVal[0]), Ln(_vVal[1])); }
	[[nodiscard]] HC_INLINE Vec3D Ln(const Vec3D& _vVal) { return Vec3D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }
	[[nodiscard]] HC_INLINE Vec4D Ln(const Vec4D& _vVal) { return Vec4D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }
	[[nodiscard]] HC_INLINE MatrixD Ln(const MatrixD& _mVal) { return MatrixD(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }
	[[nodiscard]] HC_INLINE QuaternionD Ln(const QuaternionD& _qVal) { return Ln(_qVal.m_vQuat); }

	[[nodiscard]] HC_INLINE double Oscillate(double _dStart, double _dEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec2D Oscillate(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec3D Oscillate(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec4D Oscillate(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE MatrixD Oscillate(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE QuaternionD Oscillate(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE double DampedOscillate(double _dStart, double _dEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec2D DampedOscillate(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec3D DampedOscillate(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE Vec4D DampedOscillate(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE MatrixD DampedOscillate(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE QuaternionD DampedOscillate(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE double SmoothStep(double _dVal, double _dStart, double _dEnd) {

	}

	[[nodiscard]] HC_INLINE Vec2D SmoothStep(const Vec2D& _vVal, const Vec2D& _vStart, const Vec2D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec3D SmoothStep(const Vec3D& _vVal, const Vec3D& _vStart, const Vec3D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec4D SmoothStep(const Vec4D& _vVal, const Vec4D& _vStart, const Vec4D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE MatrixD SmoothStep(const MatrixD& _mVal, const MatrixD& _mStart, const MatrixD& _mEnd) {

	}

	[[nodiscard]] HC_INLINE QuaternionD SmoothStep(const QuaternionD& _qVal, const QuaternionD& _qStart, const QuaternionD& _qEnd) {

	}

	[[nodiscard]] HC_INLINE double DampedSmoothStep(double _dVal, double _dStart, double _dEnd) {

	}

	[[nodiscard]] HC_INLINE Vec2D DampedSmoothStep(const Vec2D& _vVal, const Vec2D& _vStart, const Vec2D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec3D DampedSmoothStep(const Vec3D& _vVal, const Vec3D& _vStart, const Vec3D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE Vec4D DampedSmoothStep(const Vec4D& _vVal, const Vec4D& _vStart, const Vec4D& _vEnd) {

	}

	[[nodiscard]] HC_INLINE MatrixD DampedSmoothStep(const MatrixD& _mVal, const MatrixD& _mStart, const MatrixD& _mEnd) {

	}

	[[nodiscard]] HC_INLINE QuaternionD DampedSmoothStep(const QuaternionD& _qVal, const QuaternionD& _qStart, const QuaternionD& _qEnd) {

	}
#endif

#if HC_USE_ROTOR
	HC_INLINE RotorF Lerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) { return RotorF(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _fRatio)); }

	HC_INLINE RotorF NLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _fRatio));
	}

	HC_INLINE RotorF SLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rStart = _rStart;
		RotorF rEnd = _rEnd;
		float fDot = Dot(_rStart, _rEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			rEnd = -rEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(rStart, rEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);
		return (fFrom * rStart) + (fTo * rEnd);
	}

	[[nodiscard]] HC_INLINE RotorF Wrap(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound) {
		return RotorF(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	[[nodiscard]] HC_INLINE RotorF Pow(const RotorF& _rBase, float _fExp) { return Pow(_rBase.m_vRot, _fExp); }

	[[nodiscard]] HC_INLINE RotorF Log10(const RotorF& _rVal) { return Log10(_rVal.m_vRot); }

	[[nodiscard]] HC_INLINE RotorF Log2(const RotorF& _rVal) { return Log2(_rVal.m_vRot); }

	[[nodiscard]] HC_INLINE RotorF Ln(const RotorF& _rVal) { return Ln(_rVal.m_vRot); }

	[[nodiscard]] HC_INLINE RotorF Oscillate(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE RotorF DampedOscillate(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio, float _fPeriod, float _fTime) {

	}

	[[nodiscard]] HC_INLINE RotorF SmoothStep(const RotorF& _rVal, const RotorF& _rStart, const RotorF& _rEnd) {

	}

	[[nodiscard]] HC_INLINE RotorF DampedSmoothStep(const RotorF& _rVal, const RotorF& _rStart, const RotorF& _rEnd) {

	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE RotorD Lerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) { return RotorD(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _dRatio)); }

	HC_INLINE RotorD NLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _dRatio));
	}

	HC_INLINE RotorD SLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rStart = _rStart;
		RotorD rEnd = _rEnd;
		double dDot = Dot(_rStart, _rEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			rEnd = -rEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(rStart, rEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);
		return (dFrom * rStart) + (dTo * rEnd);
	}

	[[nodiscard]] HC_INLINE RotorD Wrap(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound) {
		return RotorD(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	[[nodiscard]] HC_INLINE RotorD Pow(const RotorD& _rBase, double _dExp) { return Pow(_rBase.m_vRot, _dExp); }

	[[nodiscard]] HC_INLINE RotorD Log10(const RotorD& _rVal) { return Log10(_rVal); }

	[[nodiscard]] HC_INLINE RotorD Log2(const RotorD& _rVal) { return Log2(_rVal); }

	[[nodiscard]] HC_INLINE RotorD Ln(const RotorD& _rVal) { return Ln(_rVal); }

	[[nodiscard]] HC_INLINE RotorD Oscillate(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE RotorD DampedOscillate(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio, double _dPeriod, double _dTime) {

	}

	[[nodiscard]] HC_INLINE RotorD SmoothStep(const RotorD& _rVal, const RotorD& _rStart, const RotorD& _rEnd) {

	}

	[[nodiscard]] HC_INLINE RotorD DampedSmoothStep(const RotorD& _rVal, const RotorD& _rStart, const RotorD& _rEnd) {

	}
#endif
#endif
}