#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Asset/Mesh.hpp>

typedef uint32 MeshHandle;
typedef uint32 InstanceHandle;

struct InstanceData {
	//TODO: Add instance members, likely going to be material index and other data related to textures.
};

struct MeshData {
	uint32 m_u32VertexCount = 0;
	uint32 m_u32VertexOffset = 0;
	uint32 m_u32IndexCount = 0;
	uint32 m_u32IndexOffset = 0;
};

class MeshManager {
private:
	static MeshManager* m_pmmInstancePtr;

	static Array<Vertex2D> m_v2DVertexBuffer;
	static Array<Vertex3D> m_v3DVertexBuffer;

	static Array<uint32> m_vIndexBuffer;

	static Map<HCUID, MeshHandle> m_mMeshAssets;
	static Map<MeshHandle, MeshData> m_mMeshDataTable;

	static MeshHandle m_mhCurrentMeshHandle;

	void CleanupPlatformObjects();

	MeshManager() {}

public:
	MeshManager(MeshManager& _other) = delete;
	void operator=(const MeshManager& _other) = delete;

	static MeshManager* GetInstance();

	void Init() {}

	void SendToPlatform();

	void Cleanup();

	MeshHandle InitMesh(HCUID _gMeshAsset);
	void UnloadMesh(MeshHandle _mhHandle);

	InstanceHandle InitInstance(MeshHandle _mhHandle, const InstanceData& _idData);
	void UnloadInstance(MeshHandle _mhHandle, InstanceHandle _ihHandle);
};