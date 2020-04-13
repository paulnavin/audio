#include <Display/ErrorDisplay.hpp>

#include <Platform/WindowsInterface.hpp>

namespace ErrorDisplay {

    void ShowErrors(const Result& result) {
        ShowCursor(TRUE);
        MessageBox(NULL, result.Errors().c_str(), "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

}
