#include <Graphics/DebugInfo.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/TextManager2d.hpp>
#include <Platform/WindowsInterface.hpp>

DebugInfo::DebugInfo(Element* parent)
    : Element(parent)
    , fpsText_(nullptr)
    , mousePositionText_(nullptr) {
}

Result DebugInfo::Init(const GraphicsEngine& gfx) {
    Result initResult = fpsText_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising 2D FPS text.");
        return initResult;
    }
    fpsText_.SetPosition(5.0f, 5.0f);
    fpsText_.SetDimensions(20.0f, 100.0f);

    initResult = mousePositionText_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("Model2d::Init() : Error initialising 2D mouse position text.");
        return initResult;
    }

    mousePositionText_.SetPosition(5.0f, 35.0f);
    mousePositionText_.SetDimensions(20.0f, 100.0f);

    return initResult;
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
