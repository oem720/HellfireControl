
#include <HellfireControl/Render/RenderManager.hpp>

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

void RenderManager::AddRenderer(std::unique_ptr<Renderer> _pRenderer) {
	m_mRenderers[_pRenderer->GetTag()] = std::move(_pRenderer);
}

void RenderManager::Init(const std::string& _strAppName, uint32_t _u32AppVersion, WindowHandleGeneric _whgWindowHandle) {
	m_whgWindowHandle = _whgWindowHandle;

	Window(_whgWindowHandle).RegisterEventCallback(WindowEventHandler);

	InitPlatformObjects(_strAppName, _u32AppVersion);

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

std::shared_ptr<Job> RenderManager::RecursiveInitRenderJobs(uint32_t _u32RenderId, int _iDepthLimit, int _iDepth) {
	if (_iDepth == _iDepthLimit) {
		throw std::runtime_error("ERROR: Depth limit of " + std::to_string(_iDepthLimit) + " reached! Circular dependency or improbably large render system is unsupported!");
	}

	if (m_mRenderJobs.contains(_u32RenderId)) {
		return m_mRenderJobs[_u32RenderId];
	}

	m_mRenderers[_u32RenderId]->Init();

	std::shared_ptr<Job> pJob = std::make_shared<Job>([this, _u32RenderId]() { m_mRenderers[_u32RenderId]->Render(); }, std::vector<std::shared_ptr<Job>>());

	//Now we need to create the dependencies
	for (const uint32_t& u32Dependency : m_mRenderers[_u32RenderId]->GetDependencies()) {
		pJob->m_vDependencies.push_back(RecursiveInitRenderJobs(u32Dependency, _iDepthLimit, _iDepth + 1));
	}

	m_mRenderJobs[_u32RenderId] = pJob;

	return pJob;
}

void RenderManager::Cleanup() {
	for (const auto& aRenderer : m_mRenderers) {
		aRenderer.second->Cleanup();
	}

	CleanupPlatformObjects();

	delete m_prsInstancePtr;
}