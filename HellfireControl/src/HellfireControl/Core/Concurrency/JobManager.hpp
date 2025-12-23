#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Concurrency/Job.hpp>
#include <HellfireControl/Core/Concurrency/JobQueue.hpp>

class JobManager {
private:
	Array<Thread> m_vWorkerPool;

	std::atomic<size_t> m_asBlockedThreads = 0;
	std::atomic<size_t> m_asBusyThreads = 0;

	JobQueue m_jqQueue;

	ConditionVariable m_cvDependencyCheck;
	Mutex m_mutDependencyMutex;

	void WorkerExecute();

	void Poll();

public:
	JobManager() = delete;

	JobManager(uint32 _u32WorkerCount);

	void AddJob(Shared<Job> _pJob);

	bool CheckBusyStatus();

	void BlockUntilQueueClear();
};