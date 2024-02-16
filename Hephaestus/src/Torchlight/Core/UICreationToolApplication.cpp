
#include <Torchlight/Core/UICreationToolApplication.hpp>
#include <HellfireControl/Render/Renderer.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED_FULLSCREEN, Vec2F(800, 1200), Vec2F(0, 0));

	m_prsRenderHandle = RenderingSubsystem::GetInstance();

	m_prsRenderHandle->Init(m_strApplicationName);
}

void UICreationToolApplication::Run() {
	this->Start();

	//TODO Add window event processing here.

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderHandle->Cleanup();

	m_wWindow.CleanupWindow();
}
