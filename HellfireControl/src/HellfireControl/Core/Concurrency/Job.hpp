#pragma once

#include <HellfireControl/Core/Common.hpp>

enum JobStatus : uint8 {
	IDLING,
	ASSIGNED,
	RUNNING,
	COMPLETED,
	ERROR,
	CANCELLED
};

struct Job {
	Function<void()> m_funcJobAction;
	Array<Shared<Job>> m_vDependencies;
	std::atomic<JobStatus> m_jsStatus;

	Job() = delete;

	Job(Function<void()> _funcJob, const Array<Shared<Job>>& _vDependencies = Array<Shared<Job>>()) 
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