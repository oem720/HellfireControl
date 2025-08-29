
#include <HellfireControl/Render/RenderManager.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkUtil.hpp>

#include <Platform/OSInclude.hpp>

#include <HellfireControl/Core/Window.hpp>

#pragma region Static Members
RenderManager* RenderManager::m_prsInstancePtr = nullptr;
bool RenderManager::m_bFramebufferInvalid = false;

uint32_t VkRenderManager::m_u32CurrentFrame = 0;
std::array<VkClearValue, 2> VkRenderManager::m_arrClearValues = {};

VkInstance VkRenderManager::m_iInstance = VK_NULL_HANDLE;
VkPhysicalDevice VkRenderManager::m_pdPhysicalDevice = VK_NULL_HANDLE;
VkSurfaceKHR VkRenderManager::m_sSurface = VK_NULL_HANDLE;
VkDevice VkRenderManager::m_dDeviceHandle = VK_NULL_HANDLE;
VkQueue VkRenderManager::m_qGraphicsQueue = VK_NULL_HANDLE;
VkQueue VkRenderManager::m_qPresentQueue = VK_NULL_HANDLE;
VkSwapchainKHR VkRenderManager::m_scSwapchain = VK_NULL_HANDLE;
VkCommandPool VkRenderManager::m_cpCommandPool = VK_NULL_HANDLE;
VkImage VkRenderManager::m_iDepth = VK_NULL_HANDLE;
VkImageView VkRenderManager::m_ivDepthView = VK_NULL_HANDLE;
VkDeviceMemory VkRenderManager::m_dmDepthMem = VK_NULL_HANDLE;
VkRenderPass VkRenderManager::m_rpRenderPass = VK_NULL_HANDLE;

VkFormat VkRenderManager::m_fFormat = {};
VkExtent2D VkRenderManager::m_eExtent = {};

std::vector<VkImage> VkRenderManager::m_vSwapchainImages = {};
std::vector<VkImageView> VkRenderManager::m_vSwapchainImageViews = {};
std::vector<VkFramebuffer> VkRenderManager::m_vSwapchainFramebuffers = {};
std::vector<VkSemaphore> VkRenderManager::m_vImageAvailableSemaphores = {};
std::vector<VkSemaphore> VkRenderManager::m_vRenderFinishedSemaphores = {};
std::vector<VkFence> VkRenderManager::m_vInFlightFences = {};
#pragma endregion

#pragma region Engine Interface
void RenderManager::InitPlatformObjects(const std::string& _strAppName, uint32_t _u32AppVersion, const Vec4F& _v4ClearColor) {
	VkRenderManager::m_arrClearValues = { 
		VkClearValue{
			.color = { _v4ClearColor.x, _v4ClearColor.y, _v4ClearColor.z, _v4ClearColor.w }
		},
		VkClearValue{
			.depthStencil = { 1.0f, 0 }
		}
	};

	VkRenderManager::CreateInstance(_strAppName, _u32AppVersion);

	PlatformSurface::CreatePlatformSurface(m_whgWindowHandle, VkRenderManager::m_iInstance, VkRenderManager::m_sSurface);

	VkRenderManager::SelectPhysicalDevice();

	VkRenderManager::CreateLogicalDevice();

	VkRenderManager::CreateSwapchain(m_whgWindowHandle);

	VkRenderManager::CreateSwapchainImageViews();

	VkRenderManager::CreateCommandPool();

	VkRenderManager::CreateDepthResources();

	VkRenderManager::CreateFinalRenderPass();

	VkRenderManager::CreateSwapchainFramebuffers();

	VkRenderManager::CreateSyncObjects();
}

void RenderFrame() {

}

