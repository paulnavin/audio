#include "WindowsInterface.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"

// Global Variables:
HINSTANCE hInst;                                // current instance
Window* mainWindow = nullptr;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    hInst = hInstance; // Store instance handle in our global variable

    // TODO: Handle initialisation errors.
    WindowManager& windowManager = WindowManager::GetInstance();
    windowManager.Init(hInstance);
    mainWindow = windowManager.CreateNewWindow();
    mainWindow->Show();

    // TODO: Place code here.

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AUDIOPLAYER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}
