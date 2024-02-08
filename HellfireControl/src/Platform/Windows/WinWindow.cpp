
#include <Platform/Windows/WinWindow.hpp>

#include <HellfireControl/Util/Util.hpp>

#define HC_WINDOW_CLASS "HCE"

namespace PlatformWindow {
	struct Win32WindowData {
		int m_iX;
		int m_iY;
		int m_iWidth;
		int m_iHeight;
		uint8_t m_u8Style;
	};

	struct Win32Globals {
		bool g_bWindowClassRegistered = false;
		std::map<HWND, Win32WindowData> g_mapWindowData;
		HINSTANCE g_hiInstance;
	};

	static Win32Globals g_LocalData = {};

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_SIZE: {
			int iWidth = LOWORD(lParam);
			int iHeight = HIWORD(lParam);

			g_LocalData.g_mapWindowData[hwnd].m_iWidth = iWidth;
			g_LocalData.g_mapWindowData[hwnd].m_iHeight = iHeight;
		} break;
		case WM_MOVE: {
			int iX = LOWORD(lParam);
			int iY = HIWORD(lParam);

			g_LocalData.g_mapWindowData[hwnd].m_iX = iX;
			g_LocalData.g_mapWindowData[hwnd].m_iY = iY;
		} break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
			.hbrBackground = NULL,
			.lpszMenuName = NULL,
			.lpszClassName = HC_WINDOW_CLASS
		};

		if (!RegisterClass(&wcClass)) {
			assert(!"ERROR: [Windows Only] Window Class could not be initialized!");
		}

		g_LocalData.g_bWindowClassRegistered = true;
	}

	void DeregisterWindowClass() {
		UnregisterClass(HC_WINDOW_CLASS, g_LocalData.g_hiInstance);

		g_LocalData.g_bWindowClassRegistered = false;
	}

	void InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc){
		if (!g_LocalData.g_bWindowClassRegistered) {
			InitWindowClass();
		}

		HWND hwndWindowHandle = CreateWindowEx(
			0,
			HC_WINDOW_CLASS, //Class
			_strName.c_str(), //Name
			WS_OVERLAPPEDWINDOW, //TODO Add window style translation here

			static_cast<int>(_v2Loc.x), static_cast<int>(_v2Loc.y), 
			static_cast<int>(_v2Size.x), static_cast<int>(_v2Size.y),

			NULL,
			NULL,
			g_LocalData.g_hiInstance,
			NULL
		);

		if (hwndWindowHandle == NULL) {
			assert(!"ERROR: Window failed to create!");
		}

		ShowWindow(hwndWindowHandle, 1);

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
		return false;
	}

	bool SetWindowStyleParameters(uint64_t _u64Handle, uint8_t _u8Type) {
		return false;
	}

	bool SetWindowSize(uint64_t _u64Handle, const Vec2F& _v2Size) {
		return false;
	}

	bool SetWindowLocation(uint64_t _u64Handle, const Vec2F& _v2Loc) {
		return false;
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
		//TODO Proper cleanup procedure

		g_LocalData.g_mapWindowData.erase(reinterpret_cast<HWND>(_u64Handle)); //Delete local data for this window instance.

		if (g_LocalData.g_mapWindowData.empty()) {
			DeregisterWindowClass(); //Deregister the window class, as we have no windows currently using it. Any new windows will need to recreate the class.
		}
	}
}