#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

class Shader : public Asset {
private:
	HCShaderStageBit m_ssbStage = SHADER_STAGE_INVALID_BIT;
	std::vector<uint32_t> m_vCodeBlob;
	std::map<std::string, HCShaderVar> m_mVariables;

public:
	void Initialize();

	[[nodiscard]] HC_INLINE HCShaderStageBit GetShaderStageBit() const { return m_ssbStage; }

	friend class ShaderParser;
};

class ShaderParser : public AssetParser {
private:
	static std::map<HCShaderStageType, HCShaderStageBit> m_mStageBitTable;

public:
	std::shared_ptr<Asset> Parse(File& _fAssetFile) const;
};