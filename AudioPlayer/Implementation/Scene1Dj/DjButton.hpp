#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

#include "Button.hpp"

struct ModelPortal;

class DjButton : public Element {
public:
    DjButton() = default;
    virtual ~DjButton() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

public:
    Result SetHighlightColour(const Colour& newColour);

private:
    Button button_;
    Rectangle2d highlight_;
};
