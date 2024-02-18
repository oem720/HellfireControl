
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/Renderer.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_prsRenderHandle = RenderingSubsystem::GetInstance();

	m_prsRenderHandle->Init(m_strApplicationName, m_wWindow.GetNativeWindowHandle());
}

void UICreationToolApplication::Run() {
	this->Start();

	while (!m_wWindow.CloseRequested()) {
		m_wWindow.PollEvents();

		m_prsRenderHandle->RenderFrame();
	}

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderHandle->Cleanup();

	m_wWindow.CleanupWindow();
}
