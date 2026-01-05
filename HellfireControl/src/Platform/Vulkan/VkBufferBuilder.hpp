#pragma once

#include <Platform/GLCommon.hpp>

#include <Platform/Vulkan/VkRenderManager.hpp>

struct VkBufferData {
	VkBuffer m_bBuffer = VK_NULL_HANDLE;
	VkDeviceMemory m_dmBufferMemory = VK_NULL_HANDLE;

	void Destroy() {
		vkDestroyBuffer(VkRenderManager::GetDevice(), m_bBuffer, nullptr);
		vkFreeMemory(VkRenderManager::GetDevice(), m_dmBufferMemory, nullptr);
	}
};

class VkBufferBuilder {
private:
	VkBufferUsageFlags m_bufFlags = 0;
	VkMemoryPropertyFlags m_mpfFlags = 0;

	uint32 m_u32DataSize;
	void* m_pData;

	VkBufferData CreateBuffer(VkBufferUsageFlags _bufFlags);
	void CopyBuffer(VkBuffer _bSource, VkBuffer _bDestination);
	uint32_t FindMemoryType(uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags);

public:
	VkBufferBuilder& SetBufferFlags(VkBufferUsageFlags _bufFlags, VkMemoryPropertyFlags _mpfFlags);
	VkBufferBuilder& SetData(uint32 _u32Size, const void* _pData);

	VkBufferData Build();

	void Clear();
};