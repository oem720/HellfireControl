#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

class Shader : public Asset {
private:
	HCShaderStageBit m_ssbStage = SHADER_STAGE_INVALID_BIT;
	Array<uint32> m_vCodeBlob;
	Map<String, HCShaderVar> m_mVariables;

public:
	void Initialize();

	[[nodiscard]] HC_INLINE HCShaderStageBit GetShaderStageBit() const { return m_ssbStage; }
	[[nodiscard]] HC_INLINE const Map<String, HCShaderVar>& GetShaderVars() const { return m_mVariables; }

	friend class ShaderParser;
};

class ShaderParser : public AssetParser {
private:
	static Map<HCShaderStageType, HCShaderStageBit> m_mStageBitTable;

public:
	SharedPointer<Asset> Parse(File& _fAssetFile) const;
};