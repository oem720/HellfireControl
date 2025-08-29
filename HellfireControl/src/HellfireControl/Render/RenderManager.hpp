#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Window.hpp>

class RenderManager {
private:
	WindowHandleGeneric m_whgWindowHandle = 0;

	static bool m_bFramebufferInvalid;

	static RenderManager* m_prsInstancePtr;

	RenderManager() {}

	void InitPlatformObjects(const std::string& _strAppName, uint32_t _u32AppVersion, const Vec4F& _v4ClearColor);

	void CleanupPlatformObjects();

	static void MarkSwapchainInvalid() { m_bFramebufferInvalid = true; }

	static void WindowEventHandler(WindowHandleGeneric _whgHandle, const WindowCallbackMessage& _wcmMessage) {
		if (_wcmMessage.m_wcetType & WINDOW_RESIZE) {
			//At the moment, these values are not needed and it's merely a demonstration of how parameters might be packed in a message
			int iNewWidth = static_cast<int>(_wcmMessage.lower >> 32); //Shift the packed value enough to extract width
			int iNewHeight = static_cast<int>(_wcmMessage.lower & 0xFFFFFFFF); //Use bit masking to extract height

			MarkSwapchainInvalid();
		}

		if (_wcmMessage.m_wcetType & WINDOW_CLOSE) {
			//TODO: Possibly handle WINDOW_CLOSE here.
		}
	}

public:
	RenderManager(RenderManager& _other) = delete;

	void operator=(const RenderManager& _other) = delete;

	static RenderManager* GetInstance() {
		if (m_prsInstancePtr == nullptr) {
			m_prsInstancePtr = new RenderManager();
		}

		return m_prsInstancePtr;
	}

	void Init(const std::string& _strAppName, uint32_t _u32AppVersion, WindowHandleGeneric _whgWindowHandle, const Vec4F& _v4ClearColor = Vec4F()) {
		m_whgWindowHandle = _whgWindowHandle;

		Window(_whgWindowHandle).RegisterEventCallback(WindowEventHandler);

		InitPlatformObjects(_strAppName, _u32AppVersion, _v4ClearColor);
	}

	void Cleanup() {
		CleanupPlatformObjects();

		delete m_prsInstancePtr;
	}

	void RenderFrame();
};