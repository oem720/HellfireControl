
#include <Platform/Vulkan/VkCore.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

#define HC_INCLUDE_SURFACE_VK
#include <Platform/OSInclude.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <External/stb/stb_image.h>

#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Core/Window.hpp>
#include <HellfireControl/Math/Matrix.hpp>

namespace LayersAndExtensions {
	std::vector<const char*> g_vValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};

#ifndef NDEBUG
	const bool g_bEnableValidationLayers = true;
#else
	const bool g_bEnableValidationLayers = false;
#endif

	const std::vector<const char*> g_vInstanceExtensions = {
		VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef WIN32
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#else

#endif
	};

	const std::vector<const char*> g_vDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
}

using namespace LayersAndExtensions;

//TEMPORARY FUNCTION!!!!!
static std::vector<char> ReadFile(const std::string& _strFilename) {
	std::ifstream fFile(_strFilename, std::ios::ate | std::ios::binary);

	if (!fFile.is_open()) {
		throw std::runtime_error("ERROR: Failed to open file!");
	}

	size_t sFileSize = static_cast<size_t>(fFile.tellg());
	std::vector<char> vBuffer(sFileSize);

	fFile.seekg(0);
	fFile.read(vBuffer.data(), sFileSize);
	fFile.close();

	return vBuffer;
}

VkVars PlatformRenderer::g_vVars = {};

void PlatformRenderer::InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor) {
	g_vVars.g_u64WindowHandle = _u64WindowHandle;

	g_vVars.g_arrClearValues = {
		VkClearValue {
			.color = { _v4ClearColor.x, _v4ClearColor.y, _v4ClearColor.z, _v4ClearColor.w }
		},
		VkClearValue {
			.depthStencil = { 1.0f, 0 }
		}
	};

	CreateInstance(_strAppName, _u32AppVersion);

	CreateSurface(_u64WindowHandle);

	SelectPhysicalDevice();

	CreateLogicalDevice();

	CreateSwapChain();

	CreateImageViews();

	CreateRenderPass();

	CreateDescriptorSetLayout();

	CreateGraphicsPipeline();

	CreateCommandPool();

	CreateDepthResources();

	CreateFramebuffers();

	CreateTextureImage(); //VERY EXTREMELY TEMPORARY ! ! !
	CreateTextureImageView();

	CreateTextureSampler();

	CreateUniformBuffers();

	CreateDescriptorPool();

	CreateDescriptorSets();

	CreateCommandBuffer();

	CreateSyncObjects();
}

void PlatformRenderer::MarkFramebufferUpdated() {
	g_vVars.g_bFramebufferResized = true;
}

void PlatformRenderer::RenderFrame() {
	vkWaitForFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame], VK_TRUE, UINT64_MAX);

	vkResetFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame]);

	VkResult rRes = vkAcquireNextImageKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, UINT64_MAX,
		g_vVars.g_vImageAvailableSemaphores[g_vVars.g_u32CurrentFrame], VK_NULL_HANDLE, &g_vVars.g_u32CurrentFrame);

	if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes == VK_SUBOPTIMAL_KHR) {
		RecreateSwapchain();
		return;
	}
	else if (rRes != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to acquire swapchain image!");
	}

	vkResetFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame]);

	vkResetCommandBuffer(g_vVars.g_vCommandBuffers[g_vVars.g_u32CurrentFrame], 0);

	RecordCommandBuffer(g_vVars.g_vCommandBuffers[g_vVars.g_u32CurrentFrame], g_vVars.g_u32CurrentFrame);

	UpdateUniformBuffer(g_vVars.g_u32CurrentFrame);

	VkPipelineStageFlags psfStageFlags[] = {
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
	};

	VkSubmitInfo siSubmitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &g_vVars.g_vImageAvailableSemaphores[g_vVars.g_u32CurrentFrame],
		.pWaitDstStageMask = psfStageFlags,
		.commandBufferCount = 1,
		.pCommandBuffers = &g_vVars.g_vCommandBuffers[g_vVars.g_u32CurrentFrame],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &g_vVars.g_vRenderFinishedSemaphores[g_vVars.g_u32CurrentFrame]
	};

	if (vkQueueSubmit(g_vVars.g_qGraphicsQueue, 1, &siSubmitInfo, g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to submit draw command buffer!");
	}

	VkPresentInfoKHR piPresentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &g_vVars.g_vRenderFinishedSemaphores[g_vVars.g_u32CurrentFrame],
		.swapchainCount = 1,
		.pSwapchains = &g_vVars.g_scSwapChain,
		.pImageIndices = &g_vVars.g_u32CurrentFrame,
		.pResults = nullptr
	};

	rRes = vkQueuePresentKHR(g_vVars.g_qPresentQueue, &piPresentInfo);

	if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes == VK_SUBOPTIMAL_KHR || g_vVars.g_bFramebufferResized) {
		g_vVars.g_bFramebufferResized = false;
		RecreateSwapchain();
		return;
	}
	else if (rRes != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to present swapchain image!");
	}

	g_vVars.g_u32CurrentFrame = (g_vVars.g_u32CurrentFrame + 1) % HC_MAX_FRAMES_IN_FLIGHT;
}

