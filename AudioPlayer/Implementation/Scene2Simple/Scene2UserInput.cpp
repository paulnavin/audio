#include "Scene2UserInput.hpp"

Result Scene2UserInput::Init(Scene* newScene, InputManager* inputManager) {
    return SceneUserInput::Init(newScene, inputManager);

    // No extra commands for now.
};

void Scene2UserInput::Update() {
    SceneUserInput::Update();

    // No extra commands for now.
}
