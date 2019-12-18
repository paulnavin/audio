#include <UserInterface/ErrorDisplay.hpp>

#include "StringUtil.hpp"

#include <UserInterface/WindowsInterface.hpp>

namespace ErrorDisplay {

    void ShowErrors(const Result& result) {
        std::wstring errorString = StringUtil::StringToWideString(result.Errors());
        MessageBox(NULL, errorString.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
    }

}
