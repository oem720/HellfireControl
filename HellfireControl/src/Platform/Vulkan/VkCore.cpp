
#include <Platform/Vulkan/VkCore.hpp>

#define HC_INCLUDE_SURFACE_VK
#include <Platform/OSInclude.hpp>

#include <HellfireControl/Core/Window.hpp>

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

using namespace LayersAndExtensions;

namespace PlatformRenderer {
	void CreateInstance(const std::string& _strAppName, uint32_t _u32Version);
	void CreateSurface(uint64_t _u64WindowHandle);
	void SelectPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffer();
	void CreateSyncObjects();

	void RecordCommandBuffer(VkCommandBuffer _cbBuffer, uint32_t _u32ImageIndex);
	void CleanupSwapchain();
	void RecreateSwapchain();

	void ValidateSupportedLayers();
	bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice);
	bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice);
	VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice);
	VkSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _pdDevice);
	VkSurfaceFormatKHR SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats);
	VkPresentModeKHR SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes);
	VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities);
	VkShaderModule CreateShaderModule(const std::vector<char>& _vCode);

	void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor) {
		g_vVars.g_u64WindowHandle = _u64WindowHandle;

		g_vVars.g_cvClearColor.color = { _v4ClearColor.x, _v4ClearColor.y, _v4ClearColor.z, _v4ClearColor.w };

		CreateInstance(_strAppName, _u32AppVersion);

		CreateSurface(_u64WindowHandle);

		SelectPhysicalDevice();

		CreateLogicalDevice();

		CreateSwapChain();

		CreateImageViews();

		CreateRenderPass();

		CreateGraphicsPipeline();

		CreateFramebuffers();

		CreateCommandPool();

		CreateCommandBuffer();

		CreateSyncObjects();
	}

	void CreateInstance(const std::string& _strAppName, uint32_t _u32AppVersion) {
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

	void CreateSurface(uint64_t _u32WindowHandle) {
		PlatformSurface::CreatePlatformSurface(_u32WindowHandle, g_vVars.g_iInstance, g_vVars.g_sSurface);
	}

	void SelectPhysicalDevice() {
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

	void CreateLogicalDevice() {
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

		VkPhysicalDeviceFeatures pdfFeatures = {}; //TODO Enumerate device features needed for engine function

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

	void CreateSwapChain() {
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

	void CreateImageViews() {
		g_vVars.g_vImageViews.resize(g_vVars.g_vImages.size());

		for (int ndx = 0; ndx < g_vVars.g_vImages.size(); ++ndx) {
			VkComponentMapping cmMapping = {
				.r = VK_COMPONENT_SWIZZLE_IDENTITY,
				.g = VK_COMPONENT_SWIZZLE_IDENTITY,
				.b = VK_COMPONENT_SWIZZLE_IDENTITY,
				.a = VK_COMPONENT_SWIZZLE_IDENTITY
			};

			VkImageSubresourceRange isrRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			};

			VkImageViewCreateInfo ivciImageViewInfo = {
				.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.image = g_vVars.g_vImages[ndx],
				.viewType = VK_IMAGE_VIEW_TYPE_2D,
				.format = g_vVars.g_fFormat,
				.components = cmMapping,
				.subresourceRange = isrRange
			};

			if (vkCreateImageView(g_vVars.g_dDeviceHandle, &ivciImageViewInfo, nullptr, &g_vVars.g_vImageViews[ndx]) != VK_SUCCESS) {
				throw std::runtime_error("ERROR: Failed to initialize image views!");
			}
		}
	}

	void CreateRenderPass() {
		VkAttachmentDescription adAttachmentDesc = {
			.flags = 0,
			.format = g_vVars.g_fFormat,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
		};

		VkAttachmentReference arAttachmentRef = {
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		};

		VkSubpassDescription sdSubpassDesc = {
			.flags = 0,
			.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
			.inputAttachmentCount = 0,
			.pInputAttachments = nullptr,
			.colorAttachmentCount = 1,
			.pColorAttachments = &arAttachmentRef,
			.pResolveAttachments = 0,
			.pDepthStencilAttachment = nullptr,
			.preserveAttachmentCount = 0,
			.pPreserveAttachments = nullptr
		};

		VkSubpassDependency sdSubpassDependency = {
			.srcSubpass = VK_SUBPASS_EXTERNAL,
			.dstSubpass = 0,
			.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
			.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
			.srcAccessMask = 0,
			.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
			.dependencyFlags = 0
		};

		VkRenderPassCreateInfo rpciRenderPassInfo = {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.attachmentCount = 1,
			.pAttachments = &adAttachmentDesc,
			.subpassCount = 1,
			.pSubpasses = &sdSubpassDesc,
			.dependencyCount = 1,
			.pDependencies = &sdSubpassDependency
		};

		if (vkCreateRenderPass(g_vVars.g_dDeviceHandle, &rpciRenderPassInfo, nullptr, &g_vVars.g_rpRenderPass) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create render pass!");
		}
	}

	void CreateGraphicsPipeline() {
		auto aVertShader = ReadFile("../../Assets/Shaders/Vulkan/vert.spv"); //TEMPORARY ! ! !
		auto aFragShader = ReadFile("../../Assets/Shaders/Vulkan/frag.spv");

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

		VkPipelineVertexInputStateCreateInfo pvisciVertexInputInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.vertexBindingDescriptionCount = 0, //TEMPORARY ! ! ! 
			.pVertexBindingDescriptions = nullptr,
			.vertexAttributeDescriptionCount = 0,
			.pVertexAttributeDescriptions = nullptr
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

		//DEPTH BUFFER GOES HERE

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
			.setLayoutCount = 0,
			.pSetLayouts = nullptr,
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
			.pDepthStencilState = nullptr,
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

	void CreateFramebuffers() {
		g_vVars.g_vFramebuffers.resize(g_vVars.g_vImageViews.size());

		for (int ndx = 0; ndx < g_vVars.g_vImageViews.size(); ++ndx) {
			VkFramebufferCreateInfo fciFramebufferInfo = {
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.renderPass = g_vVars.g_rpRenderPass,
				.attachmentCount = 1,
				.pAttachments = &g_vVars.g_vImageViews[ndx],
				.width = g_vVars.g_eExtent.width,
				.height = g_vVars.g_eExtent.height,
				.layers = 1
			};

			if (vkCreateFramebuffer(g_vVars.g_dDeviceHandle, &fciFramebufferInfo, nullptr, &g_vVars.g_vFramebuffers[ndx]) != VK_SUCCESS) {
				throw std::runtime_error("ERROR: Failed to create framebuffers!");
			}
		}
	}

	void CreateCommandPool() {
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

	void CreateCommandBuffer() {
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

	void CreateSyncObjects() {
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

	void RecordCommandBuffer(VkCommandBuffer _cbBuffer, uint32_t _u32ImageIndex) {
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
			.clearValueCount = 1,
			.pClearValues = &g_vVars.g_cvClearColor
		};

		vkCmdBeginRenderPass(_cbBuffer, &rpbiBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(_cbBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, g_vVars.g_pPipeline);

		VkViewport vViewport = {
			.x = 0.0f,
			.y = 0.0f,
			.width = static_cast<float>(g_vVars.g_eExtent.width),
			.height = static_cast<float>(g_vVars.g_eExtent.height),
			.minDepth = 0.0f,
			.maxDepth = 1.0f
		};

		vkCmdSetViewport(_cbBuffer, 0, 1, &vViewport);

		VkRect2D rScissor = {
			.offset = { 0, 0 },
			.extent = g_vVars.g_eExtent
		};

		vkCmdSetScissor(_cbBuffer, 0, 1, &rScissor);

		vkCmdDraw(_cbBuffer, 3, 1, 0, 0); //SERIOUSLY ! ! ! THIS SHIT IS TEMPORARY ! ! !

		vkCmdEndRenderPass(_cbBuffer);

		if (vkEndCommandBuffer(_cbBuffer) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to record command buffer!");
		}
	}

	void CleanupSwapchain() {
		for (auto aFramebuffer : g_vVars.g_vFramebuffers) {
			vkDestroyFramebuffer(g_vVars.g_dDeviceHandle, aFramebuffer, nullptr);
		}

		for (auto aView : g_vVars.g_vImageViews) {
			vkDestroyImageView(g_vVars.g_dDeviceHandle, aView, nullptr);
		}

		vkDestroySwapchainKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, nullptr);
	}

	void RecreateSwapchain() {
		vkDeviceWaitIdle(g_vVars.g_dDeviceHandle);

		CreateSwapChain();

		CreateImageViews();

		CreateFramebuffers();
	}

#pragma region HelperFunctions
	void ValidateSupportedLayers() {
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

	bool ValidateSupportedDeviceExtensions(VkPhysicalDevice _pdDevice) {
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

	bool CheckDeviceSuitability(VkPhysicalDevice _pdDevice) {
		VkPhysicalDeviceProperties pdpProperties = {};
		vkGetPhysicalDeviceProperties(_pdDevice, &pdpProperties);

		VkQueueFamilyIndices qfiIndices = GetQueueFamilies(_pdDevice);

		bool bExtensionsSupported = ValidateSupportedDeviceExtensions(_pdDevice);

		bool bSwapChainAdequate = false;

		if (bExtensionsSupported) {
			VkSwapChainSupportDetails scsdSupport = QuerySwapChainSupport(_pdDevice);
			bSwapChainAdequate = !scsdSupport.m_vFormats.empty() && !scsdSupport.m_vPresentModes.empty();
		}
		
		return pdpProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && qfiIndices.IsComplete() && bExtensionsSupported && bSwapChainAdequate;
	}

	VkQueueFamilyIndices GetQueueFamilies(VkPhysicalDevice _pdDevice) {
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

	VkSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _pdDevice) {
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

	VkSurfaceFormatKHR SelectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _vAvailableFormats) {
		for (const auto& aAvailableFormat : _vAvailableFormats) {
			if (aAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && aAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return aAvailableFormat;
			}
		}

		return _vAvailableFormats[0];
	}

	VkPresentModeKHR SelectSwapPresentMode(const std::vector<VkPresentModeKHR>& _vAvailablePresentModes) {
		for (const auto& aAvailablePresentMode : _vAvailablePresentModes) {
			if (aAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return aAvailablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SelectSwapExtent(const VkSurfaceCapabilitiesKHR& _scCapabilities) {
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

	VkShaderModule CreateShaderModule(const std::vector<char>& _vCode) {
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
#pragma endregion

	void RenderFrame() {
		vkWaitForFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame], VK_TRUE, UINT64_MAX);

		vkResetFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame]);

		uint32_t u32ImageIndex = 0;
		VkResult rRes = vkAcquireNextImageKHR(g_vVars.g_dDeviceHandle, g_vVars.g_scSwapChain, UINT64_MAX, g_vVars.g_vImageAvailableSemaphores[g_vVars.g_u32CurrentFrame], VK_NULL_HANDLE, &u32ImageIndex);

		if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes != VK_SUBOPTIMAL_KHR) {
			RecreateSwapchain();
			return;
		}
		else if (rRes != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to acquire swapchain image!");
		}

		vkResetFences(g_vVars.g_dDeviceHandle, 1, &g_vVars.g_vInFlightFences[g_vVars.g_u32CurrentFrame]);

		vkResetCommandBuffer(g_vVars.g_vCommandBuffers[g_vVars.g_u32CurrentFrame], 0);

		RecordCommandBuffer(g_vVars.g_vCommandBuffers[g_vVars.g_u32CurrentFrame], u32ImageIndex);

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
			.pImageIndices = &u32ImageIndex,
			.pResults = nullptr
		};

		rRes = vkQueuePresentKHR(g_vVars.g_qPresentQueue, &piPresentInfo);

		if (rRes == VK_ERROR_OUT_OF_DATE_KHR || rRes != VK_SUBOPTIMAL_KHR) {
			RecreateSwapchain();
			return;
		}
		else if (rRes != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to present swapchain image!");
		}

		g_vVars.g_u32CurrentFrame = (g_vVars.g_u32CurrentFrame + 1) % HC_MAX_FRAMES_IN_FLIGHT;
	}

	void CleanupRenderer() {
		vkDeviceWaitIdle(g_vVars.g_dDeviceHandle);

		CleanupSwapchain();

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
}