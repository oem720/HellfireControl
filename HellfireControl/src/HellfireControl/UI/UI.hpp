#pragma once

#include <HellfireControl/Core/Common.hpp>

class Renderer;

class UIManager {
private:
	static UIManager* m_pInstance;

	static Shared<Renderer> m_pUIRenderer;

	UIManager() {}


public:
	UIManager(UIManager& _other) = delete;

	void operator=(const UIManager& _other) = delete;

	static UIManager* GetInstance();

	void Init();

	void Cleanup();

};