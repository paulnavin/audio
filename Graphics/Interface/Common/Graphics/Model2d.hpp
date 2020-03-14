#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Sprite.hpp>
#include <Stl/StlWrapper.hpp>

#include <Graphics/DebugInfo.hpp>

class Element;
class GraphicsEngine;
class ResourceManager;

class Model2d {
public:
    Model2d();
    virtual ~Model2d() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx);
    virtual void Update(const double& dt);
    void Render(const double& dt);

    void OnMouseClicked(const float& x, const float& y);

    void SetFps(const int64_t& newFps);
    void SetMousePosition(const float& x, const float& y);
    void ToggleDebugInfo();

protected:
    using ElementVector = std::vector<Element*>;
    using ElementList = std::list<Element*>;
    using ElementSet = std::set<Element*>;
    ElementSet elements_;

    float mouseXPosition_;
    float mouseYPosition_;
    Sprite mouseCursor_;

    bool showDebugInfo_;
    DebugInfo debugElement_;
};
