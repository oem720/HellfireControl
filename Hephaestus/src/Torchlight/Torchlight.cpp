#include <iostream>

#include <Torchlight/Core/UICreationToolApplication.hpp>

int main() {
	UICreationToolApplication appTorchlight;
	appTorchlight.Start();
	appTorchlight.Run();
	appTorchlight.End();

	return 0;
}