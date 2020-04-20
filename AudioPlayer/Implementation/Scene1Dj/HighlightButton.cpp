#include "HighlightButton.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Platform/File.hpp>

Result HighlightButton::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    background_.SetParent(this);
    background_.SetDimensionsAsPercentage(100.0f, 100.0f);
    background_.SetBitmapName("apollo_panel_button_night.9");
    initResult = background_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("HighlightButton::Init() : Error initialising background.");
        return initResult;
    }

    button_.SetParent(this);
    button_.SetPositionAsPercentage(2.5f, 2.5f);
    button_.SetDimensionsAsPercentage(95.0f, 95.0f);
    button_.SetBackgroundImage("apollo_panel_button_inner_night.9");
    button_.SetOnClickHandler(
        []() {
        OutputDebugStringA("Clicked");
        // TODO: Don't call ShowOpenFileDialog() directly here, send a message to something on another thread.
        File::ShowOpenFileDialog();
    });
    initResult = button_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("HighlightButton::Init() : Error initialising button.");
        return initResult;
    }

    highlight_.SetParent(this);
    highlight_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 0.0f });
    highlight_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = highlight_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("HighlightButton::Init() : Error initialising highlight.");
        return initResult;
    }

    AddChild(&background_);
    AddChild(&button_);
    AddChild(&highlight_);

    return initResult;
}


Result HighlightButton::SetHighlightColour(const Colour& newColour) {
    return highlight_.SetColour(newColour);
}
