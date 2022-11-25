
#include "HCMatrix.h"

struct QuaternionF {
	Vec4F m_vQuat;

	HC_INLINE QuaternionF() {}
	HC_INLINE QuaternionF(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4F(_fX, _fY, _fZ, _fW); }
	HC_INLINE QuaternionF(int _fX, int _fY, int _fZ, int _fW) { m_vQuat = Vec4F(static_cast<float>(_fX), static_cast<float>(_fY), static_cast<float>(_fZ), static_cast<float>(_fW)); }
	HC_INLINE QuaternionF(double _fX, double _fY, double _fZ, double _fW) { m_vQuat = Vec4F(static_cast<float>(_fX), static_cast<float>(_fY), static_cast<float>(_fZ), static_cast<float>(_fW)); }
	HC_INLINE QuaternionF(MatrixF _mMat) {
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
	HC_INLINE float operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	HC_INLINE float& operator[](int _iNdx) { return m_vQuat[_iNdx] ; }
	HC_INLINE float X() const { return m_vQuat.X(); }
	HC_INLINE float Y() const { return m_vQuat.Y(); }
	HC_INLINE float Z() const { return m_vQuat.Z(); }
	HC_INLINE float W() const { return m_vQuat.W(); }
	HC_INLINE void SetX(float _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void SetY(float _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void SetZ(float _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void SetW(float _fW) { m_vQuat.SetW(_fW); }
};

struct QuaternionD {
	Vec4D m_vQuat;

	HC_INLINE QuaternionD() {}
	HC_INLINE QuaternionD(double _fX, double _fY, double _fZ, double _fW) { m_vQuat = Vec4D(_fX, _fY, _fZ, _fW); }
	HC_INLINE QuaternionD(int _fX, int _fY, int _fZ, int _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE QuaternionD(float _fX, float _fY, float _fZ, float _fW) { m_vQuat = Vec4D(static_cast<double>(_fX), static_cast<double>(_fY), static_cast<double>(_fZ), static_cast<double>(_fW)); }
	HC_INLINE QuaternionD(MatrixD _mMat) {
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
	HC_INLINE double operator[](int _iNdx) const { return m_vQuat[_iNdx]; }
	HC_INLINE double& operator[](int _iNdx) { return m_vQuat[_iNdx]; }
	HC_INLINE double X() const { return m_vQuat.X(); }
	HC_INLINE double Y() const { return m_vQuat.Y(); }
	HC_INLINE double Z() const { return m_vQuat.Z(); }
	HC_INLINE double W() const { return m_vQuat.W(); }
	HC_INLINE void SetX(double _fX) { m_vQuat.SetX(_fX); }
	HC_INLINE void SetY(double _fY) { m_vQuat.SetY(_fY); }
	HC_INLINE void SetZ(double _fZ) { m_vQuat.SetZ(_fZ); }
	HC_INLINE void SetW(double _fW) { m_vQuat.SetW(_fW); }
};

