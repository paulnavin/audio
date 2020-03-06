#pragma once

#include <ErrorHandling/Result.hpp>

class App;
class InputManager;
class Window;

class AppUserInput {
public:
    AppUserInput() = default;
    ~AppUserInput() = default;

public:
    Result Init(App* newApp, InputManager* inputManager);
    void Update();

private:
    App* app_;
    InputManager* inputManager_;
};

