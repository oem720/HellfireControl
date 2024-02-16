#pragma once

#include <Platform/GLCommon.hpp>

namespace PlatformRenderer {
	void InitRenderer(const std::string& _strAppName, uint32_t _u32Version);

	void CleanupRenderer();
}