void PlatformRenderer::CleanupRenderer() {
	vkDeviceWaitIdle(g_vVars.g_dDeviceHandle);

	CleanupSwapchain();

	vkDestroySampler(g_vVars.g_dDeviceHandle, g_vVars.g_sSampler, nullptr);

	vkDestroyImageView(g_vVars.g_dDeviceHandle, g_vVars.ivTextureView, nullptr);

	vkDestroyImage(g_vVars.g_dDeviceHandle, g_vVars.imgTexture, nullptr);

	vkFreeMemory(g_vVars.g_dDeviceHandle, g_vVars.dmTextureMemory, nullptr);

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		vkDestroyBuffer(g_vVars.g_dDeviceHandle, g_vVars.g_vUbo[ndx], nullptr);
		vkFreeMemory(g_vVars.g_dDeviceHandle, g_vVars.g_vUboMem[ndx], nullptr);
	}

	vkDestroyDescriptorPool(g_vVars.g_dDeviceHandle, g_vVars.g_dpDescriptorPool, nullptr);

	vkDestroyDescriptorSetLayout(g_vVars.g_dDeviceHandle, g_vVars.g_dslDescriptorSetLayout, nullptr);

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		vkDestroySemaphore(g_vVars.g_dDeviceHandle, g_vVars.g_vImageAvailableSemaphores[ndx], nullptr);
		vkDestroySemaphore(g_vVars.g_dDeviceHandle, g_vVars.g_vRenderFinishedSemaphores[ndx], nullptr);
		vkDestroyFence(g_vVars.g_dDeviceHandle, g_vVars.g_vInFlightFences[ndx], nullptr);
	}

	vkDestroyCommandPool(g_vVars.g_dDeviceHandle, g_vVars.g_cpCommandPool, nullptr);

	vkDestroyPipeline(g_vVars.g_dDeviceHandle, g_vVars.g_pPipeline, nullptr);

	vkDestroyPipelineLayout(g_vVars.g_dDeviceHandle, g_vVars.g_plPipelineLayout, nullptr);

	vkDestroyRenderPass(g_vVars.g_dDeviceHandle, g_vVars.g_rpRenderPass, nullptr);

	vkDestroyDevice(g_vVars.g_dDeviceHandle, nullptr);

	vkDestroySurfaceKHR(g_vVars.g_iInstance, g_vVars.g_sSurface, nullptr);

	vkDestroyInstance(g_vVars.g_iInstance, nullptr);
}

void PlatformRenderer::CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion) {
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
		.enabledExtensionCount = static_cast<uint32_t>(g_vInstanceExtensions.size()),
		.ppEnabledExtensionNames = g_vInstanceExtensions.data()
	};

	if (g_bEnableValidationLayers) {
		ValidateSupportedLayers();
	
		icInstanceInfo.enabledLayerCount = static_cast<uint32_t>(g_vValidationLayers.size());
		icInstanceInfo.ppEnabledLayerNames = g_vValidationLayers.data();
	}

	if (vkCreateInstance(&icInstanceInfo, nullptr, &g_vVars.g_iInstance) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create Vulkan Instance!");
	}
}

void PlatformRenderer::CreateSurface(uint64_t _u32WindowHandle) {
	PlatformSurface::CreatePlatformSurface(_u32WindowHandle, g_vVars.g_iInstance, g_vVars.g_sSurface);
}

void PlatformRenderer::SelectPhysicalDevice() {
	uint32_t u32DeviceCount = 0;
	vkEnumeratePhysicalDevices(g_vVars.g_iInstance, &u32DeviceCount, nullptr);

	if (!u32DeviceCount) {
		throw std::runtime_error("ERROR: Failed to find compatible GPUs!");
	}

	std::vector<VkPhysicalDevice> vDevices(u32DeviceCount);
	vkEnumeratePhysicalDevices(g_vVars.g_iInstance, &u32DeviceCount, vDevices.data());

	for (const auto& aDevice : vDevices) {
		if (CheckDeviceSuitability(aDevice)) {
			g_vVars.g_pdPhysicalDevice = aDevice;
			break;
		}
	}

	if (g_vVars.g_pdPhysicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("ERROR: Failed to find a suitable GPU!");
	}
}

void PlatformRenderer::CreateLogicalDevice() {
	VkQueueFamilyIndices qfiIndices = GetQueueFamilies(g_vVars.g_pdPhysicalDevice);

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

	VkDeviceCreateInfo dciDeviceInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueCreateInfoCount = static_cast<uint32_t>(vQueueCreateInfos.size()),
		.pQueueCreateInfos = vQueueCreateInfos.data(),
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = static_cast<uint32_t>(g_vDeviceExtensions.size()),
		.ppEnabledExtensionNames = g_vDeviceExtensions.data(),
		.pEnabledFeatures = &pdfFeatures,
	};

	if (g_bEnableValidationLayers) {
		dciDeviceInfo.enabledLayerCount = static_cast<uint64_t>(g_vValidationLayers.size());
		dciDeviceInfo.ppEnabledLayerNames = g_vValidationLayers.data();
	}

	if (vkCreateDevice(g_vVars.g_pdPhysicalDevice, &dciDeviceInfo, nullptr, &g_vVars.g_dDeviceHandle) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create logical device!");
	}

	vkGetDeviceQueue(g_vVars.g_dDeviceHandle, qfiIndices.m_u32GraphicsFamily.value(), 0, &g_vVars.g_qGraphicsQueue);
	vkGetDeviceQueue(g_vVars.g_dDeviceHandle, qfiIndices.m_u32PresentFamily.value(), 0, &g_vVars.g_qPresentQueue);
}

