#include "ExplosionAnimation.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Platform/Stl.hpp>
#include <Resources/ResourceLocator.hpp>
#include <UserInterface/ModelPortal.hpp>

Result ExplosionAnimation::Init(ModelPortal* portal) {
    const ResourceLocator& resourceManager = portal->gfx->GetResourceLocator();

    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ExplosionAnimation::Init() : Error initialising base Element.");
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

    //animatedSprite_.SetParent(this);
    //animatedSprite_.SetCycleData(explosionAnimationCycles);
    //initResult = animatedSprite_.SetSourceFileName(animatedSpriteFileName);
    //if (initResult.HasErrors()) {
    //    initResult.AppendError("ExplosionAnimation::Init() : Error setting animated sprite file name.");
    //    return initResult;
    //}

    //initResult = animatedSprite_.Init(portal);
    //if (initResult.HasErrors()) {
    //    initResult.AppendError("ExplosionAnimation::Init() : Error initialising animated sprite.");
    //    return initResult;
    //}

    return Result{};
}

void ExplosionAnimation::Update(const double& /*dt*/) {
    //animatedSprite_.UpdateAnimation(dt);
}

void ExplosionAnimation::Render(const double& /*dt*/) {
    //animatedSprite_.Render(dt);
}

