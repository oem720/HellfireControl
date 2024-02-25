#pragma once

#include <vector>
#include <HellfireControl/UI/Interactable.hpp>

static class UISubsystem {
private:

	static UISubsystem* m_UIInstance;

	static std::vector<Interactable> m_InterableElements;

	UISubsystem() {};

	void Init();

public:

	[[nodiscard]] HC_INLINE static UISubsystem* GetInstance();


};