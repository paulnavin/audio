#pragma once

#include "WindowsInterface.hpp"

#include "AppTimer.hpp"
#include "Direct2dController.hpp"
#include "Direct3dController.hpp"
#include "Result.hpp"
#include "Text2d.hpp"
#include "TextManager2d.hpp"

class Window;

class App {
public:
    App() = default;
    ~App() = default;

public:
    Result Init(const HINSTANCE& appInstance);
    void Run();
    void Update(const double& dt);
    void Render(const double& dt);
    void ShutDown();

private:
    Result RenderFps();
    Result SetFpsValue(const int64_t& newFps);
    void UpdateFps();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    Direct2dController direct2dController_;
    Direct3dController direct3dController_;
    int64_t fps_;
    Text2d fpsText_;  // TODO: Provide this as a renderable object, instead of a raw object.
    double lastFpsCalculationTime_;
    bool showFps_ = true;
    TextManager2d textManager2d_;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_;
};
