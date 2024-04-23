#pragma once

#include <vector>
#include <HellfireControl/UI/Interactable.hpp>

static class UISubsystem {
private:

	static UISubsystem* m_UIInstance;

	static std::vector<Interactable> m_InterableElements;

	static int m_IScreenWidth;
	static int m_IScreenHeight;

	UISubsystem() {};

	void Init();

public:

	[[nodiscard]] HC_INLINE static UISubsystem* GetInstance();

	void CreateButton();

	void CreateTextField();

	void CreateImage();

	void CreateSlider();

	void CreateDropdown();

	//Check for click input and go into functions depending on state of user.

	//Add system to read file into here with preset interactables.

};