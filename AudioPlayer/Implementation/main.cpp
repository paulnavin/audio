#include <UserInterface/ErrorDisplay.hpp>
#include <Utility/EasyLogging++.hpp>
#include <Utility/ResourceManager.hpp>
#include <Utility/Result.hpp>
#include <Utility/WindowsInterface.hpp>

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

    //START_EASYLOGGINGPP(__argc, __argv);
    ResourceManager resourceManager;

    el::Configurations loggingConfig;
    loggingConfig.setGlobally(el::ConfigurationType::Filename, resourceManager.GetLogFileName());
    el::Loggers::reconfigureLogger("default", loggingConfig);
    el::Loggers::reconfigureAllLoggers(loggingConfig);

    App app;
    
    Result appInitResult = app.Init(hInstance, resourceManager);
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
