
#include <Athena/Core/UnitTesterApplication.hpp>
#include <Athena/Core/Util.hpp>

#include <Athena/Tests/Tests.hpp>

void UnitTesterApplication::Start() {
	this->Application::Start();

	//Call the overarching Init function
	Tests::InitTests(m_vTestBlocks);
}

void UnitTesterApplication::Run() {
	uint32_t u32Successes = 0;
	uint32_t u32TotalTests = 0;

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
		
		u32Successes += m_vTestBlocks[ndx].GetSuccessfulTestCount();
		u32TotalTests += m_vTestBlocks[ndx].GetTestCount();

		DisplayProfiledResults(); //Display profiled results from math

		m_vTestBlocks[ndx].ClearBlock(); //Free Test Memory

		//Pause for 1 second before continuing testing. May replace with waiting for confirmation from user. Do this if and only if we aren't on the last block.
		if (ndx < m_vTestBlocks.size() - 1) {
			Util::Wait(1000);
			//Util::PauseForUserConfirmation();
		}
	}

	//Average the total execution time
	m_fAverageExecutionTimeMs /= static_cast<float>(m_vTestBlocks.size());

	//Display the overall succeeded tests, overall test count, overall average speed, fastest function/time, slowest function/time
	Console::Print("\n\nOverall Results\n---------------\n");

	Console::Print("Successful tests: ");
	Console::Print(std::to_string(u32Successes), u32Successes == u32TotalTests ? Console::GREEN : Console::RED);
	Console::Print(" out of " + std::to_string(u32TotalTests) + "\n");

	Console::Print("Overall Average Speed: ");
	Console::Print(std::to_string(m_fAverageExecutionTimeMs), Console::YELLOW);
	Console::Print(" ms\n");
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