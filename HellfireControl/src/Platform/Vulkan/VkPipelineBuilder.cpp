#include <Platform/Vulkan/VkPipelineBuilder.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>

VkPipelineLayout VkGraphicsPipelineLayoutBuilder::Build() {
	VkPipelineLayout plPipelineLayout = VK_NULL_HANDLE;

	VkPipelineLayoutCreateInfo plciPipelineLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.setLayoutCount = static_cast<uint32>(m_vDescriptorSetLayouts.size()),
		.pSetLayouts = m_vDescriptorSetLayouts.data(),
		.pushConstantRangeCount = static_cast<uint32>(m_vPushConstants.size()),
		.pPushConstantRanges = m_vPushConstants.data()
	};

	if (vkCreatePipelineLayout(VkRenderManager::m_dDeviceHandle, &plciPipelineLayoutInfo, nullptr, &plPipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout!");
	}

	Clear();

	return plPipelineLayout;
}

void VkGraphicsPipelineLayoutBuilder::Clear() {
	m_vDescriptorSetLayouts.clear();
	m_vPushConstants.clear();
}

VkGraphicsPipelineLayoutBuilder& VkGraphicsPipelineLayoutBuilder::SetDescriptorSetLayouts(const Array<VkDescriptorSetLayout>& _vDescriptorSetLayouts) {
	m_vDescriptorSetLayouts = _vDescriptorSetLayouts;

	return *this;
}

VkGraphicsPipelineLayoutBuilder& VkGraphicsPipelineLayoutBuilder::SetPushConstants(const ShaderPipelineData& _spdPipelineData) {
	Map<String, VkPushConstantRange> mPushConstantRangeNames;

	for (const auto& aShader : _spdPipelineData.m_vShaderStages) {
		auto aVars = aShader->GetShaderVars();
		for (const auto& aShaderVar : aVars) {
			if (aShaderVar.second.m_u16Type != VAR_PUSH_CONSTANT_BUFFER) {
				continue; //Only push constant buffers are relevant here.
			}

			if (mPushConstantRangeNames.find(aShaderVar.first) != mPushConstantRangeNames.end()) {
				mPushConstantRangeNames[aShaderVar.first].stageFlags |= aShader->GetShaderStageBit();
				continue;
			}

			mPushConstantRangeNames[aShaderVar.first] = {
				.stageFlags = static_cast<VkShaderStageFlags>(aShader->GetShaderStageBit()),
				.offset = aShaderVar.second.m_arrData[0],
				.size = aShaderVar.second.m_arrData[1]
			};
		}
	}

	for (const auto& aRangePair : mPushConstantRangeNames) {
		m_vPushConstants.push_back(aRangePair.second);
	}

	return *this;
}

VkPipeline VkGraphicsPipelineBuilder::Build() {
	VkPipeline pPipeline = VK_NULL_HANDLE;

	//TODO: Allow for base pipelines to be specified. At the moment, this is entirely unsupported behavior,
	//but is very useful for optimization, especially during shader compiles as we're actively rendering.
	//EDIT: Evaluate this TODO in the future to see if it's even necessary or worth it. It's possible
	//that it won't actually be feasible and won't actually provide any benefit, since the pipelines are
	//generally created before rendering starts, and with all the data provided to begin with.
	VkGraphicsPipelineCreateInfo gpciGraphicsPipelineInfo = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stageCount = static_cast<uint32>(m_vShaderStages.size()),
		.pStages = m_vShaderStages.data(),
		.pVertexInputState = m_pvisciVertexInputStateInfo.sType == 0 ? nullptr : &m_pvisciVertexInputStateInfo,
		.pInputAssemblyState = m_piasciInputAssemblyStateInfo.sType == 0 ? nullptr : &m_piasciInputAssemblyStateInfo,
		.pTessellationState = m_ptsciTessellationStateInfo.sType == 0 ? nullptr : &m_ptsciTessellationStateInfo,
		.pViewportState = m_pvsciViewportStateInfo.sType == 0 ? nullptr : &m_pvsciViewportStateInfo,
		.pRasterizationState = m_prsciRasterizationStateInfo.sType == 0 ? nullptr : &m_prsciRasterizationStateInfo,
		.pMultisampleState = m_pmsciMultisampleStateInfo.sType == 0 ? nullptr : &m_pmsciMultisampleStateInfo,
		.pDepthStencilState = m_pdssciDepthStencilStateInfo.sType == 0 ? nullptr : &m_pdssciDepthStencilStateInfo,
		.pColorBlendState = m_pcbsciColorBlendStateInfo.sType == 0 ? nullptr : &m_pcbsciColorBlendStateInfo,
		.pDynamicState = m_pdsciDynamicStateInfo.sType == 0 ? nullptr : &m_pdsciDynamicStateInfo,
		.layout = m_plPipelineLayout,
		.renderPass = m_rpRenderpass,
		.subpass = m_u32Subpass,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = 0
	};

	if (vkCreateGraphicsPipelines(VkRenderManager::m_dDeviceHandle, VK_NULL_HANDLE, 1, &gpciGraphicsPipelineInfo, nullptr, &pPipeline) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create graphics pipeline!");
	}

	Clear();

	return pPipeline;
}

