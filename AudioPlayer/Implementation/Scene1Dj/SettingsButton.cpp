#include "SettingsButton.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Resources/ResourceManager.hpp>

Result SettingsButton::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("SettingsButton::Init() : Error initialising base Element.");
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
        initResult.AppendError("SettingsButton::Init() : Error initialising button.");
        return initResult;
    }

    AddChild(&button_);

    return initResult;
}
