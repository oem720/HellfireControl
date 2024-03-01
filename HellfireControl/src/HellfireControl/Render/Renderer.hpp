#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Matrix.hpp>

#include <HellfireControl/Render/Buffer.hpp>

struct UniformBufferData {
	MatrixF m_mModel;
	MatrixF m_mView;
	MatrixF m_mProj;
};

class RenderingSubsystem {
private:
	std::vector<BufferHandleGeneric> m_vActiveBuffers;

	static RenderingSubsystem* m_prsInstancePtr;

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName, uint64_t _u64WindowHandle);

	void RenderFrame();

	void Cleanup();

	void RegisterBuffer(const BufferHandleGeneric& _bhgNewBuffer);

	void DeregisterBuffer(const BufferHandleGeneric& _bhgNewBuffer);
};