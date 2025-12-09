
#include <Torchlight/Core/UICreationToolApplication.hpp>

#include <HellfireControl/Core/Console.hpp>

int main() {
	UICreationToolApplication appTorchlight;

	try {
		appTorchlight.Run();
	}
	catch (const std::exception& _exError) {
		Console::DebugError(_exError.what());
		return -1;
	}

	return 0;
}