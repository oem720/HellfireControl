#pragma once

#include <HellfireControl/Core/Common.hpp>

class RenderingSubsystem {
private:
	static RenderingSubsystem* m_prsInstancePtr;

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName, uint64_t _u64WindowHandle);

	void Cleanup();
};