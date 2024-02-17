
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/Renderer.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_prsRenderHandle = RenderingSubsystem::GetInstance();

	m_prsRenderHandle->Init(m_strApplicationName, m_wWindow.GetNativeWindowHandle());
}

void UICreationToolApplication::Run() {
	this->Start();

	//SERIOUSLY TEMPORARY TEST CODE ! ! !
	for (int i = 0; i < 5; ++i) {
		m_prsRenderHandle->RenderFrame();
		std::this_thread::sleep_for(std::chrono::seconds(1)); 
	}

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderHandle->Cleanup();

	m_wWindow.CleanupWindow();
}
