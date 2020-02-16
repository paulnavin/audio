#pragma once

#include <Graphics/AnimatedSprite.hpp>
#include <Graphics/Element.hpp>
#include <Utility/ResourceManager.hpp>
#include <Utility/StlWrapper.hpp>

class ExplosionAnimation : public Element {
public:
    ExplosionAnimation(Element* parent) : Element(parent), animatedSprite_(parent){ }
    ~ExplosionAnimation() = default;

public:
    virtual Result Init(const Engine2d& /*engine*/, const TextManager2d& /*textManager*/) override {
        return Result{};
    }

    Result Init(const Engine2d& engine, const TextManager2d& textManager, const ResourceManager& resourceManager) {
        Result initResult{};
        initResult = animatedSprite_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ExplosionAnimation::Init() : Error initialising animated sprite.");
            return initResult;
        }

        AnimatedSpriteCycleDataVector explosionAnimationCycles;

        AnimatedSpriteCycleData cycle;
        cycle.name = "Explosion";
        cycle.startFrame = 0;
        cycle.numberOfFrames = 8;
        cycle.framesPerRow = 8;
        cycle.width = 16;
        cycle.height = 16;
        cycle.paddingWidth = 0;
        cycle.paddingHeight = 0;
        cycle.borderPaddingHeight = cycle.borderPaddingWidth = 0;
        cycle.rotationCenterX = cycle.rotationCenterY = 0.5f;
        explosionAnimationCycles.push_back(cycle);

        std::string animatedSpriteFileName = resourceManager.GetFullAnimatedSpriteFileName("BlueCrystal.png");
        initResult = animatedSprite_.SetSourceFileName(animatedSpriteFileName);
        if (initResult.HasErrors()) {
            initResult.AppendError("ExplosionAnimation::Init() : Error setting animated sprite file name.");
            return initResult;
        }
        animatedSprite_.SetCycleData(explosionAnimationCycles);
        animatedSprite_.SetPosition(GetPosition().x, GetPosition().y);

        return Result{};
    }

    void Update(const double& dt) {
        animatedSprite_.UpdateAnimation(dt);
    }

    void Render(const double& dt) {
        animatedSprite_.Render(dt);
    }

private:
    AnimatedSprite animatedSprite_;
};

