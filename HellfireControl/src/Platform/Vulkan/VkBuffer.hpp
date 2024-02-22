#pragma once

#include <Platform/GLCommon.hpp>

struct BufferHandleGeneric;

struct BufferData {
	uint8_t m_u8Type = 3;
	uint32_t m_u32ItemWidth = 0;
	uint32_t m_u32ItemCount = 0;
};

struct BufferLocals {
	std::map<VkBuffer, BufferData> g_mBufferTypeTable;
};

class PlatformBuffer {
	friend class PlatformRenderer;

private:
	static uint32_t FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags);

	static BufferLocals g_blData;

	static const std::map<VkBuffer, BufferData>* GetActiveBufferData();
public:
	static void InitBuffer(BufferHandleGeneric& _bhgOutHandle, uint8_t _u8Type, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	static void Append(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	static void ReplaceData(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount);

	static void CleanupBuffer(const BufferHandleGeneric& _bhgHandle);
};