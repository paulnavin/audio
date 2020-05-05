#include <Platform/WindowManager.hpp>

#include <Platform/AppInstance.hpp>
#include <Platform/Window.hpp>
#include <Platform/WindowConfig.hpp>
#include <Platform/WindowsInterface.hpp>

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Window* window = WindowManager::GetInstance().GetWindow();
    if (window == nullptr) {
        // If the HWND doesn't exist yet, we are getting a message as the new window
        // is being created, so we can use the default processing.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    if (message == WM_DESTROY) {
        // If the last window was just closed, then close the whole app.
        PostQuitMessage(0);

        return 0;
    }

    return window->ProcessMessage(message, wParam, lParam);
}

WindowManager& WindowManager::GetInstance() {
    static WindowManager instance; // Guaranteed to be destroyed.
    return instance;               // Instantiated on first use.
}

Result WindowManager::Init(const AppInstance& appInstance, const WindowConfig& windowConfig) {
    Result result = {};
    WNDCLASSEX wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = appInstance.appHandle;
    wcex.hIcon = windowConfig.appIcon_.GetHandle();
    wcex.hCursor = windowConfig.mouseCursor_.GetHandle();
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = windowConfig.mainWindowClassName_.data();
    wcex.hIconSm = windowConfig.smallAppIcon_.GetHandle();

    if (!RegisterClassEx(&wcex)) {
        result.AppendError("WindowManager::Init() : Error registering window class.");
    }

    Window* newWindow = new Window();
    result = newWindow->Init(wcex, windowConfig);
    if (result.IsOkay()) {
        window_ = newWindow;
    } else {
        delete newWindow;
        result.AppendError("WindowManager::Init() : Couldn't init new window.");
    }

    return result;
}

Window* WindowManager::GetWindow() {
    return window_;
}

WindowManager::~WindowManager() {
    delete window_;
    window_ = nullptr;
}
