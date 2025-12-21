#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>
#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Asset/Converters/Shader/ShaderCommon.hpp>

#include <spirv_cross/spirv_cross.hpp>
#include <spirv-tools/optimizer.hpp>

struct HCUncompiledShader {
	FilePath m_pthFilename;
	Array<uint8> m_vFileBlob;
	HCShaderFormat m_sfFormat = SHADER_FORMAT_INVALID;
	HCShaderStageType m_sstStage = SHADER_STAGE_INVALID;
	String m_strEntrypointName = "main";
};

struct HCCompiledShader {
	FilePath m_pthFilepath;
	uint32 m_u32MagicNumber = HC_SHADER_IDENTIFIER;
	HCShaderStageType m_sstType = SHADER_STAGE_INVALID;
	HCShaderVarTable m_svtVars;
	Array<uint32> m_vCodeBlob;
};

class ShaderCompiler {
private:
	static Map<uint32, String> m_mImageFormatNames;
	static Map<uint32, String> m_mImageDimensions;
	static Map<uint16, String> m_mTypeNames;
	static Map<uint32, String> m_mBuiltinNames;

public:
	ShaderCompiler() {}

	virtual HCCompiledShader Compile(const HCUncompiledShader& _ucsShader) = 0;

protected:
	virtual void InitializeCompiler() = 0;
	virtual void CleanupCompiler() = 0;

	HCShaderVarTable HCShaderVarTableReflectSPIRV(const Array<uint32>& _vCodeBlob);
	Array<uint32> OptimizeSPIRV(const Array<uint32>& _vCodeBlob);

private:
	Map<String, HCShaderVar> ParseShaderVars(const spirv_cross::Compiler& _cComp, const spirv_cross::ShaderResources& _srRes);
};