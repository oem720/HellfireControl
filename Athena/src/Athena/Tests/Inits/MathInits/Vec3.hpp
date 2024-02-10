#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Vec3(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - Vec3F");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec3F Equals 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(72.7684f, 93.9137f, -80.9734f);
				Vec3F vec2(72.7684f, 93.9137f, -80.9734f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Equals 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, -38.3864f);
				Vec3F vec2(1000.0f, 2233.32f, -38.3864f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Equals 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 49.2350f);
				Vec3F vec2(12321.0f, 2233.32f, 82.9944f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Not Equals 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, -11.9128f);
				Vec3F vec2(1.0f, 2.0f, -11.9128f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Not Equals 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 99.4377f);
				Vec3F vec2(1000.0f, 2233.32f, 99.4377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Not Equals 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 5.4785f);
				Vec3F vec2(12321.0f, 2233.32f, 64.1631f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Less Than 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Less Than 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Less Than 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 99.4377f);
				Vec3F vec2(12321.0f, 2233.32f, 994.377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 99.4377f);
				Vec3F vec2(12321.0f, 2233.32f, 994.377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 16.5280f);
				Vec3F vec2(212.0f, 63.002f, 16.5280f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 16.5280f);
				Vec3F vec2(212.0f, 63.002f, 16.5280f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
				});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec3F Add 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(562.3817f, 879.1950f, -54.7428f);
				Vec3F vec2(729.7944f, 330.4333f, 98.9734f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3F Add 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(956.2237f, 331.7911f, 68.3852f);
				Vec3F vec2(349.2213f, 312.8308f, 64.1928f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3F Add 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(725.3930f, 269.9619f, 47.9971f);
				Vec3F vec2(922.0483f, 544.8846f, -32.1389f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3F Sub 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(949.4220f, 254.6960f, 95.4638f);
				Vec3F vec2(952.8229f, 548.7633f, -85.3625f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3F Sub 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(708.4678f, 545.4393f, 87.8738f);
				Vec3F vec2(585.3077f, 910.9493f, -40.6951f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3F Sub 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(513.1027f, 509.7849f, 98.1163f);
				Vec3F vec2(868.3063f, 73.3378f, 81.0108f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3F Mul 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(80.2183f, 48.4900f, 38.3640f);
				Vec3F vec2(48.6584f, 28.2959f, -4.9290f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Mul 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(36.6653f, 28.2451f, 30.5739f);
				Vec3F vec2(4.1396f, 78.3024f, -56.1665f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Mul 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(51.6924f, 27.1861f, 8.4850f);
				Vec3F vec2(79.7343f, 60.6889f, 49.8523f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Scale 1", [](float& _fDelta) -> const bool {
				Vec3F vec(128.3676f, 386.5519f, 91.3604f);
				float scale = 4.7647f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3F Scale 2", [](float& _fDelta) -> const bool {
				Vec3F vec(640.0216f, 599.3427f, 14.4820f);
				float scale = 8.6124f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3F Scale 3", [](float& _fDelta) -> const bool {
				Vec3F vec(826.0256f, 312.1744f, -94.6371f);
				float scale = 3.4540f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3F Div 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(645.6976f, 133.4426f, -13.1399f);
				Vec3F vec2(324.8063f, 246.3471f, 79.5019f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3F Div 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(866.2313f, 958.3398f, 30.8907f);
				Vec3F vec2(729.4492f, 272.1197f, 38.8574f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3F Div 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(832.8854f, 711.4308f, -21.1883f);
				Vec3F vec2(98.4148f, 581.0262f, 98.4090f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3F Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec3F vec(128.3676f, 386.5519f, 60.3248f);
				float scale = 4.7647f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
				});

			tbBlock.AddTest("Vec3F Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec3F vec(640.0216f, 599.3427f, -31.3702f);
				float scale = 8.6124f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
				});

			tbBlock.AddTest("Vec3F Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec3F vec(826.0256f, 312.1744f, 54.1705f);
				float scale = 3.4540f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
				});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec3F Zero", [](float& _fDelta) -> const bool {
				Vec3F vec(1.0f, 2.0f, 3.0f);

				HC_TIME_EXECUTION(vec = ~vec, _fDelta);

				return vec == Vec3F();
				});

			tbBlock.AddTest("Vec3F Negate", [](float& _fDelta) -> const bool {
				Vec3F vec(1.0f, 2.0f, 3.0f);

				HC_TIME_EXECUTION(vec = -vec, _fDelta);

				return vec == Vec3F(-1.0f, -2.0f, -3.0f);
				});
		}

		//Functions
		{
			tbBlock.AddTest("Vec3F Min 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(51.1165f, 42.3195f, 49.7369f);
				Vec3F vec2(39.1151f, 59.8660f, -28.4884f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3F(39.1151f, 42.3195f, -28.4884f);
				});

			tbBlock.AddTest("Vec3F Min 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(28.7146f, 41.3594f, 97.7016f);
				Vec3F vec2(76.2211f, 68.4067f, -1.3772f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3F(28.7146f, 41.3594f, -1.3772f);
				});

			tbBlock.AddTest("Vec3F Min 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(8.0429f, 40.1981f, -59.5477f);
				Vec3F vec2(16.0625f, 83.4853f, 14.7856f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3F(8.0429f, 40.1981f, -59.5477f);
				});

			tbBlock.AddTest("Vec3F Max 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(96.7911f, 64.2846f, -35.3075f);
				Vec3F vec2(30.4101f, 11.5474f, 64.8257f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3F(96.7911f, 64.2846f, 64.8257f);
				});

			tbBlock.AddTest("Vec3F Max 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(16.2844f, 32.5915f, 72.0709f);
				Vec3F vec2(45.5970f, 41.9927f, 78.8099f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3F(45.5970f, 41.9927f, 78.8099f);
				});

			tbBlock.AddTest("Vec3F Max 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(72.7684f, 93.9137f, 85.4258f);
				Vec3F vec2(30.2332f, 19.2606f, 99.2068f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3F(72.7684f, 93.9137f, 99.2068f);
				});

			//TODO: Manually calculate the Horizontal Min/Max so that we aren't literally comparing
			//against the code we're attempting to test. This is only a placeholder.

			tbBlock.AddTest("Vec3F Horizontal Min 1", [](float& _fDelta) -> const bool {
				Vec3F vec(-49.9858f, 22.1010f, 80.5901f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMin(vec), _fDelta);

				return fRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Horizontal Min 2", [](float& _fDelta) -> const bool {
				Vec3F vec(-30.6412f, 83.5648f, 91.0338f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMin(vec), _fDelta);

				return fRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Horizontal Min 3", [](float& _fDelta) -> const bool {
				Vec3F vec(60.9762f, 64.6941f, -16.5442f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMin(vec), _fDelta);

				return fRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Horizontal Max 1", [](float& _fDelta) -> const bool {
				Vec3F vec(82.9484f, -77.1554f, -74.0920f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMax(vec), _fDelta);

				return fRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Horizontal Max 2", [](float& _fDelta) -> const bool {
				Vec3F vec(80.4559f, 84.6935f, 34.1138f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMax(vec), _fDelta);

				return fRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Horizontal Max 3", [](float& _fDelta) -> const bool {
				Vec3F vec(-35.8166f, 47.5177f, -19.3538f);
				float fRes;

				HC_TIME_EXECUTION(fRes = HorizontalMax(vec), _fDelta);

				return fRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3F Sum 1", [](float& _fDelta) -> const bool {
				Vec3F vec(78.0600f, 87.2512f, 17.4745f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3F Sum 2", [](float& _fDelta) -> const bool {
				Vec3F vec(97.3376f, 78.5648f, -72.4875f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3F Sum 3", [](float& _fDelta) -> const bool {
				Vec3F vec(57.8870f, 81.7546f, -56.3297f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3F Dot 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(26.8330f, 70.8067f, 94.4725f);
				Vec3F vec2(79.1302f, 60.2868f, 38.1920f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Dot 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(86.4119f, 47.2965f, 55.8695f);
				Vec3F vec2(20.8300f, 16.3871f, -65.5612f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Dot 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(91.6068f, 54.0450f, -8.8122f);
				Vec3F vec2(30.6695f, 92.2011f, -60.2328f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Length 1", [](float& _fDelta) -> const bool {
				Vec3F vec(9.4654f, 17.3159f, -65.7723f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Length 2", [](float& _fDelta) -> const bool {
				Vec3F vec(60.8574f, 49.0449f, -73.1398f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Length 3", [](float& _fDelta) -> const bool {
				Vec3F vec(65.8412f, 59.2604f, 83.9684f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Length Squared 1", [](float& _fDelta) -> const bool {
				Vec3F vec(43.9689f, 96.0509f, 88.9848f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Length Squared 2", [](float& _fDelta) -> const bool {
				Vec3F vec(53.1229f, 66.8357f, -1.5535f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Length Squared 3", [](float& _fDelta) -> const bool {
				Vec3F vec(28.9374f, 1.0988f, 49.2252f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3F Normalize 1", [](float& _fDelta) -> const bool {
				Vec3F vec(74.2584f, 69.7548f, 41.2219f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3F Normalize 2", [](float& _fDelta) -> const bool {
				Vec3F vec(37.8081f, 90.8517f, -26.2088f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3F Normalize 3", [](float& _fDelta) -> const bool {
				Vec3F vec(52.8772f, 94.8309f, 31.6384f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3F Angle Between 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(89.6417f, 79.4191f, 22.7910f);
				Vec3F vec2(1.4510f, 0.0928f, -27.6698f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Angle Between 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(91.8041f, 90.4006f, 9.4439f);
				Vec3F vec2(6.7411f, 43.1172f, 56.0758f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Angle Between 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(69.2061f, 74.7766f, -6.6671f);
				Vec3F vec2(56.8069f, 54.0597f, -91.8969f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3F Cross 1", [](float& _fDelta) -> const bool {
				Vec3F vec1(-97.2270f, 38.6223f, -28.2738f);
				Vec3F vec2(86.0807f, 1.9667f, -94.1717f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec3F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3F Cross 2", [](float& _fDelta) -> const bool {
				Vec3F vec1(23.5460f, 38.0488f, 17.8359f);
				Vec3F vec2(-42.1373f, -70.5776f, -33.3752f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 ^ vec2, _fDelta);

				return vRes == Vec3F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3F Cross 3", [](float& _fDelta) -> const bool {
				Vec3F vec1(13.7789f, 88.7826f, -27.1393f);
				Vec3F vec2(-13.9210f, -42.339f, 54.9631f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec3F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3F Abs 1", [](float& _fDelta) -> const bool {
				Vec3F vec(96.5146f, -61.7155f, -9.8896f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3F(abs(vec.x), abs(vec.y), abs(vec.z));
				});

			tbBlock.AddTest("Vec3F Abs 2", [](float& _fDelta) -> const bool {
				Vec3F vec(1.7028f, -53.4726f, 65.2977f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3F(abs(vec.x), abs(vec.y), abs(vec.z));
				});

			tbBlock.AddTest("Vec3F Abs 3", [](float& _fDelta) -> const bool {
				Vec3F vec(-86.6360f, -7.9589f, -58.1190f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3F(abs(vec.x), abs(vec.y), abs(vec.z));
				});
		}

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - Vec3D");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec3D Equals 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(72.7684, 93.9137, -80.9734);
				Vec3D vec2(72.7684, 93.9137, -80.9734);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Equals 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, -38.3864);
				Vec3D vec2(1000.0, 2233.32, -38.3864);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Equals 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 49.2350);
				Vec3D vec2(12321.0, 2233.32, 82.9944);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Not Equals 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(1.0, 2.0, -11.9128);
				Vec3D vec2(1.0, 2.0, -11.9128);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Not Equals 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, 99.4377);
				Vec3D vec2(1000.0, 2233.32, 99.4377);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Not Equals 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 5.4785);
				Vec3D vec2(12321.0, 2233.32, 64.1631);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Less Than 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(1.0, 2.0, 3.0);
				Vec3D vec2(2.0, 3.0, 4.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Less Than 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, 54.785);
				Vec3D vec2(100.0, 233.32, 5.4785);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Less Than 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 99.4377);
				Vec3D vec2(12321.0, 2233.32, 994.377);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(1.0, 2.0, 3.0);
				Vec3D vec2(2.0, 3.0, 4.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, 54.785);
				Vec3D vec2(100.0, 233.32, 5.4785);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 99.4377);
				Vec3D vec2(12321.0, 2233.32, 994.377);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(1.0, 2.0, 3.0);
				Vec3D vec2(2.0, 3.0, 4.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, 54.785);
				Vec3D vec2(100.0, 233.32, 5.4785);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 16.5280);
				Vec3D vec2(212.0, 63.002, 16.5280);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(1.0, 2.0, 3.0);
				Vec3D vec2(2.0, 3.0, 4.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return !bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(1000.0, 2233.32, 54.785);
				Vec3D vec2(100.0, 233.32, 5.4785);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
				});

			tbBlock.AddTest("Vec3D Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(212.0, 63.002, 16.5280);
				Vec3D vec2(212.0, 63.002, 16.5280);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
				});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec3D Add 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(562.3817, 879.1950, -54.7428);
				Vec3D vec2(729.7944, 330.4333, 98.9734);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3D Add 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(956.2237, 331.7911, 68.3852);
				Vec3D vec2(349.2213, 312.8308, 64.1928);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3D Add 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(725.3930, 269.9619, 47.9971);
				Vec3D vec2(922.0483, 544.8846, -32.1389);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec3D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
				});

			tbBlock.AddTest("Vec3D Sub 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(949.4220, 254.6960, 95.4638);
				Vec3D vec2(952.8229, 548.7633, -85.3625);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3D Sub 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(708.4678, 545.4393, 87.8738);
				Vec3D vec2(585.3077, 910.9493, -40.6951);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3D Sub 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(513.1027, 509.7849, 98.1163);
				Vec3D vec2(868.3063, 73.3378, 81.0108);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec3D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
				});

			tbBlock.AddTest("Vec3D Mul 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(80.2183, 48.4900, 38.3640);
				Vec3D vec2(48.6584, 28.2959, -4.9290);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Mul 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(36.6653, 28.2451, 30.5739);
				Vec3D vec2(4.1396, 78.3024, -56.1665);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Mul 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(51.6924, 27.1861, 8.4850);
				Vec3D vec2(79.7343, 60.6889, 49.8523);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec3D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Scale 1", [](float& _fDelta) -> const bool {
				Vec3D vec(128.3676, 386.5519, 91.3604);
				double scale = 4.7647;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec3D(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3D Scale 2", [](float& _fDelta) -> const bool {
				Vec3D vec(640.0216, 599.3427, 14.4820);
				double scale = 8.6124;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);

				return vRes == Vec3D(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3D Scale 3", [](float& _fDelta) -> const bool {
				Vec3D vec(826.0256, 312.1744, -94.6371);
				double scale = 3.4540;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec3D(vec.x * scale, vec.y * scale, vec.z * scale);
				});

			tbBlock.AddTest("Vec3D Div 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(645.6976, 133.4426, -13.1399);
				Vec3D vec2(324.8063, 246.3471, 79.5019);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3D Div 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(866.2313, 958.3398, 30.8907);
				Vec3D vec2(729.4492, 272.1197, 38.8574);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3D Div 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(832.8854, 711.4308, -21.1883);
				Vec3D vec2(98.4148, 581.0262, 98.4090);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec3D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
				});

			tbBlock.AddTest("Vec3D Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec3D vec(128.3676, 386.5519, 60.3248);
				double scale = 4.7647;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec3D(vec.x / scale, vec.y / scale, vec.z / scale);
				});

			tbBlock.AddTest("Vec3D Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec3D vec(640.0216, 599.3427, -31.3702);
				double scale = 8.6124;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);

				return vRes == Vec3D(vec.x / scale, vec.y / scale, vec.z / scale);
				});

			tbBlock.AddTest("Vec3D Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec3D vec(826.0256, 312.1744, 54.1705);
				double scale = 3.4540;
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec3D(vec.x / scale, vec.y / scale, vec.z / scale);
				});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec3D Zero", [](float& _fDelta) -> const bool {
				Vec3D vec(1.0, 2.0, 3.0);

				HC_TIME_EXECUTION(vec = ~vec, _fDelta);

				return vec == Vec3D();
				});

			tbBlock.AddTest("Vec3D Negate", [](float& _fDelta) -> const bool {
				Vec3D vec(1.0, 2.0, 3.0);

				HC_TIME_EXECUTION(vec = -vec, _fDelta);

				return vec == Vec3D(-1.0, -2.0, -3.0);
				});
		}

		//Functions
		{
			tbBlock.AddTest("Vec3D Min 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(51.1165, 42.3195, 49.7369);
				Vec3D vec2(39.1151, 59.8660, -28.4884);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3D(39.1151, 42.3195, -28.4884);
				});

			tbBlock.AddTest("Vec3D Min 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(28.7146, 41.3594, 97.7016);
				Vec3D vec2(76.2211, 68.4067, -1.3772);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3D(28.7146, 41.3594, -1.3772);
				});

			tbBlock.AddTest("Vec3D Min 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(8.0429, 40.1981, -59.5477);
				Vec3D vec2(16.0625, 83.4853, 14.7856);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec3D(8.0429, 40.1981, -59.5477);
				});

			tbBlock.AddTest("Vec3D Max 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(96.7911, 64.2846, -35.3075);
				Vec3D vec2(30.4101, 11.5474, 64.8257);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3D(96.7911, 64.2846, 64.8257);
				});

			tbBlock.AddTest("Vec3D Max 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(16.2844, 32.5915, 72.0709);
				Vec3D vec2(45.5970, 41.9927, 78.8099);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3D(45.5970, 41.9927, 78.8099);
				});

			tbBlock.AddTest("Vec3D Max 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(72.7684, 93.9137, 85.4258);
				Vec3D vec2(30.2332, 19.2606, 99.2068);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec3D(72.7684, 93.9137, 99.2068);
				});

			//TODO: Manually calculate the Horizontal Min/Max so that we aren't literally comparing
			//against the code we're attempting to test. This is only a placeholder.

			tbBlock.AddTest("Vec3D Horizontal Min 1", [](float& _fDelta) -> const bool {
				Vec3D vec(-49.9858, 22.1010, 80.5901);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMin(vec), _fDelta);

				return dRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Horizontal Min 2", [](float& _fDelta) -> const bool {
				Vec3D vec(-30.6412, 83.5648, 91.0338);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMin(vec), _fDelta);

				return dRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Horizontal Min 3", [](float& _fDelta) -> const bool {
				Vec3D vec(60.9762, 64.6941, -16.5442);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMin(vec), _fDelta);

				return dRes == Min(Min(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Horizontal Max 1", [](float& _fDelta) -> const bool {
				Vec3D vec(82.9484, -77.1554, -74.0920);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMax(vec), _fDelta);

				return dRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Horizontal Max 2", [](float& _fDelta) -> const bool {
				Vec3D vec(80.4559, 84.6935, 34.1138);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMax(vec), _fDelta);

				return dRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Horizontal Max 3", [](float& _fDelta) -> const bool {
				Vec3D vec(-35.8166, 47.5177, -19.3538);
				double dRes;

				HC_TIME_EXECUTION(dRes = HorizontalMax(vec), _fDelta);

				return dRes == Max(Max(vec, vec.YXZ()), vec.ZXY()).x;
				});

			tbBlock.AddTest("Vec3D Sum 1", [](float& _fDelta) -> const bool {
				Vec3D vec(78.0600, 87.2512, 17.4745);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3D Sum 2", [](float& _fDelta) -> const bool {
				Vec3D vec(97.3376, 78.5648, -72.4875);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3D Sum 3", [](float& _fDelta) -> const bool {
				Vec3D vec(57.8870, 81.7546, -56.3297);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z;
				});

			tbBlock.AddTest("Vec3D Dot 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(26.8330, 70.8067, 94.4725);
				Vec3D vec2(79.1302, 60.2868, 38.1920);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Dot 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(86.4119, 47.2965, 55.8695);
				Vec3D vec2(20.8300, 16.3871, -65.5612);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Dot 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(91.6068, 54.0450, -8.8122);
				Vec3D vec2(30.6695, 92.2011, -60.2328);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Length 1", [](float& _fDelta) -> const bool {
				Vec3D vec(9.4654, 17.3159, -65.7723);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Length 2", [](float& _fDelta) -> const bool {
				Vec3D vec(60.8574, 49.0449, -73.1398);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Length 3", [](float& _fDelta) -> const bool {
				Vec3D vec(65.8412, 59.2604, 83.9684);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Length Squared 1", [](float& _fDelta) -> const bool {
				Vec3D vec(43.9689, 96.0509, 88.9848);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Length Squared 2", [](float& _fDelta) -> const bool {
				Vec3D vec(53.1229, 66.8357, -1.5535);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Length Squared 3", [](float& _fDelta) -> const bool {
				Vec3D vec(28.9374, 1.0988, 49.2252);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				});

			tbBlock.AddTest("Vec3D Normalize 1", [](float& _fDelta) -> const bool {
				Vec3D vec(74.2584, 69.7548, 41.2219);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3D Normalize 2", [](float& _fDelta) -> const bool {
				Vec3D vec(37.8081, 90.8517, -26.2088);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3D Normalize 3", [](float& _fDelta) -> const bool {
				Vec3D vec(52.8772, 94.8309, 31.6384);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
				});

			tbBlock.AddTest("Vec3D Angle Between 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(89.6417, 79.4191, 22.7910);
				Vec3D vec2(1.4510, 0.0928, -27.6698);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Angle Between 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(91.8041, 90.4006, 9.4439);
				Vec3D vec2(6.7411, 43.1172, 56.0758);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Angle Between 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(69.2061, 74.7766, -6.6671);
				Vec3D vec2(56.8069, 54.0597, -91.8969);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
				});

			tbBlock.AddTest("Vec3D Cross 1", [](float& _fDelta) -> const bool {
				Vec3D vec1(-97.2270, 38.6223, -28.2738);
				Vec3D vec2(86.0807, 1.9667, -94.1717);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec3D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3D Cross 2", [](float& _fDelta) -> const bool {
				Vec3D vec1(23.5460, 38.0488, 17.8359);
				Vec3D vec2(-42.1373, -70.5776, -33.3752);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = vec1 ^ vec2, _fDelta);

				return vRes == Vec3D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3D Cross 3", [](float& _fDelta) -> const bool {
				Vec3D vec1(13.7789, 88.7826, -27.1393);
				Vec3D vec2(-13.9210, -42.339, 54.9631);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec3D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
				});

			tbBlock.AddTest("Vec3D Abs 1", [](float& _fDelta) -> const bool {
				Vec3D vec(96.5146, -61.7155, -9.8896);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3D(abs(vec.x), abs(vec.y), abs(vec.z));
				});

			tbBlock.AddTest("Vec3D Abs 2", [](float& _fDelta) -> const bool {
				Vec3D vec(1.7028, -53.4726, 65.2977);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3D(abs(vec.x), abs(vec.y), abs(vec.z));
				});

			tbBlock.AddTest("Vec3D Abs 3", [](float& _fDelta) -> const bool {
				Vec3D vec(-86.6360, -7.9589, -58.1190);
				Vec3D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec3D(abs(vec.x), abs(vec.y), abs(vec.z));
				});
		}

		_vBlockList.push_back(tbBlock);
	}
}