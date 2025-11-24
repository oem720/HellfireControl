#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Render/Renderer.hpp>

class VkRenderer : public PlatformRenderpass {
private:
	VkRenderPass m_rpRenderPass;

	std::vector<VkShaderModule> m_vShaders;

	void CreateRenderpass(const RenderpassData& _rdRenderpass);

public:
	void Init(const RenderpassData& _rdRenderpass);

	void Render();

	void Cleanup();
};