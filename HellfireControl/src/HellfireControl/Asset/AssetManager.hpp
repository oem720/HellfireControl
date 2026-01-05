#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

class AssetManifest;
class AssetLoader;

class AssetManager {
private:
	static AssetManager* m_pInstance;

	Map<HCUID, Shared<Asset>> m_mAssetCache;

	AssetManifest* m_pamManifest = nullptr;

	AssetLoader* m_palLoader = nullptr;

	AssetManager() {}

public:

	AssetManager(AssetManager& _other) = delete;

	void operator=(const AssetManager& _other) = delete;

	static AssetManager* GetInstance();

	void Init();

	HCUID AddAssetFromMemory(const Shared<Asset>& _pAsset);

	HCUID LoadAssetFromPath(const String& _strPath);

	Shared<Asset> GetAsset(const HCUID& _gId);

	void UnloadAsset(const HCUID& _gId);

	void Cleanup();
};