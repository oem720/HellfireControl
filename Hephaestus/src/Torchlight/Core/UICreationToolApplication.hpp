#pragma once

#include <HellfireControl/Core/Application.hpp>

class RenderingSubsystem;

class UICreationToolApplication : public Application {
private:
	RenderingSubsystem* m_prsRenderHandle = nullptr;

	void Start();

	void End();

public:

	UICreationToolApplication() : Application("Torchlight", AppType::WINDOWED) {}

	void Run();
};