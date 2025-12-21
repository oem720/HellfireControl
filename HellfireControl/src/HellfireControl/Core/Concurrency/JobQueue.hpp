#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Concurrency/Job.hpp>

class JobQueue {
private:
	Queue<SharedPointer<Job>> m_qJobs;
	Mutex m_mutLock;

	ConditionVariable m_cvJobsCheck;

public:
	JobQueue() : m_qJobs(), m_mutLock() {}

	void AddJob(SharedPointer<Job> _pJob);

	SharedPointer<Job> PopJob();

	[[nodiscard]] HC_INLINE bool Empty() {
		std::lock_guard<Mutex> lgLock(m_mutLock);
		return m_qJobs.size() == 0;
	}

	HC_INLINE void WakeSleepers() {
		m_cvJobsCheck.notify_all();
	}
};