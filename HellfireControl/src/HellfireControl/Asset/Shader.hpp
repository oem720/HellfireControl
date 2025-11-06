#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

class Shader : public Asset {
private:
	HCShaderStageType m_sstStage = SHADER_STAGE_INVALID;
	std::vector<uint32_t> m_vCodeBlob;
	std::map<std::string, HCShaderVar> m_mVariables;

public:
	void Initialize();

	friend class ShaderParser;
};

class ShaderParser : public AssetParser {
public:
	std::shared_ptr<Asset> Parse(File& _fAssetFile) const;
};