#pragma once

#include <HellfireControl/Math/Internal/Vector_Common.hpp>

#if HC_USE_SIMD
#define HC_SHUFFLE4D(_vec, _x, _y, _z, _w) Vec4D(_mm256_shuffle_pd((_vec).m_dVec, (_vec).m_dVec, _MM_SHUFFLE(_w, _z, _y, _x)))
#define HC_SHUFFLE4D_2(_vec1, _vec2, _x, _y, _z, _w) Vec4D(_mm256_shuffle_pd((_vec1).m_dVec, (_vec2).m_dVec, _MM_SHUFFLE(_w, _z, _y, _x)))

struct Vec4D {
	__m256d m_dVec;

	HC_INLINE HC_VECTORCALL Vec4D() { m_dVec = _mm256_setzero_pd(); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(const double* _pValues) { m_dVec = _mm256_set_pd(_pValues[3], _pValues[2], _pValues[1], _pValues[0]); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(double _dX, double _dY, double _dZ, double _dA) { m_dVec = _mm256_set_pd(_dA, _dZ, _dY, _dX); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(float _fX, float _fY, float _fZ, float _fA) { m_dVec = _mm256_set_pd(static_cast<double>(_fA), static_cast<double>(_fZ), static_cast<double>(_fY), static_cast<double>(_fX)); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(int _iX, int _iY, int _iZ, int _iA) { m_dVec = _mm256_set_pd(static_cast<double>(_iA), static_cast<double>(_iZ), static_cast<double>(_iY), static_cast<double>(_iX)); }
	HC_INLINE explicit HC_VECTORCALL Vec4D(__m256d _vData) { m_dVec = _vData; }
	HC_INLINE double HC_VECTORCALL operator[](int _iNdx) const { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double& HC_VECTORCALL operator[](int _iNdx) { assert(_iNdx < 4); return m_dVec.m256d_f64[_iNdx]; }
	HC_INLINE double HC_VECTORCALL X() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL Y() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL Z() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double HC_VECTORCALL W() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE double HC_VECTORCALL R() const { return _mm256_cvtsd_f64(m_dVec); }
	HC_INLINE double HC_VECTORCALL G() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(1, 1, 1, 1))); }
	HC_INLINE double HC_VECTORCALL B() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(2, 2, 2, 2))); }
	HC_INLINE double HC_VECTORCALL A() const { return _mm256_cvtsd_f64(_mm256_shuffle_pd(m_dVec, m_dVec, _MM_SHUFFLE(3, 3, 3, 3))); }
	HC_INLINE void HC_VECTORCALL SetX(double _dX) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dX); }
	HC_INLINE void HC_VECTORCALL SetY(double _dY) { m_dVec = _mm256_set_pd(W(), Z(), _dY, X()); }
	HC_INLINE void HC_VECTORCALL SetZ(double _dZ) { m_dVec = _mm256_set_pd(W(), _dZ, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetW(double _dW) { m_dVec = _mm256_set_pd(_dW, Z(), Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetR(double _dR) { m_dVec = _mm256_set_pd(W(), Z(), Y(), _dR); }
	HC_INLINE void HC_VECTORCALL SetG(double _dG) { m_dVec = _mm256_set_pd(W(), Z(), _dG, X()); }
	HC_INLINE void HC_VECTORCALL SetB(double _dB) { m_dVec = _mm256_set_pd(W(), _dB, Y(), X()); }
	HC_INLINE void HC_VECTORCALL SetA(double _dA) { m_dVec = _mm256_set_pd(_dA, Z(), Y(), X()); }
	HC_INLINE Vec2D HC_VECTORCALL XX() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YY() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL ZZ() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL WW() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D HC_VECTORCALL XY() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL XZ() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL XW() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D HC_VECTORCALL YX() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL YZ() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL YW() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D HC_VECTORCALL ZX() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL ZY() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D HC_VECTORCALL ZW() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D HC_VECTORCALL WX() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D HC_VECTORCALL WY() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D HC_VECTORCALL WZ() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec2D HC_VECTORCALL RR() const { return HC_SHUFFLE2D(*this, 0, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GG() const { return HC_SHUFFLE2D(*this, 1, 1); }
	HC_INLINE Vec2D HC_VECTORCALL BB() const { return HC_SHUFFLE2D(*this, 2, 2); }
	HC_INLINE Vec2D HC_VECTORCALL AA() const { return HC_SHUFFLE2D(*this, 3, 3); }
	HC_INLINE Vec2D HC_VECTORCALL RG() const { return HC_SHUFFLE2D(*this, 0, 1); }
	HC_INLINE Vec2D HC_VECTORCALL RB() const { return HC_SHUFFLE2D(*this, 0, 2); }
	HC_INLINE Vec2D HC_VECTORCALL RA() const { return HC_SHUFFLE2D(*this, 0, 3); }
	HC_INLINE Vec2D HC_VECTORCALL GR() const { return HC_SHUFFLE2D(*this, 1, 0); }
	HC_INLINE Vec2D HC_VECTORCALL GB() const { return HC_SHUFFLE2D(*this, 1, 2); }
	HC_INLINE Vec2D HC_VECTORCALL GA() const { return HC_SHUFFLE2D(*this, 1, 3); }
	HC_INLINE Vec2D HC_VECTORCALL BR() const { return HC_SHUFFLE2D(*this, 2, 0); }
	HC_INLINE Vec2D HC_VECTORCALL BG() const { return HC_SHUFFLE2D(*this, 2, 1); }
	HC_INLINE Vec2D HC_VECTORCALL BA() const { return HC_SHUFFLE2D(*this, 2, 3); }
	HC_INLINE Vec2D HC_VECTORCALL AR() const { return HC_SHUFFLE2D(*this, 3, 0); }
	HC_INLINE Vec2D HC_VECTORCALL AG() const { return HC_SHUFFLE2D(*this, 3, 1); }
	HC_INLINE Vec2D HC_VECTORCALL AB() const { return HC_SHUFFLE2D(*this, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XXX() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XXY() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XXZ() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XXW() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XYX() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XYY() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XYZ() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XYW() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XZX() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XZY() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XZZ() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XZW() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL XWX() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL XWY() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL XWZ() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL XWW() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YXX() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YXY() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YXZ() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YXW() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YYX() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YYY() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YYZ() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YYW() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YZX() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YZY() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YZZ() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YZW() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL YWX() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL YWY() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL YWZ() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL YWW() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZXX() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZXY() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZXZ() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZXW() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZYX() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZYY() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZYZ() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZYW() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZZX() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZZY() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZZZ() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZZW() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ZWX() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ZWY() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ZWZ() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ZWW() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WXX() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WXY() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WXZ() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WXW() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WYX() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WYY() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WYZ() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WYW() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WZX() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WZY() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WZZ() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WZW() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL WWX() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL WWY() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL WWZ() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL WWW() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RRR() const { return HC_SHUFFLE3D(*this, 0, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RRG() const { return HC_SHUFFLE3D(*this, 0, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RRB() const { return HC_SHUFFLE3D(*this, 0, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RRA() const { return HC_SHUFFLE3D(*this, 0, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RGR() const { return HC_SHUFFLE3D(*this, 0, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RGG() const { return HC_SHUFFLE3D(*this, 0, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RGA() const { return HC_SHUFFLE3D(*this, 0, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RGB() const { return HC_SHUFFLE3D(*this, 0, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RBR() const { return HC_SHUFFLE3D(*this, 0, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RBG() const { return HC_SHUFFLE3D(*this, 0, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RBB() const { return HC_SHUFFLE3D(*this, 0, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RBA() const { return HC_SHUFFLE3D(*this, 0, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL RAR() const { return HC_SHUFFLE3D(*this, 0, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL RAG() const { return HC_SHUFFLE3D(*this, 0, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL RAB() const { return HC_SHUFFLE3D(*this, 0, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL RAA() const { return HC_SHUFFLE3D(*this, 0, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GRR() const { return HC_SHUFFLE3D(*this, 1, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GRG() const { return HC_SHUFFLE3D(*this, 1, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GRB() const { return HC_SHUFFLE3D(*this, 1, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GRA() const { return HC_SHUFFLE3D(*this, 1, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GGR() const { return HC_SHUFFLE3D(*this, 1, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GGG() const { return HC_SHUFFLE3D(*this, 1, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GGB() const { return HC_SHUFFLE3D(*this, 1, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GGA() const { return HC_SHUFFLE3D(*this, 1, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GBR() const { return HC_SHUFFLE3D(*this, 1, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GBG() const { return HC_SHUFFLE3D(*this, 1, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GBB() const { return HC_SHUFFLE3D(*this, 1, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GBA() const { return HC_SHUFFLE3D(*this, 1, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL GAR() const { return HC_SHUFFLE3D(*this, 1, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL GAG() const { return HC_SHUFFLE3D(*this, 1, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL GAB() const { return HC_SHUFFLE3D(*this, 1, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL GAA() const { return HC_SHUFFLE3D(*this, 1, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BRR() const { return HC_SHUFFLE3D(*this, 2, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BRG() const { return HC_SHUFFLE3D(*this, 2, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BRB() const { return HC_SHUFFLE3D(*this, 2, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BRA() const { return HC_SHUFFLE3D(*this, 2, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BGR() const { return HC_SHUFFLE3D(*this, 2, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BGG() const { return HC_SHUFFLE3D(*this, 2, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BGB() const { return HC_SHUFFLE3D(*this, 2, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BGA() const { return HC_SHUFFLE3D(*this, 2, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BBR() const { return HC_SHUFFLE3D(*this, 2, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BBG() const { return HC_SHUFFLE3D(*this, 2, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BBB() const { return HC_SHUFFLE3D(*this, 2, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BBA() const { return HC_SHUFFLE3D(*this, 2, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL BAR() const { return HC_SHUFFLE3D(*this, 2, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL BAG() const { return HC_SHUFFLE3D(*this, 2, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL BAB() const { return HC_SHUFFLE3D(*this, 2, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL BAA() const { return HC_SHUFFLE3D(*this, 2, 3, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ARR() const { return HC_SHUFFLE3D(*this, 3, 0, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ARG() const { return HC_SHUFFLE3D(*this, 3, 0, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ARB() const { return HC_SHUFFLE3D(*this, 3, 0, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ARA() const { return HC_SHUFFLE3D(*this, 3, 0, 3); }
	HC_INLINE Vec3D HC_VECTORCALL AGR() const { return HC_SHUFFLE3D(*this, 3, 1, 0); }
	HC_INLINE Vec3D HC_VECTORCALL AGG() const { return HC_SHUFFLE3D(*this, 3, 1, 1); }
	HC_INLINE Vec3D HC_VECTORCALL AGB() const { return HC_SHUFFLE3D(*this, 3, 1, 2); }
	HC_INLINE Vec3D HC_VECTORCALL AGA() const { return HC_SHUFFLE3D(*this, 3, 1, 3); }
	HC_INLINE Vec3D HC_VECTORCALL ABR() const { return HC_SHUFFLE3D(*this, 3, 2, 0); }
	HC_INLINE Vec3D HC_VECTORCALL ABG() const { return HC_SHUFFLE3D(*this, 3, 2, 1); }
	HC_INLINE Vec3D HC_VECTORCALL ABB() const { return HC_SHUFFLE3D(*this, 3, 2, 2); }
	HC_INLINE Vec3D HC_VECTORCALL ABA() const { return HC_SHUFFLE3D(*this, 3, 2, 3); }
	HC_INLINE Vec3D HC_VECTORCALL AAR() const { return HC_SHUFFLE3D(*this, 3, 3, 0); }
	HC_INLINE Vec3D HC_VECTORCALL AAG() const { return HC_SHUFFLE3D(*this, 3, 3, 1); }
	HC_INLINE Vec3D HC_VECTORCALL AAB() const { return HC_SHUFFLE3D(*this, 3, 3, 2); }
	HC_INLINE Vec3D HC_VECTORCALL AAA() const { return HC_SHUFFLE3D(*this, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXXX() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXXY() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXXZ() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXXW() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXYX() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXYY() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXYZ() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXYW() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXZX() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXZY() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXZZ() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXZW() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XXWX() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XXWY() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XXWZ() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XXWW() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYXX() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYXY() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYXZ() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYXW() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYYX() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYYY() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYYZ() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYYW() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XYZX() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYZY() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYZZ() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYWX() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XYWY() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XYWZ() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XYWW() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZXX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZXY() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZXZ() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZXW() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZYX() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZYY() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZYZ() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZYW() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZZX() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZZY() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZZZ() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZZW() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XZWX() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XZWY() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XZWZ() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XZWW() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWXX() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWXY() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWXZ() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWXW() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWYX() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWYY() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWYZ() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWYW() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWZX() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWZY() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWZZ() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWZW() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL XWWX() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL XWWY() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL XWWZ() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL XWWW() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXXX() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXXY() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXXZ() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXXW() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXYX() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXYY() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXYZ() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXYW() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXZX() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXZY() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXZZ() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXZW() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YXWX() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YXWY() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YXWZ() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YXWW() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYXX() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYXY() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYXZ() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYXW() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYYX() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYYY() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYYZ() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYYW() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYZX() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYZY() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYZZ() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYZW() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YYWX() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YYWY() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YYWZ() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YYWW() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZXX() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZXY() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZXZ() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZXW() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZYX() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZYY() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZYZ() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZYW() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZZX() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZZY() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZZZ() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZZW() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YZWX() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YZWY() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YZWZ() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YZWW() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWXX() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWXY() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWXZ() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWXW() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWYX() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWYY() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWYZ() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWYW() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWZX() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWZY() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWZZ() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWZW() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL YWWX() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL YWWY() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL YWWZ() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL YWWW() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXX() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXY() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXZ() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXXW() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYX() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYY() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYZ() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXYW() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZX() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZY() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZZ() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXZW() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWX() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWY() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWZ() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZXWW() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXX() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXY() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXZ() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYXW() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYX() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYY() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYZ() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYYW() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZX() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZY() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZZ() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYZW() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWX() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWY() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWZ() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZYWW() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXX() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXY() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXZ() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZXW() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYX() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYY() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYZ() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZYW() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZX() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZY() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZZ() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZZW() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWX() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWY() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWZ() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZZWW() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXX() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXY() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXZ() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWXW() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYX() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYY() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYZ() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWYW() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZX() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZY() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZZ() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWZW() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWX() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWY() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWZ() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ZWWW() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXXX() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXXY() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXXZ() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXXW() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXYX() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXYY() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXYZ() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXYW() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXZX() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXZY() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXZZ() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXZW() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WXWX() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WXWY() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WXWZ() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WXWW() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYXX() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYXY() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYXZ() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYXW() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYYX() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYYY() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYYZ() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYYW() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYZX() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYZY() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYZZ() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYZW() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WYWX() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WYWY() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WYWZ() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WYWW() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZXX() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZXY() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZXZ() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZXW() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZYX() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZYY() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZYZ() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZYW() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZZX() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZZY() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZZZ() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZZW() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WZWX() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WZWY() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WZWZ() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WZWW() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWXX() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWXY() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWXZ() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWXW() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWYX() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWYY() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWYZ() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWYW() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWZX() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWZY() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWZZ() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWZW() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL WWWX() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL WWWY() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL WWWZ() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL WWWW() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRRR() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRRG() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRRB() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRRA() const { return HC_SHUFFLE4D(*this, 0, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRGR() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRGG() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRGB() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRGA() const { return HC_SHUFFLE4D(*this, 0, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRBR() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRBG() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRBB() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRBA() const { return HC_SHUFFLE4D(*this, 0, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RRAR() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RRAG() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RRAB() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RRAA() const { return HC_SHUFFLE4D(*this, 0, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGRR() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGRG() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGRB() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGRA() const { return HC_SHUFFLE4D(*this, 0, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGGR() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGGG() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGGB() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGGA() const { return HC_SHUFFLE4D(*this, 0, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RGBR() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGBG() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGBB() const { return HC_SHUFFLE4D(*this, 0, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGAR() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RGAG() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RGAB() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RGAA() const { return HC_SHUFFLE4D(*this, 0, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBRR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBRG() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBRB() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBRA() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBGR() const { return HC_SHUFFLE4D(*this, 0, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBGG() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBGB() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBGA() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBBR() const { return HC_SHUFFLE4D(*this, 0, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBBG() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBBB() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBBA() const { return HC_SHUFFLE4D(*this, 0, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RBAR() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RBAG() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RBAB() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RBAA() const { return HC_SHUFFLE4D(*this, 0, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RARR() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RARG() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RARB() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RARA() const { return HC_SHUFFLE4D(*this, 0, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RAGR() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RAGG() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RAGB() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RAGA() const { return HC_SHUFFLE4D(*this, 0, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RABR() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RABG() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RABB() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RABA() const { return HC_SHUFFLE4D(*this, 0, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL RAAR() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL RAAG() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL RAAB() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL RAAA() const { return HC_SHUFFLE4D(*this, 0, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRRR() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRRG() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRRB() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRRA() const { return HC_SHUFFLE4D(*this, 1, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRGR() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRGG() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRGB() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRGA() const { return HC_SHUFFLE4D(*this, 1, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRBR() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRBG() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRBB() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRBA() const { return HC_SHUFFLE4D(*this, 1, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GRAR() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GRAG() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GRAB() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GRAA() const { return HC_SHUFFLE4D(*this, 1, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGRR() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGRG() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGRB() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGRA() const { return HC_SHUFFLE4D(*this, 1, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGGR() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGGG() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGGB() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGGA() const { return HC_SHUFFLE4D(*this, 1, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGBR() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGBG() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGBB() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGBA() const { return HC_SHUFFLE4D(*this, 1, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GGAR() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GGAG() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GGAB() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GGAA() const { return HC_SHUFFLE4D(*this, 1, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBRR() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBRG() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBRB() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBRA() const { return HC_SHUFFLE4D(*this, 1, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBGR() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBGG() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBGB() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBGA() const { return HC_SHUFFLE4D(*this, 1, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBBR() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBBG() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBBB() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBBA() const { return HC_SHUFFLE4D(*this, 1, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GBAR() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GBAG() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GBAB() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GBAA() const { return HC_SHUFFLE4D(*this, 1, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GARR() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GARG() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GARB() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GARA() const { return HC_SHUFFLE4D(*this, 1, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GAGR() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GAGG() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GAGB() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GAGA() const { return HC_SHUFFLE4D(*this, 1, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GABR() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GABG() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GABB() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GABA() const { return HC_SHUFFLE4D(*this, 1, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL GAAR() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL GAAG() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL GAAB() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL GAAA() const { return HC_SHUFFLE4D(*this, 1, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRRR() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRRG() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRRB() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRRA() const { return HC_SHUFFLE4D(*this, 2, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRGR() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRGG() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRGB() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRGA() const { return HC_SHUFFLE4D(*this, 2, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRBR() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRBG() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRBB() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRBA() const { return HC_SHUFFLE4D(*this, 2, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BRAR() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BRAG() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BRAB() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BRAA() const { return HC_SHUFFLE4D(*this, 2, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGRR() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGRG() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGRB() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGRA() const { return HC_SHUFFLE4D(*this, 2, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGGR() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGGG() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGGB() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGGA() const { return HC_SHUFFLE4D(*this, 2, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGBR() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGBG() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGBB() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGBA() const { return HC_SHUFFLE4D(*this, 2, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BGAR() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BGAG() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BGAB() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BGAA() const { return HC_SHUFFLE4D(*this, 2, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBRR() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBRG() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBRB() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBRA() const { return HC_SHUFFLE4D(*this, 2, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBGR() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBGG() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBGB() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBGA() const { return HC_SHUFFLE4D(*this, 2, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBBR() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBBG() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBBB() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBBA() const { return HC_SHUFFLE4D(*this, 2, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BBAR() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BBAG() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BBAB() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BBAA() const { return HC_SHUFFLE4D(*this, 2, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BARR() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BARG() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BARB() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BARA() const { return HC_SHUFFLE4D(*this, 2, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BAGR() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BAGG() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BAGB() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BAGA() const { return HC_SHUFFLE4D(*this, 2, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BABR() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BABG() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BABB() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BABA() const { return HC_SHUFFLE4D(*this, 2, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL BAAR() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL BAAG() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL BAAB() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL BAAA() const { return HC_SHUFFLE4D(*this, 2, 3, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARRR() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARRG() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARRB() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARRA() const { return HC_SHUFFLE4D(*this, 3, 0, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARGR() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARGG() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARGB() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARGA() const { return HC_SHUFFLE4D(*this, 3, 0, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARBR() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARBG() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARBB() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARBA() const { return HC_SHUFFLE4D(*this, 3, 0, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ARAR() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ARAG() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ARAB() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ARAA() const { return HC_SHUFFLE4D(*this, 3, 0, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGRR() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGRG() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGRB() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGRA() const { return HC_SHUFFLE4D(*this, 3, 1, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGGR() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGGG() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGGB() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGGA() const { return HC_SHUFFLE4D(*this, 3, 1, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGBR() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGBG() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGBB() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGBA() const { return HC_SHUFFLE4D(*this, 3, 1, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AGAR() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AGAG() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AGAB() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AGAA() const { return HC_SHUFFLE4D(*this, 3, 1, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABRR() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABRG() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABRB() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABRA() const { return HC_SHUFFLE4D(*this, 3, 2, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABGR() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABGG() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABGB() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABGA() const { return HC_SHUFFLE4D(*this, 3, 2, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABBR() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABBG() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABBB() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABBA() const { return HC_SHUFFLE4D(*this, 3, 2, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL ABAR() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL ABAG() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL ABAB() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL ABAA() const { return HC_SHUFFLE4D(*this, 3, 2, 3, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AARR() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AARG() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AARB() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AARA() const { return HC_SHUFFLE4D(*this, 3, 3, 0, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AAGR() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AAGG() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AAGB() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AAGA() const { return HC_SHUFFLE4D(*this, 3, 3, 1, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AABR() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AABG() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AABB() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AABA() const { return HC_SHUFFLE4D(*this, 3, 3, 2, 3); }
	HC_INLINE Vec4D HC_VECTORCALL AAAR() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 0); }
	HC_INLINE Vec4D HC_VECTORCALL AAAG() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 1); }
	HC_INLINE Vec4D HC_VECTORCALL AAAB() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 2); }
	HC_INLINE Vec4D HC_VECTORCALL AAAA() const { return HC_SHUFFLE4D(*this, 3, 3, 3, 3); }
};

HC_INLINE Vec4D HC_VECTORCALL operator+(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_add_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator-(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_sub_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator*(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator*(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_mul_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL operator/(Vec4D _vLeft, double _fRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _mm256_set1_pd(_fRight)); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator/(double _fLeft, Vec4D _vRight) { _vRight.m_dVec = _mm256_div_pd(_mm256_set1_pd(_fLeft), _vRight.m_dVec); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL operator*(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_mul_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator/(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_div_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator+=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator-=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator*=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator/=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator*=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft * _fRight; return _vLeft; }
HC_INLINE Vec4D& HC_VECTORCALL operator/=(Vec4D& _vLeft, double _fRight) { _vLeft = _vLeft / _fRight; return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL operator~(Vec4D _vVector) { return Vec4D(); }
HC_INLINE Vec4D HC_VECTORCALL operator-(Vec4D _vVector) { return Vec4D() - _vVector; }
HC_INLINE bool HC_VECTORCALL operator==(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_EQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator<(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator<=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_LE_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator>=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_GT_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) == 15; }
HC_INLINE bool HC_VECTORCALL operator!=(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_cmp_pd(_vLeft.m_dVec, _vRight.m_dVec, _CMP_NEQ_OQ); return (_mm256_movemask_pd(_vLeft.m_dVec) & 15) != 0; }
HC_INLINE Vec4D HC_VECTORCALL Min(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_min_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL Max(Vec4D _vLeft, Vec4D _vRight) { _vLeft.m_dVec = _mm256_max_pd(_vLeft.m_dVec, _vRight.m_dVec); return _vLeft; }
HC_INLINE Vec4D HC_VECTORCALL Clamp(Vec4D _vVector, Vec4D _vMin, Vec4D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
HC_INLINE double HC_VECTORCALL Sum(const Vec4D _vVector) { return _vVector.X() + _vVector.Y() + _vVector.Z() + _vVector.W(); }
HC_INLINE double HC_VECTORCALL Dot(Vec4D _vLeft, Vec4D _vRight) { return Sum(_vLeft * _vRight); }
HC_INLINE double HC_VECTORCALL Length(Vec4D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
HC_INLINE double HC_VECTORCALL LengthSquared(Vec4D _vVector) { return Dot(_vVector, _vVector); }
HC_INLINE Vec4D HC_VECTORCALL Normalize(Vec4D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
HC_INLINE double HC_VECTORCALL AngleBetween(Vec4D _vLeft, Vec4D _vRight) { return acos(Dot(_vLeft, _vRight)); }
HC_INLINE Vec4D HC_VECTORCALL Cross(Vec4D _vLeft, Vec4D _vRight) { _vRight.m_dVec = (_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY().m_dVec; _vRight.SetW(_vLeft.W()); return _vRight; }
HC_INLINE Vec4D HC_VECTORCALL Abs(Vec4D _vVector) { return Vec4D(_mm256_andnot_pd(_vVector.m_dVec, SignBitMaskD().m_dVec)); }

#else

struct HC_ALIGNAS(32) Vec4D
{
	union
	{
		double m_dData[4];
		struct
		{
			double x;
			double y;
			double z;
			double w;
		};
	};

	HC_INLINE Vec4D() { m_dData[0] = 0.0f; m_dData[1] = 0.0f; m_dData[2] = 0.0f; m_dData[3] = 0.0f; }
	HC_INLINE explicit Vec4D(float _fVal) { m_dData[0] = static_cast<double>(_fVal); m_dData[1] = static_cast<double>(_fVal); m_dData[2] = static_cast<double>(_fVal); m_dData[3] = static_cast<double>(_fVal); }
	HC_INLINE explicit Vec4D(int _iVal) { m_dData[0] = static_cast<double>(_iVal); m_dData[1] = static_cast<double>(_iVal); m_dData[2] = static_cast<double>(_iVal); m_dData[3] = static_cast<double>(_iVal); }
	HC_INLINE explicit Vec4D(double _dVal) { m_dData[0] = _dVal; m_dData[1] = _dVal; m_dData[2] = _dVal; m_dData[3] = _dVal; }
	HC_INLINE explicit Vec4D(float _fX, float _fY, float _fZ, float _fW) { m_dData[0] = static_cast<double>(_fX); m_dData[1] = static_cast<double>(_fY); m_dData[2] = static_cast<double>(_fZ); m_dData[3] = static_cast<double>(_fW); }
	HC_INLINE explicit Vec4D(int _iX, int _iY, int _iZ, int _iW) { m_dData[0] = static_cast<float>(_iX); m_dData[1] = static_cast<float>(_iY); m_dData[2] = static_cast<float>(_iZ); m_dData[3] = static_cast<float>(_iW); }
	HC_INLINE explicit Vec4D(double _dX, double _dY, double _dZ, double _dW) { m_dData[0] = _dX; m_dData[1] = _dY; m_dData[2] = _dZ; m_dData[3] = _dW; }
	HC_INLINE explicit Vec4D(Vec2D _vXY, double _fZ, double _fW) { m_dData[0] = _vXY.x; m_dData[1] = _vXY.y; m_dData[2] = _fZ; m_dData[3] = _fW; }
	HC_INLINE explicit Vec4D(double _fX, Vec2D _vYZ, double _fW) { m_dData[0] = _fX; m_dData[1] = _vYZ.x; m_dData[2] = _vYZ.y; m_dData[3] = _fW; }
	HC_INLINE explicit Vec4D(double _fX, double _fY, Vec2D _vZW) { m_dData[0] = _fX; m_dData[1] = _fY; m_dData[2] = _vZW.x; m_dData[3] = _vZW.y; }
	HC_INLINE explicit Vec4D(Vec2D _vXY, Vec2D _vZW) { m_dData[0] = _vXY.x; m_dData[1] = _vXY.y; m_dData[2] = _vZW.x; m_dData[3] = _vZW.y; }
	HC_INLINE explicit Vec4D(Vec3D _vXYZ, double _fW) { m_dData[0] = _vXYZ.x; m_dData[1] = _vXYZ.y; m_dData[2] = _vXYZ.z; m_dData[3] = _fW; }
	HC_INLINE explicit Vec4D(double _fX, Vec3D _vYZW) { m_dData[0] = _fX; m_dData[1] = _vYZW.x; m_dData[2] = _vYZW.y; m_dData[3] = _vYZW.z; }

	[[nodiscard]] HC_INLINE double operator[](int _iNdx) const { assert(_iNdx < 4); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE double& operator[](int _iNdx) { assert(_iNdx < 4); return m_dData[_iNdx]; }
	[[nodiscard]] HC_INLINE Vec2D XX() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D YY() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D ZZ() const { return Vec2D(z, z); }
	[[nodiscard]] HC_INLINE Vec2D WW() const { return Vec2D(w, w); }
	[[nodiscard]] HC_INLINE Vec2D XY() const { return Vec2D(x, y); }
	[[nodiscard]] HC_INLINE Vec2D XZ() const { return Vec2D(x, z); }
	[[nodiscard]] HC_INLINE Vec2D XW() const { return Vec2D(x, w); }
	[[nodiscard]] HC_INLINE Vec2D YX() const { return Vec2D(y, x); }
	[[nodiscard]] HC_INLINE Vec2D YZ() const { return Vec2D(y, z); }
	[[nodiscard]] HC_INLINE Vec2D YW() const { return Vec2D(y, w); }
	[[nodiscard]] HC_INLINE Vec2D ZX() const { return Vec2D(z, x); }
	[[nodiscard]] HC_INLINE Vec2D ZY() const { return Vec2D(z, y); }
	[[nodiscard]] HC_INLINE Vec2D ZW() const { return Vec2D(z, w); }
	[[nodiscard]] HC_INLINE Vec2D WX() const { return Vec2D(w, x); }
	[[nodiscard]] HC_INLINE Vec2D WY() const { return Vec2D(w, y); }
	[[nodiscard]] HC_INLINE Vec2D WZ() const { return Vec2D(w, z); }
	[[nodiscard]] HC_INLINE Vec2D RR() const { return Vec2D(x, x); }
	[[nodiscard]] HC_INLINE Vec2D GG() const { return Vec2D(y, y); }
	[[nodiscard]] HC_INLINE Vec2D BB() const { return Vec2D(z, z); }
	[[nodiscard]] HC_INLINE Vec2D AA() const { return Vec2D(w, w); }
	[[nodiscard]] HC_INLINE Vec2D RG() const { return Vec2D(x, y); }
	[[nodiscard]] HC_INLINE Vec2D RB() const { return Vec2D(x, z); }
	[[nodiscard]] HC_INLINE Vec2D RA() const { return Vec2D(x, w); }
	[[nodiscard]] HC_INLINE Vec2D GR() const { return Vec2D(y, x); }
	[[nodiscard]] HC_INLINE Vec2D GB() const { return Vec2D(y, z); }
	[[nodiscard]] HC_INLINE Vec2D GA() const { return Vec2D(y, w); }
	[[nodiscard]] HC_INLINE Vec2D BR() const { return Vec2D(z, x); }
	[[nodiscard]] HC_INLINE Vec2D BG() const { return Vec2D(z, y); }
	[[nodiscard]] HC_INLINE Vec2D BA() const { return Vec2D(z, w); }
	[[nodiscard]] HC_INLINE Vec2D AR() const { return Vec2D(w, x); }
	[[nodiscard]] HC_INLINE Vec2D AG() const { return Vec2D(w, y); }
	[[nodiscard]] HC_INLINE Vec2D AB() const { return Vec2D(w, z); }
	[[nodiscard]] HC_INLINE Vec3D XXX() const { return Vec3D(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3D XXY() const { return Vec3D(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3D XXZ() const { return Vec3D(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3D XXW() const { return Vec3D(x, x, w); }
	[[nodiscard]] HC_INLINE Vec3D XYX() const { return Vec3D(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3D XYY() const { return Vec3D(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3D XYZ() const { return Vec3D(x, y, z); }
	[[nodiscard]] HC_INLINE Vec3D XYW() const { return Vec3D(x, y, w); }
	[[nodiscard]] HC_INLINE Vec3D XZX() const { return Vec3D(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3D XZY() const { return Vec3D(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3D XZZ() const { return Vec3D(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3D XZW() const { return Vec3D(x, z, w); }
	[[nodiscard]] HC_INLINE Vec3D XWX() const { return Vec3D(x, w, x); }
	[[nodiscard]] HC_INLINE Vec3D XWY() const { return Vec3D(x, w, y); }
	[[nodiscard]] HC_INLINE Vec3D XWZ() const { return Vec3D(x, w, z); }
	[[nodiscard]] HC_INLINE Vec3D XWW() const { return Vec3D(x, w, w); }
	[[nodiscard]] HC_INLINE Vec3D YXX() const { return Vec3D(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3D YXY() const { return Vec3D(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3D YXZ() const { return Vec3D(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3D YXW() const { return Vec3D(y, x, w); }
	[[nodiscard]] HC_INLINE Vec3D YYX() const { return Vec3D(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3D YYY() const { return Vec3D(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3D YYZ() const { return Vec3D(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3D YYW() const { return Vec3D(y, y, w); }
	[[nodiscard]] HC_INLINE Vec3D YZX() const { return Vec3D(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3D YZY() const { return Vec3D(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3D YZZ() const { return Vec3D(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3D YZW() const { return Vec3D(y, z, w); }
	[[nodiscard]] HC_INLINE Vec3D YWX() const { return Vec3D(y, w, x); }
	[[nodiscard]] HC_INLINE Vec3D YWY() const { return Vec3D(y, w, y); }
	[[nodiscard]] HC_INLINE Vec3D YWZ() const { return Vec3D(y, w, z); }
	[[nodiscard]] HC_INLINE Vec3D YWW() const { return Vec3D(y, w, w); }
	[[nodiscard]] HC_INLINE Vec3D ZXX() const { return Vec3D(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3D ZXY() const { return Vec3D(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3D ZXZ() const { return Vec3D(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3D ZXW() const { return Vec3D(z, x, w); }
	[[nodiscard]] HC_INLINE Vec3D ZYX() const { return Vec3D(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3D ZYY() const { return Vec3D(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3D ZYZ() const { return Vec3D(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3D ZYW() const { return Vec3D(z, y, w); }
	[[nodiscard]] HC_INLINE Vec3D ZZX() const { return Vec3D(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3D ZZY() const { return Vec3D(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3D ZZZ() const { return Vec3D(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3D ZZW() const { return Vec3D(z, z, w); }
	[[nodiscard]] HC_INLINE Vec3D ZWX() const { return Vec3D(z, w, x); }
	[[nodiscard]] HC_INLINE Vec3D ZWY() const { return Vec3D(z, w, y); }
	[[nodiscard]] HC_INLINE Vec3D ZWZ() const { return Vec3D(z, w, z); }
	[[nodiscard]] HC_INLINE Vec3D ZWW() const { return Vec3D(z, w, w); }
	[[nodiscard]] HC_INLINE Vec3D WXX() const { return Vec3D(w, x, x); }
	[[nodiscard]] HC_INLINE Vec3D WXY() const { return Vec3D(w, x, y); }
	[[nodiscard]] HC_INLINE Vec3D WXZ() const { return Vec3D(w, x, z); }
	[[nodiscard]] HC_INLINE Vec3D WXW() const { return Vec3D(w, x, w); }
	[[nodiscard]] HC_INLINE Vec3D WYX() const { return Vec3D(w, y, x); }
	[[nodiscard]] HC_INLINE Vec3D WYY() const { return Vec3D(w, y, y); }
	[[nodiscard]] HC_INLINE Vec3D WYZ() const { return Vec3D(w, y, z); }
	[[nodiscard]] HC_INLINE Vec3D WYW() const { return Vec3D(w, y, w); }
	[[nodiscard]] HC_INLINE Vec3D WZX() const { return Vec3D(w, z, x); }
	[[nodiscard]] HC_INLINE Vec3D WZY() const { return Vec3D(w, z, y); }
	[[nodiscard]] HC_INLINE Vec3D WZZ() const { return Vec3D(w, z, z); }
	[[nodiscard]] HC_INLINE Vec3D WZW() const { return Vec3D(w, z, w); }
	[[nodiscard]] HC_INLINE Vec3D WWX() const { return Vec3D(w, w, x); }
	[[nodiscard]] HC_INLINE Vec3D WWY() const { return Vec3D(w, w, y); }
	[[nodiscard]] HC_INLINE Vec3D WWZ() const { return Vec3D(w, w, z); }
	[[nodiscard]] HC_INLINE Vec3D WWW() const { return Vec3D(w, w, w); }
	[[nodiscard]] HC_INLINE Vec3D RRR() const { return Vec3D(x, x, x); }
	[[nodiscard]] HC_INLINE Vec3D RRG() const { return Vec3D(x, x, y); }
	[[nodiscard]] HC_INLINE Vec3D RRB() const { return Vec3D(x, x, z); }
	[[nodiscard]] HC_INLINE Vec3D RRA() const { return Vec3D(x, x, w); }
	[[nodiscard]] HC_INLINE Vec3D RGR() const { return Vec3D(x, y, x); }
	[[nodiscard]] HC_INLINE Vec3D RGG() const { return Vec3D(x, y, y); }
	[[nodiscard]] HC_INLINE Vec3D RGA() const { return Vec3D(x, y, z); }
	[[nodiscard]] HC_INLINE Vec3D RGB() const { return Vec3D(x, y, w); }
	[[nodiscard]] HC_INLINE Vec3D RBR() const { return Vec3D(x, z, x); }
	[[nodiscard]] HC_INLINE Vec3D RBG() const { return Vec3D(x, z, y); }
	[[nodiscard]] HC_INLINE Vec3D RBB() const { return Vec3D(x, z, z); }
	[[nodiscard]] HC_INLINE Vec3D RBA() const { return Vec3D(x, z, w); }
	[[nodiscard]] HC_INLINE Vec3D RAR() const { return Vec3D(x, w, x); }
	[[nodiscard]] HC_INLINE Vec3D RAG() const { return Vec3D(x, w, y); }
	[[nodiscard]] HC_INLINE Vec3D RAB() const { return Vec3D(x, w, z); }
	[[nodiscard]] HC_INLINE Vec3D RAA() const { return Vec3D(x, w, w); }
	[[nodiscard]] HC_INLINE Vec3D GRR() const { return Vec3D(y, x, x); }
	[[nodiscard]] HC_INLINE Vec3D GRG() const { return Vec3D(y, x, y); }
	[[nodiscard]] HC_INLINE Vec3D GRB() const { return Vec3D(y, x, z); }
	[[nodiscard]] HC_INLINE Vec3D GRA() const { return Vec3D(y, x, w); }
	[[nodiscard]] HC_INLINE Vec3D GGR() const { return Vec3D(y, y, x); }
	[[nodiscard]] HC_INLINE Vec3D GGG() const { return Vec3D(y, y, y); }
	[[nodiscard]] HC_INLINE Vec3D GGB() const { return Vec3D(y, y, z); }
	[[nodiscard]] HC_INLINE Vec3D GGA() const { return Vec3D(y, y, w); }
	[[nodiscard]] HC_INLINE Vec3D GBR() const { return Vec3D(y, z, x); }
	[[nodiscard]] HC_INLINE Vec3D GBG() const { return Vec3D(y, z, y); }
	[[nodiscard]] HC_INLINE Vec3D GBB() const { return Vec3D(y, z, z); }
	[[nodiscard]] HC_INLINE Vec3D GBA() const { return Vec3D(y, z, w); }
	[[nodiscard]] HC_INLINE Vec3D GAR() const { return Vec3D(y, w, x); }
	[[nodiscard]] HC_INLINE Vec3D GAG() const { return Vec3D(y, w, y); }
	[[nodiscard]] HC_INLINE Vec3D GAB() const { return Vec3D(y, w, z); }
	[[nodiscard]] HC_INLINE Vec3D GAA() const { return Vec3D(y, w, w); }
	[[nodiscard]] HC_INLINE Vec3D BRR() const { return Vec3D(z, x, x); }
	[[nodiscard]] HC_INLINE Vec3D BRG() const { return Vec3D(z, x, y); }
	[[nodiscard]] HC_INLINE Vec3D BRB() const { return Vec3D(z, x, z); }
	[[nodiscard]] HC_INLINE Vec3D BRA() const { return Vec3D(z, x, w); }
	[[nodiscard]] HC_INLINE Vec3D BGR() const { return Vec3D(z, y, x); }
	[[nodiscard]] HC_INLINE Vec3D BGG() const { return Vec3D(z, y, y); }
	[[nodiscard]] HC_INLINE Vec3D BGB() const { return Vec3D(z, y, z); }
	[[nodiscard]] HC_INLINE Vec3D BGA() const { return Vec3D(z, y, w); }
	[[nodiscard]] HC_INLINE Vec3D BBR() const { return Vec3D(z, z, x); }
	[[nodiscard]] HC_INLINE Vec3D BBG() const { return Vec3D(z, z, y); }
	[[nodiscard]] HC_INLINE Vec3D BBB() const { return Vec3D(z, z, z); }
	[[nodiscard]] HC_INLINE Vec3D BBA() const { return Vec3D(z, z, w); }
	[[nodiscard]] HC_INLINE Vec3D BAR() const { return Vec3D(z, w, x); }
	[[nodiscard]] HC_INLINE Vec3D BAG() const { return Vec3D(z, w, y); }
	[[nodiscard]] HC_INLINE Vec3D BAB() const { return Vec3D(z, w, z); }
	[[nodiscard]] HC_INLINE Vec3D BAA() const { return Vec3D(z, w, w); }
	[[nodiscard]] HC_INLINE Vec3D ARR() const { return Vec3D(w, x, x); }
	[[nodiscard]] HC_INLINE Vec3D ARG() const { return Vec3D(w, x, y); }
	[[nodiscard]] HC_INLINE Vec3D ARB() const { return Vec3D(w, x, z); }
	[[nodiscard]] HC_INLINE Vec3D ARA() const { return Vec3D(w, x, w); }
	[[nodiscard]] HC_INLINE Vec3D AGR() const { return Vec3D(w, y, x); }
	[[nodiscard]] HC_INLINE Vec3D AGG() const { return Vec3D(w, y, y); }
	[[nodiscard]] HC_INLINE Vec3D AGB() const { return Vec3D(w, y, z); }
	[[nodiscard]] HC_INLINE Vec3D AGA() const { return Vec3D(w, y, w); }
	[[nodiscard]] HC_INLINE Vec3D ABR() const { return Vec3D(w, z, x); }
	[[nodiscard]] HC_INLINE Vec3D ABG() const { return Vec3D(w, z, y); }
	[[nodiscard]] HC_INLINE Vec3D ABB() const { return Vec3D(w, z, z); }
	[[nodiscard]] HC_INLINE Vec3D ABA() const { return Vec3D(w, z, w); }
	[[nodiscard]] HC_INLINE Vec3D AAR() const { return Vec3D(w, w, x); }
	[[nodiscard]] HC_INLINE Vec3D AAG() const { return Vec3D(w, w, y); }
	[[nodiscard]] HC_INLINE Vec3D AAB() const { return Vec3D(w, w, z); }
	[[nodiscard]] HC_INLINE Vec3D AAA() const { return Vec3D(w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D XXXX() const { return Vec4D(x, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D XXXY() const { return Vec4D(x, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D XXXZ() const { return Vec4D(x, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D XXXW() const { return Vec4D(x, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D XXYX() const { return Vec4D(x, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D XXYY() const { return Vec4D(x, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D XXYZ() const { return Vec4D(x, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D XXYW() const { return Vec4D(x, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D XXZX() const { return Vec4D(x, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D XXZY() const { return Vec4D(x, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D XXZZ() const { return Vec4D(x, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D XXZW() const { return Vec4D(x, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D XXWX() const { return Vec4D(x, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D XXWY() const { return Vec4D(x, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D XXWZ() const { return Vec4D(x, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D XXWW() const { return Vec4D(x, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D XYXX() const { return Vec4D(x, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D XYXY() const { return Vec4D(x, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D XYXZ() const { return Vec4D(x, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D XYXW() const { return Vec4D(x, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D XYYX() const { return Vec4D(x, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D XYYY() const { return Vec4D(x, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D XYYZ() const { return Vec4D(x, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D XYYW() const { return Vec4D(x, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D XYZX() const { return Vec4D(x, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D XYZY() const { return Vec4D(x, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D XYZZ() const { return Vec4D(x, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D XYWX() const { return Vec4D(x, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D XYWY() const { return Vec4D(x, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D XYWZ() const { return Vec4D(x, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D XYWW() const { return Vec4D(x, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D XZXX() const { return Vec4D(x, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D XZXY() const { return Vec4D(x, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D XZXZ() const { return Vec4D(x, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D XZXW() const { return Vec4D(x, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D XZYX() const { return Vec4D(x, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D XZYY() const { return Vec4D(x, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D XZYZ() const { return Vec4D(x, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D XZYW() const { return Vec4D(x, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D XZZX() const { return Vec4D(x, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D XZZY() const { return Vec4D(x, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D XZZZ() const { return Vec4D(x, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D XZZW() const { return Vec4D(x, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D XZWX() const { return Vec4D(x, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D XZWY() const { return Vec4D(x, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D XZWZ() const { return Vec4D(x, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D XZWW() const { return Vec4D(x, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D XWXX() const { return Vec4D(x, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D XWXY() const { return Vec4D(x, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D XWXZ() const { return Vec4D(x, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D XWXW() const { return Vec4D(x, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D XWYX() const { return Vec4D(x, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D XWYY() const { return Vec4D(x, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D XWYZ() const { return Vec4D(x, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D XWYW() const { return Vec4D(x, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D XWZX() const { return Vec4D(x, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D XWZY() const { return Vec4D(x, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D XWZZ() const { return Vec4D(x, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D XWZW() const { return Vec4D(x, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D XWWX() const { return Vec4D(x, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D XWWY() const { return Vec4D(x, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D XWWZ() const { return Vec4D(x, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D XWWW() const { return Vec4D(x, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D YXXX() const { return Vec4D(y, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D YXXY() const { return Vec4D(y, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D YXXZ() const { return Vec4D(y, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D YXXW() const { return Vec4D(y, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D YXYX() const { return Vec4D(y, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D YXYY() const { return Vec4D(y, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D YXYZ() const { return Vec4D(y, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D YXYW() const { return Vec4D(y, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D YXZX() const { return Vec4D(y, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D YXZY() const { return Vec4D(y, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D YXZZ() const { return Vec4D(y, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D YXZW() const { return Vec4D(y, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D YXWX() const { return Vec4D(y, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D YXWY() const { return Vec4D(y, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D YXWZ() const { return Vec4D(y, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D YXWW() const { return Vec4D(y, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D YYXX() const { return Vec4D(y, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D YYXY() const { return Vec4D(y, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D YYXZ() const { return Vec4D(y, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D YYXW() const { return Vec4D(y, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D YYYX() const { return Vec4D(y, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D YYYY() const { return Vec4D(y, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D YYYZ() const { return Vec4D(y, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D YYYW() const { return Vec4D(y, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D YYZX() const { return Vec4D(y, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D YYZY() const { return Vec4D(y, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D YYZZ() const { return Vec4D(y, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D YYZW() const { return Vec4D(y, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D YYWX() const { return Vec4D(y, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D YYWY() const { return Vec4D(y, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D YYWZ() const { return Vec4D(y, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D YYWW() const { return Vec4D(y, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D YZXX() const { return Vec4D(y, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D YZXY() const { return Vec4D(y, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D YZXZ() const { return Vec4D(y, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D YZXW() const { return Vec4D(y, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D YZYX() const { return Vec4D(y, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D YZYY() const { return Vec4D(y, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D YZYZ() const { return Vec4D(y, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D YZYW() const { return Vec4D(y, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D YZZX() const { return Vec4D(y, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D YZZY() const { return Vec4D(y, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D YZZZ() const { return Vec4D(y, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D YZZW() const { return Vec4D(y, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D YZWX() const { return Vec4D(y, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D YZWY() const { return Vec4D(y, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D YZWZ() const { return Vec4D(y, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D YZWW() const { return Vec4D(y, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D YWXX() const { return Vec4D(y, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D YWXY() const { return Vec4D(y, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D YWXZ() const { return Vec4D(y, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D YWXW() const { return Vec4D(y, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D YWYX() const { return Vec4D(y, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D YWYY() const { return Vec4D(y, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D YWYZ() const { return Vec4D(y, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D YWYW() const { return Vec4D(y, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D YWZX() const { return Vec4D(y, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D YWZY() const { return Vec4D(y, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D YWZZ() const { return Vec4D(y, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D YWZW() const { return Vec4D(y, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D YWWX() const { return Vec4D(y, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D YWWY() const { return Vec4D(y, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D YWWZ() const { return Vec4D(y, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D YWWW() const { return Vec4D(y, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ZXXX() const { return Vec4D(z, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ZXXY() const { return Vec4D(z, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ZXXZ() const { return Vec4D(z, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ZXXW() const { return Vec4D(z, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ZXYX() const { return Vec4D(z, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ZXYY() const { return Vec4D(z, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ZXYZ() const { return Vec4D(z, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ZXYW() const { return Vec4D(z, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ZXZX() const { return Vec4D(z, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ZXZY() const { return Vec4D(z, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ZXZZ() const { return Vec4D(z, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ZXZW() const { return Vec4D(z, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ZXWX() const { return Vec4D(z, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ZXWY() const { return Vec4D(z, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ZXWZ() const { return Vec4D(z, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ZXWW() const { return Vec4D(z, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ZYXX() const { return Vec4D(z, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ZYXY() const { return Vec4D(z, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ZYXZ() const { return Vec4D(z, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ZYXW() const { return Vec4D(z, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ZYYX() const { return Vec4D(z, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ZYYY() const { return Vec4D(z, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ZYYZ() const { return Vec4D(z, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ZYYW() const { return Vec4D(z, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ZYZX() const { return Vec4D(z, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ZYZY() const { return Vec4D(z, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ZYZZ() const { return Vec4D(z, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ZYZW() const { return Vec4D(z, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ZYWX() const { return Vec4D(z, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ZYWY() const { return Vec4D(z, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ZYWZ() const { return Vec4D(z, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ZYWW() const { return Vec4D(z, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ZZXX() const { return Vec4D(z, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ZZXY() const { return Vec4D(z, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ZZXZ() const { return Vec4D(z, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ZZXW() const { return Vec4D(z, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ZZYX() const { return Vec4D(z, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ZZYY() const { return Vec4D(z, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ZZYZ() const { return Vec4D(z, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ZZYW() const { return Vec4D(z, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ZZZX() const { return Vec4D(z, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ZZZY() const { return Vec4D(z, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ZZZZ() const { return Vec4D(z, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ZZZW() const { return Vec4D(z, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ZZWX() const { return Vec4D(z, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ZZWY() const { return Vec4D(z, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ZZWZ() const { return Vec4D(z, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ZZWW() const { return Vec4D(z, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ZWXX() const { return Vec4D(z, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ZWXY() const { return Vec4D(z, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ZWXZ() const { return Vec4D(z, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ZWXW() const { return Vec4D(z, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ZWYX() const { return Vec4D(z, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ZWYY() const { return Vec4D(z, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ZWYZ() const { return Vec4D(z, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ZWYW() const { return Vec4D(z, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ZWZX() const { return Vec4D(z, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ZWZY() const { return Vec4D(z, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ZWZZ() const { return Vec4D(z, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ZWZW() const { return Vec4D(z, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ZWWX() const { return Vec4D(z, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ZWWY() const { return Vec4D(z, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ZWWZ() const { return Vec4D(z, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ZWWW() const { return Vec4D(z, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D WXXX() const { return Vec4D(w, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D WXXY() const { return Vec4D(w, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D WXXZ() const { return Vec4D(w, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D WXXW() const { return Vec4D(w, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D WXYX() const { return Vec4D(w, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D WXYY() const { return Vec4D(w, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D WXYZ() const { return Vec4D(w, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D WXYW() const { return Vec4D(w, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D WXZX() const { return Vec4D(w, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D WXZY() const { return Vec4D(w, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D WXZZ() const { return Vec4D(w, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D WXZW() const { return Vec4D(w, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D WXWX() const { return Vec4D(w, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D WXWY() const { return Vec4D(w, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D WXWZ() const { return Vec4D(w, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D WXWW() const { return Vec4D(w, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D WYXX() const { return Vec4D(w, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D WYXY() const { return Vec4D(w, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D WYXZ() const { return Vec4D(w, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D WYXW() const { return Vec4D(w, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D WYYX() const { return Vec4D(w, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D WYYY() const { return Vec4D(w, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D WYYZ() const { return Vec4D(w, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D WYYW() const { return Vec4D(w, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D WYZX() const { return Vec4D(w, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D WYZY() const { return Vec4D(w, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D WYZZ() const { return Vec4D(w, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D WYZW() const { return Vec4D(w, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D WYWX() const { return Vec4D(w, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D WYWY() const { return Vec4D(w, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D WYWZ() const { return Vec4D(w, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D WYWW() const { return Vec4D(w, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D WZXX() const { return Vec4D(w, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D WZXY() const { return Vec4D(w, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D WZXZ() const { return Vec4D(w, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D WZXW() const { return Vec4D(w, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D WZYX() const { return Vec4D(w, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D WZYY() const { return Vec4D(w, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D WZYZ() const { return Vec4D(w, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D WZYW() const { return Vec4D(w, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D WZZX() const { return Vec4D(w, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D WZZY() const { return Vec4D(w, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D WZZZ() const { return Vec4D(w, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D WZZW() const { return Vec4D(w, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D WZWX() const { return Vec4D(w, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D WZWY() const { return Vec4D(w, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D WZWZ() const { return Vec4D(w, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D WZWW() const { return Vec4D(w, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D WWXX() const { return Vec4D(w, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D WWXY() const { return Vec4D(w, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D WWXZ() const { return Vec4D(w, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D WWXW() const { return Vec4D(w, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D WWYX() const { return Vec4D(w, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D WWYY() const { return Vec4D(w, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D WWYZ() const { return Vec4D(w, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D WWYW() const { return Vec4D(w, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D WWZX() const { return Vec4D(w, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D WWZY() const { return Vec4D(w, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D WWZZ() const { return Vec4D(w, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D WWZW() const { return Vec4D(w, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D WWWX() const { return Vec4D(w, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D WWWY() const { return Vec4D(w, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D WWWZ() const { return Vec4D(w, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D WWWW() const { return Vec4D(w, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D RRRR() const { return Vec4D(x, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D RRRG() const { return Vec4D(x, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D RRRB() const { return Vec4D(x, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D RRRA() const { return Vec4D(x, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D RRGR() const { return Vec4D(x, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D RRGG() const { return Vec4D(x, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D RRGB() const { return Vec4D(x, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D RRGA() const { return Vec4D(x, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D RRBR() const { return Vec4D(x, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D RRBG() const { return Vec4D(x, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D RRBB() const { return Vec4D(x, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D RRBA() const { return Vec4D(x, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D RRAR() const { return Vec4D(x, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D RRAG() const { return Vec4D(x, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D RRAB() const { return Vec4D(x, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D RRAA() const { return Vec4D(x, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D RGRR() const { return Vec4D(x, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D RGRG() const { return Vec4D(x, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D RGRB() const { return Vec4D(x, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D RGRA() const { return Vec4D(x, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D RGGR() const { return Vec4D(x, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D RGGG() const { return Vec4D(x, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D RGGB() const { return Vec4D(x, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D RGGA() const { return Vec4D(x, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D RGBR() const { return Vec4D(x, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D RGBG() const { return Vec4D(x, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D RGBB() const { return Vec4D(x, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D RGAR() const { return Vec4D(x, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D RGAG() const { return Vec4D(x, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D RGAB() const { return Vec4D(x, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D RGAA() const { return Vec4D(x, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D RBRR() const { return Vec4D(x, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D RBRG() const { return Vec4D(x, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D RBRB() const { return Vec4D(x, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D RBRA() const { return Vec4D(x, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D RBGR() const { return Vec4D(x, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D RBGG() const { return Vec4D(x, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D RBGB() const { return Vec4D(x, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D RBGA() const { return Vec4D(x, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D RBBR() const { return Vec4D(x, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D RBBG() const { return Vec4D(x, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D RBBB() const { return Vec4D(x, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D RBBA() const { return Vec4D(x, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D RBAR() const { return Vec4D(x, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D RBAG() const { return Vec4D(x, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D RBAB() const { return Vec4D(x, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D RBAA() const { return Vec4D(x, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D RARR() const { return Vec4D(x, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D RARG() const { return Vec4D(x, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D RARB() const { return Vec4D(x, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D RARA() const { return Vec4D(x, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D RAGR() const { return Vec4D(x, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D RAGG() const { return Vec4D(x, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D RAGB() const { return Vec4D(x, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D RAGA() const { return Vec4D(x, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D RABR() const { return Vec4D(x, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D RABG() const { return Vec4D(x, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D RABB() const { return Vec4D(x, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D RABA() const { return Vec4D(x, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D RAAR() const { return Vec4D(x, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D RAAG() const { return Vec4D(x, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D RAAB() const { return Vec4D(x, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D RAAA() const { return Vec4D(x, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D GRRR() const { return Vec4D(y, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D GRRG() const { return Vec4D(y, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D GRRB() const { return Vec4D(y, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D GRRA() const { return Vec4D(y, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D GRGR() const { return Vec4D(y, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D GRGG() const { return Vec4D(y, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D GRGB() const { return Vec4D(y, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D GRGA() const { return Vec4D(y, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D GRBR() const { return Vec4D(y, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D GRBG() const { return Vec4D(y, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D GRBB() const { return Vec4D(y, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D GRBA() const { return Vec4D(y, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D GRAR() const { return Vec4D(y, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D GRAG() const { return Vec4D(y, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D GRAB() const { return Vec4D(y, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D GRAA() const { return Vec4D(y, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D GGRR() const { return Vec4D(y, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D GGRG() const { return Vec4D(y, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D GGRB() const { return Vec4D(y, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D GGRA() const { return Vec4D(y, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D GGGR() const { return Vec4D(y, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D GGGG() const { return Vec4D(y, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D GGGB() const { return Vec4D(y, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D GGGA() const { return Vec4D(y, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D GGBR() const { return Vec4D(y, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D GGBG() const { return Vec4D(y, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D GGBB() const { return Vec4D(y, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D GGBA() const { return Vec4D(y, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D GGAR() const { return Vec4D(y, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D GGAG() const { return Vec4D(y, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D GGAB() const { return Vec4D(y, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D GGAA() const { return Vec4D(y, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D GBRR() const { return Vec4D(y, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D GBRG() const { return Vec4D(y, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D GBRB() const { return Vec4D(y, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D GBRA() const { return Vec4D(y, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D GBGR() const { return Vec4D(y, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D GBGG() const { return Vec4D(y, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D GBGB() const { return Vec4D(y, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D GBGA() const { return Vec4D(y, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D GBBR() const { return Vec4D(y, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D GBBG() const { return Vec4D(y, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D GBBB() const { return Vec4D(y, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D GBBA() const { return Vec4D(y, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D GBAR() const { return Vec4D(y, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D GBAG() const { return Vec4D(y, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D GBAB() const { return Vec4D(y, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D GBAA() const { return Vec4D(y, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D GARR() const { return Vec4D(y, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D GARG() const { return Vec4D(y, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D GARB() const { return Vec4D(y, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D GARA() const { return Vec4D(y, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D GAGR() const { return Vec4D(y, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D GAGG() const { return Vec4D(y, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D GAGB() const { return Vec4D(y, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D GAGA() const { return Vec4D(y, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D GABR() const { return Vec4D(y, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D GABG() const { return Vec4D(y, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D GABB() const { return Vec4D(y, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D GABA() const { return Vec4D(y, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D GAAR() const { return Vec4D(y, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D GAAG() const { return Vec4D(y, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D GAAB() const { return Vec4D(y, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D GAAA() const { return Vec4D(y, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D BRRR() const { return Vec4D(z, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D BRRG() const { return Vec4D(z, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D BRRB() const { return Vec4D(z, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D BRRA() const { return Vec4D(z, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D BRGR() const { return Vec4D(z, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D BRGG() const { return Vec4D(z, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D BRGB() const { return Vec4D(z, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D BRGA() const { return Vec4D(z, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D BRBR() const { return Vec4D(z, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D BRBG() const { return Vec4D(z, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D BRBB() const { return Vec4D(z, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D BRBA() const { return Vec4D(z, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D BRAR() const { return Vec4D(z, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D BRAG() const { return Vec4D(z, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D BRAB() const { return Vec4D(z, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D BRAA() const { return Vec4D(z, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D BGRR() const { return Vec4D(z, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D BGRG() const { return Vec4D(z, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D BGRB() const { return Vec4D(z, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D BGRA() const { return Vec4D(z, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D BGGR() const { return Vec4D(z, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D BGGG() const { return Vec4D(z, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D BGGB() const { return Vec4D(z, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D BGGA() const { return Vec4D(z, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D BGBR() const { return Vec4D(z, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D BGBG() const { return Vec4D(z, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D BGBB() const { return Vec4D(z, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D BGBA() const { return Vec4D(z, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D BGAR() const { return Vec4D(z, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D BGAG() const { return Vec4D(z, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D BGAB() const { return Vec4D(z, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D BGAA() const { return Vec4D(z, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D BBRR() const { return Vec4D(z, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D BBRG() const { return Vec4D(z, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D BBRB() const { return Vec4D(z, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D BBRA() const { return Vec4D(z, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D BBGR() const { return Vec4D(z, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D BBGG() const { return Vec4D(z, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D BBGB() const { return Vec4D(z, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D BBGA() const { return Vec4D(z, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D BBBR() const { return Vec4D(z, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D BBBG() const { return Vec4D(z, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D BBBB() const { return Vec4D(z, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D BBBA() const { return Vec4D(z, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D BBAR() const { return Vec4D(z, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D BBAG() const { return Vec4D(z, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D BBAB() const { return Vec4D(z, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D BBAA() const { return Vec4D(z, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D BARR() const { return Vec4D(z, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D BARG() const { return Vec4D(z, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D BARB() const { return Vec4D(z, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D BARA() const { return Vec4D(z, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D BAGR() const { return Vec4D(z, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D BAGG() const { return Vec4D(z, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D BAGB() const { return Vec4D(z, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D BAGA() const { return Vec4D(z, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D BABR() const { return Vec4D(z, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D BABG() const { return Vec4D(z, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D BABB() const { return Vec4D(z, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D BABA() const { return Vec4D(z, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D BAAR() const { return Vec4D(z, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D BAAG() const { return Vec4D(z, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D BAAB() const { return Vec4D(z, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D BAAA() const { return Vec4D(z, w, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ARRR() const { return Vec4D(w, x, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ARRG() const { return Vec4D(w, x, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ARRB() const { return Vec4D(w, x, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ARRA() const { return Vec4D(w, x, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ARGR() const { return Vec4D(w, x, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ARGG() const { return Vec4D(w, x, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ARGB() const { return Vec4D(w, x, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ARGA() const { return Vec4D(w, x, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ARBR() const { return Vec4D(w, x, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ARBG() const { return Vec4D(w, x, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ARBB() const { return Vec4D(w, x, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ARBA() const { return Vec4D(w, x, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ARAR() const { return Vec4D(w, x, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ARAG() const { return Vec4D(w, x, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ARAB() const { return Vec4D(w, x, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ARAA() const { return Vec4D(w, x, w, w); }
	[[nodiscard]] HC_INLINE Vec4D AGRR() const { return Vec4D(w, y, x, x); }
	[[nodiscard]] HC_INLINE Vec4D AGRG() const { return Vec4D(w, y, x, y); }
	[[nodiscard]] HC_INLINE Vec4D AGRB() const { return Vec4D(w, y, x, z); }
	[[nodiscard]] HC_INLINE Vec4D AGRA() const { return Vec4D(w, y, x, w); }
	[[nodiscard]] HC_INLINE Vec4D AGGR() const { return Vec4D(w, y, y, x); }
	[[nodiscard]] HC_INLINE Vec4D AGGG() const { return Vec4D(w, y, y, y); }
	[[nodiscard]] HC_INLINE Vec4D AGGB() const { return Vec4D(w, y, y, z); }
	[[nodiscard]] HC_INLINE Vec4D AGGA() const { return Vec4D(w, y, y, w); }
	[[nodiscard]] HC_INLINE Vec4D AGBR() const { return Vec4D(w, y, z, x); }
	[[nodiscard]] HC_INLINE Vec4D AGBG() const { return Vec4D(w, y, z, y); }
	[[nodiscard]] HC_INLINE Vec4D AGBB() const { return Vec4D(w, y, z, z); }
	[[nodiscard]] HC_INLINE Vec4D AGBA() const { return Vec4D(w, y, z, w); }
	[[nodiscard]] HC_INLINE Vec4D AGAR() const { return Vec4D(w, y, w, x); }
	[[nodiscard]] HC_INLINE Vec4D AGAG() const { return Vec4D(w, y, w, y); }
	[[nodiscard]] HC_INLINE Vec4D AGAB() const { return Vec4D(w, y, w, z); }
	[[nodiscard]] HC_INLINE Vec4D AGAA() const { return Vec4D(w, y, w, w); }
	[[nodiscard]] HC_INLINE Vec4D ABRR() const { return Vec4D(w, z, x, x); }
	[[nodiscard]] HC_INLINE Vec4D ABRG() const { return Vec4D(w, z, x, y); }
	[[nodiscard]] HC_INLINE Vec4D ABRB() const { return Vec4D(w, z, x, z); }
	[[nodiscard]] HC_INLINE Vec4D ABRA() const { return Vec4D(w, z, x, w); }
	[[nodiscard]] HC_INLINE Vec4D ABGR() const { return Vec4D(w, z, y, x); }
	[[nodiscard]] HC_INLINE Vec4D ABGG() const { return Vec4D(w, z, y, y); }
	[[nodiscard]] HC_INLINE Vec4D ABGB() const { return Vec4D(w, z, y, z); }
	[[nodiscard]] HC_INLINE Vec4D ABGA() const { return Vec4D(w, z, y, w); }
	[[nodiscard]] HC_INLINE Vec4D ABBR() const { return Vec4D(w, z, z, x); }
	[[nodiscard]] HC_INLINE Vec4D ABBG() const { return Vec4D(w, z, z, y); }
	[[nodiscard]] HC_INLINE Vec4D ABBB() const { return Vec4D(w, z, z, z); }
	[[nodiscard]] HC_INLINE Vec4D ABBA() const { return Vec4D(w, z, z, w); }
	[[nodiscard]] HC_INLINE Vec4D ABAR() const { return Vec4D(w, z, w, x); }
	[[nodiscard]] HC_INLINE Vec4D ABAG() const { return Vec4D(w, z, w, y); }
	[[nodiscard]] HC_INLINE Vec4D ABAB() const { return Vec4D(w, z, w, z); }
	[[nodiscard]] HC_INLINE Vec4D ABAA() const { return Vec4D(w, z, w, w); }
	[[nodiscard]] HC_INLINE Vec4D AARR() const { return Vec4D(w, w, x, x); }
	[[nodiscard]] HC_INLINE Vec4D AARG() const { return Vec4D(w, w, x, y); }
	[[nodiscard]] HC_INLINE Vec4D AARB() const { return Vec4D(w, w, x, z); }
	[[nodiscard]] HC_INLINE Vec4D AARA() const { return Vec4D(w, w, x, w); }
	[[nodiscard]] HC_INLINE Vec4D AAGR() const { return Vec4D(w, w, y, x); }
	[[nodiscard]] HC_INLINE Vec4D AAGG() const { return Vec4D(w, w, y, y); }
	[[nodiscard]] HC_INLINE Vec4D AAGB() const { return Vec4D(w, w, y, z); }
	[[nodiscard]] HC_INLINE Vec4D AAGA() const { return Vec4D(w, w, y, w); }
	[[nodiscard]] HC_INLINE Vec4D AABR() const { return Vec4D(w, w, z, x); }
	[[nodiscard]] HC_INLINE Vec4D AABG() const { return Vec4D(w, w, z, y); }
	[[nodiscard]] HC_INLINE Vec4D AABB() const { return Vec4D(w, w, z, z); }
	[[nodiscard]] HC_INLINE Vec4D AABA() const { return Vec4D(w, w, z, w); }
	[[nodiscard]] HC_INLINE Vec4D AAAR() const { return Vec4D(w, w, w, x); }
	[[nodiscard]] HC_INLINE Vec4D AAAG() const { return Vec4D(w, w, w, y); }
	[[nodiscard]] HC_INLINE Vec4D AAAB() const { return Vec4D(w, w, w, z); }
	[[nodiscard]] HC_INLINE Vec4D AAAA() const { return Vec4D(w, w, w, w); }
};

[[nodiscard]] HC_INLINE Vec4D operator+(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(_vLeft.x + _vRight.x, _vLeft.y + _vRight.y, _vLeft.z + _vRight.z, _vLeft.w + _vRight.w); }
[[nodiscard]] HC_INLINE Vec4D operator-(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(_vLeft.x - _vRight.x, _vLeft.y - _vRight.y, _vLeft.z - _vRight.z, _vLeft.w - _vRight.w); }
[[nodiscard]] HC_INLINE Vec4D operator*(Vec4D _vLeft, double _dRight) { return Vec4D(_vLeft.x * _dRight, _vLeft.y * _dRight, _vLeft.z * _dRight, _vLeft.w * _dRight); }
[[nodiscard]] HC_INLINE Vec4D operator*(double _dLeft, Vec4D _vRight) { return Vec4D(_vRight.x * _dLeft, _vRight.y * _dLeft, _vRight.z * _dLeft, _vRight.w * _dLeft); }
[[nodiscard]] HC_INLINE Vec4D operator/(Vec4D _vLeft, double _dRight) { return Vec4D(_vLeft.x / _dRight, _vLeft.y / _dRight, _vLeft.z / _dRight, _vLeft.w / _dRight); }
[[nodiscard]] HC_INLINE Vec4D operator/(double _dLeft, Vec4D _vRight) { return Vec4D(_dLeft / _vRight.x, _dLeft / _vRight.y, _dLeft / _vRight.z, _dLeft / _vRight.w); }
[[nodiscard]] HC_INLINE Vec4D operator*(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(_vLeft.x * _vRight.x, _vLeft.y * _vRight.y, _vLeft.z * _vRight.z, _vLeft.w * _vRight.w); }
[[nodiscard]] HC_INLINE Vec4D operator/(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(_vLeft.x / _vRight.x, _vLeft.y / _vRight.y, _vLeft.z / _vRight.z, _vLeft.w / _vRight.w); }
HC_INLINE Vec4D& operator+=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft + _vRight; return _vLeft; }
HC_INLINE Vec4D& operator-=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft - _vRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft * _vRight; return _vLeft; }
HC_INLINE Vec4D& operator/=(Vec4D& _vLeft, Vec4D _vRight) { _vLeft = _vLeft / _vRight; return _vLeft; }
HC_INLINE Vec4D& operator*=(Vec4D& _vLeft, double _dRight) { _vLeft = _vLeft * _dRight; return _vLeft; }
HC_INLINE Vec4D& operator/=(Vec4D& _vLeft, double _dRight) { _vLeft = _vLeft / _dRight; return _vLeft; }
[[nodiscard]] HC_INLINE Vec4D operator~(Vec4D _vVector) { return Vec4D(); }
[[nodiscard]] HC_INLINE Vec4D operator-(Vec4D _vVector) { return Vec4D(-_vVector.x, -_vVector.y, -_vVector.z, -_vVector.w); }
HC_INLINE bool operator==(Vec4D _vLeft, Vec4D _vRight) { return HC_DOUBLE_COMPARE(_vLeft.x, _vRight.x) && HC_DOUBLE_COMPARE(_vLeft.y, _vRight.y) && HC_DOUBLE_COMPARE(_vLeft.z, _vRight.z) && HC_DOUBLE_COMPARE(_vLeft.w, _vRight.w); }
HC_INLINE bool operator<(Vec4D _vLeft, Vec4D _vRight) { return _vLeft.x < _vRight.x && _vLeft.y < _vRight.y && _vLeft.z < _vRight.z && _vLeft.w < _vRight.w; }
HC_INLINE bool operator>(Vec4D _vLeft, Vec4D _vRight) { return _vLeft.x > _vRight.x && _vLeft.y > _vRight.y && _vLeft.z > _vRight.z && _vLeft.w > _vRight.w; }
HC_INLINE bool operator<=(Vec4D _vLeft, Vec4D _vRight) { return !(_vLeft > _vRight); }
HC_INLINE bool operator>=(Vec4D _vLeft, Vec4D _vRight) { return !(_vLeft < _vRight); }
HC_INLINE bool operator!=(Vec4D _vLeft, Vec4D _vRight) { return !(_vLeft == _vRight); }
[[nodiscard]] HC_INLINE Vec4D Min(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(HC_TERNARY(_vLeft.x, _vRight.x, < ), HC_TERNARY(_vLeft.y, _vRight.y, < ), HC_TERNARY(_vLeft.z, _vRight.z, < ), HC_TERNARY(_vLeft.w, _vRight.w, < )); }
[[nodiscard]] HC_INLINE Vec4D Max(Vec4D _vLeft, Vec4D _vRight) { return Vec4D(HC_TERNARY(_vLeft.x, _vRight.x, > ), HC_TERNARY(_vLeft.y, _vRight.y, > ), HC_TERNARY(_vLeft.z, _vRight.z, > ), HC_TERNARY(_vLeft.w, _vRight.w, > )); }
[[nodiscard]] HC_INLINE Vec4D Clamp(Vec4D _vVector, Vec4D _vMin, Vec4D _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
[[nodiscard]] HC_INLINE double Sum(const Vec4D _vVector) { return _vVector.x + _vVector.y + _vVector.z + _vVector.w; }
[[nodiscard]] HC_INLINE double Dot(Vec4D _vLeft, Vec4D _vRight) { return Sum((_vLeft * _vRight).XYZ()); }
[[nodiscard]] HC_INLINE double Length(Vec4D _vVector) { return sqrt(Dot(_vVector, _vVector)); }
[[nodiscard]] HC_INLINE double LengthSquared(Vec4D _vVector) { return Dot(_vVector, _vVector); }
[[nodiscard]] HC_INLINE Vec4D Normalize(Vec4D _vVector) { return _vVector * (1.0 / Length(_vVector)); }
[[nodiscard]] HC_INLINE double AngleBetween(Vec4D _vLeft, Vec4D _vRight) { return acos(Dot(_vLeft, _vRight)); }
[[nodiscard]] HC_INLINE Vec4D Cross(Vec4D _vLeft, Vec4D _vRight) { return Vec4D((_vLeft.ZXY() * _vRight.XYZ() - _vLeft.XYZ() * _vRight.ZXY()).ZXY(), _vLeft.w); }
[[nodiscard]] HC_INLINE Vec4D Abs(Vec4D _vVector) { return Vec4D(abs(_vVector.x), abs(_vVector.y), abs(_vVector.z), abs(_vVector.w)); }

#endif