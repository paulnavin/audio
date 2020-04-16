#pragma once

#include <App/AppTimer.hpp>
#include <Display/WindowConfig.hpp>
#include <Display/WindowMessageHandler.hpp>
#include <ErrorHandling/Result.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Vertex.hpp>
#include <Platform/AppInstance.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInput/InputManager.hpp>
#include <UserInterface/Commander.hpp>
#include <UserInterface/ModelPortal.hpp>
#include <UserInterface/Rectangle2d.hpp>
#include <UserInterface/Text2d.hpp>

class AppUserInput;
class Scene;
class ResourceLocator;
class Window;

class App : public WindowMessageHandler {
public:
    App() = default;
    virtual ~App() = default;

public:
    Result SetWindowConfig(const WindowConfig& windowConfig);
    Result SetConfigFileName(const std::string& fileName);
    void SetUserInputHandler(AppUserInput* appUserInputHandler);
    virtual Result Init(const AppInstance& appInstance, const ResourceLocator& resourceManager);
    virtual Result Run();
    virtual void ShutDown();

public:
    // Window Handling
    virtual void OnActivate() override;
    virtual void OnClose() override;
    virtual void OnMinimise() override;
    virtual void OnMaximise() override;
    virtual void OnRestore() override;
    virtual void OnStartSizeOrMove() override;
    virtual void OnFinishSizeOrMove() override;

    // User Input Commands
    void OnCommandNextDisplayConfig();
    void OnCommandPreviousDisplayConfig();
    void OnCommandQuit();
    void OnCommandResetDisplayConfig();
    void OnCommandToggleFullScreen();

    void HandleAppCommand(const Command::Id& command);

    Result SelectScene(Scene* newScene);
    Result PushScene(Scene* newScene);
    void PopScene();
    void PopAllScenes();
    void ReinitialiseScenes();

private:
    static constexpr float FRAMES_PER_SECOND = 60.0f;
    static constexpr float MS_PER_SECOND = 1000.0f;
    static constexpr float MS_PER_FRAME = MS_PER_SECOND / FRAMES_PER_SECOND;
    static constexpr int32_t MAX_SKIP_FRAMES = 10;
    static constexpr uint8_t MAX_SCENE_COUNT = 10;
    static constexpr uint8_t ACTUAL_SCENE_COUNT = 3;

private:
    void Update(const double& dt);
    Result UpdateFps();

protected:
    AppInstance appInstance_;
    ConfigStore config_;
    InputManager inputManager_;

private:
    Commander keen_;
    GraphicsEngine graphicsEngine_;
    ModelPortal portal_;
    ResourceManager resourceManager_;
    bool initialised_ = false;
    bool finished_ = false;
    bool paused_ = false;
    bool resizeRequired_ = false;
    bool toggleFullScreen_ = false;
    int64_t fps_;
    double lastFpsCalculationTime_;
    bool showFps_ = true;
    bool showMousePosition_ = true;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_ = nullptr;
    WindowConfig mainWindowConfig_;
    std::string configFileName_;
    AppUserInput* userInputHandler_ = nullptr;
    std::deque<Scene*> currentScenes_;
};
