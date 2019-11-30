#include "WindowManager.hpp"

static constexpr size_t MAX_LOADSTRING = 100;
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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

Result WindowManager::Init(const HINSTANCE& hInstance) {
    Result returnValue = {};
    // Initialize global strings
    LoadStringW(hInstance, IDC_AUDIOPLAYER, szWindowClass, MAX_LOADSTRING);
    
    wcex_.cbSize = sizeof(WNDCLASSEX);

    wcex_.style = CS_HREDRAW | CS_VREDRAW;
    wcex_.lpfnWndProc = WndProc;
    wcex_.cbClsExtra = 0;
    wcex_.cbWndExtra = 0;
    wcex_.hInstance = hInstance;
    wcex_.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AUDIOPLAYER));
    wcex_.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_DARK_OXYGEN_CURSOR_NORMAL));
    wcex_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex_.lpszMenuName = MAKEINTRESOURCEW(IDC_AUDIOPLAYER);
    wcex_.lpszClassName = szWindowClass;
    wcex_.hIconSm = LoadIcon(wcex_.hInstance, MAKEINTRESOURCE(IDI_MONKEY_ICON));

    if (!RegisterClassExW(&wcex_)) {
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
    // The user chose "Exit" from the menu, so quit everything.
    if (message == WM_COMMAND) {
        int wmId = LOWORD(wParam);
        if (wmId == IDM_EXIT) {
            PostQuitMessage(0);
            return 0;
        }
    }
    
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
