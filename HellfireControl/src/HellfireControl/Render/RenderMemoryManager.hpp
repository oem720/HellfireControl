#pragma once

#include <HellfireControl/Core/Common.hpp>

typedef uint32 BufferHandle;

enum BufferType : uint32 {
	BUFFER_TYPE_UNIFORM_TEXEL = (1 << 2),
	BUFFER_TYPE_STORAGE_TEXEL = (1 << 3),
	BUFFER_TYPE_UNIFORM = (1 << 4),
	BUFFER_TYPE_STORAGE = (1 << 5),
	BUFFER_TYPE_INDEX = (1 << 6),
	BUFFER_TYPE_VERTEX = (1 << 7),
};

class RenderMemoryManager {
private:
	typedef uint32 AllocationOffset;
	
	struct Allocation {
		uint32 m_u32Size;
		bool m_bFree;
	};

	uint32 m_u32TotalMemorySize = 0;

	static Map<AllocationOffset, Allocation> m_mAllocations;

	static RenderMemoryManager* m_prmmInstance;

	void InitPlatformMemoryPool();
	void CleanupPlatformMemoryPool();

	RenderMemoryManager() = default;

public:
	RenderMemoryManager(RenderMemoryManager& _other) = delete;

	void operator=(const RenderMemoryManager& _other) = delete;

	static RenderMemoryManager* GetInstance();

	void Init(uint32 _u32InitialMemoryPool);

	void Grow(); //TODO: Move to being private after testing is complete.

	BufferHandle CreateBuffer(BufferType _btType, uint32 _u32Size, const void* _pData);
	BufferHandle CreateBuffer(BufferType _btType, uint32 _u32Size);

	void UploadData(BufferHandle _bhBuffer, uint32 _u32Size, const void* _pData);
	void DeleteData(BufferHandle _bhBuffer, uint32 _u32Offset);

	void DestroyBuffer(BufferHandle _bhBuffer);

	void Cleanup();
};