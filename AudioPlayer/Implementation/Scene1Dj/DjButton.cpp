#include "DjButton.hpp"

#include <Graphics/GraphicsEngine.hpp>

Result DjButton::Init(const GraphicsEngine& gfx) {
    Result initResult = Element::Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    button_.SetParent(this);
    button_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = button_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjButton::Init() : Error initialising button.");
        return initResult;
    }

    highlight_.SetParent(this);
    highlight_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 0.0f });
    highlight_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = highlight_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjButton::Init() : Error initialising highlight.");
        return initResult;
    }

    AddChild(&button_);
    AddChild(&highlight_);

    return initResult;
}


Result DjButton::SetHighlightColour(const Colour& newColour) {
    return highlight_.SetColour(newColour);
}
