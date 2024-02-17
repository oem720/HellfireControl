#pragma once

#if defined(WIN32) || defined(_WIN32)

#ifdef HC_INCLUDE_CONSOLE
#include <Platform/Windows/WinConsole.hpp>
#endif

#ifdef HC_INCLUDE_WINDOW
#include <Platform/Windows/WinWindow.hpp>
#endif

#ifdef HC_INCLUDE_SURFACE_VK
#include <Platform/Windows/WinVkSurface.hpp>
#endif

#else

#endif