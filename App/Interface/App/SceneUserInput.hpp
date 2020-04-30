#pragma once

#include <Platform/ErrorHandling.hpp>

class InputManager;
class Scene;

class SceneUserInput {
public:
    SceneUserInput() = default;
    virtual ~SceneUserInput() = default;

public:
    virtual Result Init(Scene* newScene, InputManager* inputManager);
    virtual void Update();

protected:
    Scene* scene_;
    InputManager* inputManager_;
};

