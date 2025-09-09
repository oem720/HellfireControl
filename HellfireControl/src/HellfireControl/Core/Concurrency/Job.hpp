#pragma once

#include <HellfireControl/Core/Common.hpp>

enum JobStatus : uint8_t {
	IDLING,
	ASSIGNED,
	RUNNING,
	COMPLETED,
	ERROR,
	CANCELLED
};

struct Job {
	std::function<void()> m_funcJobAction;
	std::vector<std::shared_ptr<Job>> m_vDependencies;
	std::atomic<JobStatus> m_jsStatus;

	Job() = delete;

	Job(std::function<void()> _funcJob, const std::vector<std::shared_ptr<Job>>& _vDependencies = std::vector<std::shared_ptr<Job>>()) 
		: m_funcJobAction(_funcJob), m_vDependencies(_vDependencies), m_jsStatus(IDLING) {}

	bool Ready() {
		for (const auto& aJob : m_vDependencies) {
			switch (aJob->m_jsStatus) {
			case ERROR:
			case CANCELLED:
				throw std::runtime_error("ERROR: Job cannot be handled! Dependencies failed!"); //TODO Make more robust.
				break;

			case COMPLETED:
				break;

			default:
				return false;
			}
		}

		return true;
	}
};