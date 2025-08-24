#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

class AssetLoader {
private:
	static AssetLoader* m_pInstance;

	std::map<uint32_t, std::unique_ptr<AssetParser>> m_mAssetParsers;

	AssetLoader() {}

public:	
	AssetLoader(AssetLoader& _other) = delete;

	void operator=(const AssetLoader& _other) = delete;

	static AssetLoader* GetInstance();

	void Init();

	std::shared_ptr<Asset> LoadAsset(const std::string& _strPath);

	void Cleanup();
};