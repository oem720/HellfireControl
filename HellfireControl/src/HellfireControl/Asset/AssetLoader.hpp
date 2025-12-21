#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

class AssetLoader {
private:
	static AssetLoader* m_pInstance;

	Map<uint32, UniquePointer<AssetParser>> m_mAssetParsers;

	AssetLoader() {}

public:	
	AssetLoader(AssetLoader& _other) = delete;

	void operator=(const AssetLoader& _other) = delete;

	static AssetLoader* GetInstance();

	void Init();

	SharedPointer<Asset> LoadAsset(const String& _strPath);

	void Cleanup();
};