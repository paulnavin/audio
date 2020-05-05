#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Model2d.hpp>

#include "BottomRow.hpp"
#include "ButtonRow.hpp"
#include "DjTopRow.hpp"
#include "ExplosionAnimation.hpp"
#include "JogWheel.hpp"

struct ModelPortal;

class ModelDj : public Model2d {
public:
    ModelDj() = default;
    virtual ~ModelDj() = default;

public:
    virtual Result Init(ModelPortal* portal) override;
    virtual void Update(const double& dt) override;

private:
    Element rootElement_;
    JogWheel jogWheel1_;
    DjTopRow topRow_;
    ButtonRow buttonRow_;
    BottomRow bottomRow_;

    ExplosionAnimation explosion_;
};

