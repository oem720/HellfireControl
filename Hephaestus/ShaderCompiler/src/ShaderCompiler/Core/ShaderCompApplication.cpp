
#include <ShaderCompiler/Core/ShaderCompApplication.hpp>

#include <HellfireControl/Asset/Converters/Shader/GLSLCompiler.hpp>
#include <HellfireControl/Asset/Converters/Shader/HLSLCompiler.hpp>
#include <HellfireControl/Asset/Converters/Shader/SlangCompiler.hpp>

#include <HellfireControl/Util/Util.hpp>
#include <HellfireControl/Core/Console.hpp>

Array<Unique<ShaderCompiler>> ShaderCompApplication::m_vShaderCompilers;

Array<FixedArray<size_t, 3>> ShaderCompApplication::m_vShaderCompilerOrders = {
	{ SHADER_FORMAT_GLSL, SHADER_FORMAT_HLSL, SHADER_FORMAT_SLANG }, // GLSL
	{ SHADER_FORMAT_HLSL, SHADER_FORMAT_SLANG, SHADER_FORMAT_GLSL }, // HLSL
	{ SHADER_FORMAT_SLANG, SHADER_FORMAT_HLSL, SHADER_FORMAT_GLSL }  // Slang
};

Map<HCShaderFormat, String> ShaderCompApplication::m_mShaderFormatNames = {
	{SHADER_FORMAT_GLSL, "GLSL"},
	{SHADER_FORMAT_HLSL, "HLSL"},
	{SHADER_FORMAT_SLANG, "Slang"},
	{SHADER_FORMAT_INVALID, "INVALID"},
};

Map<HCShaderFormat, String> ShaderCompApplication::m_mShaderCompilerNames = {
	{SHADER_FORMAT_GLSL, "ShaderC"},
	{SHADER_FORMAT_HLSL, "DXC"},
	{SHADER_FORMAT_SLANG, "SlangC"},
	{SHADER_FORMAT_INVALID, "INVALID"},
};

Map<HCShaderStageType, String> ShaderCompApplication::m_mShaderStageNames = {
	{SHADER_STAGE_VERTEX, "Vertex"},
	{SHADER_STAGE_FRAGMENT, "Fragment/Pixel"},
	{SHADER_STAGE_GEOMETRY, "Geometry"},
	{SHADER_STAGE_TESSELLATION_CONTROL, "Tessellation Control/Hull"},
	{SHADER_STAGE_TESSELLATION_EVALUATION, "Tessellation Evaluation/Domain"},
	{SHADER_STAGE_COMPUTE, "Compute"},
	{SHADER_STAGE_TASK, "Task"},
	{SHADER_STAGE_MESH, "Mesh"},
	{SHADER_STAGE_RAYGEN, "Ray Generation"},
	{SHADER_STAGE_ANY_HIT, "Ray Any Hit"},
	{SHADER_STAGE_CLOSEST_HIT, "Ray Closest Hit"},
	{SHADER_STAGE_MISS, "Ray Miss"},
	{SHADER_STAGE_INTERSECTION, "Ray Intersection"},
	{SHADER_STAGE_CALLABLE, "Ray Callable"},
	{SHADER_STAGE_INVALID, "INVALID"}
};

Map<HCShaderStageType, String> ShaderCompApplication::m_mShaderStageFilenames = {
	{SHADER_STAGE_VERTEX, "vert"},
	{SHADER_STAGE_FRAGMENT, "frag"},
	{SHADER_STAGE_GEOMETRY, "geom"},
	{SHADER_STAGE_TESSELLATION_CONTROL, "tesc"},
	{SHADER_STAGE_TESSELLATION_EVALUATION, "tese"},
	{SHADER_STAGE_COMPUTE, "comp"},
	{SHADER_STAGE_TASK, "task"},
	{SHADER_STAGE_MESH, "mesh"},
	{SHADER_STAGE_RAYGEN, "rgen"},
	{SHADER_STAGE_ANY_HIT, "rahit"},
	{SHADER_STAGE_CLOSEST_HIT, "rchit"},
	{SHADER_STAGE_MISS, "rmiss"},
	{SHADER_STAGE_INTERSECTION, "rint"},
	{SHADER_STAGE_CALLABLE, "rcall"},
	{SHADER_STAGE_INVALID, "INVALID"}
};

