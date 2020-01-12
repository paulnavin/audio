#include <UserInterface/Window.hpp>

#include <UserInterface/WindowConfig.hpp>
#include <UserInterface/WindowMessageHandler.hpp>

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

const HWND Window::GetHandle() const {
    return windowHandle_;
}

const float Window::GetXPosition() const {
    return static_cast<float>(windowRectangle_.left);
}

const float Window::GetYPosition() const {
    return static_cast<float>(windowRectangle_.top);
}

Result Window::Init(const WNDCLASSEXW& wcex, const WindowConfig& config) {
    appInstance_ = wcex.hInstance;

    // Note: This function results in a message being called through to WindowManager's
    //       ProcessMessage() function, before the HWND is valid.
    windowHandle_ = CreateWindowW(wcex.lpszClassName, config.title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, config.width, config.height, nullptr, nullptr, appInstance_, nullptr);

    Result initResult{};
    if (windowHandle_ == nullptr) {
        initResult.AppendError("Window::Init() : Error creating window!");
    }

    RECT clientRect;
    GetWindowRect(windowHandle_, &windowRectangle_);
    GetClientRect(windowHandle_, &clientRect);

    return initResult;
}

void Window::Show() {
    ShowWindow(windowHandle_, TRUE);
    UpdateWindow(windowHandle_);
}

//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - Window is being destroyed (e.g. by cross click or quit).
//  WM_ACTIVATE - Window became active or inactive.
//  WM_MENUCHAR - Menu is open, and user pressed a key.
//  WM_SIZE     - Window got resized.
LRESULT Window::ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam) {
    if (messageHandler_ != nullptr) {
        switch (message) {
            case WM_ACTIVATE: { messageHandler_->OnActivate(); return 0; }
            case WM_CLOSE: { messageHandler_->OnClose(); return 0; }
            case WM_SIZE: { return HandleSizeMessage(wParam); }
            case WM_ENTERSIZEMOVE: { isResizing_ = true; messageHandler_->OnStartSizeOrMove(); return 0; }
            case WM_EXITSIZEMOVE: { isResizing_ = false; messageHandler_->OnFinishSizeOrMove(); return 0; }
        }
    }

    return DefWindowProc(windowHandle_, message, wParam, lParam);
}

void Window::SetWindowMessageHandler(WindowMessageHandler* newHandler) {
    messageHandler_ = newHandler;
}

void Window::Destroy() {
    DestroyWindow(windowHandle_);
}

LRESULT Window::HandleSizeMessage(const WPARAM& wParam) {
    if (wParam == SIZE_MINIMIZED) {
        isMinimised_ = true;
        isMaximised_ = false;
        messageHandler_->OnMinimise();
    } else if (wParam == SIZE_MAXIMIZED) {
        isMinimised_ = false;
        isMaximised_ = true;
        messageHandler_->OnMaximise();
    } else if (wParam == SIZE_RESTORED) {
        isMinimised_ = false;
        isMaximised_ = false;
        if (isResizing_ == false) {
            messageHandler_->OnRestore();
        }
    }
    return 0;
}