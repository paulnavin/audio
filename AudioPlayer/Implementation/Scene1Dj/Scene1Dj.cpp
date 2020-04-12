#include "Scene1Dj.hpp"

#include <Logging/EasyLogging++.hpp>

#include "ModelDj.hpp"
#include "ModelStarField.hpp"
#include "Scene1UserInput.hpp"

Result Scene1Dj::Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    model3d_ = new ModelStarField();
    model2d_ = new ModelDj();
    userInputHandler_ = new Scene1UserInput();

    LOG(INFO) << "Scene1Dj::Init() : Created successfully!";

    return Scene::Init(portal, config, inputManager);
}
