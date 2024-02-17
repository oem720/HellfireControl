#pragma once

#include <HellfireControl/Core/Common.hpp>

#if HC_USE_VULKAN && !HC_USE_OPENGL

#if WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.h>

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif