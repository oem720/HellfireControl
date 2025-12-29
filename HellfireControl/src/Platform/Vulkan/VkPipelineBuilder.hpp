#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Render/RendererStructs.hpp>

class VkGraphicsPipelineLayoutBuilder {
private:
	Array<VkDescriptorSetLayout> m_vDescriptorSetLayouts;
	Array<VkPushConstantRange> m_vPushConstants;

public:
	VkPipelineLayout Build();
	void Clear();

	VkGraphicsPipelineLayoutBuilder& SetDescriptorSetLayouts(const Array<VkDescriptorSetLayout>& _vDescriptorSetLayouts);
	VkGraphicsPipelineLayoutBuilder& SetPushConstants(const ShaderPipelineData& _spdPipelineData);
};

class VkGraphicsPipelineBuilder {
private:
	Array<VkPipelineShaderStageCreateInfo> m_vShaderStages;

	VkPipelineVertexInputStateCreateInfo m_pvisciVertexInputStateInfo = {};
	VkPipelineInputAssemblyStateCreateInfo m_piasciInputAssemblyStateInfo = {};
	VkPipelineTessellationStateCreateInfo m_ptsciTessellationStateInfo = {};
	VkPipelineDynamicStateCreateInfo m_pdsciDynamicStateInfo = {};
	VkPipelineViewportStateCreateInfo m_pvsciViewportStateInfo = {};
	VkPipelineRasterizationStateCreateInfo m_prsciRasterizationStateInfo = {};
	VkPipelineMultisampleStateCreateInfo m_pmsciMultisampleStateInfo = {};
	VkPipelineDepthStencilStateCreateInfo m_pdssciDepthStencilStateInfo = {};
	VkPipelineColorBlendStateCreateInfo m_pcbsciColorBlendStateInfo = {};

	VkRenderPass m_rpRenderpass = VK_NULL_HANDLE;
	VkPipelineLayout m_plPipelineLayout = VK_NULL_HANDLE;

	uint32 m_u32Subpass = 0;

public:
	VkPipeline Build();
	void Clear();

	VkGraphicsPipelineBuilder& SetRenderpass(VkRenderPass _rpRenderpass);
	VkGraphicsPipelineBuilder& SetSubpass(uint32 _u32SubpassNdx);
	VkGraphicsPipelineBuilder& SetPipelineLayout(VkPipelineLayout _plPipelineLayout);
	VkGraphicsPipelineBuilder& SetShaderStages(const Array<VkPipelineShaderStageCreateInfo>& _vShaderStages);
	VkGraphicsPipelineBuilder& SetVertexInputState(const Array<VkVertexInputBindingDescription>& _vVertexBindings, const Array<VkVertexInputAttributeDescription>& _vVertexAttributes);
	VkGraphicsPipelineBuilder& SetInputAssemblyState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetTessellationState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetDynamicState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetViewportState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetRasterizationState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetMultisampleState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetDepthStencilState(const ShaderPipelineData& _spdPipelineData);
	VkGraphicsPipelineBuilder& SetColorBlendState(const ShaderPipelineData& _spdPipelineData);
};