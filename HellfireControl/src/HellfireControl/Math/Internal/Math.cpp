
#include <HellfireControl/Math/Math.hpp>

namespace Math {
#pragma region Scalar
	float Clamp(float _fVal, float _fMin, float _fMax) { return _fVal > _fMax ? _fMax : (_fVal < _fMin ? _fMin : _fVal); }

	float Lerp(float _fStart, float _fEnd, float _fRatio) { return (_fEnd - _fStart) * _fRatio + _fStart; }

	float Wrap(float _fVal, float _fLowerBound, float _fUpperBound) {
		if (_fLowerBound > _fUpperBound) return Wrap(_fVal, _fUpperBound, _fLowerBound);
		return (_fVal >= 0.0f ? _fLowerBound : _fUpperBound) + fmodf(_fVal, _fUpperBound - _fLowerBound);
	}

	float Pow(float _fBase, float _fExp) { return powf(_fBase, _fExp); }

	float Sqrt(float _fVal) { return sqrtf(_fVal); }

	float Log10(float _fVal) { return log10f(_fVal); }

	float Log2(float _fVal) { return log2f(_fVal); }

	float Ln(float _fVal) { return logf(_fVal); }

	float Exp(float _fVal) { return expf(_fVal); }

	float Sin(float _fVal) { return sinf(_fVal); }

	float Cos(float _fVal) { return cosf(_fVal); }

	float Tan(float _fVal) { return tanf(_fVal); }

	float ArcSin(float _fVal) { return asinf(_fVal); }

	float ArcCos(float _fVal) { return acosf(_fVal); }

	float ArcTan(float _fVal) { return atanf(_fVal); }

	float ArcTan2(float _fLeft, float _fRight) { return atan2f(_fLeft, _fRight); }

	float Oscillate(float _fMin, float _fMax, float _fPeriod, float _fTime) {
		if (_fMax < _fMin) return Oscillate(_fMax, _fMin, _fPeriod, _fTime);

		float fAmp = (_fMax - _fMin) * 0.5f;
		float fPeriod = (HC_2PI / _fPeriod);
		float fMid = (_fMin + _fMax) * 0.5f;

		return fAmp * cosf(fPeriod * _fTime) + fMid;
	}

	float DampedOscillate(float _fMin, float _fMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		if (_fMax < _fMin) return DampedOscillate(_fMax, _fMin, _fPeriod, _fTime, _fDampingFactor);

		float fAmp = ((_fMax - _fMin) * 0.5f) * expf(-(_fDampingFactor)*_fTime);
		float fPeriod = HC_2PI / _fPeriod;
		float fMid = (_fMax + _fMin) * 0.5f;

		return fAmp * cosf(fPeriod * _fTime) + fMid;
	}

	float SmoothStep(float _fStart, float _fEnd, float _fRatio) {
		_fRatio = Clamp(_fRatio);
		_fRatio = _fRatio * _fRatio * (3.0f - (2.0f * _fRatio));
		return _fEnd * _fRatio + _fStart * (1.0f - _fRatio);
	}

	float DampedSmoothStep(float _fCurrent, float _fGoal, float& _fVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		float fChange = _fCurrent - _fGoal;
		fChange = Clamp(fChange, -fDeltaCap, fDeltaCap);

		float fTemp = (_fVelocity + fOmega * fChange) * _fTimeDelta;
		_fVelocity = (_fVelocity - fOmega * fTemp) * fExponent;

		return _fGoal + (fChange + fTemp) * fExponent;
	}

	float InverseSmoothStep(float _fVal) {
		_fVal = Clamp(_fVal);
		return 0.5f - sinf(asinf(1.0f - 2.0f * _fVal) / 3.0f);
	}
#pragma endregion

#pragma region Vec2
	Vec2F Clamp(const Vec2F& _vVal, const Vec2F& _vMin, const Vec2F& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }

	Vec2F ClampMagnitude(const Vec2F& _vVal, float _fMin, float _fMax) {
		float fMag = LengthSquared(_vVal);

		if (fMag < _fMin * _fMin) {
			return Normalize(_vVal) * _fMin;
		}

		if (fMag > _fMax * _fMax) {
			return Normalize(_vVal) * _fMax;
		}

		return _vVal;
	}

	Vec2F Lerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }

	Vec2F NLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	Vec2F SLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
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

	Vec2F Wrap(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound) {
		return Vec2F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	Vec2F Pow(const Vec2F& _vBase, float _fExp) { return Vec2F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp)); }

	Vec2F Sqrt(const Vec2F& _vVal) { return Vec2F(Sqrt(_vVal[0]), Sqrt(_vVal[1])); }

	Vec2F Log10(const Vec2F& _vVal) { return Vec2F(Log10(_vVal[0]), Log10(_vVal[1])); }

	Vec2F Log2(const Vec2F& _vVal) { return Vec2F(Log2(_vVal[0]), Log2(_vVal[1])); }

	Vec2F Ln(const Vec2F& _vVal) { return Vec2F(Ln(_vVal[0]), Ln(_vVal[1])); }

	Vec2F Exp(const Vec2F& _vVal) { return Vec2F(Exp(_vVal[0]), Exp(_vVal[1])); }

	Vec2F Sin(const Vec2F& _vVal) { return Vec2F(Sin(_vVal[0]), Sin(_vVal[1])); }

	Vec2F Cos(const Vec2F& _vVal) { return Vec2F(Cos(_vVal[0]), Cos(_vVal[1])); }

	Vec2F Tan(const Vec2F& _vVal) { return Vec2F(Tan(_vVal[0]), Tan(_vVal[1])); }

	Vec2F ArcSin(const Vec2F& _vVal) { return Vec2F(ArcSin(_vVal[0]), ArcSin(_vVal[1])); }

	Vec2F ArcCos(const Vec2F& _vVal) { return Vec2F(ArcCos(_vVal[0]), ArcCos(_vVal[1])); }

	Vec2F ArcTan(const Vec2F& _vVal) { return Vec2F(ArcTan(_vVal[0]), ArcTan(_vVal[1])); }

	Vec2F ArcTan2(const Vec2F& _vLeft, const Vec2F& _vRight) { return Vec2F(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1])); }

	Vec2F Oscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime) {
		return Vec2F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime));
	}

	Vec2F DampedOscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec2F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor));
	}

	Vec2F SmoothStep(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		return Vec2F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio));
	}

	Vec2F DampedSmoothStep(const Vec2F& _vCurrent, const Vec2F& _vGoal, Vec2F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec2F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec2F(-fDeltaCap), Vec2F(fDeltaCap));

		Vec2F vTemp = (_vVelocity + Vec2F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec2F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	Vec2F InverseSmoothStep(const Vec2F& _vVal) {
		return Vec2F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]));
	}
