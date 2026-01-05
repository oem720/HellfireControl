
#include <Platform/Vulkan/VkBufferBuilder.hpp>

VkBufferBuilder& VkBufferBuilder::SetBufferFlags(VkBufferUsageFlags _bufFlags, VkMemoryPropertyFlags _mpfFlags) {
	m_bufFlags = _bufFlags;
	m_mpfFlags = _mpfFlags;
	
	return *this;
}

VkBufferBuilder& VkBufferBuilder::SetData(uint32 _u32Size, const void* _pData) {
	m_u32DataSize = _u32Size;
	m_pData = const_cast<void*>(_pData);
	
	return *this;
}

VkBufferData VkBufferBuilder::Build() {
	VkBufferData bdStagingBuffer = CreateBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

	void* pData = nullptr;

	vkMapMemory(VkRenderManager::GetDevice(), bdStagingBuffer.m_dmBufferMemory, 0, m_u32DataSize, 0, &pData);

	memcpy(pData, m_pData, m_u32DataSize);

	vkUnmapMemory(VkRenderManager::GetDevice(), bdStagingBuffer.m_dmBufferMemory);

	VkBufferData bdReturnedBuffer = CreateBuffer(VK_BUFFER_USAGE_TRANSFER_DST_BIT | m_bufFlags);

	CopyBuffer(bdStagingBuffer.m_bBuffer, bdReturnedBuffer.m_bBuffer);

	bdStagingBuffer.Destroy();

	Clear();

	return bdReturnedBuffer;
}

void VkBufferBuilder::Clear() {
	m_bufFlags = 0;
	m_mpfFlags = 0;
	m_u32DataSize = 0;
	m_pData = nullptr;
}

VkBufferData VkBufferBuilder::CreateBuffer(VkBufferUsageFlags _bufFlags) {
	VkBufferData bdReturn = {};

	VkBufferCreateInfo bciBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.size = m_u32DataSize,
		.usage = _bufFlags,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr
	};

	if (vkCreateBuffer(VkRenderManager::GetDevice(), &bciBufferInfo, nullptr, &bdReturn.m_bBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create buffer object!");
	}

	VkMemoryRequirements mrRequirements = {};
	vkGetBufferMemoryRequirements(VkRenderManager::GetDevice(), bdReturn.m_bBuffer, &mrRequirements);

	VkMemoryAllocateInfo maiAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = FindMemoryType(mrRequirements.memoryTypeBits, m_mpfFlags)
	};

	if (vkAllocateMemory(VkRenderManager::GetDevice(), &maiAllocateInfo, nullptr, &bdReturn.m_dmBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("Failed to allocate buffer memory!");
	}

	vkBindBufferMemory(VkRenderManager::GetDevice(), bdReturn.m_bBuffer, bdReturn.m_dmBufferMemory, 0);

	return bdReturn;
}

void VkBufferBuilder::CopyBuffer(VkBuffer _bSource, VkBuffer _bDestination) {
	VkCommandBuffer cbBuffer = VkRenderManager::CreateSingleUseCommandBuffer();

	VkBufferCopy bcCopyRegion = {
		.srcOffset = 0,
		.dstOffset = 0,
		.size = m_u32DataSize
	};

	vkCmdCopyBuffer(cbBuffer, _bSource, _bDestination, 1, &bcCopyRegion);

	VkRenderManager::SubmitSingleUseCommandBuffer(cbBuffer);
}

uint32_t VkBufferBuilder::FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags) {
	VkPhysicalDeviceMemoryProperties pdmpMemProperties;
	vkGetPhysicalDeviceMemoryProperties(VkRenderManager::GetPhysicalDevice(), &pdmpMemProperties);

	for (uint32_t ndx = 0; ndx < pdmpMemProperties.memoryTypeCount; ++ndx) {
		if (_u32TypeFilter & (1 << ndx) && (pdmpMemProperties.memoryTypes[ndx].propertyFlags & _mpfFlags) == _mpfFlags) {
			return ndx;
		}
	}

	throw std::runtime_error("ERROR: Failed to find suitable memory type!");
}