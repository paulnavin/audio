#include <App/AppUserInput.hpp>

#include <App/App.hpp>
#include <App/AppUserInputCommands.hpp>
#include <UserInput/InputManager.hpp>

Result AppUserInput::Init(App* newApp, InputManager* inputManager) {
    app_ = newApp;
    inputManager_ = inputManager;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    bindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    bindings.push_back(KeyBinding('2', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(ToggleScene, "Toggle 2D Model", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('T', KeyState::JustReleased));
    inputManager_->AddCommand(new Command(ToggleFullScreen, "Toggle Full Screen", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    inputManager_->AddCommand(new Command(Quit, "Quit", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('P', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(NextDisplayConfig, "Next Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('I', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(PreviousDisplayConfig, "Previous Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('O', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(ResetDisplayConfig, "Reset Display Config", bindings));
    bindings.clear();

    return Result{};
};

void AppUserInput::Update() {
    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
        case Quit: {app_->OnCommandQuit(); return; }
        case ToggleScene: { app_->OnCommandToggleScene(); return; }
        case ToggleFullScreen: { app_->OnCommandToggleFullScreen(); return; }
        case NextDisplayConfig: { app_->OnCommandNextDisplayConfig(); return; }
        case PreviousDisplayConfig: { app_->OnCommandPreviousDisplayConfig(); return; }
        case ResetDisplayConfig: { app_->OnCommandResetDisplayConfig(); return; }
        }
    }
}
