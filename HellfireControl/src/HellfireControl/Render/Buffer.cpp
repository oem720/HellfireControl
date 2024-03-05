
#include <HellfireControl/Render/Buffer.hpp>
#include <HellfireControl/Render/Renderer.hpp>

#define HC_INCLUDE_BUFFER
#include <Platform/GLInclude.hpp>

Buffer::Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	m_prsRenderer = RenderingSubsystem::GetInstance();

	PlatformBuffer::InitBuffer(m_bhgHandle, _btType, _pDataBlob, _u32ItemWidth, _u32ItemCount);
}

Buffer::Buffer(const BufferHandleGeneric& _bhgPreexisting) {
	m_prsRenderer = RenderingSubsystem::GetInstance();

	m_bhgHandle = _bhgPreexisting;
}

void Buffer::Append(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	PlatformBuffer::Append(m_bhgHandle, _pDataBlob, _u32ItemWidth, _u32ItemCount);
}

void Buffer::Update(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	PlatformBuffer::Update(m_bhgHandle, _pDataBlob, _u32ItemWidth, _u32ItemCount);
}

void Buffer::Cleanup(bool _bDeregister) {
	PlatformBuffer::CleanupBuffer(m_bhgHandle);

	if (_bDeregister) {
		m_prsRenderer->DeregisterBuffer(m_bhgHandle);
	}
}

BufferType Buffer::GetBufferType(const BufferHandleGeneric& _bhgHandle) {
	return static_cast<BufferType>(PlatformBuffer::GetBufferType(_bhgHandle));
}