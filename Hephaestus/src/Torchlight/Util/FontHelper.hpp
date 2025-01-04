#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <Torchlight/Util/FontTypes.hpp>

namespace FontHelper {
	float GetMinCurveY(const TTFCurve& _cCurve) {
		return _cCurve.m_p0.y < _cCurve.m_p2.y ? _cCurve.m_p0.y : _cCurve.m_p2.y;
	}

	float GetMaxCurveY(const TTFCurve& _cCurve) {
		return _cCurve.m_p0.y >= _cCurve.m_p2.y ? _cCurve.m_p0.y : _cCurve.m_p2.y;
	}

	int GetCurveMinIndex(const TTFCurve& _cCurve) {
		return _cCurve.m_p0.y < _cCurve.m_p2.y ? 0 : 2;
	}
}