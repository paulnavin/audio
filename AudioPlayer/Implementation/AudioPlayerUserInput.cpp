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
    inputManager_->AddCommand(new Command(ToggleScene, "Toggle 2D Model", bindings));
    bindings.clear();

    return initResult;
};

void AudioPlayerUserInput::Update() {
    AppUserInput::Update();

    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
        case ToggleScene: { app_->SelectNextScene(); return; }
        }
    }
}
