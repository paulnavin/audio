#include <App/Scene.hpp>

#include <App/SceneUserInput.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Platform/Logging.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/Commander.hpp>
#include <UserInterface/Model2d.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Scene::Init(ModelPortal* portal, ConfigStore* /*config*/, InputManager* inputManager) {
    Result initResult{};

    keen_ = portal->commander;
    ResourceManager* resources = portal->resourceManager;

    initResult = userInputHandler_->Init(this, inputManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Init() : Error initialising user input handler.");
        return initResult;
    }

    initResult = resources->LoadBitmaps();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Init() : Error loading bitmaps.");
        return initResult;
    }

    initResult = resources->LoadAllText();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Init() : Error loading text.");
        return initResult;
    }

    initResult = model2d_->Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Init() : Error initialising 2D model.");
        return initResult;
    }

    LOG(INFO) << "Scene::Init() : Successful!";

    return Result{};
}

void Scene::ShutDown() {
    if (model2d_ != nullptr) {
        delete model2d_;
    }
    model2d_ = nullptr;
    if (userInputHandler_ != nullptr) {
        delete userInputHandler_;
    }
    userInputHandler_ = nullptr;
}

void Scene::OnCommand(const Command::Id& command) {
    keen_->Distribute(command);
}

void Scene::OnCommandToggleDebugInfo() {
    model2d_->ToggleDebugInfo();
}

void Scene::SetTopScene(bool isTopScene) {
    model2d_->SetActive(isTopScene);
}

void Scene::UpdateMousePosition(const float& x, const float& y) {
    keen_->DistributeMousePosition(x, y);
    model2d_->SetMousePosition(x, y);
}

void Scene::Update(const double& dt) {
    userInputHandler_->Update();
    model2d_->Update(dt);
}

void Scene::Render(const double& dt) {
    // (2) Draw 3D stuff - removed!  See here for interoperability if 3D drawing
    //     is needed again:
    //       - https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-and-direct3d-interoperation-overview

    // (3) Draw any 2D stuff on top of the 3D stuff.
    model2d_->Render(dt);
}

Result Scene::UpdateFps(const int64_t& newFps) {
    model2d_->SetFps(newFps);

    return Result{};
}
