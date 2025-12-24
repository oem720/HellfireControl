
#include <HellfireControl/Render/Renderer.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkShader.hpp>
#include <Platform/Vulkan/VkUtil.hpp>

Map<HCShaderVarType, VkDescriptorType> VkRenderer::m_mShaderVarTranslationTable = {
	{VAR_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER},
	{VAR_STORAGE_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER},
	{VAR_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER},
	{VAR_TEXTURE_2D, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE},
	{VAR_IMAGE_2D, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE},
	{VAR_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLER},
	{VAR_UNIFORM_TEXEL_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER},
	{VAR_STORAGE_TEXEL_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER},
	{VAR_SUBPASS_INPUT, VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT},
	{VAR_ACCELERATION_STRUCTURE, VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR},
	{VAR_SHADER_RECORD_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER},
	{VAR_ATOMIC_COUNTER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER}
};

void Renderer::CreatePlatformRenderpass(const RenderpassData& _rdRenderpass) {
	m_pPlatformRenderer = std::make_shared<VkRenderer>(_rdRenderpass);
}

void VkRenderer::Init() {
	for(auto& aSubpass : m_rdRenderpassData.m_vSubpasses) {
		for (auto& aPipeline : aSubpass.m_vShaderPipelines) {
			for (auto& aShader : aPipeline.m_vShaderStages) {
				aShader->Init(); //Start every shader.
			}
		}
	}

	CreateRenderpass();
	
	CreatePipelines();
}

void VkRenderer::Render() {

}

void VkRenderer::Cleanup() {
	vkDestroyRenderPass(VkRenderManager::m_dDeviceHandle, m_rpRenderpass, nullptr);
}

void VkRenderer::VerifyRenderpassPipelineData() {
	for (const auto& aSubpass : m_rdRenderpassData.m_vSubpasses) {
		for (const auto& aPipeline : aSubpass.m_vShaderPipelines) {
			uint16 u16PipelineMask = 0;
			for (const auto& aShader : aPipeline.m_vShaderStages) {
				u16PipelineMask |= aShader->GetShaderStageBit();
			}

			switch (aPipeline.m_ptPipelineType) {
			case PIPELINE_TYPE_GRAPHICS:
				if (!((u16PipelineMask >= SHADER_STAGE_GRAPHICS_MIN && u16PipelineMask <= SHADER_STAGE_GRAPHICS_MAX) ||
					(u16PipelineMask >= SHADER_STAGE_TASK_MIN && u16PipelineMask <= SHADER_STAGE_TASK_MAX))) {
					throw std::runtime_error("Pipeline validation error: Invalid stages or configuration present in a graphics pipeline!");
				}

				if (u16PipelineMask & SHADER_STAGE_VERTEX_BIT && aPipeline.m_vShaderStages.size() > 5) {
					throw std::runtime_error("Pipeline validation error: Graphics pipelines with vertex shaders cannot be longer than 5 stages!");
				}
				else if (u16PipelineMask & SHADER_STAGE_TASK_BIT && aPipeline.m_vShaderStages.size() > 3) {
					throw std::runtime_error("Pipeline validation error: Graphics pipelines with task shaders cannot be longer than 3 stages!");
				}
				break;
			case PIPELINE_TYPE_COMPUTE:
				if (u16PipelineMask != SHADER_STAGE_COMPUTE_BIT) {
					throw std::runtime_error("Pipeline validation error: Any stage other than a compute shader in a compute pipeline is invalid!");
				}

				if (aPipeline.m_vShaderStages.size() > 1) {
					throw std::runtime_error("Pipeline validation error: Compute pipelines cannot have more than 1 stage!");
				}
				break;
			case PIPELINE_TYPE_RAY_TRACING:
				if (!(u16PipelineMask >= SHADER_STAGE_RAY_TRACING_MIN && u16PipelineMask <= SHADER_STAGE_RAY_TRACING_MAX)) {
					throw std::runtime_error("Pipeline validation error: Invalid stages or configuration present in a ray tracing pipeline!");
				}

				if (aPipeline.m_vShaderStages.size() > 6) {
					throw std::runtime_error("Pipeline validation error: Ray tracing pipelines cannot have more than 6 stages!");
				}
				break;
			}
		}
	}
}

