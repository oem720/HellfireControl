
#include <HellfireControl/Asset/Converters/Shader/GLSLCompiler.hpp>

shaderc_compiler_t GLSLCompiler::m_scCompiler = nullptr;
shaderc_compile_options_t GLSLCompiler::m_scoOptions = nullptr;

void GLSLCompiler::InitializeCompiler() {
	Console::DebugInfo("Initializing ShaderC...");

	m_scCompiler = shaderc_compiler_initialize();
	m_scoOptions = shaderc_compile_options_initialize();

	shaderc_compile_options_set_target_env(m_scoOptions, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_4);
	shaderc_compile_options_set_optimization_level(m_scoOptions, shaderc_optimization_level_performance);
	shaderc_compile_options_set_source_language(m_scoOptions, shaderc_source_language_glsl);
	shaderc_compile_options_set_generate_debug_info(m_scoOptions);

	Console::DebugInfo("ShaderC initialized successfully.");
}

void GLSLCompiler::CleanupCompiler() {
	if (m_scCompiler != nullptr) {
		shaderc_compile_options_release(m_scoOptions);
		shaderc_compiler_release(m_scCompiler);
	}
}

HCCompiledShader GLSLCompiler::Compile(const HCUncompiledShader& _ucsShader) {
	if (m_scCompiler == nullptr) {
		InitializeCompiler();
	}

	shaderc_compilation_result_t scrResult = shaderc_compile_into_spv(
		m_scCompiler,
		reinterpret_cast<const char*>(_ucsShader.m_vFileBlob.data()),
		_ucsShader.m_vFileBlob.size(),
		shaderc_glsl_infer_from_source,
		_ucsShader.m_pthFilename.string().c_str(),
		_ucsShader.m_strEntrypointName.c_str(),
		m_scoOptions
	);

	if (shaderc_result_get_compilation_status(scrResult) != shaderc_compilation_status_success) {
		String strError = shaderc_result_get_error_message(scrResult);
		shaderc_result_release(scrResult);
		throw std::runtime_error(strError);
	}

	size_t sByteSize = shaderc_result_get_length(scrResult);

	Array<uint32> vCodeBlob(sByteSize >> 2);

	std::memcpy(vCodeBlob.data(), reinterpret_cast<const uint32*>(shaderc_result_get_bytes(scrResult)), sByteSize);

	Console::DebugSuccess("GLSL shader \"" + _ucsShader.m_pthFilename.string() + "\" compiled successfully. Output size: " + std::to_string(sByteSize) + " bytes");

	shaderc_result_release(scrResult);

	return {
		.m_pthFilepath = FilePath(_ucsShader.m_pthFilename).replace_extension(".hcshd").string(),
		.m_sstType = _ucsShader.m_sstStage,
		.m_svtVars = HCShaderVarTableReflectSPIRV(vCodeBlob),
		.m_vCodeBlob = OptimizeSPIRV(vCodeBlob)
	};
}