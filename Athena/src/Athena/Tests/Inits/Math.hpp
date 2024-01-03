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
			tbBlock.AddTest("Vec2F Equals 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(72.7684f, 93.9137f);
				Vec2F vec2(72.7684f, 93.9137f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Equals 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(1.0f, 2.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(1000.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Not Equals 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(12321.0f, 2233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.002f);
				Vec2F vec2(212.0f, 63.002f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(1.0f, 2.0f);
				Vec2F vec2(2.0f, 3.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(1000.0f, 2233.32f);
				Vec2F vec2(100.0f, 233.32f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2F Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(212.0f, 63.0f);
				Vec2F vec2(212.0f, 63.0f);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec2F Add 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(562.3817f, 879.1950f);
				Vec2F vec2(729.7944f, 330.4333f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Add 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(956.2237f, 331.7911f);
				Vec2F vec2(349.2213f, 312.8308f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Add 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(725.3930f, 269.9619f);
				Vec2F vec2(922.0483f, 544.8846f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2F(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(949.4220f, 254.6960f);
				Vec2F vec2(952.8229f, 548.7633f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(708.4678f, 545.4393f);
				Vec2F vec2(585.3077f, 910.9493f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Sub 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(513.1027f, 509.7849f);
				Vec2F vec2(868.3063f, 73.3378f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2F(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(80.2183f, 48.4900f);
				Vec2F vec2(48.6584f, 28.2959f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(36.6653f, 28.2451f);
				Vec2F vec2(4.1396f, 78.3024f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Mul 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(51.6924f, 27.1861f);
				Vec2F vec2(79.7343f, 60.6889f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2F(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Scale 1", [](float& _fDelta) -> const bool {
				Vec2F vec(128.3676f, 386.5519f);
				float scale = 4.7647f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Scale 2", [](float& _fDelta) -> const bool {
				Vec2F vec(640.0216f, 599.3427f);
				float scale = 8.6124f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Scale 3", [](float& _fDelta) -> const bool {
				Vec2F vec(826.0256f, 312.1744f);
				float scale = 3.4540f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec2F(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2F Div 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(645.6976f, 133.4426f);
				Vec2F vec2(324.8063f, 246.3471f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Div 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(866.2313f, 958.3398f);
				Vec2F vec2(729.4492f, 272.1197f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Div 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(832.8854f, 711.4308f);
				Vec2F vec2(98.4148f, 581.0262f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2F(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2F Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec2F vec(128.3676f, 386.5519f);
				float scale = 4.7647f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2F Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec2F vec(640.0216f, 599.3427f);
				float scale = 8.6124f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2F Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec2F vec(826.0256f, 312.1744f);
				float scale = 3.4540f;
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec2F(vec.x / scale, vec.y / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec2F Zero", [](float& _fDelta) -> const bool {
				Vec2F vec(1.0f, 2.0f);

				HC_TIME_EXECUTION(vec = ~vec, _fDelta);

				return vec == Vec2F();
			});

			tbBlock.AddTest("Vec2F Negate", [](float& _fDelta) -> const bool {
				Vec2F vec(1.0f, 2.0f);

				HC_TIME_EXECUTION(vec = -vec, _fDelta);

				return vec == Vec2F(-1.0f, -2.0f);
			});
		}

		//Functions
		{
			tbBlock.AddTest("Vec2F Min 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(51.1165f, 42.3195f);
				Vec2F vec2(39.1151f, 59.8660f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2F(39.1151f, 42.3195f);
			});

			tbBlock.AddTest("Vec2F Min 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(28.7146f, 41.3594f);
				Vec2F vec2(76.2211f, 68.4067f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2F(28.7146f, 41.3594f);
			});

			tbBlock.AddTest("Vec2F Min 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(8.0429f, 40.1981f);
				Vec2F vec2(16.0625f, 83.4853f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2F(8.0429f, 40.1981f);
			});

			tbBlock.AddTest("Vec2F Max 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(96.7911f, 64.2846f);
				Vec2F vec2(30.4101f, 11.5474f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2F(96.7911f, 64.2846f);
			});

			tbBlock.AddTest("Vec2F Max 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(16.2844f, 32.5915f);
				Vec2F vec2(45.5970f, 41.9927f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2F(45.5970f, 41.9927f);
			});

			tbBlock.AddTest("Vec2F Max 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(72.7684f, 93.9137f);
				Vec2F vec2(30.2332f, 19.2606f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2F(72.7684f, 93.9137f);
			});

			tbBlock.AddTest("Vec2F Sum 1", [](float& _fDelta) -> const bool {
				Vec2F vec(78.0600f, 87.2512f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Sum 2", [](float& _fDelta) -> const bool {
				Vec2F vec(97.3376f, 78.5648f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Sum 3", [](float& _fDelta) -> const bool {
				Vec2F vec(57.8870f, 81.7546f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);

				return fRes == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2F Dot 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(26.8330f, 70.8067f);
				Vec2F vec2(79.1302f, 60.2868f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Dot 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(86.4119f, 47.2965f);
				Vec2F vec2(20.8300f, 16.3871f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Dot 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(91.6068f, 54.0450f);
				Vec2F vec2(30.6695f, 92.2011f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Length 1", [](float& _fDelta) -> const bool {
				Vec2F vec(9.4654f, 17.3159f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length 2", [](float& _fDelta) -> const bool {
				Vec2F vec(60.8574f, 49.0449f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length 3", [](float& _fDelta) -> const bool {
				Vec2F vec(65.8412f, 59.2604f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);

				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 1", [](float& _fDelta) -> const bool {
				Vec2F vec(43.9689f, 96.0509f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 2", [](float& _fDelta) -> const bool {
				Vec2F vec(53.1229f, 66.8357f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Length Squared 3", [](float& _fDelta) -> const bool {
				Vec2F vec(28.9374f, 1.0988f);
				float fRes;

				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);

				return fRes == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2F Normalize 1", [](float& _fDelta) -> const bool {
				Vec2F vec(74.2584f, 69.7548f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Normalize 2", [](float& _fDelta) -> const bool {
				Vec2F vec(37.8081f, 90.8517f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Normalize 3", [](float& _fDelta) -> const bool {
				Vec2F vec(52.8772f, 94.8309f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2F Angle Between 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(89.6417f, 79.4191f);
				Vec2F vec2(1.4510f, 0.0928f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Angle Between 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(91.8041f, 90.4006f);
				Vec2F vec2(6.7411f, 43.1172f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Angle Between 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(69.2061f, 74.7766f);
				Vec2F vec2(56.8069f, 54.0597f);
				float fRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);

				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2F Cross 1", [](float& _fDelta) -> const bool {
				Vec2F vec1(-97.2270f, 38.6223f);
				Vec2F vec2(86.0807f, 1.9667f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Cross 2", [](float& _fDelta) -> const bool {
				Vec2F vec1(23.5460f, 38.0488f);
				Vec2F vec2(-42.1373f, -70.5776f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Cross 3", [](float& _fDelta) -> const bool {
				Vec2F vec1(13.7789f, 88.7826f);
				Vec2F vec2(-13.9210f, -42.339f);
				float fRes;

				HC_TIME_EXECUTION(fRes = Cross(vec1, vec2), _fDelta);

				return fRes == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2F Abs 1", [](float& _fDelta) -> const bool {
				Vec2F vec(96.5146f, -61.7155f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2F Abs 2", [](float& _fDelta) -> const bool {
				Vec2F vec(1.7028f, -53.4726f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2F Abs 3", [](float& _fDelta) -> const bool {
				Vec2F vec(-86.6360f, -7.9589f);
				Vec2F vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec2F(abs(vec.x), abs(vec.y));
			});
		}

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - Vec2D");

		//Comparison Operators
		{
			tbBlock.AddTest("Vec2D Equals 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(72.7684, 93.9137);
				Vec2D vec2(72.7684, 93.9137);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Equals 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(1000.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Equals 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(1.0, 2.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(1000.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Not Equals 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(12321.0, 2233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.002);
				Vec2D vec2(212.0, 63.002);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(1.0, 2.0);
				Vec2D vec2(2.0, 3.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(1000.0, 2233.32);
				Vec2D vec2(100.0, 233.32);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec2D Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(212.0, 63.0);
				Vec2D vec2(212.0, 63.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec2D Add 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(562.3817, 879.1950);
				Vec2D vec2(729.7944, 330.4333);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Add 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(956.2237, 331.7911);
				Vec2D vec2(349.2213, 312.8308);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Add 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(725.3930, 269.9619);
				Vec2D vec2(922.0483, 544.8846);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec2D(vec1.x + vec2.x, vec1.y + vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(949.4220, 254.6960);
				Vec2D vec2(952.8229, 548.7633);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(708.4678, 545.4393);
				Vec2D vec2(585.3077, 910.9493);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Sub 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(513.1027, 509.7849);
				Vec2D vec2(868.3063, 73.3378);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec2D(vec1.x - vec2.x, vec1.y - vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(80.2183, 48.4900);
				Vec2D vec2(48.6584, 28.2959);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(36.6653, 28.2451);
				Vec2D vec2(4.1396, 78.3024);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Mul 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(51.6924, 27.1861);
				Vec2D vec2(79.7343, 60.6889);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec2D(vec1.x * vec2.x, vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Scale 1", [](float& _fDelta) -> const bool {
				Vec2D vec(128.3676, 386.5519);
				double scale = 4.7647;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Scale 2", [](float& _fDelta) -> const bool {
				Vec2D vec(640.0216, 599.3427);
				double scale = 8.6124;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Scale 3", [](float& _fDelta) -> const bool {
				Vec2D vec(826.0256, 312.1744);
				double scale = 3.4540;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec2D(vec.x * scale, vec.y * scale);
			});

			tbBlock.AddTest("Vec2D Div 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(645.6976, 133.4426);
				Vec2D vec2(324.8063, 246.3471);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Div 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(866.2313, 958.3398);
				Vec2D vec2(729.4492, 272.1197);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Div 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(832.8854, 711.4308);
				Vec2D vec2(98.4148, 581.0262);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec2D(vec1.x / vec2.x, vec1.y / vec2.y);
			});

			tbBlock.AddTest("Vec2D Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec2D vec(128.3676, 386.5519);
				double scale = 4.7647;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2D Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec2D vec(640.0216, 599.3427);
				double scale = 8.6124;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});

			tbBlock.AddTest("Vec2D Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec2D vec(826.0256, 312.1744);
				double scale = 3.4540;
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec2D(vec.x / scale, vec.y / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec2D Zero", [](float& _fDelta) -> const bool {
				Vec2D vec(1.0, 2.0);

				HC_TIME_EXECUTION(vec = ~vec, _fDelta);

				return vec == Vec2D();
			});

			tbBlock.AddTest("Vec2D Negate", [](float& _fDelta) -> const bool {
				Vec2D vec(1.0, 2.0);

				HC_TIME_EXECUTION(vec = -vec, _fDelta);

				return vec == Vec2D(-1.0, -2.0);
			});
		}

		//Functions
		{
			tbBlock.AddTest("Vec2D Min 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(51.1165, 42.3195);
				Vec2D vec2(39.1151, 59.8660);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2D(39.1151, 42.3195);
			});

			tbBlock.AddTest("Vec2D Min 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(28.7146, 41.3594);
				Vec2D vec2(76.2211, 68.4067);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2D(28.7146, 41.3594);
			});

			tbBlock.AddTest("Vec2D Min 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(8.0429, 40.1981);
				Vec2D vec2(16.0625, 83.4853);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec2D(8.0429, 40.1981);
			});

			tbBlock.AddTest("Vec2D Max 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(96.7911, 64.2846);
				Vec2D vec2(30.4101, 11.5474);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2D(96.7911, 64.2846);
			});

			tbBlock.AddTest("Vec2D Max 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(16.2844, 32.5915);
				Vec2D vec2(45.5970, 41.9927);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2D(45.5970, 41.9927);
			});

			tbBlock.AddTest("Vec2D Max 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(72.7684, 93.9137);
				Vec2D vec2(30.2332, 19.2606);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec2D(72.7684, 93.9137);
			});

			tbBlock.AddTest("Vec2D Sum 1", [](float& _fDelta) -> const bool {
				Vec2D vec(78.0600, 87.2512);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), _fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Sum 2", [](float& _fDelta) -> const bool {
				Vec2D vec(97.3376, 78.5648);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), _fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Sum 3", [](float& _fDelta) -> const bool {
				Vec2D vec(57.8870, 81.7546);
				double Res;

				HC_TIME_EXECUTION(Res = Sum(vec), _fDelta);

				return Res == vec.x + vec.y;
			});

			tbBlock.AddTest("Vec2D Dot 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(26.8330, 70.8067);
				Vec2D vec2(79.1302, 60.2868);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Dot 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(86.4119, 47.2965);
				Vec2D vec2(20.8300, 16.3871);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Dot 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(91.6068, 54.0450);
				Vec2D vec2(30.6695, 92.2011);
				double Res;

				HC_TIME_EXECUTION(Res = Dot(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Length 1", [](float& _fDelta) -> const bool {
				Vec2D vec(9.4654, 17.3159);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), _fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length 2", [](float& _fDelta) -> const bool {
				Vec2D vec(60.8574, 49.0449);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), _fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length 3", [](float& _fDelta) -> const bool {
				Vec2D vec(65.8412, 59.2604);
				double Res;

				HC_TIME_EXECUTION(Res = Length(vec), _fDelta);

				return Res == sqrt(vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 1", [](float& _fDelta) -> const bool {
				Vec2D vec(43.9689, 96.0509);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), _fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 2", [](float& _fDelta) -> const bool {
				Vec2D vec(53.1229, 66.8357);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), _fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Length Squared 3", [](float& _fDelta) -> const bool {
				Vec2D vec(28.9374, 1.0988);
				double Res;

				HC_TIME_EXECUTION(Res = LengthSquared(vec), _fDelta);

				return Res == (vec.x * vec.x + vec.y * vec.y);
			});

			tbBlock.AddTest("Vec2D Normalize 1", [](float& _fDelta) -> const bool {
				Vec2D vec(74.2584, 69.7548);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Normalize 2", [](float& _fDelta) -> const bool {
				Vec2D vec(37.8081, 90.8517);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Normalize 3", [](float& _fDelta) -> const bool {
				Vec2D vec(52.8772, 94.8309);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec2D Angle Between 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(89.6417, 79.4191);
				Vec2D vec2(1.4510, 0.0928);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), _fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Angle Between 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(91.8041, 90.4006);
				Vec2D vec2(6.7411, 43.1172);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), _fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Angle Between 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(69.2061, 74.7766);
				Vec2D vec2(56.8069, 54.0597);
				double Res;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(Res = AngleBetween(vec1, vec2), _fDelta);

				return Res == acos(vec1.x * vec2.x + vec1.y * vec2.y);
			});

			tbBlock.AddTest("Vec2D Cross 1", [](float& _fDelta) -> const bool {
				Vec2D vec1(-97.2270, 38.6223);
				Vec2D vec2(86.0807, 1.9667);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Cross 2", [](float& _fDelta) -> const bool {
				Vec2D vec1(23.5460, 38.0488);
				Vec2D vec2(-42.1373, -70.5776);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Cross 3", [](float& _fDelta) -> const bool {
				Vec2D vec1(13.7789, 88.7826);
				Vec2D vec2(-13.9210, -42.339);
				double Res;

				HC_TIME_EXECUTION(Res = Cross(vec1, vec2), _fDelta);

				return Res == (vec1.x * vec2.y - vec1.y * vec2.x);
			});

			tbBlock.AddTest("Vec2D Abs 1", [](float& _fDelta) -> const bool {
				Vec2D vec(96.5146, -61.7155);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec2D(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2D Abs 2", [](float& _fDelta) -> const bool {
				Vec2D vec(1.7028, -53.4726);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec2D(abs(vec.x), abs(vec.y));
			});

			tbBlock.AddTest("Vec2D Abs 3", [](float& _fDelta) -> const bool {
				Vec2D vec(-86.6360, -7.9589);
				Vec2D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

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
#pragma endregion

		//Vec4F/D
#pragma region Vec4
		tbBlock = TestBlock("Math Library - Vec4F");
		
		//Comparison Operators
		{
			tbBlock.AddTest("Vec4F Equals 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(72.7684f, 93.9137f, -80.9734f, 68.9801f);
				Vec4F vec2(72.7684f, 93.9137f, -80.9734f, 68.9801f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Equals 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, -38.3864f, 98.9730f);
				Vec4F vec2(1000.0f, 2233.32f, -38.3864f, 98.9730f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Equals 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 49.2350f, 61.6915f);
				Vec4F vec2(12321.0f, 2233.32f, 82.9944f, -77.0042f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Not Equals 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(1.0f, 2.0f, -11.9128f, 9.7563f);
				Vec4F vec2(1.0f, 2.0f, -11.9128f, 9.7563f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Not Equals 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, 99.4377f, -82.1028f);
				Vec4F vec2(1000.0f, 2233.32f, 99.4377f, -82.1028f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Not Equals 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 5.4785f, 68.7825f);
				Vec4F vec2(12321.0f, 2233.32f, 64.1631f, -68.0975f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(1.0f, 2.0f, 3.0f, 4.0f);
				Vec4F vec2(2.0f, 3.0f, 4.0f, 5.0f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, 54.785f, 647.446f);
				Vec4F vec2(100.0f, 233.32f, 5.4785f, 64.7446f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 99.4377f, 49.6147f);
				Vec4F vec2(12321.0f, 2233.32f, 994.377f, 496.147f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(1.0f, 2.0f, 3.0f, 4.0f);
				Vec4F vec2(2.0f, 3.0f, 4.0f, 5.0f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, 54.785f, 647.446f);
				Vec4F vec2(100.0f, 233.32f, 5.4785f, 64.7446f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 99.4377f, 49.6147f);
				Vec4F vec2(12321.0f, 2233.32f, 994.377f, 496.147f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(1.0f, 2.0f, 3.0f, 4.0f);
				Vec4F vec2(2.0f, 3.0f, 4.0f, 5.0f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, 54.785f, 647.446f);
				Vec4F vec2(100.0f, 233.32f, 5.4785f, 64.7446f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 16.5280f,  -32.6626f);
				Vec4F vec2(212.0f, 63.002f, 16.5280f,  -32.6626f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(1.0f, 2.0f, 3.0f, 4.0f);
				Vec4F vec2(2.0f, 3.0f, 4.0f, 5.0f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);
			
				return !bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(1000.0f, 2233.32f, 54.785f, 647.446f);
				Vec4F vec2(100.0f, 233.32f, 5.4785f, 64.7446f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);
			
				return bRes;
			});
			
			tbBlock.AddTest("Vec4F Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(212.0f, 63.002f, 16.5280f, -32.6626f);
				Vec4F vec2(212.0f, 63.002f, 16.5280f, -32.6626f);
				bool bRes;
			
				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);
			
				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec4F Add 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(562.3817f, 879.1950f, -54.7428f, -51.8984f);
				Vec4F vec2(729.7944f, 330.4333f, 98.9734f, -73.1578f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Add 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(956.2237f, 331.7911f, 68.3852f, -26.1628f);
				Vec4F vec2(349.2213f, 312.8308f, 64.1928f, -29.0480f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Add 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(725.3930f, 269.9619f, 47.9971f, -30.3194f);
				Vec4F vec2(922.0483f, 544.8846f, -32.1389f, -23.5159f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Sub 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(949.4220f, 254.6960f, 95.4638f, -3.5822f);
				Vec4F vec2(952.8229f, 548.7633f, -85.3625f, 91.0427f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Sub 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(708.4678f, 545.4393f, 87.8738f, 53.1406f);
				Vec4F vec2(585.3077f, 910.9493f, -40.6951f, 13.4148f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Sub 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(513.1027f, 509.7849f, 98.1163f, -63.9236f);
				Vec4F vec2(868.3063f, 73.3378f, 81.0108f, -35.8630f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			}); 
			
			tbBlock.AddTest("Vec4F Mul 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(80.2183f, 48.4900f, 38.3640f, 49.4667f);
				Vec4F vec2(48.6584f, 28.2959f, -4.9290f, 62.7242f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Mul 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(36.6653f, 28.2451f, 30.5739f, 93.2984f);
				Vec4F vec2(4.1396f, 78.3024f, -56.1665f, 63.9348f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Mul 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(51.6924f, 27.1861f, 8.4850f, 22.7953f);
				Vec4F vec2(79.7343f, 60.6889f, 49.8523f, 57.2975f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Scale 1", [](float& _fDelta) -> const bool {
				Vec4F vec(128.3676f, 386.5519f, 91.3604f, 5.3337f);
				float scale = 4.7647f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);
			
				return vRes == Vec4F(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});
			
			tbBlock.AddTest("Vec4F Scale 2", [](float& _fDelta) -> const bool {
				Vec4F vec(640.0216f, 599.3427f, 14.4820f, -51.1619f);
				float scale = 8.6124f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);
			
				return vRes == Vec4F(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});
			
			tbBlock.AddTest("Vec4F Scale 3", [](float& _fDelta) -> const bool {
				Vec4F vec(826.0256f, 312.1744f, -94.6371f, 84.5961f);
				float scale = 3.4540f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);
			
				return vRes == Vec4F(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});
			
			tbBlock.AddTest("Vec4F Div 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(645.6976f, 133.4426f, -13.1399f, -59.6285f);
				Vec4F vec2(324.8063f, 246.3471f, 79.5019f, -59.6285f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Div 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(866.2313f, 958.3398f, 30.8907f, 71.5629f);
				Vec4F vec2(729.4492f, 272.1197f, 38.8574f, -37.4520f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Div 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(832.8854f, 711.4308f, -21.1883f, 34.5536f);
				Vec4F vec2(98.4148f, 581.0262f, 98.4090f, -94.2277f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);
			
				return vRes == Vec4F(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec4F vec(128.3676f, 386.5519f, 60.3248f, -84.5400f);
				float scale = 4.7647f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);
			
				return vRes == Vec4F(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});
			
			tbBlock.AddTest("Vec4F Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec4F vec(640.0216f, 599.3427f, -31.3702f, -46.6410f);
				float scale = 8.6124f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);
			
				return vRes == Vec4F(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});
			
			tbBlock.AddTest("Vec4F Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec4F vec(826.0256f, 312.1744f, 54.1705f, -26.6897f);
				float scale = 3.4540f;
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);
			
				return vRes == Vec4F(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec4F Zero", [](float& _fDelta) -> const bool {
				Vec4F vec(1.0f, 2.0f, 3.0f, 4.0f);
			
				HC_TIME_EXECUTION(vec = ~vec, _fDelta);
			
				return vec == Vec4F();
			});
			
			tbBlock.AddTest("Vec4F Negate", [](float& _fDelta) -> const bool {
				Vec4F vec(1.0f, 2.0f, 3.0f, 4.0f);
			
				HC_TIME_EXECUTION(vec = -vec, _fDelta);
			
				return vec == Vec4F(-1.0f, -2.0f, -3.0f, -4.0f);
			});
		}

		//Functions
		{
			tbBlock.AddTest("Vec4F Min 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(51.1165f, 42.3195f, 49.7369f, -75.3150f);
				Vec4F vec2(39.1151f, 59.8660f, -28.4884f, -28.7055f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(39.1151f, 42.3195f, -28.4884f, -75.3150f);
			});
			
			tbBlock.AddTest("Vec4F Min 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(28.7146f, 41.3594f, 97.7016f, -54.7634f);
				Vec4F vec2(76.2211f, 68.4067f, -1.3772f, -56.6137f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(28.7146f, 41.3594f, -1.3772f, -56.6137f);
			});
			
			tbBlock.AddTest("Vec4F Min 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(8.0429f, 40.1981f, -59.5477f, -93.4670f);
				Vec4F vec2(16.0625f, 83.4853f, 14.7856f, 49.5655f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(8.0429f, 40.1981f, -59.5477f, -93.4670f);
			});
			
			tbBlock.AddTest("Vec4F Max 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(96.7911f, 64.2846f, -35.3075f, -46.9703f);
				Vec4F vec2(30.4101f, 11.5474f, 64.8257f, 73.8171f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(96.7911f, 64.2846f, 64.8257f, 73.8171f);
			});
			
			tbBlock.AddTest("Vec4F Max 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(16.2844f, 32.5915f, 72.0709f, 84.0965f);
				Vec4F vec2(45.5970f, 41.9927f, 78.8099f, -39.0389f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(45.5970f, 41.9927f, 78.8099f, 84.0965f);
			});
			
			tbBlock.AddTest("Vec4F Max 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(72.7684f, 93.9137f, 85.4258f, -18.2931f);
				Vec4F vec2(30.2332f, 19.2606f, 99.2068f, 84.1347f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(72.7684f, 93.9137f, 99.2068f, 84.1347f);
			});
			
			tbBlock.AddTest("Vec4F Sum 1", [](float& _fDelta) -> const bool {
				Vec4F vec(78.0600f, 87.2512f, 17.4745f, -38.9328f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);
			
				return fRes == vec.x + vec.y + vec.z + vec.w;
			});
			
			tbBlock.AddTest("Vec4F Sum 2", [](float& _fDelta) -> const bool {
				Vec4F vec(97.3376f, 78.5648f, -72.4875f, 96.3222f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);
			
				return fRes == vec.x + vec.y + vec.z + vec.w;
			});
			
			tbBlock.AddTest("Vec4F Sum 3", [](float& _fDelta) -> const bool {
				Vec4F vec(57.8870f, 81.7546f, -56.3297f, -40.1260f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Sum(vec), _fDelta);
			
				return fRes == vec.x + vec.y + vec.z + vec.w;
			});
			
			tbBlock.AddTest("Vec4F Dot 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(26.8330f, 70.8067f, 94.4725f, -11.0555f);
				Vec4F vec2(79.1302f, 60.2868f, 38.1920f, -27.3375f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);
			
				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Dot 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(86.4119f, 47.2965f, 55.8695f, 39.9468f);
				Vec4F vec2(20.8300f, 16.3871f, -65.5612f, 87.4098f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);
			
				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Dot 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(91.6068f, 54.0450f, -8.8122f, -75.5348f);
				Vec4F vec2(30.6695f, 92.2011f, -60.2328f, -22.4749f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Dot(vec1, vec2), _fDelta);
			
				return fRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Length 1", [](float& _fDelta) -> const bool {
				Vec4F vec(9.4654f, 17.3159f, -65.7723f, 50.5322f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);
			
				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Length 2", [](float& _fDelta) -> const bool {
				Vec4F vec(60.8574f, 49.0449f, -73.1398f, 76.4660f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);
			
				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Length 3", [](float& _fDelta) -> const bool {
				Vec4F vec(65.8412f, 59.2604f, 83.9684f, 37.5298f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = Length(vec), _fDelta);
			
				return fRes == sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Length Squared 1", [](float& _fDelta) -> const bool {
				Vec4F vec(43.9689f, 96.0509f, 88.9848f, 92.2607f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);
			
				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Length Squared 2", [](float& _fDelta) -> const bool {
				Vec4F vec(53.1229f, 66.8357f, -1.5535f, 4.8029f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);
			
				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Length Squared 3", [](float& _fDelta) -> const bool {
				Vec4F vec(28.9374f, 1.0988f, 49.2252f, -87.9614f);
				float fRes;
			
				HC_TIME_EXECUTION(fRes = LengthSquared(vec), _fDelta);
			
				return fRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});
			
			tbBlock.AddTest("Vec4F Normalize 1", [](float& _fDelta) -> const bool {
				Vec4F vec(74.2584f, 69.7548f, 41.2219f, 79.8498f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);
			
				return vRes == vec / Length(vec);
			});
			
			tbBlock.AddTest("Vec4F Normalize 2", [](float& _fDelta) -> const bool {
				Vec4F vec(37.8081f, 90.8517f, -26.2088f, -74.4120f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);
			
				return vRes == vec / Length(vec);
			});
			
			tbBlock.AddTest("Vec4F Normalize 3", [](float& _fDelta) -> const bool {
				Vec4F vec(52.8772f, 94.8309f, 31.6384f, -30.9328f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);
			
				return vRes == vec / Length(vec);
			});
			
			tbBlock.AddTest("Vec4F Angle Between 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(89.6417f, 79.4191f, 22.7910f, -21.0206f);
				Vec4F vec2(1.4510f, 0.0928f, -27.6698f, 29.4491f);
				float fRes;
			
				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);
			
				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);
			
				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Angle Between 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(91.8041f, 90.4006f, 9.4439f, 84.1371f);
				Vec4F vec2(6.7411f, 43.1172f, 56.0758f, 21.6438f);
				float fRes;
			
				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);
			
				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);
			
				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Angle Between 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(69.2061f, 74.7766f, -6.6671f, -60.0610f);
				Vec4F vec2(56.8069f, 54.0597f, -91.8969f, -80.2745f);
				float fRes;
			
				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);
			
				HC_TIME_EXECUTION(fRes = AngleBetween(vec1, vec2), _fDelta);
			
				return fRes == acosf(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});
			
			tbBlock.AddTest("Vec4F Cross 1", [](float& _fDelta) -> const bool {
				Vec4F vec1(-97.2270f, 38.6223f, -28.2738f, -69.2833f);
				Vec4F vec2(86.0807f, 1.9667f, -94.1717f, -89.0293f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});
			
			tbBlock.AddTest("Vec4F Cross 2", [](float& _fDelta) -> const bool {
				Vec4F vec1(23.5460f, 38.0488f, 17.8359f, 92.2378f);
				Vec4F vec2(-42.1373f, -70.5776f, -33.3752f, 56.0375f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = vec1 ^ vec2, _fDelta);
			
				return vRes == Vec4F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});
			
			tbBlock.AddTest("Vec4F Cross 3", [](float& _fDelta) -> const bool {
				Vec4F vec1(13.7789f, 88.7826f, -27.1393f, 85.2095f);
				Vec4F vec2(-13.9210f, -42.339f, 54.9631f, -48.7205f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);
			
				return vRes == Vec4F(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});
			
			tbBlock.AddTest("Vec4F Abs 1", [](float& _fDelta) -> const bool {
				Vec4F vec(96.5146f, -61.7155f, -9.8896f, -71.1936f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);
			
				return vRes == Vec4F(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});
			
			tbBlock.AddTest("Vec4F Abs 2", [](float& _fDelta) -> const bool {
				Vec4F vec(1.7028f, -53.4726f, 65.2977f, -84.0155f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);
			
				return vRes == Vec4F(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});
			
			tbBlock.AddTest("Vec4F Abs 3", [](float& _fDelta) -> const bool {
				Vec4F vec(-86.6360f, -7.9589f, -58.1190f, -12.8462f);
				Vec4F vRes;
			
				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);
			
				return vRes == Vec4F(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});
		}

		_vBlockList.push_back(tbBlock);
		
		tbBlock = TestBlock("Math Library - Vec4D");
		
		//Comparison Operators
		{
			tbBlock.AddTest("Vec4D Equals 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(72.7684, 93.9137, -80.9734, 68.9801);
				Vec4D vec2(72.7684, 93.9137, -80.9734, 68.9801);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Equals 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, -38.3864, 98.9730);
				Vec4D vec2(1000.0, 2233.32, -38.3864, 98.9730);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Equals 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 49.2350, 61.6915);
				Vec4D vec2(12321.0, 2233.32, 82.9944, -77.0042);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 == vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Not Equals 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(1.0, 2.0, -11.9128, 9.7563);
				Vec4D vec2(1.0, 2.0, -11.9128, 9.7563);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Not Equals 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, 99.4377, -82.1028);
				Vec4D vec2(1000.0, 2233.32, 99.4377, -82.1028);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Not Equals 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 5.4785, 68.7825);
				Vec4D vec2(12321.0, 2233.32, 64.1631, -68.0975);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 != vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Less Than 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(1.0, 2.0, 3.0, 4.0);
				Vec4D vec2(2.0, 3.0, 4.0, 5.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Less Than 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, 54.785, 647.446);
				Vec4D vec2(100.0, 233.32, 5.4785, 64.7446);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Less Than 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 99.4377, 49.6147);
				Vec4D vec2(12321.0, 2233.32, 994.377, 496.147);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 < vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(1.0, 2.0, 3.0, 4.0);
				Vec4D vec2(2.0, 3.0, 4.0, 5.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, 54.785, 647.446);
				Vec4D vec2(100.0, 233.32, 5.4785, 64.7446);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 99.4377, 49.6147);
				Vec4D vec2(12321.0, 2233.32, 994.377, 496.147);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 > vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Less Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(1.0, 2.0, 3.0, 4.0);
				Vec4D vec2(2.0, 3.0, 4.0, 5.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Less Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, 54.785, 647.446);
				Vec4D vec2(100.0, 233.32, 5.4785, 64.7446);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Less Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 16.5280, -32.6626);
				Vec4D vec2(212.0, 63.002, 16.5280, -32.6626);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 <= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than Or Equal 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(1.0, 2.0, 3.0, 4.0);
				Vec4D vec2(2.0, 3.0, 4.0, 5.0);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return !bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than Or Equal 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(1000.0, 2233.32, 54.785, 647.446);
				Vec4D vec2(100.0, 233.32, 5.4785, 64.7446);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});

			tbBlock.AddTest("Vec4D Greater Than Or Equal 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(212.0, 63.002, 16.5280, -32.6626);
				Vec4D vec2(212.0, 63.002, 16.5280, -32.6626);
				bool bRes;

				HC_TIME_EXECUTION(bRes = vec1 >= vec2, _fDelta);

				return bRes;
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("Vec4D Add 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(562.3817, 879.1950, -54.7428, -51.8984);
				Vec4D vec2(729.7944, 330.4333, 98.9734, -73.1578);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec4D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});

			tbBlock.AddTest("Vec4D Add 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(956.2237, 331.7911, 68.3852, -26.1628);
				Vec4D vec2(349.2213, 312.8308, 64.1928, -29.0480);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec4D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});

			tbBlock.AddTest("Vec4D Add 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(725.3930, 269.9619, 47.9971, -30.3194);
				Vec4D vec2(922.0483, 544.8846, -32.1389, -23.5159);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 + vec2, _fDelta);

				return vRes == Vec4D(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
			});

			tbBlock.AddTest("Vec4D Sub 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(949.4220, 254.6960, 95.4638, -3.5822);
				Vec4D vec2(952.8229, 548.7633, -85.3625, 91.0427);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec4D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			});

			tbBlock.AddTest("Vec4D Sub 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(708.4678, 545.4393, 87.8738, 53.1406);
				Vec4D vec2(585.3077, 910.9493, -40.6951, 13.4148);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec4D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			});

			tbBlock.AddTest("Vec4D Sub 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(513.1027, 509.7849, 98.1163, -63.9236);
				Vec4D vec2(868.3063, 73.3378, 81.0108, -35.8630);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 - vec2, _fDelta);

				return vRes == Vec4D(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
			});

			tbBlock.AddTest("Vec4D Mul 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(80.2183, 48.4900, 38.3640, 49.4667);
				Vec4D vec2(48.6584, 28.2959, -4.9290, 62.7242);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec4D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Mul 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(36.6653, 28.2451, 30.5739, 93.2984);
				Vec4D vec2(4.1396, 78.3024, -56.1665, 63.9348);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec4D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Mul 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(51.6924, 27.1861, 8.4850, 22.7953);
				Vec4D vec2(79.7343, 60.6889, 49.8523, 57.2975);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 * vec2, _fDelta);

				return vRes == Vec4D(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Scale 1", [](float& _fDelta) -> const bool {
				Vec4D vec(128.3676, 386.5519, 91.3604, 5.3337);
				double scale = 4.7647;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec4D(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});

			tbBlock.AddTest("Vec4D Scale 2", [](float& _fDelta) -> const bool {
				Vec4D vec(640.0216, 599.3427, 14.4820, -51.1619);
				double scale = 8.6124;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = scale * vec, _fDelta);

				return vRes == Vec4D(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});

			tbBlock.AddTest("Vec4D Scale 3", [](float& _fDelta) -> const bool {
				Vec4D vec(826.0256, 312.1744, -94.6371, 84.5961);
				double scale = 3.4540;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec * scale, _fDelta);

				return vRes == Vec4D(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
			});

			tbBlock.AddTest("Vec4D Div 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(645.6976, 133.4426, -13.1399, -59.6285);
				Vec4D vec2(324.8063, 246.3471, 79.5019, -59.6285);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec4D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});

			tbBlock.AddTest("Vec4D Div 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(866.2313, 958.3398, 30.8907, 71.5629);
				Vec4D vec2(729.4492, 272.1197, 38.8574, -37.4520);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec4D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});

			tbBlock.AddTest("Vec4D Div 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(832.8854, 711.4308, -21.1883, 34.5536);
				Vec4D vec2(98.4148, 581.0262, 98.4090, -94.2277);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 / vec2, _fDelta);

				return vRes == Vec4D(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
			});

			tbBlock.AddTest("Vec4D Scalar Div 1", [](float& _fDelta) -> const bool {
				Vec4D vec(128.3676, 386.5519, 60.3248, -84.5400);
				double scale = 4.7647;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec4D(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});

			tbBlock.AddTest("Vec4D Scalar Div 2", [](float& _fDelta) -> const bool {
				Vec4D vec(640.0216, 599.3427, -31.3702, -46.6410);
				double scale = 8.6124;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = scale / vec, _fDelta);

				return vRes == Vec4D(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});

			tbBlock.AddTest("Vec4D Scalar Div 3", [](float& _fDelta) -> const bool {
				Vec4D vec(826.0256, 312.1744, 54.1705, -26.6897);
				double scale = 3.4540;
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec / scale, _fDelta);

				return vRes == Vec4D(vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale);
			});
		}

		//Misc Operators
		{
			tbBlock.AddTest("Vec4D Zero", [](float& _fDelta) -> const bool {
				Vec4D vec(1.0, 2.0, 3.0, 4.0);

				HC_TIME_EXECUTION(vec = ~vec, _fDelta);

				return vec == Vec4D();
			});

			tbBlock.AddTest("Vec4D Negate", [](float& _fDelta) -> const bool {
				Vec4D vec(1.0, 2.0, 3.0, 4.0);

				HC_TIME_EXECUTION(vec = -vec, _fDelta);

				return vec == Vec4D(-1.0, -2.0, -3.0, -4.0);
			});
		}

		//Functions
		{
			tbBlock.AddTest("Vec4D Min 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(51.1165, 42.3195, 49.7369, -75.3150);
				Vec4D vec2(39.1151, 59.8660, -28.4884, -28.7055);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec4D(39.1151, 42.3195, -28.4884, -75.3150);
			});

			tbBlock.AddTest("Vec4D Min 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(28.7146, 41.3594, 97.7016, -54.7634);
				Vec4D vec2(76.2211, 68.4067, -1.3772, -56.6137);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec4D(28.7146, 41.3594, -1.3772, -56.6137);
			});

			tbBlock.AddTest("Vec4D Min 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(8.0429, 40.1981, -59.5477, -93.4670);
				Vec4D vec2(16.0625, 83.4853, 14.7856, 49.5655);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Min(vec1, vec2), _fDelta);

				return vRes == Vec4D(8.0429, 40.1981, -59.5477, -93.4670);
			});

			tbBlock.AddTest("Vec4D Max 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(96.7911, 64.2846, -35.3075, -46.9703);
				Vec4D vec2(30.4101, 11.5474, 64.8257, 73.8171);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec4D(96.7911, 64.2846, 64.8257, 73.8171);
			});

			tbBlock.AddTest("Vec4D Max 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(16.2844, 32.5915, 72.0709, 84.0965);
				Vec4D vec2(45.5970, 41.9927, 78.8099, -39.0389);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec4D(45.5970, 41.9927, 78.8099, 84.0965);
			});

			tbBlock.AddTest("Vec4D Max 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(72.7684, 93.9137, 85.4258, -18.2931);
				Vec4D vec2(30.2332, 19.2606, 99.2068, 84.1347);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Max(vec1, vec2), _fDelta);

				return vRes == Vec4D(72.7684, 93.9137, 99.2068, 84.1347);
			});

			tbBlock.AddTest("Vec4D Sum 1", [](float& _fDelta) -> const bool {
				Vec4D vec(78.0600, 87.2512, 17.4745, -38.9328);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z + vec.w;
			});

			tbBlock.AddTest("Vec4D Sum 2", [](float& _fDelta) -> const bool {
				Vec4D vec(97.3376, 78.5648, -72.4875, 96.3222);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z + vec.w;
			});

			tbBlock.AddTest("Vec4D Sum 3", [](float& _fDelta) -> const bool {
				Vec4D vec(57.8870, 81.7546, -56.3297, -40.1260);
				double dRes;

				HC_TIME_EXECUTION(dRes = Sum(vec), _fDelta);

				return dRes == vec.x + vec.y + vec.z + vec.w;
			});

			tbBlock.AddTest("Vec4D Dot 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(26.8330, 70.8067, 94.4725, -11.0555);
				Vec4D vec2(79.1302, 60.2868, 38.1920, -27.3375);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Dot 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(86.4119, 47.2965, 55.8695, 39.9468);
				Vec4D vec2(20.8300, 16.3871, -65.5612, 87.4098);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Dot 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(91.6068, 54.0450, -8.8122, -75.5348);
				Vec4D vec2(30.6695, 92.2011, -60.2328, -22.4749);
				double dRes;

				HC_TIME_EXECUTION(dRes = Dot(vec1, vec2), _fDelta);

				return dRes == (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Length 1", [](float& _fDelta) -> const bool {
				Vec4D vec(9.4654, 17.3159, -65.7723, 50.5322);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Length 2", [](float& _fDelta) -> const bool {
				Vec4D vec(60.8574, 49.0449, -73.1398, 76.4660);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Length 3", [](float& _fDelta) -> const bool {
				Vec4D vec(65.8412, 59.2604, 83.9684, 37.5298);
				double dRes;

				HC_TIME_EXECUTION(dRes = Length(vec), _fDelta);

				return dRes == sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Length Squared 1", [](float& _fDelta) -> const bool {
				Vec4D vec(43.9689, 96.0509, 88.9848, 92.2607);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Length Squared 2", [](float& _fDelta) -> const bool {
				Vec4D vec(53.1229, 66.8357, -1.5535, 4.8029);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Length Squared 3", [](float& _fDelta) -> const bool {
				Vec4D vec(28.9374, 1.0988, 49.2252, -87.9614);
				double dRes;

				HC_TIME_EXECUTION(dRes = LengthSquared(vec), _fDelta);

				return dRes == (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			});

			tbBlock.AddTest("Vec4D Normalize 1", [](float& _fDelta) -> const bool {
				Vec4D vec(74.2584, 69.7548, 41.2219, 79.8498);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec4D Normalize 2", [](float& _fDelta) -> const bool {
				Vec4D vec(37.8081, 90.8517, -26.2088, -74.4120);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec4D Normalize 3", [](float& _fDelta) -> const bool {
				Vec4D vec(52.8772, 94.8309, 31.6384, -30.9328);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Normalize(vec), _fDelta);

				return vRes == vec / Length(vec);
			});

			tbBlock.AddTest("Vec4D Angle Between 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(89.6417, 79.4191, 22.7910, -21.0206);
				Vec4D vec2(1.4510, 0.0928, -27.6698, 29.4491);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Angle Between 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(91.8041, 90.4006, 9.4439, 84.1371);
				Vec4D vec2(6.7411, 43.1172, 56.0758, 21.6438);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Angle Between 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(69.2061, 74.7766, -6.6671, -60.0610);
				Vec4D vec2(56.8069, 54.0597, -91.8969, -80.2745);
				double dRes;

				vec1 = Normalize(vec1);
				vec2 = Normalize(vec2);

				HC_TIME_EXECUTION(dRes = AngleBetween(vec1, vec2), _fDelta);

				return dRes == acos(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
			});

			tbBlock.AddTest("Vec4D Cross 1", [](float& _fDelta) -> const bool {
				Vec4D vec1(-97.2270, 38.6223, -28.2738, -69.2833);
				Vec4D vec2(86.0807, 1.9667, -94.1717, -89.0293);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec4D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});

			tbBlock.AddTest("Vec4D Cross 2", [](float& _fDelta) -> const bool {
				Vec4D vec1(23.5460, 38.0488, 17.8359, 92.2378);
				Vec4D vec2(-42.1373, -70.5776, -33.3752, 56.0375);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = vec1 ^ vec2, _fDelta);

				return vRes == Vec4D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});

			tbBlock.AddTest("Vec4D Cross 3", [](float& _fDelta) -> const bool {
				Vec4D vec1(13.7789, 88.7826, -27.1393, 85.2095);
				Vec4D vec2(-13.9210, -42.339, 54.9631, -48.7205);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Cross(vec1, vec2), _fDelta);

				return vRes == Vec4D(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x, vec1.w);
			});

			tbBlock.AddTest("Vec4D Abs 1", [](float& _fDelta) -> const bool {
				Vec4D vec(96.5146, -61.7155, -9.8896, -71.1936);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec4D(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});

			tbBlock.AddTest("Vec4D Abs 2", [](float& _fDelta) -> const bool {
				Vec4D vec(1.7028, -53.4726, 65.2977, -84.0155);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec4D(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});

			tbBlock.AddTest("Vec4D Abs 3", [](float& _fDelta) -> const bool {
				Vec4D vec(-86.6360, -7.9589, -58.1190, -12.8462);
				Vec4D vRes;

				HC_TIME_EXECUTION(vRes = Abs(vec), _fDelta);

				return vRes == Vec4D(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
			});
		}

		_vBlockList.push_back(tbBlock);
#pragma endregion

		//MatrixF/D
#pragma region Matrix
		//tbBlock = TestBlock("Math Library - MatrixF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - MatrixD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//QuaternionF/D
#pragma region Quaternion
		//tbBlock = TestBlock("Math Library - QuaternionF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - QuaternionD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//RotorF/D
#pragma region Rotor
		//tbBlock = TestBlock("Math Library - RotorF");
		//
		//_vBlockList.push_back(tbBlock);
		//
		//tbBlock = TestBlock("Math Library - RotorD");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion

		//Random
#pragma region Random
		tbBlock = TestBlock("Math Library - Random");
		
		tbBlock.AddTest("Random Set Seed Timing", [](float& _fDelta) -> const bool {
			Random rand;

			HC_TIME_EXECUTION(rand.SetSeed(999999), _fDelta);

			return true;
		});

		tbBlock.AddTest("Random Generate Char 1", [](float& _fDelta) -> const bool {
			Random rand;
			char cRes;

			HC_TIME_EXECUTION(cRes = rand.GenerateChar(-32, 64), _fDelta);

			return cRes >= -32 && cRes < 64;
		});

		tbBlock.AddTest("Random Generate Char 2", [](float& _fDelta) -> const bool {
			Random rand;
			char cRes;

			HC_TIME_EXECUTION(cRes = rand.GenerateChar(0, 64), _fDelta);

			return cRes >= 0 && cRes < 64;
		});

		tbBlock.AddTest("Random Generate Char 3", [](float& _fDelta) -> const bool {
			Random rand;
			char cRes;

			HC_TIME_EXECUTION(cRes = rand.GenerateChar(-64, 32), _fDelta);

			return cRes >= -64 && cRes < 32;
		});

		tbBlock.AddTest("Random Generate Short 1", [](float& _fDelta) -> const bool {
			Random rand;
			short sRes;

			HC_TIME_EXECUTION(sRes = rand.GenerateShort(-32, 64), _fDelta);

			return sRes >= -32 && sRes < 64;
		});

		tbBlock.AddTest("Random Generate Short 2", [](float& _fDelta) -> const bool {
			Random rand;
			short sRes;

			HC_TIME_EXECUTION(sRes = rand.GenerateShort(0, 64), _fDelta);

			return sRes >= 0 && sRes < 64;
		});

		tbBlock.AddTest("Random Generate Short 3", [](float& _fDelta) -> const bool {
			Random rand;
			short sRes;

			HC_TIME_EXECUTION(sRes = rand.GenerateShort(-64, 32), _fDelta);

			return sRes >= -64 && sRes < 32;
		});

		tbBlock.AddTest("Random Generate Int 1", [](float& _fDelta) -> const bool {
			Random rand;
			int iRes;

			HC_TIME_EXECUTION(iRes = rand.GenerateInt(-32, 64), _fDelta);

			return iRes >= -32 && iRes < 64;
		});

		tbBlock.AddTest("Random Generate Int 2", [](float& _fDelta) -> const bool {
			Random rand;
			int iRes;

			HC_TIME_EXECUTION(iRes = rand.GenerateInt(0, 64), _fDelta);

			return iRes >= 0 && iRes < 64;
		});

		tbBlock.AddTest("Random Generate Int 3", [](float& _fDelta) -> const bool {
			Random rand;
			int iRes;

			HC_TIME_EXECUTION(iRes = rand.GenerateInt(-64, 32), _fDelta);

			return iRes >= -64 && iRes < 32;
		});

		tbBlock.AddTest("Random Generate Unsigned Int 1", [](float& _fDelta) -> const bool {
			Random rand;
			uint32_t u32Res;

			HC_TIME_EXECUTION(u32Res = rand.GenerateUnsignedInt(32, 64), _fDelta);

			return u32Res >= 32 && u32Res < 64;
		});

		tbBlock.AddTest("Random Generate Unsigned Int 2", [](float& _fDelta) -> const bool {
			Random rand;
			uint32_t u32Res;

			HC_TIME_EXECUTION(u32Res = rand.GenerateUnsignedInt(0, 64), _fDelta);

			return u32Res >= 0 && u32Res < 64;
		});

		tbBlock.AddTest("Random Generate Unsigned Int 3", [](float& _fDelta) -> const bool {
			Random rand;
			uint32_t u32Res;

			HC_TIME_EXECUTION(u32Res = rand.GenerateUnsignedInt(16, 32), _fDelta);

			return u32Res >= 16 && u32Res < 32;
		});

		tbBlock.AddTest("Random Generate Long 1", [](float& _fDelta) -> const bool {
			Random rand;
			long lRes;

			HC_TIME_EXECUTION(lRes = rand.GenerateLong(-32, 64), _fDelta);

			return lRes >= -32 && lRes < 64;
		});

		tbBlock.AddTest("Random Generate Long 2", [](float& _fDelta) -> const bool {
			Random rand;
			long lRes;

			HC_TIME_EXECUTION(lRes = rand.GenerateLong(0, 64), _fDelta);

			return lRes >= 0 && lRes < 64;
		});

		tbBlock.AddTest("Random Generate Long 3", [](float& _fDelta) -> const bool {
			Random rand;
			long lRes;

			HC_TIME_EXECUTION(lRes = rand.GenerateLong(-64, 32), _fDelta);

			return lRes >= -64 && lRes < 32;
		});

		tbBlock.AddTest("Random Generate Float 1", [](float& _fDelta) -> const bool {
			Random rand;
			float fRes;

			HC_TIME_EXECUTION(fRes = rand.GenerateFloat(-32.0f, 64.0f), _fDelta);

			return fRes >= -32.0f && fRes < 64.0f;
		});

		tbBlock.AddTest("Random Generate Float 2", [](float& _fDelta) -> const bool {
			Random rand;
			float fRes;

			HC_TIME_EXECUTION(fRes = rand.GenerateFloat(0.0f, 64.0f), _fDelta);

			return fRes >= 0.0f && fRes < 64.0f;
		});

		tbBlock.AddTest("Random Generate Float 3", [](float& _fDelta) -> const bool {
			Random rand;
			float fRes;

			HC_TIME_EXECUTION(fRes = rand.GenerateFloat(-64.0f, 32.0f), _fDelta);

			return fRes >= -64.0f && fRes < 32.0f;
		});

		tbBlock.AddTest("Random Generate Double 1", [](float& _fDelta) -> const bool {
			Random rand;
			double dRes;

			HC_TIME_EXECUTION(dRes = rand.GenerateDouble(-32.0, 64.0), _fDelta);

			return dRes >= -32.0 && dRes < 64.0;
		});

		tbBlock.AddTest("Random Generate Double 2", [](float& _fDelta) -> const bool {
			Random rand;
			double dRes;

			HC_TIME_EXECUTION(dRes = rand.GenerateDouble(0.0, 64.0), _fDelta);

			return dRes >= 0.0 && dRes < 64.0;
		});

		tbBlock.AddTest("Random Generate Double 3", [](float& _fDelta) -> const bool {
			Random rand;
			double dRes;

			HC_TIME_EXECUTION(dRes = rand.GenerateDouble(-64.0, 32.0), _fDelta);

			return dRes >= -64.0 && dRes < 32.0;
		});

		_vBlockList.push_back(tbBlock);
#pragma endregion

		//Math
#pragma region Math
		//tbBlock = TestBlock("Math Library - Misc");
		//
		//_vBlockList.push_back(tbBlock);
#pragma endregion
	}
}
