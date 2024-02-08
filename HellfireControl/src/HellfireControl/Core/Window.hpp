#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>

typedef uint64_t WindowHandleGeneric;

enum WindowType : uint8_t {
	WINDOWED,
	WINDOWED_FULLSCREEN,
	BORDERLESS,
	FULLSCREEN
};

class Window {
private:
	/// <summary>
	/// Handle to the OS-specific window object.
	/// </summary>
	WindowHandleGeneric m_whgHandle = 0;

	/// <summary>
	/// Type of window we are managing.
	/// </summary>
	WindowType m_wtType;

	/// <summary>
	/// Name of the window to be displayed.
	/// </summary>
	std::string m_strWindowName;

	/// <summary>
	/// Window dimensions.
	/// </summary>
	Vec2F m_v2WindowSize;

	/// <summary>
	/// Location of the window on screen.
	/// </summary>
	Vec2F m_v2WindowLocation;

	/// <summary>
	/// Helper function to initialize the window.
	/// </summary>
	void InitWindow();

	/// <summary>
	/// Helper function to request all low-level data from OS.
	/// </summary>
	void UpdateWindowData();

	/// <summary>
	/// Helper function to request only the up-to-date window size from OS.
	/// </summary>
	void UpdateWindowSize();

	/// <summary>
	/// Helper function to request only the up-to-date window location from OS.
	/// </summary>
	void UpdateWindowLocation();

	/// <summary>
	/// Helper function to request only the up-to-date window type from OS (only useful in windowed, non-borderless modes).
	/// </summary>
	void UpdateWindowType();
public:
	/// <summary>
	/// By default, this inits the window to have the name Hellfire Control Engine and the type of Windowed.
	/// Location and size are defaulted to 0, 0 and 800x400 respectively
	/// Name could be omitted and left to cascade down from Application, however, leaving the ability to
	/// set window name at any time is useful for special in-game effects.
	/// </summary>
	Window() : m_strWindowName("Hellfire Control Engine"), m_wtType(WindowType::WINDOWED), m_v2WindowSize(800, 400), m_v2WindowLocation(0, 0) {
		InitWindow();
	}

	/// <summary>
	/// Generate a window of a giving name and given type.
	/// </summary>
	/// <param name="_strName: The name of the window"></param>
	/// <param name="_wtType: The type of the window"></param>
	/// <param name="_v2Size: The size of the window (Default: 800x400)"></param>
	/// <param name="_v2Loc: The location of the window (Default: [0, 0])"></param>
	explicit Window(std::string _strName, WindowType _wtType, const Vec2F& _v2Size, const Vec2F& _v2Loc) : m_strWindowName(_strName), m_wtType(_wtType),
	m_v2WindowSize(_v2Size), m_v2WindowLocation(_v2Loc) {
		InitWindow();
	}

	/// <summary>
	/// Transfer constrol of an existing window to this instance. This is typically used
	/// for transferring control of the console to this application.
	/// </summary>
	/// <param name="_whgPreexisting: Handle to the existing window"></param>
	explicit Window(WindowHandleGeneric _whgPreexisting) : m_whgHandle(_whgPreexisting) {
		UpdateWindowData();
	}

	/// <summary>
	/// Cleans all OS Memory and destroys current window.
	/// </summary>
	void CleanupWindow();

	/// <summary>
	/// Set the name of the window.
	/// </summary>
	/// <param name="_strName: New name for the window"></param>
	/// <returns>
	/// bool: Confirmation of successful name change
	/// </returns>
	bool SetWindowName(const std::string& _strName);

	/// <summary>
	/// Set the type of the window.
	/// </summary>
	/// <param name="_wtType: New type for the window"></param>
	/// <returns>
	/// bool: Confirmation of successful type change
	/// </returns>
	bool SetWindowType(WindowType _wtType);

	/// <summary>
	/// Set the size of the window.
	/// </summary>
	/// <param name="_v2Size: New size for the window"></param>
	/// <returns>
	/// bool: Confirmation of successful size change
	/// </returns>
	bool SetWindowSize(const Vec2F& _v2Size);

	/// <summary>
	/// Set the location for the window.
	/// </summary>
	/// <param name="_v2Loc: New location for the window"></param>
	/// <returns>
	/// bool: Confirmation of successful location change
	/// </returns>
	bool SetWindowLocation(const Vec2F& _v2Loc);

	/// <summary>
	/// Get the window's current name.
	/// </summary>
	/// <returns>
	/// string: The current window name
	/// </returns>
	[[nodiscard]] HC_INLINE std::string GetWindowName() const { return m_strWindowName; }

	/// <summary>
	/// Get the window's current type.
	/// </summary>
	/// <returns>
	/// WindowType: The current window type
	/// </returns>
	[[nodiscard]] HC_INLINE WindowType GetWindowType() {
		if (m_wtType == WindowType::WINDOWED || m_wtType == WindowType::WINDOWED_FULLSCREEN) {
			UpdateWindowType();
		}

		return m_wtType; 
	}

	/// <summary>
	/// Get the window's current size.
	/// </summary>
	/// <returns>
	/// Vec2F: The current window size
	/// </returns>
	[[nodiscard]] HC_INLINE Vec2F GetWindowSize() {
		if (m_wtType == WindowType::WINDOWED || m_wtType == WindowType::WINDOWED_FULLSCREEN) {
			UpdateWindowSize();
		}

		return m_v2WindowSize;
	}

	/// <summary>
	/// Get the window's current location.
	/// </summary>
	/// <returns>
	/// Vec2F: The current window location
	/// </returns>
	[[nodiscard]] HC_INLINE Vec2F GetWindowLocation() {
		if (m_wtType == WindowType::WINDOWED || m_wtType == WindowType::WINDOWED_FULLSCREEN) {
			UpdateWindowLocation();
		}

		return m_v2WindowLocation;
	}
};