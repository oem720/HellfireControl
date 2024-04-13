#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Math/Vector.hpp>

class PlatformRenderer {
	friend class PlatformBuffer;
	friend class PlatformRenderContext;
	friend class VkUtil;
private:
	static uint64_t						m_u64WindowHandle;
	static uint32_t						m_u32CurrentFrame;
	static bool							m_bFramebufferResized;
	static VkInstance					m_iInstance;
	static VkPhysicalDevice				m_pdPhysicalDevice;
	static VkDevice						m_dDeviceHandle;
	static VkQueue						m_qGraphicsQueue;
	static VkQueue						m_qPresentQueue;
	static VkSurfaceKHR					m_sSurface;
	static VkSwapchainKHR				m_scSwapChain;
	static VkRenderPass					m_rpRenderPass;
	static VkDescriptorSetLayout		m_dslDescriptorSetLayout;
	static VkCommandPool				m_cpCommandPool;
	static VkDescriptorPool				m_dpDescriptorPool;
	static VkSampler					m_sSampler;
	static VkImage						m_iDepth;
	static VkDeviceMemory				m_dmDepthMem;
	static VkImageView					m_ivDepthView;
	static VkFormat						m_fFormat;
	static VkExtent2D					m_eExtent;
	static std::array<VkClearValue, 2>	m_arrClearValues;
	static std::vector<VkCommandBuffer> m_vCommandBuffers;
	static std::vector<VkDescriptorSet>	m_vDescriptorSets;
	static std::vector<VkSemaphore>		m_vImageAvailableSemaphores;
	static std::vector<VkSemaphore>		m_vRenderFinishedSemaphores;
	static std::vector<VkFence>			m_vInFlightFences;
	static std::vector<VkImage>			m_vSwapchainImages;
	static std::vector<VkImageView>		m_vSwapchainImageViews;
	static std::vector<VkFramebuffer>	m_vFramebuffers;

	static VkImage imgTexture; //SUPER TEMPORARY ! ! !
	static VkDeviceMemory dmTextureMemory;
	static VkImageView ivTextureView;

	static void CreateInstance(const std::string& _strAppName, uint32_t _u32Version);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapChain();
	static void CreateSwapchainImageViews();
	static void CreateRenderPass();
	static void CreateCommandPool();
	static void CreateDepthResources();
	static void CreateFramebuffers();
	static void CreateTextureSampler();
	static void CreateCommandBuffer();
	static void CreateSyncObjects();
	static void CleanupSwapchain();
	static void RecreateSwapchain();

	static void CreateTextureImage();
	static void CreateTextureImageView();
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
	/// Prepares the renderer for drawing to the current frame
	/// </summary>
	static void BeginRenderPass();

	/// <summary>
	/// Submits all draw commands tied to the given render context
	/// </summary>
	/// <param name="_u32ContextID: The render context to draw from"></param>
	static void Draw(uint32_t _u32ContextID);

	/// <summary>
	/// Closes out the current render pass and posts the image to the screen
	/// </summary>
	static void Present();

	/// <summary>
	/// Destroys all allocated objects on the GPU and shuts down the rendering system.
	/// </summary>
	static void CleanupRenderer();

	/// <summary>
	/// Returns the actual active area that is being rendered to. In a fullscreen/borderless application, this number is equal to the window resolution.
	/// In a windowed application of any size, this number is not guaranteed to be equal to the resolution.
	/// </summary>
	/// <returns>
	/// Vec2F: Contains the width and height of the renderable area.
	/// </returns>
	[[nodiscard]] HC_INLINE static const Vec2F GetRenderableExtent() {
		return Vec2F(static_cast<float>(m_eExtent.width), static_cast<float>(m_eExtent.height));
	}
};