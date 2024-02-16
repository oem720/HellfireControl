
#include <Platform/Windows/WinWindow.hpp>

#include <HellfireControl/Util/Util.hpp>

#include <stdexcept>

#define HC_WINDOW_CLASS L"HCE"

namespace PlatformWindow {
	struct Win32WindowData {
		int m_iX;
		int m_iY;
		int m_iWidth;
		int m_iHeight;
		uint8_t m_u8Style;
	};

	struct Win32Globals {
		HINSTANCE g_hiInstance;

		bool g_bWindowClassRegistered = false;
		bool g_bFullscreen = false;

		std::map<HWND, Win32WindowData> g_mapWindowData;
	};

	static Win32Globals g_LocalData = {};

	LONG TranslateWindowStyle(uint8_t _u8Style) {
		LONG lVal = 0;

		switch (_u8Style) {
		case 0: { //Windowed
			lVal = WS_OVERLAPPEDWINDOW;
		} break;
		case 1: { //Windowed_Fullscreen
			lVal = WS_OVERLAPPEDWINDOW | WS_MAXIMIZE;
		} break;
		case 2: { //Borderless
			lVal = WS_POPUP | WS_MAXIMIZE;
		} break;
		case 3: { //Fullscreen
			lVal = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		} break;
		}

		return lVal;
	}

