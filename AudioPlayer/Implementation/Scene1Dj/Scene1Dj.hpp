#pragma once

#include <App/Scene.hpp>

class Scene1Dj : public Scene {
public:
    Scene1Dj() = default;
    virtual ~Scene1Dj() = default;

public:
    virtual Result Init(GraphicsEngine* gfx, ConfigStore* config, InputManager* inputManager) override;
};