void RenderManager::CleanupPlatformObjects() {
	vkDeviceWaitIdle(VkRenderManager::m_dDeviceHandle);

	VkRenderManager::CleanupSwapchain();

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		vkDestroySemaphore(VkRenderManager::m_dDeviceHandle, VkRenderManager::m_vImageAvailableSemaphores[ndx], nullptr);
		vkDestroySemaphore(VkRenderManager::m_dDeviceHandle, VkRenderManager::m_vRenderFinishedSemaphores[ndx], nullptr);
		vkDestroyFence(VkRenderManager::m_dDeviceHandle, VkRenderManager::m_vInFlightFences[ndx], nullptr);
	}

	vkDestroyCommandPool(VkRenderManager::m_dDeviceHandle, VkRenderManager::m_cpCommandPool, nullptr);

	vkDestroyRenderPass(VkRenderManager::m_dDeviceHandle, VkRenderManager::m_rpRenderPass, nullptr);

	vkDestroyDevice(VkRenderManager::m_dDeviceHandle, nullptr);

	vkDestroySurfaceKHR(VkRenderManager::m_iInstance, VkRenderManager::m_sSurface, nullptr);

	vkDestroyInstance(VkRenderManager::m_iInstance, nullptr);
}
#pragma endregion

#pragma region Platform Functionality
void VkRenderManager::CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion) {
	std::vector<const char*> vInstanceExtensions = VkUtil::GetInstanceExtensions();
	std::vector<const char*> vValidationLayers = VkUtil::GetValidationLayers();

	VkApplicationInfo aiAppInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = _strAppName.c_str(),
		.applicationVersion = HC_ENGINE_VERSION,
		.pEngineName = "Hellfire Control Engine",
		.engineVersion = _u32AppVersion,
		.apiVersion = VK_API_VERSION_1_3
	};

	VkInstanceCreateInfo icInstanceInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pApplicationInfo = &aiAppInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = static_cast<uint32_t>(vInstanceExtensions.size()),
		.ppEnabledExtensionNames = vInstanceExtensions.data()
	};

	if (VkUtil::GetValidationLayersEnabled()) {
		VkUtil::ValidateSupportedLayers();
	
		icInstanceInfo.enabledLayerCount = static_cast<uint32_t>(vValidationLayers.size());
		icInstanceInfo.ppEnabledLayerNames = vValidationLayers.data();
	}

	if (vkCreateInstance(&icInstanceInfo, nullptr, &m_iInstance) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create Vulkan Instance!");
	}
}

void VkRenderManager::SelectPhysicalDevice() {
	uint32_t u32DeviceCount = 0;
	vkEnumeratePhysicalDevices(m_iInstance, &u32DeviceCount, nullptr);

	if (!u32DeviceCount) {
		throw std::runtime_error("ERROR: Failed to find compatible GPUs!");
	}

	std::vector<VkPhysicalDevice> vDevices(u32DeviceCount);
	vkEnumeratePhysicalDevices(m_iInstance, &u32DeviceCount, vDevices.data());

	for (const auto& aDevice : vDevices) {
		if (VkUtil::CheckDeviceSuitability(aDevice, m_sSurface)) {
			m_pdPhysicalDevice = aDevice;
			break;
		}
	}

	if (m_pdPhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("ERROR: Failed to find a suitable GPU!");
	}
}

