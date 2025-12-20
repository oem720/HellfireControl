#pragma once

#include <Platform/GLCommon.hpp>
#include <Platform/Vulkan/VkDescriptor.hpp>

class VkRenderer;

struct VkFrameData {
	VkImageView m_ivSwapchainImageView = VK_NULL_HANDLE;
	VkSemaphore m_sImageAvailableSemaphore = VK_NULL_HANDLE;
	VkSemaphore m_sRenderFinishedSemaphore = VK_NULL_HANDLE;
	VkFence m_fInFlightFence = VK_NULL_HANDLE;
	VkCommandPool m_cpCommandPool = VK_NULL_HANDLE;
	VkCommandBuffer m_cbMasterCommandBuffer = VK_NULL_HANDLE;
	VkDescriptorPoolManager m_dpmDescriptorPool;

	void Cleanup(VkDevice _dDevice) {
		//Image views are cleaned up during swapchain cleanup
		vkDestroySemaphore(_dDevice, m_sImageAvailableSemaphore, nullptr);
		vkDestroySemaphore(_dDevice, m_sRenderFinishedSemaphore, nullptr);
		vkDestroyFence(_dDevice, m_fInFlightFence, nullptr);

		m_dpmDescriptorPool.Cleanup(_dDevice);

		vkFreeCommandBuffers(_dDevice, m_cpCommandPool, 1, &m_cbMasterCommandBuffer);
		vkDestroyCommandPool(_dDevice, m_cpCommandPool, nullptr);
	}
};

class VkRenderManager {
private:
	static uint32_t m_u32CurrentFrame;

	static VkInstance m_iInstance;
	static VkPhysicalDevice m_pdPhysicalDevice;
	static VkSurfaceKHR m_sSurface;
	static VkDevice m_dDeviceHandle;
	static VkQueue m_qGraphicsQueue;
	static VkQueue m_qPresentQueue;
	static VkSwapchainKHR m_scSwapchain;

	static VkFormat m_fFormat;
	static VkExtent2D m_eExtent;

	static std::vector<VkImage> m_vSwapchainImages;
	static std::array<VkFrameData, HC_MAX_FRAMES_IN_FLIGHT> m_arrFrames;

	static std::map<VkDescriptorType, uint32_t> m_mDescriptorTypeCounts;

	static void CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapchain(WindowHandleGeneric _whgHandle);
	static void CreateFrameData();

	static VkCommandBuffer CreateSingleUseCommandBuffer();
	static void SubmitSingleUseCommandBuffer(VkCommandBuffer _cbBuffer);

	static void CleanupSwapchain();
	static void RecreateSwapchain(WindowHandleGeneric _whgHandle);

	friend class RenderManager;
	friend class VkRenderer;
};