#pragma once

#include <Platform/OSCommon.hpp>
#include <HellfireControl/Math/Internal/Vector/Vector2_F.hpp>


#include <HellfireControl/Core/Window.hpp> //FIXME: Remove from this file and make generic callback system.


namespace PlatformWindow {
	/// <summary>
	/// Initializes a window from the given inputs and writes the new window handle to the given,
	/// presumed empty, handle variable.
	/// </summary>
	/// <param name="_u64OutHandle: An unsigned 64 bit integer representing the window handle"></param>
	/// <param name="_u8Type: An unsigned 8 bit integer representing the window type"></param>
	/// <param name="_strName: The name to be displayed at the top of the window"></param>
	/// <param name="_v2Size: A vector2 representing the size of the window in pixels"></param>
	/// <param name="_v2Loc: A vector2 representing the location of the window in pixels"></param>
	void InitWindow(uint64_t& _u64OutHandle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc);

	/// <summary>
	/// Registers the wrapper callbacks with the platform-specific callbacks. Must be called after InitWindow.
	/// </summary>
	void RegisterWindowCallbacks(uint64_t _u64Handle, std::vector<WindowCallback>*& _pOutWindowCallbacks);

	/// <summary>
	/// Determines if the window represented by the handle has requested it be closed from the user.
	/// </summary>
	/// <param name="_u64Handle: The handle to the window being tested for closing"></param>
	/// <returns>
	/// bool: True if a window close was requested, false otherwise.
	/// </returns>
	[[nodiscard]] bool CloseRequested(uint64_t _u64Handle);

	/// <summary>
	/// Polls the event queue for the window reprenseted by the handle and processes all messages in it.
	/// </summary>
	/// <param name="_u64Handle: Handle to the window whose events must be processed"></param>
	void PollEventQueue(uint64_t _u64Handle);

	/// <summary>
	/// Waits until the event queue spits out a new event.
	/// </summary>
	/// <param name="_u64Handle: The handle to the window being polled"></param>
	void WaitEvents(uint64_t _u64Handle);

	/// <summary>
	/// Sets the name of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <param name="_strName: The name to be set within the window"></param>
	/// <returns>
	/// bool: True if succeeded, false if failed
	/// </returns>
	[[nodiscard]] bool SetWindowName(uint64_t _u64Handle, const std::string& _strName);

	/// <summary>
	/// Sets the style of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <param name="_u8Type: The style to be set within the window"></param>
	/// <returns>
	/// bool: True if succeeded, false if failed
	/// </returns>
	[[nodiscard]] bool SetWindowStyleParameters(uint64_t _u64Handle, uint8_t _u8Type);

	/// <summary>
	/// Sets the size of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <param name="_v2Size: The size to be set within the window"></param>
	/// <returns>
	/// bool: True if succeeded, false if failed
	/// </returns>
	[[nodiscard]] bool SetWindowSize(uint64_t _u64Handle, const Vec2F& _v2Size);

	/// <summary>
	/// Sets the location of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <param name="_v2Loc: The location to be set within the window"></param>
	/// <returns>
	/// bool: True if succeeded, false if failed
	/// </returns>
	[[nodiscard]] bool SetWindowLocation(uint64_t _u64Handle, const Vec2F& _v2Loc);

	/// <summary>
	/// Sets the window represented by the handle as the focus.
	/// </summary>
	/// <param name="_u64Handle: A handle to the window set to be the focus"></param>
	[[nodiscard]] void SetWindowFocus(uint64_t _u64Handle);

	/// <summary>
	/// Returns the up-to-date size of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <returns>
	/// Vec2F: The current size of the window in pixels
	/// </returns>
	[[nodiscard]] Vec2F GetWindowSize(uint64_t _u64Handle);

	/// <summary>
	/// Returns the up-to-date location of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	/// <returns>
	/// Vec2F: The current location of the window
	/// </returns>
	[[nodiscard]] Vec2F GetWindowLocation(uint64_t _u64Handle);

	/// <summary>
	/// Returns the up-to-date parameters of the window represented by the given handle.
	/// </summary>
	/// <param name="_u64Handle"></param>
	/// <returns>
	/// uint8_t: The current parameters of the window represented by the given handle.
	/// </returns>
	[[nodiscard]] uint8_t GetWindowParameters(uint64_t _u64Handle);

	/// <summary>
	/// Determines if the window represented by the given handle is the current focus.
	/// </summary>
	/// <param name="_u64Handle: A handle to the window that must be checked for focus"></param>
	/// <returns></returns>
	[[nodiscard]] bool GetWindowFocus(uint64_t _u64Handle);

	/// <summary>
	/// Cleans up the window represented by the given handle
	/// </summary>
	/// <param name="_u64Handle: An unsigned 64 bit integer representing the window handle"></param>
	[[nodiscard]] void CleanupWindow(uint64_t _u64Handle);
}