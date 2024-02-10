#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Random(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - Random");

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
	}
}