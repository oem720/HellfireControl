
#include <HellfireControl/Render/RenderManager.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkUtil.hpp>
#include <Platform/Vulkan/VkRenderer.hpp>

#include <Platform/OSInclude.hpp>

#include <HellfireControl/Core/Window.hpp>
#include <HellfireControl/Render/RenderMemory.hpp>

#pragma region Static Members
uint32 VkRenderManager::m_u32CurrentFrame = 0;

VkInstance VkRenderManager::m_iInstance = VK_NULL_HANDLE;
VkPhysicalDevice VkRenderManager::m_pdPhysicalDevice = VK_NULL_HANDLE;
VkSurfaceKHR VkRenderManager::m_sSurface = VK_NULL_HANDLE;
VkDevice VkRenderManager::m_dDeviceHandle = VK_NULL_HANDLE;
VkQueue VkRenderManager::m_qGraphicsQueue = VK_NULL_HANDLE;
VkQueue VkRenderManager::m_qPresentQueue = VK_NULL_HANDLE;
VkSwapchainKHR VkRenderManager::m_scSwapchain = VK_NULL_HANDLE;

VkFormat VkRenderManager::m_fFormat = {};
VkExtent2D VkRenderManager::m_eExtent = {};

Array<VkImage> VkRenderManager::m_vSwapchainImages = {};
FixedArray<VkFrameData, HC_MAX_FRAMES_IN_FLIGHT> VkRenderManager::m_arrFrames = {};

Map<VkDescriptorType, uint32> VkRenderManager::m_mDescriptorTypeCounts = {};
#pragma endregion

#pragma region Engine Interface
void RenderManager::InitPlatformObjects(const String& _strAppName, uint32 _u32AppVersion) {
	VkRenderManager::CreateInstance(_strAppName, _u32AppVersion);

	PlatformSurface::CreatePlatformSurface(m_whgWindowHandle, VkRenderManager::m_iInstance, VkRenderManager::m_sSurface);

	VkRenderManager::SelectPhysicalDevice();

	VkRenderManager::CreateLogicalDevice();

	VkRenderManager::CreateSwapchain(m_whgWindowHandle);

	VkRenderManager::CreateFrameData();

	VkPhysicalDeviceProperties pdpProperties = {};
	vkGetPhysicalDeviceProperties(VkRenderManager::m_pdPhysicalDevice, &pdpProperties);

	RenderMemoryAllocator::GetInstance()
		->SetAllocationLimitAndGranularity(
			pdpProperties.limits.maxMemoryAllocationCount,
			pdpProperties.limits.bufferImageGranularity
		);
}

void RenderManager::RegisterPlatformRenderer(const Shared<Renderer>& _pRenderer) {
	Shared<VkRenderer> pPlatformRenderer = std::dynamic_pointer_cast<VkRenderer>(_pRenderer->GetPlatformRenderer());

	if (pPlatformRenderer == nullptr) {
		throw std::runtime_error("Failed to cast to platform renderer. Improperly specified renderer?");
	}

	Array<VkDescriptorType> vDescriptors = pPlatformRenderer->GetDescriptorCounts();

	for (const auto& aDescriptor : vDescriptors) {
		VkRenderManager::m_mDescriptorTypeCounts[aDescriptor]++;
	}
}

void RenderManager::PresentFrame() {
	
}

void RenderManager::CleanupPlatformObjects() {
	vkDeviceWaitIdle(VkRenderManager::m_dDeviceHandle);

	for(auto& aFrame : VkRenderManager::m_arrFrames) {
		aFrame.Cleanup(VkRenderManager::m_dDeviceHandle);
	}

	VkRenderManager::CleanupSwapchain();

	vkDestroyDevice(VkRenderManager::m_dDeviceHandle, nullptr);

	vkDestroySurfaceKHR(VkRenderManager::m_iInstance, VkRenderManager::m_sSurface, nullptr);

	vkDestroyInstance(VkRenderManager::m_iInstance, nullptr);
}
#pragma endregion

