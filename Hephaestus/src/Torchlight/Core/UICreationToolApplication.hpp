#pragma once

#include <HellfireControl/Core/Application.hpp>

class UICreationToolApplication : public Application {
private:
	//TODO Add private members here

public:

	UICreationToolApplication() : Application("Torchlight", AppType::WINDOWED) {}

	void Start();

	void Run();

	void End();
};