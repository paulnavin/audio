#include <Graphics/Model2d.hpp>

#include <Graphics/Element.hpp>
#include <Graphics/GraphicsEngine.hpp>

Model2d::Model2d()
    : showDebugInfo_(false) {
}

Result Model2d::Init(const GraphicsEngine& gfx) {
    const ResourceManager& resourceManager = gfx.GetResourceManager();
    
    Result initResult = debugElement_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising debug info.");
        return initResult;
    }

    std::string spriteFileName = resourceManager.GetFullCursorFileName("BlueArrow.png");
    initResult = mouseCursor_.SetSourceFileName(spriteFileName);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error setting mouse cursor file name.");
        return initResult;
    }
    mouseCursor_.SetDimensions(48.0f, 48.0f);

    initResult = mouseCursor_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising mouse cursor sprite.");
        return initResult;
    }

    return initResult;
}

void Model2d::Update(const double& /*dt*/) {
    // Nothing at the moment.
}

void Model2d::Render(const double& dt) {
    for (Element* element : elements_) {
        element->Render(dt);
    }

    mouseCursor_.Render(dt);

    if (showDebugInfo_ == true) {
        debugElement_.Render(dt);
    }
}

void Model2d::OnMouseClicked(const float& x, const float& y) {
    Position2d position;
    Dimension2d dimensions;
    for (Element* element : elements_) {
        position = element->GetAbsolutePosition();
        dimensions = element->GetDimensions();
        if ((x >= position.x) &&
            (x <= position.x + dimensions.width) &&
            (y >= position.y) &&
            (y <= position.y + dimensions.height)) {
            bool clickResult = element->OnClick();
            if (clickResult == false) {
                element->OnMouseClicked(x, y);
            }
        }
    }
}

void Model2d::SetFps(const int64_t& newFps) {
    debugElement_.SetFps(newFps);
}

void Model2d::ToggleDebugInfo() {
    showDebugInfo_ = !showDebugInfo_;
}


void Model2d::SetMousePosition(const float& x, const float& y) {
    mouseXPosition_ = x;
    mouseYPosition_ = y;

    mouseCursor_.SetPosition(x, y);
    debugElement_.SetMousePosition(x, y);
}

void Model2d::SetWindow(Window* window) {
    window_ = window;
}
