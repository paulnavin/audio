#pragma once

namespace StringUtil {

    void StringToWideString(wchar_t* destination, const char* source, size_t maxSize);
    void WideStringToString(char* destination, const wchar_t* source, size_t maxSize);
}
