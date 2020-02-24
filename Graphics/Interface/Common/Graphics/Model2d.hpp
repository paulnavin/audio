#pragma once

#include <ErrorHandling/Result.hpp>
#include <Stl/StlWrapper.hpp>

#include "Element.hpp"

class Engine2d;
class ResourceManager;

class Model2d {
public:
    Model2d() = default;
    virtual ~Model2d() = default;

public:
    virtual Result Init(const Engine2d& engine, const TextManager2d& textManager, const ResourceManager& resourceManager) = 0;

    virtual void Update(const double& dt) = 0;

    // Note: No Result passing in Render, for performance reasons.
    void Render(const double& dt);

    void OnMouseClicked(const float& x, const float& y);

    virtual void SetFps(const int64_t& newFps);
    virtual void SetShowFps(const bool show);
    void SetFpsElement(Element* newElement);

    virtual void SetMousePosition(const float& x, const float& y);
    virtual void SetShowMousePosition(const bool show);
    void SetMousePositionElement(Element* newElement);

protected:
    using ElementVector = std::vector<Element*>;
    using ElementList = std::list<Element*>;
    using ElementSet = std::set<Element*>;
    ElementSet elements_;

    bool showFps_;
    int64_t fps_;
    Element* fpsElement_;

    bool showMousePosition_;
    float mouseXPosition_;
    float mouseYPosition_;
    Element* mousePositionElement_;
};
