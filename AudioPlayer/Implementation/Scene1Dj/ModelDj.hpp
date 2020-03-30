#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Model2d.hpp>

#include "DjTopRow.hpp"
#include "ExplosionAnimation.hpp"
#include "JogWheel.hpp"

class GraphicsEngine;

class ModelDj : public Model2d {
public:
    ModelDj() = default;
    virtual ~ModelDj() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;
    virtual void Update(const double& dt) override;

private:
    Element rootElement_;
    JogWheel jogWheel1_;
    DjTopRow topRow_;

    ExplosionAnimation explosion_;
};

