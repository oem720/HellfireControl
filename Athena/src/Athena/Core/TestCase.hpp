#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <functional>

class TestCase {
private:
	/// <summary>
	/// Variable to store whether or not the function passed its test.
	/// </summary>
	bool m_bPass = false;

	/// <summary>
	/// Variable to store the execution time in nanoseconds.
	/// </summary>
	float m_fExecTimeNs = 0.0f;

	/// <summary>
	/// The name of the function being tested. This will be replaced with an HC String when completed
	/// </summary>
	std::string m_strFuncName;

	/// <summary>
	/// The actual unit test being performed. This will be replaced with an HC Function when completed
	/// </summary>
	std::function<const bool(float&)> m_funcTest;
public:
	/// <summary>
	/// Default constructor has been deleted, as there is no need for one.
	/// </summary>
	TestCase() = delete;

	/// <summary>
	/// Constructor for the unit test.
	/// </summary>
	/// <param name="_strFuncName: Name of the function being tested"></param>
	/// <param name="_funcTest: The unit test supplied by the test system"></param>
	explicit TestCase(const std::string& _strFuncName, const std::function<const bool(float&)> _funcTest) : m_strFuncName(_strFuncName), m_funcTest(_funcTest) {}

	/// <summary>
	/// Executes the stored unit test and displays the results.
	/// </summary>
	void ExecuteTest();

	/// <summary>
	/// Returns the time to execute the function being tested in nanoseconds
	/// </summary>
	/// <returns>
	/// float: The time in nanoseconds to execute the test function
	/// </returns>
	[[nodiscard]] HC_INLINE float GetExecutionTimeNanoseconds() const { return m_fExecTimeNs; }

	/// <summary>
	/// Returns the time to execute the function being tested in milliseconds
	/// </summary>
	/// <returns>
	/// float: The time in milliseconds to execute the test function
	/// </returns>
	[[nodiscard]] HC_INLINE float GetExecutionTimeMilliseconds() const { return m_fExecTimeNs / 1.0E6f; }

	/// <summary>
	/// Returns the time to execute the function being tested in seconds
	/// </summary>
	/// <returns>
	/// float: The time in seconds to execute the test function
	/// </returns>
	[[nodiscard]] HC_INLINE float GetExecutionTimeSeconds() const { return m_fExecTimeNs / 1.0E9f; }

	[[nodiscard]] HC_INLINE std::string& GetFunctionName() { return m_strFuncName; }

	/// <summary>
	/// Returns whether or not the function passed its unit test
	/// </summary>
	/// <returns>
	/// bool: True if the function passed, false if failed.
	/// </returns>
	[[nodiscard]] HC_INLINE bool Passed() const { return m_bPass; }
};