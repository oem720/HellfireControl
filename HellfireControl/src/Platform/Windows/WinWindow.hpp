#pragma once

#include <Platform/OSCommon.hpp>
#include <HellfireControl/Math/Internal/Vector/Vector2_F.hpp>

namespace PlatformWindow {
	void InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc);

	[[nodiscard]] bool SetWindowName(uint64_t _u64Handle, const std::string& _strName);

	[[nodiscard]] bool SetWindowStyleParameters(uint64_t _u64Handle, uint8_t _u8Type);

	[[nodiscard]] bool SetWindowSize(uint64_t _u64Handle, const Vec2F& _v2Size);

	[[nodiscard]] bool SetWindowLocation(uint64_t _u64Handle, const Vec2F& _v2Loc);

	[[nodiscard]] Vec2F GetWindowSize(uint64_t _u64Handle);

	[[nodiscard]] Vec2F GetWindowLocation(uint64_t _u64Handle);

	[[nodiscard]] uint8_t GetWindowParameters(uint64_t _u64Handle);

	[[nodiscard]] void CleanupWindow(uint64_t _u64Handle);
}