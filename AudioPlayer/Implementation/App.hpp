#pragma once

#include "WindowsInterface.hpp"

#include "AppTimer.hpp"
#include "Result.hpp"

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
    void UpdateFps();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    int64_t fps_;
    double lastFpsCalculationTime_;
    Window* mainWindow_;
    AppTimer timer_;
    int64_t totalAppFrames_;
#pragma warning(push)
#pragma warning(disable : 4820) // Padding.
    bool showFps_ = true;
};
#pragma warning(pop)
