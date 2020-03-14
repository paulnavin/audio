#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text2d.hpp>
#include <Stl/StlWrapper.hpp>

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

    // TODO: Move this all into a debug element.
    Sprite mouseCursor_;
    Text2d fpsText_;
    Text2d mousePositionText_;
};
