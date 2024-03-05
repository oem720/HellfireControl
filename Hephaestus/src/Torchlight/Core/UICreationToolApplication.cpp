
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/Renderer.hpp>
#include <HellfireControl/Render/Buffer.hpp>

#include <Platform/GLInclude.hpp> //Hack to get hard coded values working. This will be fixed when vertices are moved to their own file.

void UICreationToolApplication::UpdateUniformBuffer() {
	static auto aStartTime = std::chrono::high_resolution_clock::now();
	auto aCurrentTime = std::chrono::high_resolution_clock::now();
	float fTime = std::chrono::duration<float, std::chrono::seconds::period>(aCurrentTime - aStartTime).count();

	Vec2F v2RenderableArea = m_prsRenderer->GetRenderableExtents();

	UniformBufferData ubdData = {
		.m_mModel = RotateZGlobalDeg(fTime * HC_DEG2RAD(90.0f) * 15.0f, IdentityF()),
		.m_mView = Inverse(LookAtLH(Vec3F(1.0f, 1.0f, 1.0f), Vec3F(0.0f, 0.0f, 0.0f), Vec3F(0.0f, 0.0f, 1.0f))),
		.m_mProj = ProjectionF(v2RenderableArea.x / v2RenderableArea.y, HC_DEG2RAD(45.0f), 0.1f, 10.0f)
	};
}

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_prsRenderer = RenderingSubsystem::GetInstance();

	m_prsRenderer->Init(m_strApplicationName, m_wWindow.GetNativeWindowHandle(), CONTEXT_TYPE_3D);

	const std::vector<VertexSimple> vVertices = {
		{ Vec3F(-0.5f, -0.5f, 0.25f), Vec3F(1.0f, 0.0f, 0.0f), Vec2F(1.0f, 0.0f) },
		{ Vec3F(0.5f, -0.5f, 0.25f), Vec3F(0.0f, 1.0f, 0.0f), Vec2F(0.0f, 0.0f) },
		{ Vec3F(0.5f, 0.5f, 0.25f), Vec3F(0.0f, 0.0f, 1.0f), Vec2F(0.0f, 1.0f) },
		{ Vec3F(-0.5f, 0.5f, 0.25f), Vec3F(1.0f, 1.0f, 1.0f), Vec2F(1.0f, 1.0f) },

		{ Vec3F(-0.5f, -0.5f, -0.25f), Vec3F(1.0f, 0.0f, 0.0f), Vec2F(1.0f, 0.0f) },
		{ Vec3F(0.5f, -0.5f, -0.25f), Vec3F(0.0f, 1.0f, 0.0f), Vec2F(0.0f, 0.0f) },
		{ Vec3F(0.5f, 0.5f, -0.25f), Vec3F(0.0f, 0.0f, 1.0f), Vec2F(0.0f, 1.0f) },
		{ Vec3F(-0.5f, 0.5f, -0.25f), Vec3F(1.0f, 1.0f, 1.0f), Vec2F(1.0f, 1.0f) }
	};

	const std::vector<uint16_t> vIndices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	Buffer vertexBuffer(BufferType::VERTEX_BUFFER, vVertices.data(), sizeof(VertexSimple), vVertices.size());
	Buffer indexBuffer(BufferType::INDEX_BUFFER, vIndices.data(), sizeof(uint16_t), vIndices.size());

	m_prsRenderer->RegisterBuffer(vertexBuffer.GetBufferHandle());
	m_prsRenderer->RegisterBuffer(indexBuffer.GetBufferHandle());

	UniformBufferData ubdData = {};

	Buffer uniformBuffer(BufferType::UNIFORM_BUFFER, &ubdData, sizeof(UniformBufferData), m_prsRenderer->GetRenderContext(CONTEXT_TYPE_3D).m_u32ContextID);
}

void UICreationToolApplication::Run() {
	this->Start();	

	while (!m_wWindow.CloseRequested()) {
		m_wWindow.PollEvents();

		UpdateUniformBuffer(); //TEMPORARY ! ! !

		m_prsRenderer->RenderFrame();
	}

	this->End();
}

void UICreationToolApplication::End() {
	m_prsRenderer->Cleanup();

	m_wWindow.Cleanup();
}