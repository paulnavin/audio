#include <Ui/WindowsInterface.hpp>
#include <Ui/EasyLogging++.hpp>
#include <Ui/ErrorDisplay.hpp>
#include <Ui/Result.hpp>

#include "App.hpp"

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
        ErrorDisplay::ShowErrors(appInitResult);
        return 1;
    }

    Result appRunResult = app.Run();
    if (appRunResult.HasErrors()) {
        ErrorDisplay::ShowErrors(appRunResult);
        return 1;
    }
    
    app.ShutDown();
    return 0;
}
