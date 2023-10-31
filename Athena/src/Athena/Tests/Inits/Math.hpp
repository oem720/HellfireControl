#pragma once

#include <Athena/Core/TestBlock.hpp>
#include <Athena/Core/Util.hpp>

#include <HellfireControl/Math/Math.hpp>
#include <HellfireControl/Math/Random.hpp>

namespace Math {
	void InitTests(std::vector<TestBlock>& _vBlockList) {
		Console::Print("Generating tests for Math\n");

		TestBlock tbBlock;

		//Vec2F/D
#pragma region Vec2
		tbBlock = TestBlock("Math Library - Vec2F");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec2F Equals 1", [](float& fDelta) -> const bool {
				Vec2F vec1(72.7684f, 93.9137f);
				Vec2F vec2(72.7684f, 93.9137f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(1.0f, 2.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(212.0f, 63.002f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.0f);
				Vec2F vec2(212.0f, 63.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

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

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Add 2", [](float& fDelta) -> const bool {
				Vec2F vec1(956.2237f, 331.7911f);
				Vec2F vec2(349.2213f, 312.8308f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Add 3", [](float& fDelta) -> const bool {
				Vec2F vec1(725.3930f, 269.9619f);
				Vec2F vec2(922.0483f, 544.8846f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 1", [](float& fDelta) -> const bool {
				Vec2F vec1(949.4220f, 254.6960f);
				Vec2F vec2(952.8229f, 548.7633f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 2", [](float& fDelta) -> const bool {
				Vec2F vec1(708.4678f, 545.4393f);
				Vec2F vec2(585.3077f, 910.9493f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 3", [](float& fDelta) -> const bool {
				Vec2F vec1(513.1027f, 509.7849f);
				Vec2F vec2(868.3063f, 73.3378f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 1", [](float& fDelta) -> const bool {
				Vec2F vec1(80.2183f, 48.4900f);
				Vec2F vec2(48.6584f, 28.2959f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 2", [](float& fDelta) -> const bool {
				Vec2F vec1(36.6653f, 28.2451f);
				Vec2F vec2(4.1396f, 78.3024f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 3", [](float& fDelta) -> const bool {
				Vec2F vec1(51.6924f, 27.1861f);
				Vec2F vec2(79.7343f, 60.6889f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Scale 1", [](float& fDelta) -> const bool {
				Vec2F vec(128.3676f, 386.5519f);
				float scale = 4.7647f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Scale 2", [](float& fDelta) -> const bool {
				Vec2F vec(640.0216f, 599.3427f);
				float scale = 8.6124f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Scale 3", [](float& fDelta) -> const bool {
				Vec2F vec(826.0256f, 312.1744f);
				float scale = 3.4540f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Div 1", [](float& fDelta) -> const bool {
				Vec2F vec1(645.6976f, 133.4426f);
				Vec2F vec2(324.8063f, 246.3471f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Div 2", [](float& fDelta) -> const bool {
				Vec2F vec1(866.2313f, 958.3398f);
				Vec2F vec2(729.4492f, 272.1197f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Div 3", [](float& fDelta) -> const bool {
				Vec2F vec1(832.8854f, 711.4308f);
				Vec2F vec2(98.4148f, 581.0262f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Scalar Div 1", [](float& fDelta) -> const bool {
				Vec2F vec(128.3676f, 386.5519f);
				float scale = 4.7647f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2F Scalar Div 2", [](float& fDelta) -> const bool {
				Vec2F vec(640.0216f, 599.3427f);
				float scale = 8.6124f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2F Scalar Div 3", [](float& fDelta) -> const bool {
				Vec2F vec(826.0256f, 312.1744f);
				float scale = 3.4540f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
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
			tbBlock.AddTest("Vec2F Min 1", [](float& fDelta) -> const bool {
				Vec2F vec1(51.1165f, 42.3195f);
				Vec2F vec2(39.1151f, 59.8660f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2F(39.1151f, 42.3195f);
			});

			tbBlock.AddTest("Vec2F Min 2", [](float& fDelta) -> const bool {
				Vec2F vec1(28.7146f, 41.3594f);
				Vec2F vec2(76.2211f, 68.4067f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2F(28.7146f, 41.3594f);
			});

			tbBlock.AddTest("Vec2F Min 3", [](float& fDelta) -> const bool {
				Vec2F vec1(8.0429f, 40.1981f);
				Vec2F vec2(16.0625f, 83.4853f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2F(8.0429f, 40.1981f);
			});

			tbBlock.AddTest("Vec2F Max 1", [](float& fDelta) -> const bool {
				Vec2F vec1(96.7911f, 64.2846f);
				Vec2F vec2(30.4101f, 11.5474f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2F(96.7911f, 64.2846f);
			});

			tbBlock.AddTest("Vec2F Max 2", [](float& fDelta) -> const bool {
				Vec2F vec1(16.2844f, 32.5915f);
				Vec2F vec2(45.5970f, 41.9927f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2F(45.5970f, 41.9927f);
			});

			tbBlock.AddTest("Vec2F Max 3", [](float& fDelta) -> const bool {
				Vec2F vec1(72.7684f, 93.9137f);
				Vec2F vec2(30.2332f, 19.2606f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2F(72.7684f, 93.9137f);
			});

			tbBlock.AddTest("Vec2F Sum 1", [](float& fDelta) -> const bool {
				Vec2F vec(78.0600f, 87.2512f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Sum 2", [](float& fDelta) -> const bool {
				Vec2F vec(97.3376f, 78.5648f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Sum 3", [](float& fDelta) -> const bool {
				Vec2F vec(57.8870f, 81.7546f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Dot 1", [](float& fDelta) -> const bool {
				Vec2F vec1(26.8330f, 70.8067f);
				Vec2F vec2(79.1302f, 60.2868f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Dot 2", [](float& fDelta) -> const bool {
				Vec2F vec1(86.4119f, 47.2965f);
				Vec2F vec2(20.8300f, 16.3871f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Dot 3", [](float& fDelta) -> const bool {
				Vec2F vec1(91.6068f, 54.0450f);
				Vec2F vec2(30.6695f, 92.2011f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Length 1", [](float& fDelta) -> const bool {
				Vec2F vec(9.4654f, 17.3159f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length 2", [](float& fDelta) -> const bool {
				Vec2F vec(60.8574f, 49.0449f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length 3", [](float& fDelta) -> const bool {
				Vec2F vec(65.8412f, 59.2604f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 1", [](float& fDelta) -> const bool {
				Vec2F vec(43.9689f, 96.0509f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 2", [](float& fDelta) -> const bool {
				Vec2F vec(53.1229f, 66.8357f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 3", [](float& fDelta) -> const bool {
				Vec2F vec(28.9374f, 1.0988f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Normalize 1", [](float& fDelta) -> const bool {
				Vec2F vec(74.2584f, 69.7548f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Normalize 2", [](float& fDelta) -> const bool {
				Vec2F vec(37.8081f, 90.8517f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Normalize 3", [](float& fDelta) -> const bool {
				Vec2F vec(52.8772f, 94.8309f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Angle Between 1", [](float& fDelta) -> const bool {
				Vec2F vec1(89.6417f, 79.4191f);
				Vec2F vec2(1.4510f, 0.0928f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Angle Between 2", [](float& fDelta) -> const bool {
				Vec2F vec1(91.8041f, 90.4006f);
				Vec2F vec2(6.7411f, 43.1172f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Angle Between 3", [](float& fDelta) -> const bool {
				Vec2F vec1(69.2061f, 74.7766f);
				Vec2F vec2(56.8069f, 54.0597f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Cross 1", [](float& fDelta) -> const bool {
				Vec2F vec1(-97.2270f, 38.6223f);
				Vec2F vec2(86.0807f, 1.9667f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Cross 2", [](float& fDelta) -> const bool {
				Vec2F vec1(23.5460f, 38.0488f);
				Vec2F vec2(-42.1373f, -70.5776f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Cross 3", [](float& fDelta) -> const bool {
				Vec2F vec1(13.7789f, 88.7826f);
				Vec2F vec2(-13.9210f, -42.339f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Abs 1", [](float& fDelta) -> const bool {
				Vec2F vec(96.5146f, -61.7155f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2F Abs 2", [](float& fDelta) -> const bool {
				Vec2F vec(1.7028f, -53.4726f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2F Abs 3", [](float& fDelta) -> const bool {
				Vec2F vec(-86.6360f, -7.9589f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});
		}

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - Vec2D");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec2D Equals 1", [](float& fDelta) -> const bool {
				Vec2D vec1(72.7684, 93.9137);
				Vec2D vec2(72.7684, 93.9137);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Equals 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(1000.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Equals 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 1", [](float& fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(1.0, 2.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(1000.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 1", [](float& fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 1", [](float& fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(212.0, 63.002);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec2D vec1(212.0, 63.0);
				Vec2D vec2(212.0, 63.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec2D Add 1", [](float& fDelta) -> const bool {
				Vec2D vec1(562.3817, 879.1950);
				Vec2D vec2(729.7944, 330.4333);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Add 2", [](float& fDelta) -> const bool {
				Vec2D vec1(956.2237, 331.7911);
				Vec2D vec2(349.2213, 312.8308);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Add 3", [](float& fDelta) -> const bool {
				Vec2D vec1(725.3930, 269.9619);
				Vec2D vec2(922.0483, 544.8846);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 1", [](float& fDelta) -> const bool {
				Vec2D vec1(949.4220, 254.6960);
				Vec2D vec2(952.8229, 548.7633);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 2", [](float& fDelta) -> const bool {
				Vec2D vec1(708.4678, 545.4393);
				Vec2D vec2(585.3077, 910.9493);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 3", [](float& fDelta) -> const bool {
				Vec2D vec1(513.1027, 509.7849);
				Vec2D vec2(868.3063, 73.3378);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 1", [](float& fDelta) -> const bool {
				Vec2D vec1(80.2183, 48.4900);
				Vec2D vec2(48.6584, 28.2959);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 2", [](float& fDelta) -> const bool {
				Vec2D vec1(36.6653, 28.2451);
				Vec2D vec2(4.1396, 78.3024);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 3", [](float& fDelta) -> const bool {
				Vec2D vec1(51.6924, 27.1861);
				Vec2D vec2(79.7343, 60.6889);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Scale 1", [](float& fDelta) -> const bool {
				Vec2D vec(128.3676, 386.5519);
				double scale = 4.7647;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Scale 2", [](float& fDelta) -> const bool {
				Vec2D vec(640.0216, 599.3427);
				double scale = 8.6124;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Scale 3", [](float& fDelta) -> const bool {
				Vec2D vec(826.0256, 312.1744);
				double scale = 3.4540;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Div 1", [](float& fDelta) -> const bool {
				Vec2D vec1(645.6976, 133.4426);
				Vec2D vec2(324.8063, 246.3471);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Div 2", [](float& fDelta) -> const bool {
				Vec2D vec1(866.2313, 958.3398);
				Vec2D vec2(729.4492, 272.1197);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Div 3", [](float& fDelta) -> const bool {
				Vec2D vec1(832.8854, 711.4308);
				Vec2D vec2(98.4148, 581.0262);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Scalar Div 1", [](float& fDelta) -> const bool {
				Vec2D vec(128.3676, 386.5519);
				double scale = 4.7647;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2D Scalar Div 2", [](float& fDelta) -> const bool {
				Vec2D vec(640.0216, 599.3427);
				double scale = 8.6124;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2D Scalar Div 3", [](float& fDelta) -> const bool {
				Vec2D vec(826.0256, 312.1744);
				double scale = 3.4540;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec2D Zero", [](float& fDelta) -> const bool {
				Vec2D vec(1.0, 2.0);

				HC_TIME_EXECUTION(vec = ~vec, fDelta);

				return vec == Vec2D();
			});

			tbBlock.AddTest("Vec2D Negate", [](float& fDelta) -> const bool {
				Vec2D vec(1.0, 2.0);

				HC_TIME_EXECUTION(vec = -vec, fDelta);

				return vec == Vec2D(-1.0, -2.0);
			});
		}

		//Functions
		{
			tbBlock.AddTest("Vec2D Min 1", [](float& fDelta) -> const bool {
				Vec2D vec1(51.1165, 42.3195);
				Vec2D vec2(39.1151, 59.8660);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2D(39.1151, 42.3195);
			});

			tbBlock.AddTest("Vec2D Min 2", [](float& fDelta) -> const bool {
				Vec2D vec1(28.7146, 41.3594);
				Vec2D vec2(76.2211, 68.4067);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2D(28.7146, 41.3594);
			});

			tbBlock.AddTest("Vec2D Min 3", [](float& fDelta) -> const bool {
				Vec2D vec1(8.0429, 40.1981);
				Vec2D vec2(16.0625, 83.4853);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);

				return vRes == Vec2D(8.0429, 40.1981);
			});

			tbBlock.AddTest("Vec2D Max 1", [](float& fDelta) -> const bool {
				Vec2D vec1(96.7911, 64.2846);
				Vec2D vec2(30.4101, 11.5474);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2D(96.7911, 64.2846);
			});

			tbBlock.AddTest("Vec2D Max 2", [](float& fDelta) -> const bool {
				Vec2D vec1(16.2844, 32.5915);
				Vec2D vec2(45.5970, 41.9927);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2D(45.5970, 41.9927);
			});

			tbBlock.AddTest("Vec2D Max 3", [](float& fDelta) -> const bool {
				Vec2D vec1(72.7684, 93.9137);
				Vec2D vec2(30.2332, 19.2606);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);

				return vRes == Vec2D(72.7684, 93.9137);
			});

			tbBlock.AddTest("Vec2D Sum 1", [](float& fDelta) -> const bool {
				Vec2D vec(78.0600, 87.2512);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Sum 2", [](float& fDelta) -> const bool {
				Vec2D vec(97.3376, 78.5648);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Sum 3", [](float& fDelta) -> const bool {
				Vec2D vec(57.8870, 81.7546);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Dot 1", [](float& fDelta) -> const bool {
				Vec2D vec1(26.8330, 70.8067);
				Vec2D vec2(79.1302, 60.2868);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Dot 2", [](float& fDelta) -> const bool {
				Vec2D vec1(86.4119, 47.2965);
				Vec2D vec2(20.8300, 16.3871);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Dot 3", [](float& fDelta) -> const bool {
				Vec2D vec1(91.6068, 54.0450);
				Vec2D vec2(30.6695, 92.2011);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Length 1", [](float& fDelta) -> const bool {
				Vec2D vec(9.4654, 17.3159);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length 2", [](float& fDelta) -> const bool {
				Vec2D vec(60.8574, 49.0449);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length 3", [](float& fDelta) -> const bool {
				Vec2D vec(65.8412, 59.2604);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 1", [](float& fDelta) -> const bool {
				Vec2D vec(43.9689, 96.0509);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 2", [](float& fDelta) -> const bool {
				Vec2D vec(53.1229, 66.8357);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 3", [](float& fDelta) -> const bool {
				Vec2D vec(28.9374, 1.0988);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Normalize 1", [](float& fDelta) -> const bool {
				Vec2D vec(74.2584, 69.7548);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Normalize 2", [](float& fDelta) -> const bool {
				Vec2D vec(37.8081, 90.8517);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Normalize 3", [](float& fDelta) -> const bool {
				Vec2D vec(52.8772, 94.8309);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Angle Between 1", [](float& fDelta) -> const bool {
				Vec2D vec1(89.6417, 79.4191);
				Vec2D vec2(1.4510, 0.0928);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Angle Between 2", [](float& fDelta) -> const bool {
				Vec2D vec1(91.8041, 90.4006);
				Vec2D vec2(6.7411, 43.1172);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Angle Between 3", [](float& fDelta) -> const bool {
				Vec2D vec1(69.2061, 74.7766);
				Vec2D vec2(56.8069, 54.0597);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Cross 1", [](float& fDelta) -> const bool {
				Vec2D vec1(-97.2270, 38.6223);
				Vec2D vec2(86.0807, 1.9667);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Cross 2", [](float& fDelta) -> const bool {
				Vec2D vec1(23.5460, 38.0488);
				Vec2D vec2(-42.1373, -70.5776);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Cross 3", [](float& fDelta) -> const bool {
				Vec2D vec1(13.7789, 88.7826);
				Vec2D vec2(-13.9210, -42.339);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Abs 1", [](float& fDelta) -> const bool {
				Vec2D vec(96.5146, -61.7155);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2D(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2D Abs 2", [](float& fDelta) -> const bool {
				Vec2D vec(1.7028, -53.4726);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2D(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2D Abs 3", [](float& fDelta) -> const bool {
				Vec2D vec(-86.6360, -7.9589);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);

				return vRes == Vec2D(abs(vec.x), abs(vec.y));
			});
		}

		_vBlockList.push_back(tbBlock);
#pragma endregion

		//Vec3F/D
#pragma region Vec3
		tbBlock = TestBlock("Math Library - Vec3F");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec3F Equals 1", [](float& fDelta) -> const bool {
				Vec3F vec1(72.7684f, 93.9137f, -80.9734f);
				Vec3F vec2(72.7684f, 93.9137f, -80.9734f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Equals 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, -38.3864f);
				Vec3F vec2(1000.0f, 2233.32f, -38.3864f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Equals 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 49.2350f);
				Vec3F vec2(12321.0f, 2233.32f, 82.9944f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Not Equals 1", [](float& fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, -11.9128f);
				Vec3F vec2(1.0f, 2.0f, -11.9128f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Not Equals 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 99.4377f);
				Vec3F vec2(1000.0f, 2233.32f, 99.4377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Not Equals 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 5.4785f);
				Vec3F vec2(12321.0f, 2233.32f, 64.1631f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Less Than 1", [](float& fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Less Than 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Less Than 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 99.4377f);
				Vec3F vec2(12321.0f, 2233.32f, 994.377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than 1", [](float& fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 99.4377f);
				Vec3F vec2(12321.0f, 2233.32f, 994.377f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Less Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Less Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Less Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 16.5280f);
				Vec3F vec2(212.0f, 63.002f, 16.5280f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 1", [](float& fDelta) -> const bool {
				Vec3F vec1(1.0f, 2.0f, 3.0f);
				Vec3F vec2(2.0f, 3.0f, 4.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 2", [](float& fDelta) -> const bool {
				Vec3F vec1(1000.0f, 2233.32f, 54.785f);
				Vec3F vec2(100.0f, 233.32f, 5.4785f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec3F Greater Than Or Equal 3", [](float& fDelta) -> const bool {
				Vec3F vec1(212.0f, 63.002f, 16.5280f);
				Vec3F vec2(212.0f, 63.002f, 16.5280f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, fDelta);

				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec3F Add 1", [](float& fDelta) -> const bool {
				Vec3F vec1(562.3817f, 879.1950f, -54.7428f);
				Vec3F vec2(729.7944f, 330.4333f, 98.9734f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
			});

			tbBlock.AddTest("Vec3F Add 2", [](float& fDelta) -> const bool {
				Vec3F vec1(956.2237f, 331.7911f, 68.3852f);
				Vec3F vec2(349.2213f, 312.8308f, 64.1928f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
			});

			tbBlock.AddTest("Vec3F Add 3", [](float& fDelta) -> const bool {
				Vec3F vec1(725.3930f, 269.9619f, 47.9971f);
				Vec3F vec2(922.0483f, 544.8846f, -32.1389f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, fDelta);

				return vRes == Vec3F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
			});

			tbBlock.AddTest("Vec3F Sub 1", [](float& fDelta) -> const bool {
				Vec3F vec1(949.4220f, 254.6960f, 95.4638f);
				Vec3F vec2(952.8229f, 548.7633f, -85.3625f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
			});

			tbBlock.AddTest("Vec3F Sub 2", [](float& fDelta) -> const bool {
				Vec3F vec1(708.4678f, 545.4393f, 87.8738f);
				Vec3F vec2(585.3077f, 910.9493f, -40.6951f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
			});

			tbBlock.AddTest("Vec3F Sub 3", [](float& fDelta) -> const bool {
				Vec3F vec1(513.1027f, 509.7849f, 98.1163f);
				Vec3F vec2(868.3063f, 73.3378f, 81.0108f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, fDelta);

				return vRes == Vec3F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
			});

			tbBlock.AddTest("Vec3F Mul 1", [](float& fDelta) -> const bool {
				Vec3F vec1(80.2183f, 48.4900f, 38.3640f);
				Vec3F vec2(48.6584f, 28.2959f, -4.9290f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
			});

			tbBlock.AddTest("Vec3F Mul 2", [](float& fDelta) -> const bool {
				Vec3F vec1(36.6653f, 28.2451f, 30.5739f);
				Vec3F vec2(4.1396f, 78.3024f, -56.1665f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
			});

			tbBlock.AddTest("Vec3F Mul 3", [](float& fDelta) -> const bool {
				Vec3F vec1(51.6924f, 27.1861f, 8.4850f);
				Vec3F vec2(79.7343f, 60.6889f, 49.8523f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, fDelta);

				return vRes == Vec3F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
			});

			tbBlock.AddTest("Vec3F Scale 1", [](float& fDelta) -> const bool {
				Vec3F vec(128.3676f, 386.5519f, 91.3604f);
				float scale = 4.7647f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
			});

			tbBlock.AddTest("Vec3F Scale 2", [](float& fDelta) -> const bool {
				Vec3F vec(640.0216f, 599.3427f, 14.4820f);
				float scale = 8.6124f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
			});

			tbBlock.AddTest("Vec3F Scale 3", [](float& fDelta) -> const bool {
				Vec3F vec(826.0256f, 312.1744f, -94.6371f);
				float scale = 3.4540f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, fDelta);

				return vRes == Vec3F(vec.x * scale, vec.y * scale, vec.z * scale);
			});

			tbBlock.AddTest("Vec3F Div 1", [](float& fDelta) -> const bool {
				Vec3F vec1(645.6976f, 133.4426f, -13.1399f);
				Vec3F vec2(324.8063f, 246.3471f, 79.5019f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
			});

			tbBlock.AddTest("Vec3F Div 2", [](float& fDelta) -> const bool {
				Vec3F vec1(866.2313f, 958.3398f, 30.8907f);
				Vec3F vec2(729.4492f, 272.1197f, 38.8574f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
			});

			tbBlock.AddTest("Vec3F Div 3", [](float& fDelta) -> const bool {
				Vec3F vec1(832.8854f, 711.4308f, -21.1883f);
				Vec3F vec2(98.4148f, 581.0262f, 98.4090f);
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, fDelta);

				return vRes == Vec3F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
			});

			tbBlock.AddTest("Vec3F Scalar Div 1", [](float& fDelta) -> const bool {
				Vec3F vec(128.3676f, 386.5519f, 60.3248f);
				float scale = 4.7647f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
			});

			tbBlock.AddTest("Vec3F Scalar Div 2", [](float& fDelta) -> const bool {
				Vec3F vec(640.0216f, 599.3427f, -31.3702f);
				float scale = 8.6124f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
			});

			tbBlock.AddTest("Vec3F Scalar Div 3", [](float& fDelta) -> const bool {
				Vec3F vec(826.0256f, 312.1744f, 54.1705f);
				float scale = 3.4540f;
				Vec3F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, fDelta);

				return vRes == Vec3F(vec.x / scale, vec.y / scale, vec.z / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec3F Zero", [](float& fDelta) -> const bool {
				Vec3F vec(1.0f, 2.0f, 3.0f);

				HC_TIME_EXECUTION(vec = ~vec, fDelta);

				return vec == Vec3F();
			});

			tbBlock.AddTest("Vec3F Negate", [](float& fDelta) -> const bool {
				Vec3F vec(1.0f, 2.0f, 3.0f);

				HC_TIME_EXECUTION(vec = -vec, fDelta);

				return vec == Vec3F(-1.0f, -2.0f, -3.0f);
			});
		}

		//Functions
		{
			//tbBlock.AddTest("Vec3F Min 1", [](float& fDelta) -> const bool {
			//	Vec3F vec1(51.1165f, 42.3195f);
			//	Vec3F vec2(39.1151f, 59.8660f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(39.1151f, 42.3195f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Min 2", [](float& fDelta) -> const bool {
			//	Vec3F vec1(28.7146f, 41.3594f);
			//	Vec3F vec2(76.2211f, 68.4067f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(28.7146f, 41.3594f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Min 3", [](float& fDelta) -> const bool {
			//	Vec3F vec1(8.0429f, 40.1981f);
			//	Vec3F vec2(16.0625f, 83.4853f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Min(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(8.0429f, 40.1981f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Max 1", [](float& fDelta) -> const bool {
			//	Vec3F vec1(96.7911f, 64.2846f);
			//	Vec3F vec2(30.4101f, 11.5474f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(96.7911f, 64.2846f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Max 2", [](float& fDelta) -> const bool {
			//	Vec3F vec1(16.2844f, 32.5915f);
			//	Vec3F vec2(45.5970f, 41.9927f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(45.5970f, 41.9927f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Max 3", [](float& fDelta) -> const bool {
			//	Vec3F vec1(72.7684f, 93.9137f);
			//	Vec3F vec2(30.2332f, 19.2606f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Max(vec1, vec2), fDelta);
			//
			//	return vRes == Vec3F(72.7684f, 93.9137f);
			//	});
			//
			//tbBlock.AddTest("Vec3F Sum 1", [](float& fDelta) -> const bool {
			//	Vec3F vec(78.0600f, 87.2512f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);
			//
			//	return fRes == vec.x + vec.y;
			//	});
			//
			//tbBlock.AddTest("Vec3F Sum 2", [](float& fDelta) -> const bool {
			//	Vec3F vec(97.3376f, 78.5648f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);
			//
			//	return fRes == vec.x + vec.y;
			//	});
			//
			//tbBlock.AddTest("Vec3F Sum 3", [](float& fDelta) -> const bool {
			//	Vec3F vec(57.8870f, 81.7546f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Sum(vec), fDelta);
			//
			//	return fRes == vec.x + vec.y;
			//	});
			//
			//tbBlock.AddTest("Vec3F Dot 1", [](float& fDelta) -> const bool {
			//	Vec3F vec1(26.8330f, 70.8067f);
			//	Vec3F vec2(79.1302f, 60.2868f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Dot 2", [](float& fDelta) -> const bool {
			//	Vec3F vec1(86.4119f, 47.2965f);
			//	Vec3F vec2(20.8300f, 16.3871f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Dot 3", [](float& fDelta) -> const bool {
			//	Vec3F vec1(91.6068f, 54.0450f);
			//	Vec3F vec2(30.6695f, 92.2011f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length 1", [](float& fDelta) -> const bool {
			//	Vec3F vec(9.4654f, 17.3159f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Length(vec), fDelta);
			//
			//	return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length 2", [](float& fDelta) -> const bool {
			//	Vec3F vec(60.8574f, 49.0449f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Length(vec), fDelta);
			//
			//	return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length 3", [](float& fDelta) -> const bool {
			//	Vec3F vec(65.8412f, 59.2604f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Length(vec), fDelta);
			//
			//	return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length Squared 1", [](float& fDelta) -> const bool {
			//	Vec3F vec(43.9689f, 96.0509f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);
			//
			//	return fRes == (vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length Squared 2", [](float& fDelta) -> const bool {
			//	Vec3F vec(53.1229f, 66.8357f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);
			//
			//	return fRes == (vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Length Squared 3", [](float& fDelta) -> const bool {
			//	Vec3F vec(28.9374f, 1.0988f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = LengthSquared(vec), fDelta);
			//
			//	return fRes == (vec.x * vec.x + vec.y * vec.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Normalize 1", [](float& fDelta) -> const bool {
			//	Vec3F vec(74.2584f, 69.7548f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);
			//
			//	return vRes == vec / Length(vec);
			//	});
			//
			//tbBlock.AddTest("Vec3F Normalize 2", [](float& fDelta) -> const bool {
			//	Vec3F vec(37.8081f, 90.8517f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);
			//
			//	return vRes == vec / Length(vec);
			//	});
			//
			//tbBlock.AddTest("Vec3F Normalize 3", [](float& fDelta) -> const bool {
			//	Vec3F vec(52.8772f, 94.8309f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Normalize(vec), fDelta);
			//
			//	return vRes == vec / Length(vec);
			//	});
			//
			//tbBlock.AddTest("Vec3F Angle Between 1", [](float& fDelta) -> const bool {
			//	Vec3F vec1(89.6417f, 79.4191f);
			//	Vec3F vec2(1.4510f, 0.0928f);
			//	float fRes;
			//
			//	vec1 = Normalize(vec1);
			//	vec2 = Normalize(vec2);
			//
			//	HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);
			//
			//	return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Angle Between 2", [](float& fDelta) -> const bool {
			//	Vec3F vec1(91.8041f, 90.4006f);
			//	Vec3F vec2(6.7411f, 43.1172f);
			//	float fRes;
			//
			//	vec1 = Normalize(vec1);
			//	vec2 = Normalize(vec2);
			//
			//	HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);
			//
			//	return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Angle Between 3", [](float& fDelta) -> const bool {
			//	Vec3F vec1(69.2061f, 74.7766f);
			//	Vec3F vec2(56.8069f, 54.0597f);
			//	float fRes;
			//
			//	vec1 = Normalize(vec1);
			//	vec2 = Normalize(vec2);
			//
			//	HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), fDelta);
			//
			//	return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			//	});
			//
			//tbBlock.AddTest("Vec3F Cross 1", [](float& fDelta) -> const bool {
			//	Vec3F vec1(-97.2270f, 38.6223f);
			//	Vec3F vec2(86.0807f, 1.9667f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			//	});
			//
			//tbBlock.AddTest("Vec3F Cross 2", [](float& fDelta) -> const bool {
			//	Vec3F vec1(23.5460f, 38.0488f);
			//	Vec3F vec2(-42.1373f, -70.5776f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			//	});
			//
			//tbBlock.AddTest("Vec3F Cross 3", [](float& fDelta) -> const bool {
			//	Vec3F vec1(13.7789f, 88.7826f);
			//	Vec3F vec2(-13.9210f, -42.339f);
			//	float fRes;
			//
			//	HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), fDelta);
			//
			//	return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			//	});
			//
			//tbBlock.AddTest("Vec3F Abs 1", [](float& fDelta) -> const bool {
			//	Vec3F vec(96.5146f, -61.7155f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);
			//
			//	return vRes == Vec3F(abs(vec.x), abs(vec.y));
			//	});
			//
			//tbBlock.AddTest("Vec3F Abs 2", [](float& fDelta) -> const bool {
			//	Vec3F vec(1.7028f, -53.4726f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);
			//
			//	return vRes == Vec3F(abs(vec.x), abs(vec.y));
			//	});
			//
			//tbBlock.AddTest("Vec3F Abs 3", [](float& fDelta) -> const bool {
			//	Vec3F vec(-86.6360f, -7.9589f);
			//	Vec3F vRes;
			//
			//	HC_TIME_EXECUTION(vRes = Abs(vec), fDelta);
			//
			//	return vRes == Vec3F(abs(vec.x), abs(vec.y));
			//	});
		}

		_vBlockList.push_back(tbBlock);

		//tbBlock = TestBlock("Math Library - Vec3D");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//Vec4F/D
#pragma region Vec4
		//TestBlock tbBlock("Math Library - Vec4F");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - Vec4D");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//MatrixF/D
#pragma region Matrix
		//TestBlock tbBlock("Math Library - MatrixF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - MatrixD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//QuaternionF/D
#pragma region Quaternion
		//TestBlock tbBlock("Math Library - QuaternionF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - QuaternionD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//RotorF/D
#pragma region Rotor
		//TestBlock tbBlock("Math Library - RotorF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - RotorD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//Random
#pragma region Random
		//TestBlock tbBlock("Math Library - Random");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//Math
#pragma region Math
		//TestBlock tbBlock("Math Library - Misc");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion
	}
}
