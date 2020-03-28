#pragma once

#include <ErrorHandling/Result.hpp>

class ConfigStore;
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
    virtual Result Init(GraphicsEngine* gfx, ConfigStore* config, InputManager* inputManager);
    void ShutDown();
    void UpdateMousePosition(const float& x, const float& y);
    void Update(const double& dt);
    Result UpdateFps(const int64_t& newFps);

    void OnCommandMouseDown(const float& x, const float& y);
    void OnCommandMouseUp(const float& x, const float& y);
    void OnCommandMouseClicked(const float& x, const float& y);
    void OnCommandToggleDebugInfo();

protected:
    GraphicsEngine* graphicsEngine_;
    Window* mainWindow_;
    Model3d* model3d_;
    Model2d* model2d_;
    SceneUserInput* userInputHandler_;
};
