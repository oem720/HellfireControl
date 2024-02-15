
#include <Torchlight/Core/UICreationToolApplication.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED_FULLSCREEN, Vec2F(800, 1200), Vec2F(0, 0));
}

void UICreationToolApplication::Run() {
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void UICreationToolApplication::End() {
	m_wWindow.CleanupWindow();
}
