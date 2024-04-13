
#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>
#include <Platform/Vulkan/VkRenderContext.hpp>
#include <Platform/Vulkan/VkUtil.hpp>

#define HC_INCLUDE_SURFACE_VK
#include <Platform/OSInclude.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <External/stb/stb_image.h>

#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Core/Window.hpp>
#include <HellfireControl/Math/Matrix.hpp>

#pragma region Static Member Declarations

uint64_t PlatformRenderer::m_u64WindowHandle = 0;
uint32_t PlatformRenderer::m_u32CurrentFrame = 0;
bool PlatformRenderer::m_bFramebufferResized = false;

VkInstance PlatformRenderer::m_iInstance = VK_NULL_HANDLE;
VkPhysicalDevice PlatformRenderer::m_pdPhysicalDevice = VK_NULL_HANDLE;
VkDevice PlatformRenderer::m_dDeviceHandle = VK_NULL_HANDLE;
VkQueue PlatformRenderer::m_qGraphicsQueue = VK_NULL_HANDLE;
VkQueue PlatformRenderer::m_qPresentQueue = VK_NULL_HANDLE;
VkSurfaceKHR PlatformRenderer::m_sSurface = VK_NULL_HANDLE;
VkSwapchainKHR PlatformRenderer::m_scSwapChain = VK_NULL_HANDLE;
VkRenderPass PlatformRenderer::m_rpRenderPass = VK_NULL_HANDLE;
VkDescriptorSetLayout PlatformRenderer::m_dslDescriptorSetLayout = VK_NULL_HANDLE;
VkCommandPool PlatformRenderer::m_cpCommandPool = VK_NULL_HANDLE;
VkDescriptorPool PlatformRenderer::m_dpDescriptorPool = VK_NULL_HANDLE;
VkSampler PlatformRenderer::m_sSampler = VK_NULL_HANDLE;

VkImage PlatformRenderer::m_iDepth = VK_NULL_HANDLE;
VkDeviceMemory PlatformRenderer::m_dmDepthMem = VK_NULL_HANDLE;
VkImageView PlatformRenderer::m_ivDepthView = VK_NULL_HANDLE;

VkFormat PlatformRenderer::m_fFormat = {};
VkExtent2D PlatformRenderer::m_eExtent = {};

std::array<VkClearValue, 2> PlatformRenderer::m_arrClearValues = {};
std::vector<VkCommandBuffer> PlatformRenderer::m_vCommandBuffers = {};
std::vector<VkDescriptorSet> PlatformRenderer::m_vDescriptorSets = {};
std::vector<VkSemaphore> PlatformRenderer::m_vImageAvailableSemaphores = {};
std::vector<VkSemaphore> PlatformRenderer::m_vRenderFinishedSemaphores = {};
std::vector<VkFence> PlatformRenderer::m_vInFlightFences = {};
std::vector<VkImage> PlatformRenderer::m_vSwapchainImages = {};
std::vector<VkImageView> PlatformRenderer::m_vSwapchainImageViews = {};
std::vector<VkFramebuffer> PlatformRenderer::m_vFramebuffers = {};

VkImage PlatformRenderer::imgTexture = VK_NULL_HANDLE; //SUPER TEMPORARY ! ! !
VkDeviceMemory PlatformRenderer::dmTextureMemory = VK_NULL_HANDLE;
VkImageView PlatformRenderer::ivTextureView = VK_NULL_HANDLE;
#pragma endregion

void PlatformRenderer::InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor) {
	m_u64WindowHandle = _u64WindowHandle;

	m_arrClearValues = {
		VkClearValue {
			.color = { _v4ClearColor.x, _v4ClearColor.y, _v4ClearColor.z, _v4ClearColor.w }
		},
		VkClearValue {
			.depthStencil = { 1.0f, 0 }
		}
	};

	CreateInstance(_strAppName, _u32AppVersion);

	PlatformSurface::CreatePlatformSurface(_u64WindowHandle, m_iInstance, m_sSurface);

	SelectPhysicalDevice();

	CreateLogicalDevice();

	CreateSwapChain();

	CreateSwapchainImageViews();

	CreateRenderPass();

	CreateCommandPool();

	CreateDepthResources();

	CreateFramebuffers();

	CreateTextureImage();
	CreateTextureImageView();

	CreateTextureSampler();

	CreateCommandBuffer();

	CreateSyncObjects();
}

