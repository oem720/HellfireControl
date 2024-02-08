
#include <HellfireControl/Core/Window.hpp>

#define HC_INCLUDE_WINDOW //Enable window include

#include <Platform/OSInclude.hpp>

void Window::CleanupWindow() {
	PlatformWindow::CleanupWindow(m_whgHandle);
}

bool Window::SetWindowName(const std::string& _strName) {
	return PlatformWindow::SetWindowName(m_whgHandle, _strName);
}

bool Window::SetWindowType(WindowType _wtType) {
	return PlatformWindow::SetWindowStyleParameters(m_whgHandle, _wtType);
}

bool Window::SetWindowSize(const Vec2F& _v2Size) {
	return PlatformWindow::SetWindowSize(m_whgHandle, _v2Size);
}

bool Window::SetWindowLocation(const Vec2F& _v2Loc) {
	return PlatformWindow::SetWindowLocation(m_whgHandle, _v2Loc);
}

void Window::InitWindow() {
	PlatformWindow::InitWindow(m_whgHandle, m_wtType, m_strWindowName, m_v2WindowSize, m_v2WindowLocation);
}

void Window::UpdateWindowData() {
	m_v2WindowSize = PlatformWindow::GetWindowSize(m_whgHandle);
	m_v2WindowLocation = PlatformWindow::GetWindowLocation(m_whgHandle);
	m_wtType = static_cast<WindowType>(PlatformWindow::GetWindowParameters(m_whgHandle));
}

void Window::UpdateWindowSize() {
	m_v2WindowSize = PlatformWindow::GetWindowSize(m_whgHandle);
}

void Window::UpdateWindowLocation() {
	m_v2WindowLocation = PlatformWindow::GetWindowLocation(m_whgHandle);
}

void Window::UpdateWindowType() {
	m_wtType = static_cast<WindowType>(PlatformWindow::GetWindowParameters(m_whgHandle));
}