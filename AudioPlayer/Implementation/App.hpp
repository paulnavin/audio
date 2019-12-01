#pragma once

#include <Ui/Config.hpp>
#include <Ui/Engine2d.hpp>
#include <Ui/Engine3d.hpp>
#include <Ui/Result.hpp>
#include <Ui/Text2d.hpp>
#include <Ui/TextManager2d.hpp>
#include <Ui/Vertex.hpp>
#include <Ui/WindowsInterface.hpp>

#include "AppTimer.hpp"
#include "ModelStarField.hpp"
#include "ModelTriangle.hpp"

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
    Result RenderFps();
    Result SetFpsText(const int64_t& newFps);
    Result UpdateFps();

private:
    HACCEL acceleratorTable_;
    HINSTANCE appInstance_;
    ::Config::Config config_;
    Engine2d engine2d_;
    Engine3d engine3d_;
    int64_t fps_;
    Text2d fpsText_;  // TODO: Provide this as a renderable object, instead of a raw object.
    double lastFpsCalculationTime_;
    Model3d* model3d_;
    bool showFps_ = true;
    TextManager2d textManager2d_;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_;
};
