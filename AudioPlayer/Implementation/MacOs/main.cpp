#include <App/AppInstance.hpp>
#include <Display/ErrorDisplay.hpp>
#include <Logging/EasyLogging++.hpp>
#include <FileSystem/ResourceLocator.hpp>
#include <ErrorHandling/Result.hpp>

#include <AudioPlayerApp.hpp>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv)
{
    //START_EASYLOGGINGPP(__argc, __argv);
    // TODO: Should this be here?  Or in App?
    ResourceLocator resourceManager;

    el::Configurations loggingConfig;
    loggingConfig.setGlobally(el::ConfigurationType::Filename, resourceManager.GetLogFileName());
    el::Loggers::reconfigureLogger("default", loggingConfig);
    el::Loggers::reconfigureAllLoggers(loggingConfig);

    AudioPlayerApp app;
    AppInstance appInstance;

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
