
#include <Platform/Vulkan/VkUtil.hpp>

#include <HellfireControl/Core/Window.hpp>

namespace LayersAndExtensions {
	std::vector<const char*> m_vValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};

#	ifndef NDEBUG
	const bool m_bEnableValidationLayers = true;
#	else
	const bool m_bEnableValidationLayers = false;
#	endif

	const std::vector<const char*> m_vInstanceExtensions = {
		VK_KHR_SURFACE_EXTENSION_NAME,
#	ifdef WIN32
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#	else

#	endif
	};

	const std::vector<const char*> m_vDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		//VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
	};
}

using namespace LayersAndExtensions;

void VkUtil::ValidateSupportedLayers() {
	uint32_t u32LayerCount = 0;
	vkEnumerateInstanceLayerProperties(&u32LayerCount, nullptr);

	std::vector<VkLayerProperties> vLayerProperties(u32LayerCount);
	vkEnumerateInstanceLayerProperties(&u32LayerCount, vLayerProperties.data());

	for (int ndx = 0; ndx < m_vValidationLayers.size(); ++ndx) {
		bool bLayerFound = false;

		for (const auto& aLayerProperties : vLayerProperties) {
			if (!strcmp(m_vValidationLayers[ndx], aLayerProperties.layerName)) {
				bLayerFound = true;
				break;
			}
		}

		if (!bLayerFound) {
			m_vValidationLayers.erase(m_vValidationLayers.begin() + ndx--); //If our layer is unsupported, remove it.
		}
	}
}

bool VkUtil::ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice) {
	uint32_t u32ExtensionCount;
	vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, nullptr);

	std::vector<VkExtensionProperties> vAvailableExtensions(u32ExtensionCount);
	vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, vAvailableExtensions.data());

	std::set<std::string> sRequiredExtensions(m_vDeviceExtensions.begin(), m_vDeviceExtensions.end());

	for (const auto& aExtension : vAvailableExtensions) {
		sRequiredExtensions.erase(aExtension.extensionName);
	}

	return sRequiredExtensions.empty();
} 

bool VkUtil::GetValidationLayersEnabled() { return m_bEnableValidationLayers; }

std::vector<const char*> VkUtil::GetValidationLayers() { return m_vValidationLayers; }

std::vector<const char*> VkUtil::GetInstanceExtensions() { return m_vInstanceExtensions; }

std::vector<const char*> VkUtil::GetDeviceExtensions() { return m_vDeviceExtensions; }

bool VkUtil::CheckDeviceSuitability(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface) {
	VkPhysicalDeviceProperties pdpProperties = {};
	vkGetPhysicalDeviceProperties(_pdDevice, &pdpProperties);

	VkPhysicalDeviceFeatures pdfFeatures = {};
	vkGetPhysicalDeviceFeatures(_pdDevice, &pdfFeatures);

	VkQueueFamilyIndices qfiIndices = GetQueueFamilies(_pdDevice, _sSurface);

	bool bExtensionsSupported = ValidateSupportedDeviceExtensions(_pdDevice);

	bool bSwapChainAdequate = false;

	if (bExtensionsSupported) {
		VkSwapChainSupportDetails scsdSupport = QuerySwapchainSupport(_pdDevice, _sSurface);
		bSwapChainAdequate = !scsdSupport.m_vFormats.empty() && !scsdSupport.m_vPresentModes.empty();
	}

	return pdpProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && qfiIndices.IsComplete()
		&& bExtensionsSupported && bSwapChainAdequate && pdfFeatures.samplerAnisotropy;
}

VkSwapChainSupportDetails VkUtil::QuerySwapchainSupport(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface) {
	VkSwapChainSupportDetails scsdDetails = {};

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_pdDevice, _sSurface, &scsdDetails.m_scCapabilities);

	uint32_t u32FormatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, _sSurface, &u32FormatCount, nullptr);

	if (u32FormatCount) {
		scsdDetails.m_vFormats.resize(u32FormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, _sSurface, &u32FormatCount, scsdDetails.m_vFormats.data());
	}

	uint32_t u32PresentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, _sSurface, &u32PresentModeCount, nullptr);

	if (u32PresentModeCount) {
		scsdDetails.m_vPresentModes.resize(u32PresentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, _sSurface, &u32PresentModeCount, scsdDetails.m_vPresentModes.data());
	}

	return scsdDetails;
}

