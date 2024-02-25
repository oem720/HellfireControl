#include <iostream>
#include <stdexcept>

#include <Torchlight/Core/UICreationToolApplication.hpp>
#include <HellfireControl/UI/UI.hpp>

int main() {
	UICreationToolApplication appTorchlight;

	try {
		appTorchlight.Run();
	}
	catch (const std::exception& _exError) {
		std::cerr << _exError.what() << std::endl;
		return -1;
	}

	return 0;
}