#include "AudioPlayerUserInput.hpp"

#include <UserInput/InputManager.hpp>

#include "AudioPlayerApp.hpp"
#include "AudioPlayerUserInputCommands.hpp"

Result AudioPlayerUserInput::Init(App* newApp, InputManager* inputManager) {
    app_ = dynamic_cast<AudioPlayerApp*>(newApp);
    inputManager_ = inputManager;

    Result initResult = AppUserInput::Init(newApp, inputManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("AudioPlayerUserInput::Init() : Error initialising base app user input handler.");
        return initResult;
    }

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    bindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    bindings.push_back(KeyBinding('2', KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(ToggleScene, "Toggle 2D Model", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_EXECUTE, KeyState::StillPressed));
    inputManager_->AddCoreCommand(new Command(ShowSettings, "Show Settings", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_NAVIGATION_CANCEL, KeyState::StillPressed));
    inputManager_->AddCoreCommand(new Command(HideSettings, "Hide Settings", bindings));
    bindings.clear();

    return initResult;
};

void AudioPlayerUserInput::Update() {
    AppUserInput::Update();

    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
            case ToggleScene: { app_->SelectNextScene(); return; }
            case ShowSettings: { app_->ShowSettings(); return; }
            case HideSettings: { app_->HideSettings(); return; }
        }
    }
}