#pragma endregion

#pragma region Vec3
	Vec3F Clamp(const Vec3F& _vVal, const Vec3F& _vMin, const Vec3F& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }

	Vec3F ClampMagnitude(const Vec3F& _vVal, float _fMin, float _fMax) {
		float fMag = LengthSquared(_vVal);

		if (fMag < _fMin * _fMin) {
			return Normalize(_vVal) * _fMin;
		}

		if (fMag > _fMax * _fMax) {
			return Normalize(_vVal) * _fMax;
		}

		return _vVal;
	}

	Vec3F Lerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }

	Vec3F NLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	Vec3F SLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
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

	Vec3F Wrap(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound) {
		return Vec3F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	Vec3F Pow(const Vec3F& _vBase, float _fExp) { return Vec3F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp)); }

	Vec3F Sqrt(const Vec3F& _vVal) { return Vec3F(Sqrt(_vVal[0]), Sqrt(_vVal[1]), Sqrt(_vVal[2])); }

	Vec3F Log10(const Vec3F& _vVal) { return Vec3F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }

	Vec3F Log2(const Vec3F& _vVal) { return Vec3F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }

	Vec3F Ln(const Vec3F& _vVal) { return Vec3F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }

	Vec3F Exp(const Vec3F& _vVal) { return Vec3F(Exp(_vVal[0]), Exp(_vVal[1]), Exp(_vVal[2])); }

	Vec3F Sin(const Vec3F& _vVal) { return Vec3F(Sin(_vVal[0]), Sin(_vVal[1]), Sin(_vVal[2])); }

	Vec3F Cos(const Vec3F& _vVal) { return Vec3F(Cos(_vVal[0]), Cos(_vVal[1]), Cos(_vVal[2])); }

	Vec3F Tan(const Vec3F& _vVal) { return Vec3F(Tan(_vVal[0]), Tan(_vVal[1]), Tan(_vVal[2])); }

	Vec3F ArcSin(const Vec3F& _vVal) { return Vec3F(ArcSin(_vVal[0]), ArcSin(_vVal[1]), ArcSin(_vVal[2])); }

	Vec3F ArcCos(const Vec3F& _vVal) { return Vec3F(ArcCos(_vVal[0]), ArcCos(_vVal[1]), ArcCos(_vVal[2])); }

	Vec3F ArcTan(const Vec3F& _vVal) { return Vec3F(ArcTan(_vVal[0]), ArcTan(_vVal[1]), ArcTan(_vVal[2])); }

	Vec3F ArcTan2(const Vec3F& _vLeft, const Vec3F& _vRight) { return Vec3F(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1]), ArcTan2(_vLeft[2], _vRight[2])); }

	Vec3F Oscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime) {
		return Vec3F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[2], _vMax[2], _fPeriod, _fTime));
	}

	Vec3F DampedOscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec3F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[2], _vMax[2], _fPeriod, _fTime, _fDampingFactor));
	}

	Vec3F SmoothStep(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		return Vec3F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio),
			SmoothStep(_vStart[2], _vEnd[2], _fRatio));
	}

	Vec3F DampedSmoothStep(const Vec3F& _vCurrent, const Vec3F& _vGoal, Vec3F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec3F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec3F(-fDeltaCap), Vec3F(fDeltaCap));

		Vec3F vTemp = (_vVelocity + Vec3F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec3F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	Vec3F InverseSmoothStep(const Vec3F& _vVal) {
		return Vec3F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]));
	}
#pragma endregion

#pragma region Vec4
	Vec4F Clamp(const Vec4F& _vVal, const Vec4F& _vMin, const Vec4F& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }

	Vec4F ClampMagnitude(const Vec4F& _vVal, float _fMin, float _fMax) {
		float fMag = LengthSquared(_vVal);

		if (fMag < _fMin * _fMin) {
			return Normalize(_vVal) * _fMin;
		}

		if (fMag > _fMax * _fMax) {
			return Normalize(_vVal) * _fMax;
		}

		return _vVal;
	}

	Vec4F Lerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }

	Vec4F NLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	Vec4F SLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
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

	Vec4F Wrap(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound) {
		return Vec4F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
			Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	Vec4F Pow(const Vec4F& _vBase, float _fExp) { return Vec4F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[2], _fExp)); }

	Vec4F Sqrt(const Vec4F& _vVal) { return Vec4F(Sqrt(_vVal[0]), Sqrt(_vVal[1]), Sqrt(_vVal[2]), Sqrt(_vVal[3])); }

	Vec4F Log10(const Vec4F& _vVal) { return Vec4F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }

	Vec4F Log2(const Vec4F& _vVal) { return Vec4F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }

	Vec4F Ln(const Vec4F& _vVal) { return Vec4F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }

	Vec4F Exp(const Vec4F& _vVal) { return Vec4F(Exp(_vVal[0]), Exp(_vVal[1]), Exp(_vVal[2]), Exp(_vVal[3])); }

	Vec4F Sin(const Vec4F& _vVal) { return Vec4F(Sin(_vVal[0]), Sin(_vVal[1]), Sin(_vVal[2]), Sin(_vVal[3])); }

	Vec4F Cos(const Vec4F& _vVal) { return Vec4F(Cos(_vVal[0]), Cos(_vVal[1]), Cos(_vVal[2]), Cos(_vVal[3])); }

	Vec4F Tan(const Vec4F& _vVal) { return Vec4F(Tan(_vVal[0]), Tan(_vVal[1]), Tan(_vVal[2]), Tan(_vVal[3])); }

	Vec4F ArcSin(const Vec4F& _vVal) { return Vec4F(ArcSin(_vVal[0]), ArcSin(_vVal[1]), ArcSin(_vVal[2]), ArcSin(_vVal[3])); }

	Vec4F ArcCos(const Vec4F& _vVal) { return Vec4F(ArcCos(_vVal[0]), ArcCos(_vVal[1]), ArcCos(_vVal[2]), ArcCos(_vVal[3])); }

	Vec4F ArcTan(const Vec4F& _vVal) { return Vec4F(ArcTan(_vVal[0]), ArcTan(_vVal[1]), ArcTan(_vVal[2]), ArcTan(_vVal[3])); }

	Vec4F ArcTan2(const Vec4F& _vLeft, const Vec4F& _vRight) { return Vec4F(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1]), ArcTan2(_vLeft[2], _vRight[2]), ArcTan2(_vLeft[3], _vRight[3])); }

	Vec4F Oscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime) {
		return Vec4F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[2], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[3], _vMax[3], _fPeriod, _fTime));
	}

	Vec4F DampedOscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec4F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[2], _vMax[2], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[3], _vMax[3], _fPeriod, _fTime, _fDampingFactor));
	}

	Vec4F SmoothStep(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		return Vec4F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio),
			SmoothStep(_vStart[2], _vEnd[2], _fRatio),
			SmoothStep(_vStart[3], _vEnd[3], _fRatio));
	}

	Vec4F DampedSmoothStep(const Vec4F& _vCurrent, const Vec4F& _vGoal, Vec4F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec4F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec4F(-fDeltaCap), Vec4F(fDeltaCap));

		Vec4F vTemp = (_vVelocity + Vec4F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec4F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	Vec4F InverseSmoothStep(const Vec4F& _vVal) {
		return Vec4F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]),
			InverseSmoothStep(_vVal[3]));
	}
