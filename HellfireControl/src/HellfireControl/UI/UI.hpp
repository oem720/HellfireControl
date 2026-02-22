#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Singleton.hpp>

class Renderer;

class UIManager : public Singleton<UIManager> {
private:
	Shared<Renderer> m_pUIRenderer;
public:
	void Init();
	void Cleanup();

private:
	UIManager() {}

	friend class Singleton<UIManager>;
};