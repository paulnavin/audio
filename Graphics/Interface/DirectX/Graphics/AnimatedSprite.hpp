#pragma once

#include <Graphics/AnimatedSpriteCycleData.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Sprite.hpp>
#include <ErrorHandling/Result.hpp>

class Engine2d;
class TextManager2d;

class AnimatedSprite : public Sprite {

public:
    AnimatedSprite(Element* parent);
    ~AnimatedSprite() = default;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager) override;
    void Render(const double& dt) override;
    void OnClick() override;

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
