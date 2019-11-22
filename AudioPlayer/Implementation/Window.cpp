#include "Window.hpp"



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

Result Window::Init(const WNDCLASSEXW& wcex) {
    Result returnValue = {};
    appInstance_ = wcex.hInstance;

    static constexpr size_t MAX_LOADSTRING = 100;
    WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
    LoadStringW(appInstance_, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    // Note: This function results in a message being called through to WindowManager's
    //       ProcessMessage() function, before the HWND is valid.
    windowHandle_ = CreateWindowW(wcex.lpszClassName, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, appInstance_, nullptr);

    if (windowHandle_ == nullptr) {
        returnValue.AppendError("Window::Init() : Error creating window!");
    }

    return returnValue;
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
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(appInstance_, MAKEINTRESOURCE(IDD_ABOUTBOX), windowHandle_, About);
            break;
        default:
            return DefWindowProc(windowHandle_, message, wParam, lParam);
        }
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
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle_, message, wParam, lParam);
    }
    return 0;
}

void Window::Destroy() {
    DestroyWindow(windowHandle_);
}
