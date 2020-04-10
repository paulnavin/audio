#include "ViewSelectionButton.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Resources/ResourceManager.hpp>

Result ViewSelectionButton::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionButton::Init() : Error initialising base Element.");
        return initResult;
    }

    button_.SetParent(this);
    button_.SetDimensionsAsPercentage(100.0f, 100.0f);
    button_.SetOnClickHandler(
        []() {
        OutputDebugStringA("Selected");
    });
    initResult = button_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionButton::Init() : Error initialising button.");
        return initResult;
    }

    text_.SetParent(this);
    text_.SetDimensionsAsPercentage(100.0f, 100.0f);
    initResult = text_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionButton::Init() : Error initialising text.");
        return initResult;
    }

    AddChild(&button_);
    AddChild(&text_);

    return initResult;
}


Result ViewSelectionButton::SetText(const std::string& text) {
    return text_.SetText(text);
}