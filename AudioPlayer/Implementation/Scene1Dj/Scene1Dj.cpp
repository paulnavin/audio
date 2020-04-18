#include "Scene1Dj.hpp"

#include <Logging/EasyLogging++.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/ModelPortal.hpp>

#include "ModelDj.hpp"
#include "Scene1TextStyles.hpp"
#include "Scene1UserInput.hpp"

Result Scene1Dj::Init(ModelPortal* portal, ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    model2d_ = new ModelDj();
    userInputHandler_ = new Scene1UserInput();

    ResourceManager* resources = portal->resourceManager;
    resources->RegisterBitmapToLoad("BlueArrow");
    resources->RegisterBitmapToLoad("SettingsButton");

    TextStyle defaultStyle = { DefaultText, Colour{1.0f, 1.0f, 1.0f, 1.0f}, "Times New Roman", 12.0f };
    resources->RegisterTextStyle(defaultStyle);
    TextStyle standardStyle = { StandardText, Colour{1.0f, 0.0f, 0.0f, 1.0f}, "Lucida Console", 12.0f };
    resources->RegisterTextStyle(standardStyle);
    TextStyle bigStyle = { BigText, Colour{0.0f, 0.0f, 1.0f, 1.0f}, "Lucida Console", 36.0f };
    resources->RegisterTextStyle(bigStyle);

    LOG(INFO) << "Scene1Dj::Init() : Created successfully!";

    return Scene::Init(portal, config, inputManager);
}
