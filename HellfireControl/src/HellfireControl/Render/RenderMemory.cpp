
#include <HellfireControl/Render/RenderMemory.hpp>

uint32 RenderMemoryAllocator::m_u32AllocationIDCounter = 0;
uint32 RenderMemoryAllocator::m_u32AllocationLimit = 0;
uint64 RenderMemoryAllocator::m_u64Granularity = 0;

void RenderMemoryAllocator::Init() {
	m_pDeviceLocalMemoryPool = std::make_unique<RenderMemoryPool>(RENDER_MEMORY_DEVICE_LOCAL);
	m_pHostAccessibleMemoryPool = std::make_unique<RenderMemoryPool>(RENDER_MEMORY_HOST_ACCESSIBLE);
	m_pTransientMemory = std::make_unique<RenderMemoryChunk>();

	m_pDeviceLocalMemoryPool->Init();
	m_pHostAccessibleMemoryPool->Init();
}

void RenderMemoryAllocator::Cleanup() {
	if (m_pDeviceLocalMemoryPool) m_pDeviceLocalMemoryPool->Cleanup();
	if (m_pHostAccessibleMemoryPool) m_pHostAccessibleMemoryPool->Cleanup();
	if (m_pTransientMemory) m_pTransientMemory->Free();

	m_mAllocations.clear();

	Singleton<RenderMemoryAllocator>::DestroyInstance();
}

uint32 RenderMemoryAllocator::Allocate(uint64 _u64Size, RenderMemoryType _rmtType) {

	return uint32();
}

uint32 RenderMemoryAllocator::Write(uint64 _u64Size, const void* _pData, RenderMemoryType _rmtType) {

	return uint32();
}

void RenderMemoryAllocator::Write(uint64 _u64Size, const void* _pData, uint32 _u32AllocationId) {

}

void RenderMemoryAllocator::Free(uint32 _u32AllocationId) {

}

void RenderMemoryAllocator::SetAllocationLimitAndGranularity(uint32 _u32AllocationLimit, uint64 _u64Granularity) {
	m_u32AllocationLimit = _u32AllocationLimit;
	m_u64Granularity = _u64Granularity;
}

void RenderMemoryPool::Init() {

}

void RenderMemoryPool::Cleanup() {
	
}

RenderMemoryAllocation RenderMemoryPool::Allocate(uint64 _u64Size) {

	return RenderMemoryAllocation();
}

void RenderMemoryPool::Write(uint64 _u64Size, const void* _pData, const RenderMemoryAllocation& _rmaAllocation) {

}

void RenderMemoryPool::Free(const RenderMemoryAllocation& _rmaAllocation) {

}

void RenderMemoryChunk::Init(uint32 _u32Size, RenderMemoryType _rmtType) {
	m_u32Size = _u32Size;

	m_pPlatformAllocation = std::move(CreatePlatformMemoryChunk());
	m_pPlatformAllocation->Init(_u32Size, _rmtType);
}

void RenderMemoryChunk::Free() {
	if (m_pPlatformAllocation) m_pPlatformAllocation->Free();
}
