#pragma once

#include <App/App.hpp>

#include "AudioPlayerUserInput.hpp"
#include "Scene1Dj/Scene1Dj.hpp"
#include "Scene2Simple/Scene2Basic.hpp"
#include "Scene3SettingsOverlay/Scene3.hpp"

class AudioPlayerApp final : public App {
public:
    AudioPlayerApp() = default;
    virtual ~AudioPlayerApp() = default;

public:
    Result Init(const HINSTANCE& appInstance, const ResourceLocator& resourceManager) override;

public:
    Result SelectNextScene();
    void ShowSettings();
    void HideSettings();

private:
    AudioPlayerUserInput userInputHandler_;

    Scene1Dj scene1_;
    Scene2Basic scene2_;
    Scene3 scene3_;

    Scene* currentScene_;
};