void PlatformRenderer::MarkFramebufferUpdated() {
	m_bFramebufferResized = true;
}

void PlatformRenderer::BeginRenderPass() {
	vkWaitForFences(m_dDeviceHandle, 1, &m_vInFlightFences[m_u32CurrentFrame], VK_TRUE, UINT64_MAX);

	vkResetFences(m_dDeviceHandle, 1, &m_vInFlightFences[m_u32CurrentFrame]);

	VkResult rRes = vkAcquireNextImageKHR(m_dDeviceHandle, m_scSwapChain, UINT64_MAX,
		m_vImageAvailableSemaphores[m_u32CurrentFrame], VK_NULL_HANDLE, &m_u32CurrentFrame);

	if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes == VK_SUBOPTIMAL_KHR) {
		RecreateSwapchain();
		return;
	}
	else if (rRes != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to acquire swapchain image!");
	}

	vkResetFences(m_dDeviceHandle, 1, &m_vInFlightFences[m_u32CurrentFrame]);

	VkCommandBuffer cbBuffer = m_vCommandBuffers[m_u32CurrentFrame];

	vkResetCommandBuffer(cbBuffer, 0);

	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pInheritanceInfo = nullptr
	};

	if (vkBeginCommandBuffer(cbBuffer, &cbbiBeginInfo) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to being recording a command buffer!");
	}

	VkRenderPassBeginInfo rpbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext = nullptr,
		.renderPass = m_rpRenderPass,
		.framebuffer = m_vFramebuffers[m_u32CurrentFrame],
		.renderArea = { { 0, 0 }, m_eExtent},
		.clearValueCount = static_cast<uint32_t>(m_arrClearValues.size()),
		.pClearValues = m_arrClearValues.data()
	};

	vkCmdBeginRenderPass(cbBuffer, &rpbiBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

}

void PlatformRenderer::Draw(uint32_t _u32ContextID) {
	VkCommandBuffer cbBuffer = m_vCommandBuffers[m_u32CurrentFrame]; //Grab command buffer for current frame.

	PlatformRenderContext::VkRenderContextData& rcdCurrentContext = PlatformRenderContext::m_mContextMap[_u32ContextID]; //Grab render context data.

	vkCmdBindPipeline(cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, rcdCurrentContext.m_pPipeline); //Set pipeline, viewport, and scissor from context.

	vkCmdSetViewport(cbBuffer, 0, 1, &rcdCurrentContext.m_vViewport);

	vkCmdSetScissor(cbBuffer, 0, 1, &rcdCurrentContext.m_rScissor);
	//Bind descriptor data from context.
	vkCmdBindDescriptorSets(cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, rcdCurrentContext.m_plPipelineLayout, 0, 1, &rcdCurrentContext.m_ddDescriptorData.m_vDescriptorSets[m_u32CurrentFrame], 0, nullptr);

	if (rcdCurrentContext.m_vVertexBuffers.size() > 0 && rcdCurrentContext.m_vIndexBuffers.size() == rcdCurrentContext.m_vVertexBuffers.size()) {
		VkDeviceSize dsOffsets[] = { 0 }; //Vulkan forcing my hand. Possibly use offsets for bindless vertices?

		for (int ndx = 0; ndx < rcdCurrentContext.m_vVertexBuffers.size(); ++ndx) {
			//Extract matching buffer handles. This assumes buffers are loaded simultaneously and thus match in bindings.
			//This will be guaranteed by the asset load code for models.
			//Possible future implementation -- Combine with bindless design to eliminate multiple vertex buffers and use
			//instancer to greatly reduce number of draw calls. Current design requires separate buffer per object per RenderContext
			VkBuffer bVertexBuffer = reinterpret_cast<VkBuffer>(rcdCurrentContext.m_vVertexBuffers[ndx].upper);
			VkBuffer bIndexBuffer = reinterpret_cast<VkBuffer>(rcdCurrentContext.m_vIndexBuffers[ndx].upper);

			vkCmdBindVertexBuffers(cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 1, &bVertexBuffer, dsOffsets);

			vkCmdBindIndexBuffer(cbBuffer, bIndexBuffer, 0, VK_INDEX_TYPE_UINT16); //Temporary -- store index type.

			vkCmdDrawIndexed(cbBuffer, PlatformBuffer::g_blData.g_mBufferDataTable[bIndexBuffer].m_u32ItemCount, 1, 0, 0, 0); //Temporary -- support instancing.
		}
	}
	else {
		throw std::runtime_error("ERROR: Attempted to draw an object with no index buffer! Models MUST include an index buffer!");
	}
}

