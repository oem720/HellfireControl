
#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Core/Window.hpp>

#include <Platform/GLInclude.hpp>

RenderingSubsystem* RenderingSubsystem::m_prsInstancePtr = nullptr;

RenderingSubsystem* RenderingSubsystem::GetInstance() {
	if (!m_prsInstancePtr) {
		m_prsInstancePtr = new RenderingSubsystem();
	}

	return m_prsInstancePtr;
}

static void WindowEventHandler(WindowHandleGeneric _whgHandle, const WindowCallbackMessage& _wcmMessage) {
	if (_wcmMessage.m_wcetType & WINDOW_RESIZE) {
		int iNewWidth = static_cast<int>(_wcmMessage.m_llLowerParam >> 32); //Shift the packed value enough to extract width
		int iNewHeight = static_cast<int>(_wcmMessage.m_llLowerParam & 0xFFFFFFFF); //Use bit masking to extract height

		PlatformRenderer::MarkFramebufferUpdated();
	}

	if (_wcmMessage.m_wcetType & WINDOW_CLOSE) {

	}
}

void RenderingSubsystem::Init(const std::string& _strAppName, uint64_t _u64WindowHandle) {
	//TODO Add ability to store end app version data to replace the engine version. For now, they'll be identical.
	PlatformRenderer::InitRenderer(_strAppName, HC_ENGINE_VERSION, _u64WindowHandle);

	Window(_u64WindowHandle).RegisterEventCallback(WindowEventHandler);
}

void RenderingSubsystem::RenderFrame() {
	PlatformRenderer::RenderFrame();
}

void RenderingSubsystem::Cleanup() {
	PlatformRenderer::CleanupRenderer();

	delete m_prsInstancePtr; //Final renderer cleanup
}