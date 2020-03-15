#include <Graphics/DebugInfo.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/TextManager2d.hpp>
#include <Platform/WindowsInterface.hpp>
#include <UserInterface/Window.hpp>

Result DebugInfo::Init(const GraphicsEngine& gfx) {
    SetPosition(0.0f, 0.0f);
    SetDimensions(gfx.GetTargetWindow()->GetWidth(), gfx.GetTargetWindow()->GetHeight());
    SetFps(0);
    SetMousePosition(0.0f, 0.0f);

    fpsText_.SetParent(this);
    fpsText_.SetPosition(5.0f, 5.0f);
    fpsText_.SetDimensions(100.0f, 20.0f);
    Result initResult = fpsText_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DebugInfo::Init() : Error initialising 2D FPS text.");
        return initResult;
    }

    mousePositionText_.SetParent(this);
    mousePositionText_.SetPosition(5.0f, 35.0f);
    mousePositionText_.SetDimensions(150.0f, 20.0f);
    initResult = mousePositionText_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DebugInfo::Init() : Error initialising 2D mouse position text.");
        return initResult;
    }

    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("DebugInfo::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Element::Init(gfx);
}

void DebugInfo::Render(const double& dt) {
    fpsText_.Render(dt);
    mousePositionText_.Render(dt);
}

void DebugInfo::SetFps(const int64_t& newFps) {
    std::wostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << newFps << std::endl;

    fpsText_.SetText(fpsString.str());
}

void DebugInfo::SetMousePosition(const float& x, const float& y) {
    std::wostringstream outputString{};
    outputString.precision(6);
    outputString << "Mouse: " << x << ", " << y << std::endl;

    mousePositionText_.SetText(outputString.str());
}

Result DebugInfo::UpdateDetails() {
    // Nothing here at the moment...
    // TODO: Maybe store FPS and mouse position values, and SetText here?
    return Result{};
}
