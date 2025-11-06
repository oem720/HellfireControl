
#include <HellfireControl/Asset/Shader.hpp>

void Shader::Initialize() {

}

std::shared_ptr<Asset> ShaderParser::Parse(File& _fAssetFile) const {
	std::shared_ptr<Shader> pShaderAsset = std::make_shared<Shader>();

	_fAssetFile.Read(&pShaderAsset->m_sstStage, sizeof(HCShaderStageType));

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
