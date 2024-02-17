#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Math/Vector.hpp>

namespace PlatformRenderer {
	void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor = Vec4F());

	void RenderFrame();

	void CleanupRenderer();
}