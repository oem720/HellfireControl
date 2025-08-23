#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Math/Math.hpp>
#include <HellfireControl/Asset/Asset.hpp>

class AssetParser {
public:
	virtual std::shared_ptr<Asset> Parse(File& _fAssetFile) const = 0;
};

enum FontType : uint8_t {
	FONT_BITMAP = 0,
	FONT_SINGLE_CHANNEL_SDF = 1,
	FONT_MULTI_CHANNEL_SDF = 2
};

struct BakedGlyphBoxInfo {
	Vec4F m_v4BoundingBox = Vec4F();
	float m_fAdvanceWidth = 0.0f;
	float m_fHorizontalShift = 0.0f;
	float m_fVerticalShift = 0.0f;
	uint32_t m_u32AtlasIndex = 0;
};

enum AssetMagicNumbers : uint32_t {
	HC_MANIFEST_IDENTIFIER = 1229865293U,
	HC_FONT_IDENTIFIER = 1179797320U,
};