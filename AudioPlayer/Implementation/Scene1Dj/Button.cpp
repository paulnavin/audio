#include "Button.hpp"

Result Button::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Button::Init() : Error initialising base Element.");
        return initResult;
    }

    background_.SetParent(this);
    background_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    background_.SetPosition(0.0f, 0.0f);
    background_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = background_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Button::Init() : Error initialising background.");
        return initResult;
    }

    AddChild(&background_);

    return initResult;
}

bool Button::OnClick() {
    if (background_.GetColour().alpha > 0.7f) {
        background_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 0.5f });
    } else {
        background_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    return true;
}