#pragma endregion

#pragma region Matrix
	MatrixF Clamp(const MatrixF& _mVal, const MatrixF& _mMin, const MatrixF& _mMax) {
		return MatrixF(Clamp(_mVal[0], _mMin[0], _mMax[0]),
			Clamp(_mVal[1], _mMin[1], _mMax[1]),
			Clamp(_mVal[2], _mMin[2], _mMin[2]),
			Clamp(_mVal[3], _mMin[3], _mMax[3]));
	}

	MatrixF ClampMagnitude(const MatrixF& _mVal, float _fMin, float _fMax) {
		return MatrixF(ClampMagnitude(_mVal[0], _fMin, _fMax), ClampMagnitude(_mVal[1], _fMin, _fMax), ClampMagnitude(_mVal[2], _fMin, _fMax), ClampMagnitude(_mVal[3], _fMin, _fMax));
	}

	MatrixF Lerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) { return (_mEnd - _mStart) * _fRatio + _mStart; }

	MatrixF NLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(NLerp(_mStart[0], _mEnd[0], _fRatio),
			NLerp(_mStart[1], _mEnd[1], _fRatio),
			NLerp(_mStart[2], _mEnd[2], _fRatio),
			NLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	MatrixF SLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SLerp(_mStart[0], _mEnd[0], _fRatio),
			SLerp(_mStart[1], _mEnd[1], _fRatio),
			SLerp(_mStart[2], _mEnd[2], _fRatio),
			SLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	MatrixF Wrap(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound) {
		return MatrixF(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
			Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]),
			Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
			Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	MatrixF Pow(const MatrixF& _mBase, float _fExp) { return MatrixF(Pow(_mBase[0], _fExp), Pow(_mBase[1], _fExp), Pow(_mBase[2], _fExp), Pow(_mBase[3], _fExp)); }

	MatrixF Sqrt(const MatrixF& _mVal) { return MatrixF(Sqrt(_mVal[0]), Sqrt(_mVal[1]), Sqrt(_mVal[2]), Sqrt(_mVal[3])); }

	MatrixF Log10(const MatrixF& _mVal) { return MatrixF(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }

	MatrixF Log2(const MatrixF& _mVal) { return MatrixF(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }

	MatrixF Ln(const MatrixF& _mVal) { return MatrixF(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }

	MatrixF Exp(const MatrixF& _mVal) { return MatrixF(Exp(_mVal[0]), Exp(_mVal[1]), Exp(_mVal[2]), Exp(_mVal[3])); }

	MatrixF Sin(const MatrixF& _mVal) { return MatrixF(Sin(_mVal[0]), Sin(_mVal[1]), Sin(_mVal[2]), Sin(_mVal[3])); }

	MatrixF Cos(const MatrixF& _mVal) { return MatrixF(Cos(_mVal[0]), Cos(_mVal[1]), Cos(_mVal[2]), Cos(_mVal[3])); }

	MatrixF Tan(const MatrixF& _mVal) { return MatrixF(Tan(_mVal[0]), Tan(_mVal[1]), Tan(_mVal[2]), Tan(_mVal[3])); }

	MatrixF ArcSin(const MatrixF& _mVal) { return MatrixF(ArcSin(_mVal[0]), ArcSin(_mVal[1]), ArcSin(_mVal[2]), ArcSin(_mVal[3])); }

	MatrixF ArcCos(const MatrixF& _mVal) { return MatrixF(ArcCos(_mVal[0]), ArcCos(_mVal[1]), ArcCos(_mVal[2]), ArcCos(_mVal[3])); }

	MatrixF ArcTan(const MatrixF& _mVal) { return MatrixF(ArcTan(_mVal[0]), ArcTan(_mVal[1]), ArcTan(_mVal[2]), ArcTan(_mVal[3])); }

	MatrixF ArcTan2(const MatrixF& _mLeft, const MatrixF& _mRight) { return MatrixF(ArcTan2(_mLeft[0], _mRight[0]), ArcTan2(_mLeft[1], _mRight[1]), ArcTan2(_mLeft[2], _mRight[2]), ArcTan2(_mLeft[3], _mRight[3])); }

	MatrixF Oscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime) {
		return MatrixF(Oscillate(_mMin[0], _mMax[0], _fPeriod, _fTime),
			Oscillate(_mMin[1], _mMax[2], _fPeriod, _fTime),
			Oscillate(_mMin[2], _mMax[2], _fPeriod, _fTime),
			Oscillate(_mMin[3], _mMax[3], _fPeriod, _fTime));
	}

	MatrixF DampedOscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return MatrixF(DampedOscillate(_mMin[0], _mMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[1], _mMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[2], _mMax[2], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[3], _mMax[3], _fPeriod, _fTime, _fDampingFactor));
	}

	MatrixF SmoothStep(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SmoothStep(_mStart[0], _mEnd[0], _fRatio),
			SmoothStep(_mStart[1], _mEnd[1], _fRatio),
			SmoothStep(_mStart[2], _mEnd[2], _fRatio),
			SmoothStep(_mStart[3], _mEnd[3], _fRatio));
	}

	MatrixF DampedSmoothStep(const MatrixF& _mCurrent, const MatrixF& _mGoal, MatrixF& _mVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return MatrixF(DampedSmoothStep(_mCurrent[0], _mGoal[0], _mVelocity[0], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[1], _mGoal[1], _mVelocity[1], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[2], _mGoal[2], _mVelocity[2], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[3], _mGoal[3], _mVelocity[3], _fTimeDelta, _fSmoothTime, _fMaxChange));
	}

	MatrixF InverseSmoothStep(const MatrixF& _mVal) {
		return MatrixF(InverseSmoothStep(_mVal[0]),
			InverseSmoothStep(_mVal[1]),
			InverseSmoothStep(_mVal[2]),
			InverseSmoothStep(_mVal[3]));
	}
#pragma endregion

#pragma region Quaternion
	QuaternionF Clamp(const QuaternionF& _qVal, const QuaternionF& _qMin, const QuaternionF& _qMax) { return Clamp(_qVal.m_vQuat, _qMin.m_vQuat, _qMax.m_vQuat); }

	QuaternionF ClampMagnitude(const QuaternionF& _qVal, float _fMin, float _fMax) {
		return ClampMagnitude(_qVal.m_vQuat, _fMin, _fMax);
	}

	QuaternionF Lerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) { return (_qEnd - _qStart) * _fRatio + _qStart; }

	QuaternionF NLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0f) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _fRatio));
	}

	QuaternionF SLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
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

	QuaternionF Wrap(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound) {
		return QuaternionF(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	QuaternionF Pow(const QuaternionF& _qBase, float _fExp) { return Pow(_qBase.m_vQuat, _fExp); }

	QuaternionF Sqrt(const QuaternionF& _qVal) { return Sqrt(_qVal.m_vQuat); }

	QuaternionF Log10(const QuaternionF& _qVal) { return Log10(_qVal.m_vQuat); }

	QuaternionF Log2(const QuaternionF& _qVal) { return Log2(_qVal.m_vQuat); }

	QuaternionF Ln(const QuaternionF& _qVal) { return Ln(_qVal.m_vQuat); }

	QuaternionF Exp(const QuaternionF& _qVal) { return Exp(_qVal.m_vQuat); }

	QuaternionF Sin(const QuaternionF& _qVal) { return Sin(_qVal.m_vQuat); }

	QuaternionF Cos(const QuaternionF& _qVal) { return Cos(_qVal.m_vQuat); }

	QuaternionF Tan(const QuaternionF& _qVal) { return Tan(_qVal.m_vQuat); }

	QuaternionF ArcSin(const QuaternionF& _qVal) { return ArcSin(_qVal.m_vQuat); }

	QuaternionF ArcCos(const QuaternionF& _qVal) { return ArcCos(_qVal.m_vQuat); }

	QuaternionF ArcTan(const QuaternionF& _qVal) { return ArcTan(_qVal.m_vQuat); }

	QuaternionF ArcTan2(const QuaternionF& _qLeft, const QuaternionF& _qRight) { return ArcTan2(_qLeft.m_vQuat, _qRight.m_vQuat); }

	QuaternionF Oscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime) {
		return Oscillate(_qMin.m_vQuat, _qMax.m_vQuat, _fPeriod, _fTime);
	}

	QuaternionF DampedOscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return DampedOscillate(_qMin.m_vQuat, _qMax.m_vQuat, _fPeriod, _fTime, _fDampingFactor);
	}

	QuaternionF SmoothStep(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		return SmoothStep(_qStart.m_vQuat, _qEnd.m_vQuat, _fRatio);
	}

	QuaternionF DampedSmoothStep(const QuaternionF& _qCurrent, const QuaternionF& _qGoal, QuaternionF& _qVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return DampedSmoothStep(_qCurrent.m_vQuat, _qGoal.m_vQuat, _qVelocity.m_vQuat, _fTimeDelta, _fSmoothTime, _fMaxChange);
	}

	QuaternionF InverseSmoothStep(const QuaternionF& _qVal) {
		return InverseSmoothStep(_qVal.m_vQuat);
	}
