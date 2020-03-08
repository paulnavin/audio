#pragma once

#include <ErrorHandling/Result.hpp>

#include "SceneUserInput.hpp"

class Scene2UserInput : public SceneUserInput {
public:
    Scene2UserInput() = default;
    virtual ~Scene2UserInput() = default;

public:
    virtual Result Init(Scene* newScene, InputManager* inputManager) override;
    virtual void Update() override;
};

