
#include <ShaderCompiler/Core/ShaderCompApplication.hpp>

#include <HellfireControl/Core/Console.hpp>

#include <atlbase.h>
#include <shaderc/shaderc.hpp>
#include <slang/slang.h>
#include <dxc/dxcapi.h>
#include <spirv_cross/spirv_cross.hpp>

std::vector<std::function<std::vector<uint8_t>(const std::filesystem::path&)>> ShaderCompApplication::m_vShaderCompilers = {
	ShaderCompApplication::CompileGLSL,
	ShaderCompApplication::CompileHLSL,
	ShaderCompApplication::CompileSlang
};

std::vector<std::array<size_t, 3>> ShaderCompApplication::m_vShaderCompilerOrders = {
	{ SHADER_FORMAT_GLSL, SHADER_FORMAT_HLSL, SHADER_FORMAT_SLANG }, // GLSL
	{ SHADER_FORMAT_HLSL, SHADER_FORMAT_GLSL, SHADER_FORMAT_SLANG }, // HLSL
	{ SHADER_FORMAT_SLANG, SHADER_FORMAT_HLSL, SHADER_FORMAT_GLSL }  // Slang
};

static shaderc_compiler_t g_scCompiler = nullptr;
static shaderc_compile_options_t g_scoOptions = nullptr;

void ShaderCompApplication::Start() {
	//ShaderC Init
	{
		g_scCompiler = shaderc_compiler_initialize();
		g_scoOptions = shaderc_compile_options_initialize();

		shaderc_compile_options_set_target_env(g_scoOptions, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_4);
		shaderc_compile_options_set_optimization_level(g_scoOptions, shaderc_optimization_level_performance);
		shaderc_compile_options_set_source_language(g_scoOptions, shaderc_source_language_glsl);
		shaderc_compile_options_set_generate_debug_info(g_scoOptions);
	}
}

void ShaderCompApplication::Run() {
	this->Start();

	m_bUseMenu ? MenuRoutine() : CommandLineRoutine();

	this->End();
}

void ShaderCompApplication::End() {
	//ShaderC Cleanup
	{
		shaderc_compile_options_release(g_scoOptions);
		shaderc_compiler_release(g_scCompiler);
	}

	for (const auto& aShader : m_vCompiledShaders) {
		File fShaderAsset(aShader.m_strFilepath, FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_BINARY);

		uint32_t u32VarCount = aShader.m_vShaderVars.size();
		uint32_t u32CodeSize = aShader.m_vCodeBlob.size();

		fShaderAsset.Write(&aShader.m_u32MagicNumber, sizeof(uint32_t));
		fShaderAsset.Write(&aShader.m_sstType, sizeof(HCShaderFormat));
		fShaderAsset.Write(&u32CodeSize, sizeof(uint32_t));
		fShaderAsset.Write(aShader.m_vCodeBlob.data(), sizeof(uint8_t) * u32CodeSize);

		fShaderAsset.Write(&u32VarCount, sizeof(uint32_t));
		fShaderAsset.Write(aShader.m_vShaderVars.data(), sizeof(HCShaderVar) * u32VarCount);

		fShaderAsset.Close();
	}
}

void ShaderCompApplication::CommandLineRoutine() {
	HCShaderFormat sfType = SHADER_FORMAT_INVALID;

	for (const auto& aArg : m_vArgs) {
		std::vector<uint8_t> vCompiledBlob;

		if ((sfType = ParseShaderType(aArg)) != SHADER_FORMAT_INVALID) {
			continue;
		}
		else if (std::filesystem::exists(aArg)) {
			vCompiledBlob = CompileShader(aArg, sfType);
		}
		else {
			Console::DebugWarn("Invalid argument detected! Execution has not ended, but the compiler may not work as expected!");
		}

		if (vCompiledBlob.empty()) {
			Console::DebugFail("Failed to compile shader: " + aArg);
			continue;
		}

		m_vCompiledShaders.push_back(CreateCompiledShader(aArg, vCompiledBlob));
	}
}

void ShaderCompApplication::MenuRoutine() {

}