#pragma endregion

#if HC_ENABLE_DOUBLE_PRECISION
#pragma region Scalar
	double Clamp(double _dVal, double _dMin, double _dMax) { return _dVal > _dMax ? _dMax : (_dVal < _dMin ? _dMin : _dVal); }

	double Lerp(double _dStart, double _dEnd, double _dRatio) { return (_dEnd - _dStart) * _dRatio + _dStart; }

	double Wrap(double _dVal, double _dLowerBound, double _dUpperBound) {
		if (_dLowerBound > _dUpperBound) return Wrap(_dVal, _dUpperBound, _dLowerBound);
		return (_dVal >= 0.0 ? _dLowerBound : _dUpperBound) + fmod(_dVal, _dUpperBound - _dLowerBound);
	}

	double Pow(double _dBase, double _dExp) { return pow(_dBase, _dExp); }

	double Sqrt(double _dVal) { return sqrt(_dVal); }

	double Log10(double _dVal) { return log10(_dVal); }

	double Log2(double _dVal) { return log2(_dVal); }

	double Ln(double _dVal) { return log(_dVal); }

	double Exp(double _dVal) { return exp(_dVal); }

	double Sin(double _dVal) { return sin(_dVal); }

	double Cos(double _dVal) { return cos(_dVal); }

	double Tan(double _dVal) { return tan(_dVal); }

	double ArcSin(double _dVal) { return asin(_dVal); }

	double ArcCos(double _dVal) { return acos(_dVal); }

	double ArcTan(double _dVal) { return atan(_dVal); }

	double ArcTan2(double _dLeft, double _dRight) { return atan2f(_dLeft, _dRight); }

	double Oscillate(double _dMin, double _dMax, double _dPeriod, double _dTime) {
		if (_dMax < _dMin) return Oscillate(_dMax, _dMin, _dPeriod, _dTime);

		double dAmp = (_dMax - _dMin) * 0.5;
		double dPeriod = (HC_2PI / _dPeriod);
		double dMid = (_dMin + _dMax) * 0.5;

		return dAmp * cos(dPeriod * _dTime) + dMid;
	}

	double DampedOscillate(double _dMin, double _dMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		if (_dMax < _dMin) return DampedOscillate(_dMax, _dMin, _dPeriod, _dTime, _dDampingFactor);

		double dAmp = ((_dMax - _dMin) * 0.5) * exp(-(_dDampingFactor)*_dTime);
		double dPeriod = HC_2PI / _dPeriod;
		double dMid = (_dMax + _dMin) * 0.5;

		return dAmp * cos(dPeriod * _dTime) + dMid;
	}

	double SmoothStep(double _dStart, double _dEnd, double _dRatio) {
		_dRatio = Clamp(_dRatio);
		_dRatio = _dRatio * _dRatio * (3.0 - (2.0 * _dRatio));
		return _dEnd * _dRatio + _dStart * (1.0 - _dRatio);
	}

	double DampedSmoothStep(double _dCurrent, double _dGoal, double& _dVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48f + 0.235f * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		double dChange = _dCurrent - _dGoal;
		dChange = Clamp(dChange, -dDeltaCap, dDeltaCap);

		double dTemp = (_dVelocity + dOmega * dChange) * _dTimeDelta;
		_dVelocity = (_dVelocity - dOmega * dTemp) * dExponent;

		return _dGoal + (dChange + dTemp) * dExponent;
	}

	double InverseSmoothStep(double _dVal) {
		_dVal = Clamp(_dVal);
		return 0.5 - sin(asin(1.0 - 2.0 * _dVal) / 3.0);
	}
