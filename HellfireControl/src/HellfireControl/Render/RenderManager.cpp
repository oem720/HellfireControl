
#include <HellfireControl/Render/RenderManager.hpp>

#include <HellfireControl/Render/RenderMemoryManager.hpp>

RenderManager* RenderManager::m_prsInstancePtr = nullptr;

bool RenderManager::m_bFramebufferInvalid = false;

RenderManager* RenderManager::GetInstance() {
	if (m_prsInstancePtr == nullptr) {
		m_prsInstancePtr = new RenderManager();
	}

	return m_prsInstancePtr;
}

void RenderManager::WindowEventHandler(WindowHandleGeneric _whgHandle, const WindowCallbackMessage& _wcmMessage) {
	if (_wcmMessage.m_wcetType & WINDOW_RESIZE) {
		//At the moment, these values are not needed and it's merely a demonstration of how parameters might be packed in a message
		int iNewWidth = static_cast<int>(_wcmMessage.lower >> 32);
		int iNewHeight = static_cast<int>(_wcmMessage.lower & 0xFFFFFFFF);

		MarkSwapchainInvalid();
	}

	if (_wcmMessage.m_wcetType & WINDOW_CLOSE) {
		//TODO: Possibly handle WINDOW_CLOSE here.
	}
}

void RenderManager::AddRenderer(RendererTag _rtTag, Shared<Renderer> _pRenderer) {
	RegisterPlatformRenderer(_pRenderer);
	
	m_mRenderers[_rtTag] = _pRenderer;
}

void RenderManager::Init(const String& _strAppName, uint32 _u32AppVersion, WindowHandleGeneric _whgWindowHandle, uint32 _u32InitialMemorySize) {
	m_whgWindowHandle = _whgWindowHandle;

	Window(_whgWindowHandle).RegisterEventCallback(WindowEventHandler);

	InitPlatformObjects(_strAppName, _u32AppVersion);

	m_prmmMemoryManager = RenderMemoryManager::GetInstance();
	m_prmmMemoryManager->Init(_u32InitialMemorySize);

	InitRenderJobs();

}

void RenderManager::RenderFrame() {
	for (const auto& aRenderJob : m_mRenderJobs) {
		m_jmRenderJobManager.AddJob(aRenderJob.second);
	}

	m_jmRenderJobManager.BlockUntilQueueClear();

	PresentFrame();
}

void RenderManager::InitRenderJobs() {
	for (const auto& aRenderer : m_mRenderers) {
		if (m_mRenderJobs.size() == m_mRenderers.size()) {
			break; //If we have all the jobs we need, exit.
		}

		if (m_mRenderJobs.contains(aRenderer.first)) {
			continue;
		}

		RecursiveInitRenderJobs(aRenderer.first, g_iMaxRenderLayerComplexity); //We do this in a loop because we need to ensure that all render jobs are hit.
	}
}

Shared<Job> RenderManager::RecursiveInitRenderJobs(RendererTag _rtTag, int _iDepthLimit, int _iDepth) {
	if (_iDepth == _iDepthLimit) {
		throw std::runtime_error("ERROR: Depth limit of " + std::to_string(_iDepthLimit) + " reached! Circular dependency or improbably large render system is unsupported!");
	}

	if (m_mRenderJobs.contains(_rtTag)) {
		return m_mRenderJobs[_rtTag];
	}

	m_mRenderers[_rtTag]->Init();

	Shared<Job> pJob = std::make_shared<Job>([this, _rtTag]() { m_mRenderers[_rtTag]->Render(); }, Array<Shared<Job>>());

	//Now we need to create the dependencies
	for (const uint32& u32Dependency : m_mRenderers[_rtTag]->GetDependencies()) {
		pJob->m_vDependencies.push_back(RecursiveInitRenderJobs(u32Dependency, _iDepthLimit, _iDepth + 1));
	}

	m_mRenderJobs[_rtTag] = pJob;

	return pJob;
}

void RenderManager::Cleanup() {
	for (const auto& aRenderer : m_mRenderers) {
		aRenderer.second->Cleanup();
	}

	m_prmmMemoryManager->Cleanup();

	CleanupPlatformObjects();

	delete m_prsInstancePtr;
}