#pragma once

#include <ShaderCompiler/Compilers/Compiler.hpp>

#include <atlbase.h>
#include <dxc/dxcapi.h>

class HLSLCompiler : public ShaderCompiler {
private:
	static CComPtr<IDxcLibrary> m_pDXCLibrary;
	static CComPtr<IDxcCompiler3> m_pDXCCompiler;
	static CComPtr<IDxcUtils> m_pDXCUtils;

	void InitializeCompiler();
	void CleanupCompiler();

	static std::string ConvertShaderStageToDXCProfile(HCShaderStageType _sstType);

public:
	~HLSLCompiler() { this->CleanupCompiler(); }

	HCCompiledShader Compile(const HCUncompiledShader& _ucsShader);
};