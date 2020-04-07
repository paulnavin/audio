#include <App/SceneUserInput.hpp>

#include <App/AppUserInputCommands.hpp>
#include <App/Scene.hpp>
#include <Platform/WindowsInterface.hpp>
#include <UserInput/InputManager.hpp>

Result SceneUserInput::Init(Scene* newScene, InputManager* inputManager) {
    scene_ = newScene;
    inputManager_ = inputManager;

    std::vector<KeyBinding> bindings;

    bindings.push_back(KeyBinding('D', KeyState::JustPressed));
    inputManager_->AddCommand(new Command(ToggleDebugInfo, "Toggle Debug Info", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustPressed));
    inputManager_->AddCommand(new Command(LeftButtonDown, "Left Button Down", bindings));
    bindings.clear();

    bindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    inputManager_->AddCommand(new Command(LeftButtonUp, "Left Button Up", bindings));
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
            case ToggleDebugInfo: { 
                scene_->OnCommandToggleDebugInfo();
                return; 
            }
            default: {
                scene_->OnCommand(command.first);
            }
        }
    }
}
