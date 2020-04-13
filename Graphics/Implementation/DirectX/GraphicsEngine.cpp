#include <Graphics/GraphicsEngine.hpp>

#include <Display/ErrorDisplay.hpp>
#include <Display/Window.hpp>

const Engine2d& GraphicsEngine::GetEngine2d() const {
    return engine2d_;
}

const ResourceLocator& GraphicsEngine::GetResourceLocator() const {
    return resourceLocator_;
}

const TextManager2d& GraphicsEngine::GetTextManager2d() const {
    return textManager2d_;
}

const Window* GraphicsEngine::GetTargetWindow() const {
    return targetWindow_;
}

Result GraphicsEngine::Init(Window* targetWindow, const ResourceLocator& resourceManager) {
    Result initResult{};

    resourceLocator_ = resourceManager;
    targetWindow_ = targetWindow;

    initResult = engine3d_.Init(*targetWindow, resourceManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init() : Error initialising 3D controller.");
        return initResult;
    }

    initResult = engine2d_.Init(*targetWindow, engine3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init() : Error initialising 2D controller.");
        return initResult;
    }

    initResult = textManager2d_.Init(*targetWindow, engine2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine2d::Init() : Error initialising 2D text manager.");
        return initResult;
    }

    return Result{};
}

Result GraphicsEngine::Init3dVertices(const VertexBuffer& vertexBuffer) {
    Result initResult = engine3d_.InitGraphics(vertexBuffer);
    if (initResult.HasErrors()) {
        initResult.AppendError("GraphicsEngine::Init3dVertices() : Error initialising 3D vertices.");
    }
    return initResult;
}

void GraphicsEngine::NextDisplayConfig() {
    engine3d_.NextDisplayConfig();
    targetWindow_->UpdateSizes();
}

void GraphicsEngine::PreviousDisplayConfig() {
    engine3d_.PreviousDisplayConfig();
    targetWindow_->UpdateSizes();
}

void GraphicsEngine::StartRender() {
    // (1) Clear the screen.
    engine3d_.ClearBuffers();

    // (2) Draw any 3D stuff.
    //engine3d_.RenderVertices();

    engine2d_.StartRender();
    // The 2D model will Render() after this.
}

void GraphicsEngine::EndRender() {
    engine2d_.EndRender();

    // (4) Present the buffers to the screen.
    engine3d_.Present();
}

void GraphicsEngine::ResetDisplayConfig() {
    engine3d_.ResetDisplayConfig();
    targetWindow_->UpdateSizes();
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

void GraphicsEngine::ToggleFullScreen() {
    engine3d_.ToggleFullScreen();
}
