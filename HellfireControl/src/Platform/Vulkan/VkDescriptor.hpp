#pragma once

#include <Platform/GLCommon.hpp>

#define HC_VULKAN_DESCRIPTOR_POOL_SIZE_HARD_LIMIT 4096U //Find a way to make these values configurable
#define HC_VULKAN_DESCRIPTOR_POOL_INITIAL_SIZE (HC_VULKAN_DESCRIPTOR_POOL_SIZE_HARD_LIMIT >> 2)

class VkDescriptorPoolManager {
public:
	struct PoolSizeRatio {
		VkDescriptorType m_dtType;
		float m_fRatio;
	};

private:
	VkDescriptorPool GetPool(VkDevice _dDeviceHandle);

	VkDescriptorPool CreatePool(VkDevice _dDeviceHandle, uint32_t _u32SetCount, std::span<PoolSizeRatio> _spRatios);

	std::vector<PoolSizeRatio> m_vPoolSizeRatios;
	std::vector<VkDescriptorPool> m_vFullPools;
	std::vector<VkDescriptorPool> m_vReadyPools;
	uint32_t m_u32SetsPerPool = 0;

public:
	void Init(VkDevice _dDeviceHandle, uint32_t _u32InitialSetCount, std::span<PoolSizeRatio> _spRatios);

	void ResetPools(VkDevice _dDeviceHandle);

	void Cleanup(VkDevice _dDeviceHandle);

	VkDescriptorSet AllocateDescriptorSet(VkDevice _dDeviceHandle, VkDescriptorSetLayout _dslLayout);
};

struct DescriptorWriter {

};