
#include <HellfireControl/Render/Mesh/Primitives.hpp>

#include <HellfireControl/Asset/AssetManager.hpp>

#include <HellfireControl/Asset/Mesh.hpp>

HCUID Primitives::m_hQuadMesh = HCUID();
HCUID Primitives::m_hCubeMesh = HCUID();

HCUID Primitives::GetQuadMesh() {
	if (m_hQuadMesh.IsValid()) {
		return m_hQuadMesh;
	}

	Shared<Mesh> pQuadMesh = std::make_shared<Mesh>();

	pQuadMesh->m_u8MeshFlags = MESH_2D | MESH_INDEXED;
	pQuadMesh->m_v2DVertices = {
		Vertex2D {
			.m_v2Position = Vec2F{-0.5f, -0.5f},
			.m_v2TexCoord = Vec2F{0.0f, 0.0f},
			.m_v4Color = Vec4F{1.0f, 1.0f, 1.0f, 1.0f}
		},
		Vertex2D {
			.m_v2Position = Vec2F{-0.5f, 0.5f},
			.m_v2TexCoord = Vec2F{1.0f, 0.0f},
			.m_v4Color = Vec4F{1.0f, 1.0f, 1.0f, 1.0f}
		},
		Vertex2D {
			.m_v2Position = Vec2F{0.5f, 0.5f},
			.m_v2TexCoord = Vec2F{1.0f, 1.0f},
			.m_v4Color = Vec4F{1.0f, 1.0f, 1.0f, 1.0f}
		},
		Vertex2D {
			.m_v2Position = Vec2F{0.5f, -0.5f},
			.m_v2TexCoord = Vec2F{0.0f, 1.0f},
			.m_v4Color = Vec4F{1.0f, 1.0f, 1.0f, 1.0f}
		}
	};

	pQuadMesh->m_vIndices = {
		0, 1, 2, 0, 2, 3
	};

	m_hQuadMesh = AssetManager::GetInstance()->AddAssetFromMemory(pQuadMesh);

	return m_hQuadMesh;
}

HCUID Primitives::GetCubeMesh() {
	if (m_hCubeMesh.IsValid()) {
		return m_hCubeMesh;
	}

	Shared<Mesh> pCubeMesh = std::make_shared<Mesh>();

	pCubeMesh->m_u8MeshFlags = MESH_3D | MESH_INDEXED;

	Vec3F v3FrontTopLeft = Vec3F(-0.5f, 0.5f, 0.5f);
	Vec3F v3FrontTopRight = Vec3F(0.5f, 0.5f, 0.5f);
	Vec3F v3FrontBottomLeft = Vec3F(-0.5f, -0.5f, 0.5f);
	Vec3F v3FrontBottomRight = Vec3F(0.5f, -0.5f, 0.5f);
	Vec3F v3BackTopLeft = Vec3F{ -0.5f, 0.5f, -0.5f };
	Vec3F v3BackTopRight = Vec3F{ 0.5f, 0.5f, -0.5f };
	Vec3F v3BackBottomLeft = Vec3F{ -0.5f, -0.5f, -0.5f };
	Vec3F v3BackBottomRight = Vec3F{ 0.5f, -0.5f, -0.5f };

	Vec3F v3FrontNormal = Vec3F{ 0, 0, 1 };
	Vec3F v3BackNormal = Vec3F{ 0, 0, -1 };
	Vec3F v3TopNormal = Vec3F{ 0, 1, 0 };
	Vec3F v3BottomNormal = Vec3F{ 0, -1, 0 };
	Vec3F v3RightNormal = Vec3F{ 1, 0, 0 };
	Vec3F v3LeftNormal = Vec3F{ -1, 0, 0 };

	//TODO: Finish this.
	pCubeMesh->m_v3DVertices = {
		
	};

	pCubeMesh->m_vIndices = {
		
	};

	m_hCubeMesh = AssetManager::GetInstance()->AddAssetFromMemory(pCubeMesh);

	return m_hCubeMesh;
}
