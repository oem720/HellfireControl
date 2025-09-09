#pragma once

#include <HellfireControl/Core/Common.hpp>

class UIManager {
private:
	static UIManager* m_pInstance;

	UIManager() {}


public:
	UIManager(UIManager& _other) = delete;

	void operator=(const UIManager& _other) = delete;

	static UIManager* GetInstance();

	void Init();

	void Cleanup();

};