std::vector<uint8_t> ShaderCompApplication::CompileShader(const std::filesystem::path& _strPath, HCShaderFormat _sfType) {
	Console::DebugInfo("Attempting to compile shader: " + _strPath.filename().string());

	if (_sfType == SHADER_FORMAT_INVALID) {
		_sfType = InferShaderType(_strPath);

		Console::DebugWarn("Type argument unspecified! Shader type inferred as: " + ShaderFormatToString(_sfType));
	}

	std::vector<uint8_t> vCompiledBlob;

	for (const size_t aCompilerIndex : m_vShaderCompilerOrders[_sfType]) {
		Console::DebugInfo("Attemping to compile with compiler: " + ShaderCompilerToString(static_cast<HCShaderFormat>(aCompilerIndex)));

		try {
			vCompiledBlob = m_vShaderCompilers[aCompilerIndex](_strPath);
			if (!vCompiledBlob.empty()) {
				Console::DebugSuccess("Successfully compiled shader: " + _strPath.filename().string());
				break;
			}
		}
		catch (const std::exception& e) {
			Console::DebugError("Shader compilation error:\n\n" + std::string(e.what()));
		}

		Console::DebugFail("Shader compilation failed with compiler: " + ShaderCompilerToString(static_cast<HCShaderFormat>(aCompilerIndex)));
	}

	return vCompiledBlob;
}

HCCompiledShader ShaderCompApplication::CreateCompiledShader(const std::filesystem::path& _strPath, const std::vector<uint8_t>& _vCodeBlob) {

	return HCCompiledShader();
}

std::vector<uint8_t> ShaderCompApplication::CompileGLSL(const std::filesystem::path& _strPath) {
	File fFile(_strPath.string(), FILE_OPEN_FLAG_BLOB);

	std::vector<uint8_t> vShaderSource = fFile.ExtractFileBlob();

	std::string strShaderSource(vShaderSource.begin(), vShaderSource.end());

	shaderc_compilation_result_t scrResult = shaderc_compile_into_spv(
		g_scCompiler,
		strShaderSource.c_str(),
		strShaderSource.size(),
		shaderc_glsl_infer_from_source,
		_strPath.filename().string().data(),
		"main",
		g_scoOptions
	);

	if (shaderc_result_get_compilation_status(scrResult) != shaderc_compilation_status_success) {
		std::string strError = shaderc_result_get_error_message(scrResult);
		shaderc_result_release(scrResult);
		throw std::runtime_error(strError);
	}

	std::vector<uint8_t> vCompiledBlob(shaderc_result_get_length(scrResult));

	std::memcpy(vCompiledBlob.data(), shaderc_result_get_bytes(scrResult), vCompiledBlob.size());

	shaderc_result_release(scrResult);

	return vCompiledBlob;
}

std::vector<uint8_t> ShaderCompApplication::CompileHLSL(const std::filesystem::path& _strPath) {

	return std::vector<uint8_t>();
}

std::vector<uint8_t> ShaderCompApplication::CompileSlang(const std::filesystem::path& _strPath) {

	return std::vector<uint8_t>();
}

HCShaderFormat ShaderCompApplication::InferShaderType(const std::filesystem::path& _strPath) {
	std::filesystem::path pthExtension = _strPath.extension();

	if (pthExtension == ".hlsl" || pthExtension == ".fx" || pthExtension == ".fxh") {
		return SHADER_FORMAT_HLSL;
	}
	else if (pthExtension == ".slang" || pthExtension == ".sl") {
		return SHADER_FORMAT_SLANG;
	}

	return SHADER_FORMAT_GLSL; //Default to GLSL if the extensions don't match HLSL or Slang
}

HCShaderFormat ShaderCompApplication::ParseShaderType(const std::string& _strArg) {
	std::string strArgCopy = _strArg;

	//Force it to lowercase to make it casing agnostic
	std::transform(strArgCopy.begin(), strArgCopy.end(), strArgCopy.begin(), [](unsigned char cChar) { return std::tolower(cChar); });

	if (strArgCopy == "-glsl") return SHADER_FORMAT_GLSL;
	if (strArgCopy == "-hlsl") return SHADER_FORMAT_HLSL;
	if (strArgCopy == "-slang") return SHADER_FORMAT_SLANG;

	return SHADER_FORMAT_INVALID;
}

std::string ShaderCompApplication::ShaderCompilerToString(HCShaderFormat _sfType) {
	std::string strName;

	switch (_sfType) {
	case SHADER_FORMAT_GLSL:
		strName = "ShaderC";
		break;
	case SHADER_FORMAT_HLSL:
		strName = "DXC";
		break;
	case SHADER_FORMAT_SLANG:
		strName = "SlangC";
		break;
	default:
		strName = "Invalid";
		break;
	};

	return strName;
}

std::string ShaderCompApplication::ShaderFormatToString(HCShaderFormat _sfType) {
	std::string strName;

	switch (_sfType) {
	case SHADER_FORMAT_GLSL:
		strName = "GLSL";
		break;
	case SHADER_FORMAT_HLSL:
		strName = "HLSL";
		break;
	case SHADER_FORMAT_SLANG:
		strName = "Slang";
		break;
	default:
		strName = "Invalid";
		break;
	};

	return strName;
}
