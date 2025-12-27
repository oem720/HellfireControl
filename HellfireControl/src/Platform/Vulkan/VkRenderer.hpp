#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Render/Renderer.hpp>

struct VkRenderPipelineData {
	VkPipelineLayout m_plPipelineLayout;
	VkPipeline m_pPipeline;
	Array<VkDescriptorSetLayout> m_vDescriptorSetLayouts;
};

class VkRenderer : public PlatformRenderer {
private:
	static Map<HCShaderVarType, VkDescriptorType> m_mShaderVarTranslationTable;

	VkRenderPass m_rpRenderpass = VK_NULL_HANDLE;
	Array<VkRenderPipelineData> m_vPipelines;

	void VerifyRenderpassPipelineData();

	void CreateRenderpass();
	void CreatePipelines();

	VkRenderPipelineData CreateGraphicsPipeline(uint32 _u32Renderpass, const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateComputePipeline(const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateRaytracingPipeline(const ShaderPipelineData& _spdPipelineData);

	Array<VkPipelineShaderStageCreateInfo> CreateShaderStages(const ShaderPipelineData& _spdPipelineData);
	Array<VkDescriptorSetLayout> CreateDescriptorSetLayouts(const ShaderPipelineData& _spdPipelineData);
	Array<VkPushConstantRange> CreatePushConstantRanges(const ShaderPipelineData& _spdPipelineData);

public:
	VkRenderer(const RenderpassData& _rdRenderpass) : PlatformRenderer(_rdRenderpass) { VerifyRenderpassPipelineData(); }

	void Init();

	void Render();

	void Cleanup();

	Array<VkDescriptorType> GetDescriptorCounts() const;

	friend class VkDescriptorSetLayoutBuilder;
};