#pragma once

#include <UserInput/InputManager.hpp>
#include <ErrorHandling/Result.hpp>

class Scene1Dj;

class Scene1UserInput {
public:
    Scene1UserInput() = default;
    ~Scene1UserInput() = default;

public:
    Result Init(Scene1Dj* newApp, InputManager* inputManager);
    void Update();

private:
    Scene1Dj* app_;
    InputManager* inputManager_;
};

