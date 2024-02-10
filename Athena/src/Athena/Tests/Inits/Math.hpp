#pragma once

#include <Athena/Core/TestBlock.hpp>
#include <Athena/Core/Util.hpp>

#include <Athena/Tests/Inits/MathInits/Vec2.hpp>
#include <Athena/Tests/Inits/MathInits/Vec3.hpp>
#include <Athena/Tests/Inits/MathInits/Vec4.hpp>
#include <Athena/Tests/Inits/MathInits/Matrix.hpp>
#include <Athena/Tests/Inits/MathInits/Quaternion.hpp>
#include <Athena/Tests/Inits/MathInits/Rotor.hpp>
#include <Athena/Tests/Inits/MathInits/Random.hpp>
#include <Athena/Tests/Inits/MathInits/Miscellaneous.hpp>

namespace MathTests {
	void InitTests(std::vector<TestBlock>& _vBlockList) {
		Console::Print("Generating tests for Math\n");

		//Vec2
		InitTests_Vec2(_vBlockList);

		//Vec3
		InitTests_Vec3(_vBlockList);

		//Vec4
		InitTests_Vec4(_vBlockList);

		//Matrix
		InitTests_Matrix(_vBlockList);

		//Quaternion
		InitTests_Quaternion(_vBlockList);

		//Rotor
		//InitTests_Rotor(_vBlockList);

		//Random
		InitTests_Random(_vBlockList);

		//Math
		//InitTests_Miscellaneous(_vBlockList);
	}
}