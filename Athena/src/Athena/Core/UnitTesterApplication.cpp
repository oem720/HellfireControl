
#include <Athena/Core/UnitTesterApplication.hpp>
#include <Athena/Core/Util.hpp>

#include <Athena/Tests/Tests.hpp>

void UnitTesterApplication::Start() {
	this->Application::Start();

	//TODO: Whenever a new module needs to be added, create a header file with an init tests function that matches this signature.
	//Generate your tests and then add the new test block to the list passed in. Ensure to use a new namespace name to differentiate.

	Math::InitTests(m_vTestBlocks); //Math
}

void UnitTesterApplication::Run() {
	for (int ndx = 0; ndx < m_vTestBlocks.size(); ++ndx) {
		m_vTestBlocks[ndx].ExecuteTests(); //Run tests

		m_fAverageExecutionTimeMs += m_vTestBlocks[ndx].GetAverageExecutionTimeMilliseconds(); //Collect profiler data

		TestCase* tcTest = m_vTestBlocks[ndx].GetFastestTestCase();
		if (tcTest != nullptr) {
			m_fFastestExecutionTimeMs = tcTest->GetExecutionTimeMilliseconds();
			m_strFastestFuncName = tcTest->GetFunctionName();
		}

		tcTest = m_vTestBlocks[ndx].GetSlowestTestCase();
		if (tcTest != nullptr) {
			m_fSlowestExecutionTimeMs = tcTest->GetExecutionTimeMilliseconds();
			m_strSlowestFuncName = tcTest->GetFunctionName();
		}
		
		DisplayProfiledResults(); //Display profiled results from math

		//Pause for 2 seconds before continuing testing. May replace with waiting for confirmation from user. Do this if and only if we aren't on the last block.
		if (ndx < m_vTestBlocks.size() - 1) {
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

	//Average the total execution time
	m_fAverageExecutionTimeMs /= static_cast<float>(m_vTestBlocks.size());
}

void UnitTesterApplication::End() {
	this->Application::End();

	//TODO: Final cleanup and closing profiler file
}

void UnitTesterApplication::DisplayProfiledResults() {
	//Display fastest/slowest time for execution and the function names.
	Console::Print("Fastest function: ");
	Console::Print("\"" + m_strFastestFuncName + "\"", Console::GREEN);
	Console::Print(" -- ");
	Console::Print(std::to_string(m_fFastestExecutionTimeMs), Console::GREEN);
	Console::Print(" milliseconds");

	Console::Print("\nSlowest function: ");
	Console::Print("\"" + m_strSlowestFuncName + "\"", Console::RED);
	Console::Print(" -- ");
	Console::Print(std::to_string(m_fSlowestExecutionTimeMs), Console::RED);
	Console::Print(" milliseconds\n");

	//Write the function names to profiler file along with execution times.

	//Clear profiler data for next test batch
	m_fFastestExecutionTimeMs = 0.0f;
	m_fSlowestExecutionTimeMs = 0.0f;
	m_strFastestFuncName.clear();
	m_strSlowestFuncName.clear();
}