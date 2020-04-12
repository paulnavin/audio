#pragma once

#include <App/Scene.hpp>

class Scene3 : public Scene {
public:
    Scene3() = default;
    virtual ~Scene3() = default;

public:
    virtual Result Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) override;
};
