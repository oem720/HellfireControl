#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

class PlatformShader {
public:
	virtual void Init(const Array<uint32>& _vCodeBlob, const Map<String, HCShaderVar>& _mVars) = 0;
	virtual void Cleanup() = 0;
};

class Shader : public Asset {
private:
	HCShaderStageBit m_ssbStage = SHADER_STAGE_INVALID_BIT;
	Array<uint32> m_vCodeBlob;
	Map<String, HCShaderVar> m_mVariables;

	Shared<PlatformShader> m_pPlatformShader;

public:
	void Init();

	[[nodiscard]] HC_INLINE HCShaderStageBit GetShaderStageBit() const { return m_ssbStage; }
	[[nodiscard]] HC_INLINE const Map<String, HCShaderVar>& GetShaderVars() const { return m_mVariables; }
	[[nodiscard]] HC_INLINE Shared<PlatformShader> GetPlatformShader() const { return m_pPlatformShader; }

	friend class ShaderParser;
};

class ShaderParser : public AssetParser {
private:
	static Map<HCShaderStageType, HCShaderStageBit> m_mStageBitTable;

public:
	Shared<Asset> Parse(File& _fAssetFile) const;
};