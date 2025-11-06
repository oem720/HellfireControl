#pragma once

#include <HellfireControl/Asset/Converters/Shader/Compiler.hpp>

#include <shaderc/shaderc.hpp>

class GLSLCompiler : public ShaderCompiler {
private:
	static shaderc_compiler_t m_scCompiler;
	static shaderc_compile_options_t m_scoOptions;

	void InitializeCompiler();
	void CleanupCompiler();

public:
	~GLSLCompiler() { this->CleanupCompiler(); }

	HCCompiledShader Compile(const HCUncompiledShader& _ucsShader);
};