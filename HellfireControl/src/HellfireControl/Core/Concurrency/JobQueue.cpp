
#include <HellfireControl/Core/Concurrency/JobQueue.hpp>

void JobQueue::AddJob(SharedPointer<Job> _pJob) {
	std::lock_guard<Mutex> lgLock(m_mutLock);

	m_qJobs.push(_pJob);

	m_cvJobsCheck.notify_one();
}

SharedPointer<Job> JobQueue::PopJob() {
	std::unique_lock<Mutex> ulLock(m_mutLock);
	m_cvJobsCheck.wait(ulLock, [&] { return !m_qJobs.empty(); });

	SharedPointer<Job> pJob = m_qJobs.front();
	m_qJobs.pop();
	return pJob;
}