#pragma region Platform Functionality
void VkRenderManager::CreateInstance(const String& _strAppName, uint32 _u32AppVersion) {
	Array<const char*> vInstanceExtensions = VkUtil::GetInstanceExtensions();
	Array<const char*> vValidationLayers = VkUtil::GetValidationLayers();

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
		.ppEnabledLayerNames = VK_NULL_HANDLE,
		.enabledExtensionCount = static_cast<uint32>(vInstanceExtensions.size()),
		.ppEnabledExtensionNames = vInstanceExtensions.data()
	};

	if (VkUtil::GetValidationLayersEnabled()) {
		VkUtil::ValidateSupportedLayers();
	
		icInstanceInfo.enabledLayerCount = static_cast<uint32>(vValidationLayers.size());
		icInstanceInfo.ppEnabledLayerNames = vValidationLayers.data();
	}

	if (vkCreateInstance(&icInstanceInfo, nullptr, &m_iInstance) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create Vulkan Instance!");
	}
}

void VkRenderManager::SelectPhysicalDevice() {
	uint32 u32DeviceCount = 0;
	vkEnumeratePhysicalDevices(m_iInstance, &u32DeviceCount, nullptr);

	if (!u32DeviceCount) {
		throw std::runtime_error("ERROR: Failed to find compatible GPUs!");
	}

	Array<VkPhysicalDevice> vDevices(u32DeviceCount);
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

	Array<VkDeviceQueueCreateInfo> vQueueCreateInfos;
	Set<uint32> sUniqueQueueFamilies = {
		qfiIndices.m_u32GraphicsFamily.value(),
		qfiIndices.m_u32PresentFamily.value()
	};

	float fQueuePriority = 1.0f;

	for (uint32 u32QueueFamily : sUniqueQueueFamilies) {
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

	Array<const char*> vDeviceExtensions = VkUtil::GetDeviceExtensions();
	Array<const char*> vValidationLayers = VkUtil::GetValidationLayers();

	VkDeviceCreateInfo dciDeviceInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueCreateInfoCount = static_cast<uint32>(vQueueCreateInfos.size()),
		.pQueueCreateInfos = vQueueCreateInfos.data(),
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = VK_NULL_HANDLE,
		.enabledExtensionCount = static_cast<uint32>(vDeviceExtensions.size()),
		.ppEnabledExtensionNames = vDeviceExtensions.data(),
		.pEnabledFeatures = &pdfFeatures,
	};

	if (VkUtil::GetValidationLayersEnabled()) {
		dciDeviceInfo.enabledLayerCount = static_cast<uint64>(vValidationLayers.size());
		dciDeviceInfo.ppEnabledLayerNames = vValidationLayers.data();
	}

	if (vkCreateDevice(m_pdPhysicalDevice, &dciDeviceInfo, VK_NULL_HANDLE, &m_dDeviceHandle) != VK_SUCCESS) {
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

	uint32 u32ImageCount = scsdSupport.m_scCapabilities.minImageCount + 1;

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
	uint32 u32QueueFamilyIndices[] = { 
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
		scciSwapChainInfo.pQueueFamilyIndices = VK_NULL_HANDLE;
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

void VkRenderManager::CreateFrameData() {
	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice, m_sSurface);

	VkCommandPoolCreateInfo cpciPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = VK_NULL_HANDLE,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = qfiIndices.m_u32GraphicsFamily.value()
	};

	VkSemaphoreCreateInfo sciSemaphoreInfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = VK_NULL_HANDLE,
		.flags = 0
	};

	VkFenceCreateInfo fciFenceInfo = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.pNext = VK_NULL_HANDLE,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT
	};

	Array<VkDescriptorPoolManager::PoolSizeRatio> vDescriptorPoolSizes;

	for (const auto& aDescriptorCount : m_mDescriptorTypeCounts) {
		vDescriptorPoolSizes.push_back(VkDescriptorPoolManager::PoolSizeRatio{
			.m_dtType = aDescriptorCount.first,
			.m_fRatio = static_cast<float>(aDescriptorCount.second)
		});
	}

	for (int ndx = 0; ndx < m_arrFrames.size(); ++ndx) {
		m_arrFrames[ndx].m_ivSwapchainImageView = VkUtil::CreateImageView(m_dDeviceHandle, m_vSwapchainImages[ndx], m_fFormat, VK_IMAGE_ASPECT_COLOR_BIT);

		if (vkCreateCommandPool(m_dDeviceHandle, &cpciPoolCreateInfo, nullptr, &m_arrFrames[ndx].m_cpCommandPool) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create command pool!");
		}

		if (vkCreateSemaphore(m_dDeviceHandle, &sciSemaphoreInfo, nullptr, &m_arrFrames[ndx].m_sImageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_dDeviceHandle, &sciSemaphoreInfo, nullptr, &m_arrFrames[ndx].m_sRenderFinishedSemaphore) != VK_SUCCESS ||
			vkCreateFence(m_dDeviceHandle, &fciFenceInfo, nullptr, &m_arrFrames[ndx].m_fInFlightFence) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create sync objects!");
		}

		m_arrFrames[ndx].m_dpmDescriptorPool.Init(m_dDeviceHandle, HC_VULKAN_DESCRIPTOR_POOL_INITIAL_SIZE, vDescriptorPoolSizes);
	}
}

