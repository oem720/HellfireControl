#pragma once

#include <Platform/OSCommon.hpp>
#include <HellfireControl/Math/Vector.hpp>

namespace PlatformWindow {
	void InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc);


}