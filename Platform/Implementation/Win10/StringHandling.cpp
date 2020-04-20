#include <Platform/StringHandling.hpp>

#include <Platform/WindowsInterface.hpp>
#include <Platform/Stl.hpp>

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

    std::string WideStringToString(const std::wstring& s) {
        static const char defaultChar = '-';
        BOOL usedDefaultChar = FALSE;
        size_t len = 0;
        size_t slength = s.length() + 1;
        len = static_cast<size_t>(WideCharToMultiByte(CP_ACP, 0, s.c_str(), static_cast<int>(slength), 0, 0, &defaultChar, &usedDefaultChar));
        char* buf = new char[len];
        WideCharToMultiByte(CP_ACP, 0, s.c_str(), static_cast<int>(slength), buf, static_cast<int>(len), &defaultChar, &usedDefaultChar);
        std::string r(buf);
        delete[] buf;
        return r;
    }
}