Map<HCShaderStageType, String> ShaderCompApplication::m_mGLSLShaderAttributeNames = {
	{SHADER_STAGE_VERTEX, "vertex"},
	{SHADER_STAGE_FRAGMENT, "fragment"},
	{SHADER_STAGE_GEOMETRY, "geometry"},
	{SHADER_STAGE_TESSELLATION_CONTROL, "tesscontrol"},
	{SHADER_STAGE_TESSELLATION_EVALUATION, "tessevaluation"},
	{SHADER_STAGE_COMPUTE, "compute"},
	{SHADER_STAGE_TASK, "task"},
	{SHADER_STAGE_MESH, "mesh"},
	{SHADER_STAGE_RAYGEN, "raygen"},
	{SHADER_STAGE_ANY_HIT, "anyhit"},
	{SHADER_STAGE_CLOSEST_HIT, "closesthit"},
	{SHADER_STAGE_MISS, "miss"},
	{SHADER_STAGE_INTERSECTION, "intersection"},
	{SHADER_STAGE_CALLABLE, "callable"}
};

Map<HCShaderStageType, String> ShaderCompApplication::m_mHLSLShaderAttributeNames = {
	{SHADER_STAGE_VERTEX, "vertex"},
	{SHADER_STAGE_FRAGMENT, "pixel"},
	{SHADER_STAGE_GEOMETRY, "geometry"},
	{SHADER_STAGE_TESSELLATION_CONTROL, "hull"},
	{SHADER_STAGE_TESSELLATION_EVALUATION, "domain"},
	{SHADER_STAGE_COMPUTE, "compute"},
	{SHADER_STAGE_TASK, "amplification"},
	{SHADER_STAGE_MESH, "mesh"},
	{SHADER_STAGE_RAYGEN, "raygeneration"},
	{SHADER_STAGE_ANY_HIT, "anyhit"},
	{SHADER_STAGE_CLOSEST_HIT, "closesthit"},
	{SHADER_STAGE_MISS, "miss"},
	{SHADER_STAGE_INTERSECTION, "intersection"},
	{SHADER_STAGE_CALLABLE, "callable"}
};

void ShaderCompApplication::Start() {
	if (m_vArgs.size() == 0) {
		m_bUseMenu = true;
	}

	HCShaderFormat sfType = SHADER_FORMAT_INVALID;
	HCShaderStageType sstStage = SHADER_STAGE_INVALID;
	String strEntryPoint = "main";

	bool bEntryPointNext = false;

	for (const auto& aArg : m_vArgs) {
		if (bEntryPointNext) {
			strEntryPoint = aArg;
			bEntryPointNext = false;
			continue;
		}

		if (HCShaderFormat sfTemp = ParseShaderType(aArg); sfTemp != SHADER_FORMAT_INVALID) {
			sfType = sfTemp;
			continue;
		}
		
		if (HCShaderStageType sstTemp = ParseShaderStage(aArg); sstTemp != SHADER_STAGE_INVALID) {
			sstStage = sstTemp;
			continue;
		}

		if (aArg == "-entry" || aArg == "-e") {
			bEntryPointNext = true;
			continue;
		}

		if(aArg == "-menu" || aArg == "-m") {
			m_bUseMenu = true;
			continue;
		}

		if(std::filesystem::exists(aArg) && std::filesystem::is_regular_file(aArg)) {
			HCUncompiledShader ucsShader = {
				.m_pthFilename = FilePath(aArg).filename(),
				.m_vFileBlob = File(aArg, FILE_OPEN_FLAG_BLOB).ExtractFileBlob(),
				.m_sfFormat = sfType,
				.m_sstStage = sstStage
			};

			if(sfType == SHADER_FORMAT_INVALID) {
				Console::DebugWarn("Type argument unspecified for shader \"" + aArg + "\". Inferring type from file extension...");
				ucsShader.m_sfFormat = InferShaderFormat(ucsShader.m_pthFilename);
				Console::DebugWarn("Shader type for shader \"" + aArg + "\" inferred as : " + m_mShaderFormatNames[ucsShader.m_sfFormat]);
			}

			if(sstStage == SHADER_STAGE_INVALID) {
				Console::DebugWarn("Stage argument unspecified for shader \"" + aArg + "\". Inferring from file name or contained code...");
				ucsShader.m_sstStage = InferShaderStage(ucsShader.m_pthFilename, ucsShader.m_vFileBlob);
				Console::DebugWarn("Shader stage for shader \"" + aArg + "\" inferred as : " + m_mShaderStageNames[ucsShader.m_sstStage]);
			}

			m_vUncompiledShaders.push_back(ucsShader);
			continue;
		}
		
		Console::DebugWarn("Unrecognized argument: \"" + aArg + "\". Ignoring...");
	}
}