void VkRenderManager::CreateLogicalDevice() {
	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice, m_sSurface);

	std::vector<VkDeviceQueueCreateInfo> vQueueCreateInfos;
	std::set<uint32_t> sUniqueQueueFamilies = {
		qfiIndices.m_u32GraphicsFamily.value(),
		qfiIndices.m_u32PresentFamily.value()
	};

	float fQueuePriority = 1.0f;

	for (uint32_t u32QueueFamily : sUniqueQueueFamilies) {
		VkDeviceQueueCreateInfo dqciQueueInfo = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.queueFamilyIndex = qfiIndices.m_u32GraphicsFamily.value(),
			.queueCount = 1,
			.pQueuePriorities = &fQueuePriority
		};

		vQueueCreateInfos.push_back(dqciQueueInfo);
	}

	VkPhysicalDeviceFeatures pdfFeatures = {};
	pdfFeatures.samplerAnisotropy = VK_TRUE;

	std::vector<const char*> vDeviceExtensions = VkUtil::GetDeviceExtensions();
	std::vector<const char*> vValidationLayers = VkUtil::GetValidationLayers();

	VkDeviceCreateInfo dciDeviceInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueCreateInfoCount = static_cast<uint32_t>(vQueueCreateInfos.size()),
		.pQueueCreateInfos = vQueueCreateInfos.data(),
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = static_cast<uint32_t>(vDeviceExtensions.size()),
		.ppEnabledExtensionNames = vDeviceExtensions.data(),
		.pEnabledFeatures = &pdfFeatures,
	};

	if (VkUtil::GetValidationLayersEnabled()) {
		dciDeviceInfo.enabledLayerCount = static_cast<uint64_t>(vValidationLayers.size());
		dciDeviceInfo.ppEnabledLayerNames = vValidationLayers.data();
	}

	if (vkCreateDevice(m_pdPhysicalDevice, &dciDeviceInfo, nullptr, &m_dDeviceHandle) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create logical device!");
	}

	vkGetDeviceQueue(m_dDeviceHandle, qfiIndices.m_u32GraphicsFamily.value(), 0, &m_qGraphicsQueue);
	vkGetDeviceQueue(m_dDeviceHandle, qfiIndices.m_u32PresentFamily.value(), 0, &m_qPresentQueue);
}

void VkRenderManager::CreateSwapchain(WindowHandleGeneric _whgHandle) {
	VkSwapChainSupportDetails scsdSupport = VkUtil::QuerySwapchainSupport(m_pdPhysicalDevice, m_sSurface);

	VkSurfaceFormatKHR sfFormat = VkUtil::SelectSwapSurfaceFormat(scsdSupport.m_vFormats);
	VkPresentModeKHR pmMode = VkUtil::SelectSwapPresentMode(scsdSupport.m_vPresentModes);
	VkExtent2D eExtent = VkUtil::SelectSwapExtent(scsdSupport.m_scCapabilities, _whgHandle);

	uint32_t u32ImageCount = scsdSupport.m_scCapabilities.minImageCount + 1;

	if (scsdSupport.m_scCapabilities.maxImageCount > 0 && u32ImageCount > scsdSupport.m_scCapabilities.maxImageCount) {
		u32ImageCount = scsdSupport.m_scCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR scciSwapChainInfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.surface = m_sSurface,
		.minImageCount = u32ImageCount,
		.imageFormat = sfFormat.format,
		.imageColorSpace = sfFormat.colorSpace,
		.imageExtent = eExtent,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = scsdSupport.m_scCapabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = pmMode,
		.clipped = VK_TRUE,
		.oldSwapchain = VK_NULL_HANDLE,
	};

	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice, m_sSurface);
	uint32_t u32QueueFamilyIndices[] = { 
		qfiIndices.m_u32GraphicsFamily.value(),
		qfiIndices.m_u32PresentFamily.value()
	};

	if (qfiIndices.m_u32GraphicsFamily != qfiIndices.m_u32PresentFamily) {
		scciSwapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		scciSwapChainInfo.queueFamilyIndexCount = 2;
		scciSwapChainInfo.pQueueFamilyIndices = u32QueueFamilyIndices;
	}
	else {
		scciSwapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		scciSwapChainInfo.queueFamilyIndexCount = 0;
		scciSwapChainInfo.pQueueFamilyIndices = nullptr;
	}

	if (vkCreateSwapchainKHR(m_dDeviceHandle, &scciSwapChainInfo, nullptr, &m_scSwapchain) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create swapchain!");
	}

	vkGetSwapchainImagesKHR(m_dDeviceHandle, m_scSwapchain, &u32ImageCount, nullptr);
	m_vSwapchainImages.resize(u32ImageCount);
	vkGetSwapchainImagesKHR(m_dDeviceHandle, m_scSwapchain, &u32ImageCount, m_vSwapchainImages.data());

	m_fFormat = sfFormat.format;
	m_eExtent = eExtent;
}

