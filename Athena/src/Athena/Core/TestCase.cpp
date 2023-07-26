
#include <Athena/Core/TestCase.hpp>
#include <Athena/Core/Util.hpp>

void TestCase::ExecuteTest() {
	Console::Print("\nExecuting function: " + m_strFuncName + "\n"); //Display the current test

	m_bPass = m_funcTest(m_fExecTimeNs); //Execute the test

	Console::Print("Results: "); 
	m_bPass ? Console::Print("Succeeded\n", Console::GREEN) : Console::Print("Failed\n", Console::RED); //Print the results

	Console::Print("Time to execute (ns): ");
	Console::Print(std::to_string(m_fExecTimeNs) + " ns\n", Console::YELLOW); //Print time in ns

	Console::Print("Time to execute (ms): ");
	Console::Print(std::to_string(GetExecutionTimeMilliseconds()) + " ms\n", Console::YELLOW); //Print time in ms

	Console::Print("Time to execute (s): ");
	Console::Print(std::to_string(GetExecutionTimeSeconds()) + " s\n", Console::YELLOW); //Print time in s
}