#include <Graphics/Model2d.hpp>

#include <Graphics/Element.hpp>
#include <Graphics/GraphicsEngine.hpp>

Model2d::Model2d() 
    : mouseCursor_ (nullptr)
    , showDebugInfo_(false)
    , debugElement_(nullptr) {
}

Result Model2d::Init(const GraphicsEngine& gfx) {
    const Engine2d& engine = gfx.GetEngine2d();
    const TextManager2d& textManager = gfx.GetTextManager2d();
    const ResourceManager& resourceManager = gfx.GetResourceManager();
    
    Result initResult = debugElement_.Init(engine, textManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising debug info.");
        return initResult;
    }

    initResult = mouseCursor_.Init(engine, textManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising mouse cursor sprite.");
        return initResult;
    }

    std::string spriteFileName = resourceManager.GetFullCursorFileName("BlueArrow.png");
    initResult = mouseCursor_.SetSourceFileName(spriteFileName);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error setting mouse cursor file name.");
        return initResult;
    }
    mouseCursor_.SetDimensions(48.0f, 48.0f);

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
        position = element->GetPosition();
        dimensions = element->GetDimensions();
        if ((x >= position.x) &&
            (x <= position.x + dimensions.width) &&
            (y >= position.y) &&
            (y <= position.y + dimensions.height)) {
            element->OnClick();
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
