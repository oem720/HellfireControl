#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Math/Vector.hpp>

struct VertexSimple {
	Vec3F m_v2Position;
	Vec3F m_v3Color;
	Vec2F m_v2TexCoord;

	static VkVertexInputBindingDescription GetBindingDescription() {
		VkVertexInputBindingDescription vibdVertexBindingDesc = {
			.binding = 0,
			.stride = sizeof(VertexSimple),
			.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
		};

		return vibdVertexBindingDesc;
	}

	static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> vAttributes = {
			VkVertexInputAttributeDescription {
				.location = 0,
				.binding = 0,
				.format = VK_FORMAT_R32G32B32_SFLOAT,
				.offset = offsetof(VertexSimple, m_v2Position)
			},
			VkVertexInputAttributeDescription {
				.location = 1,
				.binding = 0,
				.format = VK_FORMAT_R32G32B32_SFLOAT,
				.offset = offsetof(VertexSimple, m_v3Color)
			},
			VkVertexInputAttributeDescription {
				.location = 2,
				.binding = 0,
				.format = VK_FORMAT_R32G32_SFLOAT,
				.offset = offsetof(VertexSimple, m_v2TexCoord)
			}
		};

		return vAttributes;
	}
};

struct VkVertexData {
	VkVertexInputBindingDescription m_vibdBindingDescription;
	std::vector<VkVertexInputAttributeDescription> m_vAttributes;
};

class PlatformRenderer {
	friend class PlatformBuffer;
	friend class PlatformRenderContext;
private:
	struct VkQueueFamilyIndices {
		std::optional<uint32_t> m_u32GraphicsFamily;
		std::optional<uint32_t> m_u32PresentFamily;

		HC_INLINE bool IsComplete() const {
			return m_u32GraphicsFamily.has_value() && m_u32PresentFamily.has_value();
		}
	};

	struct VkSwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR m_scCapabilities = {};
		std::vector<VkSurfaceFormatKHR> m_vFormats;
		std::vector<VkPresentModeKHR> m_vPresentModes;
	};

	static uint64_t m_u64WindowHandle;
	static uint32_t m_u32CurrentFrame;
	static bool m_bFramebufferResized;

	static VkInstance m_iInstance;
	static VkPhysicalDevice m_pdPhysicalDevice;
	static VkDevice m_dDeviceHandle;
	static VkQueue m_qGraphicsQueue;
	static VkQueue m_qPresentQueue;
	static VkSurfaceKHR m_sSurface;
	static VkSwapchainKHR m_scSwapChain;
	static VkRenderPass m_rpRenderPass;
	static VkDescriptorSetLayout m_dslDescriptorSetLayout;
	static VkCommandPool m_cpCommandPool;
	static VkDescriptorPool m_dpDescriptorPool;
	static VkSampler m_sSampler;

	static VkImage m_iDepth;
	static VkDeviceMemory m_dmDepthMem;
	static VkImageView m_ivDepthView;

	static VkFormat m_fFormat;
	static VkExtent2D m_eExtent;

	static std::array<VkClearValue, 2> m_arrClearValues;
	static std::vector<VkCommandBuffer> m_vCommandBuffers;
	static std::vector<VkDescriptorSet> m_vDescriptorSets;
	static std::vector<VkSemaphore> m_vImageAvailableSemaphores;
	static std::vector<VkSemaphore> m_vRenderFinishedSemaphores;
	static std::vector<VkFence> m_vInFlightFences;
	static std::vector<VkImage> m_vImages;
	static std::vector<VkImageView> m_vImageViews;
	static std::vector<VkFramebuffer> m_vFramebuffers;

	static std::vector<VkBuffer> m_vUbo; //TODO: POSSIBLE TEMPORARY ! ! !
	static std::vector<VkDeviceMemory> m_vUboMem;
	static std::vector<void*> m_vUboMapped;

	static VkImage imgTexture; //SUPER TEMPORARY ! ! !
	static VkDeviceMemory dmTextureMemory;
	static VkImageView ivTextureView;

	static void CreateInstance(const std::string& _strAppName, uint32_t _u32Version);
	static void CreateSurface(uint64_t _u64WindowHandle);
	static void SelectPhysicalDevice();
	static void CreateLogicalDevice();
	static void CreateSwapChain();
	static void CreateImageViews();
	static void CreateRenderPass();
	static void CreateDescriptorSetLayout();
	static void CreateCommandPool();
	static void CreateDepthResources();
	static void CreateFramebuffers();

	static void CreateTextureImage(); //VERY EXTREMELY TEMPORARY ! ! !
	static void CreateTextureImageView();
	static void CreateImage(uint32_t _u32Width, uint32_t _u32Height, VkFormat _fFormat, VkImageTiling _itTiling, VkImageUsageFlags _iufUsage, VkMemoryPropertyFlags _mpfProperties, VkImage& _iImage, VkDeviceMemory& _dmMem);
	static void TransitionImageLayout(VkImage _iImage, VkFormat _fFormat, VkImageLayout _ilLayoutOld, VkImageLayout _ilLayoutNew);
	static void CopyBufferToImage(VkBuffer _bBuffer, VkImage _iImage, uint32_t _u32Width, uint32_t _u32Height);
	static void CreateUniformBuffers(); //TODO: POSSIBLE TEMPORARY ! ! !

	static void CreateTextureSampler();
	static void CreateDescriptorPool();
	static void CreateDescriptorSets();
	static void CreateCommandBuffer();
	static void CreateSyncObjects();

	static void RecordCommandBuffer(VkCommandBuffer _cbBuffer, uint32_t _u32ImageIndex);
	static VkCommandBuffer BeginSingleTimeCommands();
	static void EndSingleTimeCommands(VkCommandBuffer _cbBuffer);
	static VkImageView CreateImageView(VkImage _iImage, VkFormat _fFormat, VkImageAspectFlags _iafFlags);
	static VkFormat FindSupportedFormat(const std::vector<VkFormat>& _vCandidates, VkImageTiling _itTiling, VkFormatFeatureFlags _fffFeatures);
	static VkFormat FindDepthFormat();
	static bool HasStencilComponent(VkFormat _fFormat);
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
	static void UpdateUniformBuffer(uint32_t _u32CurrentImage); //VERY TEMPORARY ! ! !
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