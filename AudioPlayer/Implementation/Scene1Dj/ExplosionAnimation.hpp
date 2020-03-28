#pragma once

#include <Graphics/AnimatedSprite.hpp>
#include <Graphics/Element.hpp>

class GraphicsEngine;

class ExplosionAnimation : public Element {
public:
    ExplosionAnimation() = default;
    virtual ~ExplosionAnimation() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;

    virtual void Update(const double& dt);

    virtual void Render(const double& dt) override;

private:
    AnimatedSprite animatedSprite_;
};

