
#include <HellfireControl/Util/Util.hpp>

#include <codecvt>
#include <locale>

namespace Util {
    [[nodiscard]] std::wstring ConvertToWString(const String& _strConvert) {
        return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(_strConvert);
    }

	[[nodiscard]] String ConvertFromWString(const std::wstring& _strConvert) {
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(_strConvert);
	}

	[[nodiscard]] Array<char> ReadFile(const String& _strFilename) {
		std::ifstream fFile(_strFilename, std::ios::ate | std::ios::binary);

		if (!fFile.is_open()) {
			throw std::runtime_error("ERROR: Failed to open file!");
		}

		size_t sFileSize = static_cast<size_t>(fFile.tellg());
		Array<char> vBuffer(sFileSize);

		fFile.seekg(0);
		fFile.read(vBuffer.data(), sFileSize);
		fFile.close();

		return vBuffer;
	}
}
