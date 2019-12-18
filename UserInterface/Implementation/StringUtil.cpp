#include "StringUtil.hpp"

#include <UserInterface/WindowsInterface.hpp>

namespace StringUtil {

    std::wstring StringToWideString(const std::string& s) {
        size_t len = 0;
        size_t slength = s.length() + 1;
        len = static_cast<size_t>(MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(slength), 0, 0));
        wchar_t* buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(slength), buf, static_cast<int>(len));
        std::wstring r(buf);
        delete[] buf;
        return r;
    }
}
