#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/Concurrency/Job.hpp>
#include <HellfireControl/Core/Concurrency/JobQueue.hpp>

class JobManager {
private:
	std::vector<std::thread> m_vWorkerPool;

	std::atomic<size_t> m_asBlockedThreads = 0;
	std::atomic<size_t> m_asBusyThreads = 0;

	JobQueue m_jqQueue;

	std::condition_variable m_cvDependencyCheck;
	std::mutex m_mutDependencyMutex;

	void WorkerExecute();

	void Poll();

public:
	JobManager() = delete;

	JobManager(uint32_t _u32WorkerCount);

	void AddJob(std::shared_ptr<Job> _pJob);

	bool CheckBusyStatus();

	void BlockUntilQueueClear();
};