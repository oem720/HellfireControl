#pragma once

#include <Platform/GLCommon.hpp>

class VkRenderManager {
private:
	static uint32_t m_u32CurrentFrame;
	static std::array<VkClearValue, 2> m_arrClearValues;

	static VkInstance m_iInstance;
	static VkPhysicalDevice m_pdPhysicalDevice;
	static VkSurfaceKHR m_sSurface;
	static VkDevice m_dDeviceHandle;
	static VkQueue m_qGraphicsQueue;
	static VkQueue m_qPresentQueue;
	static VkSwapchainKHR m_scSwapchain;
	static VkCommandPool m_cpCommandPool;
	static VkImage m_iDepth;
	static VkImageView m_ivDepthView;
	static VkDeviceMemory m_dmDepthMem;
	static VkRenderPass m_rpRenderPass;

	static VkFormat m_fFormat;
	static VkExtent2D m_eExtent;

	static std::vector<VkImage> m_vSwapchainImages;
	static std::vector<VkImageView> m_vSwapchainImageViews;
	static std::vector<VkFramebuffer> m_vSwapchainFramebuffers;
	static std::vector<VkSemaphore> m_vImageAvailableSemaphores;
	static std::vector<VkSemaphore> m_vRenderFinishedSemaphores;
	static std::vector<VkFence> m_vInFlightFences;

	static void CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapchain(WindowHandleGeneric _whgHandle);
	static void CreateSwapchainImageViews();
	static void CreateCommandPool();
	static void CreateDepthResources();
	static void CreateFinalRenderPass();
	static void CreateSwapchainFramebuffers();
	static void CreateSyncObjects();

	static VkCommandBuffer CreateSingleUseCommandBuffer();
	static void SubmitSingleUseCommandBuffer(VkCommandBuffer _cbBuffer);

	static void CleanupSwapchain();
	static void RecreateSwapchain(WindowHandleGeneric _whgHandle);

	friend class RenderManager;
};