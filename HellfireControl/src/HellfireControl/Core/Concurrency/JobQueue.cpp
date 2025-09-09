
#include <HellfireControl/Core/Concurrency/JobQueue.hpp>

void JobQueue::AddJob(std::shared_ptr<Job> _pJob) {
	std::lock_guard<std::mutex> lgLock(m_mutLock);

	m_qJobs.push(_pJob);

	m_cvJobsCheck.notify_one();
}

std::shared_ptr<Job> JobQueue::PopJob() {
	std::unique_lock<std::mutex> ulLock(m_mutLock);
	m_cvJobsCheck.wait(ulLock, [&] { return !m_qJobs.empty(); });

	std::shared_ptr<Job> pJob = m_qJobs.front();
	m_qJobs.pop();
	return pJob;
}
