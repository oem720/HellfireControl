#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>
#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

#include <spirv_cross/spirv_cross.hpp>
#include <spirv-tools/optimizer.hpp>

struct HCUncompiledShader {
	std::filesystem::path m_pthFilename;
	std::vector<uint8_t> m_vFileBlob;
	HCShaderFormat m_sfFormat = SHADER_FORMAT_INVALID;
	HCShaderStageType m_sstStage = SHADER_STAGE_INVALID;
	std::string m_strEntrypointName = "main";
};

struct HCCompiledShader {
	std::filesystem::path m_pthFilepath;
	uint32_t m_u32MagicNumber = HC_SHADER_IDENTIFIER;
	HCShaderStageType m_sstType = SHADER_STAGE_INVALID;
	HCShaderVarTable m_svtVars;
	std::vector<uint32_t> m_vCodeBlob;
};

class ShaderCompiler {
private:
	static std::map<uint32_t, std::string> m_mImageFormatNames;
	static std::map<uint32_t, std::string> m_mImageDimensions;
	static std::map<uint16_t, std::string> m_mTypeNames;
	static std::map<uint32_t, std::string> m_mBuiltinNames;

public:
	ShaderCompiler() {}

	virtual HCCompiledShader Compile(const HCUncompiledShader& _ucsShader) = 0;

protected:
	virtual void InitializeCompiler() = 0;
	virtual void CleanupCompiler() = 0;

	HCShaderVarTable HCShaderVarTableReflectSPIRV(const std::vector<uint32_t>& _vCodeBlob);
	std::vector<uint32_t> OptimizeSPIRV(const std::vector<uint32_t>& _vCodeBlob);

private:
	std::map<std::string, HCShaderVar> ParseShaderVars(const spirv_cross::Compiler& _cComp, const spirv_cross::ShaderResources& _srRes);
};