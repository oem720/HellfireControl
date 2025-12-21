
#include <HellfireControl/Core/Concurrency/JobManager.hpp>

JobManager::JobManager(uint32 _u32WorkerCount) {
	uint32 u32WorkerCount = HC_MIN(_u32WorkerCount, HC_ABSOLUTE_THREAD_MAX);

	for (uint32 u32Count = 0; u32Count < u32WorkerCount; ++u32Count) {
		m_vWorkerPool.push_back(Thread(&JobManager::WorkerExecute, this));
		m_vWorkerPool[u32Count].detach();
	}
}

void JobManager::AddJob(SharedPointer<Job> _pJob) {
	m_jqQueue.AddJob(_pJob);

	Poll();
}

bool JobManager::CheckBusyStatus() {
	return m_asBusyThreads > 0 && m_asBlockedThreads > 0;
}

void JobManager::BlockUntilQueueClear() {
	while (CheckBusyStatus()) {
		Poll();
	}
}

void JobManager::WorkerExecute() {
	SharedPointer<Job> pJob = nullptr;

	while (true) {
		if (pJob == nullptr) {
			pJob = m_jqQueue.PopJob();
			pJob->m_jsStatus = ASSIGNED;
			++m_asBlockedThreads;
		}
		
		if (pJob->Ready()) {
			pJob->m_jsStatus = RUNNING;
			--m_asBlockedThreads;
			++m_asBusyThreads;

			try {
				pJob->m_funcJobAction();
			}
			catch (const std::exception& eError) {
				std::cout << "Thread returned an error: " << eError.what() << "\n";
				pJob->m_jsStatus = ERROR;
				continue;
			}
				
			pJob->m_jsStatus = COMPLETED;
			--m_asBusyThreads;
			pJob = nullptr;

			m_cvDependencyCheck.notify_all(); //Notify those who are waiting on a dependency to check if they're ready
		}
		else {
			if (m_asBlockedThreads == m_vWorkerPool.size()) { //Deadlock detected, return this job to the queue and try again.
				m_jqQueue.AddJob(pJob);
				pJob = nullptr;
			}
			else {
				std::unique_lock<Mutex> ulLock(m_mutDependencyMutex);
				m_cvDependencyCheck.wait(ulLock, [&] { return pJob->Ready(); });
			}
		}
	}
}

void JobManager::Poll() {
	m_jqQueue.WakeSleepers();
	std::this_thread::yield();
}
