#include "Scene1UserInput.hpp"

Result Scene1UserInput::Init(Scene* newScene, InputManager* inputManager) {
    return SceneUserInput::Init(newScene, inputManager);

    // No extra commands for now.
};

void Scene1UserInput::Update(const double& dt) {
    SceneUserInput::Update(dt);

    // No extra commands for now.
}
