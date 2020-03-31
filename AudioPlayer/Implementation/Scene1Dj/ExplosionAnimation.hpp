#pragma once

#include <UserInterface/AnimatedSprite.hpp>
#include <UserInterface/Element.hpp>

struct ModelPortal;

class ExplosionAnimation : public Element {
public:
    ExplosionAnimation() = default;
    virtual ~ExplosionAnimation() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

    virtual void Update(const double& dt);

    virtual void Render(const double& dt) override;

private:
    AnimatedSprite animatedSprite_;
};

