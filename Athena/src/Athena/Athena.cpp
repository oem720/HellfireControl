
#include <iostream>

#include <Athena/Core/UnitTesterApplication.hpp>

int main() {
	UnitTesterApplication appAthena;
	appAthena.Start();
	appAthena.Run();
	appAthena.End();

	return 0;
}