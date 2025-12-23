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

	VkDescriptorPool CreatePool(VkDevice _dDeviceHandle, uint32 _u32SetCount, Span<PoolSizeRatio> _spRatios);

	Array<PoolSizeRatio> m_vPoolSizeRatios;
	Array<VkDescriptorPool> m_vFullPools;
	Array<VkDescriptorPool> m_vReadyPools;
	uint32 m_u32SetsPerPool = 0;

public:
	void Init(VkDevice _dDeviceHandle, uint32 _u32InitialSetCount, Span<PoolSizeRatio> _spRatios);

	void ResetPools(VkDevice _dDeviceHandle);

	void Cleanup(VkDevice _dDeviceHandle);

	VkDescriptorSet AllocateDescriptorSet(VkDevice _dDeviceHandle, VkDescriptorSetLayout _dslLayout);
};

struct VkDescriptorWriter {
	DoubleEndedQueue<VkDescriptorImageInfo> m_dImageInfos;
	DoubleEndedQueue<VkDescriptorBufferInfo> m_dBufferInfos;
	Array<VkWriteDescriptorSet> m_vWriteBuffer;

	void WriteImage(uint32 _u32Binding, VkImageView _ivImageView, VkSampler _sSampler, VkImageLayout _ilImageLayout, VkDescriptorType _dtType);
	void WriteBuffer(uint32 _u32Binding, VkBuffer _bBuffer, size_t _sSize, size_t _sOffset, VkDescriptorType _dtType);

	void Clear();
	void UpdateDescriptorSets(VkDevice _dDeviceHandle, VkDescriptorSet _dsSet);
};