#pragma once

#include <HellfireControl/Core/Application.hpp>

#include <Athena/Core/TestBlock.hpp>

class UnitTesterApplication : public Application {
private:
	/// <summary>
	/// The overall average execution time for functions
	/// </summary>
	float m_fAverageExecutionTimeMs = 0.0f;

	/// <summary>
	/// The slowest execution time of the current block
	/// </summary>
	float m_fSlowestExecutionTimeMs = 0.0f;

	/// <summary>
	/// The fastest execution time of the current block
	/// </summary>
	float m_fFastestExecutionTimeMs = 0.0f;

	/// <summary>
	/// The name of the slowest function of the current block
	/// </summary>
	std::string m_strSlowestFuncName = "";

	/// <summary>
	/// The name of the fastest function of the current block
	/// </summary>
	std::string m_strFastestFuncName = "";

	/// <summary>
	/// The unit test blocks to be executed
	/// </summary>
	std::vector<TestBlock> m_vTestBlocks;
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	UnitTesterApplication() : Application("Athena Unit Tester", AppType::CONSOLE), m_vTestBlocks() {}

	/// <summary>
	/// Calls all init functions for test initialization.
	/// </summary>
	virtual void Start() override;

	/// <summary>
	/// Executes all unit tests and displays results.
	/// </summary>
	void Run();

	/// <summary>
	/// Finishes output of data to the profiler file and gracefully exits.
	/// </summary>
	virtual void End() override;

private:
	/// <summary>
	/// Helper function to easily display to the console the profiled data.
	/// </summary>
	void DisplayProfiledResults();
};