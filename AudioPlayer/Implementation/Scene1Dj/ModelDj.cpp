#include "ModelDj.hpp"

#include <Display/Window.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/AnimatedSprite.hpp>
#include <UserInterface/Ellipse2d.hpp>
#include <UserInterface/ModelPortal.hpp>

Result ModelDj::Init(ModelPortal* portal) {
    rootElement_.SetDimensions(
        portal->gfx->GetTargetWindow()->GetWidth(),
        portal->gfx->GetTargetWindow()->GetHeight());

    Result initResult = rootElement_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising root element.");
        return initResult;
    }

    // 21, 10, 48, 21.

    topRow_.SetParent(&rootElement_);
    topRow_.SetDimensionsAsPercentage(100.0f, 21.0f);
    initResult = topRow_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising top row.");
        return initResult;
    }

    buttonRow_.SetParent(&rootElement_);
    buttonRow_.SetDimensionsAsPercentage(100.0f, 10.0f);
    buttonRow_.SetPositionAsPercentage(0.0f, 21.0f);
    initResult = buttonRow_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising button row.");
        return initResult;
    }

    jogWheel1_.SetParent(&rootElement_);
    jogWheel1_.SetSlipmatColour(Colour{ 1.0f, 0.5f, 0.5f, 1.0f });
    jogWheel1_.SetPositionColour(Colour{ 0.0f, 0.0f, 0.6f, 1.0f });
    jogWheel1_.SetPosition(181.0f, 225.0f);  // Note: This doesn't match the JogWheel code, cos for click detection need origin at top left.
    jogWheel1_.SetDimensions(150.0f, 150.0f);
    initResult = jogWheel1_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising 2D jog wheel.");
        return initResult;
    }

    explosion_.SetParent(&rootElement_);
    explosion_.SetPosition(400.0f, 400.0f);
    initResult = explosion_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ModelDj::Init() : Error initialising explosion.");
        return initResult;
    }

    elements_.push_back(&topRow_);
    elements_.push_back(&buttonRow_);
    elements_.push_back(&jogWheel1_);
    elements_.push_back(&explosion_);

    return Model2d::Init(portal);
}

void ModelDj::Update(const double& dt) {
    Model2d::Update(dt);

    jogWheel1_.Update(dt);
    explosion_.Update(dt);
}
