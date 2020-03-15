#pragma once

#include <Graphics/AnimatedSprite.hpp>
#include <Graphics/Element.hpp>
#include <FileSystem/ResourceManager.hpp>
#include <Stl/StlWrapper.hpp>

class ExplosionAnimation : public Element {
public:
    ExplosionAnimation() = default;
    virtual ~ExplosionAnimation() = default;

public:
    Result Init(const GraphicsEngine& gfx) {
        const ResourceManager& resourceManager = gfx.GetResourceManager();

        Result initResult{};
        
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

        animatedSprite_.SetParent(this);
        animatedSprite_.SetCycleData(explosionAnimationCycles);
        animatedSprite_.SetPosition(GetPosition().x, GetPosition().y);
        initResult = animatedSprite_.SetSourceFileName(animatedSpriteFileName);
        if (initResult.HasErrors()) {
            initResult.AppendError("ExplosionAnimation::Init() : Error setting animated sprite file name.");
            return initResult;
        }

        initResult = animatedSprite_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("ExplosionAnimation::Init() : Error initialising animated sprite.");
            return initResult;
        }

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

