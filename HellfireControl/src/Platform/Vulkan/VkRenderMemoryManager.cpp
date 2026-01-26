
#include <HellfireControl/Render/RenderMemoryManager.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderMemoryManager.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>

#define HC_VULKAN_PROTOTYPE_BUFFER_USAGE_BITS (VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)

VkDeviceMemory VkRenderMemoryManager::m_dmMemoryBlock = VK_NULL_HANDLE;
Map<uint32, VkBufferData> VkRenderMemoryManager::m_mBufferDataMap = {};

void RenderMemoryManager::InitPlatformMemoryPool() {
	VkRenderMemoryManager::Init(m_u32TotalMemorySize);
}

void RenderMemoryManager::Grow() {
	//Test stub function for now. Future implementation will algorithmically determine new m_dsSize and may possible signal for defragmentation.
	VkRenderMemoryManager::Resize(m_u32TotalMemorySize, m_u32TotalMemorySize * 2);

	m_u32TotalMemorySize *= 2;
}

void RenderMemoryManager::CleanupPlatformMemoryPool() {
	VkRenderMemoryManager::Cleanup();
}

void VkRenderMemoryManager::Init(uint32 _u32InitialSize) {
	m_dmMemoryBlock = AllocateMemoryBlock(_u32InitialSize);
}

