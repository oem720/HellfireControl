
#include <Athena/Tests/Tests.hpp>

#include <Athena/Core/Util.hpp>

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>

#include <Athena/Tests/Inits/Math.hpp>

#include <chrono>


namespace Tests {
	void InitTests(std::vector<TestBlock>& _vBlockList) {
		Math::InitTests(_vBlockList);
	}
}