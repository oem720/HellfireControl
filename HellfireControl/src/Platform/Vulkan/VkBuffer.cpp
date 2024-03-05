
#include <Platform/Vulkan/VkCore.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

#include <HellfireControl/Render/Buffer.hpp>

BufferLocals PlatformBuffer::g_blData = {};

void PlatformBuffer::InitBuffer(BufferHandleGeneric& _bhgOutHandle, uint8_t _u8Type, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext) {
	VkDeviceSize dsSize = static_cast<uint64_t>(_u32ItemWidth) * static_cast<uint64_t>(_u32ItemCount);

	if (_u8Type & UNIFORM_BUFFER) {
		PlatformRenderer::VkSyncedBufferVars vsbBufferData = {};

		vsbBufferData.m_bufFlags = _u8Type; //Set the buffer type, assuming no flags have been merged (that would be catastrophic)

		vsbBufferData.m_vBuffers.resize(HC_MAX_FRAMES_IN_FLIGHT);
		vsbBufferData.m_vMemory.resize(HC_MAX_FRAMES_IN_FLIGHT);
		vsbBufferData.m_vMappedPtrs.resize(HC_MAX_FRAMES_IN_FLIGHT);

		for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
			PlatformBuffer::CreateBuffer(dsSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, HC_MEMORY_FLAGS, vsbBufferData.m_vBuffers[ndx], vsbBufferData.m_vMemory[ndx]);

			vkMapMemory(PlatformRenderer::m_dDeviceHandle, vsbBufferData.m_vMemory[ndx], 0, dsSize, 0, &vsbBufferData.m_vMappedPtrs[ndx]);
		}

		_bhgOutHandle = {
			.upper = reinterpret_cast<uint64_t>(vsbBufferData.m_vBuffers[0]),
			.lower = reinterpret_cast<uint64_t>(vsbBufferData.m_vMemory[0])
		};

		g_blData.g_mBufferTypeTable[vsbBufferData.m_vBuffers[0]] = {
			.m_u8Type = _u8Type,
			.m_u32ItemWidth = _u32ItemWidth,
			.m_u32ItemCount = _u32ItemCount,
			.m_u32RenderContextID = _u32RenderContext
		};
	}
	else {
		VkBuffer bStagingBuffer;
		VkDeviceMemory dmStagingMemory;
		CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, HC_MEMORY_FLAGS, bStagingBuffer, dmStagingMemory);

		void* pvData;
		vkMapMemory(PlatformRenderer::m_dDeviceHandle, dmStagingMemory, 0, dsSize, 0, &pvData);
		memcpy(pvData, _pDataBlob, dsSize);
		vkUnmapMemory(PlatformRenderer::m_dDeviceHandle, dmStagingMemory);

		VkBuffer bNewBufferHandle;
		VkDeviceMemory dmNewBufferMemory;

		CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | TranslateBufferUsage(_u8Type), HC_MEMORY_FLAGS, bNewBufferHandle, dmNewBufferMemory);

		CopyBuffer(bStagingBuffer, bNewBufferHandle, dsSize);

		vkDestroyBuffer(PlatformRenderer::m_dDeviceHandle, bStagingBuffer, nullptr); //Free the staging buffer
		vkFreeMemory(PlatformRenderer::m_dDeviceHandle, dmStagingMemory, nullptr);

		_bhgOutHandle = {
			.upper = reinterpret_cast<uint64_t>(bNewBufferHandle),
			.lower = reinterpret_cast<uint64_t>(dmNewBufferMemory)
		};

		g_blData.g_mBufferTypeTable[bNewBufferHandle] = {
			.m_u8Type = _u8Type,
			.m_u32ItemWidth = _u32ItemWidth,
			.m_u32ItemCount = _u32ItemCount
		};
	}
}

void PlatformBuffer::Append(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext) {

}

void PlatformBuffer::Update(const BufferHandleGeneric& _bhgHandle, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount, uint32_t _u32RenderContext) {
	if (GetBufferType(_bhgHandle) & UNIFORM_BUFFER) {
		uint32_t u32Context = GetBufferRenderContext(_bhgHandle);

		void* pvDest = nullptr;
		PlatformRenderer::m_mContextMap[u32Context].m_vContextBuffers
	}
}

void PlatformBuffer::CleanupBuffer(const BufferHandleGeneric& _bhgHandle, uint32_t _u32RenderContext) {
	vkDeviceWaitIdle(PlatformRenderer::m_dDeviceHandle);

	vkDestroyBuffer(PlatformRenderer::m_dDeviceHandle, reinterpret_cast<VkBuffer>(_bhgHandle.upper), nullptr);
	vkFreeMemory(PlatformRenderer::m_dDeviceHandle, reinterpret_cast<VkDeviceMemory>(_bhgHandle.lower), nullptr);

	g_blData.g_mBufferTypeTable.erase(reinterpret_cast<VkBuffer>(_bhgHandle.upper));
}

uint8_t PlatformBuffer::GetBufferType(const BufferHandleGeneric& _bhgHandle) {
	return g_blData.g_mBufferTypeTable[reinterpret_cast<VkBuffer>(_bhgHandle.upper)].m_u8Type;
}

uint32_t PlatformBuffer::GetBufferRenderContext(const BufferHandleGeneric& _bhgHandle) {
	return g_blData.g_mBufferTypeTable[reinterpret_cast<VkBuffer>(_bhgHandle.upper)].m_u32RenderContextID;
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

	if (vkCreateBuffer(PlatformRenderer::m_dDeviceHandle, &bciBufferInfo, nullptr, &_bBuffer) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create buffer!");
	}

	VkMemoryRequirements mrRequirements;
	vkGetBufferMemoryRequirements(PlatformRenderer::m_dDeviceHandle, _bBuffer, &mrRequirements);

	VkMemoryAllocateInfo maiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = FindMemoryType(mrRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	};

	if (vkAllocateMemory(PlatformRenderer::m_dDeviceHandle, &maiAllocInfo, nullptr, &_dmMemory) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate buffer memory!");
	}

	vkBindBufferMemory(PlatformRenderer::m_dDeviceHandle, _bBuffer, _dmMemory, 0);
}

void PlatformBuffer::CopyBuffer(VkBuffer _bSource, VkBuffer _bDestination, VkDeviceSize _dsSize) {
	VkCommandBuffer cbBuffer = PlatformRenderer::BeginSingleTimeCommands();

	VkBufferCopy bcCopyRegion = {
		.srcOffset = 0,
		.dstOffset = 0,
		.size = _dsSize
	};

	vkCmdCopyBuffer(cbBuffer, _bSource, _bDestination, 1, &bcCopyRegion);

	PlatformRenderer::EndSingleTimeCommands(cbBuffer);
}

uint32_t PlatformBuffer::TranslateBufferUsage(uint8_t _u8Type) {
	switch (_u8Type) {
	case 0: { //Vertex
		return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	} break;
	case 1: { //Index
		return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	} break;
	case 2: { //Storage
		return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
	} break;
	case 3: {
		return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	} break;
	default: {
		throw std::runtime_error("ERROR: Attempted to construct a buffer of INVALID type!");
	} break;
	}
}

uint32_t PlatformBuffer::FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags) {
	VkPhysicalDeviceMemoryProperties pdmpMemProperties;
	vkGetPhysicalDeviceMemoryProperties(PlatformRenderer::m_pdPhysicalDevice, &pdmpMemProperties);

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