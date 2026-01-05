
#include <HellfireControl/Render/Mesh/MeshManager.hpp>

#if HC_USE_VULKAN
#include <Platform/Vulkan/VkMeshManager.hpp>
#include <Platform/Vulkan/VkRenderManager.hpp>

VkBufferData VkMeshManager::m_bd2DVertexBuffer = {};
VkBufferData VkMeshManager::m_bd3DVertexBuffer = {};
VkBufferData VkMeshManager::m_bdIndexBuffer = {};

void MeshManager::SendToPlatform() {
	VkMeshManager::Init(m_v2DVertexBuffer, m_v3DVertexBuffer, m_vIndexBuffer);

	m_v2DVertexBuffer.clear();
	m_v3DVertexBuffer.clear();
	m_vIndexBuffer.clear();
}

void MeshManager::CleanupPlatformObjects() {
	VkMeshManager::Cleanup();
}

void VkMeshManager::Init(const Array<Vertex2D>& _v2DVertices, const Array<Vertex3D>& _v3DVertices, const Array<uint32>& _vIndices) {
	VkBufferBuilder bbBuilder;

	if (!_v2DVertices.empty()) {
		m_bd2DVertexBuffer = bbBuilder
			.SetBufferFlags(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
			.SetData(sizeof(Vertex2D) * _v2DVertices.size(), _v2DVertices.data())
			.Build();
	}

	if (!_v3DVertices.empty()) {
		m_bd3DVertexBuffer = bbBuilder
			.SetBufferFlags(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
			.SetData(sizeof(Vertex3D) * _v3DVertices.size(), _v3DVertices.data())
			.Build();
	}

	if (!_vIndices.empty()) {
		m_bdIndexBuffer = bbBuilder
			.SetBufferFlags(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
			.SetData(sizeof(uint32) * _vIndices.size(), _vIndices.data())
			.Build();
	}
}

void VkMeshManager::Cleanup() {
	m_bd2DVertexBuffer.Destroy();
	m_bd3DVertexBuffer.Destroy();
	m_bdIndexBuffer.Destroy();
}

#endif