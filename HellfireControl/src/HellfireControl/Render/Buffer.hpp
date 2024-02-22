#pragma once

#include <HellfireControl/Core/Common.hpp>

enum BufferType : uint8_t {
	VERTEX,
	INDEX,
	UNIFORM,
	INVALID
};

struct BufferHandleGeneric {
	uint64_t m_u64UpperParam;
	uint64_t m_u64LowerParam;
};

class RenderingSubsystem;

class Buffer {
private:
	RenderingSubsystem* m_prsRenderer = nullptr;

	BufferType m_btType = BufferType::INVALID;

	BufferHandleGeneric m_bhgHandle = {};
public:
	Buffer() = delete;

	Buffer(BufferType _btType, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	Buffer(const BufferHandleGeneric& _bhgPreexisting);

	void Append(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	void ReplaceData(const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	void Cleanup();
};