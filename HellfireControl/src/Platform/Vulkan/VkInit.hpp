#pragma once

#include <Platform/GLCommon.hpp>

namespace PlatformRenderer {
	void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle);

	void CleanupRenderer();
}