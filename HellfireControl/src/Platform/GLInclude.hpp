#pragma once

#if HC_USE_VULKAN && !HC_USE_OPENGL

#include <Platform/Vulkan/VkCore.hpp>

#ifdef HC_INCLUDE_BUFFER
#include <Platform/Vulkan/VkBuffer.hpp>
#endif

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif