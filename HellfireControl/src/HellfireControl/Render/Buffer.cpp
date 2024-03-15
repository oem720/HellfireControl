
#include <HellfireControl/Render/Buffer.hpp>

#include <Platform/GLInclude.hpp>

Buffer::Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContextID) {
	m_u32RenderContextID = _u32RenderContextID;

	PlatformBuffer::InitBuffer(m_bhgHandle, _btType, _pDataBlob, _u32ItemWidth, _u32ItemCount, m_u32RenderContextID);
}

Buffer::Buffer(const BufferHandleGeneric& _bhgPreexisting) {
	m_u32RenderContextID = PlatformBuffer::GetBufferRenderContext(_bhgPreexisting);

	m_bhgHandle = _bhgPreexisting;
}

void Buffer::Append(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	PlatformBuffer::Append(m_bhgHandle, _pDataBlob, _u32ItemWidth, _u32ItemCount, m_u32RenderContextID);
}

void Buffer::Update(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	PlatformBuffer::Update(m_bhgHandle, _pDataBlob, _u32ItemWidth, _u32ItemCount, m_u32RenderContextID);
}

void Buffer::Cleanup() {
	PlatformBuffer::CleanupBuffer(m_bhgHandle, m_u32RenderContextID);
}

BufferType Buffer::GetBufferType(const BufferHandleGeneric& _bhgHandle) {
	return static_cast<BufferType>(PlatformBuffer::GetBufferType(_bhgHandle));
}