void PlatformRenderer::Present() {
	vkCmdEndRenderPass(m_vCommandBuffers[m_u32CurrentFrame]);

	if (vkEndCommandBuffer(m_vCommandBuffers[m_u32CurrentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to record command buffer!");
	}

	VkPipelineStageFlags psfStageFlags[] = {
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
	};

	VkSubmitInfo siSubmitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &m_vImageAvailableSemaphores[m_u32CurrentFrame],
		.pWaitDstStageMask = psfStageFlags,
		.commandBufferCount = 1,
		.pCommandBuffers = &m_vCommandBuffers[m_u32CurrentFrame],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &m_vRenderFinishedSemaphores[m_u32CurrentFrame]
	};

	if (vkQueueSubmit(m_qGraphicsQueue, 1, &siSubmitInfo, m_vInFlightFences[m_u32CurrentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to submit draw command buffer!");
	}

	VkPresentInfoKHR piPresentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &m_vRenderFinishedSemaphores[m_u32CurrentFrame],
		.swapchainCount = 1,
		.pSwapchains = &m_scSwapChain,
		.pImageIndices = &m_u32CurrentFrame,
		.pResults = nullptr
	};

	VkResult rRes = vkQueuePresentKHR(m_qPresentQueue, &piPresentInfo);

	if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes == VK_SUBOPTIMAL_KHR || m_bFramebufferResized) {
		m_bFramebufferResized = false;
		RecreateSwapchain();
		return;
	}
	else if (rRes != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to present swapchain image!");
	}

	m_u32CurrentFrame = (m_u32CurrentFrame + 1) % HC_MAX_FRAMES_IN_FLIGHT;
}

void PlatformRenderer::CleanupRenderer() {
	vkDeviceWaitIdle(m_dDeviceHandle);

	CleanupSwapchain();

	vkDestroySampler(m_dDeviceHandle, m_sSampler, nullptr);

	vkDestroyImageView(m_dDeviceHandle, ivTextureView, nullptr);

	vkDestroyImage(m_dDeviceHandle, imgTexture, nullptr);

	vkFreeMemory(m_dDeviceHandle, dmTextureMemory, nullptr);

	vkDestroyDescriptorPool(m_dDeviceHandle, m_dpDescriptorPool, nullptr);

	vkDestroyDescriptorSetLayout(m_dDeviceHandle, m_dslDescriptorSetLayout, nullptr);

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		vkDestroySemaphore(m_dDeviceHandle, m_vImageAvailableSemaphores[ndx], nullptr);
		vkDestroySemaphore(m_dDeviceHandle, m_vRenderFinishedSemaphores[ndx], nullptr);
		vkDestroyFence(m_dDeviceHandle, m_vInFlightFences[ndx], nullptr);
	}

	vkDestroyCommandPool(m_dDeviceHandle, m_cpCommandPool, nullptr);

	PlatformRenderContext::CleanupAllContextData();

	vkDestroyRenderPass(m_dDeviceHandle, m_rpRenderPass, nullptr);

	vkDestroyDevice(m_dDeviceHandle, nullptr);

	vkDestroySurfaceKHR(m_iInstance, m_sSurface, nullptr);

	vkDestroyInstance(m_iInstance, nullptr);
}

