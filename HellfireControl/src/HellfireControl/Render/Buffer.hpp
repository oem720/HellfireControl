#pragma once

#include <HellfireControl/Core/Common.hpp>

enum BufferType : uint8_t {
	VERTEX_BUFFER,
	INDEX_BUFFER,
	STORAGE_BUFFER,
	UNIFORM_BUFFER,
	INVALID_BUFFER
};

struct HC_ALIGNAS(128) BufferHandleGeneric {
	uint64_t upper;
	uint64_t lower;

	HC_INLINE bool operator==(const BufferHandleGeneric& _bhgOther) {
		return this->upper == _bhgOther.upper && this->lower == _bhgOther.lower;
	}
};

class RenderingSubsystem;

class Buffer {
private:
	RenderingSubsystem* m_prsRenderer = nullptr;

	BufferType m_btType = BufferType::INVALID_BUFFER;

	BufferHandleGeneric m_bhgHandle = {};

	BufferType GetBufferType(const BufferHandleGeneric& _bhgHandle);
public:
	Buffer() = delete;

	Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth = 1U, uint32_t _u32ItemCount = 1U);

	Buffer(const BufferHandleGeneric& _bhgPreexisting);

	void Append(const void* _pDataBlob, uint32_t _u32ItemWidth = 1U, uint32_t _u32ItemCount = 1U);

	void Update(const void* _pDataBlob, uint32_t _u32ItemWidth = 1U, uint32_t _u32ItemCount = 1U);

	void Cleanup(bool _bDeregister = true);

	[[nodiscard]] HC_INLINE BufferHandleGeneric GetBufferHandle() const { return m_bhgHandle; }
};