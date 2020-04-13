#pragma once

#include <UserInterface/Button.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

struct ModelPortal;

class HighlightButton : public Element {
public:
    HighlightButton() = default;
    virtual ~HighlightButton() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

public:
    Result SetHighlightColour(const Colour& newColour);

private:
    Button button_;
    Rectangle2d highlight_;
};
