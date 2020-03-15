#include <UserInterface/Window.hpp>

#include <UserInterface/WindowConfig.hpp>
#include <UserInterface/WindowMessageHandler.hpp>

const HWND Window::GetHandle() const {
    return windowHandle_;
}

const float Window::GetWidth() const {
    return width_;
}

const float Window::GetHeight() const {
    return height_;
}

Result Window::Init(const WNDCLASSEXW& wcex, const WindowConfig& config) {
    appInstance_ = wcex.hInstance;

    // Note: This function results in a message being called through to WindowManager's
    //       ProcessMessage() function, before the HWND is valid.
    windowHandle_ = CreateWindowW(wcex.lpszClassName, config.title.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, config.width, config.height, nullptr, nullptr, appInstance_, nullptr);

    Result initResult{};
    if (windowHandle_ == nullptr) {
        initResult.AppendError("Window::Init() : Error creating window!");
    }

    ShowCursor(config.showCursor_);

    UpdateSizes();
    
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
            case WM_SIZE: { HandleSizeMessage(wParam); return 0; }
            case WM_ENTERSIZEMOVE: { isResizing_ = true; messageHandler_->OnStartSizeOrMove(); return 0; }
            case WM_EXITSIZEMOVE: { isResizing_ = false; messageHandler_->OnFinishSizeOrMove(); return 0; }
            case WM_MENUCHAR: { return DisableAnnoyingMenuBeepingSound(); }
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

void Window::HandleSizeMessage(const WPARAM& wParam) {
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
            UpdateSizes();
            messageHandler_->OnRestore();
        }
    }
}

LRESULT Window::DisableAnnoyingMenuBeepingSound() {
    return MAKELRESULT(0, MNC_CLOSE);
}

void Window::UpdateSizes() {
    GetClientRect(windowHandle_, &clientArea_);

    width_ = static_cast<float>(clientArea_.right - clientArea_.left);
    height_ = static_cast<float>(clientArea_.bottom - clientArea_.top);
}