
#include <HellfireControl/Render/Renderer.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkShader.hpp>
#include <Platform/Vulkan/VkPipelineBuilder.hpp>
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
	for (uint32 u32Ndx = 0; u32Ndx < m_rdRenderpassData.m_vSubpasses.size(); ++u32Ndx) {
		for (const auto& aShaderPipeline : m_rdRenderpassData.m_vSubpasses[u32Ndx].m_vShaderPipelines) {
			VkRenderPipelineData rpdPipelineData = {};

			switch (aShaderPipeline.m_ptPipelineType) {
			case PIPELINE_TYPE_GRAPHICS:
				rpdPipelineData = CreateGraphicsPipeline(u32Ndx, aShaderPipeline);
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

VkRenderPipelineData VkRenderer::CreateGraphicsPipeline(uint32 _u32Subpass, const ShaderPipelineData& _spdPipelineData) {
	VkGraphicsPipelineLayoutBuilder plbBuilder;
	VkGraphicsPipelineBuilder pbBuilder;

	Array<VkPipelineShaderStageCreateInfo> vShaderStages = CreateShaderStages(_spdPipelineData);
	Array<VkDescriptorSetLayout> vDescriptorSetLayouts = CreateDescriptorSetLayouts(_spdPipelineData);
	
	VkPipelineLayout plPipelineLayout = plbBuilder
		.SetDescriptorSetLayouts(vDescriptorSetLayouts)
		.SetPushConstants(_spdPipelineData)
		.Build();

	plbBuilder.Clear();

	//TODO: Properly handle this such that it doesn't risk attempting to dereference a null pointer, as will happen
	//with task/mesh shader pipelines. It should also gracefully fail should a vertex shader not be provided.
	Shared<VkShader> pVertexShader = std::dynamic_pointer_cast<VkShader>(
		(*std::find_if(
			_spdPipelineData.m_vShaderStages.begin(),
			_spdPipelineData.m_vShaderStages.end(),
			[](const Shared<Shader>& _sShader) { return (_sShader->GetShaderStageBit() == SHADER_STAGE_VERTEX_BIT); }
		))
		->GetPlatformShader()
	);

	VkPipeline pPipeline = pbBuilder
		.SetRenderpass(m_rpRenderpass)
		.SetSubpass(_u32Subpass)
		.SetPipelineLayout(plPipelineLayout)
		.SetVertexInputState(pVertexShader->GetVertexInputBindings(), pVertexShader->GetVertexInputAttributes())
		.SetInputAssemblyState(_spdPipelineData)
		.SetTessellationState(_spdPipelineData)
		.SetDynamicState(_spdPipelineData)
		.SetViewportState(_spdPipelineData)
		.SetRasterizationState(_spdPipelineData)
		.SetMultisampleState(_spdPipelineData)
		.SetDepthStencilState(_spdPipelineData)
		.SetColorBlendState(_spdPipelineData)
		.Build();

	pbBuilder.Clear();

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
#endif