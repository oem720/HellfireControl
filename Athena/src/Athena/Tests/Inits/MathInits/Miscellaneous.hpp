#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Miscellaneous(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - Misc");
		
		_vBlockList.push_back(tbBlock);
	}
}