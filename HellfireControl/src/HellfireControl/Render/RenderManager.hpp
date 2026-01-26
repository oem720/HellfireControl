#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Window.hpp>

#include <HellfireControl/Core/Concurrency/JobManager.hpp>

#include <HellfireControl/Render/Renderer.hpp>

constexpr int g_iMaxRenderLayerComplexity = 10;

class RenderMemoryManager;

class RenderManager {
private:
	WindowHandleGeneric m_whgWindowHandle = 0;

	Map<RendererTag, Shared<Renderer>> m_mRenderers;

	Map<RendererTag, Shared<Job>> m_mRenderJobs;

	JobManager m_jmRenderJobManager;

	RenderMemoryManager* m_prmmMemoryManager = nullptr;

	static bool m_bFramebufferInvalid;

	static RenderManager* m_prsInstancePtr;

	void InitPlatformObjects(const String& _strAppName, uint32 _u32AppVersion);

	void RegisterPlatformRenderer(const Shared<Renderer>& _pRenderer);

	void PresentFrame();

	void InitRenderJobs();

	Shared<Job> RecursiveInitRenderJobs(RendererTag _rtTag, int _iDepthLimit, int _iDepth = 0);

	void CleanupPlatformObjects();

	static void WindowEventHandler(WindowHandleGeneric _whgHandle, const WindowCallbackMessage& _wcmMessage);

	static void MarkSwapchainInvalid() { m_bFramebufferInvalid = true; }

	RenderManager() : m_jmRenderJobManager(HC_MAX(2, (Thread::hardware_concurrency() >> 2))) {}

public:
	RenderManager(RenderManager& _other) = delete;

	void operator=(const RenderManager& _other) = delete;

	static RenderManager* GetInstance();

	void AddRenderer(RendererTag _rtTag, Shared<Renderer> _pRenderer);

	void Init(const String& _strAppName, uint32 _u32AppVersion, WindowHandleGeneric _whgWindowHandle, uint32 _u32InitialMemorySize);

	void RenderFrame();

	void Cleanup();
};