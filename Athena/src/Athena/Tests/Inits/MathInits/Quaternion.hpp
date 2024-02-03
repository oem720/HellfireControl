#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Quaternion(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - QuaternionF");

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - QuaternionD");

		_vBlockList.push_back(tbBlock);
	}
}