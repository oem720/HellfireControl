
#include <HellfireControl/Asset/AssetManager.hpp>

#include <HellfireControl/Asset/AssetManifest.hpp>

#include <HellfireControl/Asset/AssetLoader.hpp>

#include <HellfireControl/Core/Console.hpp>

AssetManager* AssetManager::m_pInstance = nullptr;

AssetManager* AssetManager::GetInstance() {
	if (m_pInstance == nullptr) {
		m_pInstance = new AssetManager();
	}

	return m_pInstance;
}

void AssetManager::Init() {
	m_pamManifest = AssetManifest::GetInstance();
	m_palLoader = AssetLoader::GetInstance();

	m_pamManifest->Init();
	m_palLoader->Init();
}

HCUID AssetManager::AddAssetFromMemory(const Shared<Asset>& _pAsset) {
	if (_pAsset == nullptr) {
		Console::DebugWarn("Attempted to add null asset to AssetManager from memory!");
		return HCUID();
	}

	HCUID gId = HCUID::ConstructRandom();

	m_mAssetCache[gId] = _pAsset;

	return gId;
}

HCUID AssetManager::LoadAssetFromPath(const String& _strPath) {
	HCUID gId = HCUID::ConstructFromFilepath(_strPath);

	if (!std::filesystem::exists(_strPath)) {
		Console::DebugWarn("Asset filepath doesn't exist! Path: " + _strPath);
		return HCUID();
	}

	if(m_pamManifest->Contains(gId)) {
		Console::DebugWarn("Attempted to manually load asset that exists within the manifest. ID: " + gId.AsString());
		return gId;
	}
	else {
		m_pamManifest->SetManifestEntry(gId, _strPath);
	}

	if(m_mAssetCache.contains(gId)) {
		Console::DebugWarn("Attempted to manually load asset that exists within the cache. ID: " + gId.AsString());
		return gId;
	}

	Shared<Asset> pAsset = m_palLoader->LoadAsset(_strPath);

	if (pAsset != nullptr) {
		m_mAssetCache[gId] = pAsset;
		return gId;
	}

	return HCUID();
}

Shared<Asset> AssetManager::GetAsset(const HCUID& _gId) {
	if (m_mAssetCache.contains(_gId)) {
		return m_mAssetCache[_gId];
	}

	if (!m_pamManifest->Contains(_gId)) {
		Console::DebugWarn("Asset ID not found in manifest! ID: " + _gId.AsString());
		return nullptr;
	}

	String strPath = m_pamManifest->GetManifestEntry(_gId);

	if (!std::filesystem::exists(strPath)) {
		Console::DebugWarn("Asset filepath doesn't exist! Path: " + strPath);
		return nullptr;
	}

	Shared<Asset> pAsset = m_palLoader->LoadAsset(strPath);

	if (pAsset != nullptr) {
		m_mAssetCache[_gId] = pAsset;
	}

	return pAsset;
}

void AssetManager::UnloadAsset(const HCUID& _gId) {
	if (!m_mAssetCache.contains(_gId)) {
		Console::DebugWarn("Attempted to unload asset that wasn't loaded! ID: " + _gId.AsString());
		return;
	}

	if (m_mAssetCache[_gId].use_count() > 1) {
		Console::DebugWarn("Attempted to unload asset that is still in use! ID: " + _gId.AsString());
		return;
	}

	m_mAssetCache.erase(_gId);
}

void AssetManager::Cleanup() {
	m_pamManifest->Cleanup();
	m_palLoader->Cleanup();

	m_mAssetCache.clear();

	delete m_pInstance;
}