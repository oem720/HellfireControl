#pragma once

#include <Platform/OSCommon.hpp>

class WinConsole {
	static bool m_bInit;

	static bool InitConsole();

public:
	friend class Console;
};