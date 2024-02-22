
#include <Platform/Vulkan/VkCore.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

#include <HellfireControl/Render/Buffer.hpp>

BufferLocals PlatformBuffer::g_blData = {};

void PlatformBuffer::InitBuffer(BufferHandleGeneric& _bhgOutHandle, uint8_t _u8Type, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	VkDeviceSize dsSize = _u32ItemWidth * _u32ItemCount;

	VkBuffer bStagingBuffer;
	VkDeviceMemory dmStagingMemory;
	CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, HC_MEMORY_FLAGS, bStagingBuffer, dmStagingMemory);

	void* pvData;
	vkMapMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, dmStagingMemory, 0, dsSize, 0, &pvData);
	memcpy(pvData, _pDataBlob, dsSize);
	vkUnmapMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, dmStagingMemory);

	VkBuffer bNewBufferHandle;
	VkDeviceMemory dmNewBufferMemory;

	CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | TranslateBufferUsage(_u8Type), HC_MEMORY_FLAGS, bNewBufferHandle, dmNewBufferMemory);

	CopyBuffer(bStagingBuffer, bNewBufferHandle, dsSize);

	vkDestroyBuffer(PlatformRenderer::g_vVars.g_dDeviceHandle, bStagingBuffer, nullptr); //Free the staging buffer
	vkFreeMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, dmStagingMemory, nullptr);

	_bhgOutHandle = {
		.m_u64UpperParam = reinterpret_cast<uint64_t>(bNewBufferHandle),
		.m_u64LowerParam = reinterpret_cast<uint64_t>(dmNewBufferMemory)
	};

	g_blData.g_mBufferTypeTable[bNewBufferHandle] = {
		.m_u8Type = _u8Type,
		.m_u32ItemWidth = _u32ItemWidth,
		.m_u32ItemCount = _u32ItemCount
	};
}

void PlatformBuffer::Append(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {

}

void PlatformBuffer::ReplaceData(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {

}

void PlatformBuffer::CleanupBuffer(const BufferHandleGeneric& _bhgHandle) {
	vkDeviceWaitIdle(PlatformRenderer::g_vVars.g_dDeviceHandle);

	vkDestroyBuffer(PlatformRenderer::g_vVars.g_dDeviceHandle, reinterpret_cast<VkBuffer>(_bhgHandle.m_u64UpperParam), nullptr);
	vkFreeMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, reinterpret_cast<VkDeviceMemory>(_bhgHandle.m_u64LowerParam), nullptr);

	g_blData.g_mBufferTypeTable.erase(reinterpret_cast<VkBuffer>(_bhgHandle.m_u64UpperParam));
}

void PlatformBuffer::CreateBuffer(VkDeviceSize _dsSize, VkBufferUsageFlags _bufFlags, VkMemoryPropertyFlags _mpfFlags, VkBuffer& _bBuffer, VkDeviceMemory& _dmMemory) {
	VkBufferCreateInfo bciBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.size = _dsSize,
			.usage = _bufFlags,
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = nullptr
	};

	if (vkCreateBuffer(PlatformRenderer::g_vVars.g_dDeviceHandle, &bciBufferInfo, nullptr, &_bBuffer) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create buffer!");
	}

	VkMemoryRequirements mrRequirements;
	vkGetBufferMemoryRequirements(PlatformRenderer::g_vVars.g_dDeviceHandle, _bBuffer, &mrRequirements);

	VkMemoryAllocateInfo maiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = FindMemoryType(mrRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	};

	if (vkAllocateMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, &maiAllocInfo, nullptr, &_dmMemory) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate buffer memory!");
	}

	vkBindBufferMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, _bBuffer, _dmMemory, 0);
}

void PlatformBuffer::CopyBuffer(VkBuffer _bSource, VkBuffer _bDestination, VkDeviceSize _dsSize) {
	VkCommandBufferAllocateInfo cbaiBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = PlatformRenderer::g_vVars.g_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1
	};

	VkCommandBuffer cbBuffer;

	vkAllocateCommandBuffers(PlatformRenderer::g_vVars.g_dDeviceHandle, &cbaiBufferInfo, &cbBuffer);

	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = nullptr
	};

	vkBeginCommandBuffer(cbBuffer, &cbbiBeginInfo);

	VkBufferCopy bcCopyRegion = {
		.srcOffset = 0,
		.dstOffset = 0,
		.size = _dsSize
	};

	vkCmdCopyBuffer(cbBuffer, _bSource, _bDestination, 1, &bcCopyRegion);

	vkEndCommandBuffer(cbBuffer);

	VkSubmitInfo siSubmitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 0,
		.pWaitSemaphores = nullptr,
		.pWaitDstStageMask = nullptr,
		.commandBufferCount = 1,
		.pCommandBuffers = &cbBuffer,
		.signalSemaphoreCount = 0,
		.pSignalSemaphores = nullptr
	};

	vkQueueSubmit(PlatformRenderer::g_vVars.g_qGraphicsQueue, 1, &siSubmitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(PlatformRenderer::g_vVars.g_qGraphicsQueue);

	vkFreeCommandBuffers(PlatformRenderer::g_vVars.g_dDeviceHandle, PlatformRenderer::g_vVars.g_cpCommandPool, 1, &cbBuffer);
}

uint32_t PlatformBuffer::TranslateBufferUsage(uint8_t _u8Type) {
	switch (_u8Type) {
	case 0: { //Vertex
		return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	} break;
	case 1: { //Index
		return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	} break;
	case 2: { //Uniform
		return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	} break;
	default: {
		throw std::runtime_error("ERROR: Attempted to construct a buffer of NONE type!");
	} break;
	}
}

uint32_t PlatformBuffer::FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags) {
	VkPhysicalDeviceMemoryProperties pdmpMemProperties;
	vkGetPhysicalDeviceMemoryProperties(PlatformRenderer::g_vVars.g_pdPhysicalDevice, &pdmpMemProperties);

	for (uint32_t ndx = 0; ndx < pdmpMemProperties.memoryTypeCount; ++ndx) {
		if (_u32TypeFilter & (1 << ndx) && (pdmpMemProperties.memoryTypes[ndx].propertyFlags & _mpfFlags) == _mpfFlags) {
			return ndx;
		}
	}

	throw std::runtime_error("ERROR: Failed to find suitable memory type!");
}

const std::map<VkBuffer, BufferData>* PlatformBuffer::GetActiveBufferData() {
	return &g_blData.g_mBufferTypeTable;
}