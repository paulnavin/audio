#pragma once

#include <ErrorHandling/Result.hpp>
#include <UserConfiguration/Config.hpp>

class GraphicsEngine;
class InputManager;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual Result Init(GraphicsEngine* gfx, ::uc::ConfigStore* config, InputManager* inputManager) = 0;
    virtual void ShutDown() = 0;
    virtual void UpdateMousePosition(const float& x, const float& y) = 0;
    virtual void Update(const double& dt) = 0;
    virtual Result UpdateFps(const int64_t& newFps) = 0;

    virtual void OnCommandMouseClicked(const float& x, const float& y) = 0;
};
