
#include <ShaderCompiler/Core/ShaderCompApplication.hpp>

int main() {
	ShaderCompApplication appShader;

	try {
		appShader.Run();
	}
	catch (const std::exception& _exError) {
		std::cerr << _exError.what() << std::endl;
		return -1;
	}

	return 0;
}