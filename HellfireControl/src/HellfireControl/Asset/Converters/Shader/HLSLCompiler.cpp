
#include <HellfireControl/Asset/Converters/Shader/HLSLCompiler.hpp>

#include <HellfireControl/Util/Util.hpp>

CComPtr<IDxcLibrary> HLSLCompiler::m_pDXCLibrary = nullptr;
CComPtr<IDxcCompiler3> HLSLCompiler::m_pDXCCompiler = nullptr;
CComPtr<IDxcUtils> HLSLCompiler::m_pDXCUtils = nullptr;

void HLSLCompiler::InitializeCompiler() {
	Console::DebugInfo("Initializing DXC...");

	HRESULT hRes;

	hRes = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&m_pDXCLibrary));
	if (FAILED(hRes)) {
		throw std::runtime_error("Failed to create DXC Library instance!");
	}

	hRes = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m_pDXCCompiler));
	if (FAILED(hRes)) {
		throw std::runtime_error("Failed to create DXC ShaderCompiler instance!");
	}

	hRes = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_pDXCUtils));
	if (FAILED(hRes)) {
		throw std::runtime_error("Failed to create DXC Utils instance!");
	}

	Console::DebugInfo("DXC initialized successfully.");
}

void HLSLCompiler::CleanupCompiler() {
	if (m_pDXCCompiler != nullptr) {
		m_pDXCUtils.Release();
		m_pDXCCompiler.Release();
		m_pDXCLibrary.Release();
	}
}

HCCompiledShader HLSLCompiler::Compile(const HCUncompiledShader& _ucsShader) {
	if (m_pDXCCompiler == nullptr) {
		InitializeCompiler();
	}

	CComPtr<IDxcBlobEncoding> dxcSourceBlob;
	if (FAILED(m_pDXCUtils->CreateBlobFromPinned(_ucsShader.m_vFileBlob.data(), _ucsShader.m_vFileBlob.size(), CP_UTF8, &dxcSourceBlob))) {
		throw std::runtime_error("Failed to properly load data! Shader: " + _ucsShader.m_pthFilename.string() + "\n");
	}

	std::wstring strFilename = _ucsShader.m_pthFilename.wstring();
	std::wstring strEntrypoint = Util::ConvertToWString(_ucsShader.m_strEntrypointName);
	std::wstring strProfile = Util::ConvertToWString(ConvertShaderStageToDXCProfile(_ucsShader.m_sstStage));

	Array<LPCWSTR> vArguments = {
		strFilename.c_str(),
		L"-E", strEntrypoint.c_str(),
		L"-T", strProfile.c_str(),
		L"-spirv",
	};

	DxcBuffer dbBuffer = {
		.Ptr = dxcSourceBlob->GetBufferPointer(),
		.Size = dxcSourceBlob->GetBufferSize(),
		.Encoding = DXC_CP_ACP,
	};

	CComPtr<IDxcResult> pResult = nullptr;

	HRESULT hRes = m_pDXCCompiler->Compile(
		&dbBuffer,
		vArguments.data(),
		vArguments.size(),
		nullptr,
		IID_PPV_ARGS(&pResult)
	);

	if (SUCCEEDED(hRes)) {
		pResult->GetStatus(&hRes);
	}

	if (FAILED(hRes)) {
		CComPtr<IDxcBlobEncoding> pErrorBlob;
		hRes = pResult->GetErrorBuffer(&pErrorBlob);

		SUCCEEDED(hRes) ?
			throw std::runtime_error(String(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()))) :
			throw std::runtime_error("Failed to compile shader, and failed to retrieve error message! HRESULT: " + std::to_string(hRes) + "\n");
	}

	CComPtr<IDxcBlob> pCode;
	pResult->GetResult(&pCode);

	size_t sByteSize = pCode->GetBufferSize();

	Array<uint32> vCodeBlob(sByteSize >> 2);

	std::memcpy(vCodeBlob.data(), pCode->GetBufferPointer(), sByteSize);

	Console::DebugSuccess("GLSL shader \"" + _ucsShader.m_pthFilename.string() + "\" compiled successfully. Output size: " + std::to_string(sByteSize) + " bytes");

	return {
		.m_pthFilepath = FilePath(_ucsShader.m_pthFilename).replace_extension(".hcshd").string(),
		.m_sstType = _ucsShader.m_sstStage,
		.m_svtVars = HCShaderVarTableReflectSPIRV(vCodeBlob),
		.m_vCodeBlob = OptimizeSPIRV(vCodeBlob)
	};;
}

String HLSLCompiler::ConvertShaderStageToDXCProfile(HCShaderStageType _sstType) {
	switch (_sstType) {
	case SHADER_STAGE_VERTEX:
		return "vs_6_3";
	case SHADER_STAGE_FRAGMENT:
		return "ps_6_3";
	case SHADER_STAGE_GEOMETRY:
		return "gs_6_3";
	case SHADER_STAGE_TESSELLATION_CONTROL:
		return "hs_6_3";
	case SHADER_STAGE_TESSELLATION_EVALUATION:
		return "ds_6_3";
	case SHADER_STAGE_COMPUTE:
		return "cs_6_3";
	default:
		return "lib_6_3";
	}
}