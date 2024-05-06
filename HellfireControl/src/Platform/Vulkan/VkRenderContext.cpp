
#include <Platform/Vulkan/VkRenderContext.hpp>

#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkBuffer.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/File.hpp>
#include <HellfireControl/Render/RenderContext.hpp>

uint32_t PlatformRenderContext::m_u32ActiveRenderContext = 0;

std::map<uint32_t, PlatformRenderContext::VkRenderContextData> PlatformRenderContext::m_mContextMap = {};

void PlatformRenderContext::InitRenderContext(const RenderContext& _rcContext) {
	std::vector<VkShaderModule> vShaders;
	std::vector<VkPipelineShaderStageCreateInfo> vShaderInfos;

	if ((_rcContext.m_rcsfEnabledShaderStages & VK_SHADER_STAGE_COMPUTE_BIT) && (_rcContext.m_rcsfEnabledShaderStages & VK_SHADER_STAGE_ALL_GRAPHICS)) {
		throw std::runtime_error("ERROR: Attempted to initialize a compute shader on a graphics pipeline!");
	}

	for (uint32_t u32Flags = VK_SHADER_STAGE_VERTEX_BIT, ndx = 0; u32Flags < VK_SHADER_STAGE_ALL && ndx < _rcContext.m_vShaderFileNames.size(); u32Flags <<= 1) {
		if (_rcContext.m_rcsfEnabledShaderStages & u32Flags) {
			auto aShaderCode = Util::ReadFile(_rcContext.m_vShaderFileNames[ndx++]); //Temporary load code

			vShaders.push_back(VkUtil::CreateShaderModule(aShaderCode)); //Add our shader to the module list

			vShaderInfos.push_back(
				VkPipelineShaderStageCreateInfo { //Add our shader stage info to the vector
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, //Much of this is temporary, as we will be adding much of the metadata to
					.pNext = nullptr,											  //the shader asset file.
					.flags = 0,
					.stage = static_cast<VkShaderStageFlagBits>(u32Flags),
					.module = vShaders.back(),
					.pName = "main",
					.pSpecializationInfo = nullptr
				}
			);
		}
	}

	VkRenderContextData rcdData = {};

	CreateDescriptorData(rcdData);

	if (_rcContext.m_rcsfEnabledShaderStages & VK_SHADER_STAGE_COMPUTE_BIT) {
		//TODO: Compute pipeline here.
	}
	else {
		VkVertexData vdData = GetVertexAttributesFromType(_rcContext.m_rcvtVertexType);

		VkPipelineVertexInputStateCreateInfo pvisciVertexInputInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.vertexBindingDescriptionCount = 1,
			.pVertexBindingDescriptions = &vdData.m_vibdBindingDescription,
			.vertexAttributeDescriptionCount = static_cast<uint32_t>(vdData.m_vAttributes.size()),
			.pVertexAttributeDescriptions = vdData.m_vAttributes.data()
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

		VkPipelineLayoutCreateInfo plciLayoutInfo = { //Obviously, this is a temporary copy-paste from existing code.
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, //The idea is to have descriptor sets created per context as needed.
			.pNext = nullptr,										//Push constants will follow the same principle, and all will be stored in the .ini file.
			.flags = 0,
			.setLayoutCount = 1,
			.pSetLayouts = &rcdData.m_ddDescriptorData.m_dslDescriptorSetLayout,
			.pushConstantRangeCount = 0,
			.pPushConstantRanges = nullptr
		};

		if (vkCreatePipelineLayout(PlatformRenderer::m_dDeviceHandle, &plciLayoutInfo, nullptr, &rcdData.m_plPipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create pipeline layout for the context: " + std::to_string(_rcContext.m_rctContextType) + "!");
		}

		VkGraphicsPipelineCreateInfo gpciGraphicsPipelineInfo = {
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stageCount = static_cast<uint32_t>(vShaderInfos.size()),
			.pStages = vShaderInfos.data(),
			.pVertexInputState = &pvisciVertexInputInfo,
			.pInputAssemblyState = &piasciInputAssemblyInfo,
			.pTessellationState = nullptr, //Tessellation state MAY be needed, but for now, it will remain null.
			.pViewportState = &pvsciViewportStateInfo,
			.pRasterizationState = &prsciRasterizerInfo,
			.pMultisampleState = &pmsciMultisampleStateInfo,
			.pDepthStencilState = &pdssciDepthStencilStateInfo,
			.pColorBlendState = &pcbsciColorBlendStateInfo,
			.pDynamicState = &pdsciDynamicStateInfo,
			.layout = rcdData.m_plPipelineLayout,
			.renderPass = PlatformRenderer::m_rpRenderPass,
			.subpass = 0,
			.basePipelineHandle = VK_NULL_HANDLE,
			.basePipelineIndex = 0
		};

		if (vkCreateGraphicsPipelines(PlatformRenderer::m_dDeviceHandle, VK_NULL_HANDLE, 1, &gpciGraphicsPipelineInfo, nullptr, &rcdData.m_pPipeline) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create the graphics pipeline for the context: " + std::to_string(_rcContext.m_rctContextType) + "!");
		}
	}

	for (auto& aShader : vShaders) {
		vkDestroyShaderModule(PlatformRenderer::m_dDeviceHandle, aShader, nullptr); //Cleanup shader data
	}

	m_mContextMap[_rcContext.m_u32ContextID] = rcdData; //Add the new render context to the map.
}

void PlatformRenderContext::CleanupRenderContext(uint32_t _u32ContextID) {
	m_mContextMap[_u32ContextID].Destroy();

	m_mContextMap.erase(_u32ContextID); //Remove from the map after free.
}

void PlatformRenderContext::CreateDescriptorData(VkRenderContextData& _rcdContext) {
	//TODO For now all descriptor set data is hard coded from what the demo needs. Future implementation requires that shaders be
	//analyzed for the proper descriptors and the descriptor sets be built accordingly.

	//Descriptor Layout
	{
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

		if (vkCreateDescriptorSetLayout(PlatformRenderer::m_dDeviceHandle, &dslciDescriptorLayoutInfo, nullptr, &_rcdContext.m_ddDescriptorData.m_dslDescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create descriptor set layout!");
		}
	}

	//Descriptor Pool
	{
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

		if (vkCreateDescriptorPool(PlatformRenderer::m_dDeviceHandle, &dpciPoolInfo, nullptr, &_rcdContext.m_ddDescriptorData.m_dpDescriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("ERROR: Failed to create Descriptor Pool!");
		}
	}
}

void PlatformRenderContext::TempInitDescriptors(uint32_t _u32BufferID, VkRenderContextData& _rcdData) {
	std::vector<VkDescriptorSetLayout> vLayouts(HC_MAX_FRAMES_IN_FLIGHT, _rcdData.m_ddDescriptorData.m_dslDescriptorSetLayout); //Blech, fuck you Vulkan
	_rcdData.m_ddDescriptorData.m_vDescriptorSets.resize(HC_MAX_FRAMES_IN_FLIGHT);

	VkDescriptorSetAllocateInfo dsaiAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pNext = nullptr,
		.descriptorPool = _rcdData.m_ddDescriptorData.m_dpDescriptorPool,
		.descriptorSetCount = static_cast<uint32_t>(HC_MAX_FRAMES_IN_FLIGHT),
		.pSetLayouts = vLayouts.data()
	};

	if (vkAllocateDescriptorSets(PlatformRenderer::m_dDeviceHandle, &dsaiAllocateInfo, _rcdData.m_ddDescriptorData.m_vDescriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("ERROR: Failed to allocate Descriptor Sets!");
	}

	for (int ndx = 0; ndx < HC_MAX_FRAMES_IN_FLIGHT; ++ndx) {
		VkDescriptorBufferInfo dbiBufferInfo = {
			.buffer = _rcdData.m_vContextBuffers[_u32BufferID].m_vBuffers[ndx],
			.offset = 0,
			.range = PlatformBuffer::g_blData.g_mBufferDataTable[_rcdData.m_vContextBuffers[_u32BufferID].m_vBuffers[0]].m_u32ItemWidth
		};

		VkDescriptorImageInfo dbiImageInfo = {
			.sampler = PlatformRenderer::m_sSampler,
			.imageView = PlatformRenderer::ivTextureView,
			.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		};

		std::array<VkWriteDescriptorSet, 2> arrDescWrite = {
			VkWriteDescriptorSet {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = _rcdData.m_ddDescriptorData.m_vDescriptorSets[ndx],
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
				.dstSet = _rcdData.m_ddDescriptorData.m_vDescriptorSets[ndx],
				.dstBinding = 1,
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.pImageInfo = &dbiImageInfo,
				.pBufferInfo = nullptr,
				.pTexelBufferView = nullptr
			}
		};

		vkUpdateDescriptorSets(PlatformRenderer::m_dDeviceHandle, static_cast<uint32_t>(arrDescWrite.size()), arrDescWrite.data(), 0, nullptr);
	}
}

void PlatformRenderContext::CleanupAllContextData() {
	for (auto& aContextData : m_mContextMap) {
		aContextData.second.Destroy();
	}

	m_mContextMap.clear();
}

VkVertexData PlatformRenderContext::GetVertexAttributesFromType(uint8_t _u8VertexType) {
	switch (_u8VertexType) {
	case CONTEXT_VERTEX_TYPE_3D: {
		return VkVertexData{
			.m_vibdBindingDescription = VertexSimple::GetBindingDescription(),
			.m_vAttributes = VertexSimple::GetAttributeDescriptions()
		};
	} break;
	}

	throw std::runtime_error("ERROR: Attempted to get vertex metadata for a type that doesn't exist/is unsupported!");
}