#pragma once

#include "WindowsInterface.hpp"

#include "AppTimer.hpp"
#include "Config.hpp"
#include "Engine2d.hpp"
#include "Engine3d.hpp"
#include "ModelStarField.hpp"
#include "ModelTriangle.hpp"
#include "Result.hpp"
#include "Text2d.hpp"
#include "TextManager2d.hpp"
#include "Vertex.hpp"

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
    ModelStarField starField_;
    bool showFps_ = true;
    TextManager2d textManager2d_;
    AppTimer timer_;
    int64_t totalAppFrames_;
    Window* mainWindow_;
};
