#include <HellfireControl/UI/UI.hpp>

UISubsystem* UISubsystem::m_UIInstance = nullptr;

void UISubsystem::Init() {
	
}

UISubsystem* UISubsystem::GetInstance() {
	if (!m_UIInstance) {
		m_UIInstance = new UISubsystem();
	}
	return m_UIInstance;
};