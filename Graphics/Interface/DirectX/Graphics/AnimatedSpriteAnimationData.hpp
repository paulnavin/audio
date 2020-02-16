#pragma once

#include <Graphics/AnimatedSpriteCycleData.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

class Engine2d;
class TextManager2d;

class AnimatedSpriteAnimationData {

public:
    AnimatedSpriteAnimationData() = default;
    ~AnimatedSpriteAnimationData() = default;

public:
    const AnimatedSpriteCycleDataVector& GetCycleData() const;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager);
    Result SetSourceFileName(const std::string& fileName);
    Result SetAnimatedSpriteCycleData(const AnimatedSpriteCycleDataVector& newCycleData);

private:
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> spriteSheet_;	// the image containing all the animations
    AnimatedSpriteCycleDataVector cycleData_;			// the cycle data for all the different cycles in this animation
};
