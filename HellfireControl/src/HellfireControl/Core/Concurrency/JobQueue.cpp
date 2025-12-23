
#include <HellfireControl/Core/Concurrency/JobQueue.hpp>

void JobQueue::AddJob(Shared<Job> _pJob) {
	std::lock_guard<Mutex> lgLock(m_mutLock);

	m_qJobs.push(_pJob);

	m_cvJobsCheck.notify_one();
}

Shared<Job> JobQueue::PopJob() {
	std::unique_lock<Mutex> ulLock(m_mutLock);
	m_cvJobsCheck.wait(ulLock, [&] { return !m_qJobs.empty(); });

	Shared<Job> pJob = m_qJobs.front();
	m_qJobs.pop();
	return pJob;
}
