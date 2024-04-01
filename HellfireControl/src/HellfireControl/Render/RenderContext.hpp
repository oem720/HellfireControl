#pragma once

#include <HellfireControl/Core/Common.hpp>

enum RenderContextType : uint8_t {
	CONTEXT_TYPE_2D = 1U,
	CONTEXT_TYPE_3D = 2U,
	CONTEXT_TYPE_PARTICLE = 4U,
	CONTEXT_TYPE_UI = 8U,
	CONTEXT_TYPE_POST_PROCESSING = 16U,
	CONTEXT_TYPE_ALL = 31U,
	CONTEXT_TYPE_COMPUTE = 32U,
	CONTEXT_TYPE_CUSTOM = 64U,
};

enum RenderContextPriorityLevel : uint8_t {
	CONTEXT_PRIORITY_2D = 1U,
	CONTEXT_PRIORITY_3D = 2U,
	CONTEXT_PRIORITY_PARTICLE = 3U,
	CONTEXT_PRIORITY_UI = 4U,
	CONTEXT_PRIORITY_POST_PROCESSING = 5U,
	CONTEXT_PRIORITY_LAST = 6U
};

enum RenderContextShaderFlags : uint32_t {
	CONTEXT_SHADER_VERTEX = 1U,
	CONTEXT_SHADER_TESSELLATION_CONTROL = 2U,
	CONTEXT_SHADER_TESSELLATION_EVALUATION = 4U,
	CONTEXT_SHADER_GEOMETRY = 8U,
	CONTEXT_SHADER_FRAGMENT = 16U,
	CONTEXT_SHADER_GRAPHICS_ALL = 31U,
	CONTEXT_SHADER_COMPUTE = 32U,
	//TODO: Add Raytracing shader stages.
};

enum RenderContextVertexType : uint8_t {
	CONTEXT_VERTEX_TYPE_2D = 1U,
	CONTEXT_VERTEX_TYPE_3D = 2U,
	CONTEXT_VERTEX_TYPE_PARTICLE = 4U,
	CONTEXT_VERTEX_TYPE_UI = 8U,
	CONTEXT_VERTEX_TYPE_POST_PROCESSING = 16U,
	CONTEXT_VERTEX_TYPE_UNDEFINED = 128U
};

class RenderContext {
	friend class RenderingSubsystem;
	friend class PlatformRenderContext;
private:
	uint32_t m_u32ContextID = 0;

	RenderContextType m_rctContextType = CONTEXT_TYPE_CUSTOM;

	RenderContextPriorityLevel m_rcplContextPriority = CONTEXT_PRIORITY_LAST;

	uint32_t m_u32ContextSubPriority = 0;

	RenderContextVertexType m_rcvtVertexType = CONTEXT_VERTEX_TYPE_UNDEFINED;

	RenderContextShaderFlags m_rcsfEnabledShaderStages = CONTEXT_SHADER_GRAPHICS_ALL;

	std::vector<std::string> m_vShaderFileNames;
public:
	RenderContext() = delete;

	RenderContext(RenderContextType _rctType, RenderContextPriorityLevel _rcplPriority, uint32_t _u32SubPriority,
		RenderContextVertexType _rcvtVertex, RenderContextShaderFlags _rcsfEnabledShaders, const std::vector<std::string> _vShaderFilenames);

	void SetActive();

	void BindVertexBuffer(const BufferHandleGeneric& _bhgHandle);

	void BindIndexBuffer(const BufferHandleGeneric& _bhgHandle);

	void BindUniformBuffer(const BufferHandleGeneric& _bhghandle);

	void BindStorageBuffer(const BufferHandleGeneric& _bhgHandle);

	void Cleanup();
};