void PlatformRenderer::CreateSwapChain() {
	VkSwapChainSupportDetails scsdSupport = QuerySwapChainSupport(g_vVars.g_pdPhysicalDevice);

	VkSurfaceFormatKHR sfFormat = SelectSwapSurfaceFormat(scsdSupport.m_vFormats);
	VkPresentModeKHR pmMode = SelectSwapPresentMode(scsdSupport.m_vPresentModes);
	VkExtent2D eExtent = SelectSwapExtent(scsdSupport.m_scCapabilities);

	uint32_t u32ImageCount = scsdSupport.m_scCapabilities.minImageCount + 1;

	if (scsdSupport.m_scCapabilities.maxImageCount > 0 && u32ImageCount > scsdSupport.m_scCapabilities.maxImageCount) {
		u32ImageCount = scsdSupport.m_scCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR scciSwapChainInfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.surface = g_vVars.g_sSurface,
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

	VkQueueFamilyIndices qfiIndices = GetQueueFamilies(g_vVars.g_pdPhysicalDevice);
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

	if (vkCreateSwapchainKHR(g_vVars.g_dDeviceHandle, &scciSwapChainInfo, nullptr, &g_vVars.g_scSwapChain) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create swapchain!");
	}

	vkGetSwapchainImagesKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, &u32ImageCount, nullptr);
	g_vVars.g_vImages.resize(u32ImageCount);
	vkGetSwapchainImagesKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, &u32ImageCount, g_vVars.g_vImages.data());

	g_vVars.g_fFormat = sfFormat.format;
	g_vVars.g_eExtent = eExtent;
}

void PlatformRenderer::CreateImageViews() {
	g_vVars.g_vImageViews.resize(g_vVars.g_vImages.size());

	for (int ndx = 0; ndx < g_vVars.g_vImages.size(); ++ndx) {
		g_vVars.g_vImageViews[ndx] = CreateImageView(g_vVars.g_vImages[ndx], g_vVars.g_fFormat, VK_IMAGE_ASPECT_COLOR_BIT);
	}
}

void PlatformRenderer::CreateRenderPass() {
	std::array<VkAttachmentDescription, 2> arrAttachments = {
		VkAttachmentDescription {
			.flags = 0,
			.format = g_vVars.g_fFormat,
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
			.format = FindDepthFormat(),
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

	if (vkCreateRenderPass(g_vVars.g_dDeviceHandle, &rpciRenderPassInfo, nullptr, &g_vVars.g_rpRenderPass) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create render pass!");
	}
}

void PlatformRenderer::CreateDescriptorSetLayout() {
	VkDescriptorSetLayoutBinding dslbUboLayoutBinding = {
		.binding = 0,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = 1,
		.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
		.pImmutableSamplers = nullptr
	};

	VkDescriptorSetLayoutBinding dslbSamplerBinding = {
		.binding = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		.descriptorCount = 1,
		.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
		.pImmutableSamplers = nullptr
	};

	std::array<VkDescriptorSetLayoutBinding, 2> arrBindings = { dslbUboLayoutBinding, dslbSamplerBinding };

	VkDescriptorSetLayoutCreateInfo dslciDescriptorLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.bindingCount = static_cast<uint32_t>(arrBindings.size()),
		.pBindings = arrBindings.data()
	};

	if (vkCreateDescriptorSetLayout(g_vVars.g_dDeviceHandle, &dslciDescriptorLayoutInfo, nullptr, &g_vVars.g_dslDescriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create descriptor set layout!");
	}
}

void PlatformRenderer::CreateGraphicsPipeline() {
	auto aVertShader = ReadFile("../../Assets/Shaders/Vulkan/test_vert.spv"); //TEMPORARY ! ! !
	auto aFragShader = ReadFile("../../Assets/Shaders/Vulkan/test_frag.spv");

	VkShaderModule smVert = CreateShaderModule(aVertShader);
	VkShaderModule smFrag = CreateShaderModule(aFragShader);

	VkPipelineShaderStageCreateInfo pssciVertShaderInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = smVert,
		.pName = "main",
		.pSpecializationInfo = nullptr
	};

	VkPipelineShaderStageCreateInfo pssciFragShaderInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = smFrag,
		.pName = "main",
		.pSpecializationInfo = nullptr
	};

	VkPipelineShaderStageCreateInfo pssciShaderStages[] = { pssciVertShaderInfo, pssciFragShaderInfo };

	auto aBinding = VertexSimple::GetBindingDescription();
	auto aAttributes = VertexSimple::GetAttributeDescriptions();

	VkPipelineVertexInputStateCreateInfo pvisciVertexInputInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.vertexBindingDescriptionCount = 1, //TEMPORARY ! ! ! 
		.pVertexBindingDescriptions = &aBinding,
		.vertexAttributeDescriptionCount = static_cast<uint32_t>(aAttributes.size()),
		.pVertexAttributeDescriptions = aAttributes.data()
	};

	VkPipelineInputAssemblyStateCreateInfo piasciInputAssemblyInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE
	};

	std::vector<VkDynamicState> vDynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo pdsciDynamicStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.dynamicStateCount = static_cast<uint32_t>(vDynamicStates.size()),
		.pDynamicStates = vDynamicStates.data(),
	};

	VkPipelineViewportStateCreateInfo pvsciViewportStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.viewportCount = 1,
		.pViewports = nullptr,
		.scissorCount = 1,
		.pScissors = nullptr
	};

	VkPipelineRasterizationStateCreateInfo prsciRasterizerInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 0.0f,
		.depthBiasClamp = 0.0f,
		.depthBiasSlopeFactor = 0.0f,
		.lineWidth = 1.0f
	};

	VkPipelineMultisampleStateCreateInfo pmsciMultisampleStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 1.0f,
		.pSampleMask = nullptr,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE
	};

	VkPipelineDepthStencilStateCreateInfo pdssciDepthStencilStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthTestEnable = VK_TRUE,
		.depthWriteEnable = VK_TRUE,
		.depthCompareOp = VK_COMPARE_OP_LESS,
		.depthBoundsTestEnable = VK_FALSE,
		.stencilTestEnable = VK_FALSE,
		.front = {},
		.back = {},
		.minDepthBounds = 1.0f,
		.maxDepthBounds = 0.0f
	};

	VkPipelineColorBlendAttachmentState pcbasColorBlendState = {
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
	};

	VkPipelineColorBlendStateCreateInfo pcbsciColorBlendStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = &pcbasColorBlendState,
		.blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f }
	};

	VkPipelineLayoutCreateInfo plciLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.setLayoutCount = 1,
		.pSetLayouts = &g_vVars.g_dslDescriptorSetLayout,
		.pushConstantRangeCount = 0, //PUSH CONSTANTS HERE
		.pPushConstantRanges = nullptr
	};

	if (vkCreatePipelineLayout(g_vVars.g_dDeviceHandle, &plciLayoutInfo, nullptr, &g_vVars.g_plPipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo gpciGraphicsPipelineInfo = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stageCount = 2,
		.pStages = pssciShaderStages,
		.pVertexInputState = &pvisciVertexInputInfo,
		.pInputAssemblyState = &piasciInputAssemblyInfo,
		.pTessellationState = nullptr,
		.pViewportState = &pvsciViewportStateInfo,
		.pRasterizationState = &prsciRasterizerInfo,
		.pMultisampleState = &pmsciMultisampleStateInfo,
		.pDepthStencilState = &pdssciDepthStencilStateInfo,
		.pColorBlendState = &pcbsciColorBlendStateInfo,
		.pDynamicState = &pdsciDynamicStateInfo,
		.layout = g_vVars.g_plPipelineLayout,
		.renderPass = g_vVars.g_rpRenderPass,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = 0
	};

	if (vkCreateGraphicsPipelines(g_vVars.g_dDeviceHandle, VK_NULL_HANDLE, 1, &gpciGraphicsPipelineInfo, nullptr, &g_vVars.g_pPipeline) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create the graphics pipeline!");
	}

	vkDestroyShaderModule(g_vVars.g_dDeviceHandle, smVert, nullptr); //TEMPORARY ! ! !
	vkDestroyShaderModule(g_vVars.g_dDeviceHandle, smFrag, nullptr);
}

