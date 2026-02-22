#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Singleton.hpp>

enum RenderMemoryType : uint8 {
	RENDER_MEMORY_DEVICE_LOCAL,
	RENDER_MEMORY_HOST_ACCESSIBLE,
	RENDER_MEMORY_TRANSIENT,
	RENDER_MEMORY_READBACK
};

class PlatformRenderMemoryChunk {
public:
	virtual void Init(uint32 _u32Size, RenderMemoryType _rmtType) = 0;
	virtual void Write(uint64 _u64Size, uint64 _u64Offset, const void* _pData) = 0;
	virtual void Free() = 0;
};

class RenderMemoryChunk {
private:
	Unique<PlatformRenderMemoryChunk> m_pPlatformAllocation;

	uint32 m_u32Size = 0;
public:
	RenderMemoryChunk() = default;

	void Init(uint32 _u32Size, RenderMemoryType _rmtType);
	void Free();

	const Unique<PlatformRenderMemoryChunk>& GetPlatformAllocation() { return m_pPlatformAllocation; }

private:
	static Unique<PlatformRenderMemoryChunk> CreatePlatformMemoryChunk();
};

struct RenderMemoryAllocation {
	uint64 m_u64Size = 0;
	uint64 m_u64Offset = 0;
	uint32 m_u32ChunkId = 0;
	RenderMemoryType m_rmtPoolType = RENDER_MEMORY_TRANSIENT;
};

class RenderMemoryPool {
private:
	Map<uint32, Unique<RenderMemoryChunk>> m_mChunks;

	uint32 m_u32ChunkIDCounter = 0;
	RenderMemoryType m_rmtPoolType = RENDER_MEMORY_TRANSIENT;
public:
	RenderMemoryPool() = delete;
	RenderMemoryPool(RenderMemoryType _rmtPoolType) : m_rmtPoolType(_rmtPoolType) {}

	void Init();
	void Cleanup();

	RenderMemoryAllocation Allocate(uint64 _u64Size);
	void Write(uint64 _u64Size, const void* _pData, const RenderMemoryAllocation& _rmaAllocation);
	void Free(const RenderMemoryAllocation& _rmaAllocation);
};

class RenderMemoryAllocator : public Singleton<RenderMemoryAllocator> {
private:
	Map<uint32, RenderMemoryAllocation> m_mAllocations;

	Unique<RenderMemoryPool> m_pDeviceLocalMemoryPool;
	Unique<RenderMemoryPool> m_pHostAccessibleMemoryPool;
	Unique<RenderMemoryChunk> m_pTransientMemory;

	static uint32 m_u32AllocationIDCounter;
	static uint32 m_u32AllocationLimit;
	static uint64 m_u64Granularity;
public:
	void Init();
	void Cleanup();

	uint32 Allocate(uint64 _u64Size, RenderMemoryType _rmtType);
	uint32 Write(uint64 _u64Size, const void* _pData, RenderMemoryType _rmtType);
	void Write(uint64 _u64Size, const void* _pData, uint32 _u32AllocationId);
	void Free(uint32 _u32AllocationId);

private:
	RenderMemoryAllocator() {}

	void SetAllocationLimitAndGranularity(uint32 _u32AllocationLimit, uint64 _u64Granularity);

	friend class Singleton<RenderMemoryAllocator>;
	friend class RenderManager;
};