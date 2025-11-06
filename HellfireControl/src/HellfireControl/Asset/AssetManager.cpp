
#include <HellfireControl/Asset/AssetManager.hpp>

#include <HellfireControl/Asset/AssetManifest.hpp>

#include <HellfireControl/Asset/AssetLoader.hpp>

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

std::shared_ptr<Asset> AssetManager::LoadAssetFromPath(const std::string& _strPath) {
	if(m_mAssetCache.contains(HCUID::ConstructFromFilepath(_strPath))) {
		return m_mAssetCache[HCUID::ConstructFromFilepath(_strPath)];
	}

	if (!std::filesystem::exists(_strPath)) {
		std::cout << "WARNING: Asset filepath doesn't exist! Path: " << _strPath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Asset> pAsset = m_palLoader->LoadAsset(_strPath);

	if (pAsset != nullptr) {
		HCUID gId = HCUID::ConstructFromFilepath(_strPath);
		m_mAssetCache[gId] = pAsset;
	}

	return pAsset;
}

std::shared_ptr<Asset> AssetManager::GetAsset(const HCUID& _gId) {
	if (m_mAssetCache.contains(_gId)) {
		return m_mAssetCache[_gId];
	}

	if (!m_pamManifest->Contains(_gId)) {
		std::cout << "WARNING: Asset ID not found! ID: " << _gId << std::endl;
		return nullptr;
	}

	std::string strPath = m_pamManifest->GetManifestEntry(_gId);

	if (!std::filesystem::exists(strPath)) {
		std::cout << "WARNING: Asset filepath doesn't exist! Path: " << strPath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Asset> pAsset = m_palLoader->LoadAsset(strPath);

	if (pAsset != nullptr) {
		m_mAssetCache[_gId] = pAsset;
	}

	return pAsset;
}

void AssetManager::UnloadAsset(const HCUID& _gId) {
	if (!m_mAssetCache.contains(_gId)) {
		std::cout << "WARNING: Attempted to unload asset that wasn't loaded! ID: " << _gId << std::endl;
		return;
	}

	if (m_mAssetCache[_gId].use_count() > 1) {
		std::cout << "WARNING: Asset being unloaded is still in use -- Unload aborted. Current use count: " << m_mAssetCache[_gId].use_count() - 1 << ". ID: " << _gId << std::endl;
		return;
	}

	m_mAssetCache.erase(_gId);
}

void AssetManager::Cleanup() {
	m_pamManifest->Cleanup();
	m_palLoader->Cleanup();

	delete m_pInstance;
}