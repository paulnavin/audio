#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/Engine3d.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Graphics/TextManager2d.hpp>
#include <Graphics/Vertex.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInput/InputManager.hpp>
#include <UserInterface/WindowMessageHandler.hpp>
#include <Utility/Result.hpp>
#include <Utility/WindowsInterface.hpp>

#include "AppTimer.hpp"

class Model2d;
class Model3d;
class Window;

class App : public WindowMessageHandler {
public:
    App() = default;
    ~App() = default;

public:
    Result Init(const HINSTANCE& appInstance);
    Result Run();
    void ShutDown();

public:
    virtual void OnActivate() override;
    virtual void OnClose() override;
    virtual void OnResize() override;
    virtual void OnMinimise() override;
    virtual void OnMaximise() override;
    virtual void OnRestore() override;
    virtual void OnStartSizeOrMove() override;
    virtual void OnFinishSizeOrMove() override;

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

    void Destroy3dModel();
    void Destroy2dModel();
    Result Create3dModel();
    Result Create2dModel();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    ::uc::ConfigStore config_;
    Engine2d engine2d_;
    Engine3d engine3d_;
    bool finished_ = false;
    bool paused_ = false;
    bool resizeRequired_ = false;
    int64_t fps_;
    InputManager inputManager_;
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
};
