#pragma once

#include <Platform/GLCommon.hpp>

class PlatformSurface {
public:
	static void CreatePlatformSurface(uint64_t _u64WindowHandle, VkInstance _iInstance, VkSurfaceKHR& _sOutSurface) {
		VkWin32SurfaceCreateInfoKHR sciSurfaceInfo = {
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.pNext = nullptr,
			.flags = 0,
			.hinstance = GetModuleHandle(NULL),
			.hwnd = reinterpret_cast<HWND>(_u64WindowHandle),
		};

		if (vkCreateWin32SurfaceKHR(_iInstance, &sciSurfaceInfo, nullptr, &_sOutSurface) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to initialize a window surface!");
		}
	}
};