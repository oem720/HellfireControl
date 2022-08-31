#pragma once

#include "HCVector.h"

struct MatrixF {
	Vec4F m_vRows[4];

	HC_INLINE MatrixF() {};
	HC_INLINE MatrixF(Vec4F _vRow1, Vec4F _vRow2, Vec4F _vRow3, Vec4F _vRow4) { m_vRows[0] = _vRow1; m_vRows[1] = _vRow2; m_vRows[2] = _vRow3; m_vRows[3] = _vRow4; }
	HC_INLINE MatrixF(Vec4F* _vRows) { m_vRows[0] = _vRows[0]; m_vRows[1] = _vRows[1]; m_vRows[2] = _vRows[2]; m_vRows[3] = _vRows[3]; }

};

struct MatrixD {
	Vec4D m_vRows[4];


};

struct MatrixI {
	Vec4I m_vRows[4];


};

