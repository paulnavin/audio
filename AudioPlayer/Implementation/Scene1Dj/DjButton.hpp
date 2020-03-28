#pragma once

#include <Graphics/Element.hpp>
#include <Graphics/Rectangle2d.hpp>

#include "Button.hpp"

class GraphicsEngine;

class DjButton : public Element {
public:
    DjButton() = default;
    virtual ~DjButton() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;

public:
    Result SetHighlightColour(const Colour& newColour);

private:
    Button button_;
    Rectangle2d highlight_;
};
