#pragma once

#include <Platform/GLCommon.hpp>

#include <Platform/Vulkan/VkBufferBuilder.hpp>

#include <HellfireControl/Asset/Mesh.hpp>

class VkMeshManager {
private:
	static VkBufferData m_bd2DVertexBuffer;
	static VkBufferData m_bd3DVertexBuffer;
	static VkBufferData m_bdIndexBuffer;

public:
	static void Init(const Array<Vertex2D>& _v2DVertices, const Array<Vertex3D>& _v3DVertices, const Array<uint32>& _vIndices);
	static void Cleanup();
};