
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Render/RenderManager.hpp>
#include <HellfireControl/Asset/AssetManager.hpp>
#include <HellfireControl/UI/UI.hpp>

#include <HellfireControl/Asset/Font.hpp>

#include <HellfireControl/Asset/Converters/Font/FontProcessor.hpp>

void UICreationToolApplication::Start() {
	m_wWindow = Window(m_strApplicationName, WINDOWED, Vec2F(800, 600), Vec2F(0, 0));

	m_pamAssetManager = AssetManager::GetInstance();
	m_pumUIManager = UIManager::GetInstance();
	m_prmRenderManager = RenderManager::GetInstance();

	m_pamAssetManager->Init();
	m_pumUIManager->Init();

	//Manual render layer creation for testing.
	std::unique_ptr<Renderer> TestRenderer1 = std::make_unique<Renderer>(1, std::vector<uint32_t>(), 0);
	std::unique_ptr<Renderer> TestRenderer2 = std::make_unique<Renderer>(2, std::vector<uint32_t>(), 0);
	std::unique_ptr<Renderer> TestRenderer3 = std::make_unique<Renderer>(3, std::vector<uint32_t>(), 0);
	std::unique_ptr<Renderer> TestRenderer4 = std::make_unique<Renderer>(4, std::vector<uint32_t>(), 0);
	std::unique_ptr<Renderer> TestRenderer5 = std::make_unique<Renderer>(5, std::vector<uint32_t>(), 0);

	m_prmRenderManager->AddRenderer(std::move(TestRenderer4));
	m_prmRenderManager->AddRenderer(std::move(TestRenderer2));
	m_prmRenderManager->AddRenderer(std::move(TestRenderer5));
	m_prmRenderManager->AddRenderer(std::move(TestRenderer1));
	m_prmRenderManager->AddRenderer(std::move(TestRenderer3));

	m_prmRenderManager->Init(m_strApplicationName, HC_ENGINE_VERSION, m_wWindow.GetNativeWindowHandle());
}

void UICreationToolApplication::Run() {
	this->Start();

	/*Font fFont = FontProcessor::ProcessFont("./Assets/Fonts/JetBrainsMono-Bold.ttf", 15);
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/JetBrainsMono-Bold15.hcgrf", fFont);
	fFont = FontProcessor::ProcessFont("./Assets/Fonts/arial.ttf", 32);
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/arial32.hcgrf", fFont);
	fFont = FontProcessor::ProcessFont("./Assets/Fonts/Sniglet.ttf");
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/sniglet12.hcgrf", fFont);
	fFont = FontProcessor::ProcessFont("./Assets/Fonts/RobotoSlab-Bold.ttf", 60);
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/RobotoSlab-Bold60.hcgrf", fFont);
	fFont = FontProcessor::ProcessFont("./Assets/Fonts/calibri.ttf");
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/calibri12.hcgrf", fFont);
	fFont = FontProcessor::ProcessFont("./Assets/Fonts/Envy Code R.ttf");
	FontProcessor::SaveFontToDisk("./Assets/Fonts/TestOutput/Envy_Code_R12.hcgrf", fFont);*/

	auto aJetBrains = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/JetBrainsMono-Bold15.hcgrf"));
	auto aArial = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/arial32.hcgrf"));
	auto aSniglet = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/sniglet12.hcgrf"));
	auto aRobotoSlab = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/RobotoSlab-Bold60.hcgrf"));
	auto aCalibri = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/calibri12.hcgrf"));
	auto aEnvyCode = m_pamAssetManager->GetAsset(HCUID::ConstructFromFilepath("./Assets/Fonts/TestOutput/Envy_Code_R12.hcgrf"));

	/*while (!m_wWindow.CloseRequested()) {
		m_wWindow.PollEvents();
	}*/

	m_prmRenderManager->RenderFrame();

	this->End();
}

void UICreationToolApplication::End() {
	m_pamAssetManager->Cleanup();
	m_prmRenderManager->Cleanup();

	m_wWindow.Cleanup();
}