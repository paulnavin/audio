#include <App/SceneUserInput.hpp>

#include <App/AppUserInputCommands.hpp>
#include <App/Scene.hpp>
#include <Platform/WindowsInterface.hpp>
#include <UserInput/InputManager.hpp>

Result SceneUserInput::Init(Scene* newScene, InputManager* inputManager) {
    scene_ = newScene;
    inputManager_ = inputManager;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding('F', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(ToggleFps, "Toggle FPS", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_RBUTTON, KeyState::JustReleased));
    inputManager_->AddCommand(new Command(ToggleMousePosition, "Toggle Mouse Position", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_->AddCommand(new Command(MouseClicked, "Left Click", bindings));
    bindings.clear();

    return Result{};
};

void SceneUserInput::Update() {
    float mouseXPosition = static_cast<float>(inputManager_->GetMouseXPos());
    float mouseYPosition = static_cast<float>(inputManager_->GetMouseYPos());
    scene_->UpdateMousePosition(mouseXPosition, mouseYPosition);

    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
        case MouseClicked: { scene_->OnCommandMouseClicked(mouseXPosition, mouseYPosition); return; }
        case ToggleFps: { scene_->OnCommandShowFps(); return; }
        case ToggleMousePosition: { scene_->OnCommandShowMousePosition(); return; }
        }
    }
}