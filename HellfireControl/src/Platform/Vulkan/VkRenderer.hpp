#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Render/Renderer.hpp>

struct VkRenderPipelineData {
	VkPipelineLayout m_plPipelineLayout;
	VkPipeline m_pPipeline;
	VkDescriptorSetLayout m_dslDescriptorSetLayout;
};

struct VkDescriptorTypeCount {
	VkDescriptorType m_dtType = VK_DESCRIPTOR_TYPE_SAMPLER;
	uint32_t m_u32DescriptorCount = 0;
};

class VkRenderer : public PlatformRenderer {
private:
	VkRenderPass m_rpRenderPass = VK_NULL_HANDLE;
	std::vector<VkRenderPipelineData> m_vPipelines;

	void CreateRenderpass(const RenderpassData& _rdRenderpass);
	void CreatePipelines(const RenderpassData& _rdRenderpass);

	VkRenderPipelineData CreateGraphicsPipeline(const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateComputePipeline(const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateRaytracingPipeline(const ShaderPipelineData& _spdPipelineData);

public:
	void Init(const RenderpassData& _rdRenderpass);

	void Render();

	void Cleanup();

	std::vector<VkDescriptorTypeCount> GetDescriptorCounts() const;
};