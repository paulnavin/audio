#include <UserInterface/AnimatedSprite.hpp>

#include <Graphics/Engine2d.hpp>
#include <Platform/StringHandling.hpp>

Result AnimatedSprite::Init(ModelPortal* portal) {
    return Sprite::Init(portal);
}

void AnimatedSprite::Render(const double& /*dt*/) {
    //AnimatedSpriteCycleData cycleData = cycleData_[0];
    //D2D1_RECT_F destRect = { positionOnScreen_.x - (cycleData.width*cycleData.rotationCenterX),
    //                positionOnScreen_.y - (cycleData.height*cycleData.rotationCenterY),
    //                positionOnScreen_.x + (cycleData.width*(1.0f - cycleData.rotationCenterX)),
    //                positionOnScreen_.y + (cycleData.height*(1.0f - cycleData.rotationCenterY)) };
    //D2D1_SIZE_U size = bitmap_->GetPixelSize();

    //size_t startingRow = activeAnimationFrame_ / cycleData.framesPerRow;
    //size_t startingCol = activeAnimationFrame_ % cycleData.framesPerRow;

    //float startX = startingCol * (cycleData.width + cycleData.paddingWidth) + cycleData.borderPaddingWidth;
    //float startY = cycleData.borderPaddingHeight;
    //startY += (cycleData.height + cycleData.paddingHeight) * startingRow;

    //D2D1_RECT_F sourceRect = { startX, startY, startX + cycleData.width, startY + cycleData.height };

    //D2D1_BITMAP_INTERPOLATION_MODE interPol = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
    //float opacity = 1.0f;
    //deviceContext2d_->DrawBitmap(bitmap_.Get(), destRect, opacity, interPol, sourceRect);
}

Result AnimatedSprite::SetSourceFileName(const std::string& fileName) {
    // TODO: Fix this relationship.
    Sprite::SetBitmapName(fileName.c_str());
    return Result{};
}

void AnimatedSprite::SetCycleData(const AnimatedSpriteCycleDataVector& newData) {
    cycleData_ = newData;
}

void AnimatedSprite::UpdateAnimation(double deltaTimeInMs) {
    const double animationFpsInverse = (1.0 / animationFPS_);
    // update how long the currently active frame has been displayed
    frameTime_ += (deltaTimeInMs / 1000.0f);

    // check whether it is time to change to another frame
    if (frameTime_ > animationFpsInverse) {
        // the number of frames to increment is the integral result of frameTime / (1 / animationFPS), thus frameTime * animationFPS
        activeAnimationFrame_ += (unsigned int)(frameTime_ * animationFPS_);

        // use modulo computation to make sure to not jump past the last frame
        if (activeAnimationFrame_ >= cycleData_[activeAnimation_].numberOfFrames) {
            activeAnimationFrame_ = activeAnimationFrame_ % cycleData_[activeAnimation_].numberOfFrames;
        }
    }

    // set the frame time
    frameTime_ = std::fmod(frameTime_, animationFpsInverse);
}
