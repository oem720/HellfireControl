
#include <Athena/Core/Util.hpp>

namespace Util {
	void PauseForUserConfirmation() {

	}

	void Wait(uint32_t _u32Time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(_u32Time));
	}
}