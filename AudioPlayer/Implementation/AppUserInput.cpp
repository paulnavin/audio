#pragma once

#include "AppUserInput.hpp"
#include "App.hpp"
#include "UserInputCommands.hpp"

Result AppUserInput::Init(App* newApp) {
    app_ = newApp;

    std::vector<KeyBinding> toggleFpsBindings;
    toggleFpsBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding('F', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(ToggleFps, "Toggle FPS", toggleFpsBindings));

    std::vector<KeyBinding> toggleModelBindings;
    toggleModelBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    toggleModelBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    toggleModelBindings.push_back(KeyBinding('2', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(Toggle2dModel, "Toggle 2D Model", toggleModelBindings));

    std::vector<KeyBinding> recreateModelBindings;
    recreateModelBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    recreateModelBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    recreateModelBindings.push_back(KeyBinding('R', KeyState::JustPressed));
    inputManager_.AddCommand(new Command(RecreateModels, "Recreate Models", recreateModelBindings));

    std::vector<KeyBinding> toggleMousePositionBindings;
    toggleMousePositionBindings.push_back(KeyBinding(VK_RBUTTON, KeyState::JustReleased));
    inputManager_.AddCommand(new Command(ToggleMousePosition, "Toggle Mouse Position", toggleMousePositionBindings));

    std::vector<KeyBinding> mouseClickedBindings;
    mouseClickedBindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_.AddCommand(new Command(MouseClicked, "Left Click", mouseClickedBindings));

    std::vector<KeyBinding> toggleFullScreenBindings;
    toggleFullScreenBindings.push_back(KeyBinding('T', KeyState::JustReleased));
    inputManager_.AddCommand(new Command(ToggleFullScreen, "Toggle Full Screen", toggleFullScreenBindings));

    std::vector<KeyBinding> quitBindings;
    quitBindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    inputManager_.AddCommand(new Command(Quit, "Quit", quitBindings));

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
        case RecreateModels: { app_->OnCommandRecreateModels(); return; }
        case Toggle2dModel: { app_->OnCommandToggle2dModel(); return; }
        case ToggleFps: { app_->OnCommandShowFps(); return; }
        case ToggleFullScreen: { app_->OnCommandToggleFullScreen(); return; }
        case ToggleMousePosition: { app_->OnCommandShowMousePosition(); return; }
        case MouseClicked: { app_->OnCommandMouseClicked(mouseXPosition, mouseYPosition); return; }
        }
    }
}
