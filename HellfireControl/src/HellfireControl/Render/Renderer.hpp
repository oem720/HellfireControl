#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Matrix.hpp>

#include <HellfireControl/Render/Buffer.hpp>
#include <HellfireControl/Render/RenderContext.hpp>

struct UniformBufferData {
	MatrixF m_mModel;
	MatrixF m_mView;
	MatrixF m_mProj;
};

class RenderingSubsystem {
private:
	std::vector<RenderContext> m_vRenderContexts;

	uint32_t m_u32NewRenderContextID = 0;

	static RenderingSubsystem* m_prsInstancePtr;

	std::vector<std::string> GetShaderFileNames(uint8_t _rctType); //TEMPORARY ! ! ! WILL BE REPLACED WITH READING FROM AN INI FILE

	RenderingSubsystem() {}
public:
	static RenderingSubsystem* GetInstance();

	void Init(const std::string& _strAppName, uint64_t _u64WindowHandle, uint8_t _u8ActiveContextIDs);

	void RenderFrame();

	void Cleanup();

	void RegisterRenderContext(const RenderContext& _rcContext, uint8_t _u8PreceedingContextCount = UINT8_MAX);

	[[nodiscard]] const Vec2F GetRenderableExtents();

	[[nodiscard]] const uint32_t GetRenderContextID(uint8_t _rctType);
};