void PlatformRenderer::CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion) {
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

void PlatformRenderer::SelectPhysicalDevice() {
	uint32_t u32DeviceCount = 0;
	vkEnumeratePhysicalDevices(m_iInstance, &u32DeviceCount, nullptr);

	if (!u32DeviceCount) {
		throw std::runtime_error("ERROR: Failed to find compatible GPUs!");
	}

	std::vector<VkPhysicalDevice> vDevices(u32DeviceCount);
	vkEnumeratePhysicalDevices(m_iInstance, &u32DeviceCount, vDevices.data());

	for (const auto& aDevice : vDevices) {
		if (VkUtil::CheckDeviceSuitability(aDevice)) {
			m_pdPhysicalDevice = aDevice;
			break;
		}
	}

	if (m_pdPhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("ERROR: Failed to find a suitable GPU!");
	}
}

void PlatformRenderer::CreateLogicalDevice() {
	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice);

	std::vector<VkDeviceQueueCreateInfo> vQueueCreateInfos;
	std::set<uint32_t> sUniqueQueueFamilies = {
		qfiIndices.m_u32GraphicsFamily.value(),
		qfiIndices.m_u32PresentFamily.value()
	};

	float fQueuePriority = 1.0f; //BLECK, REQUIRED FOR FUNCTION.

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

void PlatformRenderer::CreateSwapChain() {
	VkSwapChainSupportDetails scsdSupport = VkUtil::QuerySwapChainSupport(m_pdPhysicalDevice);

	VkSurfaceFormatKHR sfFormat = VkUtil::SelectSwapSurfaceFormat(scsdSupport.m_vFormats);
	VkPresentModeKHR pmMode = VkUtil::SelectSwapPresentMode(scsdSupport.m_vPresentModes);
	VkExtent2D eExtent = VkUtil::SelectSwapExtent(scsdSupport.m_scCapabilities);

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

	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice);
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

	if (vkCreateSwapchainKHR(m_dDeviceHandle, &scciSwapChainInfo, nullptr, &m_scSwapChain) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create swapchain!");
	}

	vkGetSwapchainImagesKHR(m_dDeviceHandle, m_scSwapChain, &u32ImageCount, nullptr);
	m_vSwapchainImages.resize(u32ImageCount);
	vkGetSwapchainImagesKHR(m_dDeviceHandle, m_scSwapChain, &u32ImageCount, m_vSwapchainImages.data());

	m_fFormat = sfFormat.format;
	m_eExtent = eExtent;
}

