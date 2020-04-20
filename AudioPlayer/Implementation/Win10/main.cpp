#include <Display/ErrorDisplay.hpp>
#include <Logging/EasyLogging++.hpp>
#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>
#include <Resources/ResourceLocator.hpp>

#include "AudioPlayerApp.hpp"

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

    // TODO: Should this be here?  Or in App?
    ResourceLocator resourceManager;

    el::Configurations loggingConfig;
    loggingConfig.setGlobally(el::ConfigurationType::Filename, resourceManager.GetLogFileName());
    el::Loggers::reconfigureLogger("default", loggingConfig);
    el::Loggers::reconfigureAllLoggers(loggingConfig);

    AudioPlayerApp app;
    AppInstance appInstance{ hInstance };

    Result appInitResult = app.Init(appInstance, resourceManager);
    if (appInitResult.HasErrors()) {
        ErrorDisplay::ShowErrors(appInitResult);
        return 1;
    }

    Result appRunResult = app.Run();
    if (appRunResult.HasErrors()) {
        ErrorDisplay::ShowErrors(appRunResult);
        return 1;
    }

    // TODO: Maybe don't shutdown in release mode, just quit...?
    app.ShutDown();
    return 0;
}
