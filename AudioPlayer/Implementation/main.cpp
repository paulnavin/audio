#include "WindowsInterface.hpp"
#include "App.hpp"
#include "EasyLogging++.hpp"
#include "Result.hpp"
#include "StringUtil.hpp"

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

void ShowErrors(const Result& result) {
    std::wstring errorString = StringUtil::StringToWideString(result.Errors());
    MessageBox(NULL, errorString.c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
}
