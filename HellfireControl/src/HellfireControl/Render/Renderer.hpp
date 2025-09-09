#pragma once

#include <HellfireControl/Core/Common.hpp>

enum RendererFlags : uint16_t {
	VERTEX_STATIC = (1 << 0),
	VERTEX_SKINNED = (1 << 1),
	VERTEX_2D = (1 << 2),
	VERTEX_UI = (1 << 3),
	CACHE_FRAME = (1 << 4),
	OUTPUT_RENDER_TARGET = (1 << 5),
	OUTPUT_MULTIPLE_RENDER_TARGETS = (1 << 6),
	USE_DEPTH_BUFFER = (1 << 7),
	OUTPUT_DEPTH_BUFFER = (1 << 8),
	TRIANGLE_STRIP = (1 << 9),
	TRIANGLE_LIST = (1 << 10),
	LINE_STRIP = (1 << 11),
	LINE_LIST = (1 << 12)
};

enum DefaultRendererTags : uint32_t {
	RENDERER_2D = HC_CREATE_32BIT_TAG('2', 'D', '2', 'D'),
	RENDERER_3D = HC_CREATE_32BIT_TAG('3', 'D', '3', 'D'),
	RENDERER_UI = HC_CREATE_32BIT_TAG('G', 'U', 'I', 'R'),
	RENDERER_POST = HC_CREATE_32BIT_TAG('P', 'O', 'S', 'T')
};

class Renderer {
private:
	uint32_t m_u32Tag;

	uint16_t m_u16Flags;

	std::vector<uint32_t> m_vDependencies;

public:
	Renderer() = delete;

	Renderer(uint32_t _u32Tag, std::vector<uint32_t> _vDependencies, uint16_t _rfFlags) : m_u32Tag(_u32Tag), m_vDependencies(_vDependencies), m_u16Flags(_rfFlags) {}

	void Init();

	void Render();

	void Cleanup();

	[[nodiscard]] HC_INLINE uint32_t GetTag() const { return m_u32Tag; }

	[[nodiscard]] HC_INLINE const std::vector<uint32_t>& GetDependencies() const { return m_vDependencies; }

	[[nodiscard]] HC_INLINE size_t GetDependencyCount() const { return m_vDependencies.size(); }
};