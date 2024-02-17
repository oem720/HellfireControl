#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>
#include <HellfireControl/Core/File.hpp>

#define HC_TIME_EXECUTION(func, delta) auto tStart = std::chrono::high_resolution_clock::now(); func; auto tEnd = std::chrono::high_resolution_clock::now(); delta = std::chrono::duration<float, std::nano>(tEnd - tStart).count()

namespace Util {
	void PauseForUserConfirmation();

	void Wait(uint64_t _u32Time);
}