void VkRenderManager::CreateSwapchainImageViews() {
	m_vSwapchainImageViews.resize(m_vSwapchainImages.size());

	for (int ndx = 0; ndx < m_vSwapchainImages.size(); ++ndx) {
		m_vSwapchainImageViews[ndx] = VkUtil::CreateImageView(m_dDeviceHandle, m_vSwapchainImages[ndx], m_fFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void VkRenderManager::CreateCommandPool() {
	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice, m_sSurface);

	VkCommandPoolCreateInfo cpciPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = qfiIndices.m_u32GraphicsFamily.value()
	};

	if (vkCreateCommandPool(m_dDeviceHandle, &cpciPoolCreateInfo, nullptr, &m_cpCommandPool) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create command pool!");
	}
}

void VkRenderManager::CreateDepthResources() {
	VkFormat fDepthFormat = VkUtil::FindDepthFormat(m_pdPhysicalDevice);

	VkUtil::CreateImage(m_dDeviceHandle, m_pdPhysicalDevice, m_eExtent.width, m_eExtent.height, fDepthFormat, VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_iDepth, m_dmDepthMem);

	m_ivDepthView = VkUtil::CreateImageView(m_dDeviceHandle, m_iDepth, fDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	VkCommandBuffer cbTemp = CreateSingleUseCommandBuffer();

	VkUtil::TransitionImageLayout(cbTemp, m_iDepth, fDepthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

	SubmitSingleUseCommandBuffer(cbTemp);
}

void VkRenderManager::CreateFinalRenderPass() {
	std::array<VkAttachmentDescription, 2> arrAttachments = {
		VkAttachmentDescription {
			.flags = 0,
			.format = m_fFormat,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		},
		VkAttachmentDescription {
			.flags = 0,
			.format = VkUtil::FindDepthFormat(m_pdPhysicalDevice),
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		}
	};

	VkAttachmentReference arColorRef = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	};

	VkAttachmentReference arDepthRef = {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
	};

	VkSubpassDescription sdSubpassDesc = {
		.flags = 0,
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.inputAttachmentCount = 0,
		.pInputAttachments = nullptr,
		.colorAttachmentCount = 1,
		.pColorAttachments = &arColorRef,
		.pResolveAttachments = 0,
		.pDepthStencilAttachment = &arDepthRef,
		.preserveAttachmentCount = 0,
		.pPreserveAttachments = nullptr
	};

	VkSubpassDependency sdSubpassDependency = {
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
		.srcAccessMask = 0,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
		.dependencyFlags = 0
	};

	VkRenderPassCreateInfo rpciRenderPassInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.attachmentCount = static_cast<uint32_t>(arrAttachments.size()),
		.pAttachments = arrAttachments.data(),
		.subpassCount = 1,
		.pSubpasses = &sdSubpassDesc,
		.dependencyCount = 1,
		.pDependencies = &sdSubpassDependency
	};

	if (vkCreateRenderPass(m_dDeviceHandle, &rpciRenderPassInfo, nullptr, &m_rpRenderPass) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create render pass!");
	}
}

void VkRenderManager::CreateSwapchainFramebuffers() {
	m_vSwapchainFramebuffers.resize(m_vSwapchainImageViews.size());

	for (int ndx = 0; ndx < m_vSwapchainImageViews.size(); ++ndx) {
		std::array<VkImageView, 2> arrAttachments = {
			m_vSwapchainImageViews[ndx],
			m_ivDepthView
		};

		VkFramebufferCreateInfo fciFramebufferInfo = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.renderPass = m_rpRenderPass,
			.attachmentCount = static_cast<uint32_t>(arrAttachments.size()),
			.pAttachments = arrAttachments.data(),
			.width = m_eExtent.width,
			.height = m_eExtent.height,
			.layers = 1
		};

		if (vkCreateFramebuffer(m_dDeviceHandle, &fciFramebufferInfo, nullptr, &m_vSwapchainFramebuffers[ndx]) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create framebuffers!");
		}
	}
}

