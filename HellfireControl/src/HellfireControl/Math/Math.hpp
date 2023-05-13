#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Vector.hpp>
#include <HellfireControl/Math/Matrix.hpp>
#include <HellfireControl/Math/Quaternion.hpp>

#if HC_USE_ROTOR
#include <HellfireControl/Math/Rotor.hpp>
#endif

namespace Math {
	[[nodiscard]] HC_INLINE float Clamp(float _fVal, float _fMin = 0.0f, float _fMax = 1.0f);
	[[nodiscard]] HC_INLINE Vec2F Clamp(const Vec2F& _vVal, const Vec2F& _vMin, const Vec2F& _vMax);
	[[nodiscard]] HC_INLINE Vec3F Clamp(const Vec3F& _vVal, const Vec3F& _vMin, const Vec3F& _vMax);
	[[nodiscard]] HC_INLINE Vec4F Clamp(const Vec4F& _vVal, const Vec4F& _vMin, const Vec4F& _vMax);
	[[nodiscard]] HC_INLINE MatrixF Clamp(const MatrixF& _mVal, const MatrixF& _mMin, const MatrixF& _mMax);
	[[nodiscard]] HC_INLINE QuaternionF Clamp(const QuaternionF& _qVal, const QuaternionF& _qMin, const QuaternionF& _qMax);

