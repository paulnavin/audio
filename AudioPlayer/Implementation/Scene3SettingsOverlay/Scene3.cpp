#include "Scene3.hpp"

#include <Platform/Logging.hpp>

#include "Model2dSettingsOverlay.hpp"
#include "Scene3UserInput.hpp"

Result Scene3::Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    model2d_ = new Model2dSettingsOverlay();
    userInputHandler_ = new Scene3UserInput();

    Scene::Init(portal, config, inputManager);

    LOG(INFO) << "Scene3::Init() : Successful!";

    return Result{};
}
