#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Concurrency/Job.hpp>

class JobQueue {
private:
	std::queue<std::shared_ptr<Job>> m_qJobs;
	std::mutex m_mutLock;

	std::condition_variable m_cvJobsCheck;

public:
	JobQueue() : m_qJobs(), m_mutLock() {}

	void AddJob(std::shared_ptr<Job> _pJob);

	std::shared_ptr<Job> PopJob();

	[[nodiscard]] HC_INLINE bool Empty() {
		std::lock_guard<std::mutex> lgLock(m_mutLock);
		return m_qJobs.size() == 0;
	}

	HC_INLINE void WakeSleepers() {
		m_cvJobsCheck.notify_all();
	}
};