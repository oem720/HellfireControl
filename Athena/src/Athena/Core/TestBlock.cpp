
#include <Athena/Core/TestBlock.hpp>
#include <Athena/Core/Util.hpp>

void TestBlock::AddTest(const TestCase& _tcUnitTest) {
	m_vTests.push_back(_tcUnitTest);
}

void TestBlock::AddTest(const std::string& _strFuncName, const std::function<const bool(float&)>& _funcTest) {
	m_vTests.push_back(TestCase(_strFuncName, _funcTest));
}

void TestBlock::ExecuteTests() {
	//Execute every test, summing their execution time in NS to average later.
	for (int ndx = 0; ndx < m_vTests.size(); ++ndx) {
		m_vTests[ndx].ExecuteTest();

		float fExecTime = m_vTests[ndx].GetExecutionTimeNanoseconds();

		m_fAverageExecutionTimeNs += fExecTime;

		if (fExecTime < m_vTests[m_sFastestFuncNdx].GetExecutionTimeNanoseconds()) {
			m_sFastestFuncNdx = ndx;
		}

		if (fExecTime > m_vTests[m_sSlowestFuncNdx].GetExecutionTimeNanoseconds()) {
			m_sSlowestFuncNdx = ndx;
		}

		if (m_vTests[ndx].Passed()) {
			++m_u32SuccessfulTests;
		}
	}

	m_fAverageExecutionTimeNs /= static_cast<float>(m_vTests.size()); //Average the execution time

	Console::Print("\nTesting of block \"" + m_strBlockName + "\" complete. Outputting results:\n");
	
	Console::Print("Successful tests: "); 
	Console::Print(std::to_string(m_u32SuccessfulTests), m_u32SuccessfulTests == m_vTests.size() ? Console::GREEN : Console::RED); //Print the number of tests that passed
	Console::Print(" out of " + std::to_string(m_vTests.size()) + "\n");

	Console::Print("Average time to execute (ns): ");
	Console::Print(std::to_string(m_fAverageExecutionTimeNs) + " ns\n", Console::YELLOW); //Print time in ns

	Console::Print("Average time to execute (ms): ");
	Console::Print(std::to_string(GetAverageExecutionTimeMilliseconds()) + " ms\n", Console::YELLOW); //Print time in ms

	Console::Print("Average time to execute (s): ");
	Console::Print(std::to_string(GetAverageExecutionTimeSeconds()) + " s\n", Console::YELLOW); //Print time in s
}

void TestBlock::ClearResults() {
	m_fAverageExecutionTimeNs = 0.0f;
	m_u32SuccessfulTests = 0u;
}

void TestBlock::ClearBlock() {
	m_vTests.clear();
}