	[[nodiscard]] HC_INLINE float Lerp(float _fStart, float _fEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec2F Lerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F Lerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F Lerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF Lerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF Lerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE Vec2F NLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F NLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F NLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF NLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF NLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE Vec2F SLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F SLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F SLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF SLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF SLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE float Wrap(float _fVal, float _fLowerBound, float _fUpperBound);
	[[nodiscard]] HC_INLINE Vec2F Wrap(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec3F Wrap(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec4F Wrap(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound);
	[[nodiscard]] HC_INLINE MatrixF Wrap(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound);
	[[nodiscard]] HC_INLINE QuaternionF Wrap(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound);

	[[nodiscard]] HC_INLINE float Pow(float _fBase, float _fExp);
	[[nodiscard]] HC_INLINE Vec2F Pow(const Vec2F& _vBase, float _fExp);
	[[nodiscard]] HC_INLINE Vec3F Pow(const Vec3F& _vBase, float _fExp);
	[[nodiscard]] HC_INLINE Vec4F Pow(const Vec4F& _vBase, float _fExp);
	[[nodiscard]] HC_INLINE MatrixF Pow(const MatrixF& _mBase, float _fExp);
	[[nodiscard]] HC_INLINE QuaternionF Pow(const QuaternionF& _qBase, float _fExp);

	[[nodiscard]] HC_INLINE float Log10(float _fVal);
	[[nodiscard]] HC_INLINE Vec2F Log10(const Vec2F& _vVal);
	[[nodiscard]] HC_INLINE Vec3F Log10(const Vec3F& _vVal);
	[[nodiscard]] HC_INLINE Vec4F Log10(const Vec4F& _vVal);
	[[nodiscard]] HC_INLINE MatrixF Log10(const MatrixF& _mVal);
	[[nodiscard]] HC_INLINE QuaternionF Log10(const QuaternionF& _qVal);

	[[nodiscard]] HC_INLINE float Log2(float _fVal);
	[[nodiscard]] HC_INLINE Vec2F Log2(const Vec2F& _vVal);
	[[nodiscard]] HC_INLINE Vec3F Log2(const Vec3F& _vVal);
	[[nodiscard]] HC_INLINE Vec4F Log2(const Vec4F& _vVal);
	[[nodiscard]] HC_INLINE MatrixF Log2(const MatrixF& _mVal);
	[[nodiscard]] HC_INLINE QuaternionF Log2(const QuaternionF& _qVal);

	[[nodiscard]] HC_INLINE float Ln(float _fVal);
	[[nodiscard]] HC_INLINE Vec2F Ln(const Vec2F& _vVal);
	[[nodiscard]] HC_INLINE Vec3F Ln(const Vec3F& _vVal);
	[[nodiscard]] HC_INLINE Vec4F Ln(const Vec4F& _vVal);
	[[nodiscard]] HC_INLINE MatrixF Ln(const MatrixF& _mVal);
	[[nodiscard]] HC_INLINE QuaternionF Ln(const QuaternionF& _qVal);

	[[nodiscard]] HC_INLINE float Oscillate(float _fMin, float _fMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE Vec2F Oscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE Vec3F Oscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE Vec4F Oscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE MatrixF Oscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE QuaternionF Oscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime);

	[[nodiscard]] HC_INLINE float DampedOscillate(float _fMin, float _fMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE Vec2F DampedOscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE Vec3F DampedOscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE Vec4F DampedOscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE MatrixF DampedOscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE QuaternionF DampedOscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);

	[[nodiscard]] HC_INLINE float SmoothStep(float _fStart, float _fEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec2F SmoothStep(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F SmoothStep(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F SmoothStep(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF SmoothStep(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF SmoothStep(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE float InverseSmoothStep(float _fVal);
	[[nodiscard]] HC_INLINE Vec2F InverseSmoothStep(const Vec2F& _vVal);
	[[nodiscard]] HC_INLINE Vec3F InverseSmoothStep(const Vec3F& _vVal);
	[[nodiscard]] HC_INLINE Vec4F InverseSmoothStep(const Vec4F& _vVal);
	[[nodiscard]] HC_INLINE MatrixF InverseSmoothStep(const MatrixF& _mVal);
	[[nodiscard]] HC_INLINE QuaternionF InverseSmoothStep(const QuaternionF& _qVal);

#if HC_ENABLE_DOUBLE_PRECISION
	[[nodiscard]] HC_INLINE double Clamp(double _dVal, double _dMin = 0.0, double _dMax = 1.0);
	[[nodiscard]] HC_INLINE Vec2D Clamp(const Vec2D& _vVal, const Vec2D& _vMin, const Vec2D& _vMax);
	[[nodiscard]] HC_INLINE Vec3D Clamp(const Vec3D& _vVal, const Vec3D& _vMin, const Vec3D& _vMax);
	[[nodiscard]] HC_INLINE Vec4D Clamp(const Vec4D& _vVal, const Vec4D& _vMin, const Vec4D& _vMax);
	[[nodiscard]] HC_INLINE MatrixD Clamp(const MatrixD& _mVal, const MatrixD& _mMin, const MatrixD& _mMax);
	[[nodiscard]] HC_INLINE QuaternionD Clamp(const QuaternionD& _qVal, const QuaternionD& _qMin, const QuaternionD& _qMax);

	[[nodiscard]] HC_INLINE double Lerp(double _dStart, double _dEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec2D Lerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D Lerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D Lerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD Lerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD Lerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE Vec2D NLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D NLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D NLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD NLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD NLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE Vec2D SLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D SLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D SLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD SLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD SLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE double Wrap(double _dVal, double _dLowerBound, double _dUpperBound);
	[[nodiscard]] HC_INLINE Vec2D Wrap(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec3D Wrap(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec4D Wrap(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound);
	[[nodiscard]] HC_INLINE MatrixD Wrap(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound);
	[[nodiscard]] HC_INLINE QuaternionD Wrap(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound);

	[[nodiscard]] HC_INLINE double Pow(double _dBase, double _dExp);
	[[nodiscard]] HC_INLINE Vec2D Pow(const Vec2D& _vBase, double _dExp);
	[[nodiscard]] HC_INLINE Vec3D Pow(const Vec3D& _vBase, double _dExp);
	[[nodiscard]] HC_INLINE Vec4D Pow(const Vec4D& _vBase, double _dExp);
	[[nodiscard]] HC_INLINE MatrixD Pow(const MatrixD& _mBase, double _dExp);
	[[nodiscard]] HC_INLINE QuaternionD Pow(const QuaternionD& _qBase, double _dExp);

	[[nodiscard]] HC_INLINE double Log10(double _dVal);
	[[nodiscard]] HC_INLINE Vec2D Log10(const Vec2D& _vVal);
	[[nodiscard]] HC_INLINE Vec3D Log10(const Vec3D& _vVal);
	[[nodiscard]] HC_INLINE Vec4D Log10(const Vec4D& _vVal);
	[[nodiscard]] HC_INLINE MatrixD Log10(const MatrixD& _mVal);
	[[nodiscard]] HC_INLINE QuaternionD Log10(const QuaternionD& _qVal);

	[[nodiscard]] HC_INLINE double Log2(double _dVal);
	[[nodiscard]] HC_INLINE Vec2D Log2(const Vec2D& _vVal);
	[[nodiscard]] HC_INLINE Vec3D Log2(const Vec3D& _vVal);
	[[nodiscard]] HC_INLINE Vec4D Log2(const Vec4D& _vVal);
	[[nodiscard]] HC_INLINE MatrixD Log2(const MatrixD& _mVal);
	[[nodiscard]] HC_INLINE QuaternionD Log2(const QuaternionD& _qVal);

	[[nodiscard]] HC_INLINE double Ln(double _dVal);
	[[nodiscard]] HC_INLINE Vec2D Ln(const Vec2D& _vVal);
	[[nodiscard]] HC_INLINE Vec3D Ln(const Vec3D& _vVal);
	[[nodiscard]] HC_INLINE Vec4D Ln(const Vec4D& _vVal);
	[[nodiscard]] HC_INLINE MatrixD Ln(const MatrixD& _mVal);
	[[nodiscard]] HC_INLINE QuaternionD Ln(const QuaternionD& _qVal);

	[[nodiscard]] HC_INLINE double Oscillate(double _dMin, double _dMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE Vec2D Oscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE Vec3D Oscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE Vec4D Oscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE MatrixD Oscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE QuaternionD Oscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime);

	[[nodiscard]] HC_INLINE double DampedOscillate(double _dMin, double _dMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);
	[[nodiscard]] HC_INLINE Vec2D DampedOscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);
	[[nodiscard]] HC_INLINE Vec3D DampedOscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);
	[[nodiscard]] HC_INLINE Vec4D DampedOscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);
	[[nodiscard]] HC_INLINE MatrixD DampedOscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);
	[[nodiscard]] HC_INLINE QuaternionD DampedOscillate(const QuaternionD& _vMin, const QuaternionD& _qMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2);

	[[nodiscard]] HC_INLINE double SmoothStep(double _dStart, double _dEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec2D SmoothStep(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D SmoothStep(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D SmoothStep(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD SmoothStep(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD SmoothStep(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE double InverseSmoothStep(double _dVal);
	[[nodiscard]] HC_INLINE Vec2D InverseSmoothStep(const Vec2D& _vVal);
	[[nodiscard]] HC_INLINE Vec3D InverseSmoothStep(const Vec3D& _vVal);
	[[nodiscard]] HC_INLINE Vec4D InverseSmoothStep(const Vec4D& _vVal);
	[[nodiscard]] HC_INLINE MatrixD InverseSmoothStep(const MatrixD& _mVal);
	[[nodiscard]] HC_INLINE QuaternionD InverseSmoothStep(const QuaternionD& _qVal);
#endif

#if HC_USE_ROTOR
	[[nodiscard]] HC_INLINE RotorF Clamp(const RotorF& _rVal, const RotorF& _rMin, const RotorF& _rMax);
	[[nodiscard]] HC_INLINE RotorF Lerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF NLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF SLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF Wrap(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound);
	[[nodiscard]] HC_INLINE RotorF Pow(const RotorF& _rBase, float _fExp);
	[[nodiscard]] HC_INLINE RotorF Log10(const RotorF& _rVal);
	[[nodiscard]] HC_INLINE RotorF Log2(const RotorF& _rVal);
	[[nodiscard]] HC_INLINE RotorF Ln(const RotorF& _rVal);
	[[nodiscard]] HC_INLINE RotorF Oscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime);
	[[nodiscard]] HC_INLINE RotorF DampedOscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE RotorF SmoothStep(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF InverseSmoothStep(const RotorF& _rVal);

#if HC_ENABLE_DOUBLE_PRECISION
	[[nodiscard]] HC_INLINE RotorD Clamp(const RotorD& _rVal, const RotorD& _rMin, const RotorD& _rMax);
	[[nodiscard]] HC_INLINE RotorD Lerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD NLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD SLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD Wrap(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound);
	[[nodiscard]] HC_INLINE RotorD Pow(const RotorD& _rBase, double _dExp);
	[[nodiscard]] HC_INLINE RotorD Log10(const RotorD& _rVal);
	[[nodiscard]] HC_INLINE RotorD Log2(const RotorD& _rVal);
	[[nodiscard]] HC_INLINE RotorD Ln(const RotorD& _rVal);
	[[nodiscard]] HC_INLINE RotorD Oscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime);
	[[nodiscard]] HC_INLINE RotorD DampedOscillate(const RotorD& _rMax, const RotorD& _rMin, double _dPeriod, double _dTime, double _dDampingFactor = 0.2f);
	[[nodiscard]] HC_INLINE RotorD SmoothStep(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD InverseSmoothStep(const RotorD& _rVal);
#endif
#endif
}