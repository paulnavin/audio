#pragma once

#include <Ui/Config.hpp>
#include <Ui/Engine2d.hpp>
#include <Ui/Engine3d.hpp>
#include <Ui/Rectangle2d.hpp>
#include <Ui/Result.hpp>
#include <Ui/Text2d.hpp>
#include <Ui/TextManager2d.hpp>
#include <Ui/Vertex.hpp>
#include <Ui/WindowsInterface.hpp>

#include "AppTimer.hpp"

class Model2d;
class Model3d;
class Window;

class App {
public:
    App() = default;
    ~App() = default;

public:
    Result Init(const HINSTANCE& appInstance);
    Result Run();
    void ShutDown();

private:
    void Update(const double& dt);
    Result Render(const double& dt);
    Result UpdateFps();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    ::Config::Config config_;
    Engine2d engine2d_;
    Engine3d engine3d_;
    int64_t fps_;
    double lastFpsCalculationTime_;
    Model3d* model3d_;
    Model2d* model2d_;
    bool showFps_ = true;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_;
};
