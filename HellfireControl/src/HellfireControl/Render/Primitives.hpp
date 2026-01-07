#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Asset/HCUID.hpp>

class Primitives {
private:
	static HCUID m_hQuadMesh;
	static HCUID m_hCubeMesh;

public:
	static HCUID GetQuadMesh();
	static HCUID GetCubeMesh();
};