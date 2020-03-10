#include <App/Scene.hpp>

#include <App/SceneUserInput.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Model3d.hpp>
#include <Logging/EasyLogging++.hpp>
#include <UserConfiguration/Config.hpp>

Result Scene::Init(GraphicsEngine* gfx, ::uc::ConfigStore* /*config*/, InputManager* inputManager) {
    Result initResult{};

    graphicsEngine_ = gfx;

    initResult = userInputHandler_->Init(this, inputManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Init() : Error initialising user input handler.");
        return initResult;
    }

    initResult = model3d_->Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create3dModel() : Error initialising 3D model.");
        return initResult;
    }

    initResult = graphicsEngine_->Set3dModel(*model3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create3dModel() : Error setting 3D model.");
        return initResult;
    }

    initResult = graphicsEngine_->Init2dModel(model2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create2dModel : Error initialising DJ 2D model.");
        return initResult;
    }
    model2d_->SetShowFps(showFps_);

    graphicsEngine_->Set2dModel(model2d_);
    graphicsEngine_->Set3dModel(*model3d_);

    LOG(INFO) << "Scene::Init() : Successful!";

    return Result{};
}

void Scene::ShutDown() {
    if (model3d_ != nullptr) {
        delete model3d_;
    }
    model3d_ = nullptr;
    if (model2d_ != nullptr) {
        delete model2d_;
    }
    model2d_ = nullptr;
    if (userInputHandler_ != nullptr) {
        delete userInputHandler_;
    }
    userInputHandler_ = nullptr;
}

void Scene::OnCommandMouseClicked(const float& x, const float& y) {
    model2d_->OnMouseClicked(x, y);
}

void Scene::OnCommandShowFps() {
    showFps_ = !showFps_;
    model2d_->SetShowFps(showFps_);
}

void Scene::OnCommandShowMousePosition() {
    showMousePosition_ = !showMousePosition_;
    model2d_->SetShowMousePosition(showMousePosition_);
}

void Scene::UpdateMousePosition(const float& x, const float& y) {
    model2d_->SetMousePosition(x, y);
}

void Scene::Update(const double& dt) {
    userInputHandler_->Update();
    model2d_->Update(dt);
}

Result Scene::UpdateFps(const int64_t& newFps) {
    model2d_->SetFps(newFps);

    return Result{};
}