void PlatformRenderer::CreateCommandPool() {
	VkQueueFamilyIndices qfiIndices = GetQueueFamilies(g_vVars.g_pdPhysicalDevice);

	VkCommandPoolCreateInfo cpciPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = qfiIndices.m_u32GraphicsFamily.value()
	};

	if (vkCreateCommandPool(g_vVars.g_dDeviceHandle, &cpciPoolCreateInfo, nullptr, &g_vVars.g_cpCommandPool) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create command pool!");
	}
}

void PlatformRenderer::CreateDepthResources() {
	VkFormat fDepthFormat = FindDepthFormat();

	CreateImage(g_vVars.g_eExtent.width, g_vVars.g_eExtent.height, fDepthFormat, VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, g_vVars.g_iDepth, g_vVars.g_dmDepthMem);

	g_vVars.g_ivDepthView = CreateImageView(g_vVars.g_iDepth, fDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

	TransitionImageLayout(g_vVars.g_iDepth, fDepthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void PlatformRenderer::CreateFramebuffers() {
	g_vVars.g_vFramebuffers.resize(g_vVars.g_vImageViews.size());

	for (int ndx = 0; ndx < g_vVars.g_vImageViews.size(); ++ndx) {
		std::array<VkImageView, 2> arrAttachments = {
			g_vVars.g_vImageViews[ndx],
			g_vVars.g_ivDepthView
		};

		VkFramebufferCreateInfo fciFramebufferInfo = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.renderPass = g_vVars.g_rpRenderPass,
			.attachmentCount = static_cast<uint32_t>(arrAttachments.size()),
			.pAttachments = arrAttachments.data(),
			.width = g_vVars.g_eExtent.width,
			.height = g_vVars.g_eExtent.height,
			.layers = 1
		};

		if (vkCreateFramebuffer(g_vVars.g_dDeviceHandle, &fciFramebufferInfo, nullptr, &g_vVars.g_vFramebuffers[ndx]) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create framebuffers!");
		}
	}
}

void PlatformRenderer::CreateTextureImage() {
	int iWidth, iHeight, iChannels;
	stbi_uc* pPixels = stbi_load("../../Assets/Textures/test_texture.jpg", &iWidth, &iHeight, &iChannels, STBI_rgb_alpha);

	VkDeviceSize dsSize = iWidth * iHeight * 4;

	if (!pPixels) {
		throw std::runtime_error("ERROR: Failed to load texture!");
	}

	VkBuffer bStagingBuffer;
	VkDeviceMemory dmStagingMem;

	PlatformBuffer::CreateBuffer(dsSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, HC_MEMORY_FLAGS, bStagingBuffer, dmStagingMem);

	void* pvData;
	vkMapMemory(g_vVars.g_dDeviceHandle, dmStagingMem, 0, dsSize, 0, &pvData);
	memcpy(pvData, pPixels, static_cast<size_t>(dsSize));
	vkUnmapMemory(g_vVars.g_dDeviceHandle, dmStagingMem);

	stbi_image_free(pPixels);

	CreateImage(iWidth, iHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, g_vVars.imgTexture, g_vVars.dmTextureMemory);

	TransitionImageLayout(g_vVars.imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	
	CopyBufferToImage(bStagingBuffer, g_vVars.imgTexture, static_cast<uint32_t>(iWidth), static_cast<uint32_t>(iHeight));

	TransitionImageLayout(g_vVars.imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(g_vVars.g_dDeviceHandle, bStagingBuffer, nullptr);
	vkFreeMemory(g_vVars.g_dDeviceHandle, dmStagingMem, nullptr);
}

void PlatformRenderer::CreateTextureImageView() {
	g_vVars.ivTextureView = CreateImageView(g_vVars.imgTexture, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void PlatformRenderer::CreateImage(uint32_t _iWidth, uint32_t _iHeight, VkFormat _fFormat, VkImageTiling _itTiling, VkImageUsageFlags _iufFlags, VkMemoryPropertyFlags _mpfProperties, VkImage& _iImage, VkDeviceMemory& _dmImageMem) {
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

	if (vkCreateImage(g_vVars.g_dDeviceHandle, &iciImageInfo, nullptr, &_iImage) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create image!");
	}

	VkMemoryRequirements mrRequirements;
	vkGetImageMemoryRequirements(g_vVars.g_dDeviceHandle, _iImage, &mrRequirements);

	VkMemoryAllocateInfo maiAllocInfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = nullptr,
		.allocationSize = mrRequirements.size,
		.memoryTypeIndex = PlatformBuffer::FindMemoryType(mrRequirements.memoryTypeBits, _mpfProperties)
	};

	if (vkAllocateMemory(g_vVars.g_dDeviceHandle, &maiAllocInfo, nullptr, &_dmImageMem) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate iamge memory!");
	}

	vkBindImageMemory(g_vVars.g_dDeviceHandle, _iImage, _dmImageMem, 0);
}

void PlatformRenderer::TransitionImageLayout(VkImage _iImage, VkFormat _fFormat, VkImageLayout _ilLayoutOld, VkImageLayout _ilLayoutNew) {
	VkCommandBuffer cbBuffer = BeginSingleTimeCommands();

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

		if (HasStencilComponent(_fFormat)) {
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

	vkCmdPipelineBarrier(cbBuffer, psfSrcFlags, psfDestFlags, 0, 0, nullptr, 0, nullptr, 1, &imbBarrier);

	EndSingleTimeCommands(cbBuffer);
}

void PlatformRenderer::CopyBufferToImage(VkBuffer _bBuffer, VkImage _iImage, uint32_t _u32Width, uint32_t _u32Height) {
	VkCommandBuffer cbBuffer = BeginSingleTimeCommands();

	VkBufferImageCopy bicImageCopy = {
		.bufferOffset = 0,
		.bufferRowLength = 0,
		.bufferImageHeight = 0,
		.imageSubresource = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
		.imageOffset = {
			.x = 0,
			.y = 0,
			.z = 0
		},
		.imageExtent = {
			.width = _u32Width,
			.height = _u32Height,
			.depth = 1
		}
	};

	vkCmdCopyBufferToImage(cbBuffer, _bBuffer, _iImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &bicImageCopy);

	EndSingleTimeCommands(cbBuffer);
}

void PlatformRenderer::CreateUniformBuffers() {
	VkDeviceSize dsSize = sizeof(UniformBufferData);

	g_vVars.g_vUbo.resize(HC_MAX_FRAMES_IN_FLIGHT);
	g_vVars.g_vUboMem.resize(HC_MAX_FRAMES_IN_FLIGHT);
	g_vVars.g_vUboMapped.resize(HC_MAX_FRAMES_IN_FLIGHT);

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		PlatformBuffer::CreateBuffer(dsSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, HC_MEMORY_FLAGS, g_vVars.g_vUbo[ndx], g_vVars.g_vUboMem[ndx]);

		vkMapMemory(g_vVars.g_dDeviceHandle, g_vVars.g_vUboMem[ndx], 0, dsSize, 0, &g_vVars.g_vUboMapped[ndx]);
	}
}

void PlatformRenderer::CreateTextureSampler() {
	VkPhysicalDeviceProperties pdpProperties;
	vkGetPhysicalDeviceProperties(g_vVars.g_pdPhysicalDevice, &pdpProperties);

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

	if (vkCreateSampler(g_vVars.g_dDeviceHandle, &sciSamplerInfo, nullptr, &g_vVars.g_sSampler) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create texture sampler!");
	}
}

void PlatformRenderer::CreateDescriptorPool() {
	std::array<VkDescriptorPoolSize, 2> arrDescSize = {
		VkDescriptorPoolSize {
			.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = static_cast<uint32_t>(HC_MAX_FRAMES_IN_FLIGHT)
		},
		VkDescriptorPoolSize {
			.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.descriptorCount = static_cast<uint32_t>(HC_MAX_FRAMES_IN_FLIGHT)
		}
	};

	VkDescriptorPoolCreateInfo dpciPoolInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.maxSets = static_cast<uint32_t>(HC_MAX_FRAMES_IN_FLIGHT),
		.poolSizeCount = arrDescSize.size(),
		.pPoolSizes = arrDescSize.data()
	};

	if (vkCreateDescriptorPool(g_vVars.g_dDeviceHandle, &dpciPoolInfo, nullptr, &g_vVars.g_dpDescriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create Descriptor Pool!");
	}
}

void PlatformRenderer::CreateDescriptorSets() {
	std::vector<VkDescriptorSetLayout> vLayouts(HC_MAX_FRAMES_IN_FLIGHT, g_vVars.g_dslDescriptorSetLayout); //Blech, fuck you Vulkan
	g_vVars.g_vDescriptorSets.resize(HC_MAX_FRAMES_IN_FLIGHT);

	VkDescriptorSetAllocateInfo dsaiAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = g_vVars.g_dpDescriptorPool,
		.descriptorSetCount = static_cast<uint32_t>(HC_MAX_FRAMES_IN_FLIGHT),
		.pSetLayouts = vLayouts.data()
	};

	if (vkAllocateDescriptorSets(g_vVars.g_dDeviceHandle, &dsaiAllocateInfo, g_vVars.g_vDescriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate Descriptor Sets!");
	}

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		VkDescriptorBufferInfo dbiBufferInfo = {
			.buffer = g_vVars.g_vUbo[ndx],
			.offset = 0,
			.range = sizeof(UniformBufferData)
		};

		VkDescriptorImageInfo dbiImageInfo = {
			.sampler = g_vVars.g_sSampler,
			.imageView = g_vVars.ivTextureView,
			.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		};

		std::array<VkWriteDescriptorSet, 2> arrDescWrite = {
			VkWriteDescriptorSet {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = g_vVars.g_vDescriptorSets[ndx],
				.dstBinding = 0,
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImageInfo = nullptr,
				.pBufferInfo = &dbiBufferInfo,
				.pTexelBufferView = nullptr
			},
			VkWriteDescriptorSet {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = g_vVars.g_vDescriptorSets[ndx],
				.dstBinding = 1,
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.pImageInfo = &dbiImageInfo,
				.pBufferInfo = nullptr,
				.pTexelBufferView = nullptr
			}
		};

		vkUpdateDescriptorSets(g_vVars.g_dDeviceHandle, static_cast<uint32_t>(arrDescWrite.size()), arrDescWrite.data(), 0, nullptr);
	}
}

void PlatformRenderer::CreateCommandBuffer() {
	g_vVars.g_vCommandBuffers.resize(HC_MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo cbaiBufferAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = g_vVars.g_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = static_cast<uint32_t>(g_vVars.g_vCommandBuffers.size())
	};

	if (vkAllocateCommandBuffers(g_vVars.g_dDeviceHandle, &cbaiBufferAllocateInfo, g_vVars.g_vCommandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate command buffers!");
	}
}

void PlatformRenderer::CreateSyncObjects() {
	g_vVars.g_vImageAvailableSemaphores.resize(HC_MAX_FRAMES_IN_FLIGHT);
	g_vVars.g_vRenderFinishedSemaphores.resize(HC_MAX_FRAMES_IN_FLIGHT);
	g_vVars.g_vInFlightFences.resize(HC_MAX_FRAMES_IN_FLIGHT);

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
		if (vkCreateSemaphore(g_vVars.g_dDeviceHandle, &sciSemaphoreInfo, nullptr, &g_vVars.g_vImageAvailableSemaphores[ndx]) != VK_SUCCESS ||
			vkCreateSemaphore(g_vVars.g_dDeviceHandle, &sciSemaphoreInfo, nullptr, &g_vVars.g_vRenderFinishedSemaphores[ndx]) != VK_SUCCESS ||
			vkCreateFence(g_vVars.g_dDeviceHandle, &fciFenceInfo, nullptr, &g_vVars.g_vInFlightFences[ndx]) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create sync objects!");
		}
	}
}

void PlatformRenderer::RecordCommandBuffer(VkCommandBuffer _cbBuffer, uint32_t _u32ImageIndex) {
	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pInheritanceInfo = nullptr
	};

	if (vkBeginCommandBuffer(_cbBuffer, &cbbiBeginInfo) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to being recording a command buffer!");
	}
	
	//TEMPORARY ! ! ! MOVE TO MORE GENERIC FUNCTIONS ! ! !

	VkRenderPassBeginInfo rpbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext = nullptr,
		.renderPass = g_vVars.g_rpRenderPass,
		.framebuffer = g_vVars.g_vFramebuffers[_u32ImageIndex],
		.renderArea = { { 0, 0 }, g_vVars.g_eExtent},
		.clearValueCount = static_cast<uint32_t>(g_vVars.g_arrClearValues.size()),
		.pClearValues = g_vVars.g_arrClearValues.data()
	};

	vkCmdBeginRenderPass(_cbBuffer, &rpbiBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(_cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, g_vVars.g_pPipeline);

	VkViewport vViewport = {
		.x = 0.0f,
		.y = 0.0f,
		.width = static_cast<float>(g_vVars.g_eExtent.width),
		.height = static_cast<float>(g_vVars.g_eExtent.height),
		.minDepth = 1.0f,
		.maxDepth = 0.0f
	};

	vkCmdSetViewport(_cbBuffer, 0, 1, &vViewport);

	VkRect2D rScissor = {
		.offset = { 0, 0 },
		.extent = g_vVars.g_eExtent
	};

	vkCmdSetScissor(_cbBuffer, 0, 1, &rScissor);

	//SERIOUSLY ! ! ! THIS SHIT IS TEMPORARY ! ! !
	const std::map<VkBuffer, BufferData>* pBuffers = PlatformBuffer::GetActiveBufferData();

	uint32_t u32IndexCount = 0;
	for (const auto& aBufferPair : *pBuffers) {
		if (aBufferPair.second.m_u8Type == 0) {
			VkDeviceSize dsOffsets[] = { 0 };

			vkCmdBindVertexBuffers(_cbBuffer, 0, 1, &aBufferPair.first, dsOffsets);
		}
		if (aBufferPair.second.m_u8Type == 1) {
			vkCmdBindIndexBuffer(_cbBuffer, aBufferPair.first, 0, VK_INDEX_TYPE_UINT16);
			u32IndexCount = aBufferPair.second.m_u32ItemCount; 
		}
	}
	vkCmdBindDescriptorSets(_cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, g_vVars.g_plPipelineLayout, 0, 1, &g_vVars.g_vDescriptorSets[_u32ImageIndex], 0, nullptr);
	vkCmdDrawIndexed(_cbBuffer, u32IndexCount, 1, 0, 0, 0); //TEMPORARY ! ! ! WILL BREAK IF NO INDEX_BUFFER BUFFER PRESENT ! ! !

	vkCmdEndRenderPass(_cbBuffer);

	if (vkEndCommandBuffer(_cbBuffer) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to record command buffer!");
	}
}

VkCommandBuffer PlatformRenderer::BeginSingleTimeCommands() {
	VkCommandBufferAllocateInfo cbaiBufferInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = PlatformRenderer::g_vVars.g_cpCommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1
	};

	VkCommandBuffer cbBuffer;

	vkAllocateCommandBuffers(PlatformRenderer::g_vVars.g_dDeviceHandle, &cbaiBufferInfo, &cbBuffer);

	VkCommandBufferBeginInfo cbbiBeginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = nullptr
	};

	vkBeginCommandBuffer(cbBuffer, &cbbiBeginInfo);

	return cbBuffer;
}

void PlatformRenderer::EndSingleTimeCommands(VkCommandBuffer _cbBuffer) {
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

	vkQueueSubmit(PlatformRenderer::g_vVars.g_qGraphicsQueue, 1, &siSubmitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(PlatformRenderer::g_vVars.g_qGraphicsQueue);

	vkFreeCommandBuffers(PlatformRenderer::g_vVars.g_dDeviceHandle, PlatformRenderer::g_vVars.g_cpCommandPool, 1, &_cbBuffer);
}

VkImageView PlatformRenderer::CreateImageView(VkImage _iImage, VkFormat _fFormat, VkImageAspectFlags _iafFlags) {
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

	if (vkCreateImageView(g_vVars.g_dDeviceHandle, &ivciViewInfo, nullptr, &ivView) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to create texture image view!");
	}

	return ivView;
}

VkFormat PlatformRenderer::FindSupportedFormat(const std::vector<VkFormat>& _vCandidates, VkImageTiling _itTiling, VkFormatFeatureFlags _fffFeatures) {
	for (VkFormat fFormat : _vCandidates) {
		VkFormatProperties fpProperties;
		vkGetPhysicalDeviceFormatProperties(g_vVars.g_pdPhysicalDevice, fFormat, &fpProperties);

		if ((_itTiling == VK_IMAGE_TILING_LINEAR && (fpProperties.linearTilingFeatures & _fffFeatures) == _fffFeatures) ||
			(_itTiling == VK_IMAGE_TILING_OPTIMAL && (fpProperties.optimalTilingFeatures & _fffFeatures) == _fffFeatures)) {
			return fFormat;
		}
	}

	throw std::runtime_error("ERROR: Failed to find a supported format!");
}

VkFormat PlatformRenderer::FindDepthFormat() {
	return FindSupportedFormat({VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
		VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

bool PlatformRenderer::HasStencilComponent(VkFormat _fFormat) {
	return _fFormat == VK_FORMAT_D32_SFLOAT_S8_UINT || _fFormat == VK_FORMAT_D24_UNORM_S8_UINT;
}

void PlatformRenderer::CleanupSwapchain() {
	vkDestroyImageView(g_vVars.g_dDeviceHandle, g_vVars.g_ivDepthView, nullptr);
	
	vkDestroyImage(g_vVars.g_dDeviceHandle, g_vVars.g_iDepth, nullptr);

	vkFreeMemory(g_vVars.g_dDeviceHandle, g_vVars.g_dmDepthMem, nullptr);

	for (auto aFramebuffer : g_vVars.g_vFramebuffers) {
		vkDestroyFramebuffer(g_vVars.g_dDeviceHandle, aFramebuffer, nullptr);
	}

	for (auto aView : g_vVars.g_vImageViews) {
		vkDestroyImageView(g_vVars.g_dDeviceHandle, aView, nullptr);
	}

	vkDestroySwapchainKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, nullptr);
}

void PlatformRenderer::RecreateSwapchain() {
	CheckWindowMinimized();

	vkDeviceWaitIdle(g_vVars.g_dDeviceHandle);

	CleanupSwapchain();

	CreateSwapChain();

	CreateImageViews();

	CreateDepthResources();

	CreateFramebuffers();

	g_vVars.g_u32CurrentFrame = 0;
}

void PlatformRenderer::ValidateSupportedLayers() {
	uint32_t u32LayerCount = 0;		
	vkEnumerateInstanceLayerProperties(&u32LayerCount, nullptr);

	std::vector<VkLayerProperties> vLayerProperties(u32LayerCount);		
	vkEnumerateInstanceLayerProperties(&u32LayerCount, vLayerProperties.data());

	for (int ndx = 0; ndx < g_vValidationLayers.size(); ++ndx) {
		bool bLayerFound = false;

		for (const auto& aLayerProperties : vLayerProperties) {
			if (!strcmp(g_vValidationLayers[ndx], aLayerProperties.layerName)) {
				bLayerFound = true;
				break;
			}
		}

		if (!bLayerFound) {
			g_vValidationLayers.erase(g_vValidationLayers.begin() + ndx--); //If our layer is unsupported, remove it.
		}
	}
}

bool PlatformRenderer::ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice) {
	uint32_t u32ExtensionCount;
	vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, nullptr);

	std::vector<VkExtensionProperties> vAvailableExtensions(u32ExtensionCount);
	vkEnumerateDeviceExtensionProperties(_pdDevice, nullptr, &u32ExtensionCount, vAvailableExtensions.data());

	std::set<std::string> sRequiredExtensions(g_vDeviceExtensions.begin(), g_vDeviceExtensions.end());

	for (const auto& aExtension : vAvailableExtensions) {
		sRequiredExtensions.erase(aExtension.extensionName);
	}

	return sRequiredExtensions.empty();
}

bool PlatformRenderer::CheckDeviceSuitability(VkPhysicalDevice _pdDevice) {
	VkPhysicalDeviceProperties pdpProperties = {};
	vkGetPhysicalDeviceProperties(_pdDevice, &pdpProperties);

	VkPhysicalDeviceFeatures pdfFeatures = {};
	vkGetPhysicalDeviceFeatures(_pdDevice, &pdfFeatures);

	VkQueueFamilyIndices qfiIndices = GetQueueFamilies(_pdDevice);

	bool bExtensionsSupported = ValidateSupportedDeviceExtensions(_pdDevice);

	bool bSwapChainAdequate = false;

	if (bExtensionsSupported) {
		VkSwapChainSupportDetails scsdSupport = QuerySwapChainSupport(_pdDevice);
		bSwapChainAdequate = !scsdSupport.m_vFormats.empty() && !scsdSupport.m_vPresentModes.empty();
	}
	
	return pdpProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && qfiIndices.IsComplete()
		&& bExtensionsSupported && bSwapChainAdequate && pdfFeatures.samplerAnisotropy;
}

VkQueueFamilyIndices PlatformRenderer::GetQueueFamilies(VkPhysicalDevice _pdDevice) {
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

		vkGetPhysicalDeviceSurfaceSupportKHR(_pdDevice, iFamilyNumber, g_vVars.g_sSurface, &bPresentSupport);
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

VkSwapChainSupportDetails PlatformRenderer::QuerySwapChainSupport(VkPhysicalDevice _pdDevice) {
	VkSwapChainSupportDetails scsdDetails = {};

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_pdDevice, g_vVars.g_sSurface, &scsdDetails.m_scCapabilities);

	uint32_t u32FormatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, g_vVars.g_sSurface, &u32FormatCount, nullptr);

	if (u32FormatCount) {
		scsdDetails.m_vFormats.resize(u32FormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_pdDevice, g_vVars.g_sSurface, &u32FormatCount, scsdDetails.m_vFormats.data());
	}

	uint32_t u32PresentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, g_vVars.g_sSurface, &u32PresentModeCount, nullptr);

	if (u32PresentModeCount) {
		scsdDetails.m_vPresentModes.resize(u32PresentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_pdDevice, g_vVars.g_sSurface, &u32PresentModeCount, scsdDetails.m_vPresentModes.data());
	}

	return scsdDetails;
}

