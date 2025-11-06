#pragma once

#include <HellfireControl/Asset/Converters/Shader/Compiler.hpp>

#include <slang/slang.h>
#include <slang/slang-com-ptr.h>

class SlangCompiler : public ShaderCompiler {
private:
	static Slang::ComPtr<slang::IGlobalSession> m_pSlangGlobalSession;

	void InitializeCompiler();
	void CleanupCompiler();

public:
	~SlangCompiler() { this->CleanupCompiler(); }

	HCCompiledShader Compile(const HCUncompiledShader& _ucsShader);
};