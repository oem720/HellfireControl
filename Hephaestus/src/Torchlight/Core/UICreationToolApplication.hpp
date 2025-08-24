#pragma once

#include <HellfireControl/Core/Application.hpp>

class RenderingSubsystem;
class AssetManager;

struct BufferHandleGeneric;

class UICreationToolApplication : public Application {
private:
	RenderingSubsystem* m_prsRenderer = nullptr;
	AssetManager* m_pamManager = nullptr;

	void Start();

	void End();

	void UpdateUniformBuffer(const BufferHandleGeneric& _bhgHandle);

public:

	UICreationToolApplication() : Application("Torchlight", AppType::WINDOWED) {}

	void Run();
};