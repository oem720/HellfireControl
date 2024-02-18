#pragma once

#include <HellfireControl/Core/Common.hpp>

#if HC_USE_VULKAN && !HC_USE_OPENGL

#if WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define HC_MAX_FRAMES_IN_FLIGHT 2

#include <vulkan/vulkan.h>

//TODO HANDLE WINDOW MODIFICATION

struct VkQueueFamilyIndices {
	std::optional<uint32_t> m_u32GraphicsFamily;
	std::optional<uint32_t> m_u32PresentFamily;

	HC_INLINE bool IsComplete() {
		return m_u32GraphicsFamily.has_value() && m_u32PresentFamily.has_value();
	}
	};

struct VkSwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR m_scCapabilities = {};
	std::vector<VkSurfaceFormatKHR> m_vFormats;
	std::vector<VkPresentModeKHR> m_vPresentModes;
};

struct VkVars {
	uint64_t g_u64WindowHandle = 0;
	uint32_t g_u32CurrentFrame = 0;

	VkInstance g_iInstance = VK_NULL_HANDLE;
	VkPhysicalDevice g_pdPhysicalDevice = VK_NULL_HANDLE;
	VkDevice g_dDeviceHandle = VK_NULL_HANDLE;
	VkQueue g_qGraphicsQueue = VK_NULL_HANDLE;
	VkQueue g_qPresentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR g_sSurface = VK_NULL_HANDLE;
	VkSwapchainKHR g_scSwapChain = VK_NULL_HANDLE;
	VkRenderPass g_rpRenderPass = VK_NULL_HANDLE;
	VkPipelineLayout g_plPipelineLayout = VK_NULL_HANDLE; //TEMPORARY ! ! !
	VkPipeline g_pPipeline = VK_NULL_HANDLE;
	VkCommandPool g_cpCommandPool = VK_NULL_HANDLE;

	VkFormat g_fFormat = {};
	VkExtent2D g_eExtent = {};
	VkClearValue g_cvClearColor = {};

	std::vector<VkCommandBuffer> g_vCommandBuffers;
	std::vector<VkSemaphore> g_vImageAvailableSemaphores;
	std::vector<VkSemaphore> g_vRenderFinishedSemaphores;
	std::vector<VkFence> g_vInFlightFences;
	std::vector<VkImage> g_vImages;
	std::vector<VkImageView> g_vImageViews;
	std::vector<VkFramebuffer> g_vFramebuffers;
};

static VkVars g_vVars = {};

#elif HC_USE_OPENGL && !HC_USE_VULKAN



#else

#error No or Improper Graphical API Specified!

#endif