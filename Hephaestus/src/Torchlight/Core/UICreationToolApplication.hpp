#pragma once

#include <HellfireControl/Core/Application.hpp>

class RenderManager;
class AssetManager;

class UICreationToolApplication : public Application {
private:
	RenderManager* m_prmRenderManager = nullptr;
	AssetManager* m_pamAssetManager = nullptr;

	void Start();

	void End();

public:
	UICreationToolApplication() : Application("Torchlight", AppType::WINDOWED) {}

	void Run();
};