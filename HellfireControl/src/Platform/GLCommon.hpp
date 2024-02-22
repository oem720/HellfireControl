#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>

#if HC_USE_VULKAN && !HC_USE_OPENGL

#if WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define HC_MAX_FRAMES_IN_FLIGHT 2

#include <vulkan/vulkan.h>

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif