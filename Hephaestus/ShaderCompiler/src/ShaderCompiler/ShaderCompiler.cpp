
#include <HellfireControl/Core/Console.hpp>

#include <ShaderCompiler/Core/ShaderCompApplication.hpp>

int main(int argc, char* argv[]) {
	ShaderCompApplication appShader(argc, argv);

	try {
		appShader.Run();
	}
	catch (const std::exception& _exError) {
		Console::DebugError(_exError.what());
		return -1;
	}

	return 0;
}