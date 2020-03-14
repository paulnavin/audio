#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Element.hpp>
#include <Graphics/Text2d.hpp>

class Engine2d;
class TextManager2d;

class DebugInfo : public Element {

public:
    DebugInfo(Element* parent);
    virtual ~DebugInfo() = default;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager) override;
    void Render(const double& dt) override;

public:
    void SetFps(const int64_t& newFps);
    void SetMousePosition(const float& x, const float& y);

private:
    int64_t fps_;
    Text2d fpsText_;
    Text2d mousePositionText_;
};
