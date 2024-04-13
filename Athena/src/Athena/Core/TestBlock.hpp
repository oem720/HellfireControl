#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <Athena/Core/TestCase.hpp>

class TestBlock {
private:
	std::string m_strBlockName;
	std::vector<TestCase> m_vTests;

	float m_fAverageExecutionTimeNs = 0.0f;

	size_t m_sFastestFuncNdx = 0;
	size_t m_sSlowestFuncNdx = 0;

	uint64_t m_u32SuccessfulTests = 0u;
public:
	TestBlock() : m_strBlockName("DEFAULT"), m_vTests() {}
	TestBlock(const std::string& _strName) : m_strBlockName(_strName), m_vTests() {}

	void AddTest(const TestCase& _tcUnitTest);
	void AddTest(const std::string& _strFuncName, const std::function<const bool(float&)>& _funcTest);

	void ExecuteTests();

	void ClearResults();

	void ClearBlock();
	
	[[nodiscard]] HC_INLINE float GetAverageExecutionTimeNanoseconds() const { return m_fAverageExecutionTimeNs; }
	[[nodiscard]] HC_INLINE float GetAverageExecutionTimeMilliseconds() const { return m_fAverageExecutionTimeNs / 1.0E6f; }
	[[nodiscard]] HC_INLINE float GetAverageExecutionTimeSeconds() const { return m_fAverageExecutionTimeNs / 1.0E9f; }

	[[nodiscard]] HC_INLINE TestCase* GetFastestTestCase() { return m_vTests.size() > 0 ? &m_vTests[m_sFastestFuncNdx] : nullptr; }
	[[nodiscard]] HC_INLINE TestCase* GetSlowestTestCase() { return m_vTests.size() > 0 ? &m_vTests[m_sSlowestFuncNdx] : nullptr; }

	[[nodiscard]] HC_INLINE uint64_t GetSuccessfulTestCount() const { return m_u32SuccessfulTests; }
	[[nodiscard]] HC_INLINE uint64_t GetTestCount() const { return m_vTests.size(); }
};