Array<VkDescriptorType> VkRenderer::GetDescriptorCounts() const {
	//Gather the data necessary for descriptor creation.
	//We will eventually need a check to ensure that whatever is being accessed, such as the texture manager, does not get duplicated.
	//Future implementation will remove the ability to create descriptors for the texture system, opting instead to enforce the bindless design.
	Array<VkDescriptorType> vDescriptors;

	for (const auto& aSubpass : m_rdRenderpassData.m_vSubpasses) {
		for (const auto& aPipeline : aSubpass.m_vShaderPipelines) {
			for (const auto& aShader : aPipeline.m_vShaderStages) {
				auto aVars = aShader->GetShaderVars();
				for (const auto& aShaderVar : aVars) {
					if (aShaderVar.second.m_u16Type == VAR_STAGE_INPUT ||
						aShaderVar.second.m_u16Type == VAR_STAGE_OUTPUT ||
						aShaderVar.second.m_u16Type == VAR_BUILTIN_STAGE_INPUT ||
						aShaderVar.second.m_u16Type == VAR_BUILTIN_STAGE_OUTPUT ||
						aShaderVar.second.m_u16Type == VAR_PUSH_CONSTANT_BUFFER ||
						aShaderVar.second.m_u16Type == VAR_GL_PLAIN_UNIFORM) {
						continue; //None of these vars generate descriptors
					}

					//TODO: fix this such that dynamic ubo/ssbo objects are distinguished from non-dynamic counterparts.
					vDescriptors.push_back(m_mShaderVarTranslationTable[static_cast<HCShaderVarType>(aShaderVar.second.m_u16Type)]);
				}
			}
		}
	}

	return vDescriptors;
}

void VkRenderer::CreateRenderpass() {
	Array<VkAttachmentDescription> vAttachments;
	Array<VkSubpassDescription> vSubpasses;
	Array<VkSubpassDependency> vDependencies;

	for(const auto& aAttachment : m_rdRenderpassData.m_vAttachments) {
		VkFormat fFormat = aAttachment.m_ifFormat >= 0
			? static_cast<VkFormat>(aAttachment.m_ifFormat)
			: (aAttachment.m_ifFormat == FORMAT_SWAPCHAIN_DETERMINED 
				? VkRenderManager::m_fFormat 
				: VkUtil::FindDepthFormat(VkRenderManager::m_pdPhysicalDevice));

		VkAttachmentDescription adAttachmentDesc = {
			.flags = 0,
			.format = fFormat,
			.samples = static_cast<VkSampleCountFlagBits>(aAttachment.m_u32SampleCount),
			.loadOp = static_cast<VkAttachmentLoadOp>(aAttachment.m_aloLoadOp),
			.storeOp = static_cast<VkAttachmentStoreOp>(aAttachment.m_asoStoreOp),
			.stencilLoadOp = static_cast<VkAttachmentLoadOp>(aAttachment.m_aloStencilLoadOp),
			.stencilStoreOp = static_cast<VkAttachmentStoreOp>(aAttachment.m_asoStencilStoreOp),
			.initialLayout = static_cast<VkImageLayout>(aAttachment.m_ilInitialLayout),
			.finalLayout = static_cast<VkImageLayout>(aAttachment.m_ilFinalLayout),
		};

		vAttachments.push_back(adAttachmentDesc);
	}

	for (const auto& aSubpass : m_rdRenderpassData.m_vSubpasses) {
		VkSubpassDescription sdSubpassDesc = {
			.flags = aSubpass.m_u32Flags,
			.pipelineBindPoint = static_cast<VkPipelineBindPoint>(aSubpass.m_pbpBindPoint),
			.inputAttachmentCount = static_cast<uint32>(aSubpass.m_vInputAttachments.size()),
			.pInputAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vInputAttachments.data()),
			.colorAttachmentCount = static_cast<uint32>(aSubpass.m_vColorAttachments.size()),
			.pColorAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vColorAttachments.data()),
			.pResolveAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vResolveAttachments.data()),
			.pDepthStencilAttachment = reinterpret_cast<const VkAttachmentReference*>(&aSubpass.m_arDepthStencilAttachment),
			.preserveAttachmentCount = static_cast<uint32>(aSubpass.m_vPreserveAttachments.size()),
			.pPreserveAttachments = aSubpass.m_vPreserveAttachments.data()
		};

		vSubpasses.push_back(sdSubpassDesc);

		for (const auto& aDependency : aSubpass.m_vDependencies) {
			VkSubpassDependency sdDependency = {
				.srcSubpass = aDependency.m_u32SrcSubpass,
				.dstSubpass = aDependency.m_u32DstSubpass,
				.srcStageMask = aDependency.m_u32SrcStageMask,
				.dstStageMask = aDependency.m_u32DstStageMask,
				.srcAccessMask = aDependency.m_u32SrcAccessMask,
				.dstAccessMask = aDependency.m_u32DstAccessMask,
				.dependencyFlags = aDependency.m_u32DependencyFlags
			};

			vDependencies.push_back(sdDependency);
		}
	}

	VkRenderPassCreateInfo rpciRenderPassInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.attachmentCount = static_cast<uint32>(vAttachments.size()),
		.pAttachments = vAttachments.data(),
		.subpassCount = static_cast<uint32>(vSubpasses.size()),
		.pSubpasses = vSubpasses.data(),
		.dependencyCount = static_cast<uint32>(vDependencies.size()),
		.pDependencies = vDependencies.data()
	};

	if(vkCreateRenderPass(VkRenderManager::m_dDeviceHandle, &rpciRenderPassInfo, nullptr, &m_rpRenderpass) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create render pass!");
	}
}