	void EnterFullscreen(int _iWidth, int _iHeight) {
		DEVMODE dmSettings = {};

		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings)) {
			throw std::runtime_error("ERROR: Failed to enumerate settings!");
		}

		dmSettings.dmPelsWidth = _iWidth;
		dmSettings.dmPelsHeight = _iHeight;
		dmSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			throw std::runtime_error("ERROR: Display resolution incompatible!");
		}

		g_LocalData.g_bFullscreen = true;
	}

	void ExitFullscreen() {
		ChangeDisplaySettings(NULL, 0);

		g_LocalData.g_bFullscreen = false;
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_WINDOWPOSCHANGED: {
			WINDOWPOS* pWindowPos = reinterpret_cast<WINDOWPOS*>(lParam);

			g_LocalData.g_mapWindowData[hwnd].m_iX = pWindowPos->x;
			g_LocalData.g_mapWindowData[hwnd].m_iY = pWindowPos->y;
			g_LocalData.g_mapWindowData[hwnd].m_iWidth = pWindowPos->cx;
			g_LocalData.g_mapWindowData[hwnd].m_iHeight = pWindowPos->cy;

			return 0;
		} break;
		case WM_CLOSE: {
			CleanupWindow(reinterpret_cast<uint64_t>(hwnd));

			return 0;
		} break;
		default: {
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		}
	}

	void InitWindowClass() {
		g_LocalData.g_hiInstance = GetModuleHandle(NULL);

		WNDCLASS wcClass = {
			.style = 0,
			.lpfnWndProc = WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = g_LocalData.g_hiInstance,
			.hIcon = NULL, //TODO Add ability to set icon, inititally with a default icon value
			.hCursor = NULL, //TODO Add ability to set cursor, initially with a default cursor value
			.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)),
			.lpszMenuName = NULL,
			.lpszClassName = HC_WINDOW_CLASS
		};

		if (!RegisterClass(&wcClass)) {
			throw std::runtime_error("ERROR: [Windows Only] Window Class could not be initialized!");
		}

		g_LocalData.g_bWindowClassRegistered = true;
	}

	void DeregisterWindowClass() {
		UnregisterClass(HC_WINDOW_CLASS, g_LocalData.g_hiInstance);

		g_LocalData.g_bWindowClassRegistered = false;
	}

	void InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc) {
		if (!g_LocalData.g_bWindowClassRegistered) {
			InitWindowClass();
		}

		HWND hwndWindowHandle = CreateWindowEx(
			0,
			HC_WINDOW_CLASS,							//Class
			Util::ConvertToWString(_strName).c_str(),	//Name
			TranslateWindowStyle(_u8Type),

			static_cast<int>(_v2Loc.x), static_cast<int>(_v2Loc.y),
			static_cast<int>(_v2Size.x), static_cast<int>(_v2Size.y),

			NULL,
			NULL,
			g_LocalData.g_hiInstance,
			NULL
		);

		if (hwndWindowHandle == NULL) {
			throw std::runtime_error("ERROR: Window failed to create!");
		}

		if (_u8Type == 3) { //If in fullscreen mode, call the fullscreen function
			EnterFullscreen(static_cast<int>(_v2Size.x), static_cast<int>(_v2Size.y));
		}

		ShowWindow(hwndWindowHandle, _u8Type == 1 ? 3 : 1); //Only on the Windowed_Fullscreen type do we start fullscreen


		_u64Handle = reinterpret_cast<uint64_t>(hwndWindowHandle); //Assign to our generic handle pointer

		Win32WindowData wwdData = {
			.m_iX = static_cast<int>(_v2Loc.x),
			.m_iY = static_cast<int>(_v2Loc.y),
			.m_iWidth = static_cast<int>(_v2Size.x),
			.m_iHeight = static_cast<int>(_v2Size.y)
		};

		g_LocalData.g_mapWindowData[hwndWindowHandle] = wwdData; //Insert our window data into the structure
	}

	bool SetWindowName(uint64_t _u64Handle, const std::string& _strName) {
		return SetWindowText(reinterpret_cast<HWND>(_u64Handle), Util::ConvertToWString(_strName).c_str());
	}

	bool SetWindowStyleParameters(uint64_t _u64Handle, uint8_t _u8Type) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		bool bSucceeded = SetWindowLongPtr(
			hwnd,							//Handle
			GWL_STYLE,						//We're setting the style here, so use GWL_STYLE
			TranslateWindowStyle(_u8Type)	//The changed value
		);

		bSucceeded = bSucceeded && SetWindowPos(
			hwnd,														//Handle
			NULL,														//Unused
			0,															//Unused
			0,															//Unused
			0,															//Unused
			0,															//Unused
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED	//We are resetting the window, therefore, only FRAMECHANGED is needed, all others must be blocked.
		);

		if (_u8Type == 1) {
			ShowWindow(hwnd, 3); //If and only if we are working with a Windowed_Fullscreen window, reshow the window as maximized
		}

		if (g_LocalData.g_bFullscreen && _u8Type != 3) {
			ExitFullscreen(); //If and only if we are exiting fullscreen
		}

		g_LocalData.g_mapWindowData[hwnd].m_u8Style = _u8Type;

		return bSucceeded; //Returns true if and only if both SetWindowLongPtr and SetWindowPos return true
	}

	bool SetWindowSize(uint64_t _u64Handle, const Vec2F& _v2Size) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		bool bSucceeded = SetWindowPos(
			hwnd,								//Handle
			NULL,								//Unused
			0,									//Unused
			0,									//Unused
			static_cast<int>(_v2Size.x),		//New Width
			static_cast<int>(_v2Size.y),		//New Height
			SWP_NOMOVE | SWP_FRAMECHANGED		//Mark for no location changes and to repaint the screen
		);

		if (bSucceeded) {
			g_LocalData.g_mapWindowData[hwnd].m_iWidth = static_cast<int>(_v2Size.x);
			g_LocalData.g_mapWindowData[hwnd].m_iHeight = static_cast<int>(_v2Size.y);
		}

		return bSucceeded;
	}

	bool SetWindowLocation(uint64_t _u64Handle, const Vec2F& _v2Loc) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		bool bSucceeded = SetWindowPos(
			hwnd,								//Handle
			NULL,								//Unused
			static_cast<int>(_v2Loc.x),			//Unused
			static_cast<int>(_v2Loc.y),			//Unused
			0,									//Unused
			0,									//Unused
			SWP_NOSIZE | SWP_FRAMECHANGED		//Mark for no size changes and to repaint the screen
		);

		if (bSucceeded) {
			g_LocalData.g_mapWindowData[hwnd].m_iX = static_cast<int>(_v2Loc.x);
			g_LocalData.g_mapWindowData[hwnd].m_iY = static_cast<int>(_v2Loc.y);
		}

		return bSucceeded;
	}

	Vec2F GetWindowSize(uint64_t _u64Handle) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		return Vec2F(g_LocalData.g_mapWindowData[hwnd].m_iWidth, g_LocalData.g_mapWindowData[hwnd].m_iHeight);
	}

	Vec2F GetWindowLocation(uint64_t _u64Handle) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		return Vec2F(g_LocalData.g_mapWindowData[hwnd].m_iX, g_LocalData.g_mapWindowData[hwnd].m_iY);
	}

	uint8_t GetWindowParameters(uint64_t _u64Handle) {
		return g_LocalData.g_mapWindowData[reinterpret_cast<HWND>(_u64Handle)].m_u8Style;
	}

	void CleanupWindow(uint64_t _u64Handle) {
		HWND hwnd = reinterpret_cast<HWND>(_u64Handle);

		if (g_LocalData.g_bFullscreen) {
			ExitFullscreen(); //Exit fullscreen and reset the user's resolution.
		}

		if (!DestroyWindow(hwnd)) {
			throw std::runtime_error("ERROR: Window failed to destroy!");
		}

		g_LocalData.g_mapWindowData.erase(hwnd); //Delete local data for this window instance.

		if (g_LocalData.g_mapWindowData.empty()) {
			DeregisterWindowClass(); //Deregister the window class, as we have no windows currently using it. Any new windows will need to recreate the class.
		}
	}
}