#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Quaternion(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - QuaternionF");

		//Construction
		{
			tbBlock.AddTest("QuaternionF Construct From Yaw Pitch Roll 1", [](float& _fDelta) -> const bool {
				float fYaw = 0.0f;
				float fPitch = 0.0f;
				float fRoll = 0.0f;

				HC_TIME_EXECUTION(QuaternionF quatRes(fRoll, fPitch, fYaw), _fDelta);

				return quatRes == QuaternionF();
			});

			tbBlock.AddTest("QuaternionF Construct From Yaw Pitch Roll 2", [](float& _fDelta) -> const bool {
				float fYaw = 0.0f;
				float fPitch = 0.0f;
				float fRoll = 0.0f;

				HC_TIME_EXECUTION(QuaternionF quatRes(fRoll, fPitch, fYaw), _fDelta);

				return quatRes == QuaternionF();
			});

			tbBlock.AddTest("QuaternionF Construct From Yaw Pitch Roll 3", [](float& _fDelta) -> const bool {
				float fYaw = 0.0f;
				float fPitch = 0.0f;
				float fRoll = 0.0f;

				HC_TIME_EXECUTION(QuaternionF quatRes(fRoll, fPitch, fYaw), _fDelta);

				return quatRes == QuaternionF();
			});
		}

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - QuaternionD");

		//Construction
		{

		}

		_vBlockList.push_back(tbBlock);
	}
}