VkCommandBuffer VkRenderManager::CreateSingleUseCommandBuffer() {
	VkCommandBufferAllocateInfo cbaiBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = m_arrFrames[m_u32CurrentFrame].m_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1
	};

	VkCommandBuffer cbBuffer;

	vkAllocateCommandBuffers(m_dDeviceHandle, &cbaiBufferInfo, &cbBuffer);

	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = VK_NULL_HANDLE
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
		.pWaitSemaphores = VK_NULL_HANDLE,
		.pWaitDstStageMask = VK_NULL_HANDLE,
		.commandBufferCount = 1,
		.pCommandBuffers = &_cbBuffer,
		.signalSemaphoreCount = 0,
		.pSignalSemaphores = VK_NULL_HANDLE
	};

	vkQueueSubmit(m_qGraphicsQueue, 1, &siSubmitInfo, nullptr);
	vkQueueWaitIdle(m_qGraphicsQueue);

	//TODO: This is currently a bug -- This command m_bBuffer is freed from the current frame's pool,
	//as we assume that the single use command m_bBuffer is created and submitted within the same frame.
	//If this is incorrect, it will cause a validation error and possible crash. May need documentation
	//for future public use, or a better system to track command m_bBuffer ownership.
	vkFreeCommandBuffers(m_dDeviceHandle, m_arrFrames[m_u32CurrentFrame].m_cpCommandPool, 1, &_cbBuffer);
}

void VkRenderManager::CleanupSwapchain() {
	for(auto& aFrame : m_arrFrames) {
		vkDestroyImageView(m_dDeviceHandle, aFrame.m_ivSwapchainImageView, nullptr);
	}

	vkDestroySwapchainKHR(m_dDeviceHandle, m_scSwapchain, nullptr);
}

void VkRenderManager::RecreateSwapchain(WindowHandleGeneric _whgHandle) {
	Window wWindow(_whgHandle);

	Vec2F v2WindowSize = wWindow.GetWindowSize();

	//Wait here to until the window is no longer 0,0 m_dsSize.
	//This is terrible right now, as this is not on a separate thread. In the future,
	//this should pause rendering and return when the window reports it is no longer minimized
	while (v2WindowSize == Vec2F(0, 0)) {
		v2WindowSize = wWindow.GetWindowSize();
		wWindow.WaitEvents();
	}

	vkDeviceWaitIdle(m_dDeviceHandle);

	CleanupSwapchain();

	CreateSwapchain(_whgHandle);

	for (int ndx = 0; ndx < m_arrFrames.size(); ++ndx) {
		m_arrFrames[ndx].m_ivSwapchainImageView = VkUtil::CreateImageView(m_dDeviceHandle, m_vSwapchainImages[ndx], m_fFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}

	m_u32CurrentFrame = 0;
}
#pragma endregion
#endif