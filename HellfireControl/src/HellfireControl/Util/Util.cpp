
#include <HellfireControl/Util/Util.hpp>

#include <codecvt>
#include <locale>

namespace Util {
    [[nodiscard]] std::wstring ConvertToWString(const std::string& _strConvert) {
        return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(_strConvert);
    }
}
