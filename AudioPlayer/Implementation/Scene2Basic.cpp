#include "Scene2Basic.hpp"

#include <Logging/EasyLogging++.hpp>

#include "ModelBasic2d.hpp"
#include "ModelTriangle.hpp"
#include "Scene2UserInput.hpp"

Result Scene2Basic::Init(GraphicsEngine* gfx, ::uc::ConfigStore* config, InputManager* inputManager) {
    Result initResult{};

    graphicsEngine_ = gfx;

    model3d_ = new ModelTriangle();
    model2d_ = new ModelBasic2d();
    userInputHandler_ = new Scene2UserInput();

    Scene::Init(gfx, config, inputManager);

    LOG(INFO) << "Scene2Basic::Init() : Successful!";

    return Result{};
}
