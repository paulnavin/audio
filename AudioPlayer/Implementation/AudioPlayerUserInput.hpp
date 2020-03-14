#pragma once

#include <ErrorHandling/Result.hpp>

class AudioPlayerApp;
class InputManager;
class Window;

class AudioPlayerUserInput {
public:
    AudioPlayerUserInput() = default;
    ~AudioPlayerUserInput() = default;

public:
    Result Init(AudioPlayerApp* newApp, InputManager* inputManager);
    void Update();

private:
    AudioPlayerApp* app_;
    InputManager* inputManager_;
};

