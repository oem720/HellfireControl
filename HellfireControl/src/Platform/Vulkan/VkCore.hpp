#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Math/Vector.hpp>

struct VertexSimple {
	Vec2F m_v2Position;
	Vec3F m_v3Color;

	static VkVertexInputBindingDescription GetBindingDescription() {
		VkVertexInputBindingDescription vibdVertexBindingDesc = {
			.binding = 0,
			.stride = sizeof(VertexSimple),
			.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
		};

		return vibdVertexBindingDesc;
	}

	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> arrAttributes = {
			VkVertexInputAttributeDescription {
				.location = 0,
				.binding = 0,
				.format = VK_FORMAT_R32G32_SFLOAT,
				.offset = offsetof(VertexSimple, m_v2Position)
			},
			VkVertexInputAttributeDescription {
				.location = 1,
				.binding = 0,
				.format = VK_FORMAT_R32G32B32_SFLOAT,
				.offset = offsetof(VertexSimple, m_v3Color)
			}
		};

		return arrAttributes;
	}
};

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
	bool g_bFramebufferResized = false;

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

class PlatformRenderer {
	friend class PlatformBuffer;

private:
	static void CreateInstance(const std::string& _strAppName, uint32_t _u32Version);
	static void CreateSurface(uint64_t _u64WindowHandle);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapChain();
	static void CreateImageViews();
	static void CreateRenderPass();
	static void CreateGraphicsPipeline();
	static void CreateFramebuffers();
	static void CreateCommandPool();
	static void CreateCommandBuffer();
	static void CreateSyncObjects();
	static void RecordCommandBuffer(VkCommandBuffer _cbBuffer, uint32_t _u32ImageIndex);
	static void CleanupSwapchain();
	static void RecreateSwapchain();
	static void ValidateSupportedLayers();
	static bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice);
	static bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice);
	static VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice);
	static VkSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _pdDevice);
	static VkSurfaceFormatKHR SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats);
	static VkPresentModeKHR SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes);
	static VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities);
	static VkShaderModule CreateShaderModule(const std::vector<char>& _vCode);
	static void CheckWindowMinimized();

	static VkVars g_vVars;
public:
	/// <summary>
	/// Initializes the renderer using the given parameters
	/// </summary>
	/// <param name="_strAppName: The name of the app being registered. Needed for Instance creation"></param>
	/// <param name="_u32AppVersion: The version of the app being registered. Needed for Instance creation"></param>
	/// <param name="_u64WindowHandle: A handle to the render target window"></param>
	/// <param name="_v4ClearColor: A Vec4F representing the color that the framebuffer defaults to when no pixels are drawn there. Default: Black"></param>
	static void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor = Vec4F());

	/// <summary>
	/// Marks the framebuffer as needing to be updated, and Swapchain as needing recreation.
	/// </summary>
	static void MarkFramebufferUpdated();

	/// <summary>
	/// Renders the current frame and presents it to the screen.
	/// </summary>
	static void RenderFrame();

	/// <summary>
	/// Destroys all allocated objects on the GPU and shuts down the rendering system.
	/// </summary>
	static void CleanupRenderer();
};