#include "Scene1UserInput.hpp"

#include <UserInput/InputManager.hpp>
#include <Platform/WindowsInterface.hpp>

#include "Scene1Dj.hpp"
#include <App/AppUserInputCommands.hpp>

Result Scene1UserInput::Init(Scene* newScene, InputManager* inputManager) {
    SceneUserInput::Init(newScene, inputManager);

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

void Scene1UserInput::Update() {
    SceneUserInput::Update();

    const InputManager::CommandMap* activeCommands = inputManager_->GetActiveKeyMap();
    for (auto command : *activeCommands) {
        switch (command.first) {
            case ToggleFps: { dynamic_cast<Scene1Dj*>(scene_)->OnCommandShowFps(); return; }
            case ToggleMousePosition: { dynamic_cast<Scene1Dj*>(scene_)->OnCommandShowMousePosition(); return; }
        }
    }
}
