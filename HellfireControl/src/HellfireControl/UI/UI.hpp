#pragma once

#include <HellfireControl/UI/Interactable.hpp>

static class UI {
private:

	static UI* m_UIInstance;

	UI() {};

public:

	static UI* GetInstance() {
		if (!m_UIInstance) {
			m_UIInstance = new UI();
		}
		return m_UIInstance;
	};
};