#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Vector.hpp>
#include <HellfireControl/Math/Matrix.hpp>
#include <HellfireControl/Math/Quaternion.hpp>

#if HC_USE_ROTOR
#include <HellfireControl/Math/Rotor.hpp>
#endif

namespace Math {
#pragma region Scalar
	/// <summary>
	/// Clamps the floating point _fVal to the range [_fMin, _fMax]. Defaults to between 0 and 1.
	/// </summary>
	/// <param name="_fVal: Value to clamp"></param>
	/// <param name="_fMin: Minimum permitted value"></param>
	/// <param name="_fMax: Maximum permitted value"></param>
	/// <returns>
	/// float: Clamped value
	/// </returns>
	[[nodiscard]] float Clamp(float _fVal, float _fMin = 0.0f, float _fMax = 1.0f);

	/// <summary>
	/// Generates a tweened value between _fStart and _fEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_fStart: Starting point of interpolation"></param>
	/// <param name="_fEnd: Ending point of interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _fStart and _fEnd"></param>
	/// <returns>
	/// float: Lerped value
	/// </returns>
	[[nodiscard]] float Lerp(float _fStart, float _fEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _fLowerBound and _fUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_fVal: The value to constrain"></param>
	/// <param name="_fLowerBound: The lowest value within the range given"></param>
	/// <param name="_fUpperBound: The highest value within the range given"></param>
	/// <returns>
	/// float: Constrained value
	/// </returns>
	[[nodiscard]] float Wrap(float _fVal, float _fLowerBound, float _fUpperBound);

	[[nodiscard]] float Abs(float _fVal);

	[[nodiscard]] float Ceiling(float _fVal);

	[[nodiscard]] float Floor(float _fVal);

	/// <summary>
	/// Raises _fBase to the power of _fExp (equivalent to std::powf).
	/// </summary>
	/// <param name="_fBase: The value being raised to the power of _fExp"></param>
	/// <param name="_fExp: The exponent value"></param>
	/// <returns>
	/// float: Result of the exponential
	/// </returns>
	[[nodiscard]] float Pow(float _fBase, float _fExp);

	/// <summary>
	/// Takes the square root of _fVal (equivalent to std::sqrtf).
	/// </summary>
	/// <param name="_fVal: The value being square rooted"></param>
	/// <returns>
	/// float: Result of the square root
	/// </returns>
	[[nodiscard]] float Sqrt(float _fVal);

	/// <summary>
	/// Computes the Log base 10 of _fVal (equivalent to std::log10f).
	/// </summary>
	/// <param name="_fVal: The value being taken to the Log base 10"></param>
	/// <returns>
	/// float: Result of the logarithm
	/// </returns>
	[[nodiscard]] float Log10(float _fVal);

	/// <summary>
	/// Computes the Log base 2 of _fVal (equivalent to std::log2f).
	/// </summary>
	/// <param name="_fVal: The value being taken to the Log base 2"></param>
	/// <returns>
	/// float: Result of the logarithm
	/// </returns>
	[[nodiscard]] float Log2(float _fVal);

	/// <summary>
	/// Computes the Natural Log of _fVal (equivalent to std::logf).
	/// </summary>
	/// <param name="_fVal: The value being taken to the Natrual Logarithm"></param>
	/// <returns>
	/// float: Result of the logarithm
	/// </returns>
	[[nodiscard]] float Ln(float _fVal);

	/// <summary>
	/// Computes e Raised to the power of _fVal (equivalent to std::expf).
	/// </summary>
	/// <param name="_fVal: The power to raise e"></param>
	/// <returns>
	/// float: Result of the calculation
	/// </returns>
	[[nodiscard]] float Exp(float _fVal);

	/// <summary>
	/// Computes the Sine of _fVal (equivalent to std::sinf).
	/// </summary>
	/// <param name="_fVal: The value to take the sine of"></param>
	/// <returns>
	/// float: Computed sine of _fVal
	/// </returns>
	[[nodiscard]] float Sin(float _fVal);

	/// <summary>
	/// Computes the Cosine of _fVal (equivalent to std::cosf).
	/// </summary>
	/// <param name="_fVal: The value to take the cosine of"></param>
	/// <returns>
	/// float: Computed cosine of _fVal
	/// </returns>
	[[nodiscard]] float Cos(float _fVal);

	/// <summary>
	/// Computes the Tangent of _fVal (equivalent to std::tanf).
	/// </summary>
	/// <param name="_fVal: The value to take the tangent of"></param>
	/// <returns>
	/// float: Computed tangent of _fVal
	/// </returns>
	[[nodiscard]] float Tan(float _fVal);

	/// <summary>
	/// Computes the Arc Sine of _fVal (equivalent to std::asinf).
	/// </summary>
	/// <param name="_fVal: The value to take the arc sine of"></param>
	/// <returns>
	/// float: Computed arc sine of _fVal
	/// </returns>
	[[nodiscard]] float ArcSin(float _fVal);

	/// <summary>
	/// Computes the Arc Cosine of _fVal (equivalent to std::acosf).
	/// </summary>
	/// <param name="_fVal: The value to take the arc cosine of"></param>
	/// <returns>
	/// float: Computed arc cosine of _fVal
	/// </returns>
	[[nodiscard]] float ArcCos(float _fVal);

	/// <summary>
	/// Computes the Arc Tangent of _fVal (equivalent to std::atanf).
	/// </summary>
	/// <param name="_fVal: The value to take the arc tangent of"></param>
	/// <returns>
	/// float: Computed arc tangent of _fVal
	/// </returns>
	[[nodiscard]] float ArcTan(float _fVal);

	/// <summary>
	/// Computes the Arc Tangent of [_fRight / _fLeft] (equivalent to std::atan2f).
	/// </summary>
	/// <param name="_fLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_fRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// float: Computed arc tan of [_fRight / _fLeft]
	/// </returns>
	[[nodiscard]] float ArcTan2(float _fLeft, float _fRight);

	/// <summary>
	/// Oscillates between _fMin and _fMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _fMax.
	/// </summary>
	/// <param name="_fMin: Minimum value to oscillate to"></param>
	/// <param name="_fMax: Maximum value to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// float: Value along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] float Oscillate(float _fMin, float _fMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _fMin and _fMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _fMax.
	/// </summary>
	/// <param name="_fMin: Minimum value to oscillate to"></param>
	/// <param name="_fMax: Maximum value to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// float: Value along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] float DampedOscillate(float _fMin, float _fMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _fStart and _fEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_fStart: The initial value to interpolate from"></param>
	/// <param name="_fEnd: The goal value to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// float: Interpolated value along the curve from _fStart to _fEnd
	/// </returns>
	[[nodiscard]] float SmoothStep(float _fStart, float _fEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _fCurrent to _fGoal utilizing a damped interpolation. Velocity is given by _fVelocity, and determines
	/// the rate of change. _fTimeDelta determines how far along to move _fCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _fGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_fCurrent: Current position along the curve to _fGoal"></param>
	/// <param name="_fGoal: The point to reach from _fCurrent"></param>
	/// <param name="_fVelocity: The rate of change at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _fGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// float: Interpolated value after calculation
	/// </returns>
	[[nodiscard]] float DampedSmoothStep(float _fCurrent, float _fGoal, float& _fVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _fVal. Assumes the value is constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_fVal: The value to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// float: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] float InverseSmoothStep(float _fVal);
#pragma endregion

#pragma region Vec2
	/// <summary>
	/// Clamps the Vec2F _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec2F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec2F Clamp(const Vec2F& _vVal, const Vec2F& _vMin, const Vec2F& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec2F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec2F ClampMagnitude(const Vec2F& _vVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec2F: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec2F Lerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec2F: Lerped vector
	/// </returns>
	[[nodiscard]] Vec2F NLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec2F: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec2F SLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec2F: Constrained vector
	/// </returns>
	[[nodiscard]] Vec2F Wrap(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound);

	[[nodiscard]] Vec2F Ceiling(Vec2F _fVal);

	[[nodiscard]] Vec2F Floor(Vec2F _fVal);

	/// <summary>
	/// Raises each component of _vBase to the power _fExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec2F: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec2F Pow(const Vec2F& _vBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec2F: Result of the square root
	/// </returns>
	[[nodiscard]] Vec2F Sqrt(const Vec2F& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec2F: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec2F Log10(const Vec2F& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec2F: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec2F Log2(const Vec2F& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec2F: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec2F Ln(const Vec2F& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec2F: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec2F Exp(const Vec2F& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec2F: Result of the sine
	/// </returns>
	[[nodiscard]] Vec2F Sin(const Vec2F& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec2F: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec2F Cos(const Vec2F& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec2F: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec2F Tan(const Vec2F& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec2F: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec2F ArcSin(const Vec2F& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec2F: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec2F ArcCos(const Vec2F& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec2F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec2F ArcTan(const Vec2F& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec2F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec2F ArcTan2(const Vec2F& _vLeft, const Vec2F& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec2F: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec2F Oscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec2F: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec2F DampedOscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec2F: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec2F SmoothStep(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _vCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _vGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _vGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec2F: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec2F DampedSmoothStep(const Vec2F& _vCurrent, const Vec2F& _vGoal, Vec2F& _vVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec2F: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec2F InverseSmoothStep(const Vec2F& _vVal);
#pragma endregion

#pragma region Vec3
	/// <summary>
	/// Clamps the Vec3F _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec3F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec3F Clamp(const Vec3F& _vVal, const Vec3F& _vMin, const Vec3F& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec3F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec3F ClampMagnitude(const Vec3F& _vVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec3F: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec3F Lerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec3F: Lerped vector
	/// </returns>
	[[nodiscard]] Vec3F NLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec3F: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec3F SLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec3F: Constrained vector
	/// </returns>
	[[nodiscard]] Vec3F Wrap(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound);

	[[nodiscard]] Vec3F Ceiling(Vec3F _fVal);

	[[nodiscard]] Vec3F Floor(Vec3F _fVal);

	/// <summary>
	/// Raises each component of _vBase to the power _fExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec3F: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec3F Pow(const Vec3F& _vBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec3F: Result of the square root
	/// </returns>
	[[nodiscard]] Vec3F Sqrt(const Vec3F& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec3F: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec3F Log10(const Vec3F& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec3F: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec3F Log2(const Vec3F& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec3F: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec3F Ln(const Vec3F& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec3F: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec3F Exp(const Vec3F& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec3F: Result of the sine
	/// </returns>
	[[nodiscard]] Vec3F Sin(const Vec3F& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec3F: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec3F Cos(const Vec3F& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec3F: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec3F Tan(const Vec3F& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec3F: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec3F ArcSin(const Vec3F& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec3F: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec3F ArcCos(const Vec3F& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec3F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec3F ArcTan(const Vec3F& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec3F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec3F ArcTan2(const Vec3F& _vLeft, const Vec3F& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec3F: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec3F Oscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec3F: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec3F DampedOscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec3F: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec3F SmoothStep(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _vCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _vGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _fGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec3F: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec3F DampedSmoothStep(const Vec3F& _vCurrent, const Vec3F& _vGoal, Vec3F& _vVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec3F: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec3F InverseSmoothStep(const Vec3F& _vVal);
#pragma endregion

#pragma region Vec4
	/// <summary>
	/// Clamps the Vec4F _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec4F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec4F Clamp(const Vec4F& _vVal, const Vec4F& _vMin, const Vec4F& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec4F: Clamped vector
	/// </returns>
	[[nodiscard]] Vec4F ClampMagnitude(const Vec4F& _vVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec4F: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec4F Lerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec4F: Lerped vector
	/// </returns>
	[[nodiscard]] Vec4F NLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec4F: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec4F SLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec4F: Constrained vector
	/// </returns>
	[[nodiscard]] Vec4F Wrap(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound);

	[[nodiscard]] Vec4F Ceiling(Vec4F _fVal);

	[[nodiscard]] Vec4F Floor(Vec4F _fVal);

	/// <summary>
	/// Raises each component of _vBase to the power _fExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec4F: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec4F Pow(const Vec4F& _vBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec4F: Result of the square root
	/// </returns>
	[[nodiscard]] Vec4F Sqrt(const Vec4F& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec4F: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec4F Log10(const Vec4F& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec4F: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec4F Log2(const Vec4F& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec4F: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec4F Ln(const Vec4F& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec4F: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec4F Exp(const Vec4F& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec4F: Result of the sine
	/// </returns>
	[[nodiscard]] Vec4F Sin(const Vec4F& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec4F: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec4F Cos(const Vec4F& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec4F: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec4F Tan(const Vec4F& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec4F: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec4F ArcSin(const Vec4F& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec4F: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec4F ArcCos(const Vec4F& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec4F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec4F ArcTan(const Vec4F& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec4F: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec4F ArcTan2(const Vec4F& _vLeft, const Vec4F& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec4F: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec4F Oscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec4F: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec4F DampedOscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec4F: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec4F SmoothStep(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _vCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _vGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _vGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec4F: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec4F DampedSmoothStep(const Vec4F& _vCurrent, const Vec4F& _vGoal, Vec4F& _vVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec4F: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec4F InverseSmoothStep(const Vec4F& _vVal);
#pragma endregion

#pragma region Matrix
	/// <summary>
	/// Clamps the MatrixF _mVal to the range [_mMin, _mMax].
	/// </summary>
	/// <param name="_mVal: The matrix to clamp"></param>
	/// <param name="_mMin: The matrix corresponding to the minimum value"></param>
	/// <param name="_mMax: The matrix corresponding to the maximum value"></param>
	/// <returns>
	/// MatrixF: Clamped matrix
	/// </returns>
	[[nodiscard]] MatrixF Clamp(const MatrixF& _mVal, const MatrixF& _mMin, const MatrixF& _mMax);

	/// <summary>
	/// Clamps the length of each row of _mVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_mVal: The matrix to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// MatrixF: Clamped matrix
	/// </returns>
	[[nodiscard]] MatrixF ClampMagnitude(const MatrixF& _mVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened matrix between _mStart and _mEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	MatrixF: Lerped matrix 
	/// </returns>
	[[nodiscard]] MatrixF Lerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound matrices and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// MatrixF: Lerped matrix
	/// </returns>
	[[nodiscard]] MatrixF NLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _mStart and _mEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// MatrixF: Interpolated matrix
	/// </returns>
	[[nodiscard]] MatrixF SLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _mLowerBound and _mUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_mVal: The value to constrain"></param>
	/// <param name="_mLowerBound: The lowest value in the range given"></param>
	/// <param name="_mUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// MatrixF: Constrained matrix
	/// </returns>
	[[nodiscard]] MatrixF Wrap(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound);

	[[nodiscard]] MatrixF Ceiling(MatrixF _fVal);

	[[nodiscard]] MatrixF Floor(MatrixF _fVal);

	/// <summary>
	/// Raises each component of _mBase to the power _fExp.
	/// </summary>
	/// <param name="_mBase: The matrix containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// MatrixF: Result of the exponential
	/// </returns>
	[[nodiscard]] MatrixF Pow(const MatrixF& _mBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to square root"></param>
	/// <returns>
	/// MatrixF: Result of the square root
	/// </returns>
	[[nodiscard]] MatrixF Sqrt(const MatrixF& _mVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute Log base 10"></param>
	/// <returns>
	/// MatrixF: Result of the Log base 10
	/// </returns>
	[[nodiscard]] MatrixF Log10(const MatrixF& _mVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute Log base 2"></param>
	/// <returns>
	/// MatrixF: Result of the Log base 2
	/// </returns>
	[[nodiscard]] MatrixF Log2(const MatrixF& _mVal);

	/// <summary>
	/// Computes the Natural Log of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the Natural Log"></param>
	/// <returns>
	/// MatrixF: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] MatrixF Ln(const MatrixF& _mVal);

	/// <summary>
	/// Computes e raised to the power of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to raise e to the power"></param>
	/// <returns>
	/// MatrixF: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] MatrixF Exp(const MatrixF& _mVal);

	/// <summary>
	/// Computes the sine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the sine"></param>
	/// <returns>
	/// MatrixF: Result of the sine
	/// </returns>
	[[nodiscard]] MatrixF Sin(const MatrixF& _mVal);

	/// <summary>
	/// Computes the cosine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the cosine"></param>
	/// <returns>
	/// MatrixF: Result of the cosine
	/// </returns>
	[[nodiscard]] MatrixF Cos(const MatrixF& _mVal);

	/// <summary>
	/// Computes the tangent of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the tangent"></param>
	/// <returns>
	/// MatrixF: Result of the tangent
	/// </returns>
	[[nodiscard]] MatrixF Tan(const MatrixF& _mVal);

	/// <summary>
	/// Computes the arc sine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc sine"></param>
	/// <returns>
	/// MatrixF: Result of the arc sine
	/// </returns>
	[[nodiscard]] MatrixF ArcSin(const MatrixF& _mVal);

	/// <summary>
	/// Computes the arc cosine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc cosine"></param>
	/// <returns>
	/// MatrixF: Result of the arc cosine
	/// </returns>
	[[nodiscard]] MatrixF ArcCos(const MatrixF& _mVal);

	/// <summary>
	/// Computes the arc tangent of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc tangent"></param>
	/// <returns>
	/// MatrixF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] MatrixF ArcTan(const MatrixF& _mVal);

	/// <summary>
	/// Computes the arc tangent of [_mRight / _mLeft] for each component of the respective matrices.
	/// </summary>
	/// <param name="_mLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_mRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// MatrixF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] MatrixF ArcTan2(const MatrixF& _mLeft, const MatrixF& _mRight);

	/// <summary>
	/// Oscillates between _mMin and _mMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _mMax.
	/// </summary>
	/// <param name="_mMin: Minimum matrix to oscillate to"></param>
	/// <param name="_mMax: Maximum matrix to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// MatrixF: Matrix along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] MatrixF Oscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _mMin and _mMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _mMax.
	/// </summary>
	/// <param name="_mMin: Minimum matrix to oscillate to"></param>
	/// <param name="_mMax: Maximum matrix to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// MatrixF: Matrix along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] MatrixF DampedOscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _mStart and _mEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_mStart: The initial matrix to interpolate from"></param>
	/// <param name="_mEnd: The goal matrix to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// MatrixF: Interpolated matrix along the curve from _mStart to _mEnd
	/// </returns>
	[[nodiscard]] MatrixF SmoothStep(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _mCurrent to _mGoal utilizing a damped interpolation. Velocity is given by _mVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _mCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _mGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_mCurrent: Current position along the curve to _mGoal"></param>
	/// <param name="_mGoal: The point to reach from _mCurrent"></param>
	/// <param name="_mVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _mGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// MatrixF: Interpolated matrix after calculation
	/// </returns>
	[[nodiscard]] MatrixF DampedSmoothStep(const MatrixF& _mCurrent, const MatrixF& _mGoal, MatrixF& _mVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _mVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_mVal: The matrix to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// MatrixF: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] MatrixF InverseSmoothStep(const MatrixF& _mVal);
#pragma endregion

#pragma region Quaternion
	/// <summary>
	/// Clamps the QuaternionF _qVal to the range [_qMin, _qMax].
	/// </summary>
	/// <param name="_qVal: The quaternion to clamp"></param>
	/// <param name="_qMin: The quaternion corresponding to the minimum value"></param>
	/// <param name="_qMax: The quaternion corresponding to the maximum value"></param>
	/// <returns>
	/// QuaternionF: Clamped quaternion
	/// </returns>
	[[nodiscard]] QuaternionF Clamp(const QuaternionF& _qVal, const QuaternionF& _qMin, const QuaternionF& _qMax);

	/// <summary>
	/// Clamps the length of _qVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_qVal: The quaternion to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// QuaternionF: Clamped quaternion
	/// </returns>
	[[nodiscard]] QuaternionF ClampMagnitude(const QuaternionF& _qVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened quaternion between _qStart and _qEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _qStart and _qEnd"></param>
	/// <returns>
	///	QuaternionF: Lerped quaternion 
	/// </returns>
	[[nodiscard]] QuaternionF Lerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound quaternions and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _qStart and _qEnd"></param>
	/// <returns>
	/// QuaternionF: Lerped quaternion
	/// </returns>
	[[nodiscard]] QuaternionF NLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _qStart and _qEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _qStart and _qEnd"></param>
	/// <returns>
	/// QuatenrionF: Interpolated quaternion
	/// </returns>
	[[nodiscard]] QuaternionF SLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _qLowerBound and _qUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_qVal: The value to constrain"></param>
	/// <param name="_qLowerBound: The lowest value in the range given"></param>
	/// <param name="_qUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// QuaternionF: Constrained quaternion
	/// </returns>
	[[nodiscard]] QuaternionF Wrap(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound);

	[[nodiscard]] QuaternionF Ceiling(QuaternionF _fVal);

	[[nodiscard]] QuaternionF Floor(QuaternionF _fVal);

	/// <summary>
	/// Raises each component of _qBase to the power _fExp.
	/// </summary>
	/// <param name="_qBase: The quaternion containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// QuaternionF: Result of the exponential
	/// </returns>
	[[nodiscard]] QuaternionF Pow(const QuaternionF& _qBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to square root"></param>
	/// <returns>
	/// QuaternionF: Result of the square root
	/// </returns>
	[[nodiscard]] QuaternionF Sqrt(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute Log base 10"></param>
	/// <returns>
	/// QuaternionF: Result of the Log base 10
	/// </returns>
	[[nodiscard]] QuaternionF Log10(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute Log base 2"></param>
	/// <returns>
	/// QuaternionF: Result of the Log base 2
	/// </returns>
	[[nodiscard]] QuaternionF Log2(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the Natural Log of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the Natural Log"></param>
	/// <returns>
	/// QuaternionF: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] QuaternionF Ln(const QuaternionF& _qVal);

	/// <summary>
	/// Computes e raised to the power of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to raise e to the power"></param>
	/// <returns>
	/// QuaternionF: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] QuaternionF Exp(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the sine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the sine"></param>
	/// <returns>
	/// QuaternionF: Result of the sine
	/// </returns>
	[[nodiscard]] QuaternionF Sin(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the cosine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the cosine"></param>
	/// <returns>
	/// QuaternionF: Result of the cosine
	/// </returns>
	[[nodiscard]] QuaternionF Cos(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the tangent of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the tangent"></param>
	/// <returns>
	/// QuaternionF: Result of the tangent
	/// </returns>
	[[nodiscard]] QuaternionF Tan(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the arc sine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc sine"></param>
	/// <returns>
	/// QuaternionF: Result of the arc sine
	/// </returns>
	[[nodiscard]] QuaternionF ArcSin(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the arc cosine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc cosine"></param>
	/// <returns>
	/// QuaternionF: Result of the arc cosine
	/// </returns>
	[[nodiscard]] QuaternionF ArcCos(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the arc tangent of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc tangent"></param>
	/// <returns>
	/// QuaternionF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] QuaternionF ArcTan(const QuaternionF& _qVal);

	/// <summary>
	/// Computes the arc tangent of [_qRight / _qLeft] for each component of the respective quaternions.
	/// </summary>
	/// <param name="_qLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_qRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// QuaternionF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] QuaternionF ArcTan2(const QuaternionF& _qLeft, const QuaternionF& _qRight);

	/// <summary>
	/// Oscillates between _qMin and _qMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _qMax.
	/// </summary>
	/// <param name="_qMin: Minimum quaternion to oscillate to"></param>
	/// <param name="_qMax: Maximum quaternion to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// QuaternionF: Quaternion along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] QuaternionF Oscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _qMin and _qMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _qMax.
	/// </summary>
	/// <param name="_qMin: Minimum quaternion to oscillate to"></param>
	/// <param name="_qMax: Maximum quaternion to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// QuaternionF: Quaternion along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] QuaternionF DampedOscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _qStart and _qEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_qStart: The initial quaternion to interpolate from"></param>
	/// <param name="_qEnd: The goal quaternion to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// QuaternionF: Interpolated quaternion along the curve from _qStart to _qEnd
	/// </returns>
	[[nodiscard]] QuaternionF SmoothStep(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _qCurrent to _qGoal utilizing a damped interpolation. Velocity is given by _qVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _qCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _qGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_qCurrent: Current position along the curve to _qGoal"></param>
	/// <param name="_qGoal: The point to reach from _qCurrent"></param>
	/// <param name="_qVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _qGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// QuaternionF: Interpolated quaternion after calculation
	/// </returns>
	[[nodiscard]] QuaternionF DampedSmoothStep(const QuaternionF& _qCurrent, const QuaternionF& _qGoal, QuaternionF& _qVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _qVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_qVal: The quaternion to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// QuaternionF: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] QuaternionF InverseSmoothStep(const QuaternionF& _qVal);
#pragma endregion
#if HC_ENABLE_DOUBLE_PRECISION
#pragma region Scalar
	/// <summary>
	/// Clamps the double floating point _dVal to the range [_dMin, _dMax]. Defaults to between 0 and 1.
	/// </summary>
	/// <param name="_dVal: Value to clamp"></param>
	/// <param name="_dMin: Minimum permitted value"></param>
	/// <param name="_dMax: Maximum permitted value"></param>
	/// <returns>
	/// double: Clamped value
	/// </returns>
	[[nodiscard]] double Clamp(double _dVal, double _dMin = 0.0, double _dMax = 1.0);

	/// <summary>
	/// Generates a tweened value between _dStart and _dEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_dStart: Starting point of interpolation"></param>
	/// <param name="_dEnd: Ending point of interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _fStart and _fEnd"></param>
	/// <returns>
	/// double: Lerped value
	/// </returns>
	[[nodiscard]] double Lerp(double _dStart, double _dEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _dLowerBound and _dUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_dVal: The value to constrain"></param>
	/// <param name="_dLowerBound: The lowest value within the range given"></param>
	/// <param name="_dUpperBound: The highest value within the range given"></param>
	/// <returns>
	/// double: Constrained value
	/// </returns>
	[[nodiscard]] double Wrap(double _dVal, double _dLowerBound, double _dUpperBound);

	/// <summary>
	/// Raises _dBase to the power of _dExp (equivalent to std::pow).
	/// </summary>
	/// <param name="_dBase: The value being raised to the power of _dExp"></param>
	/// <param name="_dExp: The exponent value"></param>
	/// <returns>
	/// double: Result of the exponential
	/// </returns>
	[[nodiscard]] double Pow(double _dBase, double _dExp);

	/// <summary>
	/// Takes the square root of _dVal (equivalent to std::sqrt).
	/// </summary>
	/// <param name="_dVal: The value being square rooted"></param>
	/// <returns>
	/// double: Result of the square root
	/// </returns>
	[[nodiscard]] double Sqrt(double _dVal);

	/// <summary>
	/// Computes the Log base 10 of _dVal (equivalent to std::log10).
	/// </summary>
	/// <param name="_dVal: The value being taken to the Log base 10"></param>
	/// <returns>
	/// double: Result of the logarithm
	/// </returns>
	[[nodiscard]] double Log10(double _dVal);

	/// <summary>
	/// Computes the Log base 2 of _dVal (equivalent to std::log2).
	/// </summary>
	/// <param name="_dVal: The value being taken to the Log base 2"></param>
	/// <returns>
	/// double: Result of the logarithm
	/// </returns>
	[[nodiscard]] double Log2(double _dVal);

	/// <summary>
	/// Computes the Natural Log of _dVal (equivalent to std::log).
	/// </summary>
	/// <param name="_dVal: The value being taken to the Natrual Logarithm"></param>
	/// <returns>
	/// double: Result of the logarithm
	/// </returns>
	[[nodiscard]] double Ln(double _dVal);

	/// <summary>
	/// Computes e Raised to the power of _dVal (equivalent to std::exp).
	/// </summary>
	/// <param name="_dVal: The power to raise e"></param>
	/// <returns>
	/// double: Result of the calculation
	/// </returns>
	[[nodiscard]] double Exp(double _dVal);

	/// <summary>
	/// Computes the Sine of _dVal (equivalent to std::sin).
	/// </summary>
	/// <param name="_dVal: The value to take the sine of"></param>
	/// <returns>
	/// double: Computed sine of _dVal
	/// </returns>
	[[nodiscard]] double Sin(double _dVal);

	/// <summary>
	/// Computes the Cosine of _dVal (equivalent to std::cos).
	/// </summary>
	/// <param name="_dVal: The value to take the cosine of"></param>
	/// <returns>
	/// double: Computed cosine of _dVal
	/// </returns>
	[[nodiscard]] double Cos(double _dVal);

	/// <summary>
	/// Computes the Tangent of _dVal (equivalent to std::tan).
	/// </summary>
	/// <param name="_dVal: The value to take the tangent of"></param>
	/// <returns>
	/// double: Computed tangent of _dVal
	/// </returns>
	[[nodiscard]] double Tan(double _dVal);

	/// <summary>
	/// Computes the Arc Sine of _dVal (equivalent to std::asin).
	/// </summary>
	/// <param name="_dVal: The value to take the arc sine of"></param>
	/// <returns>
	/// double: Computed arc sine of _dVal
	/// </returns>
	[[nodiscard]] double ArcSin(double _dVal);

	/// <summary>
	/// Computes the Arc Cosine of _dVal (equivalent to std::acos).
	/// </summary>
	/// <param name="_dVal: The value to take the arc cosine of"></param>
	/// <returns>
	/// double: Computed arc cosine of _dVal
	/// </returns>
	[[nodiscard]] double ArcCos(double _dVal);

	/// <summary>
	/// Computes the Arc Tangent of _dVal (equivalent to std::atan).
	/// </summary>
	/// <param name="_dVal: The value to take the arc tangent of"></param>
	/// <returns>
	/// double: Computed arc tangent of _dVal
	/// </returns>
	[[nodiscard]] double ArcTan(double _dVal);

	/// <summary>
	/// Computes the Arc Tangent of [_dRight / _dLeft] (equivalent to std::atan2).
	/// </summary>
	/// <param name="_dLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_dRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// double: Computed arc tan of [_dRight / _dLeft]
	/// </returns>
	[[nodiscard]] double ArcTan2(double _dLeft, double _dRight);

	/// <summary>
	/// Oscillates between _dMin and _dMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _dMax.
	/// </summary>
	/// <param name="_dMin: Minimum value to oscillate to"></param>
	/// <param name="_dMax: Maximum value to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// double: Value along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] double Oscillate(double _dMin, double _dMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _dMin and _dMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _dMax.
	/// </summary>
	/// <param name="_dMin: Minimum value to oscillate to"></param>
	/// <param name="_dMax: Maximum value to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// double: Value along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] double DampedOscillate(double _dMin, double _dMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _dStart and _dEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_dStart: The initial value to interpolate from"></param>
	/// <param name="_dEnd: The goal value to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// double: Interpolated value along the curve from _dStart to _dEnd
	/// </returns>
	[[nodiscard]] double SmoothStep(double _dStart, double _dEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _dCurrent to _dGoal utilizing a damped interpolation. Velocity is given by _dVelocity, and determines
	/// the rate of change. _dTimeDelta determines how far along to move _dCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _dGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_dCurrent: Current position along the curve to _fGoal"></param>
	/// <param name="_dGoal: The point to reach from _dCurrent"></param>
	/// <param name="_dVelocity: The rate of change at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _fGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// double: Interpolated value after calculation
	/// </returns>
	[[nodiscard]] double DampedSmoothStep(double _dCurrent, double _dGoal, double& _dVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _dVal. Assumes the value is constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_dVal: The value to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// double: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] double InverseSmoothStep(double _dVal);
#pragma endregion

#pragma region Vec2
	/// <summary>
	/// Clamps the Vec2D _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec2D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec2D Clamp(const Vec2D& _vVal, const Vec2D& _vMin, const Vec2D& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_dMin, _dMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec2D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec2D ClampMagnitude(const Vec2D& _vVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec2D: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec2D Lerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec2D: Lerped vector
	/// </returns>
	[[nodiscard]] Vec2D NLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec2D: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec2D SLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec2D: Constrained vector
	/// </returns>
	[[nodiscard]] Vec2D Wrap(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound);

	/// <summary>
	/// Raises each component of _vBase to the power _fExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec2D: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec2D Pow(const Vec2D& _vBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec2D: Result of the square root
	/// </returns>
	[[nodiscard]] Vec2D Sqrt(const Vec2D& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec2D: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec2D Log10(const Vec2D& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec2D: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec2D Log2(const Vec2D& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec2D: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec2D Ln(const Vec2D& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec2D: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec2D Exp(const Vec2D& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec2D: Result of the sine
	/// </returns>
	[[nodiscard]] Vec2D Sin(const Vec2D& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec2D: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec2D Cos(const Vec2D& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec2D: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec2D Tan(const Vec2D& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec2D: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec2D ArcSin(const Vec2D& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec2D: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec2D ArcCos(const Vec2D& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec2D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec2D ArcTan(const Vec2D& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec2D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec2D ArcTan2(const Vec2D& _vLeft, const Vec2D& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec2D: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec2D Oscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec2D: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec2D DampedOscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec2D: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec2D SmoothStep(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _vCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _vGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _vGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec2D: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec2D DampedSmoothStep(const Vec2D& _vCurrent, const Vec2D& _vGoal, Vec2D& _vVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec2D: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec2D InverseSmoothStep(const Vec2D& _vVal);
#pragma endregion

#pragma region Vec3
	/// <summary>
	/// Clamps the Vec3D _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec3D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec3D Clamp(const Vec3D& _vVal, const Vec3D& _vMin, const Vec3D& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec3D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec3D ClampMagnitude(const Vec3D& _vVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec3D: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec3D Lerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec3D: Lerped vector
	/// </returns>
	[[nodiscard]] Vec3D NLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec3D: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec3D SLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec3D: Constrained vector
	/// </returns>
	[[nodiscard]] Vec3D Wrap(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound);

	/// <summary>
	/// Raises each component of _vBase to the power _dExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_dExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec3D: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec3D Pow(const Vec3D& _vBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec3D: Result of the square root
	/// </returns>
	[[nodiscard]] Vec3D Sqrt(const Vec3D& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec3D: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec3D Log10(const Vec3D& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec3D: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec3D Log2(const Vec3D& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec3D: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec3D Ln(const Vec3D& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec3D: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec3D Exp(const Vec3D& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec3D: Result of the sine
	/// </returns>
	[[nodiscard]] Vec3D Sin(const Vec3D& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec3D: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec3D Cos(const Vec3D& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec3D: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec3D Tan(const Vec3D& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec3D: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec3D ArcSin(const Vec3D& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec3D: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec3D ArcCos(const Vec3D& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec3D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec3D ArcTan(const Vec3D& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec3D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec3D ArcTan2(const Vec3D& _vLeft, const Vec3D& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec3D: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec3D Oscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec3D: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec3D DampedOscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec3D: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec3D SmoothStep(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _vCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _vGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _vGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec3D: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec3D DampedSmoothStep(const Vec3D& _vCurrent, const Vec3D& _vGoal, Vec3D& _vVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec3D: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec3D InverseSmoothStep(const Vec3D& _vVal);
#pragma endregion

#pragma region Vec4
	/// <summary>
	/// Clamps the Vec4D _vVal to the range [_vMin, _vMax].
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_vMin: The vector corresponding to the minimum value"></param>
	/// <param name="_vMax: The vector corresponding to the maximum value"></param>
	/// <returns>
	/// Vec4D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec4D Clamp(const Vec4D& _vVal, const Vec4D& _vMin, const Vec4D& _vMax);

	/// <summary>
	/// Clamps the length of _vVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_vVal: The vector to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// Vec4D: Clamped vector
	/// </returns>
	[[nodiscard]] Vec4D ClampMagnitude(const Vec4D& _vVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened vector between _vStart and _vEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	Vec4D: Lerped vector 
	/// </returns>
	[[nodiscard]] Vec4D Lerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound vectors and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec4D: Lerped vector
	/// </returns>
	[[nodiscard]] Vec4D NLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _vStart and _vEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_vStart: Starting point of the interpolation"></param>
	/// <param name="_vEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// Vec4D: Interpolated vector
	/// </returns>
	[[nodiscard]] Vec4D SLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _vLowerBound and _vUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_vVal: The value to constrain"></param>
	/// <param name="_vLowerBound: The lowest value in the range given"></param>
	/// <param name="_vUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// Vec4D: Constrained vector
	/// </returns>
	[[nodiscard]] Vec4D Wrap(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound);

	/// <summary>
	/// Raises each component of _vBase to the power _dExp.
	/// </summary>
	/// <param name="_vBase: The vector containing each value to raise to the power _fExp"></param>
	/// <param name="_dExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// Vec4D: Result of the exponential
	/// </returns>
	[[nodiscard]] Vec4D Pow(const Vec4D& _vBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to square root"></param>
	/// <returns>
	/// Vec4D: Result of the square root
	/// </returns>
	[[nodiscard]] Vec4D Sqrt(const Vec4D& _vVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 10"></param>
	/// <returns>
	/// Vec4D: Result of the Log base 10
	/// </returns>
	[[nodiscard]] Vec4D Log10(const Vec4D& _vVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute Log base 2"></param>
	/// <returns>
	/// Vec4D: Result of the Log base 2
	/// </returns>
	[[nodiscard]] Vec4D Log2(const Vec4D& _vVal);

	/// <summary>
	/// Computes the Natural Log of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the Natural Log"></param>
	/// <returns>
	/// Vec4D: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] Vec4D Ln(const Vec4D& _vVal);

	/// <summary>
	/// Computes e raised to the power of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to raise e to the power"></param>
	/// <returns>
	/// Vec4D: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] Vec4D Exp(const Vec4D& _vVal);

	/// <summary>
	/// Computes the sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the sine"></param>
	/// <returns>
	/// Vec4D: Result of the sine
	/// </returns>
	[[nodiscard]] Vec4D Sin(const Vec4D& _vVal);

	/// <summary>
	/// Computes the cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the cosine"></param>
	/// <returns>
	/// Vec4D: Result of the cosine
	/// </returns>
	[[nodiscard]] Vec4D Cos(const Vec4D& _vVal);

	/// <summary>
	/// Computes the tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the tangent"></param>
	/// <returns>
	/// Vec4D: Result of the tangent
	/// </returns>
	[[nodiscard]] Vec4D Tan(const Vec4D& _vVal);

	/// <summary>
	/// Computes the arc sine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc sine"></param>
	/// <returns>
	/// Vec4D: Result of the arc sine
	/// </returns>
	[[nodiscard]] Vec4D ArcSin(const Vec4D& _vVal);

	/// <summary>
	/// Computes the arc cosine of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc cosine"></param>
	/// <returns>
	/// Vec4D: Result of the arc cosine
	/// </returns>
	[[nodiscard]] Vec4D ArcCos(const Vec4D& _vVal);

	/// <summary>
	/// Computes the arc tangent of each component of _vVal.
	/// </summary>
	/// <param name="_vVal: The vector containing each value to compute the arc tangent"></param>
	/// <returns>
	/// Vec4D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec4D ArcTan(const Vec4D& _vVal);

	/// <summary>
	/// Computes the arc tangent of [_vRight / _vLeft] for each component of the respective vectors.
	/// </summary>
	/// <param name="_vLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_vRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// Vec4D: Result of the arc tangent
	/// </returns>
	[[nodiscard]] Vec4D ArcTan2(const Vec4D& _vLeft, const Vec4D& _vRight);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// Vec4D: Vector along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec4D Oscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _vMin and _vMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _vMax.
	/// </summary>
	/// <param name="_vMin: Minimum vector to oscillate to"></param>
	/// <param name="_vMax: Maximum vector to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// Vec4D: Vector along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] Vec4D DampedOscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _vStart and _vEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_vStart: The initial vector to interpolate from"></param>
	/// <param name="_vEnd: The goal vector to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// Vec4D: Interpolated vector along the curve from _vStart to _vEnd
	/// </returns>
	[[nodiscard]] Vec4D SmoothStep(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _vCurrent to _vGoal utilizing a damped interpolation. Velocity is given by _vVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _vCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _vGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_vCurrent: Current position along the curve to _vGoal"></param>
	/// <param name="_vGoal: The point to reach from _vCurrent"></param>
	/// <param name="_vVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _vGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// Vec4D: Interpolated vector after calculation
	/// </returns>
	[[nodiscard]] Vec4D DampedSmoothStep(const Vec4D& _vCurrent, const Vec4D& _vGoal, Vec4D& _vVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _vVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_vVal: The vector to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// Vec4D: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] Vec4D InverseSmoothStep(const Vec4D& _vVal);
#pragma endregion

#pragma region Matrix
	/// <summary>
	/// Clamps the MatrixD _mVal to the range [_mMin, _mMax].
	/// </summary>
	/// <param name="_mVal: The matrix to clamp"></param>
	/// <param name="_mMin: The matrix corresponding to the minimum value"></param>
	/// <param name="_mMax: The matrix corresponding to the maximum value"></param>
	/// <returns>
	/// MatrixD: Clamped matrix
	/// </returns>
	[[nodiscard]] MatrixD Clamp(const MatrixD& _mVal, const MatrixD& _mMin, const MatrixD& _mMax);

	/// <summary>
	/// Clamps the length of each row of _mVal to the range [_dMin, _dMax]
	/// </summary>
	/// <param name="_mVal: The matrix to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// MatrixD: Clamped matrix
	/// </returns>
	[[nodiscard]] MatrixD ClampMagnitude(const MatrixD& _mVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened matrix between _mStart and _mEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	///	MatrixD: Lerped matrix 
	/// </returns>
	[[nodiscard]] MatrixD Lerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound matrices and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _vStart and _vEnd"></param>
	/// <returns>
	/// MatrixD: Lerped matrix
	/// </returns>
	[[nodiscard]] MatrixD NLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _mStart and _mEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_mStart: Starting point of the interpolation"></param>
	/// <param name="_mEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _vStart and _vEnd"></param>
	/// <returns>
	/// MatrixD: Interpolated matrix
	/// </returns>
	[[nodiscard]] MatrixD SLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _mLowerBound and _mUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_mVal: The value to constrain"></param>
	/// <param name="_mLowerBound: The lowest value in the range given"></param>
	/// <param name="_mUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// MatrixD: Constrained matrix
	/// </returns>
	[[nodiscard]] MatrixD Wrap(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound);

	/// <summary>
	/// Raises each component of _mBase to the power _dExp.
	/// </summary>
	/// <param name="_mBase: The matrix containing each value to raise to the power _fExp"></param>
	/// <param name="_dExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// MatrixD: Result of the exponential
	/// </returns>
	[[nodiscard]] MatrixD Pow(const MatrixD& _mBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to square root"></param>
	/// <returns>
	/// MatrixD: Result of the square root
	/// </returns>
	[[nodiscard]] MatrixD Sqrt(const MatrixD& _mVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute Log base 10"></param>
	/// <returns>
	/// MatrixD: Result of the Log base 10
	/// </returns>
	[[nodiscard]] MatrixD Log10(const MatrixD& _mVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute Log base 2"></param>
	/// <returns>
	/// MatrixD: Result of the Log base 2
	/// </returns>
	[[nodiscard]] MatrixD Log2(const MatrixD& _mVal);

	/// <summary>
	/// Computes the Natural Log of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the Natural Log"></param>
	/// <returns>
	/// MatrixD: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] MatrixD Ln(const MatrixD& _mVal);

	/// <summary>
	/// Computes e raised to the power of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to raise e to the power"></param>
	/// <returns>
	/// MatrixD: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] MatrixD Exp(const MatrixD& _mVal);

	/// <summary>
	/// Computes the sine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the sine"></param>
	/// <returns>
	/// MatrixD: Result of the sine
	/// </returns>
	[[nodiscard]] MatrixD Sin(const MatrixD& _mVal);

	/// <summary>
	/// Computes the cosine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the cosine"></param>
	/// <returns>
	/// MatrixD: Result of the cosine
	/// </returns>
	[[nodiscard]] MatrixD Cos(const MatrixD& _mVal);

	/// <summary>
	/// Computes the tangent of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the tangent"></param>
	/// <returns>
	/// MatrixD: Result of the tangent
	/// </returns>
	[[nodiscard]] MatrixD Tan(const MatrixD& _mVal);

	/// <summary>
	/// Computes the arc sine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc sine"></param>
	/// <returns>
	/// MatrixD: Result of the arc sine
	/// </returns>
	[[nodiscard]] MatrixD ArcSin(const MatrixD& _mVal);

	/// <summary>
	/// Computes the arc cosine of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc cosine"></param>
	/// <returns>
	/// MatrixD: Result of the arc cosine
	/// </returns>
	[[nodiscard]] MatrixD ArcCos(const MatrixD& _mVal);

	/// <summary>
	/// Computes the arc tangent of each component of _mVal.
	/// </summary>
	/// <param name="_mVal: The matrix containing each value to compute the arc tangent"></param>
	/// <returns>
	/// MatrixD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] MatrixD ArcTan(const MatrixD& _mVal);

	/// <summary>
	/// Computes the arc tangent of [_mRight / _mLeft] for each component of the respective matrices.
	/// </summary>
	/// <param name="_mLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_mRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// MatrixD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] MatrixD ArcTan2(const MatrixD& _mLeft, const MatrixD& _mRight);

	/// <summary>
	/// Oscillates between _mMin and _mMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _mMax.
	/// </summary>
	/// <param name="_mMin: Minimum matrix to oscillate to"></param>
	/// <param name="_mMax: Maximum matrix to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// MatrixD: Matrix along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] MatrixD Oscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _mMin and _mMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _mMax.
	/// </summary>
	/// <param name="_mMin: Minimum matrix to oscillate to"></param>
	/// <param name="_mMax: Maximum matrix to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// MatrixD: Matrix along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] MatrixD DampedOscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _mStart and _mEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_mStart: The initial matrix to interpolate from"></param>
	/// <param name="_mEnd: The goal matrix to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// MatrixF: Interpolated matrix along the curve from _mStart to _mEnd
	/// </returns>
	[[nodiscard]] MatrixD SmoothStep(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _mCurrent to _mGoal utilizing a damped interpolation. Velocity is given by _mVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _mCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _mGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_mCurrent: Current position along the curve to _mGoal"></param>
	/// <param name="_mGoal: The point to reach from _mCurrent"></param>
	/// <param name="_mVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _mGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// MatrixD: Interpolated matrix after calculation
	/// </returns>
	[[nodiscard]] MatrixD DampedSmoothStep(const MatrixD& _mCurrent, const MatrixD& _mGoal, MatrixD& _mVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _mVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_mVal: The matrix to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// MatrixD: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] MatrixD InverseSmoothStep(const MatrixD& _mVal);
#pragma endregion

#pragma region Quaternion
	/// <summary>
	/// Clamps the QuaternionD _qVal to the range [_qMin, _qMax].
	/// </summary>
	/// <param name="_qVal: The quaternion to clamp"></param>
	/// <param name="_qMin: The quaternion corresponding to the minimum value"></param>
	/// <param name="_qMax: The quaternion corresponding to the maximum value"></param>
	/// <returns>
	/// QuaternionD: Clamped quaternion
	/// </returns>
	[[nodiscard]] QuaternionD Clamp(const QuaternionD& _qVal, const QuaternionD& _qMin, const QuaternionD& _qMax);

	/// <summary>
	/// Clamps the length of _qVal to the range [_dMin, _dMax]
	/// </summary>
	/// <param name="_qVal: The quaternion to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// QuaternionD: Clamped quaternion
	/// </returns>
	[[nodiscard]] QuaternionD ClampMagnitude(const QuaternionD& _qVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened quaternion between _qStart and _qEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _qStart and _qEnd"></param>
	/// <returns>
	///	QuaternionD: Lerped quaternion 
	/// </returns>
	[[nodiscard]] QuaternionD Lerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound quaternions and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _qStart and _qEnd"></param>
	/// <returns>
	/// QuaternionD: Lerped quaternion
	/// </returns>
	[[nodiscard]] QuaternionD NLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _qStart and _qEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_qStart: Starting point of the interpolation"></param>
	/// <param name="_qEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _qStart and _qEnd"></param>
	/// <returns>
	/// QuatenrionD: Interpolated quaternion
	/// </returns>
	[[nodiscard]] QuaternionD SLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _qLowerBound and _qUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_qVal: The value to constrain"></param>
	/// <param name="_qLowerBound: The lowest value in the range given"></param>
	/// <param name="_qUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// QuaternionD: Constrained quaternion
	/// </returns>
	[[nodiscard]] QuaternionD Wrap(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound);

	/// <summary>
	/// Raises each component of _qBase to the power _dExp.
	/// </summary>
	/// <param name="_qBase: The quaternion containing each value to raise to the power _dExp"></param>
	/// <param name="_dExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// QuaternionD: Result of the exponential
	/// </returns>
	[[nodiscard]] QuaternionD Pow(const QuaternionD& _qBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to square root"></param>
	/// <returns>
	/// QuaternionD: Result of the square root
	/// </returns>
	[[nodiscard]] QuaternionD Sqrt(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute Log base 10"></param>
	/// <returns>
	/// QuaternionD: Result of the Log base 10
	/// </returns>
	[[nodiscard]] QuaternionD Log10(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute Log base 2"></param>
	/// <returns>
	/// QuaternionD: Result of the Log base 2
	/// </returns>
	[[nodiscard]] QuaternionD Log2(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the Natural Log of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the Natural Log"></param>
	/// <returns>
	/// QuaternionD: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] QuaternionD Ln(const QuaternionD& _qVal);

	/// <summary>
	/// Computes e raised to the power of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to raise e to the power"></param>
	/// <returns>
	/// QuaternionD: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] QuaternionD Exp(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the sine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the sine"></param>
	/// <returns>
	/// QuaternionD: Result of the sine
	/// </returns>
	[[nodiscard]] QuaternionD Sin(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the cosine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the cosine"></param>
	/// <returns>
	/// QuaternionD: Result of the cosine
	/// </returns>
	[[nodiscard]] QuaternionD Cos(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the tangent of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the tangent"></param>
	/// <returns>
	/// QuaternionD: Result of the tangent
	/// </returns>
	[[nodiscard]] QuaternionD Tan(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the arc sine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc sine"></param>
	/// <returns>
	/// QuaternionD: Result of the arc sine
	/// </returns>
	[[nodiscard]] QuaternionD ArcSin(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the arc cosine of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc cosine"></param>
	/// <returns>
	/// QuaternionD: Result of the arc cosine
	/// </returns>
	[[nodiscard]] QuaternionD ArcCos(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the arc tangent of each component of _qVal.
	/// </summary>
	/// <param name="_qVal: The quaternion containing each value to compute the arc tangent"></param>
	/// <returns>
	/// QuaternionD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] QuaternionD ArcTan(const QuaternionD& _qVal);

	/// <summary>
	/// Computes the arc tangent of [_qRight / _qLeft] for each component of the respective quaternions.
	/// </summary>
	/// <param name="_qLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_qRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// QuaternionD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] QuaternionD ArcTan2(const QuaternionD& _qLeft, const QuaternionD& _qRight);

	/// <summary>
	/// Oscillates between _qMin and _qMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _qMax.
	/// </summary>
	/// <param name="_qMin: Minimum quaternion to oscillate to"></param>
	/// <param name="_qMax: Maximum quaternion to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// QuaternionD: Quaternion along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] QuaternionD Oscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _qMin and _qMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _qMax.
	/// </summary>
	/// <param name="_qMin: Minimum quaternion to oscillate to"></param>
	/// <param name="_qMax: Maximum quaternion to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// QuaternionD: Quaternion along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] QuaternionD DampedOscillate(const QuaternionD& _vMin, const QuaternionD& _qMax, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _qStart and _qEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_qStart: The initial quaternion to interpolate from"></param>
	/// <param name="_qEnd: The goal quaternion to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// QuaternionD: Interpolated quaternion along the curve from _qStart to _qEnd
	/// </returns>
	[[nodiscard]] QuaternionD SmoothStep(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _qCurrent to _qGoal utilizing a damped interpolation. Velocity is given by _qVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _qCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _qGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_qCurrent: Current position along the curve to _qGoal"></param>
	/// <param name="_qGoal: The point to reach from _qCurrent"></param>
	/// <param name="_qVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _qGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// QuaternionD: Interpolated quaternion after calculation
	/// </returns>
	[[nodiscard]] QuaternionD DampedSmoothStep(const QuaternionD& _qCurrent, const QuaternionD& _qGoal, QuaternionD& _qVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _qVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_qVal: The quaternion to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// QuaternionD: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] QuaternionD InverseSmoothStep(const QuaternionD& _qVal);
#pragma endregion
#endif

#if HC_USE_ROTOR
	/// <summary>
	/// Clamps the RotorF _rVal to the range [_rMin, _rMax].
	/// </summary>
	/// <param name="_rVal: The rotor to clamp"></param>
	/// <param name="_rMin: The rotor corresponding to the minimum value"></param>
	/// <param name="_rMax: The rotor corresponding to the maximum value"></param>
	/// <returns>
	/// RotorF: Clamped rotor
	/// </returns>
	[[nodiscard]] RotorF Clamp(const RotorF& _rVal, const RotorF& _rMin, const RotorF& _rMax);

	/// <summary>
	/// Clamps the length of _rVal to the range [_fMin, _fMax]
	/// </summary>
	/// <param name="_rVal: The rotor to clamp"></param>
	/// <param name="_fMin: Minimum clamp value"></param>
	/// <param name="_fMax: Maximum clamp value"></param>
	/// <returns>
	/// RotorF: Clamped rotor
	/// </returns>
	[[nodiscard]] RotorF ClampMagnitude(const RotorF& _rVal, float _fMin, float _fMax);

	/// <summary>
	/// Generates a tweened rotor between _rStart and _rEnd of _fRatio distance along the route.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _rStart and _rEnd"></param>
	/// <returns>
	///	RotorF: Lerped rotor 
	/// </returns>
	[[nodiscard]] RotorF Lerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);

	/// <summary>
	/// Normalizes the two bound rotors and then Lerps between them _fRatio distance.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the line connecting _rStart and _rEnd"></param>
	/// <returns>
	/// RotorF: Lerped rotor
	/// </returns>
	[[nodiscard]] RotorF NLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);

	/// <summary>
	/// Lerps along the sphere connecting _rStart and _rEnd via the ratio given by _fRatio.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_fRatio: Ratio along the sphere connecting _rStart and _rEnd"></param>
	/// <returns>
	/// RotorF: Interpolated rotor
	/// </returns>
	[[nodiscard]] RotorF SLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);

	/// <summary>
	/// Constrains a value to _rLowerBound and _rUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_rVal: The value to constrain"></param>
	/// <param name="_rLowerBound: The lowest value in the range given"></param>
	/// <param name="_rUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// RotorF: Constrained rotor
	/// </returns>
	[[nodiscard]] RotorF Wrap(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound);

	[[nodiscard]] RotorF Ceiling(RotorF _fVal);

	[[nodiscard]] RotorF Floor(RotorF _fVal);

	/// <summary>
	/// Raises each component of _rBase to the power _fExp.
	/// </summary>
	/// <param name="_rBase: The rotor containing each value to raise to the power _fExp"></param>
	/// <param name="_fExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// RotorF: Result of the exponential
	/// </returns>
	[[nodiscard]] RotorF Pow(const RotorF& _rBase, float _fExp);

	/// <summary>
	/// Computes the square root of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to square root"></param>
	/// <returns>
	/// RotorF: Result of the square root
	/// </returns>
	[[nodiscard]] RotorF Sqrt(const RotorF& _rVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute Log base 10"></param>
	/// <returns>
	/// RotorF: Result of the Log base 10
	/// </returns>
	[[nodiscard]] RotorF Log10(const RotorF& _rVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute Log base 2"></param>
	/// <returns>
	/// RotorF: Result of the Log base 2
	/// </returns>
	[[nodiscard]] RotorF Log2(const RotorF& _rVal);

	/// <summary>
	/// Computes the Natural Log of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the Natural Log"></param>
	/// <returns>
	/// RotorF: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] RotorF Ln(const RotorF& _rVal);

	/// <summary>
	/// Computes e raised to the power of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to raise e to the power"></param>
	/// <returns>
	/// RotorF: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] RotorF Exp(const RotorF& _rVal);

	/// <summary>
	/// Computes the sine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the sine"></param>
	/// <returns>
	/// RotorF: Result of the sine
	/// </returns>
	[[nodiscard]] RotorF Sin(const RotorF& _rVal);

	/// <summary>
	/// Computes the cosine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the cosine"></param>
	/// <returns>
	/// RotorF: Result of the cosine
	/// </returns>
	[[nodiscard]] RotorF Cos(const RotorF& _rVal);

	/// <summary>
	/// Computes the tangent of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the tangent"></param>
	/// <returns>
	/// RotorF: Result of the tangent
	/// </returns>
	[[nodiscard]] RotorF Tan(const RotorF& _rVal);

	/// <summary>
	/// Computes the arc sine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc sine"></param>
	/// <returns>
	/// RotorF: Result of the arc sine
	/// </returns>
	[[nodiscard]] RotorF ArcSin(const RotorF& _rVal);

	/// <summary>
	/// Computes the arc cosine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc cosine"></param>
	/// <returns>
	/// RotorF: Result of the arc cosine
	/// </returns>
	[[nodiscard]] RotorF ArcCos(const RotorF& _rVal);

	/// <summary>
	/// Computes the arc tangent of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc tangent"></param>
	/// <returns>
	/// RotorF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] RotorF ArcTan(const RotorF& _rVal);

	/// <summary>
	/// Computes the arc tangent of [_rRight / _rLeft] for each component of the respective rotors.
	/// </summary>
	/// <param name="_rLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_rRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// RotorF: Result of the arc tangent
	/// </returns>
	[[nodiscard]] RotorF ArcTan2(const RotorF& _rLeft, const RotorF& _rRight);

	/// <summary>
	/// Oscillates between _rMin and _rMax according to the period _fPeriod. Location on the oscillation is based on _fTime.
	/// Utilizes a cosine wave as the base form, thus starting at _rMax.
	/// </summary>
	/// <param name="_rMin: Minimum rotor to oscillate to"></param>
	/// <param name="_rMax: Maximum rotor to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <returns>
	/// RotorF: Rotor along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] RotorF Oscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime);

	/// <summary>
	/// Oscillates between _rMin and _rMax according to the period _fPeriod. Location on the oscillation is based on _fTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _fDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _rMax.
	/// </summary>
	/// <param name="_rMin: Minimum rotor to oscillate to"></param>
	/// <param name="_rMax: Maximum rotor to oscillate to"></param>
	/// <param name="_fPeriod: The time it takes to oscillate"></param>
	/// <param name="_fTime: The current position along the cosine wave"></param>
	/// <param name="_fDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// RotorF: Rotor along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] RotorF DampedOscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime, float _fDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _rStart and _rEnd, utilizing the ratio _fRatio.
	/// </summary>
	/// <param name="_rStart: The initial rotor to interpolate from"></param>
	/// <param name="_rEnd: The goal rotor to interpolate to"></param>
	/// <param name="_fRatio: The distance along the curve"></param>
	/// <returns>
	/// RotorF: Interpolated rotor along the curve from _rStart to _rEnd
	/// </returns>
	[[nodiscard]] RotorF SmoothStep(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);

	/// <summary>
	/// Gradually moves _rCurrent to _rGoal utilizing a damped interpolation. Velocity is given by _rVelocity, and determines
	/// the rate of change and direction. _fTimeDelta determines how far along to move _qCurrent this step. _fSmoothTime (default: 0.0001f) determines how
	/// long the traversal to _rGoal should take. _fMaxChange (default: FLT_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_rCurrent: Current position along the curve to _rGoal"></param>
	/// <param name="_rGoal: The point to reach from _rCurrent"></param>
	/// <param name="_rVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_fTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_fSmoothTime: The time to traverse to _rGoal"></param>
	/// <param name="_fMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// RotorF: Interpolated rotor after calculation
	/// </returns>
	[[nodiscard]] RotorF DampedSmoothStep(const RotorF& _rCurrent, const RotorF& _rGoal, RotorF& _rVelocity, float _fTimeDelta, float _fSmoothTime, float _fMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _rVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_rVal: The rotor to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// RotorF: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] RotorF InverseSmoothStep(const RotorF& _rVal);

#if HC_ENABLE_DOUBLE_PRECISION
	/// <summary>
	/// Clamps the RotorF _rVal to the range [_rMin, _rMax].
	/// </summary>
	/// <param name="_rVal: The rotor to clamp"></param>
	/// <param name="_rMin: The rotor corresponding to the minimum value"></param>
	/// <param name="_rMax: The rotor corresponding to the maximum value"></param>
	/// <returns>
	/// RotorD: Clamped rotor
	/// </returns>
	[[nodiscard]] RotorD Clamp(const RotorD& _rVal, const RotorD& _rMin, const RotorD& _rMax);

	/// <summary>
	/// Clamps the length of _rVal to the range [_dMin, _dMax]
	/// </summary>
	/// <param name="_rVal: The rotor to clamp"></param>
	/// <param name="_dMin: Minimum clamp value"></param>
	/// <param name="_dMax: Maximum clamp value"></param>
	/// <returns>
	/// RotorD: Clamped rotor
	/// </returns>
	[[nodiscard]] RotorD ClampMagnitude(const RotorD& _rVal, double _dMin, double _dMax);

	/// <summary>
	/// Generates a tweened rotor between _rStart and _rEnd of _dRatio distance along the route.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _rStart and _rEnd"></param>
	/// <returns>
	///	RotorD: Lerped rotor 
	/// </returns>
	[[nodiscard]] RotorD Lerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);

	/// <summary>
	/// Normalizes the two bound rotors and then Lerps between them _dRatio distance.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the line connecting _rStart and _rEnd"></param>
	/// <returns>
	/// RotorD: Lerped rotor
	/// </returns>
	[[nodiscard]] RotorD NLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);

	/// <summary>
	/// Lerps along the sphere connecting _rStart and _rEnd via the ratio given by _dRatio.
	/// </summary>
	/// <param name="_rStart: Starting point of the interpolation"></param>
	/// <param name="_rEnd: Ending point of the interpolation"></param>
	/// <param name="_dRatio: Ratio along the sphere connecting _rStart and _rEnd"></param>
	/// <returns>
	/// RotorD: Interpolated rotor
	/// </returns>
	[[nodiscard]] RotorD SLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);

	/// <summary>
	/// Constrains a value to _rLowerBound and _rUpperbound, wrapping the value around to either end if exceeding the bounds.
	/// </summary>
	/// <param name="_rVal: The value to constrain"></param>
	/// <param name="_rLowerBound: The lowest value in the range given"></param>
	/// <param name="_rUpperBound: The highest value in the range given"></param>
	/// <returns>
	/// RotorD: Constrained rotor
	/// </returns>
	[[nodiscard]] RotorD Wrap(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound);

	/// <summary>
	/// Raises each component of _rBase to the power _dExp.
	/// </summary>
	/// <param name="_rBase: The rotor containing each value to raise to the power _dExp"></param>
	/// <param name="_dExp: The power to raise the base _vBase to"></param>
	/// <returns>
	/// RotorD: Result of the exponential
	/// </returns>
	[[nodiscard]] RotorD Pow(const RotorD& _rBase, double _dExp);

	/// <summary>
	/// Computes the square root of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to square root"></param>
	/// <returns>
	/// RotorD: Result of the square root
	/// </returns>
	[[nodiscard]] RotorD Sqrt(const RotorD& _rVal);

	/// <summary>
	/// Computes the Log base 10 of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute Log base 10"></param>
	/// <returns>
	/// RotorD: Result of the Log base 10
	/// </returns>
	[[nodiscard]] RotorD Log10(const RotorD& _rVal);

	/// <summary>
	/// Computes the Log base 2 of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute Log base 2"></param>
	/// <returns>
	/// RotorD: Result of the Log base 2
	/// </returns>
	[[nodiscard]] RotorD Log2(const RotorD& _rVal);

	/// <summary>
	/// Computes the Natural Log of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the Natural Log"></param>
	/// <returns>
	/// RotorD: Result of the Natural Log.
	/// </returns>
	[[nodiscard]] RotorD Ln(const RotorD& _rVal);

	/// <summary>
	/// Computes e raised to the power of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to raise e to the power"></param>
	/// <returns>
	/// RotorD: Result of the e exponential operation.
	/// </returns>
	[[nodiscard]] RotorD Exp(const RotorD& _rVal);

	/// <summary>
	/// Computes the sine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the sine"></param>
	/// <returns>
	/// RotorD: Result of the sine
	/// </returns>
	[[nodiscard]] RotorD Sin(const RotorD& _rVal);

	/// <summary>
	/// Computes the cosine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the cosine"></param>
	/// <returns>
	/// RotorD: Result of the cosine
	/// </returns>
	[[nodiscard]] RotorD Cos(const RotorD& _rVal);

	/// <summary>
	/// Computes the tangent of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the tangent"></param>
	/// <returns>
	/// RotorD: Result of the tangent
	/// </returns>
	[[nodiscard]] RotorD Tan(const RotorD& _rVal);

	/// <summary>
	/// Computes the arc sine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc sine"></param>
	/// <returns>
	/// RotorD: Result of the arc sine
	/// </returns>
	[[nodiscard]] RotorD ArcSin(const RotorD& _rVal);

	/// <summary>
	/// Computes the arc cosine of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc cosine"></param>
	/// <returns>
	/// RotorD: Result of the arc cosine
	/// </returns>
	[[nodiscard]] RotorD ArcCos(const RotorD& _rVal);

	/// <summary>
	/// Computes the arc tangent of each component of _rVal.
	/// </summary>
	/// <param name="_rVal: The rotor containing each value to compute the arc tangent"></param>
	/// <returns>
	/// RotorD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] RotorD ArcTan(const RotorD& _rVal);

	/// <summary>
	/// Computes the arc tangent of [_rRight / _rLeft] for each component of the respective rotors.
	/// </summary>
	/// <param name="_rLeft: The denominator of the atan2 calculation"></param>
	/// <param name="_rRight: The numerator of the atan2 calculation"></param>
	/// <returns>
	/// RotorD: Result of the arc tangent
	/// </returns>
	[[nodiscard]] RotorD ArcTan2(const RotorD& _rLeft, const RotorD& _rRight);

	/// <summary>
	/// Oscillates between _rMin and _rMax according to the period _dPeriod. Location on the oscillation is based on _dTime.
	/// Utilizes a cosine wave as the base form, thus starting at _rMax.
	/// </summary>
	/// <param name="_rMin: Minimum rotor to oscillate to"></param>
	/// <param name="_rMax: Maximum rotor to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <returns>
	/// RotorD: Rotor along the cosine wave computed from these values
	/// </returns>
	[[nodiscard]] RotorD Oscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime);

	/// <summary>
	/// Oscillates between _rMin and _rMax according to the period _dPeriod. Location on the oscillation is based on _dTime. Oscillation
	/// damps out exponentially by a factor of e, utilizing _dDampingFactor (default: 0.2) to scale the timing. Utilizes a cosine wave 
	/// as the base form, thus starting at _rMax.
	/// </summary>
	/// <param name="_rMin: Minimum rotor to oscillate to"></param>
	/// <param name="_rMax: Maximum rotor to oscillate to"></param>
	/// <param name="_dPeriod: The time it takes to oscillate"></param>
	/// <param name="_dTime: The current position along the cosine wave"></param>
	/// <param name="_dDampingFactor: The time it takes to decrease the amplitude. By default, the factor is 0.2, so the amplitude decreases by e every 1/5th of a unit"></param>
	/// <returns>
	/// RotorD: Rotor along the damped cosine wave computed from these values
	/// </returns>
	[[nodiscard]] RotorD DampedOscillate(const RotorD& _rMax, const RotorD& _rMin, double _dPeriod, double _dTime, double _dDampingFactor);

	/// <summary>
	/// Performs a smoothed linear interpolation between _rStart and _rEnd, utilizing the ratio _dRatio.
	/// </summary>
	/// <param name="_rStart: The initial rotor to interpolate from"></param>
	/// <param name="_rEnd: The goal rotor to interpolate to"></param>
	/// <param name="_dRatio: The distance along the curve"></param>
	/// <returns>
	/// RotorD: Interpolated rotor along the curve from _rStart to _rEnd
	/// </returns>
	[[nodiscard]] RotorD SmoothStep(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);

	/// <summary>
	/// Gradually moves _rCurrent to _rGoal utilizing a damped interpolation. Velocity is given by _rVelocity, and determines
	/// the rate of change and direction. _dTimeDelta determines how far along to move _qCurrent this step. _dSmoothTime (default: 0.0001) determines how
	/// long the traversal to _rGoal should take. _dMaxChange (default: DBL_MAX) clamps the delta of this step.
	/// </summary>
	/// <param name="_rCurrent: Current position along the curve to _rGoal"></param>
	/// <param name="_rGoal: The point to reach from _rCurrent"></param>
	/// <param name="_rVelocity: The rate of change and direction at the present moment (will be altered by this function)"></param>
	/// <param name="_dTimeDelta: The time 'since' the last step (call) of this function"></param>
	/// <param name="_dSmoothTime: The time to traverse to _rGoal"></param>
	/// <param name="_dMaxChange: The speed cap for the current value"></param>
	/// <returns>
	/// RotorD: Interpolated rotor after calculation
	/// </returns>
	[[nodiscard]] RotorD DampedSmoothStep(const RotorD& _rCurrent, const RotorD& _rGoal, RotorD& _rVelocity, double _dTimeDelta, double _dSmoothTime, double _dMaxChange);

	/// <summary>
	/// Performs the inverse of SmoothStep on _rVal. Assumes the values of the components are constrained to [0.0, 1.0].
	/// </summary>
	/// <param name="_rVal: The rotor to compute the inverse SmoothStep from"></param>
	/// <returns>
	/// RotorD: The result of the calculation of SmoothStep's inverse
	/// </returns>
	[[nodiscard]] RotorD InverseSmoothStep(const RotorD& _rVal);
#endif
#endif
}