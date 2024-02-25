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

enum UIPivot : uint64_t {
	topLeft = 0, // (0, 0)
	topMiddle = 4539628424389459968, // (0.5, 0)
	topRight = 1065353216, // (0, 1)
	middleLeft = 1056964608, // (0, 0.5)
	center = 4539628425446424576, // (0.5, 0.5)
	middleRight = 4575657222465388544, // (1.0, 0.5);
	bottomLeft = 4575657221408423936, // (1, 0)
	bottomMiddle = 4539628425454813184, // (0.5, 1)
	bottomRight = 4575657222473777152, // (1, 1)
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
	Vec2F m_pPivot = Vec2F(0.5f, 0.5f);
	Interactable* m_itParent = nullptr;

public:

	[[nodiscard]] HC_INLINE bool GetEnabled() { return m_bEnabled; }
	HC_INLINE void SetEnabled(bool _inputState) { m_bEnabled = _inputState; }

	[[nodiscard]] HC_INLINE bool GetInteractableType() { return m_itType; }
	HC_INLINE void SetInteractableType(InteractableType _inputType) { m_itType = _inputType; }

	[[nodiscard]] HC_INLINE float GetWidth() { return m_fWidth; }
	HC_INLINE void SetWidth(float _fWidth) { m_fWidth = _fWidth; }

	[[nodiscard]] HC_INLINE float GetHeight() { return m_fHeight; }
	HC_INLINE void SetHeight(float _fHeight) { m_fHeight = _fHeight; }

	[[nodiscard]] HC_INLINE Vec2F GetPivot() { return m_pPivot; }
	HC_INLINE void SetPivot(UIPivot _pivot);
};