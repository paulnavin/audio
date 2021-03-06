#include <App/AppUserInput.hpp>

#include <App/App.hpp>
#include <App/AppUserInputCommands.hpp>
#include <UserInput/InputManager.hpp>

Result AppUserInput::Init(App* newApp, InputManager* inputManager) {
    app_ = newApp;
    inputManager_ = inputManager;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding('T', KeyState::JustReleased));
    inputManager_->AddCoreCommand(new Command(ToggleFullScreen, "Toggle Full Screen", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(Quit, "Quit", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('P', KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(NextDisplayConfig, "Next Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('I', KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(PreviousDisplayConfig, "Previous Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('O', KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(ResetDisplayConfig, "Reset Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustPressed));
    inputManager_->AddCoreCommand(new Command(LeftButtonDown, "Left Button Down", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_->AddCoreCommand(new Command(LeftButtonUp, "Left Button Up", bindings));
    bindings.clear();


    return Result{};
};

void AppUserInput::Update() {
    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
        case Quit: {app_->OnCommandQuit(); return; }
        case ToggleFullScreen: { app_->OnCommandToggleFullScreen(); return; }
        case NextDisplayConfig: { app_->OnCommandNextDisplayConfig(); return; }
        case PreviousDisplayConfig: { app_->OnCommandPreviousDisplayConfig(); return; }
        case ResetDisplayConfig: { app_->OnCommandResetDisplayConfig(); return; }
        }
    }
}
