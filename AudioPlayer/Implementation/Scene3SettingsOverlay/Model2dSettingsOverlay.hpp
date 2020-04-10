#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/Ellipse2d.hpp>
#include <UserInterface/Model2d.hpp>
#include <UserInterface/Rectangle2d.hpp>

class Model2dSettingsOverlay : public Model2d {
public:
    explicit Model2dSettingsOverlay()
        : Model2d() {};
    ~Model2dSettingsOverlay() = default;

public:
    virtual Result Init(ModelPortal* portal) override {
        Result initResult = rectangle_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        rectangle_.SetColour(Colour{ 0.0f, 1.0f, 0.0f, 1.0f });
        rectangle_.SetPosition(300.0f, 300.0f);
        rectangle_.SetDimensions(50.0f, 50.0f);

        initResult = ellipse_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Model2dSettingsOverlay::Init() : Error initialising 2D ellipse.");
            return initResult;
        }
        ellipse_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
        ellipse_.SetPosition(700.0f, 500.0f);
        ellipse_.SetDimensions(75.0f, 200.0f);

        elements_.push_back(&ellipse_);
        elements_.push_back(&rectangle_);

        return Model2d::Init(portal);
    }

private:
    Ellipse2d ellipse_;
    Rectangle2d rectangle_;
};