#pragma endregion

#pragma region Vec2
	Vec2D Clamp(const Vec2D& _vVal, const Vec2D& _vMin, const Vec2D& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }

	Vec2D ClampMagnitude(const Vec2D& _vVal, double _dMin, double _dMax) {
		double dMag = LengthSquared(_vVal);

		if (dMag < _dMin * _dMin) {
			return Normalize(_vVal) * _dMin;
		}

		if (dMag > _dMax * _dMax) {
			return Normalize(_vVal) * _dMax;
		}

		return _vVal;
	}

	Vec2D Lerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }

	Vec2D NLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	Vec2D SLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
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

	Vec2D Wrap(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound) {
		return Vec2D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	Vec2D Pow(const Vec2D& _vBase, double _dExp) { return Vec2D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp)); }

	Vec2D Sqrt(const Vec2D& _vVal) { return Vec2D(Sqrt(_vVal[0]), Sqrt(_vVal[1])); }

	Vec2D Log10(const Vec2D& _vVal) { return Vec2D(Log10(_vVal[0]), Log10(_vVal[1])); }

	Vec2D Log2(const Vec2D& _vVal) { return Vec2D(Log2(_vVal[0]), Log2(_vVal[1])); }

	Vec2D Ln(const Vec2D& _vVal) { return Vec2D(Ln(_vVal[0]), Ln(_vVal[1])); }

	Vec2D Exp(const Vec2D& _vVal) { return Vec2D(Exp(_vVal[0]), Exp(_vVal[1])); }

	Vec2D Sin(const Vec2D& _vVal) { return Vec2D(Sin(_vVal[0]), Sin(_vVal[1])); }

	Vec2D Cos(const Vec2D& _vVal) { return Vec2D(Cos(_vVal[0]), Cos(_vVal[1])); }

	Vec2D Tan(const Vec2D& _vVal) { return Vec2D(Tan(_vVal[0]), Tan(_vVal[1])); }

	Vec2D ArcSin(const Vec2D& _vVal) { return Vec2D(ArcSin(_vVal[0]), ArcSin(_vVal[1])); }

	Vec2D ArcCos(const Vec2D& _vVal) { return Vec2D(ArcCos(_vVal[0]), ArcCos(_vVal[1])); }

	Vec2D ArcTan(const Vec2D& _vVal) { return Vec2D(ArcTan(_vVal[0]), ArcTan(_vVal[1])); }

	Vec2D ArcTan2(const Vec2D& _vLeft, const Vec2D& _vRight) { return Vec2D(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1])); }

	Vec2D Oscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime) {
		return Vec2D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime));
	}

	Vec2D DampedOscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec2D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor));
	}

	Vec2D SmoothStep(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		return Vec2D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio));
	}

	Vec2D DampedSmoothStep(const Vec2D& _vCurrent, const Vec2D& _vGoal, Vec2D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec2D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec2D(-dDeltaCap), Vec2D(dDeltaCap));

		Vec2D vTemp = (_vVelocity + Vec2D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec2D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	Vec2D InverseSmoothStep(const Vec2D& _vVal) {
		return Vec2D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]));
	}
#pragma endregion

#pragma region Vec3
	Vec3D Clamp(const Vec3D& _vVector, const Vec3D& _vMin, const Vec3D& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }

	Vec3D ClampMagnitude(const Vec3D& _vVal, double _dMin, double _dMax) {
		double dMag = LengthSquared(_vVal);

		if (dMag < _dMin * _dMin) {
			return Normalize(_vVal) * _dMin;
		}

		if (dMag > _dMax * _dMax) {
			return Normalize(_vVal) * _dMax;
		}

		return _vVal;
	}

	Vec3D Lerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }

	Vec3D NLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	Vec3D SLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
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

	Vec3D Wrap(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound) {
		return Vec3D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	Vec3D Pow(const Vec3D& _vBase, double _dExp) { return Vec3D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp)); }

	Vec3D Sqrt(const Vec3D& _vVal) { return Vec3D(Sqrt(_vVal[0]), Sqrt(_vVal[1]), Sqrt(_vVal[2])); }

	Vec3D Log10(const Vec3D& _vVal) { return Vec3D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }

	Vec3D Log2(const Vec3D& _vVal) { return Vec3D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }

	Vec3D Ln(const Vec3D& _vVal) { return Vec3D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }

	Vec3D Exp(const Vec3D& _vVal) { return Vec3D(Exp(_vVal[0]), Exp(_vVal[1]), Exp(_vVal[2])); }

	Vec3D Sin(const Vec3D& _vVal) { return Vec3D(Sin(_vVal[0]), Sin(_vVal[1]), Sin(_vVal[2])); }

	Vec3D Cos(const Vec3D& _vVal) { return Vec3D(Cos(_vVal[0]), Cos(_vVal[1]), Cos(_vVal[2])); }

	Vec3D Tan(const Vec3D& _vVal) { return Vec3D(Tan(_vVal[0]), Tan(_vVal[1]), Tan(_vVal[2])); }

	Vec3D ArcSin(const Vec3D& _vVal) { return Vec3D(ArcSin(_vVal[0]), ArcSin(_vVal[1]), ArcSin(_vVal[2])); }

	Vec3D ArcCos(const Vec3D& _vVal) { return Vec3D(ArcCos(_vVal[0]), ArcCos(_vVal[1]), ArcCos(_vVal[2])); }

	Vec3D ArcTan(const Vec3D& _vVal) { return Vec3D(ArcTan(_vVal[0]), ArcTan(_vVal[1]), ArcTan(_vVal[2])); }

	Vec3D ArcTan2(const Vec3D& _vLeft, const Vec3D& _vRight) { return Vec3D(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1]), ArcTan2(_vLeft[2], _vRight[2])); }

	Vec3D Oscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime) {
		return Vec3D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[2], _vMax[2], _dPeriod, _dTime));
	}

	Vec3D DampedOscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec3D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[2], _vMin[2], _dPeriod, _dTime, _dDampingFactor));
	}

	Vec3D SmoothStep(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		return Vec3D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio),
			SmoothStep(_vStart[2], _vEnd[2], _dRatio));
	}

	Vec3D DampedSmoothStep(const Vec3D& _vCurrent, const Vec3D& _vGoal, Vec3D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec3D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec3D(-dDeltaCap), Vec3D(dDeltaCap));

		Vec3D vTemp = (_vVelocity + Vec3D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec3D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	Vec3D InverseSmoothStep(const Vec3D& _vVal) {
		return Vec3D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]));
	}
