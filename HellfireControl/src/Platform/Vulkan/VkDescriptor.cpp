
#include <Platform/Vulkan/VkDescriptor.hpp>
#include <HellfireControl/Math/Math.hpp>

#include <Platform/Vulkan/VkRenderer.hpp>

void VkDescriptorPoolManager::Init(VkDevice _dDeviceHandle, uint32 _u32InitialSetCount, Span<PoolSizeRatio> _spRatios) {
	m_vPoolSizeRatios = Array<PoolSizeRatio>(_spRatios.begin(), _spRatios.end());

	m_vReadyPools.push_back(CreatePool(_dDeviceHandle, _u32InitialSetCount, _spRatios));

	m_u32SetsPerPool = Math::Clamp(static_cast<uint32>(_u32InitialSetCount * 1.5f), 0U, HC_VULKAN_DESCRIPTOR_POOL_SIZE_HARD_LIMIT);
}

void VkDescriptorPoolManager::ResetPools(VkDevice _dDeviceHandle) {
	for (auto aPool : m_vReadyPools) {
		vkResetDescriptorPool(_dDeviceHandle, aPool, 0);
	}

	for (auto aPool : m_vFullPools) {
		vkResetDescriptorPool(_dDeviceHandle, aPool, 0);
		m_vReadyPools.push_back(aPool);
	}

	m_vFullPools.clear();
}

void VkDescriptorPoolManager::Cleanup(VkDevice _dDeviceHandle) {
	for (auto aPool : m_vReadyPools) {
		vkDestroyDescriptorPool(_dDeviceHandle, aPool, nullptr);
	}

	for (auto aPool : m_vFullPools) {
		vkDestroyDescriptorPool(_dDeviceHandle, aPool, nullptr);
	}

	m_vReadyPools.clear();
	m_vFullPools.clear();
}

VkDescriptorSet VkDescriptorPoolManager::AllocateDescriptorSet(VkDevice _dDeviceHandle, VkDescriptorSetLayout _dslLayout) {
	VkDescriptorPool dpPool = GetPool(_dDeviceHandle);

	VkDescriptorSetAllocateInfo dsaiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = dpPool,
		.descriptorSetCount = 1,
		.pSetLayouts = &_dslLayout
	};

	VkDescriptorSet dsAllocatedSet = VK_NULL_HANDLE;

	VkResult vResult = vkAllocateDescriptorSets(_dDeviceHandle, &dsaiAllocInfo, &dsAllocatedSet);

	if (vResult == VK_ERROR_OUT_OF_POOL_MEMORY || vResult == VK_ERROR_FRAGMENTED_POOL) {
		m_vFullPools.push_back(dpPool);

		dpPool = GetPool(_dDeviceHandle);
		dsaiAllocInfo.descriptorPool = dpPool;

		if (vkAllocateDescriptorSets(_dDeviceHandle, &dsaiAllocInfo, &dsAllocatedSet) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to allocate descriptor set!");
		}
	}

	if (vResult == VK_SUCCESS) {
		m_vReadyPools.push_back(dpPool);

		return dsAllocatedSet;
	}

	throw std::runtime_error("ERROR: Failed to allocate descriptor set!");
}

VkDescriptorPool VkDescriptorPoolManager::GetPool(VkDevice _dDeviceHandle) {
	VkDescriptorPool dpPoolToReturn = VK_NULL_HANDLE;

	if (m_vReadyPools.size() != 0) {
		dpPoolToReturn = m_vReadyPools.back();
		m_vReadyPools.pop_back();
	}
	else {
		dpPoolToReturn = CreatePool(_dDeviceHandle, m_u32SetsPerPool, m_vPoolSizeRatios);

		m_u32SetsPerPool = Math::Clamp(static_cast<uint32>(m_u32SetsPerPool * 1.5f), 0U, HC_VULKAN_DESCRIPTOR_POOL_SIZE_HARD_LIMIT);
	}

	return dpPoolToReturn;
}

VkDescriptorPool VkDescriptorPoolManager::CreatePool(VkDevice _dDeviceHandle, uint32 _u32SetCount, Span<PoolSizeRatio> _spRatios) {
	Array<VkDescriptorPoolSize> vPoolSizes;

	for (PoolSizeRatio psrRatio : _spRatios) {
		vPoolSizes.push_back(VkDescriptorPoolSize{
			.type = psrRatio.m_dtType,
			.descriptorCount = static_cast<uint32>(_u32SetCount * psrRatio.m_fRatio)
			});
	}

	VkDescriptorPoolCreateInfo dpciPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.maxSets = _u32SetCount,
		.poolSizeCount = static_cast<uint32>(vPoolSizes.size()),
		.pPoolSizes = vPoolSizes.data()
	};

	VkDescriptorPool dpCreatedPool = VK_NULL_HANDLE;

	if (vkCreateDescriptorPool(_dDeviceHandle, &dpciPoolCreateInfo, nullptr, &dpCreatedPool) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create descriptor pool!");
	}

	return dpCreatedPool;
}

