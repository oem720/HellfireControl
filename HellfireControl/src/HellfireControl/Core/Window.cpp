
#include <HellfireControl/Core/Window.hpp>

#define HC_INCLUDE_WINDOW //Enable window include

#include <Platform/OSInclude.hpp>

Window::~Window() {

}

bool Window::SetWindowName(std::string _strName) {

}

bool Window::SetWindowType(WindowType _wtType) {

}

bool Window::SetWindowSize(const Vec2F& _v2Size) {

}

bool Window::SetWindowLocation(const Vec2F& _v2Loc) {

}

void Window::InitWindow() {
	PlatformWindow::InitWindow(m_whgHandle, m_wtType, m_strWindowName, m_v2WindowSize, m_v2WindowLocation);
}

void Window::UpdateWindowData() {

}

void Window::UpdateWindowSize() const {

}

void Window::UpdateWindowLocation() const {

}

void Window::UpdateWindowType() const {

}