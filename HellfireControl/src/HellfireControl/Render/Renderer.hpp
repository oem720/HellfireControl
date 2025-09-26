#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Asset/HCUID.hpp>

enum RendererFlags : uint8_t {
	CACHE_FRAME = (1 << 0),
	OUTPUT_RENDER_TARGET = (1 << 1),
	USE_DEPTH_BUFFER = (1 << 2),
	OUTPUT_DEPTH_BUFFER = (1 << 3),
	IS_PRESENTING = (1 << 4)
};

enum DefaultRendererTags : uint32_t {
	RENDERER_2D = HC_CREATE_32BIT_TAG('2', 'D', '2', 'D'),
	RENDERER_3D = HC_CREATE_32BIT_TAG('3', 'D', '3', 'D'),
	RENDERER_UI = HC_CREATE_32BIT_TAG('U', 'I', 'U', 'I'),
	RENDERER_POST = HC_CREATE_32BIT_TAG('P', 'O', 'S', 'T')
};

struct RendererSubpass {

};

class Renderer {
private:
	uint32_t m_u32Tag;

	uint8_t m_u8Flags;

	std::vector<uint32_t> m_vDependencies;

	std::vector<RendererSubpass> m_vSubpasses;

public:
	Renderer() = delete;

	Renderer(uint32_t _u32Tag, uint8_t _u8Flags, const std::vector<uint32_t>& _vDependencies, const std::vector<RendererSubpass>& _vSubpasses) 
		: m_u32Tag(_u32Tag), m_u8Flags(_u8Flags), m_vDependencies(_vDependencies), m_vSubpasses(_vSubpasses) {}

	void Init();

	void Render();

	void Cleanup();

	[[nodiscard]] HC_INLINE uint32_t GetTag() const { return m_u32Tag; }

	[[nodiscard]] HC_INLINE const std::vector<uint32_t>& GetDependencies() const { return m_vDependencies; }

	[[nodiscard]] HC_INLINE size_t GetDependencyCount() const { return m_vDependencies.size(); }
};