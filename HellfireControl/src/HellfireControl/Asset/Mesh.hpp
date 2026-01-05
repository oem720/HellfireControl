#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Asset/AssetCommon.hpp>

enum MeshFlags : uint8 {
	MESH_2D = (1 << 0),
	MESH_3D = (1 << 1),
	MESH_INDEXED = (1 << 2),
};

struct HC_ALIGNAS(16) Vertex2D {
	Vec2F m_v2Position;
	Vec2F m_v2TexCoord;
	Vec4F m_v4Color;
};

struct HC_ALIGNAS(16) Vertex3D {
	Vec3F m_v3Position;
	Vec3F m_v3Normal;
	Vec2F m_v2TexCoord;
	Vec4F m_v4Color;
};

class Mesh : public Asset {
private:
	uint8 m_u8MeshFlags = 0;

	Array<Vertex2D> m_v2DVertices;
	Array<Vertex3D> m_v3DVertices;

	Array<uint32> m_vIndices;

	friend class Primitives;
	friend class MeshManager;
public:
	void Init() {}
};
