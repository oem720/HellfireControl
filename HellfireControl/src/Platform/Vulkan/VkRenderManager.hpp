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
		vkDestroySemaphore(_dDevice, m_sImageAvailableSemaphore, VK_NULL_HANDLE);
		vkDestroySemaphore(_dDevice, m_sRenderFinishedSemaphore, VK_NULL_HANDLE);
		vkDestroyFence(_dDevice, m_fInFlightFence, VK_NULL_HANDLE);

		m_dpmDescriptorPool.Cleanup(_dDevice);

		vkFreeCommandBuffers(_dDevice, m_cpCommandPool, 1, &m_cbMasterCommandBuffer);
		vkDestroyCommandPool(_dDevice, m_cpCommandPool, VK_NULL_HANDLE);
	}
};

class VkRenderManager {
private:
	static uint32 m_u32CurrentFrame;

	static VkInstance m_iInstance;
	static VkPhysicalDevice m_pdPhysicalDevice;
	static VkSurfaceKHR m_sSurface;
	static VkDevice m_dDeviceHandle;
	static VkQueue m_qGraphicsQueue;
	static VkQueue m_qPresentQueue;
	static VkSwapchainKHR m_scSwapchain;

	static VkFormat m_fFormat;
	static VkExtent2D m_eExtent;

	static Array<VkImage> m_vSwapchainImages;
	static FixedArray<VkFrameData, HC_MAX_FRAMES_IN_FLIGHT> m_arrFrames;

	static Map<VkDescriptorType, uint32> m_mDescriptorTypeCounts;

	static void CreateInstance(const String& _strAppName, uint32 _u32AppVersion);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapchain(WindowHandleGeneric _whgHandle);
	static void CreateFrameData();

	static void CleanupSwapchain();
	static void RecreateSwapchain(WindowHandleGeneric _whgHandle);

	friend class RenderManager;
	friend class VkRenderer;
public:
	static [[nodiscard]] HC_INLINE const VkDevice GetDevice() { return m_dDeviceHandle; }
	static [[nodiscard]] HC_INLINE const VkPhysicalDevice GetPhysicalDevice() { return m_pdPhysicalDevice; }

	static VkCommandBuffer CreateSingleUseCommandBuffer();
	static void SubmitSingleUseCommandBuffer(VkCommandBuffer _cbBuffer);
};