#pragma endregion

#pragma region Vec4
	Vec4D Clamp(const Vec4D& _vVector, const Vec4D& _vMin, const Vec4D& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }

	Vec4D ClampMagnitude(const Vec4D& _vVal, double _dMin, double _dMax) {
		double dMag = LengthSquared(_vVal);

		if (dMag < _dMin * _dMin) {
			return Normalize(_vVal) * _dMin;
		}

		if (dMag > _dMax * _dMax) {
			return Normalize(_vVal) * _dMax;
		}

		return _vVal;
	}

	Vec4D Lerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }

	Vec4D NLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	Vec4D SLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
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

	Vec4D Wrap(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound) {
		return Vec4D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
			Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	Vec4D Pow(const Vec4D& _vBase, double _dExp) { return Vec4D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp), Pow(_vBase[3], _dExp)); }

	Vec4D Sqrt(const Vec4D& _vVal) { return Vec4D(Sqrt(_vVal[0]), Sqrt(_vVal[1]), Sqrt(_vVal[2]), Sqrt(_vVal[3])); }

	Vec4D Log10(const Vec4D& _vVal) { return Vec4D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }

	Vec4D Log2(const Vec4D& _vVal) { return Vec4D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }

	Vec4D Ln(const Vec4D& _vVal) { return Vec4D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }

	Vec4D Exp(const Vec4D& _vVal) { return Vec4D(Exp(_vVal[0]), Exp(_vVal[1]), Exp(_vVal[2]), Exp(_vVal[3])); }

	Vec4D Sin(const Vec4D& _vVal) { return Vec4D(Sin(_vVal[0]), Sin(_vVal[1]), Sin(_vVal[2]), Sin(_vVal[3])); }

	Vec4D Cos(const Vec4D& _vVal) { return Vec4D(Cos(_vVal[0]), Cos(_vVal[1]), Cos(_vVal[2]), Cos(_vVal[3])); }

	Vec4D Tan(const Vec4D& _vVal) { return Vec4D(Tan(_vVal[0]), Tan(_vVal[1]), Tan(_vVal[2]), Tan(_vVal[3])); }

	Vec4D ArcSin(const Vec4D& _vVal) { return Vec4D(ArcSin(_vVal[0]), ArcSin(_vVal[1]), ArcSin(_vVal[2]), ArcSin(_vVal[3])); }

	Vec4D ArcCos(const Vec4D& _vVal) { return Vec4D(ArcCos(_vVal[0]), ArcCos(_vVal[1]), ArcCos(_vVal[2]), ArcCos(_vVal[3])); }

	Vec4D ArcTan(const Vec4D& _vVal) { return Vec4D(ArcTan(_vVal[0]), ArcTan(_vVal[1]), ArcTan(_vVal[2]), ArcTan(_vVal[3])); }

	Vec4D ArcTan2(const Vec4D& _vLeft, const Vec4D& _vRight) { return Vec4D(ArcTan2(_vLeft[0], _vRight[0]), ArcTan2(_vLeft[1], _vRight[1]), ArcTan2(_vLeft[2], _vRight[2]), ArcTan2(_vLeft[3], _vRight[3])); }

	Vec4D Oscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime) {
		return Vec4D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[2], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[3], _vMax[3], _dPeriod, _dTime));
	}

	Vec4D DampedOscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec4D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[2], _vMin[2], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[3], _vMin[3], _dPeriod, _dTime, _dDampingFactor));
	}

	Vec4D SmoothStep(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		return Vec4D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio),
			SmoothStep(_vStart[2], _vEnd[2], _dRatio),
			SmoothStep(_vStart[3], _vEnd[3], _dRatio));
	}

	Vec4D DampedSmoothStep(const Vec4D& _vCurrent, const Vec4D& _vGoal, Vec4D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec4D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec4D(-dDeltaCap), Vec4D(dDeltaCap));

		Vec4D vTemp = (_vVelocity + Vec4D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec4D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	Vec4D InverseSmoothStep(const Vec4D& _vVal) {
		return Vec4D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]),
			InverseSmoothStep(_vVal[3]));
	}
#pragma endregion

