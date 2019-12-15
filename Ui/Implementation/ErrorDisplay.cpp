#include <Ui/ErrorDisplay.hpp>

#include <Ui/StringUtil.hpp>

#include <Ui/WindowsInterface.hpp>

namespace ErrorDisplay {

    void ShowErrors(const Result& result) {
        std::wstring errorString = StringUtil::StringToWideString(result.Errors());
        MessageBox(NULL, errorString.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
    }

}
