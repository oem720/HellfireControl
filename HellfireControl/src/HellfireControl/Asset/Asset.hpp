#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/File.hpp>

#include <HellfireControl/Asset/HCUID.hpp>

class Asset {
public:
	virtual void Initialize() = 0;
};