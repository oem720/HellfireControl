
#include <HellfireControl/Core/Console.hpp>

#include <ShaderCompiler/Core/ShaderCompApplication.hpp>

int main(int argc, char* argv[]) {
	std::vector<std::string> vArgs(argc - 1);

	for (int iNdx = 1; iNdx < argc; ++iNdx) {
		vArgs[iNdx - 1] = std::string(argv[iNdx]);
	}

	ShaderCompApplication appShader(vArgs);

	try {
		appShader.Run();
	}
	catch (const std::exception& _exError) {
		Console::DebugError(_exError.what());
		return -1;
	}

	return 0;
}