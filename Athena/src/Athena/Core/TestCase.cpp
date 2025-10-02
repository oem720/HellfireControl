
#include <Athena/Core/TestCase.hpp>
#include <Athena/Core/Util.hpp>

void TestCase::ExecuteTest() {
	Console::Print("\nExecuting function: " + m_strFuncName + "\n"); //Display the current test

	m_bPass = m_funcTest(m_fExecTimeNs); //Execute the test

	Console::Print("Results: "); 
	m_bPass ? Console::Print("Succeeded\n", GREEN) : Console::Print("Failed\n", RED); //PrintDebugMessage the results

	Console::Print("Time to execute (ns): ");
	Console::Print(std::to_string(m_fExecTimeNs) + " ns\n", YELLOW); //PrintDebugMessage time in ns

	Console::Print("Time to execute (ms): ");
	Console::Print(std::to_string(GetExecutionTimeMilliseconds()) + " ms\n", YELLOW); //PrintDebugMessage time in ms

	Console::Print("Time to execute (s): ");
	Console::Print(std::to_string(GetExecutionTimeSeconds()) + " s\n", YELLOW); //PrintDebugMessage time in s
}