void VkRenderMemoryManager::Resize(uint32 _u32OriginalSize, uint32 _u32NewSize) {
	VkBuffer bDummyBuffer = CreateDummyBuffer(_u32OriginalSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

	vkBindBufferMemory(VkRenderManager::GetDevice(), bDummyBuffer, m_dmMemoryBlock, 0);

	VkBuffer bNewDummyBuffer = CreateDummyBuffer(_u32NewSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT);

	VkMemoryRequirements mrRequirements = {};

	vkGetBufferMemoryRequirements(VkRenderManager::GetDevice(), bNewDummyBuffer, &mrRequirements);

	VkDeviceMemory dmNewMemoryBlock = AllocateMemoryBlock(mrRequirements);

	vkBindBufferMemory(VkRenderManager::GetDevice(), bNewDummyBuffer, dmNewMemoryBlock, 0);

	CopyMemoryBlock(bDummyBuffer, bNewDummyBuffer, _u32OriginalSize);

	Map<uint32, VkBufferData> mReboundBuffers = RecreateBufferDataMap();

	//Find a way to signal main thread to pause so we can fully swap the map and memory blocks out
	

	VkDeviceMemory dmOldMemoryBlock = m_dmMemoryBlock;
	m_dmMemoryBlock = dmNewMemoryBlock;
	m_mBufferDataMap = std::move(mReboundBuffers);

	vkDestroyBuffer(VkRenderManager::GetDevice(), bDummyBuffer, nullptr);
	vkDestroyBuffer(VkRenderManager::GetDevice(), bNewDummyBuffer, nullptr);
	vkFreeMemory(VkRenderManager::GetDevice(), dmOldMemoryBlock, nullptr);
}

void VkRenderMemoryManager::Cleanup() {
	if(m_dmMemoryBlock != VK_NULL_HANDLE) {
		vkFreeMemory(VkRenderManager::GetDevice(), m_dmMemoryBlock, nullptr);
		m_dmMemoryBlock = VK_NULL_HANDLE;
	}
}

VkBuffer VkRenderMemoryManager::CreateDummyBuffer(uint32 _u32Size, VkBufferUsageFlags _bufTransferBit) {
	VkBufferCreateInfo bciDummyBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.size = _u32Size,
		.usage = HC_VULKAN_PROTOTYPE_BUFFER_USAGE_BITS | _bufTransferBit,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr
	};

	VkBuffer bDummyBuffer = VK_NULL_HANDLE;

	if (vkCreateBuffer(VkRenderManager::GetDevice(), &bciDummyBufferInfo, nullptr, &bDummyBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create dummy m_bBuffer for memory requirements query in VkRenderMemoryManager::Init!");
	}

	return bDummyBuffer;
}

VkDeviceMemory VkRenderMemoryManager::AllocateMemoryBlock(uint32 _u32Size) {
	VkBuffer bDummyBuffer = CreateDummyBuffer(_u32Size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

	VkMemoryRequirements mrRequirements = {};

	vkGetBufferMemoryRequirements(VkRenderManager::GetDevice(), bDummyBuffer, &mrRequirements);

	vkDestroyBuffer(VkRenderManager::GetDevice(), bDummyBuffer, nullptr);

	return AllocateMemoryBlock(mrRequirements);
}

VkDeviceMemory VkRenderMemoryManager::AllocateMemoryBlock(VkMemoryRequirements& _mrRequirements) {
	VkDeviceMemory dmMemoryBlock = VK_NULL_HANDLE;

	VkMemoryAllocateInfo maiAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = _mrRequirements.size,
		.memoryTypeIndex = GetMemoryType(_mrRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	};

	if (vkAllocateMemory(VkRenderManager::GetDevice(), &maiAllocateInfo, nullptr, &dmMemoryBlock) != VK_SUCCESS) {
		throw std::runtime_error("Failed to allocate memory block in VkRenderMemoryManager::Init!");
	}

	return dmMemoryBlock;
}

void VkRenderMemoryManager::CopyMemoryBlock(VkBuffer _bSrcBuffer, VkBuffer _bDstBuffer, VkDeviceSize _dsSize) {
	VkCommandBuffer cbBuffer = VkRenderManager::CreateSingleUseCommandBuffer();

	VkBufferCopy bcCopyRegion = {
		.srcOffset = 0,
		.dstOffset = 0,
		.size = _dsSize
	};

	vkCmdCopyBuffer(cbBuffer, _bSrcBuffer, _bDstBuffer, 1, &bcCopyRegion);

	VkRenderManager::SubmitSingleUseCommandBuffer(cbBuffer);
}

Map<uint32, VkBufferData> VkRenderMemoryManager::RecreateBufferDataMap() {
	Map<uint32, VkBufferData> mReboundBuffers = {};

	for (const auto& aBufferData : m_mBufferDataMap) {
		VkBufferCreateInfo bciInfo = {
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.size = aBufferData.second.m_dsSize,
			.usage = aBufferData.second.m_bufUsageFlags,
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = nullptr,
		};

		VkBuffer bNewBuffer = VK_NULL_HANDLE;

		if (vkCreateBuffer(VkRenderManager::GetDevice(), &bciInfo, nullptr, &bNewBuffer) != VK_SUCCESS) {
			throw std::runtime_error("Failed to recreate buffer in VkRenderMemoryManager::RecreateBufferDataMap!");
		}

		vkBindBufferMemory(VkRenderManager::GetDevice(), bNewBuffer, m_dmMemoryBlock, aBufferData.second.m_dsOffset);

		mReboundBuffers[aBufferData.first] = VkBufferData {
			.m_bBuffer = bNewBuffer,
			.m_dsOffset = aBufferData.second.m_dsOffset,
			.m_dsSize = aBufferData.second.m_dsSize,
			.m_bufUsageFlags = aBufferData.second.m_bufUsageFlags
		};
	}

	return mReboundBuffers;
}

uint32 VkRenderMemoryManager::GetMemoryType(uint32 _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags) {
	VkPhysicalDeviceMemoryProperties pdmpMemProperties = {};

	vkGetPhysicalDeviceMemoryProperties(VkRenderManager::GetPhysicalDevice(), &pdmpMemProperties);

	for (uint32_t ndx = 0; ndx < pdmpMemProperties.memoryTypeCount; ++ndx) {
		if (_u32TypeFilter & (1 << ndx) && (pdmpMemProperties.memoryTypes[ndx].propertyFlags & _mpfFlags) == _mpfFlags) {
			return ndx;
		}
	}

	throw std::runtime_error("ERROR: Failed to find suitable memory type!");
}

#endif