#pragma once

#include <Platform/Stl.hpp>

namespace StringUtil {

    std::wstring StringToWideString(const std::string& s);
    std::string WideStringToString(const std::wstring& s);
}