void VkGraphicsPipelineBuilder::Clear() {
	m_vShaderStages.clear();

	m_pvisciVertexInputStateInfo = {};
	m_piasciInputAssemblyStateInfo = {};
	m_ptsciTessellationStateInfo = {};
	m_pdsciDynamicStateInfo = {};
	m_pvsciViewportStateInfo = {};
	m_prsciRasterizationStateInfo = {};
	m_pmsciMultisampleStateInfo = {};
	m_pdssciDepthStencilStateInfo = {};
	m_pcbsciColorBlendStateInfo = {};

	m_rpRenderpass = VK_NULL_HANDLE;
	m_plPipelineLayout = VK_NULL_HANDLE;

	m_u32Subpass = 0;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetRenderpass(VkRenderPass _rpRenderpass) {
	m_rpRenderpass = _rpRenderpass;

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetSubpass(uint32 _u32SubpassNdx) {
	m_u32Subpass = _u32SubpassNdx;

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetPipelineLayout(VkPipelineLayout _plPipelineLayout) {
	m_plPipelineLayout = _plPipelineLayout;

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetShaderStages(const Array<VkPipelineShaderStageCreateInfo>& _vShaderStages) {
	m_vShaderStages = _vShaderStages;

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetVertexInputState(const Array<VkVertexInputBindingDescription>& _vVertexBindings, const Array<VkVertexInputAttributeDescription>& _vVertexAttributes) {
	m_pvisciVertexInputStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.vertexBindingDescriptionCount = static_cast<uint32>(_vVertexBindings.size()),
		.pVertexBindingDescriptions = _vVertexBindings.data(),
		.vertexAttributeDescriptionCount = static_cast<uint32>(_vVertexAttributes.size()),
		.pVertexAttributeDescriptions = _vVertexAttributes.data()
	};
	
	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetInputAssemblyState(const ShaderPipelineData& _spdPipelineData) {
	m_piasciInputAssemblyStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.topology = static_cast<VkPrimitiveTopology>(_spdPipelineData.m_ptTopology),
		.primitiveRestartEnable = _spdPipelineData.m_bEnablePrimitiveRestart
	};
	
	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetTessellationState(const ShaderPipelineData& _spdPipelineData) {
	m_ptsciTessellationStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.patchControlPoints = _spdPipelineData.m_u32PatchControlPoints
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetDynamicState(const ShaderPipelineData& _spdPipelineData) {
	m_pdsciDynamicStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.dynamicStateCount = static_cast<uint32>(_spdPipelineData.m_vDynamicStates.size()),
		.pDynamicStates = reinterpret_cast<const VkDynamicState*>(_spdPipelineData.m_vDynamicStates.data())
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetViewportState(const ShaderPipelineData& _spdPipelineData) {
	uint32 u32ViewportMin = std::find(
		_spdPipelineData.m_vDynamicStates.begin(),
		_spdPipelineData.m_vDynamicStates.end(),
		DYNAMIC_STATE_VIEWPORT_WITH_COUNT
	) != _spdPipelineData.m_vDynamicStates.end() ? 0 : 1;

	uint32 u32ScissorMin = std::find(
		_spdPipelineData.m_vDynamicStates.begin(),
		_spdPipelineData.m_vDynamicStates.end(),
		DYNAMIC_STATE_SCISSOR_WITH_COUNT
	) != _spdPipelineData.m_vDynamicStates.end() ? 0 : 1;

	m_pvsciViewportStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.viewportCount = Math::Clamp(static_cast<uint32>(_spdPipelineData.m_vViewports.size()), u32ViewportMin, UINT32_MAX),
		.pViewports = reinterpret_cast<const VkViewport*>(_spdPipelineData.m_vViewports.data()),
		.scissorCount = Math::Clamp(static_cast<uint32>(_spdPipelineData.m_vScissors.size()), u32ScissorMin, UINT32_MAX),
		.pScissors = reinterpret_cast<const VkRect2D*>(_spdPipelineData.m_vScissors.data())
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetRasterizationState(const ShaderPipelineData& _spdPipelineData) {
	m_prsciRasterizationStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthClampEnable = _spdPipelineData.m_bEnableDepthClamp,
		.rasterizerDiscardEnable = _spdPipelineData.m_bEnableRasterizerDiscard,
		.polygonMode = static_cast<VkPolygonMode>(_spdPipelineData.m_pmPolygonMode),
		.cullMode = static_cast<VkCullModeFlags>(_spdPipelineData.m_cmCullMode),
		.frontFace = static_cast<VkFrontFace>(_spdPipelineData.m_woFrontFace),
		.depthBiasEnable = _spdPipelineData.m_bEnableDepthBias,
		.depthBiasClamp = _spdPipelineData.m_fDepthBiasClamp,
		.depthBiasSlopeFactor = _spdPipelineData.m_fDepthBiasSlopeFactor,
		.lineWidth = _spdPipelineData.m_fLineWidth
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetMultisampleState(const ShaderPipelineData& _spdPipelineData) {
	m_pmsciMultisampleStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.rasterizationSamples = static_cast<VkSampleCountFlagBits>(_spdPipelineData.m_u32SampleCount),
		.sampleShadingEnable = _spdPipelineData.m_bEnableSampleShading,
		.minSampleShading = _spdPipelineData.m_fMinSampleShading,
		.pSampleMask = _spdPipelineData.m_vSampleMasks.data(),
		.alphaToCoverageEnable = _spdPipelineData.m_bEnableAlphaToCoverage,
		.alphaToOneEnable = _spdPipelineData.m_bEnableAlphaToOne
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetDepthStencilState(const ShaderPipelineData& _spdPipelineData) {
	m_pdssciDepthStencilStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthTestEnable = _spdPipelineData.m_bEnableDepthTest,
		.depthWriteEnable = _spdPipelineData.m_bEnableDepthWrite,
		.depthCompareOp = static_cast<VkCompareOp>(_spdPipelineData.m_coDepthCompareOp),
		.depthBoundsTestEnable = _spdPipelineData.m_bEnableDepthBoundsTest,
		.stencilTestEnable = _spdPipelineData.m_bEnableStencilTest,
		.front = *reinterpret_cast<const VkStencilOpState*>(&_spdPipelineData.m_sosStencilFront),
		.back = *reinterpret_cast<const VkStencilOpState*>(&_spdPipelineData.m_sosStencilBack),
		.minDepthBounds = _spdPipelineData.m_fMinDepthBounds,
		.maxDepthBounds = _spdPipelineData.m_fMaxDepthBounds
	};

	return *this;
}

VkGraphicsPipelineBuilder& VkGraphicsPipelineBuilder::SetColorBlendState(const ShaderPipelineData& _spdPipelineData) {
	m_pcbsciColorBlendStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.logicOpEnable = _spdPipelineData.m_bEnableLogicOperator,
		.logicOp = static_cast<VkLogicOp>(_spdPipelineData.m_loLogicOp),
		.attachmentCount = static_cast<uint32>(_spdPipelineData.m_vBlendAttachments.size()),
		.pAttachments = reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(_spdPipelineData.m_vBlendAttachments.data()),
		.blendConstants = { _spdPipelineData.m_v4BlendConstants.x, _spdPipelineData.m_v4BlendConstants.y, _spdPipelineData.m_v4BlendConstants.z, _spdPipelineData.m_v4BlendConstants.w }
	};

	return *this;
}