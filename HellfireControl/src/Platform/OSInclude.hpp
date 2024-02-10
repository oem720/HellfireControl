#pragma once

#if defined(WIN32) || defined(_WIN32)

#ifdef HC_INCLUDE_CONSOLE
#include <Platform/Windows/WinConsole.hpp>
#endif

#ifdef HC_INCLUDE_WINDOW
#include <Platform/Windows/WinWindow.hpp>
#endif

#elif defined(__APPLE__)

#ifdef HC_INCLUDE_CONSOLE
#include <Platform/Mac/MacTerminal.hpp>
#endif

#ifdef HC_INCLUDE_WINDOW
#include <Platform/Mac/MacWindow.hpp>
#endif

#else

#endif