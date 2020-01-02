#pragma once

#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

#include "Dimension2d.hpp"
#include "Position2d.hpp"

class Engine2d;

class Element {
public:
    Element(Element* parent);
    virtual ~Element() = default;

public:
    virtual Result Init(const Engine2d&) { return Result{}; };

    // Note: No Result passing in Render, for performance reasons.
    virtual void Render(const double&) {};

    virtual void OnClick() {
        
    };

public:
    const Position2d& GetPosition() const;
    const Dimension2d& GetDimensions() const;

public:
    void SetDimensions(const float& heightInPixels, const float& widthInPixels);
    void SetPosition(const float& newX, const float& newY);
    void SetDimensionsAsPercentage(const float& height, const float& width); // From 0 to 100.
 
protected:
    Dimension2d dimensions_;
    Position2d  position_;

private:
    using ChildVector = std::vector<Element*>;

private:
    ChildVector children_;
    Element* parent_;
};
