#pragma once

#include <Platform/GLCommon.hpp>

struct VkBufferData {
	VkBuffer m_bBuffer;
	VkDeviceSize m_dsOffset;
	VkDeviceSize m_dsSize;
	VkBufferUsageFlags m_bufUsageFlags;
};

class VkRenderMemoryManager {
private:
	static VkDeviceMemory m_dmMemoryBlock;

	static Map<uint32, VkBufferData> m_mBufferDataMap;

	static VkBuffer CreateDummyBuffer(uint32 _u32Size, VkBufferUsageFlags _bufTransferBit);

	static VkDeviceMemory AllocateMemoryBlock(uint32 _u32Size);
	static VkDeviceMemory AllocateMemoryBlock(VkMemoryRequirements& _mrRequirements);

	static void CopyMemoryBlock(VkBuffer _bSrcBuffer, VkBuffer _bDstBuffer, VkDeviceSize _dsSize);

	static Map<uint32, VkBufferData> RecreateBufferDataMap();

	static uint32 GetMemoryType(uint32 _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags);

public:
	static void Init(uint32 _u32InitialSize);

	static void Resize(uint32 _u32OriginalSize, uint32 _u32NewSize);

	static void Cleanup();
};