void VkRenderer::CreatePipelines() {
	for (const auto& aSubpass : m_rdRenderpassData.m_vSubpasses) {
		for (const auto& aShaderPipeline : aSubpass.m_vShaderPipelines) {
			VkRenderPipelineData rpdPipelineData = {};

			switch (aShaderPipeline.m_ptPipelineType) {
			case PIPELINE_TYPE_GRAPHICS:
				rpdPipelineData = CreateGraphicsPipeline(aShaderPipeline);
				break;
			case PIPELINE_TYPE_COMPUTE:
				rpdPipelineData = CreateComputePipeline(aShaderPipeline);
				break;
			case PIPELINE_TYPE_RAY_TRACING:
				rpdPipelineData = CreateRaytracingPipeline(aShaderPipeline);
				break;
			}

			m_vPipelines.push_back(rpdPipelineData);
		}
	}
}

VkRenderPipelineData VkRenderer::CreateGraphicsPipeline(const ShaderPipelineData& _spdPipelineData) {
	Array<VkPipelineShaderStageCreateInfo> vShaderStages = CreateShaderStages(_spdPipelineData);
	Array<VkDescriptorSetLayout> vDescriptorSetLayouts = CreateDescriptorSetLayouts(_spdPipelineData);
	Array<VkPushConstantRange> vPushConstantRanges = CreatePushConstantRanges(_spdPipelineData);
	
	VkPipelineLayout plPipelineLayout = VK_NULL_HANDLE;
	VkPipeline pPipeline = VK_NULL_HANDLE;

	Shared<VkShader> pVertexShader = std::dynamic_pointer_cast<VkShader>(
		(*std::find_if(
			_spdPipelineData.m_vShaderStages.begin(), 
			_spdPipelineData.m_vShaderStages.end(),
			[](const Shared<Shader>& _sShader) { return (_sShader->GetShaderStageBit() == SHADER_STAGE_VERTEX_BIT); }
		))
		->GetPlatformShader()
	);

	//TODO: Handle Task/Mesh shaders, which do not use this structure at all.
	VkPipelineVertexInputStateCreateInfo pvisciVertexInputInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.vertexBindingDescriptionCount = static_cast<uint32>(pVertexShader->GetVertexInputBindings().size()),
		.pVertexBindingDescriptions = pVertexShader->GetVertexInputBindings().data(),
		.vertexAttributeDescriptionCount = static_cast<uint32>(pVertexShader->GetVertexInputAttributes().size()),
		.pVertexAttributeDescriptions = pVertexShader->GetVertexInputAttributes().data()
	};

	VkPipelineInputAssemblyStateCreateInfo piasciInputAssemblyInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.topology = static_cast<VkPrimitiveTopology>(_spdPipelineData.m_ptTopology),
		.primitiveRestartEnable = VK_FALSE //TODO: Make configurable
	};

	VkPipelineDynamicStateCreateInfo pdsciDynamicStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.dynamicStateCount = static_cast<uint32>(_spdPipelineData.m_vDynamicStates.size()),
		.pDynamicStates = reinterpret_cast<const VkDynamicState*>(_spdPipelineData.m_vDynamicStates.data())
	};

	//TODO: Add to the pipeline data struct so that it can be configured. (Given that dynamic state is set by the current test case,
	//this is not urgent, but it will need to be addressed in the future).
	VkPipelineViewportStateCreateInfo pvsiViewportStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.viewportCount = 1,
		.pViewports = nullptr,
		.scissorCount = 1,
		.pScissors = nullptr
	};

	//TODO: Add the hardcoded values here to the pipeline struct for future configuration. From what I can gather from the documentation
	//most of those values are depcrecated, so it may not be necessary anyway, but doing so for completion sake is important for a complete design.
	VkPipelineRasterizationStateCreateInfo prsciRasterizationInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = static_cast<VkPolygonMode>(_spdPipelineData.m_pmPolygonMode),
		.cullMode = static_cast<VkCullModeFlags>(_spdPipelineData.m_cmCullMode),
		.frontFace = static_cast<VkFrontFace>(_spdPipelineData.m_woFrontFace),
		.depthBiasEnable = VK_FALSE,
		.depthBiasClamp = 0.0f,
		.depthBiasSlopeFactor = 0.0f,
		.lineWidth = 1.0f
	};

	//TODO: As before, the hard coded values here need to be added to the pipeline struct for future configuration.
	VkPipelineMultisampleStateCreateInfo pmsciMultisampleInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.rasterizationSamples = static_cast<VkSampleCountFlagBits>(_spdPipelineData.m_u32SampleCount),
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 1.0f,
		.pSampleMask = nullptr,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE
	};

	//TODO: More hardcoded values to fix.
	VkPipelineDepthStencilStateCreateInfo pdssciDepthStencilStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.depthTestEnable = _spdPipelineData.m_bEnableDepthTest,
		.depthWriteEnable = _spdPipelineData.m_bEnableDepthWrite,
		.depthCompareOp = static_cast<VkCompareOp>(_spdPipelineData.m_coDepthCompareOp),
		.depthBoundsTestEnable = VK_FALSE,
		.stencilTestEnable = _spdPipelineData.m_bEnableStencilTest,
		.front = *reinterpret_cast<const VkStencilOpState*>(&_spdPipelineData.m_sosStencilFront),
		.back = *reinterpret_cast<const VkStencilOpState*>(&_spdPipelineData.m_sosStencilBack),
		.minDepthBounds = 1.0f,
		.maxDepthBounds = 0.0f
	};

	//TODO: Yet more missed hardcoded values!
	VkPipelineColorBlendStateCreateInfo pcbsciColorBlendStateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = static_cast<uint32>(_spdPipelineData.m_vBlendAttachments.size()),
		.pAttachments = reinterpret_cast<const VkPipelineColorBlendAttachmentState*>(_spdPipelineData.m_vBlendAttachments.data()),
		.blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
	};

	VkPipelineLayoutCreateInfo plciPipelineLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.setLayoutCount = static_cast<uint32>(vDescriptorSetLayouts.size()),
		.pSetLayouts = vDescriptorSetLayouts.data(),
		.pushConstantRangeCount = static_cast<uint32>(vPushConstantRanges.size()),
		.pPushConstantRanges = vPushConstantRanges.data()
	};

	if (vkCreatePipelineLayout(VkRenderManager::m_dDeviceHandle, &plciPipelineLayoutInfo, nullptr, &plPipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo gpciGraphicsPipelineInfo = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stageCount = static_cast<uint32>(vShaderStages.size()),
		.pStages = vShaderStages.data(),
		.pVertexInputState = &pvisciVertexInputInfo,
		.pInputAssemblyState = &piasciInputAssemblyInfo,
		.pTessellationState = nullptr, //TODO: Add tessellation support
		.pViewportState = &pvsiViewportStateInfo,
		.pRasterizationState = &prsciRasterizationInfo,
		.pMultisampleState = &pmsciMultisampleInfo,
		.pDepthStencilState = &pdssciDepthStencilStateInfo,
		.pColorBlendState = &pcbsciColorBlendStateInfo,
		.pDynamicState = &pdsciDynamicStateInfo,
		.layout = plPipelineLayout,
		.renderPass = m_rpRenderpass,
		.subpass = 0, //TODO: Fix this to actually use the correct renderpass index.
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = 0
	};

	if(vkCreateGraphicsPipelines(VkRenderManager::m_dDeviceHandle, VK_NULL_HANDLE, 1, &gpciGraphicsPipelineInfo, nullptr, &pPipeline) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create graphics pipeline!");
	}

	return VkRenderPipelineData {
		.m_plPipelineLayout = plPipelineLayout,
		.m_pPipeline = pPipeline,
		.m_vDescriptorSetLayouts = vDescriptorSetLayouts
	};
}

