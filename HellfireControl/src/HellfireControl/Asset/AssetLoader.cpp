
#include <HellfireControl/Asset/AssetLoader.hpp>

#include <HellfireControl/Asset/Font.hpp>

AssetLoader* AssetLoader::m_pInstance = nullptr;

AssetLoader* AssetLoader::GetInstance() {
	if (m_pInstance == nullptr) {
		m_pInstance = new AssetLoader();
	}

	return m_pInstance;
}

void AssetLoader::Init() {
	m_mAssetParsers[HC_FONT_IDENTIFIER] = std::make_unique<FontParser>();
}

std::shared_ptr<Asset> AssetLoader::LoadAsset(const std::string& _strPath) {
	File fAsset(_strPath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);

	uint32_t u32MagicNumber;
	fAsset.Read(&u32MagicNumber, sizeof(uint32_t));

	return m_mAssetParsers[u32MagicNumber]->Parse(fAsset);
}

void AssetLoader::Cleanup() {
	m_mAssetParsers.clear();
}