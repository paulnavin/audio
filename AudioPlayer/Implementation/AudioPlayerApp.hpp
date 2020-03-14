#pragma once

#include <App/App.hpp>

#include "AudioPlayerUserInput.hpp"

class AudioPlayerApp final : public App {
public:
    AudioPlayerApp() = default;
    virtual ~AudioPlayerApp() = default;

public:
    virtual Result Init(const HINSTANCE& appInstance, const ResourceManager& resourceManager) override;

    AudioPlayerUserInput userInputHandler_;
};