#pragma region Matrix
	MatrixD Clamp(const MatrixD& _mVal, const MatrixD& _mMin, const MatrixD& _mMax) {
		return MatrixD(Clamp(_mVal[0], _mMin[0], _mMax[0]),
			Clamp(_mVal[1], _mMin[1], _mMax[1]),
			Clamp(_mVal[2], _mMin[2], _mMin[2]),
			Clamp(_mVal[3], _mMin[3], _mMax[3]));
	}

	MatrixD ClampMagnitude(const MatrixD& _mVal, double _dMin, double _dMax) {
		return MatrixD(ClampMagnitude(_mVal[0], _dMin, _dMax), ClampMagnitude(_mVal[1], _dMin, _dMax), ClampMagnitude(_mVal[2], _dMin, _dMax), ClampMagnitude(_mVal[3], _dMin, _dMax));
	}

	MatrixD Lerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) { return (_mEnd - _mStart) * _dRatio + _mStart; }

	MatrixD NLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(NLerp(_mStart[0], _mEnd[0], _dRatio),
			NLerp(_mStart[1], _mEnd[1], _dRatio),
			NLerp(_mStart[2], _mEnd[2], _dRatio),
			NLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	MatrixD SLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SLerp(_mStart[0], _mEnd[0], _dRatio),
			SLerp(_mStart[1], _mEnd[1], _dRatio),
			SLerp(_mStart[2], _mEnd[2], _dRatio),
			SLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	MatrixD Wrap(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound) {
		return MatrixD(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
			Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]),
			Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
			Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	MatrixD Pow(const MatrixD& _mBase, double _dExp) { return MatrixD(Pow(_mBase[0], _dExp), Pow(_mBase[1], _dExp), Pow(_mBase[2], _dExp), Pow(_mBase[3], _dExp)); }

	MatrixD Sqrt(const MatrixD& _mVal) { return MatrixD(Sqrt(_mVal[0]), Sqrt(_mVal[1]), Sqrt(_mVal[2]), Sqrt(_mVal[3])); }

	MatrixD Log10(const MatrixD& _mVal) { return MatrixD(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }

	MatrixD Log2(const MatrixD& _mVal) { return MatrixD(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }

	MatrixD Ln(const MatrixD& _mVal) { return MatrixD(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }

	MatrixD Exp(const MatrixD& _mVal) { return MatrixD(Exp(_mVal[0]), Exp(_mVal[1]), Exp(_mVal[2]), Exp(_mVal[3])); }

	MatrixD Sin(const MatrixD& _mVal) { return MatrixD(Sin(_mVal[0]), Sin(_mVal[1]), Sin(_mVal[2]), Sin(_mVal[3])); }

	MatrixD Cos(const MatrixD& _mVal) { return MatrixD(Cos(_mVal[0]), Cos(_mVal[1]), Cos(_mVal[2]), Cos(_mVal[3])); }

	MatrixD Tan(const MatrixD& _mVal) { return MatrixD(Tan(_mVal[0]), Tan(_mVal[1]), Tan(_mVal[2]), Tan(_mVal[3])); }

	MatrixD ArcSin(const MatrixD& _mVal) { return MatrixD(ArcSin(_mVal[0]), ArcSin(_mVal[1]), ArcSin(_mVal[2]), ArcSin(_mVal[3])); }

	MatrixD ArcCos(const MatrixD& _mVal) { return MatrixD(ArcCos(_mVal[0]), ArcCos(_mVal[1]), ArcCos(_mVal[2]), ArcCos(_mVal[3])); }

	MatrixD ArcTan(const MatrixD& _mVal) { return MatrixD(ArcTan(_mVal[0]), ArcTan(_mVal[1]), ArcTan(_mVal[2]), ArcTan(_mVal[3])); }

	MatrixD ArcTan2(const MatrixD& _mLeft, const MatrixD& _mRight) { return MatrixD(ArcTan2(_mLeft[0], _mRight[0]), ArcTan2(_mLeft[1], _mRight[1]), ArcTan2(_mLeft[2], _mRight[2]), ArcTan2(_mLeft[3], _mRight[3])); }

	MatrixD Oscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime) {
		return MatrixD(Oscillate(_mMin[0], _mMax[0], _dPeriod, _dTime),
			Oscillate(_mMin[1], _mMax[2], _dPeriod, _dTime),
			Oscillate(_mMin[2], _mMax[2], _dPeriod, _dTime),
			Oscillate(_mMin[3], _mMax[3], _dPeriod, _dTime));
	}

	MatrixD DampedOscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return MatrixD(DampedOscillate(_mMin[0], _mMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[1], _mMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[2], _mMin[2], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[3], _mMin[3], _dPeriod, _dTime, _dDampingFactor));
	}

	MatrixD SmoothStep(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SmoothStep(_mStart[0], _mEnd[0], _dRatio),
			SmoothStep(_mStart[1], _mEnd[1], _dRatio),
			SmoothStep(_mStart[2], _mEnd[2], _dRatio),
			SmoothStep(_mStart[3], _mEnd[3], _dRatio));
	}

	MatrixD DampedSmoothStep(const MatrixD& _mCurrent, const MatrixD& _mGoal, MatrixD& _mVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return MatrixD(DampedSmoothStep(_mCurrent[0], _mGoal[0], _mVelocity[0], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[1], _mGoal[1], _mVelocity[1], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[2], _mGoal[2], _mVelocity[2], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[3], _mGoal[3], _mVelocity[3], _dTimeDelta, _dSmoothTime, _dMaxChange));
	}

	MatrixD InverseSmoothStep(const MatrixD& _mVal) {
		return MatrixD(InverseSmoothStep(_mVal[0]),
			InverseSmoothStep(_mVal[1]),
			InverseSmoothStep(_mVal[2]),
			InverseSmoothStep(_mVal[3]));
	}
#pragma endregion

#pragma region Quaternion
	QuaternionD Clamp(const QuaternionD& _qVal, const QuaternionD& _qMin, const QuaternionD& _qMax) { return Clamp(_qVal.m_vQuat, _qMin.m_vQuat, _qMax.m_vQuat); }

	QuaternionD ClampMagnitude(const QuaternionD& _qVal, double _dMin, double _dMax) {
		return ClampMagnitude(_qVal.m_vQuat, _dMin, _dMax);
	}

	QuaternionD Lerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) { return (_qEnd - _qStart) * _dRatio + _qStart; }

	QuaternionD NLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _dRatio));
	}

	QuaternionD SLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
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

	QuaternionD Wrap(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound) {
		return QuaternionD(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	QuaternionD Pow(const QuaternionD& _qBase, double _dExp) { return Pow(_qBase.m_vQuat, _dExp); }

	QuaternionD Sqrt(const QuaternionD& _qVal) { return Sqrt(_qVal.m_vQuat); }

	QuaternionD Log10(const QuaternionD& _qVal) { return Log10(_qVal.m_vQuat); }

	QuaternionD Log2(const QuaternionD& _qVal) { return Log2(_qVal.m_vQuat); }

	QuaternionD Ln(const QuaternionD& _qVal) { return Ln(_qVal.m_vQuat); }

	QuaternionD Exp(const QuaternionD& _qVal) { return Exp(_qVal.m_vQuat); }

	QuaternionD Sin(const QuaternionD& _qVal) { return Sin(_qVal.m_vQuat); }

	QuaternionD Cos(const QuaternionD& _qVal) { return Cos(_qVal.m_vQuat); }

	QuaternionD Tan(const QuaternionD& _qVal) { return Tan(_qVal.m_vQuat); }

	QuaternionD ArcSin(const QuaternionD& _qVal) { return ArcSin(_qVal.m_vQuat); }

	QuaternionD ArcCos(const QuaternionD& _qVal) { return ArcCos(_qVal.m_vQuat); }

	QuaternionD ArcTan(const QuaternionD& _qVal) { return ArcTan(_qVal.m_vQuat); }

	QuaternionD ArcTan2(const QuaternionD& _qLeft, const QuaternionD& _qRight) { return ArcTan2(_qLeft.m_vQuat, _qRight.m_vQuat); }

	QuaternionD Oscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime) {
		return Oscillate(_qMin.m_vQuat, _qMax.m_vQuat, _dPeriod, _dTime);
	}

	QuaternionD DampedOscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return DampedOscillate(_qMin.m_vQuat, _qMax.m_vQuat, _dPeriod, _dTime, _dDampingFactor);
	}

	QuaternionD SmoothStep(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		return SmoothStep(_qStart.m_vQuat, _qEnd.m_vQuat, _dRatio);
	}

	QuaternionD DampedSmoothStep(const QuaternionD& _qCurrent, const QuaternionD& _qGoal, QuaternionD& _qVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return DampedSmoothStep(_qCurrent.m_vQuat, _qGoal.m_vQuat, _qVelocity.m_vQuat, _dTimeDelta, _dSmoothTime, _dMaxChange);
	}

	QuaternionD InverseSmoothStep(const QuaternionD& _qVal) {
		return InverseSmoothStep(_qVal.m_vQuat);
	}
