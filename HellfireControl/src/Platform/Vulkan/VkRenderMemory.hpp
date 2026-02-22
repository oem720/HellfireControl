#pragma once

#include <Platform/GLCommon.hpp>

class VkRenderMemoryChunk : public PlatformRenderMemoryChunk {
public:
	void Init(uint32 _u32Size, RenderMemoryType _rmtType);
	void Write(uint64 _u64Size, uint64 _u64Offset, const void* _pData);
	void Free();
};