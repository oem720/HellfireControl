
#include <Torchlight/Core/UICreationToolApplication.hpp>
#include <HellfireControl/UI/UI.hpp>
#include <HellfireControl/UI/SDF.hpp>

int main() {
	UICreationToolApplication appTorchlight;

	try {
		SignedDistanceField reader;
		//reader.Bit();
		appTorchlight.Run();
	}
	catch (const std::exception& _exError) {
		std::cerr << _exError.what() << std::endl;
		return -1;
	}

	return 0;
}