void VkRenderManager::CreateSyncObjects() {
	m_vImageAvailableSemaphores.resize(HC_MAX_FRAMES_IN_FLIGHT);
	m_vRenderFinishedSemaphores.resize(HC_MAX_FRAMES_IN_FLIGHT);
	m_vInFlightFences.resize(HC_MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo sciSemaphoreInfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0
	};

	VkFenceCreateInfo fciFenceInfo = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT
	};

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		if (vkCreateSemaphore(m_dDeviceHandle, &sciSemaphoreInfo, nullptr, &m_vImageAvailableSemaphores[ndx]) != VK_SUCCESS ||
			vkCreateSemaphore(m_dDeviceHandle, &sciSemaphoreInfo, nullptr, &m_vRenderFinishedSemaphores[ndx]) != VK_SUCCESS ||
			vkCreateFence(m_dDeviceHandle, &fciFenceInfo, nullptr, &m_vInFlightFences[ndx]) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create sync objects!");
		}
	}
}

VkCommandBuffer VkRenderManager::CreateSingleUseCommandBuffer() {
	VkCommandBufferAllocateInfo cbaiBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = m_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1
	};

	VkCommandBuffer cbBuffer;

	vkAllocateCommandBuffers(m_dDeviceHandle, &cbaiBufferInfo, &cbBuffer);

	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = nullptr
	};

	vkBeginCommandBuffer(cbBuffer, &cbbiBeginInfo);

	return cbBuffer;
}

void VkRenderManager::SubmitSingleUseCommandBuffer(VkCommandBuffer _cbBuffer) {
	vkEndCommandBuffer(_cbBuffer);

	VkSubmitInfo siSubmitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 0,
		.pWaitSemaphores = nullptr,
		.pWaitDstStageMask = nullptr,
		.commandBufferCount = 1,
		.pCommandBuffers = &_cbBuffer,
		.signalSemaphoreCount = 0,
		.pSignalSemaphores = nullptr
	};

	vkQueueSubmit(m_qGraphicsQueue, 1, &siSubmitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(m_qGraphicsQueue);

	vkFreeCommandBuffers(m_dDeviceHandle, m_cpCommandPool, 1, &_cbBuffer);
}

void VkRenderManager::CleanupSwapchain() {
	vkDestroyImageView(m_dDeviceHandle, m_ivDepthView, nullptr);

	vkDestroyImage(m_dDeviceHandle, m_iDepth, nullptr);

	vkFreeMemory(m_dDeviceHandle, m_dmDepthMem, nullptr);

	for (auto aFramebuffer : m_vSwapchainFramebuffers) {
		vkDestroyFramebuffer(m_dDeviceHandle, aFramebuffer, nullptr);
	}

	for (auto aView : m_vSwapchainImageViews) {
		vkDestroyImageView(m_dDeviceHandle, aView, nullptr);
	}

	vkDestroySwapchainKHR(m_dDeviceHandle, m_scSwapchain, nullptr);
}

void VkRenderManager::RecreateSwapchain(WindowHandleGeneric _whgHandle) {
	Window wWindow(_whgHandle);

	Vec2F v2WindowSize = wWindow.GetWindowSize();

	//Wait here to until the window is no longer 0,0 size.
	//This is terrible right now, as this is not on a separate thread. In the future,
	//this should pause rendering and return when the window reports it is no longer minimized
	while (v2WindowSize == Vec2F(0, 0)) {
		v2WindowSize = wWindow.GetWindowSize();
		wWindow.WaitEvents();
	}

	vkDeviceWaitIdle(m_dDeviceHandle);

	CleanupSwapchain();

	CreateSwapchain(_whgHandle);

	CreateSwapchainImageViews();

	CreateDepthResources();

	CreateSwapchainFramebuffers();

	m_u32CurrentFrame = 0;
}
#pragma endregion
#endif