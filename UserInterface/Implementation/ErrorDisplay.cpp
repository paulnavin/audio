#include <UserInterface/ErrorDisplay.hpp>

#include <StringHandling/StringUtil.hpp>
#include <Platform/WindowsInterface.hpp>

namespace ErrorDisplay {

    void ShowErrors(const Result& result) {
        MessageBox(NULL, result.Errors().c_str(), "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

}
