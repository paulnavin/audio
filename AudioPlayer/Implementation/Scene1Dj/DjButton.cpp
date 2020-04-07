#include "DjButton.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Resources/ResourceManager.hpp>

Result DjButton::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    button_.SetParent(this);
    button_.SetDimensionsAsPercentage(100.0f, 100.0f);
    button_.SetOnClickHandler(
        []() {
        OutputDebugStringA("Clicked");
        ResourceManager::ShowOpenFileDialog();
    });
    initResult = button_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjButton::Init() : Error initialising button.");
        return initResult;
    }

    highlight_.SetParent(this);
    highlight_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 0.0f });
    highlight_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = highlight_.Init(portal);
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
