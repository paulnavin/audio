#pragma once

#include <ErrorHandling/Result.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/Text2d.hpp>

class DebugInfo : public Element {

public:
    DebugInfo() = default;
    virtual ~DebugInfo() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;

public:
    void SetFps(const int64_t& newFps);
    void SetMousePosition(const float& x, const float& y);

private:
    Result UpdateDetails();

private:
    Text2d fpsText_;
    Text2d mousePositionText_;
};
