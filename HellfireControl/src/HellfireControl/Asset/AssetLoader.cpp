
#include <HellfireControl/Asset/AssetLoader.hpp>

#include <HellfireControl/Asset/Font.hpp>
#include <HellfireControl/Asset/Shader.hpp>

void AssetLoader::Init() {
	m_mAssetParsers[HC_FONT_IDENTIFIER] = std::make_unique<FontParser>();
	m_mAssetParsers[HC_SHADER_IDENTIFIER] = std::make_unique<ShaderParser>();
}

Shared<Asset> AssetLoader::LoadAsset(const String& _strPath) {
	File fAsset(_strPath, FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY);

	uint32 u32MagicNumber;
	fAsset.Read(&u32MagicNumber, sizeof(uint32));

	return m_mAssetParsers[u32MagicNumber]->Parse(fAsset);
}

void AssetLoader::Cleanup() {
	m_mAssetParsers.clear();

	Singleton<AssetLoader>::DestroyInstance();
}