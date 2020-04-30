#pragma once

#include <Platform/ErrorHandling.hpp>

class InputManager;
class App;

class AppUserInput {
public:
    AppUserInput() = default;
    virtual ~AppUserInput() = default;

public:
    virtual Result Init(App* newScene, InputManager* inputManager);
    virtual void Update();

protected:
    App* app_;
    InputManager* inputManager_;
};

