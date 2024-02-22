
#include <HellfireControl/Render/Buffer.hpp>
#include <HellfireControl/Render/Renderer.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

Buffer::Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	m_prsRenderer = RenderingSubsystem::GetInstance();

	PlatformBuffer::InitBuffer(m_bhgHandle, _btType, _pDataBlob, _u32ItemWidth, _u32ItemCount);
}

Buffer::Buffer(const BufferHandleGeneric& _bhgPreexisting) {
	m_prsRenderer = RenderingSubsystem::GetInstance();
}

void Buffer::Append(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {

}

void Buffer::ReplaceData(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {

}

void Buffer::Cleanup() {
	PlatformBuffer::CleanupBuffer(m_bhgHandle);
}