VkQueueFamilyIndices VkUtil::GetQueueFamilies(VkPhysicalDevice _pdDevice, VkSurfaceKHR _sSurface) {
	VkQueueFamilyIndices qfiIndices = {};

	uint32_t u32FamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_pdDevice, &u32FamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> vFamilies(u32FamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_pdDevice, &u32FamilyCount, vFamilies.data());

	int iFamilyNumber = 0;
	VkBool32 bPresentSupport = false;
	for (const auto& aFamily : vFamilies) {
		if (aFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			qfiIndices.m_u32GraphicsFamily = iFamilyNumber;
		}

		vkGetPhysicalDeviceSurfaceSupportKHR(_pdDevice, iFamilyNumber, _sSurface, &bPresentSupport);
		if (bPresentSupport) {
			qfiIndices.m_u32PresentFamily = iFamilyNumber;
		}

		if (qfiIndices.IsComplete()) {
			break;
		}

		++iFamilyNumber;
	}

	return qfiIndices;
}

VkSurfaceFormatKHR VkUtil::SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats) {
	for (const auto& aAvailableFormat : _vAvailableFormats) {
		if (aAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && aAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return aAvailableFormat;
		}
	}

	return _vAvailableFormats[0];
}

VkPresentModeKHR VkUtil::SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes) {
	for (const auto& aAvailablePresentMode : _vAvailablePresentModes) {
		if (aAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return aAvailablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VkUtil::SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities, WindowHandleGeneric _whgHandle) {
	if (_scCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return _scCapabilities.currentExtent;
	}
	else {
		Vec2F v2Size = Window(_whgHandle).GetWindowSize();

		VkExtent2D eViewportSize = {
			.width = static_cast<uint32_t>(v2Size.x),
			.height = static_cast<uint32_t>(v2Size.y)
		};

		eViewportSize.width = eViewportSize.width > _scCapabilities.maxImageExtent.width ? _scCapabilities.maxImageExtent.width :
			(eViewportSize.width < _scCapabilities.minImageExtent.width ? _scCapabilities.minImageExtent.width : eViewportSize.width);
		eViewportSize.height = eViewportSize.height > _scCapabilities.maxImageExtent.height ? _scCapabilities.maxImageExtent.height :
			(eViewportSize.height < _scCapabilities.minImageExtent.height ? _scCapabilities.minImageExtent.height : eViewportSize.height);

		return eViewportSize;
	}
}

void VkUtil::CreateImage(VkDevice _dDeviceHandle, VkPhysicalDevice _pdPhysicalDevice, uint32_t _iWidth, uint32_t _iHeight, VkFormat _fFormat, VkImageTiling _itTiling, VkImageUsageFlags _iufFlags, VkMemoryPropertyFlags _mpfProperties, VkImage& _iImage, VkDeviceMemory& _dmImageMem) {
	VkImageCreateInfo iciImageInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = _fFormat,
		.extent = { static_cast<uint32_t>(_iWidth), static_cast<uint32_t>(_iHeight), 1U },
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = _itTiling,
		.usage = _iufFlags,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};

	if (vkCreateImage(_dDeviceHandle, &iciImageInfo, nullptr, &_iImage) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create image!");
	}

	VkMemoryRequirements mrRequirements;
	vkGetImageMemoryRequirements(_dDeviceHandle, _iImage, &mrRequirements);

	VkMemoryAllocateInfo maiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = FindMemoryType(_pdPhysicalDevice, mrRequirements.memoryTypeBits, _mpfProperties)
	};

	if (vkAllocateMemory(_dDeviceHandle, &maiAllocInfo, nullptr, &_dmImageMem) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate iamge memory!");
	}

	vkBindImageMemory(_dDeviceHandle, _iImage, _dmImageMem, 0);
}