VkSurfaceFormatKHR PlatformRenderer::SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats) {
	for (const auto& aAvailableFormat : _vAvailableFormats) {
		if (aAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && aAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return aAvailableFormat;
		}
	}

	return _vAvailableFormats[0];
}

VkPresentModeKHR PlatformRenderer::SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes) {
	for (const auto& aAvailablePresentMode : _vAvailablePresentModes) {
		if (aAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return aAvailablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D PlatformRenderer::SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities) {
	if (_scCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return _scCapabilities.currentExtent;
	}
	else {
		Vec2F v2Size = Window(g_vVars.g_u64WindowHandle).GetWindowSize();

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

VkShaderModule PlatformRenderer::CreateShaderModule(const std::vector<char>& _vCode) {
	VkShaderModule smShader = VK_NULL_HANDLE;

	VkShaderModuleCreateInfo smciShaderInfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.codeSize = _vCode.size(),
		.pCode = reinterpret_cast<const uint32_t*>(_vCode.data())
	};

	if (vkCreateShaderModule(g_vVars.g_dDeviceHandle, &smciShaderInfo, nullptr, &smShader)) {
		throw std::runtime_error("ERROR: Could not create shader module!");
	}

	return smShader;
}

void PlatformRenderer::CheckWindowMinimized() {
	Window wWindow(g_vVars.g_u64WindowHandle);

	Vec2F v2WindowSize = wWindow.GetWindowSize();

	while (v2WindowSize == Vec2F(0, 0)) { //Wait here to until the window is no longer 0,0 size.
		v2WindowSize = wWindow.GetWindowSize();
		wWindow.WaitEvents();
	}
}

void PlatformRenderer::UpdateUniformBuffer(uint32_t _u32CurrentImage) {
	static auto aStartTime = std::chrono::high_resolution_clock::now();
	auto aCurrentTime = std::chrono::high_resolution_clock::now();
	float fTime = std::chrono::duration<float, std::chrono::seconds::period>(aCurrentTime - aStartTime).count();

	UniformBufferData ubdData = {
		.m_mModel = RotateZGlobalDeg(fTime * HC_DEG2RAD(90.0f) * 15.0f, IdentityF()),
		.m_mView = Inverse(LookAtLH(Vec3F(1.0f, 1.0f, 1.0f), Vec3F(0.0f, 0.0f, 0.0f), Vec3F(0.0f, 0.0f, 1.0f))),
		.m_mProj = ProjectionF(static_cast<float>(g_vVars.g_eExtent.width) / static_cast<float>(g_vVars.g_eExtent.height), HC_DEG2RAD(45.0f), 0.1f, 10.0f)
	};

	memcpy(g_vVars.g_vUboMapped[_u32CurrentImage], &ubdData, sizeof(ubdData));
}