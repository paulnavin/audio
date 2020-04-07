#include <App/Scene.hpp>

#include <App/SceneUserInput.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Logging/EasyLogging++.hpp>
#include <UserInterface/Model2d.hpp>
#include <UserInterface/Model3d.hpp>
#include <UserConfiguration/Config.hpp>

Result Scene::Init(GraphicsEngine* gfx, ConfigStore* /*config*/, InputManager* inputManager) {
    Result initResult{};

    portal_.gfx = gfx;
    portal_.commander = &keen_;

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

    VertexBuffer vertexBuffer;
    vertexBuffer.data = model3d_->GetVertexData();
    vertexBuffer.size = model3d_->GetVertexCount();
    vertexBuffer.type = model3d_->GetVertexType();
    initResult = gfx->Init3dVertices(vertexBuffer);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create3dModel() : Error setting 3D vertex buffer.");
        return initResult;
    }

    initResult = model2d_->Init(&portal_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create2dModel : Error initialising 2D model.");
        return initResult;
    }

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

void Scene::OnCommand(const Command::Id& command) {
    keen_.Distribute(command);
}

void Scene::OnCommandToggleDebugInfo() {
    model2d_->ToggleDebugInfo();
}

void Scene::UpdateMousePosition(const float& x, const float& y) {
    keen_.DistributeMousePosition(x, y);
    model2d_->SetMousePosition(x, y);
}

void Scene::Update(const double& dt) {
    userInputHandler_->Update();
    model2d_->Update(dt);
}

void Scene::Render(const double& dt) {
    portal_.gfx->StartRender();

    // (3) Draw any 2D stuff on top of the 3D stuff.
    model2d_->Render(dt);

    portal_.gfx->EndRender();
}

Result Scene::UpdateFps(const int64_t& newFps) {
    model2d_->SetFps(newFps);

    return Result{};
}
