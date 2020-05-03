#include <Platform/StringHandling.hpp>

#include <Platform/WindowsInterface.hpp>

namespace StringUtil {

    void StringToWideString(wchar_t* destination, const char* source, size_t maxSize) {
        size_t numberOfNarrowChars = strlen(source) + 1;
        size_t wideByteCount = static_cast<size_t>(MultiByteToWideChar(CP_ACP, 0, source, static_cast<int>(numberOfNarrowChars), 0, 0));

        if (wideByteCount > maxSize) {
            wideByteCount = maxSize;
        }
        MultiByteToWideChar(CP_ACP, 0, source, static_cast<int>(numberOfNarrowChars), destination, static_cast<int>(wideByteCount));
    }


    void WideStringToString(char* destination, const wchar_t* source, size_t maxSize) {
        static const char defaultChar = '-';
        BOOL usedDefaultChar = FALSE;
        size_t numberOfWideChars = wcslen(source) + 1;
        size_t narrowByteCount = static_cast<size_t>(WideCharToMultiByte(CP_ACP, 0, source, static_cast<int>(numberOfWideChars), 0, 0, &defaultChar, &usedDefaultChar));

        if (narrowByteCount > maxSize) {
            narrowByteCount = maxSize;
        }
        WideCharToMultiByte(CP_ACP, 0, source, static_cast<int>(numberOfWideChars), destination, static_cast<int>(narrowByteCount), &defaultChar, &usedDefaultChar);
    }
}
