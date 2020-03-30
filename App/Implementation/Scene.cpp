#include <App/Scene.hpp>

#include <App/SceneUserInput.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Logging/EasyLogging++.hpp>
#include <UserInterface/Model2d.hpp>
#include <UserInterface/Model3d.hpp>
#include <UserConfiguration/Config.hpp>

Result Scene::Init(GraphicsEngine* gfx, ConfigStore* /*config*/, InputManager* inputManager) {
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

    VertexBuffer vertexBuffer;
    vertexBuffer.data = model3d_->GetVertexData();
    vertexBuffer.size = model3d_->GetVertexCount();
    vertexBuffer.type = model3d_->GetVertexType();
    initResult = graphicsEngine_->Init3dVertices(vertexBuffer);
    if (initResult.HasErrors()) {
        initResult.AppendError("Scene::Create3dModel() : Error setting 3D vertex buffer.");
        return initResult;
    }

    initResult = model2d_->Init(*gfx);
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

void Scene::OnCommandMouseDown(const float& x, const float& y) {
    model2d_->OnMouseDown(x, y);
}

void Scene::OnCommandMouseUp(const float& x, const float& y) {
    model2d_->OnMouseUp(x, y);
}

void Scene::OnCommandMouseClicked(const float& x, const float& y) {
    model2d_->OnMouseClicked(x, y);
}

void Scene::OnCommandToggleDebugInfo() {
    model2d_->ToggleDebugInfo();
}

void Scene::UpdateMousePosition(const float& x, const float& y) {
    model2d_->SetMousePosition(x, y);
}

void Scene::Update(const double& dt) {
    userInputHandler_->Update(dt);
    model2d_->Update(dt);
}

void Scene::Render(const double& dt) {
    graphicsEngine_->StartRender();

    // (3) Draw any 2D stuff on top of the 3D stuff.
    model2d_->Render(dt);

    graphicsEngine_->EndRender();
}

Result Scene::UpdateFps(const int64_t& newFps) {
    model2d_->SetFps(newFps);

    return Result{};
}
