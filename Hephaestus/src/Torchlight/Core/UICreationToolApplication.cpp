
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Render/Buffer.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_prsRenderer = RenderingSubsystem::GetInstance();

	m_prsRenderer->Init(m_strApplicationName, m_wWindow.GetNativeWindowHandle());

	const std::vector<VertexSimple> vVertices = {
		{ Vec3F(-0.5f, -0.5f, 0.0f), Vec3F(1.0f, 0.0f, 0.0f), Vec2F(1.0f, 0.0f) },
		{ Vec3F(0.5f, -0.5f, 0.0f), Vec3F(0.0f, 1.0f, 0.0f), Vec2F(0.0f, 0.0f) },
		{ Vec3F(0.5f, 0.5f, 0.0f), Vec3F(0.0f, 0.0f, 1.0f), Vec2F(0.0f, 1.0f) },
		{ Vec3F(-0.5f, 0.5f, 0.0f), Vec3F(1.0f, 1.0f, 1.0f), Vec2F(1.0f, 1.0f) },

		{ Vec3F(-0.5f, -0.5f, -0.5f), Vec3F(1.0f, 0.0f, 0.0f), Vec2F(1.0f, 0.0f) },
		{ Vec3F(0.5f, -0.5f, -0.5f), Vec3F(0.0f, 1.0f, 0.0f), Vec2F(0.0f, 0.0f) },
		{ Vec3F(0.5f, 0.5f, -0.5f), Vec3F(0.0f, 0.0f, 1.0f), Vec2F(0.0f, 1.0f) },
		{ Vec3F(-0.5f, 0.5f, -0.5f), Vec3F(1.0f, 1.0f, 1.0f), Vec2F(1.0f, 1.0f) }
	};

	const std::vector<uint16_t> vIndices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	Buffer vertexBuffer(BufferType::VERTEX, vVertices.data(), sizeof(VertexSimple), vVertices.size());
	Buffer indexBuffer(BufferType::INDEX, vIndices.data(), sizeof(uint16_t), vIndices.size());

	m_prsRenderer->RegisterBuffer(vertexBuffer.GetBufferHandle());
	m_prsRenderer->RegisterBuffer(indexBuffer.GetBufferHandle());
}

void UICreationToolApplication::Run() {
	this->Start();	

	while (!m_wWindow.CloseRequested()) {
		m_wWindow.PollEvents();

		m_prsRenderer->RenderFrame();
	}

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderer->Cleanup();

	m_wWindow.CleanupWindow();
}