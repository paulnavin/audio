#pragma once

#include <ErrorHandling/Result.hpp>

#include <App/SceneUserInput.hpp>

class Scene1UserInput : public SceneUserInput {
public:
    Scene1UserInput() = default;
    virtual ~Scene1UserInput() = default;

public:
    virtual Result Init(Scene* newScene, InputManager* inputManager) override;
    void Update(const double& dt) override;
};

