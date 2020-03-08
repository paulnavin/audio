#pragma once

#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Graphics/Vertex.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInput/InputManager.hpp>
#include <UserInterface/WindowMessageHandler.hpp>
#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

#include "AppTimer.hpp"
#include "AppUserInput.hpp"

class Scene;
class ResourceManager;
class Window;

class App : public WindowMessageHandler {
public:
    App() = default;
    ~App() = default;

public:
    Result Init(const HINSTANCE& appInstance, const ResourceManager& resourceManager);
    Result Run();
    void ShutDown();

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
    void OnCommandToggleScene();
    void OnCommandToggleFullScreen();

    void UpdateMousePosition(const float& x, const float& y);

    Result SelectScene(const uint8_t& newSceneId);

private:
    static constexpr DWORD FRAMES_PER_SECOND = 60;
    static constexpr DWORD MS_PER_SECOND = 1000;
    static constexpr DWORD MS_PER_FRAME = MS_PER_SECOND / FRAMES_PER_SECOND;
    static constexpr int32_t MAX_SKIP_FRAMES = 10;
    static constexpr uint8_t SCENE_COUNT = 2;

private:
    void Update(const double& dt);
    Result UpdateFps();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    ::uc::ConfigStore config_;
    GraphicsEngine graphicsEngine_;
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
    Window* mainWindow_;
    InputManager inputManager_;
    AppUserInput userInputHandler_;
    Scene* scenes_[SCENE_COUNT];
    uint8_t currentSceneId_ = UINT8_MAX;
};
