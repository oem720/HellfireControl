#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Matrix.hpp>

#include <HellfireControl/Render/Buffer.hpp>

struct UniformBufferData {
	MatrixF m_mModel;
	MatrixF m_mView;
	MatrixF m_mProj;
};

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

struct RenderContext {
	uint32_t m_u32ContextID = 0;

	RenderContextType m_rctContextType = CONTEXT_TYPE_CUSTOM;

	RenderContextPriorityLevel m_rcplContextPriority = CONTEXT_PRIORITY_LAST;
	uint32_t m_u32ContextSubPriority = 0;

	RenderContextShaderFlags m_rcsfEnabledShaderStages = CONTEXT_SHADER_GRAPHICS_ALL;
	std::vector<std::string> m_vShaderFileNames;

	RenderContextVertexType m_rcvtVertexType = CONTEXT_VERTEX_TYPE_UNDEFINED;
};

class RenderingSubsystem {
private:
	std::vector<BufferHandleGeneric> m_vActiveBuffers;

	std::vector<RenderContext> m_vRenderContexts;

	uint32_t m_u32NewRenderContextID = 0;

	static RenderingSubsystem* m_prsInstancePtr;

	std::vector<std::string> GetShaderFileNames(RenderContextType _rctType); //TEMPORARY ! ! ! WILL BE REPLACED WITH READING FROM AN INI FILE

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName, uint64_t _u64WindowHandle, uint8_t _u8ActiveContextIDs);

	void RenderFrame();

	void Cleanup();

	void RegisterRenderContext(RenderContext& _rcContext, uint8_t _u8PreceedingContextCount = UINT8_MAX);

	void RegisterBuffer(const BufferHandleGeneric& _bhgNewBuffer);

	void DeregisterBuffer(const BufferHandleGeneric& _bhgBuffer);

	[[nodiscard]] const Vec2F GetRenderableExtents();

	[[nodiscard]] const uint32_t GetRenderContextID(RenderContextType _rctType);
};