VkRenderPipelineData VkRenderer::CreateComputePipeline(const ShaderPipelineData& _spdPipelineData) {
	return VkRenderPipelineData();
}

VkRenderPipelineData VkRenderer::CreateRaytracingPipeline(const ShaderPipelineData& _spdPipelineData) {
	return VkRenderPipelineData();
}

Array<VkPipelineShaderStageCreateInfo> VkRenderer::CreateShaderStages(const ShaderPipelineData& _spdPipelineData) {
	Array<VkPipelineShaderStageCreateInfo> vShaderStages;

	for(const auto& aShader : _spdPipelineData.m_vShaderStages) {
		Shared<VkShader> pVkShader = std::dynamic_pointer_cast<VkShader>(aShader->GetPlatformShader());

		VkPipelineShaderStageCreateInfo pssciShaderStageInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.stage = static_cast<VkShaderStageFlagBits>(aShader->GetShaderStageBit()),
			.module = pVkShader->GetShaderModule(),
			.pName = "main", //TODO: Make shader entry point and specialization info configurable.
			.pSpecializationInfo = nullptr
		};

		vShaderStages.push_back(pssciShaderStageInfo);
	}

	return vShaderStages;
}

Array<VkDescriptorSetLayout> VkRenderer::CreateDescriptorSetLayouts(const ShaderPipelineData& _spdPipelineData) {
	Array<VkDescriptorSetLayout> vDescriptorSetLayouts;

	Map<uint32, VkDescriptorSetLayoutBuilder> mSetBindings;
	for(const auto& aShader : _spdPipelineData.m_vShaderStages) {
		auto aVars = aShader->GetShaderVars();

		for (const auto& aShaderVar : aVars) {
			if (aShaderVar.second.m_u16Type == VAR_STAGE_INPUT ||
				aShaderVar.second.m_u16Type == VAR_STAGE_OUTPUT ||
				aShaderVar.second.m_u16Type == VAR_BUILTIN_STAGE_INPUT ||
				aShaderVar.second.m_u16Type == VAR_BUILTIN_STAGE_OUTPUT ||
				aShaderVar.second.m_u16Type == VAR_PUSH_CONSTANT_BUFFER ||
				aShaderVar.second.m_u16Type == VAR_GL_PLAIN_UNIFORM) {
				continue; //None of these vars generate descriptors
			}

			mSetBindings[aShaderVar.second.m_arrData[1]].AddBinding(aShaderVar.second, static_cast<VkShaderStageFlagBits>(aShader->GetShaderStageBit()));
		}
	}

	for (auto& aSetBindingsPair : mSetBindings) {
		vDescriptorSetLayouts.push_back(aSetBindingsPair.second.Build(VkRenderManager::m_dDeviceHandle));
	}

	return vDescriptorSetLayouts;
}

Array<VkPushConstantRange> VkRenderer::CreatePushConstantRanges(const ShaderPipelineData& _spdPipelineData) {
	Map<String, VkPushConstantRange> mPushConstantRangeNames;

	for(const auto& aShader : _spdPipelineData.m_vShaderStages) {
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

	Array<VkPushConstantRange> vPushConstantRanges;

	for(const auto& aRangePair : mPushConstantRangeNames) {
		vPushConstantRanges.push_back(aRangePair.second);
	}

	return vPushConstantRanges;
}
#endif