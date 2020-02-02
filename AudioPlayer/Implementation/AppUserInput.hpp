#pragma once

#include <UserInput/InputManager.hpp>
#include <Utility/Result.hpp>

class App;

class AppUserInput {
public:
    AppUserInput() = default;
    ~AppUserInput() = default;

public:
    Result Init(App* newApp);
    void Update(const Window& targetWindow);

private:
    App* app_;
    InputManager inputManager_;
    Window* window_;
};

