#pragma once

#include <HellfireControl/Math/Vector.hpp>

enum InteractableType : uint8_t {
	None,
	Image,
	Button,
	Slider,
	Dropdown,
	Radio
};

struct UIPivot {
	Vec2F center = Vec2F(0.5f, 0.5f);
	Vec2F topLeft = Vec2F(0, 0);
	Vec2F topMiddle = Vec2F(0.5f, 0.0f);
	Vec2F topRight = Vec2F(0, 1);
	Vec2F bottomLeft = Vec2F(1, 0);
	Vec2F bottomMiddle = Vec2F(0.5f, 1.0f);
	Vec2F bottomRight = Vec2F(1, 1);
	Vec2F middleLeft = Vec2F(0.0f, 0.5f);
	Vec2F middleRight = Vec2F(1.0f, 0.5f);
};

class Interactable {

	Interactable() {};
	Interactable(InteractableType _itType) { m_itType = _itType; };
	Interactable(InteractableType _itType, float _fWidth, float _fHeight) { m_itType = _itType; m_fWidth = _fWidth; m_fHeight = _fHeight; };
	Interactable(InteractableType _itType, float _fWidth, float _fHeight, bool _bEnabled) { m_itType = _itType; m_fWidth = _fWidth; m_fHeight = _fHeight; m_bEnabled = _bEnabled; };

private:

	bool m_bEnabled = false;
	InteractableType m_itType = InteractableType::None;
	Vec2F m_vPosition = Vec2F(0, 0);
	float m_fWidth = 0;
	float m_fHeight = 0;

public:

	bool GetEnabled() { return m_bEnabled; }
	void SetEnabled(bool _inputState) { m_bEnabled = _inputState; }

	bool GetInteractableType() { return m_itType; }
	void SetInteractableType(InteractableType _inputType) { m_itType = _inputType; }

	float GetWidth() { return m_fWidth; }
	float SetWidth(float _fWidth) { m_fWidth = _fWidth; }

	float GetHeight() { return m_fHeight; }
	float SetHeight(float _fHeight) { m_fHeight = _fHeight; }
};