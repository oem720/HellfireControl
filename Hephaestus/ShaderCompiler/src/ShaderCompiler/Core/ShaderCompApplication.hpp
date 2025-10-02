#pragma once

#include <HellfireControl/Core/Application.hpp>

#include <HellfireControl/Asset/AssetCommon.hpp>

enum HCShaderFormat : uint8_t {
	SHADER_FORMAT_GLSL,
	SHADER_FORMAT_HLSL,
	SHADER_FORMAT_SLANG,
	SHADER_FORMAT_INVALID
};

enum HCShaderVarType : uint8_t {
	VAR_COMBINED_IMAGE_SAMPLER,
	VAR_SAMPLER,
	VAR_TEXTURE_2D,
	VAR_IMAGE_2D,
	VAR_UNIFORM_TEXEL_BUFFER,
	VAR_STORAGE_TEXEL_BUFFER,
	VAR_UNIFORM_BUFFER,
	VAR_STORAGE_BUFFER,
	VAR_PUSH_CONSTANT_BUFFER,
	VAR_SUBPASS_INPUT,
	VAR_STAGE_INPUTS,
	VAR_STAGE_OUTPUTS
};

struct HCShaderVar {
	HCShaderVarType m_svtType;
	
	std::string m_strVarName;
};

enum HCShaderStageType : uint8_t {
	SHADER_STAGE_INVALID,
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
	SHADER_STAGE_CLUSTER_CULLING
};

struct HCCompiledShader {
	std::string m_strFilepath;
	uint32_t m_u32MagicNumber = HC_SHADER_IDENTIFIER;
	HCShaderStageType m_sstType = SHADER_STAGE_INVALID;
	std::vector<HCShaderVar> m_vShaderVars;
	std::vector<uint8_t> m_vCodeBlob;
};

class ShaderCompApplication : public Application {
private:
	static std::vector<std::function<std::vector<uint8_t>(const std::filesystem::path&)>> m_vShaderCompilers;
	
	static std::vector<std::array<size_t, 3>> m_vShaderCompilerOrders;

	std::vector<std::string> m_vArgs;

	std::vector<HCCompiledShader> m_vCompiledShaders;

	bool m_bUseMenu = false;

	void Start();

	void End();

	void CommandLineRoutine();

	void MenuRoutine();

	static std::vector<uint8_t> CompileShader(const std::filesystem::path& _strPath, HCShaderFormat _sfType);
	static HCCompiledShader CreateCompiledShader(const std::filesystem::path& _strPath, const std::vector<uint8_t>& _vCodeBlob);

	static HCShaderFormat InferShaderType(const std::filesystem::path& _strPath);
	static std::vector<uint8_t> CompileGLSL(const std::filesystem::path& _strPath);
	static std::vector<uint8_t> CompileHLSL(const std::filesystem::path& _strPath);
	static std::vector<uint8_t> CompileSlang(const std::filesystem::path& _strPath);

	static HCShaderFormat ParseShaderType(const std::string& _strArg);
	static std::string ShaderCompilerToString(HCShaderFormat _sfType);
	static std::string ShaderFormatToString(HCShaderFormat _sfType);

public:
	ShaderCompApplication(const std::vector<std::string>& _vArgs) 
		: Application("HC Shader Compiler", AppType::CONSOLE), m_vArgs(_vArgs), m_bUseMenu(_vArgs.size() <= 1) {}

	void Run();
};