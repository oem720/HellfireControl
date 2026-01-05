#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/File.hpp>

#include <HellfireControl/Asset/HCUID.hpp>

class Asset {
private:
	HCUID m_hId;

public:
	virtual void Init() = 0;
};