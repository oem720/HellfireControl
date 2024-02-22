#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Vector.hpp>

#include <Platform/GLInclude.hpp> //TEMPORARY ! ! ! HACK FOR VERTICES, MOVE VERTEX TYPES TO THEIR OWN FILE LATER AND ELIMINATE THIS GARBAGE ! ! !

class RenderingSubsystem {
private:

	static RenderingSubsystem* m_prsInstancePtr;

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName, uint64_t _u64WindowHandle);

	void RenderFrame();

	void Cleanup();
};