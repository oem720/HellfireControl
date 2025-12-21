#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

class AssetManifest {
private:
	static AssetManifest* m_pInstance;

	//TODO: support redirecting strings to compressed archives
	Map<HCUID, String> m_mManifestData;

#if HC_EDITOR
	//This remains here because we only deal with saving to disk if we're in dev mode.
	bool m_bHasChanged = false;
#endif

	AssetManifest() {}

	void ParseFile(File& _fFile);
public:
	AssetManifest(AssetManifest& _other) = delete;

	void operator=(const AssetManifest& _other) = delete;

	static AssetManifest* GetInstance();

	void Init();

	[[nodiscard]] HC_INLINE bool Contains(const HCUID& _gId) { return m_mManifestData.contains(_gId); }

	[[nodiscard]] HC_INLINE String GetManifestEntry(const HCUID& _gId) { return m_mManifestData[_gId]; }

#if HC_EDITOR
	void SetManifestEntry(const HCUID& _gId, const String& _strFilepath);

	void RemoveManifestEntry(const HCUID& _gId);
#endif

	void Cleanup();
};