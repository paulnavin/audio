#pragma once

#include <App/Scene.hpp>

class Scene2Basic : public Scene {
public:
    Scene2Basic() = default;
    virtual ~Scene2Basic() = default;

public:
    virtual Result Init(GraphicsEngine* gfx, ConfigStore* config, InputManager* inputManager) override;
};
