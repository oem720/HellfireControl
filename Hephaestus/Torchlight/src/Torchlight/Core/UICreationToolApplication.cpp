
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/RenderManager.hpp>
#include <HellfireControl/Asset/AssetManager.hpp>
#include <HellfireControl/UI/UI.hpp>

#include <HellfireControl/Render/Primitives.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Asset/Converters/Font/FontProcessor.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_pamAssetManager = AssetManager::GetInstance();
	m_pumUIManager = UIManager::GetInstance();
	m_prmRenderManager = RenderManager::GetInstance();

	m_pamAssetManager->Init();
	m_pumUIManager->Init();
	m_prmRenderManager->Init(m_strApplicationName, HC_ENGINE_VERSION, m_wWindow.GetNativeWindowHandle());
}

void UICreationToolApplication::Run() {
	this->Start();

	

	this->End();
}

void UICreationToolApplication::End() {
	m_pamAssetManager->Cleanup();
	m_pumUIManager->Cleanup();
	m_prmRenderManager->Cleanup();

	m_wWindow.Cleanup();
}