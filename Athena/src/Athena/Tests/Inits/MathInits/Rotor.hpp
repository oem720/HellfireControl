#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Rotor(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - RotorF");
		
		_vBlockList.push_back(tbBlock);
		
		tbBlock = TestBlock("Math Library - RotorD");
		
		_vBlockList.push_back(tbBlock);
	}
}