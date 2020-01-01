#include <UserInterface/Window.hpp>

#include <UserInterface/WindowConfig.hpp>

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

    switch (message) {
        case WM_COMMAND:
        {
            return DefWindowProc(windowHandle_, message, wParam, lParam);
            //int wmId = LOWORD(wParam);
            //// Parse the menu selections:
            //switch (wmId) {
            //case IDM_ABOUT:
            //    DialogBox(appInstance_, MAKEINTRESOURCE(IDD_ABOUTBOX), windowHandle_, About);
            //    break;
            //default:
            //    return DefWindowProc(windowHandle_, message, wParam, lParam);
            //}
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(windowHandle_, &ps);

            UNREFERENCED_PARAMETER(hdc);

            // TODO: Add any drawing code that uses hdc here...
        
            EndPaint(windowHandle_, &ps);
        }
        break;
        case WM_KEYUP:
        {
            HandleKeyUp(wParam);
            break;
        }
        default:
            return DefWindowProc(windowHandle_, message, wParam, lParam);
    }
    return 0;
}

void Window::Destroy() {
    DestroyWindow(windowHandle_);
}

void Window::HandleKeyUp(const WPARAM& wParam) {
    switch (wParam) {
        case VK_ESCAPE:
            PostMessage(windowHandle_, WM_CLOSE, 0, 0);
            break;

        default: break;
    }
}