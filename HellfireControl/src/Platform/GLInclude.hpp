#pragma once

#if HC_USE_VULKAN && !HC_USE_OPENGL

#include <Platform/Vulkan/VkRenderer.hpp>

#include <Platform/Vulkan/VkBuffer.hpp>

#include <Platform/Vulkan/VkRenderContext.hpp>

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif