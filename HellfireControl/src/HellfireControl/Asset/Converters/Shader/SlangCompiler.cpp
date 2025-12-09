
#include <HellfireControl/Asset/Converters/Shader/SlangCompiler.hpp>

Slang::ComPtr<slang::IGlobalSession> SlangCompiler::m_pSlangGlobalSession = nullptr;

#define SLANG_THROW_DIAGNOSTIC_ERROR(_blob) if (_blob != nullptr) { throw std::runtime_error(std::string(reinterpret_cast<const char*>(_blob->getBufferPointer()))); }
#define SLANG_THROW_RESULT_ERROR(_res, _msg) if (SLANG_FAILED(_res)) { throw std::runtime_error(_msg); }

void SlangCompiler::InitializeCompiler() {
	Console::DebugInfo("Initializing SlangC...");

	SlangResult srRes;

	SlangGlobalSessionDesc sgsdDesc = {
		.structureSize = sizeof(SlangGlobalSessionDesc),
		.apiVersion = SLANG_API_VERSION,
		.minLanguageVersion = SLANG_LANGUAGE_VERSION_2025,
		.enableGLSL = false
	};

	srRes = slang::createGlobalSession(&sgsdDesc, m_pSlangGlobalSession.writeRef());
	if (SLANG_FAILED(srRes)) {
		throw std::runtime_error("Failed to create Slang Global Session!");
	}

	Console::DebugInfo("SlangC initialized successfully.");
}

void SlangCompiler::CleanupCompiler() {
	if (m_pSlangGlobalSession != nullptr) {
		m_pSlangGlobalSession.setNull();
	}
}

HCCompiledShader SlangCompiler::Compile(const HCUncompiledShader& _ucsShader) {
	if (m_pSlangGlobalSession == nullptr) {
		InitializeCompiler();
	}

	SlangResult srRes;

	std::vector<const char*> arrSearchPaths = { //TODO: Make this configurable
		"./"
	};

	slang::CompilerOptionEntry coeOptions[] = {
		{
			.name = slang::CompilerOptionName::VulkanEmitReflection,
			.value = {.intValue0 = true }
		}
	};

	slang::TargetDesc tdTarget = {
		.format = SLANG_SPIRV,
		.profile = m_pSlangGlobalSession->findProfile("spirv_1_6"),
		.flags = 0,
		.compilerOptionEntries = coeOptions,
		.compilerOptionEntryCount = 1
	};

	slang::SessionDesc sdSessionDesc = {
		.targets = &tdTarget,
		.targetCount = 1,
		.flags = slang::kSessionFlags_None,
		.searchPaths = arrSearchPaths.data(),
		.searchPathCount = static_cast<SlangInt>(arrSearchPaths.size())
	};

	Slang::ComPtr<slang::ISession> pSession;
	srRes = m_pSlangGlobalSession->createSession(sdSessionDesc, pSession.writeRef());

	SLANG_THROW_RESULT_ERROR(srRes, "Failed to create Slang session!\n");

	Slang::ComPtr<slang::IModule> pModule;

	Slang::ComPtr<slang::IBlob> pDiagnosticBlob;

	pModule = pSession->loadModule(
		_ucsShader.m_pthFilename.string().data(),
		pDiagnosticBlob.writeRef()
	);

	SLANG_THROW_DIAGNOSTIC_ERROR(pDiagnosticBlob);

	if (pModule == nullptr) {
		throw std::runtime_error("Failed to load shader module!\n");
	}

	Slang::ComPtr<slang::IEntryPoint> pEntryPoint;
	srRes = pModule->getDefinedEntryPoint(0, pEntryPoint.writeRef()); //TODO: Support multiple entry points saving out to multiple shader files.

	SLANG_THROW_RESULT_ERROR(srRes, "Failed to get entry point from module!\n");

	std::vector<slang::IComponentType*> vComponentTypes = {
		pModule,
		pEntryPoint
	};

	Slang::ComPtr<slang::IComponentType> pComposedProgram;

	srRes = pSession->createCompositeComponentType(
		vComponentTypes.data(),
		vComponentTypes.size(),
		pComposedProgram.writeRef(),
		pDiagnosticBlob.writeRef()
	);

	SLANG_THROW_DIAGNOSTIC_ERROR(pDiagnosticBlob);

	SLANG_THROW_RESULT_ERROR(srRes, "Failed to create composite component type!\n");

	Slang::ComPtr<slang::IBlob> pCodeBlob;

	srRes = pComposedProgram->getEntryPointCode(
		0,
		0,
		pCodeBlob.writeRef(),
		pDiagnosticBlob.writeRef()
	);

	SLANG_THROW_DIAGNOSTIC_ERROR(pDiagnosticBlob);

	SLANG_THROW_RESULT_ERROR(srRes, "Failed to get entry point code!\n");

	size_t sByteSize = pCodeBlob->getBufferSize();

	std::vector<uint32_t> vCodeBlob(sByteSize >> 2);

	std::memcpy(vCodeBlob.data(), pCodeBlob->getBufferPointer(), sByteSize);

	Console::DebugSuccess("GLSL shader \"" + _ucsShader.m_pthFilename.string() + "\" compiled successfully. Output size: " + std::to_string(sByteSize) + " bytes");

	return {
		.m_pthFilepath = std::filesystem::path(_ucsShader.m_pthFilename).replace_extension(".hcshd").string(),
		.m_sstType = _ucsShader.m_sstStage,
		.m_svtVars = HCShaderVarTableReflectSPIRV(vCodeBlob),
		.m_vCodeBlob = OptimizeSPIRV(vCodeBlob)
	};
}