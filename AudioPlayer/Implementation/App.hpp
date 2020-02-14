#pragma once

#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Graphics/Vertex.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInput/InputManager.hpp>
#include <UserInterface/WindowMessageHandler.hpp>
#include <Utility/Result.hpp>
#include <Utility/WindowsInterface.hpp>

#include "AppTimer.hpp"
#include "AppUserInput.hpp"

class Model2d;
class Model3d;
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
    void OnCommandMouseClicked(const float& x, const float& y);
    void OnCommandNextDisplayConfig();
    void OnCommandPreviousDisplayConfig();
    void OnCommandQuit();
    void OnCommandRecreateModels();
    void OnCommandResetDisplayConfig();
    void OnCommandShowFps();
    void OnCommandShowMousePosition();
    void OnCommandToggle2dModel();
    void OnCommandToggleFullScreen();

    void UpdateMousePosition(const float& x, const float& y);

private:
    static constexpr DWORD FRAMES_PER_SECOND = 60;
    static constexpr DWORD MS_PER_SECOND = 1000;
    static constexpr DWORD MS_PER_FRAME = MS_PER_SECOND / FRAMES_PER_SECOND;
    static constexpr int32_t MAX_SKIP_FRAMES = 10;

private:
    void Update(const double& dt);
    Result Render(const double& dt);
    void SetActive2dModel(Model2d* newActiveModel);
    Result UpdateFps();

    // Modelling
    void Destroy3dModel();
    void Destroy2dModel();
    Result Create3dModel();
    Result Create2dModel();

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
    Model3d* model3d_;
    Model2d* djModel2d_;
    Model2d* basicModel2d_;
    Model2d* active2dModel_;
    bool showFps_ = true;
    bool showMousePosition_ = true;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_;
    AppUserInput userInputHandler_;
};
