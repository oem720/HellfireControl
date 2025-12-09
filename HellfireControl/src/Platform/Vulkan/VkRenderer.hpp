#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Render/Renderer.hpp>

struct VkRenderPipelineData {
	VkPipelineLayout m_plPipelineLayout;
	VkPipeline m_pPipeline;
	VkDescriptorSetLayout m_dslDescriptorSetLayout;
};

class VkRenderer : public PlatformRenderer {
private:
	static std::map<HCShaderVarType, VkDescriptorType> m_mShaderVarTranslationTable;

	VkRenderPass m_rpRenderpass = VK_NULL_HANDLE;
	std::vector<VkRenderPipelineData> m_vPipelines;

	void VerifyRenderpassPipelineData();

	void CreateRenderpass();
	void CreatePipelines();

	VkRenderPipelineData CreateGraphicsPipeline(const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateComputePipeline(const ShaderPipelineData& _spdPipelineData);
	VkRenderPipelineData CreateRaytracingPipeline(const ShaderPipelineData& _spdPipelineData);

public:
	VkRenderer(const RenderpassData& _rdRenderpass) : PlatformRenderer(_rdRenderpass) { VerifyRenderpassPipelineData(); }

	void Init();

	void Render();

	void Cleanup();

	std::vector<VkDescriptorType> GetDescriptorCounts() const;
};