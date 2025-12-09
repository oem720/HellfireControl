
#include <HellfireControl/Render/Renderer.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkRenderer.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>
#include <Platform/Vulkan/VkUtil.hpp>

void Renderer::VerifyRenderpassPipelineData() {
	//Verify that all pipelines are valid and gather the data necessary for descriptor creation and pipeline inputs.
	//We will eventually need a check to ensure that whatever is being accessed, such as the texture manager, does not get duplicated.
	//Future implementation will remove the ability to create descriptors for the texture system, opting instead to enforce the bindless design.


}

void Renderer::CreatePlatformRenderpass() {
	m_pPlatformRenderpass = std::make_unique<VkRenderer>();
}

void VkRenderer::Init(const RenderpassData& _rdRenderpass) {
	CreateRenderpass(_rdRenderpass);
	
	CreatePipelines(_rdRenderpass);
}

void VkRenderer::Render() {

}

void VkRenderer::Cleanup() {
	vkDestroyRenderPass(VkRenderManager::m_dDeviceHandle, m_rpRenderPass, nullptr);
}

void VkRenderer::CreateRenderpass(const RenderpassData& _rdRenderpass) {
	std::vector<VkAttachmentDescription> vAttachments;
	std::vector<VkSubpassDescription> vSubpasses;
	std::vector<VkSubpassDependency> vDependencies;

	for(const auto& aAttachment : _rdRenderpass.m_vAttachments) {
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

	for (const auto& aSubpass : _rdRenderpass.m_vSubpasses) {
		VkSubpassDescription sdSubpassDesc = {
			.flags = aSubpass.m_u32Flags,
			.pipelineBindPoint = static_cast<VkPipelineBindPoint>(aSubpass.m_pbpBindPoint),
			.inputAttachmentCount = static_cast<uint32_t>(aSubpass.m_vInputAttachments.size()),
			.pInputAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vInputAttachments.data()),
			.colorAttachmentCount = static_cast<uint32_t>(aSubpass.m_vColorAttachments.size()),
			.pColorAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vColorAttachments.data()),
			.pResolveAttachments = reinterpret_cast<const VkAttachmentReference*>(aSubpass.m_vResolveAttachments.data()),
			.pDepthStencilAttachment = reinterpret_cast<const VkAttachmentReference*>(&aSubpass.m_arDepthStencilAttachment),
			.preserveAttachmentCount = static_cast<uint32_t>(aSubpass.m_vPreserveAttachments.size()),
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
		.attachmentCount = static_cast<uint32_t>(vAttachments.size()),
		.pAttachments = vAttachments.data(),
		.subpassCount = static_cast<uint32_t>(vSubpasses.size()),
		.pSubpasses = vSubpasses.data(),
		.dependencyCount = static_cast<uint32_t>(vDependencies.size()),
		.pDependencies = vDependencies.data()
	};

	if(vkCreateRenderPass(VkRenderManager::m_dDeviceHandle, &rpciRenderPassInfo, nullptr, &m_rpRenderPass) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create render pass!");
	}
}

void VkRenderer::CreatePipelines(const RenderpassData& _rdRenderpass) {
	for (const auto& aSubpass : _rdRenderpass.m_vSubpasses) {
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
	return {};
}
#endif