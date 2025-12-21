#pragma once

#include <Platform/GLCommon.hpp>

struct VkQueueFamilyIndices {
	Optional<uint32> m_u32GraphicsFamily;
	Optional<uint32> m_u32PresentFamily;

	HC_INLINE bool IsComplete() const {
		return m_u32GraphicsFamily.has_value() && m_u32PresentFamily.has_value();
	}
};

struct VkSwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR m_scCapabilities = {};
	Array<VkSurfaceFormatKHR> m_vFormats;
	Array<VkPresentModeKHR> m_vPresentModes;
};

class VkUtil {
public:
	static void ValidateSupportedLayers();
	static bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice);
	static bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface);
	static VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface);
	static VkSwapChainSupportDetails QuerySwapchainSupport(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface);
	static bool GetValidationLayersEnabled();
	static Array<const char*> GetValidationLayers();
	static Array<const char*> GetInstanceExtensions();
	static Array<const char*> GetDeviceExtensions();
	static VkSurfaceFormatKHR SelectSwapSurfaceFormat(const Array<VkSurfaceFormatKHR>& _vAvailableFormats);
	static VkPresentModeKHR SelectSwapPresentMode(const Array<VkPresentModeKHR>& _vAvailablePresentModes);
	static VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities, WindowHandleGeneric _whgHandle);
	static void CreateImage(VkDevice _dDeviceHandle, VkPhysicalDevice _pdPhysicalDevice, uint32 _u32Width, uint32 _u32Height, VkFormat _fFormat, VkImageTiling _itTiling, VkImageUsageFlags _iufUsage, VkMemoryPropertyFlags _mpfProperties, VkImage& _iImage, VkDeviceMemory& _dmMem);
	static VkImageView CreateImageView(VkDevice _dDeviceHandle, VkImage _iImage, VkFormat _fFormat, VkImageAspectFlags _iafFlags);
	static void TransitionImageLayout(VkCommandBuffer _cbBuffer, VkImage _iImage, VkFormat _fFormat, VkImageLayout _ilLayoutOld, VkImageLayout _ilLayoutNew);
	static VkFormat FindDepthFormat(VkPhysicalDevice _pdPhysicalDevice);
	static VkFormat FindSupportedFormat(VkPhysicalDevice _pdPhysicalDevice, const Array<VkFormat>& _vCandidates, VkImageTiling _itTiling, VkFormatFeatureFlags _fffFeatures);
	static uint32 FindMemoryType(VkPhysicalDevice _pdPhysicalDevice, uint32 _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags);
	static bool HasStencilComponent(VkFormat _fFormat);

	/*static VkShaderModule CreateShaderModule(const Array<char>& _vCode);
	static void CopyBufferToImage(VkBuffer _bBuffer, VkImage _iImage, uint32 _u32Width, uint32 _u32Height); */
};