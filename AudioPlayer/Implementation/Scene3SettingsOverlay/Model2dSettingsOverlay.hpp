#pragma once

#include <Display/Window.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/Button.hpp>
#include <UserInterface/Commander.hpp>
#include <UserInterface/Ellipse2d.hpp>
#include <UserInterface/Model2d.hpp>
#include <UserInterface/ModelPortal.hpp>
#include <UserInterface/Rectangle2d.hpp>

#include "AudioPlayerUserInputCommands.hpp"

class Model2dSettingsOverlay : public Model2d {
public:
    explicit Model2dSettingsOverlay()
        : Model2d() {};
    ~Model2dSettingsOverlay() = default;

public:
    virtual Result Init(ModelPortal* portal) override {
        keen_ = portal->commander;
        rootElement_.SetDimensions(
            portal->gfx->GetTargetWindow()->GetWidth(),
            portal->gfx->GetTargetWindow()->GetHeight());

        Result initResult = rootElement_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising root element.");
            return initResult;
        }

        rectangle_.SetParent(&rootElement_);
        rectangle_.SetColour(Colour{ 0.0f, 0.0f, 0.0f, 0.5f });
        rectangle_.SetPosition(0.0f, 0.0f);
        rectangle_.SetDimensionsAsPercentage(100.0f, 100.0f);

        initResult = rectangle_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising 2D rectangle.");
            return initResult;
        }

        ellipse_.SetParent(&rootElement_);
        ellipse_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
        ellipse_.SetPosition(700.0f, 500.0f);
        ellipse_.SetDimensions(75.0f, 200.0f);
        initResult = ellipse_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising 2D ellipse.");
            return initResult;
        }

        hideSettingsButton_.SetParent(&rootElement_);
        hideSettingsButton_.SetDimensionsAsPercentage(8.0f, 21.0f);
        hideSettingsButton_.SetPositionAsPercentage(46.0f, 0.0f);
        hideSettingsButton_.SetOnClickHandler(
            [this]() {
            OutputDebugStringA("Hide Settings Clicked");
            this->keen_->SendAppCommand(HideSettings);
        });
        initResult = hideSettingsButton_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising hide settings button.");
            return initResult;
        }

        elements_.push_back(&rectangle_);
        elements_.push_back(&ellipse_);
        elements_.push_back(&hideSettingsButton_);

        SetCursorBitmap("SettingsButton");

        return Model2d::Init(portal);
    }

private:
    Element rootElement_;
    Ellipse2d ellipse_;
    Rectangle2d rectangle_;
    Button hideSettingsButton_;
    Commander* keen_;
};
