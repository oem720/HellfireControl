#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Render/RendererStructs.hpp>

typedef uint32 RendererTag;

enum DefaultRendererTags : RendererTag {
	RENDERER_2D = HC_CREATE_32BIT_TAG('2', 'D', '2', 'D'),
	RENDERER_3D = HC_CREATE_32BIT_TAG('3', 'D', '3', 'D'),
	RENDERER_UI = HC_CREATE_32BIT_TAG('U', 'I', 'U', 'I'),
	RENDERER_POST = HC_CREATE_32BIT_TAG('P', 'O', 'S', 'T')
};

enum RendererFlags : uint8 {
	CACHE_FRAME = (1 << 0),
	OUTPUT_FRAME = (1 << 1),
	CACHE_DEPTH_BUFFER = (1 << 2),
	OUTPUT_DEPTH_BUFFER = (1 << 3),
	IS_PRESENTING = (1 << 4)
};

class PlatformRenderer {
protected:
	RenderpassData m_rdRenderpassData;

	virtual void VerifyRenderpassPipelineData() = 0;

public:
	PlatformRenderer(const RenderpassData& _rdRenderpass) : m_rdRenderpassData(_rdRenderpass) {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
};

class Renderer {
private:
	uint8 m_u8Flags;
	std::vector<RendererTag> m_vDependencies;
	
	SharedPointer<PlatformRenderer> m_pPlatformRenderer;

	void CreatePlatformRenderpass(const RenderpassData& _rdRenderpass);

public:
	Renderer() = delete;

	Renderer(uint8 _u8Flags, const std::vector<RendererTag>& _vDependencies, const RenderpassData& _rdRenderpass)
		: m_u8Flags(_u8Flags)
		, m_vDependencies(_vDependencies) {
		CreatePlatformRenderpass(_rdRenderpass);
	}

	void Init() {
		m_pPlatformRenderer->Init();
	}

	void Render() { m_pPlatformRenderer->Render(); }
	void Cleanup() { m_pPlatformRenderer->Cleanup(); }

	[[nodiscard]] HC_INLINE const std::vector<RendererTag>& GetDependencies() const { return m_vDependencies; }
	[[nodiscard]] HC_INLINE size_t GetDependencyCount() const { return m_vDependencies.size(); }
	[[nodiscard]] HC_INLINE SharedPointer<PlatformRenderer> GetPlatformRenderer() { return m_pPlatformRenderer; }
};