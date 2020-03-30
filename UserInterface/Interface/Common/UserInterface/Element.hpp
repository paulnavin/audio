#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/Position2d.hpp>
#include <Stl/StlWrapper.hpp>

class GraphicsEngine;

class Element {
public:
    Element() = default;
    virtual ~Element() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx);

    // Note: No Result passing in Render, for performance reasons.
    // By default just renders all children.
    virtual void Render(const double& dt);

    // Note: By default checks children for clicking.
    virtual bool OnClick();

public:
    const Position2d& GetPosition() const;
    const Position2d& GetAbsolutePosition() const;
    const Dimension2d& GetDimensions() const;
    const bool IsInitialised() const;

public:
    void AddChild(Element* newChild);
    void OnMouseClicked(const float& x, const float& y);
    void SetDimensions(const float& widthInPixels, const float& heightInPixels);
    void SetParent(const Element* parent);
    void SetPosition(const float& newX, const float& newY);
    void SetPositionAsPercentage(const float& newX, const float& newY);
    void SetDimensionsAsPercentage(const float& width, const float& height); // From 0 to 100.

protected:
    Dimension2d dimensionsOnScreen_;
    const Element* parent_;
    Position2d  positionOnScreen_;

private:
    using ChildVector = std::vector<Element*>;

private:
    void UpdateDimensionsOnScreen();
    void UpdatePositionOnScreen();

private:
    ChildVector children_;
    bool        isInitialised_ = false;
    Position2d  position_;
    Position2d  positionAsPercentage_;
    bool        percentagePosition_ = false;
    Dimension2d dimensions_;
    bool        percentageDimensions_ = false;
};
