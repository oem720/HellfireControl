#pragma once

#include <HellfireControl/Core/Common.hpp>

class RenderingSubsystem {
private:
	static RenderingSubsystem* m_prsInstancePtr;

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName);

	void Cleanup();
};