#pragma once

#include <ErrorHandling/Result.hpp>
#include <Stl/StlWrapper.hpp>
#include <UserInterface/DebugInfo.hpp>
#include <UserInterface/Sprite.hpp>

class Element;
class GraphicsEngine;
class Window;

class Model2d {
public:
    Model2d();
    virtual ~Model2d() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx);
    virtual void Update(const double& dt);
    void Render(const double& dt);

    void OnMouseDown(const float& x, const float& y);
    void OnMouseUp(const float& x, const float& y);
    void OnMouseClicked(const float& x, const float& y);

    void SetFps(const int64_t& newFps);
    void SetMousePosition(const float& x, const float& y);
    void SetWindow(Window* window);
    void ToggleDebugInfo();

protected:
    using ElementVector = std::vector<Element*>;
    using ElementList = std::list<Element*>;
    using ElementSet = std::set<Element*>;
    ElementVector elements_;

    float mouseXPosition_;
    float mouseYPosition_;
    Sprite mouseCursor_;

    bool showDebugInfo_;
    DebugInfo debugElement_;

    Window* window_;
};