#include "Scene2Basic.hpp"

#include <Logging/EasyLogging++.hpp>

#include "ModelBasic2d.hpp"
#include "Scene2UserInput.hpp"

Result Scene2Basic::Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    model2d_ = new ModelBasic2d();
    userInputHandler_ = new Scene2UserInput();

    Scene::Init(portal, config, inputManager);

    LOG(INFO) << "Scene2Basic::Init() : Successful!";

    return Result{};
}
