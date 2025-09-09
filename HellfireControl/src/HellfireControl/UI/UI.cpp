
#include <HellfireControl/UI/UI.hpp>

UIManager* UIManager::m_pInstance = nullptr;

UIManager* UIManager::GetInstance() {
	if (m_pInstance == nullptr) {
		m_pInstance = new UIManager();
	}

	return m_pInstance;
}

void UIManager::Init() {

}

void UIManager::Cleanup() {
	delete m_pInstance;
}