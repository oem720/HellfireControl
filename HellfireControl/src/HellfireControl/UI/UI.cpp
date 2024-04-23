#include <HellfireControl/UI/UI.hpp>

UISubsystem* UISubsystem::m_UIInstance = nullptr;
int UISubsystem::m_IScreenWidth = -1;
int UISubsystem::m_IScreenHeight = -1;

void UISubsystem::Init() {
	
}

UISubsystem* UISubsystem::GetInstance() {
	if (!m_UIInstance) {
		m_UIInstance = new UISubsystem();
	}
	return m_UIInstance;
};