#pragma endregion
#endif

#if HC_USE_ROTOR
	RotorF Clamp(const RotorF& _rVal, const RotorF& _rMin, const RotorF& _rMax) { return Clamp(_rVal.m_vRot, _rMin.m_vRot, _rMax.m_vRot); }

	RotorF ClampMagnitude(const RotorF& _rVal, float _fMin, float _fMax) {
		return ClampMagnitude(_rVal.m_vRot, _fMin, _fMax);
	}

	RotorF Lerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) { return RotorF(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _fRatio)); }

	RotorF NLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _fRatio));
	}

	RotorF SLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
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

	RotorF Wrap(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound) {
		return RotorF(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	RotorF Pow(const RotorF& _rBase, float _fExp) { return Pow(_rBase.m_vRot, _fExp); }

	RotorF Sqrt(const RotorF& _rVal) { return Sqrt(_rVal.m_vRot); }

	RotorF Log10(const RotorF& _rVal) { return Log10(_rVal.m_vRot); }

	RotorF Log2(const RotorF& _rVal) { return Log2(_rVal.m_vRot); }

	RotorF Ln(const RotorF& _rVal) { return Ln(_rVal.m_vRot); }

	RotorF Exp(const RotorF& _rVal) { return Exp(_rVal.m_vRot); }

	RotorF Sin(const RotorF& _rVal) { return Sin(_rVal.m_vRot); }

	RotorF Cos(const RotorF& _rVal) { return Cos(_rVal.m_vRot); }

	RotorF Tan(const RotorF& _rVal) { return Tan(_rVal.m_vRot); }

	RotorF ArcSin(const RotorF& _rVal) { return ArcSin(_rVal.m_vRot); }

	RotorF ArcCos(const RotorF& _rVal) { return ArcCos(_rVal.m_vRot); }

	RotorF ArcTan(const RotorF& _rVal) { return ArcTan(_rVal.m_vRot); }

	RotorF ArcTan2(const RotorF& _rLeft, const RotorF& _rRight) { return ArcTan2(_rLeft.m_vRot, _rRight.m_vRot); }

	RotorF Oscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime) {
		return Oscillate(_rMin.m_vRot, _rMax.m_vRot, _fPeriod, _fTime);
	}

	RotorF DampedOscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime, float _fDampingRatio = 0.2f) {
		return DampedOscillate(_rMin.m_vRot, _rMax.m_vRot, _fPeriod, _fTime, _fDampingRatio);
	}

	RotorF SmoothStep(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		return SmoothStep(_rStart.m_vRot, _rEnd.m_vRot, _fRatio);
	}

	RotorF DampedSmoothStep(const RotorF& _rCurrent, const RotorF& _rGoal, RotorF& _rVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return DampedSmoothStep(_rCurrent.m_vRot, _rGoal.m_vRot, _rVelocity.m_vRot, _fTimeDelta, _fSmoothTime, _fMaxChange);
	}

	RotorF InverseSmoothStep(const RotorF& _rVal) {
		return InverseSmoothStep(_rVal.m_vRot);
	}

#if HC_ENABLE_DOUBLE_PRECISION
	RotorD Clamp(const RotorD& _rVal, const RotorD& _rMin, const RotorD& _rMax) { return Clamp(_rVal.m_vRot, _rMin.m_vRot, _rMax.m_vRot); }

	RotorD ClampMagnitude(const RotorD& _rVal, double _dMin, double _dMax) {
		return ClampMagnitude(_rVal.m_vRot, _dMin, _dMax);
	}

	RotorD Lerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) { return RotorD(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _dRatio)); }

	RotorD NLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _dRatio));
	}

	RotorD SLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
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

	RotorD Wrap(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound) {
		return RotorD(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	RotorD Pow(const RotorD& _rBase, double _dExp) { return Pow(_rBase.m_vRot, _dExp); }

	RotorD Sqrt(const RotorD& _rVal) { return Sqrt(_rVal.m_vRot); }

	RotorD Log10(const RotorD& _rVal) { return Log10(_rVal); }

	RotorD Log2(const RotorD& _rVal) { return Log2(_rVal); }

	RotorD Ln(const RotorD& _rVal) { return Ln(_rVal); }

	RotorD Exp(const RotorD& _rVal) { return Exp(_rVal.m_vRot); }

	RotorD Sin(const RotorD& _rVal) { return Sin(_rVal.m_vRot); }

	RotorD Cos(const RotorD& _rVal) { return Cos(_rVal.m_vRot); }

	RotorD Tan(const RotorD& _rVal) { return Tan(_rVal.m_vRot); }

	RotorD ArcSin(const RotorD& _rVal) { return ArcSin(_rVal.m_vRot); }

	RotorD ArcCos(const RotorD& _rVal) { return ArcCos(_rVal.m_vRot); }

	RotorD ArcTan(const RotorD& _rVal) { return ArcTan(_rVal.m_vRot); }

	RotorD ArcTan2(const RotorD& _rLeft, const RotorD& _rRight) { return ArcTan2(_rLeft.m_vRot, _rRight.m_vRot); }


	RotorD Oscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime) {
		return Oscillate(_rMin.m_vRot, _rMax.m_vRot, _dPeriod, _dTime);
	}

	RotorD DampedOscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime, double _dDampingRatio = 0.2) {
		return DampedOscillate(_rMin, _rMax, _dPeriod, _dTime, _dDampingRatio);
	}

	RotorD SmoothStep(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		return SmoothStep(_rStart.m_vRot, _rEnd.m_vRot, _dRatio);
	}

	RotorD DampedSmoothStep(const RotorD& _rCurrent, const RotorD& _rGoal, RotorD& _rVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return DampedSmoothStep(_rCurrent.m_vRot, _rGoal.m_vRot, _rVelocity.m_vRot, _dTimeDelta, _dSmoothTime, _dMaxChange);
	}

	RotorD InverseSmoothStep(const RotorD& _rVal) {
		return InverseSmoothStep(_rVal.m_vRot);
	}
#endif
#endif
}