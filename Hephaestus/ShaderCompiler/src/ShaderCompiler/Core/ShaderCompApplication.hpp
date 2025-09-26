#pragma once

#include <HellfireControl/Core/Application.hpp>

class ShaderCompApplication : public Application {
private:
	void Start();

	void End();

public:
	ShaderCompApplication() : Application("HC Shader Compiler", AppType::CONSOLE) {}

	void Run();
};