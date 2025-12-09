#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Render/RendererStructs.hpp>

typedef uint32_t RendererTag;

enum DefaultRendererTags : RendererTag {
	RENDERER_2D = HC_CREATE_32BIT_TAG('2', 'D', '2', 'D'),
	RENDERER_3D = HC_CREATE_32BIT_TAG('3', 'D', '3', 'D'),
	RENDERER_UI = HC_CREATE_32BIT_TAG('U', 'I', 'U', 'I'),
	RENDERER_POST = HC_CREATE_32BIT_TAG('P', 'O', 'S', 'T')
};

enum RendererFlags : uint8_t {
	CACHE_FRAME = (1 << 0),
	OUTPUT_FRAME = (1 << 1),
	CACHE_DEPTH_BUFFER = (1 << 2),
	OUTPUT_DEPTH_BUFFER = (1 << 3),
	IS_PRESENTING = (1 << 4)
};

class PlatformRenderpass {
public:
	virtual void Init(const RenderpassData& _rdRenderpass) = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
};

class Renderer {
private:
	uint8_t m_u8Flags;
	RenderpassData m_rdRenderpass;
	std::vector<RendererTag> m_vDependencies;
	
	std::unique_ptr<PlatformRenderpass> m_pPlatformRenderpass;

	void VerifyRenderpassPipelineData();

	void CreatePlatformRenderpass();

public:
	Renderer() = delete;

	Renderer(uint8_t _u8Flags, const std::vector<RendererTag>& _vDependencies, const RenderpassData& _rdRenderpass)
		: m_u8Flags(_u8Flags)
		, m_vDependencies(_vDependencies)
		, m_rdRenderpass(_rdRenderpass) {
		VerifyRenderpassPipelineData();
	}

	void Init() {
		CreatePlatformRenderpass();
		m_pPlatformRenderpass->Init(m_rdRenderpass);
	}

	void Render() { m_pPlatformRenderpass->Render(); }
	void Cleanup() { m_pPlatformRenderpass->Cleanup(); }

	[[nodiscard]] HC_INLINE const std::vector<RendererTag>& GetDependencies() const { return m_vDependencies; }
	[[nodiscard]] HC_INLINE size_t GetDependencyCount() const { return m_vDependencies.size(); }
};