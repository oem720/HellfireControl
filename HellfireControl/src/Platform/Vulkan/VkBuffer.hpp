#pragma once

#include <Platform/GLCommon.hpp>

struct BufferHandleGeneric;

struct BufferData {
	uint32_t m_u32BufferID = 0;
	uint8_t m_u8Type = 3;
	uint32_t m_u32ItemWidth = 0;
	uint32_t m_u32ItemCount = 0;
	uint32_t m_u32RenderContextID = 0;
};

struct BufferLocals {
	std::map<VkBuffer, BufferData> g_mBufferDataTable;
};

constexpr VkMemoryPropertyFlags HC_MEMORY_FLAGS = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

class PlatformBuffer {
	friend class PlatformRenderer;

private:
	static void CreateBuffer(VkDeviceSize _dsSize, VkBufferUsageFlags _bufFlags, VkMemoryPropertyFlags _mpfFlags, VkBuffer& _bBuffer, VkDeviceMemory& _dmMemory);

	static void CopyBuffer(VkBuffer _bSource, VkBuffer _bDestination, VkDeviceSize _dsSize);

	static uint32_t FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags);

	static const std::map<VkBuffer, BufferData>* GetActiveBufferData();

	static BufferLocals g_blData;
public:
	static void InitBuffer(BufferHandleGeneric& _bhgOutHandle, uint8_t _u8Type, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext);

	static void Append(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext);

	static void Update(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext);

	static void CleanupBuffer(const BufferHandleGeneric& _bhgHandle, uint32_t _u32RenderContext);

	static uint8_t GetBufferType(const BufferHandleGeneric& _bhgHandle);

	static uint32_t GetBufferRenderContext(const BufferHandleGeneric& _bhgHandle);
};