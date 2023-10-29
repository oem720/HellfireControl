
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

			//Comparison Operators
			{
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
			}

			//Arithmetic Operators
			{
				tbBlock.AddTest("Vec2F Add 1", [](float& fDelta) -> const bool {
					Vec2F vec1(562.3817f, 879.1950f);
					Vec2F vec2(729.7944f, 330.4333f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

					return vRes == Vec2F(562.3817f + 729.7944f, 879.1950f + 330.4333f);
				});

				tbBlock.AddTest("Vec2F Add 2", [](float& fDelta) -> const bool {
					Vec2F vec1(956.2237f, 331.7911f);
					Vec2F vec2(349.2213f, 312.8308f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

					return vRes == Vec2F(956.2237f + 349.2213f, 331.7911f + 312.8308f);
				});

				tbBlock.AddTest("Vec2F Add 3", [](float& fDelta) -> const bool {
					Vec2F vec1(725.3930f, 269.9619f);
					Vec2F vec2(922.0483f, 544.8846f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

					return vRes == Vec2F(725.3930f + 922.0483f, 269.9619f + 544.8846f);
				});

				tbBlock.AddTest("Vec2F Sub 1", [](float& fDelta) -> const bool {
					Vec2F vec1(949.4220f, 254.6960f);
					Vec2F vec2(952.8229f, 548.7633f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

					return vRes == Vec2F(949.4220f - 952.8229f, 254.6960f - 548.7633f);
				});

				tbBlock.AddTest("Vec2F Sub 2", [](float& fDelta) -> const bool {
					Vec2F vec1(708.4678f, 545.4393f);
					Vec2F vec2(585.3077f, 910.9493f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

					return vRes == Vec2F(708.4678f - 585.3077f, 545.4393f - 910.9493f);
				});

				tbBlock.AddTest("Vec2F Sub 3", [](float& fDelta) -> const bool {
					Vec2F vec1(513.1027f, 509.7849f);
					Vec2F vec2(868.3063f, 73.3378f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

					return vRes == Vec2F(513.1027f - 868.3063f, 509.7849f - 73.3378f);
				});

				tbBlock.AddTest("Vec2F Mul 1", [](float& fDelta) -> const bool {
					Vec2F vec1(80.2183f, 48.4900f);
					Vec2F vec2(48.6584f, 28.2959f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

					return vRes == Vec2F(80.2183f * 48.6584f, 48.4900f * 28.2959f);
				});

				tbBlock.AddTest("Vec2F Mul 2", [](float& fDelta) -> const bool {
					Vec2F vec1(36.6653f, 28.2451f);
					Vec2F vec2(4.1396f, 78.3024f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

					return vRes == Vec2F(36.6653f * 4.1396f, 28.2451f * 78.3024f);
				});

				tbBlock.AddTest("Vec2F Mul 3", [](float& fDelta) -> const bool {
					Vec2F vec1(51.6924f, 27.1861f);
					Vec2F vec2(79.7343f, 60.6889f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

					return vRes == Vec2F(51.6924f * 79.7343f, 27.1861f * 60.6889f);
				});

				tbBlock.AddTest("Vec2F Scale 1", [](float& fDelta) -> const bool {
					Vec2F vec(128.3676f, 386.5519f);
					float scale = 4.7647f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

					return vRes == Vec2F(128.3676f * 4.7647f, 386.5519f * 4.7647f);
				});

				tbBlock.AddTest("Vec2F Scale 2", [](float& fDelta) -> const bool {
					Vec2F vec(640.0216f, 599.3427f);
					float scale = 8.6124f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = scale * vec, fDelta);

					return vRes == Vec2F(640.0216f * 8.6124f, 599.3427f * 8.6124f);
				});

				tbBlock.AddTest("Vec2F Scale 3", [](float& fDelta) -> const bool {
					Vec2F vec(826.0256f, 312.1744f);
					float scale = 3.4540f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

					return vRes == Vec2F(826.0256f * 3.4540f, 312.1744f * 3.4540f);
				});

				tbBlock.AddTest("Vec2F Div 1", [](float& fDelta) -> const bool {
					Vec2F vec1(645.6976f, 133.4426f);
					Vec2F vec2(324.8063f, 246.3471f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

					return vRes == Vec2F(645.6976f / 324.8063f, 133.4426f / 246.3471f);
				});

				tbBlock.AddTest("Vec2F Div 2", [](float& fDelta) -> const bool {
					Vec2F vec1(866.2313f, 958.3398f);
					Vec2F vec2(729.4492f, 272.1197f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

					return vRes == Vec2F(866.2313f / 729.4492f, 958.3398f / 272.1197f);
				});

				tbBlock.AddTest("Vec2F Div 3", [](float& fDelta) -> const bool {
					Vec2F vec1(832.8854f, 711.4308f);
					Vec2F vec2(98.4148f, 581.0262f);
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

					return vRes == Vec2F(832.8854f / 98.4148f, 711.4308f / 581.0262f);
				});

				tbBlock.AddTest("Vec2F Scalar Div 1", [](float& fDelta) -> const bool {
					Vec2F vec(128.3676f, 386.5519f);
					float scale = 4.7647f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

					return vRes == Vec2F(128.3676f / 4.7647f, 386.5519f / 4.7647f);
				});

				tbBlock.AddTest("Vec2F Scalar Div 2", [](float& fDelta) -> const bool {
					Vec2F vec(640.0216f, 599.3427f);
					float scale = 8.6124f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = scale / vec, fDelta);

					return vRes == Vec2F(640.0216f / 8.6124f, 599.3427f / 8.6124f);
				});

				tbBlock.AddTest("Vec2F Scalar Div 3", [](float& fDelta) -> const bool {
					Vec2F vec(826.0256f, 312.1744f);
					float scale = 3.4540f;
					Vec2F vRes;

					HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

					return vRes == Vec2F(826.0256f / 3.4540f, 312.1744f / 3.4540f);
				});
			}

			//Misc Operators
			{
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
			}

			//Functions
			{
				/*tbBlock.AddTest("Vec2F Min 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Min 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Min 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Max 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Max 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Max 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Sum 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Sum 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Sum 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Dot 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Dot 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Dot 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length Squared 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length Squared 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Length Squared 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Normalize 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Normalize 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Normalize 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Angle Between 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Angle Between 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Angle Between 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Cross 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Cross 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Cross 3", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Abs 1", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Abs 2", [](float& fDelta) -> const bool {

				});

				tbBlock.AddTest("Vec2F Abs 3", [](float& fDelta) -> const bool {

				});*/
			}

			_vBlockList.push_back(tbBlock);

			tbBlock = TestBlock("Math Library - Vec2D");
			
			

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