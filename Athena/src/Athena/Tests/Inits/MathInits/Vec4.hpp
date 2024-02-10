#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Vec4(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - Vec4F");

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
				Vec4F vec1(212.0f, 63.002f, 16.5280f, -32.6626f);
				Vec4F vec2(212.0f, 63.002f, 16.5280f, -32.6626f);
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
	}
}