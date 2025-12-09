
#include <HellfireControl/Asset/Shader.hpp>

std::map<HCShaderStageType, HCShaderStageBit> ShaderParser::m_mStageBitTable = {
	{SHADER_STAGE_VERTEX, SHADER_STAGE_VERTEX_BIT},
	{SHADER_STAGE_FRAGMENT, SHADER_STAGE_FRAGMENT_BIT},
	{SHADER_STAGE_GEOMETRY, SHADER_STAGE_GEOMETRY_BIT},
	{SHADER_STAGE_TESSELLATION_CONTROL, SHADER_STAGE_TESSELLATION_CONTROL_BIT},
	{SHADER_STAGE_TESSELLATION_EVALUATION, SHADER_STAGE_TESSELLATION_EVALUATION_BIT},
	{SHADER_STAGE_COMPUTE, SHADER_STAGE_COMPUTE_BIT},
	{SHADER_STAGE_TASK, SHADER_STAGE_TASK_BIT},
	{SHADER_STAGE_MESH, SHADER_STAGE_MESH_BIT},
	{SHADER_STAGE_RAYGEN, SHADER_STAGE_RAYGEN_BIT},
	{SHADER_STAGE_ANY_HIT, SHADER_STAGE_ANY_HIT_BIT},
	{SHADER_STAGE_CLOSEST_HIT, SHADER_STAGE_CLOSEST_HIT_BIT},
	{SHADER_STAGE_MISS, SHADER_STAGE_MISS_BIT},
	{SHADER_STAGE_INTERSECTION, SHADER_STAGE_INTERSECTION_BIT},
	{SHADER_STAGE_CALLABLE, SHADER_STAGE_CALLABLE_BIT}
};

void Shader::Initialize() {

}

std::shared_ptr<Asset> ShaderParser::Parse(File& _fAssetFile) const {
	std::shared_ptr<Shader> pShaderAsset = std::make_shared<Shader>();

	HCShaderStageType sstStage;
	_fAssetFile.Read(&sstStage, sizeof(HCShaderStageType));

	pShaderAsset->m_ssbStage = m_mStageBitTable[sstStage];

	uint32_t u32CodeBlobSize = 0;
	_fAssetFile.Read(&u32CodeBlobSize, sizeof(uint32_t));

	pShaderAsset->m_vCodeBlob.resize(u32CodeBlobSize);
	_fAssetFile.Read(pShaderAsset->m_vCodeBlob.data(), u32CodeBlobSize * sizeof(uint32_t));

	uint32_t u32VarCount = 0;
	_fAssetFile.Read(&u32VarCount, sizeof(uint32_t));

	std::map<std::string, uint32_t> mVarNameTable;

	for (int iCount = 0; iCount < u32VarCount; iCount++) {
		std::string strVarName;
		uint32_t u32VarIndex = 0;
		_fAssetFile.ReadLine(strVarName, FILE_DELIMITER_NULL_TERMINATOR);
		_fAssetFile.Read(&u32VarIndex, sizeof(uint32_t));

		mVarNameTable[strVarName] = u32VarIndex;
	}

	std::vector<HCShaderVar> mVarDataTable;
	mVarDataTable.resize(u32VarCount);

	_fAssetFile.Read(mVarDataTable.data(), u32VarCount * sizeof(HCShaderVar));

	for(const auto& aName : mVarNameTable) {
		pShaderAsset->m_mVariables[aName.first] = mVarDataTable[aName.second];
	}

	return pShaderAsset;
}
