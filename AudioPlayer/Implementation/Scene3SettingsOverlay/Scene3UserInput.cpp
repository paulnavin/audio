#include "Scene3UserInput.hpp"

Result Scene3UserInput::Init(Scene* newScene, InputManager* inputManager) {
    return SceneUserInput::Init(newScene, inputManager);

    // No extra commands for now.
};

void Scene3UserInput::Update() {
    SceneUserInput::Update();

    // No extra commands for now.
}
