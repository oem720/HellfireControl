#pragma once

#include <HellfireControl/Core/Common.hpp>

#if HC_USE_VULKAN && !HC_USE_OPENGL

#include <vulkan/vulkan.h>

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif