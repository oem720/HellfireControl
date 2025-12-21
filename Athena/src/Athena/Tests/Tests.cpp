
#include <Athena/Tests/Tests.hpp>

#include <Athena/Core/Util.hpp>

#include <HellfireControl/Core/Common.hpp>

#include <Athena/Tests/Inits/Math.hpp>


namespace Tests {
	void InitTests(Array<TestBlock>& _vBlockList) {
		MathTests::InitTests(_vBlockList);
	}
}