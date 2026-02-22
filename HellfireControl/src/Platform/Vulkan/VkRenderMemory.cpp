
#include <HellfireControl/Render/RenderMemory.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderMemory.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkUtil.hpp>

Unique<PlatformRenderMemoryChunk> RenderMemoryChunk::CreatePlatformMemoryChunk() {
	return std::make_unique<VkRenderMemoryChunk>();
}

void VkRenderMemoryChunk::Init(uint32 _u32Size, RenderMemoryType _rmtType) {
	
}

void VkRenderMemoryChunk::Write(uint64 _u64Size, uint64 _u64Offset, const void* _pData) {

}

void VkRenderMemoryChunk::Free() {
	
}
#endif