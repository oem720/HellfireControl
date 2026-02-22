#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>
#include <HellfireControl/Core/Singleton.hpp>

class AssetLoader : public Singleton<AssetLoader> {
private:
	Map<uint32, Unique<AssetParser>> m_mAssetParsers;
public:
	void Init();
	void Cleanup();

	Shared<Asset> LoadAsset(const String& _strPath);

private:
	AssetLoader() {}

	friend class Singleton<AssetLoader>;
};