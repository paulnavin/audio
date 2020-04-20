#include <UserInterface/DebugInfo.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/TextManager2d.hpp>
#include <Platform/Window.hpp>
#include <Platform/WindowsInterface.hpp>
#include <UserInterface/DefaultTextStyles.hpp>
#include <UserInterface/ModelPortal.hpp>

Result DebugInfo::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionButton::Init() : Error initialising base Element.");
        return initResult;
    }

    SetPosition(0.0f, 0.0f);
    SetDimensions(portal->gfx->GetTargetWindow()->GetWidth(), portal->gfx->GetTargetWindow()->GetHeight());
    SetFps(0);
    SetMousePosition(0.0f, 0.0f);

    fpsText_.SetParent(this);
    fpsText_.SetPosition(5.0f, 5.0f);
    fpsText_.SetDimensions(200.0f, 50.0f);
    fpsText_.SetStyle(DefaultText);
    initResult = fpsText_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DebugInfo::Init() : Error initialising 2D FPS text.");
        return initResult;
    }

    mousePositionText_.SetParent(this);
    mousePositionText_.SetStyle(DefaultText);
    mousePositionText_.SetPosition(5.0f, 55.0f);
    mousePositionText_.SetDimensions(200.0f, 50.0f);
    initResult = mousePositionText_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DebugInfo::Init() : Error initialising 2D mouse position text.");
        return initResult;
    }

    initResult = UpdateDetails();
    if (initResult.HasErrors()) {
        initResult.AppendError("DebugInfo::Init() : Couldn't update details in Init()");
        return initResult;
    }
    return initResult;
}

void DebugInfo::Render(const double& dt) {
    fpsText_.RenderText(dt, fpsTextToShow_);
    mousePositionText_.RenderText(dt, mousePositionTextToShow_);
}

void DebugInfo::SetFps(const int64_t& newFps) {
    std::ostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << newFps << std::endl;
    fpsTextToShow_ = fpsString.str();
}

void DebugInfo::SetMousePosition(const float& x, const float& y) {
    std::ostringstream outputString{};
    outputString.precision(6);
    outputString << "Mouse: " << x << ", " << y << std::endl;

    mousePositionTextToShow_ = outputString.str();
}

Result DebugInfo::UpdateDetails() {
    // Nothing here at the moment...
    // TODO: Maybe store FPS and mouse position values, and SetText here?
    return Result{};
}
