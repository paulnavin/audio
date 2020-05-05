#pragma once

#include <Platform/ErrorHandling.hpp>
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
    static constexpr size_t MAX_STRING_LENGTH = 100;

private:
    Result UpdateDetails();

private:
    Text2d fpsText_;
    char fpsTextToShow_[MAX_STRING_LENGTH];
    Text2d mousePositionText_;
    char mousePositionTextToShow_[MAX_STRING_LENGTH];
};
