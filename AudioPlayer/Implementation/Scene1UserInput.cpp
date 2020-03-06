#include "Scene1UserInput.hpp"

#include "Scene1Dj.hpp"
#include "UserInputCommands.hpp"

Result Scene1UserInput::Init(Scene1Dj* newApp, InputManager* inputManager) {
    app_ = newApp;
    inputManager_ = inputManager;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding('F', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(ToggleFps, "Toggle FPS", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    bindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    bindings.push_back(KeyBinding('R', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(RecreateModels, "Recreate Models", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_RBUTTON, KeyState::JustReleased));
    inputManager_->AddCommand(new Command(ToggleMousePosition, "Toggle Mouse Position", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_->AddCommand(new Command(MouseClicked, "Left Click", bindings));
    bindings.clear();

    return Result{};
};

void Scene1UserInput::Update() {
    float mouseXPosition = static_cast<float>(inputManager_->GetMouseXPos());
    float mouseYPosition = static_cast<float>(inputManager_->GetMouseYPos());
    app_->UpdateMousePosition(mouseXPosition, mouseYPosition);

    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
            //case RecreateModels: { app_->OnCommandRecreateModels(); return; } // TODO: Fix this, needs to pause scene first.
            case ToggleFps: { app_->OnCommandShowFps(); return; }
            case ToggleMousePosition: { app_->OnCommandShowMousePosition(); return; }
            case MouseClicked: { app_->OnCommandMouseClicked(mouseXPosition, mouseYPosition); return; }
        }
    }
}
