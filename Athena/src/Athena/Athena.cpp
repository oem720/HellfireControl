#include <iostream>
#include <stdexcept>

#include <Athena/Core/UnitTesterApplication.hpp>

int main() {
	UnitTesterApplication appAthena;

	try {
		appAthena.Run();
	}
	catch (const std::exception& _exError) {
		std::cerr << _exError.what() << std::endl;
		return -1;
	}

	return 0;
}