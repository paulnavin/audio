#include <UserInterface/Model2d.hpp>

#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/ModelPortal.hpp>

Model2d::Model2d()
    : showDebugInfo_(false) {
}

Result Model2d::Init(ModelPortal* portal) {

    Result initResult = debugElement_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising debug info.");
        return initResult;
    }

    mouseCursor_.SetBitmapName(mouseCursorBitmapName_.c_str());
    mouseCursor_.SetDimensions(48.0f, 48.0f);

    initResult = mouseCursor_.Init(portal);
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

    if (isActive_ == true) {
        mouseCursor_.Render(dt);

        if (showDebugInfo_ == true) {
            debugElement_.Render(dt);
        }
    }
}

void Model2d::SetActive(bool isActive) {
    isActive_ = isActive;
}

void Model2d::SetCursorBitmap(const std::string& bitmapName) {
    mouseCursorBitmapName_ = bitmapName;
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
