#include <Graphics/Model2d.hpp>

#include <Graphics/Element.hpp>
#include <Graphics/GraphicsEngine.hpp>

Model2d::Model2d() 
    : fpsElement_(nullptr)
    , mousePositionElement_(nullptr)
    , mouseCursor_ (nullptr)
    , fpsText_(nullptr)
    , mousePositionText_(nullptr) {

}

Result Model2d::Init(const GraphicsEngine& gfx) {
    const Engine2d& engine = gfx.GetEngine2d();
    const TextManager2d& textManager = gfx.GetTextManager2d();
    const ResourceManager& resourceManager = gfx.GetResourceManager();
    
    Result initResult = fpsText_.Init(engine, textManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising 2D FPS text.");
        return initResult;
    }
    fpsText_.SetPosition(5.0f, 5.0f);
    fpsText_.SetDimensions(20.0f, 100.0f);

    showFps_ = true;

    initResult = mouseCursor_.Init(engine, textManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising mouse cursor sprite.");
        return initResult;
    }

    std::string spriteFileName = resourceManager.GetFullCursorFileName("BlueArrow.png");
    initResult = mouseCursor_.SetSourceFileName(spriteFileName);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error setting mouse cursor file name.");
        return initResult;
    }
    mouseCursor_.SetDimensions(48.0f, 48.0f);

    initResult = mousePositionText_.Init(engine, textManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising 2D mouse position text.");
        return initResult;
    }

    mousePositionText_.SetPosition(5.0f, 35.0f);
    mousePositionText_.SetDimensions(20.0f, 100.0f);

    showMousePosition_ = true;

    SetFpsElement(&fpsText_);
    SetMousePositionElement(&mousePositionText_);

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

    if (showFps_ == true) {
        fpsElement_->Render(dt);
    }

    if (showMousePosition_ == true) {
        mousePositionElement_->Render(dt);
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
    fps_ = newFps;

    std::wostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << fps_ << std::endl;
    
    fpsText_.SetText(fpsString.str());
}

void Model2d::SetShowFps(const bool show) {
    showFps_ = show;
}

void Model2d::SetFpsElement(Element* newElement) {
    fpsElement_ = newElement;
}

void Model2d::SetMousePosition(const float& x, const float& y) {
    mouseXPosition_ = x;
    mouseYPosition_ = y;

    std::wostringstream outputString{};
    outputString.precision(6);
    outputString << "Mouse: " << x << ", " << y << std::endl;
    
    mousePositionText_.SetText(outputString.str());
    
    mouseCursor_.SetPosition(x, y);
}

void Model2d::SetShowMousePosition(const bool show) {
    showMousePosition_ = show;
}

void Model2d::SetMousePositionElement(Element* newElement) {
    mousePositionElement_ = newElement;
}
