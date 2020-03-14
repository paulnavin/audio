#pragma once

#include <App/AppUserInput.hpp>
#include <ErrorHandling/Result.hpp>

class AudioPlayerApp;
class InputManager;

class AudioPlayerUserInput : public AppUserInput {
public:
    AudioPlayerUserInput() = default;
    ~AudioPlayerUserInput() = default;

public:
    Result Init(App* newApp, InputManager* inputManager);
    virtual void Update();

private:
    AudioPlayerApp* app_;
    InputManager* inputManager_;
};

