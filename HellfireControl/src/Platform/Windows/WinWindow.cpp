
#include <Platform/Windows/WinWindow.hpp>

#include <HellfireControl/Util/Util.hpp>

#define HC_WINDOW_CLASS "HCE"

namespace PlatformWindow {
	static bool g_bWindowClassRegistered = false;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	}

	void InitWindowClass(HINSTANCE _hInstance) {
		WNDCLASS wcClass = {
			.style = 0,
			.lpfnWndProc = WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = _hInstance,
			.hIcon = NULL, //TODO Add ability to set icon, inititally with a default icon value
			.hCursor = NULL, //TODO Add ability to set cursor, initially with a default cursor value
			.hbrBackground = NULL,
			.lpszMenuName = NULL,
			.lpszClassName = "HCE"
		};

		if (!RegisterClass(&wcClass)) {
			assert(!"ERROR: Window Class could not be initialized!");
		}

		g_bWindowClassRegistered = true;
	}

	void DeregisterWindowClass(HINSTANCE _hInstance) {
		UnregisterClass(HC_WINDOW_CLASS, _hInstance);

		g_bWindowClassRegistered = false;
	}

	void InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc){
		HINSTANCE hInstance = GetModuleHandle(NULL);

		if (!g_bWindowClassRegistered) {
			InitWindowClass(hInstance);
		}

		HWND hwndWindowHandle = CreateWindowEx(
			0, //TODO Add window style translation here
			HC_WINDOW_CLASS, //Class
			_strName.c_str(), //Name
			WS_OVERLAPPEDWINDOW, //TODO Add window style translation here

			static_cast<int>(_v2Loc.x), static_cast<int>(_v2Loc.y), 
			static_cast<int>(_v2Size.x), static_cast<int>(_v2Size.y),

			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (hwndWindowHandle == NULL) {
			assert(!"ERROR: Window failed to create!");
		}

		ShowWindow(hwndWindowHandle, 1);
	}
}