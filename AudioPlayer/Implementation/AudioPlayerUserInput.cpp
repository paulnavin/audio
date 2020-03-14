#include "AudioPlayerUserInput.hpp"

#include <UserInput/InputManager.hpp>

#include "AudioPlayerApp.hpp"
#include "AudioPlayerUserInputCommands.hpp"

Result AudioPlayerUserInput::Init(App* newApp, InputManager* inputManager) {
    app_ = dynamic_cast<AudioPlayerApp*>(newApp);
    inputManager_ = inputManager;

    // No extra commands for now.

    return AppUserInput::Init(newApp, inputManager);
};

void AudioPlayerUserInput::Update() {
    AppUserInput::Update();

    // No extra commands for now.
}
