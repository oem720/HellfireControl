#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Math/Vector.hpp>
#include <HellfireControl/Math/Matrix.hpp>

#include <HellfireControl/Math/Quaternion.hpp>

#if HC_USE_ROTOR
#include <HellfireControl/Math/Rotor.hpp>
#endif

namespace Math {
	[[nodiscard]] HC_INLINE float LERP(float _fStart, float _fEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec2F LERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F LERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F LERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF LERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF LERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE Vec2F NLERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F NLERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F NLERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF NLERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF NLERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE Vec2F SLERP(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec3F SLERP(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE Vec4F SLERP(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio);
	[[nodiscard]] HC_INLINE MatrixF SLERP(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio);
	[[nodiscard]] HC_INLINE QuaternionF SLERP(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio);

	[[nodiscard]] HC_INLINE float WrapAround(float _fVal, float _fLowerBound, float _fUpperBound);
	[[nodiscard]] HC_INLINE Vec2F WrapAround(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec3F WrapAround(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec4F WrapAround(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound);
	[[nodiscard]] HC_INLINE MatrixF WrapAround(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound);
	[[nodiscard]] HC_INLINE QuaternionF WrapAround(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound);

#if HC_ENABLE_DOUBLE_PRECISION
	[[nodiscard]] HC_INLINE double LERP(double _dStart, double _dEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec2D LERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D LERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D LERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD LERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD LERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE Vec2D NLERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D NLERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D NLERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD NLERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD NLERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE Vec2D SLERP(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec3D SLERP(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE Vec4D SLERP(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio);
	[[nodiscard]] HC_INLINE MatrixD SLERP(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio);
	[[nodiscard]] HC_INLINE QuaternionD SLERP(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio);

	[[nodiscard]] HC_INLINE double WrapAround(double _dVal, double _dLowerBound, double _dUpperBound);
	[[nodiscard]] HC_INLINE Vec2D WrapAround(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec3D WrapAround(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound);
	[[nodiscard]] HC_INLINE Vec4D WrapAround(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound);
	[[nodiscard]] HC_INLINE MatrixD WrapAround(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound);
	[[nodiscard]] HC_INLINE QuaternionD WrapAround(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound);
#endif

#if HC_USE_ROTOR
	[[nodiscard]] HC_INLINE RotorF LERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF NLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF SLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF WrapAround(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound);

#if HC_ENABLE_DOUBLE_PRECISION
	[[nodiscard]] HC_INLINE RotorD LERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD NLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD SLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD WrapAround(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound);
#endif
#endif
}