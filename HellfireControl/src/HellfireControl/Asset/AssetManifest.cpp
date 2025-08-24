
#include <HellfireControl/Asset/AssetManifest.hpp>

#include <HellfireControl/Core/File.hpp>

#define HC_MANIFEST_PATH "./Assets/asset_manifest.hcman"

#if HC_EDITOR
#define HC_MANIFEST_EDIT_FLAGS FILE_OPEN_FLAG_WRITE | FILE_OPEN_FLAG_ASCII
#define HC_MANIFEST_OPEN_FLAGS FILE_OPEN_FLAG_READ | HC_MANIFEST_EDIT_FLAGS
#else
#define HC_MANIFEST_OPEN_FLAGS FILE_OPEN_FLAG_READ | FILE_OPEN_FLAG_BINARY
#endif

AssetManifest* AssetManifest::m_pInstance = nullptr;

AssetManifest* AssetManifest::GetInstance() {
	if (m_pInstance == nullptr) {
		m_pInstance = new AssetManifest();
	}

	return m_pInstance;
}

void AssetManifest::Init() {
	File fManifest(HC_MANIFEST_PATH, HC_MANIFEST_OPEN_FLAGS);

	if (fManifest.IsNewlyCreated()) {
		m_bHasChanged = true;
		fManifest.Close();
		return;
	}

	uint32_t u32MagicNumber;
	fManifest.Read(&u32MagicNumber, sizeof(uint32_t));

	if (u32MagicNumber != HC_MANIFEST_IDENTIFIER) {
		throw std::runtime_error("ERROR: Asset manifest malformed or corrupted!");
	}

	ParseFile(fManifest);

	fManifest.Close();
}

#if HC_EDITOR
void AssetManifest::SetManifestEntry(const HCUID& _gId, const std::string& _strFilepath) {
	m_mManifestData[_gId] = _strFilepath;

	m_bHasChanged = true;
}

void AssetManifest::RemoveManifestEntry(const HCUID& _gId) {
	if (!m_mManifestData.contains(_gId)) {
		return;
	}

	m_mManifestData.erase(_gId);

	m_bHasChanged = true;
}

void AssetManifest::ParseFile(File& _fManifest) {
	uint8_t u8Spacer; //Annoyingly, advancing the pointer of the file doesn't remove the newline char from the input stream.
	_fManifest.Read(&u8Spacer, sizeof(uint8_t)); //This is why I must create a dummy value that I don't care about.

	struct {
		std::string m_strId;
		std::string m_strIndex;
		std::string m_strPath;
	} manifestLine;

	while (!_fManifest.AtEOF()) {
		_fManifest.ReadLine(manifestLine.m_strId, FILE_DELIMITER_SPACE);
		_fManifest.ReadLine(manifestLine.m_strIndex, FILE_DELIMITER_SPACE); //Unused for now
		_fManifest.ReadLine(manifestLine.m_strPath, FILE_DELIMITER_NEWLINE);

		if (manifestLine.m_strId == "") {
			continue;
		}

		//TODO: Replace with proper manifest entry.
		m_mManifestData[HCUID::ConstructFromGUIDString(manifestLine.m_strId)] = manifestLine.m_strPath;
	}
}
#else
void AssetManifest::ParseFile(File& _fManifest) {
	struct {
		HCUID m_gId;
		uint16_t m_u16Index;
		std::string m_strPath;
	} manifestLine;

	while (!_fManifest.AtEOF()) {
		_fManifest.Read(&manifestLine.m_gId, sizeof(HCUID));
		_fManifest.Read(&manifestLine.m_u16Index, sizeof(HCUID));
		_fManifest.ReadLine(manifestLine.m_strPath, FILE_DELIMITER_NEWLINE); //Improper implementation for now

		//TODO: Replace with proper manifest entry.
		m_mManifestData[manifestLine.m_gId] = manifestLine.m_strPath;
	}
}
#endif

void AssetManifest::Cleanup() {
#if HC_EDITOR
	if (m_bHasChanged) {
		File fManifest(HC_MANIFEST_PATH, HC_MANIFEST_EDIT_FLAGS);

		uint32_t u32Magic = HC_MANIFEST_IDENTIFIER;
		fManifest.WriteLine(&u32Magic, sizeof(uint32_t), FILE_DELIMITER_NEWLINE);

		for (const auto& aEntry : m_mManifestData) {
			fManifest.WriteLine(aEntry.first.AsString(), FILE_DELIMITER_SPACE);
			fManifest.WriteLine(std::to_string(0), FILE_DELIMITER_SPACE); //Unused for now
			fManifest.WriteLine(aEntry.second, FILE_DELIMITER_NEWLINE);
		}

		fManifest.Close();
	}
#endif

	delete m_pInstance;
}