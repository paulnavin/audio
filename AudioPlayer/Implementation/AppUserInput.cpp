#pragma once

#include "AppUserInput.hpp"
#include "App.hpp"
#include "UserInputCommands.hpp"

Result AppUserInput::Init(App* newApp) {
    app_ = newApp;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding('F', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(ToggleFps, "Toggle FPS", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    bindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    bindings.push_back(KeyBinding('2', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(Toggle2dModel, "Toggle 2D Model", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    bindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    bindings.push_back(KeyBinding('R', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(RecreateModels, "Recreate Models", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_RBUTTON, KeyState::JustReleased));
    inputManager_.AddCommand(new Command(ToggleMousePosition, "Toggle Mouse Position", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_.AddCommand(new Command(MouseClicked, "Left Click", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('T', KeyState::JustReleased));
    inputManager_.AddCommand(new Command(ToggleFullScreen, "Toggle Full Screen", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    inputManager_.AddCommand(new Command(Quit, "Quit", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('P', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(NextDisplayConfig, "Next Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('I', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(PreviousDisplayConfig, "Previous Display Config", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding('O', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(ResetDisplayConfig, "Reset Display Config", bindings));
    bindings.clear();

    return Result{};
};

void AppUserInput::Update(const Window& targetWindow) {
    inputManager_.Update(targetWindow);

    float mouseXPosition = static_cast<float>(inputManager_.GetMouseXPos());
    float mouseYPosition = static_cast<float>(inputManager_.GetMouseYPos());
    app_->UpdateMousePosition(mouseXPosition, mouseYPosition);

    const InputManager::CommandMap* activeCommands = inputManager_.GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
        case Quit: {app_->OnCommandQuit(); return; }
        case RecreateModels: { app_->OnCommandRecreateModels(); return; }
        case Toggle2dModel: { app_->OnCommandToggle2dModel(); return; }
        case ToggleFps: { app_->OnCommandShowFps(); return; }
        case ToggleFullScreen: { app_->OnCommandToggleFullScreen(); return; }
        case ToggleMousePosition: { app_->OnCommandShowMousePosition(); return; }
        case MouseClicked: { app_->OnCommandMouseClicked(mouseXPosition, mouseYPosition); return; }
        case NextDisplayConfig: { app_->OnCommandNextDisplayConfig(); return; }
        case PreviousDisplayConfig: { app_->OnCommandPreviousDisplayConfig(); return; }
        case ResetDisplayConfig: { app_->OnCommandResetDisplayConfig(); return; }
        }
    }
}
