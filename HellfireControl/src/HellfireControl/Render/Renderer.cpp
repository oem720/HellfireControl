
#include <HellfireControl/Render/Renderer.hpp>

#include <Platform/GLInclude.hpp>

RenderingSubsystem* RenderingSubsystem::m_prsInstancePtr = nullptr;

RenderingSubsystem* RenderingSubsystem::GetInstance() {
	if (!m_prsInstancePtr) {
		m_prsInstancePtr = new RenderingSubsystem();
	}

	return m_prsInstancePtr;
}

void RenderingSubsystem::Init(const std::string& _strAppName, uint64_t _u64WindowHandle) {
	//TODO Add ability to store end app version data to replace the engine version. For now, they'll be identical.
	PlatformRenderer::InitRenderer(_strAppName, HC_ENGINE_VERSION, _u64WindowHandle);
}

void RenderingSubsystem::Cleanup() {
	PlatformRenderer::CleanupRenderer();

	delete m_prsInstancePtr; //Final renderer cleanup
}