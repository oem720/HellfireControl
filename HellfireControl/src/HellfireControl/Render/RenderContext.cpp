
#include <HellfireControl/Render/RenderContext.hpp>

#include <Platform/GLInclude.hpp>

RenderContext::RenderContext(RenderContextType _rctType, RenderContextPriorityLevel _rcplPriority, uint32_t _u32SubPriority, RenderContextVertexType _rcvtVertex, RenderContextShaderFlags _rcsfEnabledShaders, const std::vector<std::string> _vShaderFilenames) :
	m_rctContextType(_rctType), m_rcplContextPriority(_rcplPriority), m_u32ContextSubPriority(_u32SubPriority), m_rcvtVertexType(_rcvtVertex), m_rcsfEnabledShaderStages(_rcsfEnabledShaders), m_vShaderFileNames(_vShaderFilenames) 
{
	static uint32_t u32ContextID = 0;

	m_u32ContextID = u32ContextID++;

	PlatformRenderContext::InitRenderContext(*this); //Ick.
}

void RenderContext::SetActive() {
	PlatformRenderContext::SetActiveRenderContext(m_u32ContextID);
}

void RenderContext::BindVertexBuffer(const BufferHandleGeneric& _bhgHandle) {

}

void RenderContext::BindIndexBuffer(const BufferHandleGeneric& _bhgHandle) {

}

void RenderContext::BindUniformBuffer(const BufferHandleGeneric& _bhghandle) {

}

void RenderContext::BindStorageBuffer(const BufferHandleGeneric& _bhgHandle) {

}

void RenderContext::Cleanup() {
	PlatformRenderContext::CleanupRenderContext(m_u32ContextID);
}
