#include <Graphics/GraphicsEngine.hpp>

#include <Graphics/Model2d.hpp>
#include <UserInterface/ErrorDisplay.hpp>
#include <UserInterface/Window.hpp>
#include <Utility/ResourceManager.hpp>

Result GraphicsEngine::Init(const Window& targetWindow, const ResourceManager& resourceManager) {
    Result initResult{};

    initResult = engine3d_.Init(targetWindow, resourceManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init() : Error initialising 3D controller.");
        return initResult;
    }

    initResult = engine2d_.Init(targetWindow, engine3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init() : Error initialising 2D controller.");
        return initResult;
    }

    initResult = textManager2d_.Init(targetWindow, engine2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine2d::Init() : Error initialising 2D text manager.");
        return initResult;
    }

    return Result{};
}

Result GraphicsEngine::Init2dModel(Model2d* model) {
    return model->Init(engine2d_, textManager2d_);
}

void GraphicsEngine::NextDisplayConfig() {
    engine3d_.NextDisplayConfig();
}

void GraphicsEngine::PreviousDisplayConfig() {
    engine3d_.PreviousDisplayConfig();
}

void GraphicsEngine::Render(const double& dt) {
    // (1) Clear the screen.
    engine3d_.ClearBuffers();

    // (2) Draw any 3D stuff.
    engine3d_.RenderVertices();

    // (3) Draw any 2D stuff on top of the 3D stuff.
    engine2d_.RenderModel(dt);

    // (4) Present the buffers to the screen.
    engine3d_.Present();
}

void GraphicsEngine::ResetDisplayConfig() {
    engine3d_.ResetDisplayConfig();
}

void GraphicsEngine::Resize() {
    Result resizeResult{};

    engine2d_.PrepareForResize();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("GraphicsEngine::Resize() : Could not prepare 2D engine for resize.");
        ErrorDisplay::ShowErrors(resizeResult);
        return;
    }

    engine3d_.Resize();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("GraphicsEngine::Resize() : Could not resize 3D engine.");
        ErrorDisplay::ShowErrors(resizeResult);
        return;
    }
    
    engine2d_.Resize();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("GraphicsEngine::Resize() : Could not resize 2D engine.");
        ErrorDisplay::ShowErrors(resizeResult);
        return;
    }

    resizeResult = textManager2d_.Resize();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("GraphicsEngine::Resize() : Could not resize 2D text manager.");
        ErrorDisplay::ShowErrors(resizeResult);
        return;
    }
}

Result GraphicsEngine::Set2dModel(Model2d* model) {
    engine2d_.SetModel(model);
    return Result{};
}

Result GraphicsEngine::Set3dModel(const Model3d& model) {
    Result initResult = engine3d_.InitGraphics(model);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init() : Error initialising 3D graphics when setting 3D model.");
    }
    return initResult;
}

void GraphicsEngine::ToggleFullScreen() {
    engine3d_.ToggleFullScreen();
}
