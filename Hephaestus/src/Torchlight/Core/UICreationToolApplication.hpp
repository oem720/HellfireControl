#pragma once

#include <HellfireControl/Core/Application.hpp>

class RenderingSubsystem;

struct BufferHandleGeneric;

class UICreationToolApplication : public Application {
private:
	RenderingSubsystem* m_prsRenderer = nullptr;

	void Start();

	void End();

	void UpdateUniformBuffer(const BufferHandleGeneric& _bhgHandle);

public:

	UICreationToolApplication() : Application("Torchlight", AppType::WINDOWED) {}

	void Run();
};