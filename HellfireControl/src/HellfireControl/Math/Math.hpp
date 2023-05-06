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
#endif

#if HC_USE_ROTOR
	[[nodiscard]] HC_INLINE RotorF LERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF NLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);
	[[nodiscard]] HC_INLINE RotorF SLERP(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio);

#if HC_ENABLE_DOUBLE_PRECISION
	[[nodiscard]] HC_INLINE RotorD LERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD NLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
	[[nodiscard]] HC_INLINE RotorD SLERP(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio);
#endif
#endif
}