VkImageView VkUtil::CreateImageView(VkDevice _dDeviceHandle, VkImage _iImage, VkFormat _fFormat, VkImageAspectFlags _iafFlags) {
	VkImageViewCreateInfo ivciViewInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = _iImage,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = _fFormat,
		.components = {
			.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.a = VK_COMPONENT_SWIZZLE_IDENTITY
		},
		.subresourceRange = {
			.aspectMask = _iafFlags,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	VkImageView ivView;

	if (vkCreateImageView(_dDeviceHandle, &ivciViewInfo, nullptr, &ivView) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create texture image view!");
	}

	return ivView;
}

void VkUtil::TransitionImageLayout(VkCommandBuffer _cbBuffer, VkImage _iImage, VkFormat _fFormat, VkImageLayout _ilLayoutOld, VkImageLayout _ilLayoutNew) {
	VkImageMemoryBarrier imbBarrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.pNext = nullptr,
		.srcAccessMask = 0,
		.dstAccessMask = 0,
		.oldLayout = _ilLayoutOld,
		.newLayout = _ilLayoutNew,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = _iImage,
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	if (_ilLayoutNew == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		imbBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (VkUtil::HasStencilComponent(_fFormat)) {
			imbBarrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}

	VkPipelineStageFlags psfSrcFlags = 0;
	VkPipelineStageFlags psfDestFlags = 0;

	if (_ilLayoutOld == VK_IMAGE_LAYOUT_UNDEFINED && _ilLayoutNew == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		imbBarrier.srcAccessMask = 0;
		imbBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		psfSrcFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		psfDestFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (_ilLayoutOld == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && _ilLayoutNew == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		imbBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		imbBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		psfSrcFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
		psfDestFlags = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else if (_ilLayoutOld == VK_IMAGE_LAYOUT_UNDEFINED && _ilLayoutNew == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		imbBarrier.srcAccessMask = 0;
		imbBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		psfSrcFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		psfDestFlags = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	}
	else {
		throw std::runtime_error("ERROR: Unsupported layout transition attempted!");
	}

	vkCmdPipelineBarrier(_cbBuffer, psfSrcFlags, psfDestFlags, 0, 0, nullptr, 0, nullptr, 1, &imbBarrier);
}

VkFormat VkUtil::FindDepthFormat(VkPhysicalDevice _pdPhysicalDevice) {
	return FindSupportedFormat(
		_pdPhysicalDevice,
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

VkFormat VkUtil::FindSupportedFormat(VkPhysicalDevice _pdPhysicalDevice, const std::vector<VkFormat>& _vCandidates, VkImageTiling _itTiling, VkFormatFeatureFlags _fffFeatures) {
	for (VkFormat fFormat : _vCandidates) {
		VkFormatProperties fpProperties;
		vkGetPhysicalDeviceFormatProperties(_pdPhysicalDevice, fFormat, &fpProperties);

		if ((_itTiling == VK_IMAGE_TILING_LINEAR && (fpProperties.linearTilingFeatures & _fffFeatures) == _fffFeatures) ||
			(_itTiling == VK_IMAGE_TILING_OPTIMAL && (fpProperties.optimalTilingFeatures & _fffFeatures) == _fffFeatures)) {
			return fFormat;
		}
	}

	throw std::runtime_error("ERROR: Failed to find a supported format!");
}

uint32_t VkUtil::FindMemoryType(VkPhysicalDevice _pdPhysicalDevice, uint32_t _u32TypeFilter, VkMemoryPropertyFlags _mpfFlags) {
	VkPhysicalDeviceMemoryProperties pdmpMemProperties;
	vkGetPhysicalDeviceMemoryProperties(_pdPhysicalDevice, &pdmpMemProperties);

	for (uint32_t ndx = 0; ndx < pdmpMemProperties.memoryTypeCount; ++ndx) {
		if (_u32TypeFilter & (1 << ndx) && (pdmpMemProperties.memoryTypes[ndx].propertyFlags & _mpfFlags) == _mpfFlags) {
			return ndx;
		}
	}

	throw std::runtime_error("ERROR: Failed to find suitable memory type!");
}

bool VkUtil::HasStencilComponent(VkFormat _fFormat) {
	return _fFormat == VK_FORMAT_D32_SFLOAT_S8_UINT || _fFormat == VK_FORMAT_D24_UNORM_S8_UINT;
}

//void VkUtil::CopyBufferToImage(VkBuffer _bBuffer, VkImage _iImage, uint32_t _u32Width, uint32_t _u32Height) {
//	VkCommandBuffer cbBuffer = BeginSingleTimeCommands();
//
//	VkBufferImageCopy bicImageCopy = {
//		.bufferOffset = 0,
//		.bufferRowLength = 0,
//		.bufferImageHeight = 0,
//		.imageSubresource = {
//			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
//			.mipLevel = 0,
//			.baseArrayLayer = 0,
//			.layerCount = 1
//		},
//		.imageOffset = {
//			.x = 0,
//			.y = 0,
//			.z = 0
//		},
//		.imageExtent = {
//			.width = _u32Width,
//			.height = _u32Height,
//			.depth = 1
//		}
//	};
//
//	vkCmdCopyBufferToImage(cbBuffer, _bBuffer, _iImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &bicImageCopy);
//
//	EndSingleTimeCommands(cbBuffer);
//}
//
//VkShaderModule VkUtil::CreateShaderModule(const std::vector<char>& _vCode) {
//	VkShaderModule smShader = VK_NULL_HANDLE;
//
//	VkShaderModuleCreateInfo smciShaderInfo = {
//		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
//		.pNext = nullptr,
//		.flags = 0,
//		.codeSize = _vCode.size(),
//		.pCode = reinterpret_cast<const uint32_t*>(_vCode.data())
//	};
//
//	if (vkCreateShaderModule(PlatformRenderManager::m_dDeviceHandle, &smciShaderInfo, nullptr, &smShader)) {
//		throw std::runtime_error("ERROR: Could not create shader module!");
//	}
//
//	return smShader;
//}
