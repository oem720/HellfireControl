
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/Renderer.hpp>

#include <HellfireControl/Render/Buffer.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_prsRenderer = RenderingSubsystem::GetInstance();

	m_prsRenderer->Init(m_strApplicationName, m_wWindow.GetNativeWindowHandle());
}

void UICreationToolApplication::Run() {
	this->Start();

	const std::vector<VertexSimple> vVertices = {
		{Vec2F(0.0f, -0.5f), Vec3F(1.0f, 0.0f, 0.0f)},
		{Vec2F(0.5f, 0.5f), Vec3F(0.0f, 1.0f, 0.0f)},
		{Vec2F(-0.5f, 0.5f), Vec3F(0.0f, 0.0f, 1.0f)}
	};

	Buffer vertexBuffer(BufferType::VERTEX, vVertices.data(), sizeof(VertexSimple), vVertices.size());

	while (!m_wWindow.CloseRequested()) {
		m_wWindow.PollEvents();

		m_prsRenderer->RenderFrame();
	}

	vertexBuffer.Cleanup(); //TEMPORARY ! ! ! ADD TO RENDERER SHUTDOWN ! ! !

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderer->Cleanup();

	m_wWindow.CleanupWindow();
}
