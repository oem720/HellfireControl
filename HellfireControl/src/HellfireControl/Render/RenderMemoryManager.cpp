
#include <HellfireControl/Render/RenderMemoryManager.hpp>

#include <HellfireControl/Math/Math.hpp>

Map<RenderMemoryManager::AllocationOffset, RenderMemoryManager::Allocation> RenderMemoryManager::m_mAllocations;

RenderMemoryManager* RenderMemoryManager::m_prmmInstance = nullptr;

constexpr uint32 g_u32MinimumMemoryPoolSize = 1024 * 1024; //1 MB

RenderMemoryManager* RenderMemoryManager::GetInstance() {
	if (m_prmmInstance == nullptr) {
		m_prmmInstance = new RenderMemoryManager();
	}

	return m_prmmInstance;
}

void RenderMemoryManager::Init(uint32 _u32InitialMemoryPool) {
	
}


void RenderMemoryManager::Cleanup() {
	delete m_prmmInstance;
}