#include <HellfireControl/UI/Interactable.hpp>

void Interactable::SetPivot(UIPivot _pivot) {
	m_pPivot = *reinterpret_cast<Vec2F*>(&_pivot);
}