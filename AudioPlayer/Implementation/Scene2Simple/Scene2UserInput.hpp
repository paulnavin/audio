#pragma once

#include <Platform/ErrorHandling.hpp>

#include <App/SceneUserInput.hpp>

class Scene2UserInput : public SceneUserInput {
public:
    Scene2UserInput() = default;
    virtual ~Scene2UserInput() = default;

public:
    Result Init(Scene* newScene, InputManager* inputManager) override;
    void Update() override;
};

