#pragma once

#include <HellfireControl/Core/Common.hpp>
#include <HellfireControl/Core/Console.hpp>
#include <HellfireControl/Asset/AssetCommon.hpp>

#include <ShaderCompiler/Compilers/ShaderVar.hpp>

#include <spirv_cross/spirv_cross.hpp>
#include <spirv-tools/optimizer.hpp>

enum HCShaderFormat : uint8_t {
	SHADER_FORMAT_GLSL,
	SHADER_FORMAT_HLSL,
	SHADER_FORMAT_SLANG,
	SHADER_FORMAT_INVALID
};

enum HCShaderStageType : uint8_t {
	SHADER_STAGE_VERTEX,
	SHADER_STAGE_FRAGMENT,
	SHADER_STAGE_GEOMETRY,
	SHADER_STAGE_TESSELLATION_CONTROL,
	SHADER_STAGE_TESSELLATION_EVALUATION,
	SHADER_STAGE_COMPUTE,
	SHADER_STAGE_TASK,
	SHADER_STAGE_MESH,
	SHADER_STAGE_RAYGEN,
	SHADER_STAGE_ANY_HIT,
	SHADER_STAGE_CLOSEST_HIT,
	SHADER_STAGE_MISS,
	SHADER_STAGE_INTERSECTION,
	SHADER_STAGE_CALLABLE,
	SHADER_STAGE_INVALID
};

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
	std::map<std::string, HCShaderVar> m_vShaderVars;
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

	std::map<std::string, HCShaderVar> ReflectSPIRV(const std::vector<uint32_t>& _vCodeBlob);
	std::vector<uint32_t> OptimizeSPIRV(const std::vector<uint32_t>& _vCodeBlob);

private:
	std::map<std::string, HCShaderVar> ParseShaderVars(const spirv_cross::Compiler& _cComp, const spirv_cross::ShaderResources& _srRes);
};