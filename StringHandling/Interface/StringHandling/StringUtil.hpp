#pragma once

#include <Stl/StlWrapper.hpp>

namespace StringUtil {

    std::wstring StringToWideString(const std::string& s);
    std::string WideStringToString(const std::wstring& s);
}
