#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/File.hpp>
#include <HellfireControl/Math/Math.hpp>
#include <HellfireControl/Asset/Asset.hpp>

class AssetParser {
public:
	virtual Shared<Asset> Parse(File& _fAssetFile) const = 0;
};

struct BakedGlyphBoxInfo {
	Vec4F m_v4BoundingBox = Vec4F();
	float m_fAdvanceWidth = 0.0f;
	float m_fHorizontalShift = 0.0f;
	float m_fVerticalShift = 0.0f;
	uint32 m_u32AtlasIndex = 0;
};

enum AssetMagicNumbers : uint32 {
	HC_MANIFEST_IDENTIFIER = HC_CREATE_32BIT_TAG('M', 'A', 'N', 'I'),
	HC_FONT_IDENTIFIER = HC_CREATE_32BIT_TAG('H', 'G', 'R', 'F'),
	HC_SHADER_IDENTIFIER = HC_CREATE_32BIT_TAG('S', 'H', 'A', 'D')
};