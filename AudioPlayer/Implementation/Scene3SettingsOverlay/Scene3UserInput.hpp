#pragma once

#include <Platform/ErrorHandling.hpp>

#include <App/SceneUserInput.hpp>

class Scene3UserInput : public SceneUserInput {
public:
    Scene3UserInput() = default;
    virtual ~Scene3UserInput() = default;

public:
    Result Init(Scene* newScene, InputManager* inputManager) override;
    void Update() override;
};

