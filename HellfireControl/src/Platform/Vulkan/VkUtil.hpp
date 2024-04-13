#pragma once

#include <Platform/GLCommon.hpp>

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

class VkUtil {
public:
	static VkCommandBuffer BeginSingleTimeCommands();
	static void EndSingleTimeCommands(VkCommandBuffer _cbBuffer);
	static VkImageView CreateImageView(VkImage _iImage, VkFormat _fFormat, VkImageAspectFlags _iafFlags);
	static void CreateImage(uint32_t _u32Width, uint32_t _u32Height, VkFormat _fFormat, VkImageTiling _itTiling, VkImageUsageFlags _iufUsage, VkMemoryPropertyFlags _mpfProperties, VkImage& _iImage, VkDeviceMemory& _dmMem);
	static void TransitionImageLayout(VkImage _iImage, VkFormat _fFormat, VkImageLayout _ilLayoutOld, VkImageLayout _ilLayoutNew);
	static void CopyBufferToImage(VkBuffer _bBuffer, VkImage _iImage, uint32_t _u32Width, uint32_t _u32Height);
	static VkFormat FindSupportedFormat(const std::vector<VkFormat>& _vCandidates, VkImageTiling _itTiling, VkFormatFeatureFlags _fffFeatures);
	static VkFormat FindDepthFormat();
	static bool HasStencilComponent(VkFormat _fFormat);
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
	static bool GetValidationLayersEnabled();
	static std::vector<const char*> GetValidationLayers();
	static std::vector<const char*> GetInstanceExtensions();
	static std::vector<const char*> GetDeviceExtensions();
};