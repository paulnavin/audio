#include <Platform/ErrorDisplay.hpp>

#include <Platform/WindowsInterface.hpp>

namespace ErrorDisplay {

    void ShowErrors(const Result& result) {
        ShowCursor(TRUE);
        MessageBox(NULL, result.Errors(), "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

}