void PlatformRenderer::CreateSwapchainImageViews() {
	m_vSwapchainImageViews.resize(m_vSwapchainImages.size());

	for (int ndx = 0; ndx < m_vSwapchainImages.size(); ++ndx) {
		m_vSwapchainImageViews[ndx] = VkUtil::CreateImageView(m_vSwapchainImages[ndx], m_fFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void PlatformRenderer::CreateRenderPass() {
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
			.format = VkUtil::FindDepthFormat(),
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

void PlatformRenderer::CreateCommandPool() {
	VkQueueFamilyIndices qfiIndices = VkUtil::GetQueueFamilies(m_pdPhysicalDevice);

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

void PlatformRenderer::CreateDepthResources() {
	VkFormat fDepthFormat = VkUtil::FindDepthFormat();

	VkUtil::CreateImage(m_eExtent.width, m_eExtent.height, fDepthFormat, VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_iDepth, m_dmDepthMem);

	m_ivDepthView = VkUtil::CreateImageView(m_iDepth, fDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	VkUtil::TransitionImageLayout(m_iDepth, fDepthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void PlatformRenderer::CreateFramebuffers() {
	m_vFramebuffers.resize(m_vSwapchainImageViews.size());

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

		if (vkCreateFramebuffer(m_dDeviceHandle, &fciFramebufferInfo, nullptr, &m_vFramebuffers[ndx]) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create framebuffers!");
		}
	}
}

void PlatformRenderer::CreateTextureImage() {
	int iWidth, iHeight, iChannels;
	stbi_uc* pPixels = stbi_load("../../Assets/Textures/debug_fallback.png", &iWidth, &iHeight, &iChannels, STBI_rgb_alpha);

	VkDeviceSize dsSize = static_cast<uint64_t>(iWidth) * static_cast<uint64_t>(iHeight) * 4U;

	if (!pPixels) {
		throw std::runtime_error("ERROR: Failed to load texture!");
	}

	VkBuffer bStagingBuffer;
	VkDeviceMemory dmStagingMem;

	PlatformBuffer::CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, HC_MEMORY_FLAGS, bStagingBuffer, dmStagingMem);

	void* pvData;
	vkMapMemory(m_dDeviceHandle, dmStagingMem, 0, dsSize, 0, &pvData);
	memcpy(pvData, pPixels, static_cast<size_t>(dsSize));
	vkUnmapMemory(m_dDeviceHandle, dmStagingMem);

	stbi_image_free(pPixels);

	VkUtil::CreateImage(iWidth, iHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, imgTexture, dmTextureMemory);

	VkUtil::TransitionImageLayout(imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	
	VkUtil::CopyBufferToImage(bStagingBuffer, imgTexture, static_cast<uint32_t>(iWidth), static_cast<uint32_t>(iHeight));

	VkUtil::TransitionImageLayout(imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(m_dDeviceHandle, bStagingBuffer, nullptr);
	vkFreeMemory(m_dDeviceHandle, dmStagingMem, nullptr);
}

void PlatformRenderer::CreateTextureImageView() {
	ivTextureView = VkUtil::CreateImageView(imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void PlatformRenderer::CreateTextureSampler() {
	VkPhysicalDeviceProperties pdpProperties;
	vkGetPhysicalDeviceProperties(m_pdPhysicalDevice, &pdpProperties);

	VkSamplerCreateInfo sciSamplerInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_TRUE,
		.maxAnisotropy = pdpProperties.limits.maxSamplerAnisotropy,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_ALWAYS,
		.minLod = 0.0f,
		.maxLod = 0.0f,
		.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE
	};

	if (vkCreateSampler(m_dDeviceHandle, &sciSamplerInfo, nullptr, &m_sSampler) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create texture sampler!");
	}
}

void PlatformRenderer::CreateCommandBuffer() {
	m_vCommandBuffers.resize(HC_MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo cbaiBufferAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = m_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = static_cast<uint32_t>(m_vCommandBuffers.size())
	};

	if (vkAllocateCommandBuffers(m_dDeviceHandle, &cbaiBufferAllocateInfo, m_vCommandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate command buffers!");
	}
}

void PlatformRenderer::CreateSyncObjects() {
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

void PlatformRenderer::CleanupSwapchain() {
	vkDestroyImageView(m_dDeviceHandle, m_ivDepthView, nullptr);

	vkDestroyImage(m_dDeviceHandle, m_iDepth, nullptr);

	vkFreeMemory(m_dDeviceHandle, m_dmDepthMem, nullptr);

	for (auto aFramebuffer : m_vFramebuffers) {
		vkDestroyFramebuffer(m_dDeviceHandle, aFramebuffer, nullptr);
	}

	for (auto aView : m_vSwapchainImageViews) {
		vkDestroyImageView(m_dDeviceHandle, aView, nullptr);
	}

	vkDestroySwapchainKHR(m_dDeviceHandle, m_scSwapChain, nullptr);
}

void PlatformRenderer::RecreateSwapchain() {
	VkUtil::CheckWindowMinimized();

	vkDeviceWaitIdle(m_dDeviceHandle);

	CleanupSwapchain();

	CreateSwapChain();

	CreateSwapchainImageViews();

	CreateDepthResources();

	CreateFramebuffers();

	m_u32CurrentFrame = 0;
}