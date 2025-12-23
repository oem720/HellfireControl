#pragma once

#include <HellfireControl/Core/Application.hpp>

#include <HellfireControl/Asset/Converters/Shader/Compiler.hpp>

class ShaderCompApplication : public Application {
private:
	static Array<Unique<ShaderCompiler>> m_vShaderCompilers;
	static Array<FixedArray<size_t, 3>> m_vShaderCompilerOrders;

	static Map<HCShaderFormat, String> m_mShaderFormatNames;
	static Map<HCShaderFormat, String> m_mShaderCompilerNames;
	static Map<HCShaderStageType, String> m_mShaderStageNames;
	static Map<HCShaderStageType, String> m_mShaderStageFilenames;
	static Map<HCShaderStageType, String> m_mGLSLShaderAttributeNames;
	static Map<HCShaderStageType, String> m_mHLSLShaderAttributeNames;

	Array<String> m_vArgs;

	Array<HCUncompiledShader> m_vUncompiledShaders;

	Array<HCCompiledShader> m_vCompiledShaders;

	bool m_bUseMenu = false;

	void Start();
	void End();

	void CommandLineRoutine();
	void MenuRoutine();

	static void InitializeCompilers();

	static HCCompiledShader CompileShader(const HCUncompiledShader& _ucsShader);

	static HCShaderFormat InferShaderFormat(const FilePath& _strPath);
	static HCShaderStageType InferShaderStage(const FilePath & _pthFilename, const Array<uint8>& _vFileBlob);

	static HCShaderFormat ParseShaderType(const String& _strArg);
	static HCShaderStageType ParseShaderStage(const String& _strArg);

public:
	ShaderCompApplication(int _iArgCount, char* _pArgs[]) : Application("HC Shader ShaderCompiler", AppType::CONSOLE) {
		m_vArgs = Array<String>(_iArgCount - 1);

		for (int iNdx = 1; iNdx < _iArgCount; ++iNdx) {
			m_vArgs[iNdx - 1] = String(_pArgs[iNdx]);
		}

		InitializeCompilers();
	}

	void Run();
};