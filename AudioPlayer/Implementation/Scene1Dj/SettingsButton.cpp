#include "SettingsButton.hpp"

#include "AudioPlayerUserInputCommands.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/Commander.hpp>
#include <UserInterface/ModelPortal.hpp>

Result SettingsButton::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("SettingsButton::Init() : Error initialising base Element.");
        return initResult;
    }

    button_.SetParent(this);
    button_.SetDimensionsAsPercentage(100.0f, 100.0f);
    button_.SetBackgroundImage("apollo_panel_button_night.9");
    button_.SetForegroundImage("SettingsButton");
    button_.SetOnClickHandler(
        [this]() {
            OutputDebugStringA("Clicked");
            this->chell_->commander->SendAppCommand(ShowSettings);
        });
    initResult = button_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("SettingsButton::Init() : Error initialising button.");
        return initResult;
    }

    AddChild(&button_);

    return initResult;
}
