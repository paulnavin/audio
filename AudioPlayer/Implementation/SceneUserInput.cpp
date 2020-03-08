#include "SceneUserInput.hpp"

#include <UserInput/InputManager.hpp>

#include "Scene.hpp"
#include "UserInputCommands.hpp"

Result SceneUserInput::Init(Scene* newScene, InputManager* inputManager) {
    scene_ = newScene;
    inputManager_ = inputManager;

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
        }
    }
}