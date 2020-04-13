#include "Scene1Dj.hpp"

#include <Logging/EasyLogging++.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/ModelPortal.hpp>

#include "ModelDj.hpp"
#include "Scene1UserInput.hpp"

Result Scene1Dj::Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    model2d_ = new ModelDj();
    userInputHandler_ = new Scene1UserInput();

    ResourceManager* resources = portal->resourceManager;
    resources->RegisterBitmapToLoad("BlueArrow");
    resources->RegisterBitmapToLoad("SettingsButton");

    LOG(INFO) << "Scene1Dj::Init() : Created successfully!";

    return Scene::Init(portal, config, inputManager);
}
