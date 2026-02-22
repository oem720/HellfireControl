#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>
#include <HellfireControl/Core/Singleton.hpp>

class AssetManifest;
class AssetLoader;

class AssetManager : public Singleton<AssetManager> {
private:
	Map<HCUID, Shared<Asset>> m_mAssetCache;

	AssetManifest* m_pamManifest = nullptr;
	AssetLoader* m_palLoader = nullptr;
public:
	void Init();
	void Cleanup();

	HCUID AddAssetFromMemory(const Shared<Asset>& _pAsset);
	HCUID LoadAssetFromPath(const String& _strPath);
	Shared<Asset> GetAsset(const HCUID& _gId);
	void UnloadAsset(const HCUID& _gId);

private:
	AssetManager() {}

	friend class Singleton<AssetManager>;
};