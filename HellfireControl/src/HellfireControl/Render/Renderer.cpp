
#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Core/Window.hpp>

#include <Platform/GLInclude.hpp>

RenderingSubsystem* RenderingSubsystem::m_prsInstancePtr = nullptr;

RenderingSubsystem* RenderingSubsystem::GetInstance() {
	if (!m_prsInstancePtr) {
		m_prsInstancePtr = new RenderingSubsystem();
	}

	return m_prsInstancePtr;
}

static void WindowEventHandler(WindowHandleGeneric _whgHandle, const WindowCallbackMessage& _wcmMessage) {
	if (_wcmMessage.m_wcetType & WINDOW_RESIZE) {
		//At the moment, these values are not needed and it's merely a demonstration of how parameters might be packed in a message
		int iNewWidth = static_cast<int>(_wcmMessage.lower >> 32); //Shift the packed value enough to extract width
		int iNewHeight = static_cast<int>(_wcmMessage.lower & 0xFFFFFFFF); //Use bit masking to extract height

		PlatformRenderer::MarkFramebufferUpdated();
	}

	if (_wcmMessage.m_wcetType & WINDOW_CLOSE) {
		//TODO Possibly handle WINDOW_CLOSE here.
	}
}

void RenderingSubsystem::Init(const std::string& _strAppName, uint64_t _u64WindowHandle, uint8_t _u8ActiveContextIDs) {
	Window(_u64WindowHandle).RegisterEventCallback(WindowEventHandler);

	//TODO Make App Version data come from the .ini file.
	PlatformRenderer::InitRenderer(_strAppName, HC_ENGINE_VERSION, _u64WindowHandle);

	if (_u8ActiveContextIDs & CONTEXT_TYPE_CUSTOM) {
		std::cerr << "WARNING: Attempted a default initialization of CONTEXT_TYPE_CUSTOM!\n\nAll Contexts of render type CUSTOM must be explicitly initialized using Renderer::RegisterRenderContext!\n";
	}

	for (uint8_t u8Flag = CONTEXT_TYPE_2D; u8Flag < CONTEXT_TYPE_ALL; u8Flag <<= 1) {
		if (_u8ActiveContextIDs & u8Flag) {
			RenderContext rcContext = {
				.m_u32ContextID = m_u32NewRenderContextID++,
				.m_rctContextType = static_cast<RenderContextType>(u8Flag),
				.m_rcplContextPriority = static_cast<RenderContextPriorityLevel>(u8Flag), //Priority level and type use the same value but are differentiated for clarity.
				.m_u32ContextSubPriority = 0, //Priority 0 signifies that this will go first during that context's render pass.
				.m_rcsfEnabledShaderStages = static_cast<RenderContextShaderFlags>(CONTEXT_SHADER_VERTEX | CONTEXT_SHADER_FRAGMENT), //Hard coded for now, will be pulled from a .ini file.
				.m_vShaderFileNames = GetShaderFileNames(static_cast<RenderContextType>(u8Flag)),
				.m_rcvtVertexType = static_cast<RenderContextVertexType>(u8Flag)
			};

			PlatformRenderer::InitRenderContext(rcContext); //Init the render context within the platform

			m_vRenderContexts.push_back(rcContext); //Add our context to the list
		}
	}
}

void RenderingSubsystem::RenderFrame() {
	PlatformRenderer::RenderFrame();
}

void RenderingSubsystem::Cleanup() {
	for (const auto& aBufferHandle : m_vActiveBuffers) {
		Buffer(aBufferHandle).Cleanup(false);
	}

	m_vActiveBuffers.clear();

	PlatformRenderer::CleanupRenderer();

	delete m_prsInstancePtr; //Final renderer cleanup
}

void RenderingSubsystem::RegisterRenderContext(RenderContext& _rcContext, uint8_t _u8PreceedingContextCount) {
	PlatformRenderer::InitRenderContext(_rcContext);

	if (_u8PreceedingContextCount >= m_vRenderContexts.size()) {
		//If no preceeding count is given or if the given preceeding count exceeds active render contexts, push to the end.
		//TODO: Add an exception to ensure that a render context of a given type goes before contexts that depend on the output.
		m_vRenderContexts.push_back(_rcContext);
	}
	else {
		//Insert to the list in the position after the preceeding count of contexts.5
		m_vRenderContexts.insert(m_vRenderContexts.begin() + _u8PreceedingContextCount, _rcContext);
	}
}

void RenderingSubsystem::RegisterBuffer(const BufferHandleGeneric& _bhgNewBuffer) {
	m_vActiveBuffers.push_back(_bhgNewBuffer);
}

void RenderingSubsystem::DeregisterBuffer(const BufferHandleGeneric& _bhgBuffer) {
	for (int ndx = 0; ndx < m_vActiveBuffers.size(); ++ndx) {
		if (m_vActiveBuffers[ndx] == _bhgBuffer) {
			m_vActiveBuffers.erase(m_vActiveBuffers.begin() + ndx);
			break;
		}
	}
}

const Vec2F RenderingSubsystem::GetRenderableExtents() {
	return PlatformRenderer::GetRenderableExtent();
}

const RenderContext RenderingSubsystem::GetRenderContext(RenderContextType _rctType) {
	for (const auto& aContext : m_vRenderContexts) {
		if (aContext.m_rctContextType == _rctType) {
			return aContext;
		}
	}

	std::cerr << "WARNING: Attempted to get a render context that either doesn't exist or has not been initialized.\n\nThe render context struct given is empty.\n";
	return {};
}

std::vector<std::string> RenderingSubsystem::GetShaderFileNames(RenderContextType _rctType) {
	switch (_rctType) {
	case CONTEXT_TYPE_3D: {
		return {
			"../../Assets/Shaders/Vulkan/test_vert.spv",
			"../../Assets/Shaders/Vulkan/test_frag.spv"
		};
	} break;
	}

	throw std::runtime_error("ERROR: Attempted to load an undefined Render Context's shaders.");
}