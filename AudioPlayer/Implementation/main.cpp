#include "WindowsInterface.hpp"
#include "EasyLogging++.hpp"
#include "Result.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"

// Global Variables:
HINSTANCE hInst = nullptr;      // The instance for the whole application.
Window* mainWindow = nullptr;   // The main window. Der.

void ShowErrors(const Result& result);

INITIALIZE_EASYLOGGINGPP

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    hInst = hInstance; // Store instance handle in our global variable

    WindowManager& windowManager = WindowManager::GetInstance();
    Result initResult = windowManager.Init(hInstance);

    if (initResult.HasErrors()) {
        ShowErrors(initResult);
        return 1;
    }

    LOG(ERROR) << "Successfully initialised WindowManager!";

    Result createWindowResult = windowManager.CreateNewWindow(&mainWindow);
    if (createWindowResult.HasErrors()) {
        ShowErrors(createWindowResult);
        return 1;
    }

    mainWindow->Show();

    Window* anotherWindow = nullptr;

    Result secondCreateWindowResult = windowManager.CreateNewWindow(&anotherWindow);
    if (secondCreateWindowResult.HasErrors()) {
        ShowErrors(secondCreateWindowResult);
        return 1;
    }

    anotherWindow->Show();

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

std::wstring s2ws(const std::string& s) {
    size_t len = 0;
    size_t slength = s.length() + 1;
    len = static_cast<size_t>(MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(slength), 0, 0));
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(slength), buf, static_cast<int>(len));
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void ShowErrors(const Result& result) {
    std::wstring errorString = s2ws(result.Errors());
    MessageBox(NULL, errorString.c_str(), L"Error!",
        MB_ICONEXCLAMATION | MB_OK);
}