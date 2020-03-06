#include "Scene1Dj.hpp"

#include <UserInterface/ErrorDisplay.hpp>
#include <UserInterface/Window.hpp>
#include <UserInterface/WindowConfig.hpp>
#include <UserInterface/WindowManager.hpp>
#include <Logging/EasyLogging++.hpp>
#include <FileSystem/ResourceManager.hpp>
#include <ErrorHandling/Result.hpp>

#include "ModelDj.hpp"
#include "ModelStarField.hpp"
#include "Resource.h"

Result Scene1Dj::Init(GraphicsEngine* gfx, ::uc::ConfigStore* /*config*/, InputManager* inputManager) {
    Result initResult{};

    graphicsEngine_ = gfx;

    initResult = userInputHandler_.Init(this, inputManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene1Dj::Init() : Error initialising user input handler.");
        return initResult;
    }

    initResult = Create3dModel();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene1Dj::Init() : Error creating 3D model.");
        return initResult;
    }

    initResult = Create2dModel();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene1Dj::Init() : Error creating 2D model.");
        return initResult;
    }

    graphicsEngine_->Set2dModel(djModel2d_);
    graphicsEngine_->Set3dModel(*model3d_);

    LOG(INFO) << "Scene1Dj::Init() : Successful!";

    return Result{};
}

void Scene1Dj::ShutDown() {
    Destroy3dModel();
    Destroy2dModel();
}

void Scene1Dj::OnCommandMouseClicked(const float& x, const float& y) {
    djModel2d_->OnMouseClicked(x, y);
}

void Scene1Dj::OnCommandShowFps() {
    showFps_ = !showFps_;
    djModel2d_->SetShowFps(showFps_);
}

void Scene1Dj::OnCommandShowMousePosition() {
    showMousePosition_ = !showMousePosition_;
    djModel2d_->SetShowMousePosition(showMousePosition_);
}

void Scene1Dj::OnCommandRecreateModels() {
    // TODO: Fix this, needs to pause scene first.
    Destroy3dModel();
    Destroy2dModel();

    Result initResult = Create3dModel();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene1Dj::OnCommandRecreateModels() : Error creating 3D model.");
        ErrorDisplay::ShowErrors(initResult);
        return;
    }

    initResult = Create2dModel();
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene1Dj::OnCommandRecreateModels() : Error creating 2D model.");
        ErrorDisplay::ShowErrors(initResult);
        return;
    }
}

void Scene1Dj::UpdateMousePosition(const float& x, const float& y) {
    djModel2d_->SetMousePosition(x, y);
}

void Scene1Dj::Update(const double& dt) {
    userInputHandler_.Update();
    djModel2d_->Update(dt);
}

Result Scene1Dj::UpdateFps(const int64_t& newFps) {
    djModel2d_->SetFps(newFps);

    return Result{};
}

void Scene1Dj::Destroy3dModel() {
    if (model3d_ != nullptr) {
        delete model3d_;
    }
    model3d_ = nullptr;
}

void Scene1Dj::Destroy2dModel() {
    if (djModel2d_ != nullptr) {
        delete djModel2d_;
    }
    djModel2d_ = nullptr;
}

Result Scene1Dj::Create3dModel() {
    model3d_ = new ModelStarField();

    Result initResult = model3d_->Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Create3dModel() : Error initialising 3D model.");
        return initResult;
    }

    initResult = graphicsEngine_->Set3dModel(*model3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Create3dModel() : Error setting 3D model.");
        return initResult;
    }

    return initResult;
}

Result Scene1Dj::Create2dModel() {
    djModel2d_ = new ModelDj();
    Result initResult = graphicsEngine_->Init2dModel(djModel2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Create2dModel : Error initialising DJ 2D model.");
        return initResult;
    }
    djModel2d_->SetShowFps(showFps_);

    return initResult;
}
