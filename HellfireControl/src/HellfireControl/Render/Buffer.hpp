#pragma once

#include <HellfireControl/Core/Common.hpp>

enum BufferType : uint8_t {
	UNIFORM_BUFFER = 16U,
	STORAGE_BUFFER = 32U,
	INDEX_BUFFER = 64U,
	VERTEX_BUFFER = 128U,
	INVALID_BUFFER = 1U
};

class Buffer {
private:
	BufferType m_btType = BufferType::INVALID_BUFFER;

	BufferHandleGeneric m_bhgHandle = {};

	uint32_t m_u32RenderContextID = 0;

	BufferType GetBufferType(const BufferHandleGeneric& _bhgHandle);
public:
	Buffer() = delete;

	Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContextID);

	Buffer(const BufferHandleGeneric& _bhgPreexisting);

	void Append(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	void Update(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	void Cleanup();

	[[nodiscard]] HC_INLINE BufferHandleGeneric GetBufferHandle() const { return m_bhgHandle; }
};