void ShaderCompApplication::Run() {
	this->Start();

	m_bUseMenu ? MenuRoutine() : CommandLineRoutine();

	this->End();
}

void ShaderCompApplication::End() {
	for (const auto& aShader : m_vCompiledShaders) {
		File fShaderAsset(aShader.m_pthFilepath.string(), FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_BINARY);

		uint32 u32CodeSize = aShader.m_vCodeBlob.size();
		uint32 u32VarCount = aShader.m_svtVars.m_vVars.size();

		fShaderAsset.Write(&aShader.m_u32MagicNumber, sizeof(uint32));
		fShaderAsset.Write(&aShader.m_sstType, sizeof(HCShaderStageType));
		fShaderAsset.Write(&u32CodeSize, sizeof(uint32));
		fShaderAsset.Write(aShader.m_vCodeBlob.data(), sizeof(uint32) * u32CodeSize);
		fShaderAsset.Write(&u32VarCount, sizeof(uint32));

		for (const auto& aLabelEntry : aShader.m_svtVars.m_vLabels) {
			fShaderAsset.Write(aLabelEntry.m_strVarName.c_str(), aLabelEntry.m_strVarName.size() + 1); //Fingers crossed this doesn't break it
			fShaderAsset.Write(&aLabelEntry.m_u32Index, sizeof(uint32));
		}

		fShaderAsset.Write(aShader.m_svtVars.m_vVars.data(), sizeof(HCShaderVar) * u32VarCount);

		fShaderAsset.Close();
	}
}

void ShaderCompApplication::CommandLineRoutine() {
	for(const auto& aShader : m_vUncompiledShaders) {
		HCCompiledShader csShader = CompileShader(aShader);
		
		if (csShader.m_vCodeBlob.size() > 0) {
			m_vCompiledShaders.push_back(csShader);
		}
	}
}

void ShaderCompApplication::MenuRoutine() {

}

void ShaderCompApplication::InitializeCompilers() {
	m_vShaderCompilers.push_back(std::make_unique<GLSLCompiler>());
	m_vShaderCompilers.push_back(std::make_unique<HLSLCompiler>());
	m_vShaderCompilers.push_back(std::make_unique<SlangCompiler>());
}

HCCompiledShader ShaderCompApplication::CompileShader(const HCUncompiledShader& _ucsShader) {
	HCCompiledShader csResult;

	for (const uint8 u8Compiler : m_vShaderCompilerOrders[_ucsShader.m_sfFormat]) {
		Console::DebugInfo("Attempting to compile shader \"" + _ucsShader.m_pthFilename.string() + "\" using compiler: " + m_mShaderCompilerNames[static_cast<HCShaderFormat>(u8Compiler)]);
		try {
			csResult = m_vShaderCompilers[u8Compiler]->Compile(_ucsShader);
		}
		catch (const std::exception& e) {
			Console::DebugError("Error occurred when compiling shader! Error:\n\n" + String(e.what()));
			Console::DebugFail("Failed to compile shader \"" + _ucsShader.m_pthFilename.string() + "\" using compiler: " +
				m_mShaderCompilerNames[static_cast<HCShaderFormat>(u8Compiler)] + ". Falling back to next compiler...");
			continue;
		}

		Console::DebugSuccess("Successfully compiled shader \"" + _ucsShader.m_pthFilename.string() + "\" using compiler: " + m_mShaderCompilerNames[static_cast<HCShaderFormat>(u8Compiler)]);
		break;
	}

	return csResult;
}

HCShaderFormat ShaderCompApplication::InferShaderFormat(const FilePath& _strPath) {
	FilePath pthExtension = _strPath.extension();

	if (pthExtension == ".hlsl" || pthExtension == ".fx" || pthExtension == ".fxh") {
		return SHADER_FORMAT_HLSL;
	}
	else if (pthExtension == ".slang" || pthExtension == ".sl") {
		return SHADER_FORMAT_SLANG;
	}

	return SHADER_FORMAT_GLSL; //Default to GLSL if the extensions don't match HLSL or Slang
}

