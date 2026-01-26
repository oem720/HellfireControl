
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
	//We keep our minimum to 1MB since it's best for scaling up.
	m_u32TotalMemorySize = Math::Clamp(_u32InitialMemoryPool, g_u32MinimumMemoryPoolSize, UINT32_MAX);

	InitPlatformMemoryPool();

	//First allocation block represents the whole empty pool.
	m_mAllocations[0] = Allocation {
		.m_u32Size = m_u32TotalMemorySize,
		.m_bFree = true
	};
}

BufferHandle RenderMemoryManager::CreateBuffer(BufferType _btType, uint32 _u32Size, const void* _pData) {
	return BufferHandle();
}

BufferHandle RenderMemoryManager::CreateBuffer(BufferType _btType, uint32 _u32Size) {
	return BufferHandle();
}

void RenderMemoryManager::UploadData(BufferHandle _bhBuffer, uint32 _u32Size, const void* _pData) {

}

void RenderMemoryManager::DeleteData(BufferHandle _bhBuffer, uint32 _u32Offset) {

}

void RenderMemoryManager::DestroyBuffer(BufferHandle _bhBuffer) {
	
}

void RenderMemoryManager::Cleanup() {
	m_mAllocations.clear();

	CleanupPlatformMemoryPool();

	delete m_prmmInstance;
}