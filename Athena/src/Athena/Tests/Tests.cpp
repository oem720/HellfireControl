
#include <Athena/Tests/Tests.hpp>

#include <Athena/Core/Util.hpp>

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>
#include <HellfireControl/Math/Math.hpp>
#include <HellfireControl/Math/Random.hpp>

#include <chrono>


namespace Math {
	void InitTests(std::vector<TestBlock>& _vBlockList) {
		Console::Print("Generating tests for Math\n");

		//Vec2F/D
		{
			TestBlock tbBlock("Math Library - Vec2F");

			tbBlock.AddTest("Vec2F Equals 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(1.0f, 2.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(1.0f, 2.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 < vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 > vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 <= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(212.0f, 63.002f);

				HC_TIME_EXECUTION(bool bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 >= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);

				HC_TIME_EXECUTION(bool bRes = vec1 >= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.0f);
				Vec2F vec2(212.0f, 63.0f);

				HC_TIME_EXECUTION(bool bRes = vec1 >= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Zero", [](float& fDelta) -> const bool {
				Vec2F vec(1.0f, 2.0f);

				HC_TIME_EXECUTION(vec = ~vec, fDelta);

				return vec == Vec2F();
			});

			tbBlock.AddTest("Vec2F Negate", [](float& fDelta) -> const bool {
				Vec2F vec(1.0f, 2.0f);

				HC_TIME_EXECUTION(vec = -vec, fDelta);

				return vec == Vec2F(-1.0f, -2.0f);
			});

			

			_vBlockList.push_back(tbBlock);

			tbBlock = TestBlock("Math Library - Vec2D");
			
			//tbBlock.AddTest("Vec2D Equals 1", [](float& fDelta) -> const bool {
			//	Vec2D vec1(1.0, 2.0);
			//	Vec2D vec2(1.0, 2.0);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);
			//
			//	return bRes;
			//});
			//
			//tbBlock.AddTest("Vec2D Equals 2", [](float& fDelta) -> const bool {
			//	Vec2D vec1(1000.0, 2233.32);
			//	Vec2D vec2(1000.0, 2233.32);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);
			//
			//	return bRes;
			//});
			//
			//tbBlock.AddTest("Vec2D Equals 3", [](float& fDelta) -> const bool {
			//	Vec2D vec1(212.0, 63.002);
			//	Vec2D vec2(12321.0, 2233.32);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 == vec2, fDelta);
			//
			//	return !bRes;
			//});
			//
			//tbBlock.AddTest("Vec2D Not Equals 1", [](float& fDelta) -> const bool {
			//	Vec2D vec1(1.0, 2.0);
			//	Vec2D vec2(1.0, 2.0);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);
			//
			//	return !bRes;
			//});
			//
			//tbBlock.AddTest("Vec2D Not Equals 2", [](float& fDelta) -> const bool {
			//	Vec2D vec1(1000.0, 2233.32);
			//	Vec2D vec2(1000.0, 2233.32);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);
			//
			//	return !bRes;
			//});
			//
			//tbBlock.AddTest("Vec2D Not Equals 3", [](float& fDelta) -> const bool {
			//	Vec2D vec1(212.0, 63.002);
			//	Vec2D vec2(12321.0, 2233.32);
			//
			//	HC_TIME_EXECUTION(bool bRes = vec1 != vec2, fDelta);
			//
			//	return bRes;
			//});

			_vBlockList.push_back(tbBlock);
		}

		//Vec3F/D
		{
			//TestBlock tbBlock("Math Library - Vec3F");
			//
			//_vBlockList.push_back(tbBlock);
			//
			//tbBlock = TestBlock("Math Library - Vec3D");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//Vec4F/D
		{
			//TestBlock tbBlock("Math Library - Vec4F");
			//
			//_vBlockList.push_back(tbBlock);
			//
			//tbBlock = TestBlock("Math Library - Vec4D");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//MatrixF/D
		{
			//TestBlock tbBlock("Math Library - MatrixF");
			//
			//_vBlockList.push_back(tbBlock);
			//
			//tbBlock = TestBlock("Math Library - MatrixD");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//QuaternionF/D
		{
			//TestBlock tbBlock("Math Library - QuaternionF");
			//
			//_vBlockList.push_back(tbBlock);
			//
			//tbBlock = TestBlock("Math Library - QuaternionD");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//RotorF/D
		{
			//TestBlock tbBlock("Math Library - RotorF");
			//
			//_vBlockList.push_back(tbBlock);
			//
			//tbBlock = TestBlock("Math Library - RotorD");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//Random
		{
			//TestBlock tbBlock("Math Library - Random");
			//
			//_vBlockList.push_back(tbBlock);
		}

		//Math
		{
			//TestBlock tbBlock("Math Library - Misc");
			//
			//_vBlockList.push_back(tbBlock);
		}
	}
}