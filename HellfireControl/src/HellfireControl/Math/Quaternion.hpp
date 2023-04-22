#pragma once

#include <intrin.h>
#include <math.h>

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>
#include <HellfireControl/Math/Matrix.hpp>

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
	HC_INLINE float& HC_VECTORCALL operator[](int _iNdx) { return m_vQuat[_iNdx] ; }
	HC_INLINE float HC_VECTORCALL X() const { return m_vQuat.X(); }
	HC_INLINE float HC_VECTORCALL Y() const { return m_vQuat.Y(); }
	HC_INLINE float HC_VECTORCALL Z() const { return m_vQuat.Z(); }
	HC_INLINE float HC_VECTORCALL W() const { return m_vQuat.W(); }
	HC_INLINE void HC_VECTORCALL SetX(float _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void HC_VECTORCALL SetY(float _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void HC_VECTORCALL SetZ(float _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void HC_VECTORCALL SetW(float _fW) { m_vQuat.SetW(_fW); }
};

#if HC_ENABLE_EXTRA_VECTOR_TYPES && HC_USE_SIMD

struct QuaternionD {
	Vec4D m_vQuat;

	HC_INLINE HC_VECTORCALL QuaternionD() {}
	HC_INLINE HC_VECTORCALL QuaternionD(double _fX, double _fY, double _fZ, double _fW) { m_vQuat = Vec4D(_fX, _fY, _fZ, _fW); }
	HC_INLINE HC_VECTORCALL QuaternionD(int _fX, int _fY, int _fZ, int _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionD(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE HC_VECTORCALL QuaternionD(MatrixD _mMat) {
		//FIXME: All of this is god-awful unoptimized crap. Make into optimized SIMD code ASAP! - Owen
		double dSum = 0.0;
		if (_mMat[2][2] < 0.0) {
			if (_mMat[0][0] > _mMat[1][1]) {
				dSum = 1.0 + _mMat[0][0] - _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4D(dSum, _mMat[0][1] + _mMat[1][0], _mMat[2][0] + _mMat[0][2], _mMat[1][2] - _mMat[2][2]);
			}
			else {
				dSum = 1.0 - _mMat[0][0] + _mMat[1][1] - _mMat[2][2];
				m_vQuat = Vec4D(_mMat[0][1] + _mMat[1][0], dSum, _mMat[1][2] + _mMat[2][1], _mMat[2][0] - _mMat[0][2]);
			}
		}
		else {
			if (_mMat[0][0] < _mMat[1][1]) {
				dSum = 1.0 - _mMat[0][0] - _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4D(_mMat[2][0] + _mMat[0][2], _mMat[1][2] + _mMat[2][1], dSum, _mMat[0][1] - _mMat[1][0]);
			}
			else {
				dSum = 1.0f + _mMat[0][0] + _mMat[1][1] + _mMat[2][2];
				m_vQuat = Vec4D(_mMat[1][2] - _mMat[2][1], _mMat[2][0] - _mMat[0][2], _mMat[0][1] - _mMat[1][0], dSum);
			}
		}

		m_vQuat *= 0.5 / sqrt(dSum);
	}
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { return m_vQuat[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return m_vQuat.X(); }
	HC_INLINE double HC_VECTORCALL Y() const { return m_vQuat.Y(); }
	HC_INLINE double HC_VECTORCALL Z() const { return m_vQuat.Z(); }
	HC_INLINE double HC_VECTORCALL W() const { return m_vQuat.W(); }
	HC_INLINE void HC_VECTORCALL SetX(double _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void HC_VECTORCALL SetY(double _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void HC_VECTORCALL SetZ(double _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void HC_VECTORCALL SetW(double _fW) { m_vQuat.SetW(_fW); }
};

#endif

#else
	
struct QuaternionF
{

};

#if HC_ENABLE_DOUBLE_PRECISION

struct QuaternionD
{

};

#endif

#endif