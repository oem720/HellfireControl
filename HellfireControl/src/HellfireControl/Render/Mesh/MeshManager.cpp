
#include <HellfireControl/Render/Mesh/MeshManager.hpp>
#include <HellfireControl/Asset/AssetManager.hpp>

#include <HellfireControl/Core/Console.hpp>

MeshManager* MeshManager::m_pmmInstancePtr = nullptr;

Array<Vertex2D> MeshManager::m_v2DVertexBuffer;
Array<Vertex3D> MeshManager::m_v3DVertexBuffer;

Array<uint32> MeshManager::m_vIndexBuffer;

Map<HCUID, MeshHandle> MeshManager::m_mMeshAssets;
Map<MeshHandle, MeshData> MeshManager::m_mMeshDataTable;

MeshHandle MeshManager::m_mhCurrentMeshHandle = 0;

MeshManager* MeshManager::GetInstance() {
	if (m_pmmInstancePtr == nullptr) {
		m_pmmInstancePtr = new MeshManager();
	}
	return m_pmmInstancePtr;
}

void MeshManager::Cleanup() {
	m_mMeshAssets.clear();
	m_mMeshDataTable.clear();

	CleanupPlatformObjects();
}

MeshHandle MeshManager::InitMesh(HCUID _gMeshAsset) {
	if(m_mMeshAssets.find(_gMeshAsset) != m_mMeshAssets.end()) {
		return m_mMeshAssets[_gMeshAsset];
	}

	Shared<Mesh> pMesh = std::dynamic_pointer_cast<Mesh>(AssetManager::GetInstance()->GetAsset(_gMeshAsset));
	
	MeshData mdNewMeshData = {};

	if (pMesh->m_u8MeshFlags & MESH_2D) {
		mdNewMeshData.m_u32VertexOffset = static_cast<uint32>(m_v2DVertexBuffer.size());
		mdNewMeshData.m_u32VertexCount = static_cast<uint32>(pMesh->m_v2DVertices.size());

		m_v2DVertexBuffer.insert(m_v2DVertexBuffer.end(), pMesh->m_v2DVertices.begin(), pMesh->m_v2DVertices.end());
	}
	else if (pMesh->m_u8MeshFlags & MESH_3D) {
		mdNewMeshData.m_u32VertexOffset = static_cast<uint32>(m_v3DVertexBuffer.size());
		mdNewMeshData.m_u32VertexCount = static_cast<uint32>(pMesh->m_v3DVertices.size());

		m_v3DVertexBuffer.insert(m_v3DVertexBuffer.end(), pMesh->m_v3DVertices.begin(), pMesh->m_v3DVertices.end());
	}

	if (pMesh->m_u8MeshFlags & MESH_INDEXED) {
		mdNewMeshData.m_u32IndexOffset = static_cast<uint32>(m_vIndexBuffer.size());
		mdNewMeshData.m_u32IndexCount = static_cast<uint32>(pMesh->m_vIndices.size());

		m_vIndexBuffer.insert(m_vIndexBuffer.end(), pMesh->m_vIndices.begin(), pMesh->m_vIndices.end());
	}

	MeshHandle mhHandle = m_mhCurrentMeshHandle++;

	m_mMeshAssets[_gMeshAsset] = mhHandle;
	m_mMeshDataTable[mhHandle] = mdNewMeshData;

	return mhHandle;
}

void MeshManager::UnloadMesh(MeshHandle _mhHandle) {
	if (!m_mMeshDataTable.contains(_mhHandle)) {
		Console::DebugWarn("Attempted to unload a mesh that isn't loaded!");
		return;
	}

	m_mMeshAssets.erase(std::find_if(m_mMeshAssets.begin(), m_mMeshAssets.end(), [&](auto aHandle) { return aHandle.second == _mhHandle; }));
	m_mMeshDataTable.erase(_mhHandle);
}

InstanceHandle MeshManager::InitInstance(MeshHandle _mhHandle, const InstanceData& _idData) {

	return InstanceHandle();
}

void MeshManager::UnloadInstance(MeshHandle _mhHandle, InstanceHandle _ihHandle) {

}