VkDescriptorSetLayoutBuilder& VkDescriptorSetLayoutBuilder::AddBinding(const HCShaderVar& _svVar, VkShaderStageFlagBits _ssfbStage) {
	auto aIter = std::find_if(
		m_vBindings.begin(),
		m_vBindings.end(),
		[&](const VkDescriptorSetLayoutBinding& _dslbBinding) {
			return _dslbBinding.binding == _svVar.m_arrData[0];
		}
	);

	if (aIter != m_vBindings.end()) {
		if (aIter->descriptorType == VkRenderer::m_mShaderVarTranslationTable[static_cast<HCShaderVarType>(_svVar.m_u16Type)]) {
			aIter->stageFlags |= _ssfbStage;
		}

		return *this;
	}

	m_vBindings.push_back(
		VkDescriptorSetLayoutBinding{
			.binding = _svVar.m_arrData[0],
			.descriptorType = VkRenderer::m_mShaderVarTranslationTable[static_cast<HCShaderVarType>(_svVar.m_u16Type)],
			.descriptorCount = 1,
			.stageFlags = static_cast<VkShaderStageFlags>(_ssfbStage),
			.pImmutableSamplers = VK_NULL_HANDLE
		}
	);

	return *this;
}

VkDescriptorSetLayout VkDescriptorSetLayoutBuilder::Build(VkDevice _dDeviceHandle) {
	VkDescriptorSetLayoutCreateInfo dslciLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.bindingCount = static_cast<uint32>(m_vBindings.size()),
		.pBindings = m_vBindings.data()
	};

	VkDescriptorSetLayout dslLayout = VK_NULL_HANDLE;

	if (vkCreateDescriptorSetLayout(_dDeviceHandle, &dslciLayoutInfo, nullptr, &dslLayout) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create descriptor set layout!");
	}

	Clear();

	return dslLayout;
}

void VkDescriptorSetLayoutBuilder::Clear() {
	m_vBindings.clear();
}

void VkDescriptorWriter::WriteImage(uint32 _u32Binding, VkImageView _ivImageView, VkSampler _sSampler, VkImageLayout _ilImageLayout, VkDescriptorType _dtType) {
	VkDescriptorImageInfo& diiInfo = m_dImageInfos.emplace_back(
		VkDescriptorImageInfo{
			.sampler = _sSampler,
			.imageView = _ivImageView,
			.imageLayout = _ilImageLayout
		}
	);

	VkWriteDescriptorSet wdsWrite = {
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = VK_NULL_HANDLE,
		.dstBinding = _u32Binding,
		.descriptorCount = 1,
		.descriptorType = _dtType,
		.pImageInfo = &diiInfo
	};

	m_vWriteBuffer.push_back(wdsWrite);
}

void VkDescriptorWriter::WriteBuffer(uint32 _u32Binding, VkBuffer _bBuffer, size_t _sSize, size_t _sOffset, VkDescriptorType _dtType) {
	VkDescriptorBufferInfo& dbiInfo = m_dBufferInfos.emplace_back(
		VkDescriptorBufferInfo {
			.buffer = _bBuffer,
			.offset = _sOffset,
			.range = _sSize
		}
	);

	VkWriteDescriptorSet wdsWrite = {
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.pNext = nullptr,
		.dstSet = VK_NULL_HANDLE,
		.dstBinding = _u32Binding,
		.descriptorCount = 1,
		.descriptorType = _dtType,
		.pBufferInfo = &dbiInfo
	};

	m_vWriteBuffer.push_back(wdsWrite);
}

void VkDescriptorWriter::Clear() {
	m_dBufferInfos.clear();
	m_dImageInfos.clear();
	m_vWriteBuffer.clear();
}

void VkDescriptorWriter::UpdateDescriptorSets(VkDevice _dDeviceHandle, VkDescriptorSet _dsSet) {
	for (auto& aWrite : m_vWriteBuffer) {
		aWrite.dstSet = _dsSet;
	}

	vkUpdateDescriptorSets(_dDeviceHandle, static_cast<uint32>(m_vWriteBuffer.size()), m_vWriteBuffer.data(), 0, nullptr);
}
