#include "WindowsInterface.hpp"
#include "App.hpp"
#include "EasyLogging++.hpp"
#include "Result.hpp"

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

    App app;
    Result appInitResult = app.Init(hInstance);
    if (appInitResult.HasErrors()) {
        ShowErrors(appInitResult);
        return 1;
    }
    app.Run();
    app.ShutDown();
    return 0;
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