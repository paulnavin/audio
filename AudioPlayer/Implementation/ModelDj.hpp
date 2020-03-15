#pragma once

#include <Graphics/AnimatedSprite.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/Ellipse2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text2d.hpp>
#include <Stl/StlWrapper.hpp>
#include <UserInterface/Window.hpp>

#include "ExplosionAnimation.hpp"
#include "JogWheel.hpp"

class ModelDj : public Model2d {
public:
    ModelDj()
        : Model2d() {};
    ~ModelDj() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override {
        rootElement_.SetDimensions(gfx.GetTargetWindow()->GetHeight(), gfx.GetTargetWindow()->GetWidth());
        
        Result initResult = rootElement_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising root element.");
            return initResult;
        }

        openFile1Button_.SetParent(&rootElement_);
        openFile1Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile1Button_.SetPosition(0.0f, 0.0f);
        openFile1Button_.SetDimensionsAsPercentage(20.0f, 10.0f);
        initResult = openFile1Button_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }

        openFile2Button_.SetParent(&rootElement_);
        openFile2Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile2Button_.SetPosition(800.0f, 0.0f);
        openFile2Button_.SetDimensionsAsPercentage(20.0f, 10.0f);
        initResult = openFile2Button_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }

        jogWheel1_.SetParent(&rootElement_);
        jogWheel1_.SetSlipmatColour(Colour{ 1.0f, 0.5f, 0.5f, 1.0f });
        jogWheel1_.SetPositionColour(Colour{ 0.0f, 0.0f, 0.6f, 1.0f });
        jogWheel1_.SetPosition(181.0f, 225.0f);  // Note: This doesn't match the JogWheel code, cos for click detection need origin at top left.
        jogWheel1_.SetDimensions(150.0f, 150.0f);
        initResult = jogWheel1_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D jog wheel.");
            return initResult;
        }

        explosion_.SetParent(&rootElement_);
        explosion_.SetPosition(400.0f, 400.0f);
        initResult = explosion_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising explosion.");
            return initResult;
        }

        elements_.push_back(&openFile1Button_);
        elements_.push_back(&openFile2Button_);
        elements_.push_back(&jogWheel1_);
        elements_.push_back(&explosion_);

        return Model2d::Init(gfx);
    }

    void Update(const double& dt) override {
        Model2d::Update(dt);

        jogWheel1_.Update(dt);
        explosion_.Update(dt);
    }

private:
    Element rootElement_;
    JogWheel jogWheel1_;
    Rectangle2d openFile1Button_;
    Rectangle2d openFile2Button_;

    ExplosionAnimation explosion_;
};

