#pragma once

#include "Scene.hpp"

class Scene1Dj : public Scene {
public:
    Scene1Dj() = default;
    virtual ~Scene1Dj() = default;

public:
    virtual Result Init(GraphicsEngine* gfx, ::uc::ConfigStore* config, InputManager* inputManager) override;
};
