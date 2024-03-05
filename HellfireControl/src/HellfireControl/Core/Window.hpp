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

enum WindowCallbackEventType : uint8_t {
	WINDOW_NONE = 0,
	WINDOW_RESIZE = 1,
	WINDOW_MOVE = 2,
	WINDOW_MAXIMIZE = 4,
	WINDOW_MINIMIZE = 8,
	WINDOW_FOCUSED = 16,
	WINDOW_UNFOCUSED = 32,
	WINDOW_CLOSE = 64,
	WINDOW_MAX = 255
};

struct WindowCallbackMessage {
	/// <summary>
	/// Determines the type of the event message being sent. Changes how the parameters are processed.
	/// </summary>
	WindowCallbackEventType m_wcetType = WINDOW_NONE;

	/// <summary>
	/// Can contain any data for the message that was sent. Determined by the event callback type.
	/// </summary>
	uint64_t upper = 0;
	uint64_t lower = 0;
};

typedef std::function<void(WindowHandleGeneric, const WindowCallbackMessage&)> WindowCallback;

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
	/// List of the callbacks stored within the window.
	/// </summary>
	std::vector<WindowCallback>* m_pWindowEventCallbacks = nullptr;

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
	/// Default constructor is deleted.
	/// </summary>
	Window() : m_strWindowName("DEFAULT"), m_wtType(WINDOWED), m_v2WindowSize(0, 0), m_v2WindowLocation(0, 0) {}

	/// <summary>
	/// Generate a window of a giving name and given type.
	/// </summary>
	/// <param name="_strName: The name of the window"></param>
	/// <param name="_wtType: The type of the window"></param>
	/// <param name="_v2Size: The size of the window (Default: 800x400)"></param>
	/// <param name="_v2Loc: The location of the window (Default: [0, 0])"></param>
	explicit Window(const std::string& _strName, WindowType _wtType, const Vec2F& _v2Size, const Vec2F& _v2Loc) : m_strWindowName(_strName), m_wtType(_wtType),
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
	/// Returns if the user has requested that the close message be sent.
	/// </summary>
	/// <returns>
	/// bool: True if the window must close, false otherwise
	/// </returns>
	[[nodiscard]] bool CloseRequested();

	/// <summary>
	/// Polls events stored in the window.
	/// </summary>
	void PollEvents();

	/// <summary>
	/// Registers the event callback given with the window. Any message that gets processed will be sent to the callback.
	/// </summary>
	/// <param name="_funcCallback: The event callback to be registered"></param>
	void RegisterEventCallback(const WindowCallback& _funcCallback);

	/// <summary>
	/// Waits until a new event comes through the window to update the program again.
	/// </summary>
	void WaitEvents();

	/// <summary>
	/// Cleans all OS Memory and destroys current window.
	/// </summary>
	void Cleanup();

	/// <summary>
	/// Set the name of the window.
	/// </summary>
	/// <param name="_strName: New name for the window"></param>
	void SetWindowName(const std::string& _strName);

	/// <summary>
	/// Set the type of the window.
	/// </summary>
	/// <param name="_wtType: New type for the window"></param>
	void SetWindowType(WindowType _wtType);

	/// <summary>
	/// Set the size of the window.
	/// </summary>
	/// <param name="_v2Size: New size for the window"></param>
	void SetWindowSize(const Vec2F& _v2Size);

	/// <summary>
	/// Set the location for the window.
	/// </summary>
	/// <param name="_v2Loc: New location for the window"></param>
	void SetWindowLocation(const Vec2F& _v2Loc);

	/// <summary>
	/// Set window as the focus for the user's desktop.
	/// </summary>
	void SetWindowFocus();

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

	/// <summary>
	/// Returns the native window handle.
	/// </summary>
	/// <returns>
	/// WindowHandleGeneric: The current window handle
	/// </returns>
	[[nodiscard]] HC_INLINE WindowHandleGeneric GetNativeWindowHandle() { return m_whgHandle; }
	
	/// <summary>
	/// Determines if the window is the current focus.
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] HC_INLINE bool GetWindowFocus();
};