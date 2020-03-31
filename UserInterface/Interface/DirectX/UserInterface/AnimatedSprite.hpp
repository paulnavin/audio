#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <UserInterface/AnimatedSpriteCycleData.hpp>
#include <UserInterface/Sprite.hpp>

class AnimatedSprite : public Sprite {

public:
    AnimatedSprite() = default;
    virtual ~AnimatedSprite() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;

public:
    Result SetSourceFileName(const std::string& fileName);
    void SetCycleData(const AnimatedSpriteCycleDataVector& newData);

    void UpdateAnimation(double deltaTime);					// updates the currently active animation cycle based on the passed time
    //void ChangeAnimation(unsigned int cycleToActivate);		// activated the specified animation cycle

private:
    AnimatedSpriteCycleDataVector cycleData_;
    unsigned int activeAnimation_;							// the currently active animation
    unsigned int activeAnimationFrame_;						// the currently active frame
    double animationFPS_ = 20.0;							// the animation's own FPS
    double frameTime_;										// the time the current frame has been displayed
};
