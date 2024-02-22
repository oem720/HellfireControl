
#include <Platform/Vulkan/VkCore.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

#include <HellfireControl/Render/Buffer.hpp>

BufferLocals PlatformBuffer::g_blData = {};

void PlatformBuffer::InitBuffer(BufferHandleGeneric& _bhgOutHandle, uint8_t _u8Type, const void* _pDataBlob, uint32_t _u32ItemWidth, uint32_t _u32ItemCount) {
	VkBufferCreateInfo bciBufferInfo;

	switch (_u8Type) {
	case 0: { //Vertex
		bciBufferInfo = {
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.size = _u32ItemWidth * _u32ItemCount,
			.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = nullptr
		};
	} break;
	case 1: { //Index

	} break;
	case 2: { //Uniform

	} break;
	default: {
		throw std::runtime_error("ERROR: Attempted to construct a buffer of NONE type!");
	} break;
	}

	if (vkCreateBuffer(PlatformRenderer::g_vVars.g_dDeviceHandle, &bciBufferInfo, nullptr, reinterpret_cast<VkBuffer*>(&_bhgOutHandle.m_u64UpperParam)) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create buffer!");
	}

	VkBuffer bBufferHandle = reinterpret_cast<VkBuffer>(_bhgOutHandle.m_u64UpperParam);

	VkMemoryRequirements mrRequirements;
	vkGetBufferMemoryRequirements(PlatformRenderer::g_vVars.g_dDeviceHandle, bBufferHandle, &mrRequirements);

	VkMemoryAllocateInfo maiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = FindMemoryType(mrRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	};

	if (vkAllocateMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, &maiAllocInfo, nullptr, reinterpret_cast<VkDeviceMemory*>(&_bhgOutHandle.m_u64LowerParam)) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate buffer memory!");
	}

	VkDeviceMemory dmMemoryHandle = reinterpret_cast<VkDeviceMemory>(_bhgOutHandle.m_u64LowerParam);

	vkBindBufferMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, bBufferHandle, dmMemoryHandle, 0);

	void* pvData;
	vkMapMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, dmMemoryHandle, 0, bciBufferInfo.size, 0, &pvData);

	memcpy(pvData, _pDataBlob, mrRequirements.size);

	vkUnmapMemory(PlatformRenderer::g_vVars.g_dDeviceHandle, dmMemoryHandle);

	g_blData.g_mBufferTypeTable[bBufferHandle] = {
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