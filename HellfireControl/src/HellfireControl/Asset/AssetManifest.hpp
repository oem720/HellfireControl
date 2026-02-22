#pragma once

#include <HellfireControl/Asset/AssetCommon.hpp>

#include <HellfireControl/Core/Singleton.hpp>

class AssetManifest : public Singleton<AssetManifest> {
private:
	//TODO: support redirecting strings to compressed archives
	Map<HCUID, String> m_mManifestData;

#if HC_EDITOR
	//This remains here because we only deal with saving to disk if we're in dev mode.
	bool m_bHasChanged = false;
#endif
public:
	void Init();
	void Cleanup();

	[[nodiscard]] HC_INLINE bool Contains(const HCUID& _gId) { return m_mManifestData.contains(_gId); }
	[[nodiscard]] HC_INLINE String GetManifestEntry(const HCUID& _gId) { return m_mManifestData[_gId]; }

#if HC_EDITOR
	void SetManifestEntry(const HCUID& _gId, const String& _strFilepath);
	void RemoveManifestEntry(const HCUID& _gId);
#endif

private:
	AssetManifest() {}

	void ParseFile(File& _fFile);

	friend class Singleton<AssetManifest>;
};