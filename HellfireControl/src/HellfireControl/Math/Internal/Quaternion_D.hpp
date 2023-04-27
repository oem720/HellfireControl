#pragma once

#include <HellfireControl/Math/Internal/Quaternion_Common.hpp>

#if HC_USE_SIMD

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

#else

struct QuaternionD
{

};

#endif