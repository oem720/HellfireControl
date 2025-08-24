#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

class AssetManifest;
class AssetLoader;

class AssetManager {
private:
	static AssetManager* m_pInstance;

	std::map<HCUID, std::shared_ptr<Asset>> m_mAssetCache;

	AssetManifest* m_pamManifest = nullptr;

	AssetLoader* m_palLoader = nullptr;

	AssetManager() {}

public:

	AssetManager(AssetManager& _other) = delete;

	void operator=(const AssetManager& _other) = delete;

	static AssetManager* GetInstance();

	void Init();

	std::shared_ptr<Asset> GetAsset(const HCUID& _gId);

	void UnloadAsset(const HCUID& _gId);

	void Cleanup();
};