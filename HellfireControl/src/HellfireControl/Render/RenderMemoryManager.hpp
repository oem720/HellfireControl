#pragma once

#include <HellfireControl/Core/Common.hpp>

typedef uint32 BufferHandle;

class RenderMemoryManager {
private:
	static RenderMemoryManager* m_prmmInstance;

	RenderMemoryManager() = default;

public:
	RenderMemoryManager(RenderMemoryManager& _other) = delete;

	void operator=(const RenderMemoryManager& _other) = delete;

	static RenderMemoryManager* GetInstance();

	void Init(uint32 _u32InitialMemoryPool);

	void Cleanup();
};