
#include <Athena/Tests/Tests.hpp>

#include <Athena/Core/Util.hpp>

#include <HellfireControl/Core/Common.hpp>

#include <Athena/Tests/Inits/Math.hpp>


namespace Tests {
	void InitTests(std::vector<TestBlock>& _vBlockList) {
		Math::InitTests(_vBlockList);
	}
}