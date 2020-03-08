#pragma once

#include <ErrorHandling/Result.hpp>

namespace uc {
class ConfigStore;
}

class GraphicsEngine;
class InputManager;
class Model2d;
class Model3d;
class SceneUserInput;
class Window;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual Result Init(GraphicsEngine* gfx, ::uc::ConfigStore* config, InputManager* inputManager);
    void ShutDown();
    void UpdateMousePosition(const float& x, const float& y);
    void Update(const double& dt);
    Result UpdateFps(const int64_t& newFps);

    void OnCommandMouseClicked(const float& x, const float& y);
    void OnCommandShowFps();
    void OnCommandShowMousePosition();

protected:
    GraphicsEngine* graphicsEngine_;
    Model3d* model3d_;
    Model2d* model2d_;
    bool showFps_ = true;
    bool showMousePosition_ = true;
    Window* mainWindow_;
    SceneUserInput* userInputHandler_;
};
