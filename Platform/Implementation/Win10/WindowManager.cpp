#include <Platform/WindowManager.hpp>

#include <Platform/AppInstance.hpp>
#include <Platform/Window.hpp>
#include <Platform/WindowConfig.hpp>

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return WindowManager::GetInstance().ProcessMessage(hWnd, message, wParam, lParam);
}

WindowManager& WindowManager::GetInstance() {
    static WindowManager instance; // Guaranteed to be destroyed.
    return instance;               // Instantiated on first use.
}

Result WindowManager::Init(const AppInstance& appInstance, const WindowConfig& windowConfig) {
    Result returnValue = {};
    wcex_.cbSize = sizeof(WNDCLASSEX);

    wcex_.style = CS_HREDRAW | CS_VREDRAW;
    wcex_.lpfnWndProc = WndProc;
    wcex_.cbClsExtra = 0;
    wcex_.cbWndExtra = 0;
    wcex_.hInstance = appInstance.appHandle;
    wcex_.hIcon = windowConfig.appIcon_.GetHandle();
    wcex_.hCursor = windowConfig.mouseCursor_.GetHandle();
    wcex_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex_.lpszClassName = windowConfig.mainWindowClassName_.data();
    wcex_.hIconSm = windowConfig.smallAppIcon_.GetHandle();

    if (!RegisterClassEx(&wcex_)) {
        returnValue.AppendError("WindowManager::Init() : Error registering window class.");
    }
    return returnValue;
}

// Note: Can't call this CreateWindow, because that is a macro defined by Windows.
Result WindowManager::CreateNewWindow(const WindowConfig& config, Window** windowToReturn) {
    Result returnValue = {};
    // TODO: Handle initialisation errors.
    Window* newWindow = new Window();
    *windowToReturn = newWindow;
    returnValue = newWindow->Init(wcex_, config);
    if (returnValue.IsOkay()) {
        HWND newWindowHandle = newWindow->GetHandle();
        windows_[newWindowHandle] = newWindow;
    } else {
        returnValue.AppendError("WindowManager::CreateNewWindow() : Couldn't init new window.");
    }

    return returnValue;
}

//  WM_COMMAND  - process the application menu
//  WM_DESTROY  - post a quit message and return
LRESULT WindowManager::ProcessMessage(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam) {
    HandleToWindowMap::iterator windowFinder = windows_.find(hWnd);
    if (windowFinder != windows_.end()) {
        Window* window = windowFinder->second;
        if (message == WM_DESTROY) {
            // Don't need to call Destroy() here, as it's already being destroyed.
            windows_.erase(hWnd);
            delete window;
            window = nullptr;

            // If the last window was just closed, then close the whole app.
            if (windows_.empty() == true) {
                PostQuitMessage(0);
            }

            return 0;
        }
        return window->ProcessMessage(message, wParam, lParam);
    } else {
        // If the HWND doesn't exist yet, we are getting a message as the new window
        // is being created, so we can use the default processing.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

WindowManager::~WindowManager() {
    HandleToWindowMap::iterator windowFinder = windows_.begin();
    HandleToWindowMap::iterator windowEnd = windows_.end();
    while (windowFinder != windowEnd) {
        Window* window = windowFinder->second;
        windowFinder = windows_.erase(windowFinder);
        window->Destroy();
        delete window;
    }
}