HCShaderStageType ShaderCompApplication::InferShaderStage(const FilePath& _pthFilename, const Array<uint8>& _vFileBlob) {
	String strFilename = _pthFilename.string();

	std::transform(strFilename.begin(), strFilename.end(), strFilename.begin(), [](unsigned char cChar) { return std::tolower(cChar); });

	for (uint8 u8Type = SHADER_STAGE_VERTEX; u8Type < SHADER_STAGE_INVALID; ++u8Type) {
		HCShaderStageType sstType = static_cast<HCShaderStageType>(u8Type);

		if (strFilename.find(m_mShaderStageFilenames[sstType]) != String::npos) {
			return sstType;
		}
	}
	
	String strSource(_vFileBlob.begin(), _vFileBlob.end());

	for (uint8 u8Type = SHADER_STAGE_VERTEX; u8Type < SHADER_STAGE_INVALID; ++u8Type) {
		HCShaderStageType sstType = static_cast<HCShaderStageType>(u8Type);

		String strGLSLAttribute = "#pragma shader_stage(" + m_mGLSLShaderAttributeNames[sstType] + ")";

		String strHLSLAttribute = "[shader(\"" + m_mHLSLShaderAttributeNames[sstType] + "\")]";

		if (strSource.find(strGLSLAttribute) != String::npos || strSource.find(strHLSLAttribute) != String::npos) {
			return sstType;
		}
	}

	return SHADER_STAGE_INVALID;
}

HCShaderFormat ShaderCompApplication::ParseShaderType(const String& _strArg) {
	String strArgCopy = _strArg;

	//Force it to lowercase to make it casing agnostic
	std::transform(strArgCopy.begin(), strArgCopy.end(), strArgCopy.begin(), [](unsigned char cChar) { return std::tolower(cChar); });

	if (strArgCopy == "-glsl") return SHADER_FORMAT_GLSL;
	if (strArgCopy == "-hlsl") return SHADER_FORMAT_HLSL;
	if (strArgCopy == "-slang") return SHADER_FORMAT_SLANG;

	return SHADER_FORMAT_INVALID;
}

HCShaderStageType ShaderCompApplication::ParseShaderStage(const String& _strArg) {
	String strArgCopy = _strArg;

	//Force it to lowercase to make it casing agnostic
	std::transform(strArgCopy.begin(), strArgCopy.end(), strArgCopy.begin(), [](unsigned char cChar) { return std::tolower(cChar); });

	if (strArgCopy == "-vert" || strArgCopy == "-vertex") return SHADER_STAGE_VERTEX;
	if (strArgCopy == "-frag" || strArgCopy == "-fragment" || strArgCopy == "-pix" || strArgCopy == "-pixel") return SHADER_STAGE_FRAGMENT;
	if (strArgCopy == "-geom" || strArgCopy == "-geometry") return SHADER_STAGE_GEOMETRY;
	if (strArgCopy == "-tesc" || strArgCopy == "-tesscontrol" || strArgCopy == "-hull") return SHADER_STAGE_TESSELLATION_CONTROL;
	if (strArgCopy == "-tese" || strArgCopy == "-tessevaluation" || strArgCopy == "-dom" || strArgCopy == "-domain") return SHADER_STAGE_TESSELLATION_EVALUATION;
	if (strArgCopy == "-comp" || strArgCopy == "-compute") return SHADER_STAGE_COMPUTE;
	if (strArgCopy == "-task") return SHADER_STAGE_TASK;
	if (strArgCopy == "-mesh") return SHADER_STAGE_MESH;
	if (strArgCopy == "-rgen" || strArgCopy == "-raygen" || strArgCopy == "-raygeneration") return SHADER_STAGE_RAYGEN;
	if (strArgCopy == "-rahit" || strArgCopy == "-anyhit" || strArgCopy == "-rayanyhit") return SHADER_STAGE_ANY_HIT;
	if (strArgCopy == "-rchit" || strArgCopy == "-closesthit" || strArgCopy == "-rayclosesthit") return SHADER_STAGE_CLOSEST_HIT;
	if (strArgCopy == "-rmiss" || strArgCopy == "-miss" || strArgCopy == "-raymiss") return SHADER_STAGE_MISS;
	if (strArgCopy == "-rint" || strArgCopy == "-intersection" || strArgCopy == "-rayintersection") return SHADER_STAGE_INTERSECTION;
	if (strArgCopy == "-rcall" || strArgCopy == "-callable" || strArgCopy == "-raycallable") return SHADER_STAGE_CALLABLE;

	return SHADER_STAGE_INVALID;
}