#pragma once

#include <HellfireControl/Core/Application.hpp>

#include <ShaderCompiler/Compilers/Compiler.hpp>

class ShaderCompApplication : public Application {
private:
	static std::vector<std::unique_ptr<ShaderCompiler>> m_vShaderCompilers;
	static std::vector<std::array<size_t, 3>> m_vShaderCompilerOrders;

	static std::map<HCShaderFormat, std::string> m_mShaderFormatNames;
	static std::map<HCShaderFormat, std::string> m_mShaderCompilerNames;
	static std::map<HCShaderStageType, std::string> m_mShaderStageNames;
	static std::map<HCShaderStageType, std::string> m_mShaderStageFilenames;
	static std::map<HCShaderStageType, std::string> m_mGLSLShaderAttributeNames;
	static std::map<HCShaderStageType, std::string> m_mHLSLShaderAttributeNames;

	std::vector<std::string> m_vArgs;

	std::vector<HCUncompiledShader> m_vUncompiledShaders;

	std::vector<HCCompiledShader> m_vCompiledShaders;

	bool m_bUseMenu = false;

	void Start();
	void End();

	void CommandLineRoutine();
	void MenuRoutine();

	static void InitializeCompilers();

	static HCCompiledShader CompileShader(const HCUncompiledShader& _ucsShader);

	static HCShaderFormat InferShaderFormat(const std::filesystem::path& _strPath);
	static HCShaderStageType InferShaderStage(const std::filesystem::path & _pthFilename, const std::vector<uint8_t>& _vFileBlob);

	static HCShaderFormat ParseShaderType(const std::string& _strArg);
	static HCShaderStageType ParseShaderStage(const std::string& _strArg);

public:
	ShaderCompApplication(int _iArgCount, char* _pArgs[]) : Application("HC Shader ShaderCompiler", AppType::CONSOLE) {
		m_vArgs = std::vector<std::string>(_iArgCount - 1);

		for (int iNdx = 1; iNdx < _iArgCount; ++iNdx) {
			m_vArgs[iNdx - 1] = std::string(_pArgs[iNdx]);
		}

		InitializeCompilers();
	}

	void Run();
};