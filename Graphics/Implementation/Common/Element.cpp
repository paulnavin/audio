#include <Graphics/Element.hpp>

Result Element::Init(const GraphicsEngine& /*gfx*/) {
    UpdatePositionOnScreen();
    UpdateDimensionsOnScreen();
    isInitialised_ = true;
    return Result{};
}

const bool Element::IsInitialised() const {
    return isInitialised_;
}

const Position2d& Element::GetPosition() const {
    return position_;
}

const Dimension2d& Element::GetDimensions() const {
    return dimensionsOnScreen_;
}

void Element::SetDimensions(const float& heightInPixels, const float& widthInPixels) {
    dimensionsOnScreen_.height = heightInPixels;
    dimensionsOnScreen_.width = widthInPixels;
    relativeDimensions_ = false;
}

void Element::SetParent(const Element* parent) {
    parent_ = parent;
}

void Element::SetPosition(const float& newX, const float& newY) {
    position_.x = newX;
    position_.y = newY;

    if (IsInitialised()) {
        UpdatePositionOnScreen();
    }
}

void Element::SetDimensionsAsPercentage(const float& height, const float& width) {
    dimensions_.height = height;
    dimensions_.width = width;
    relativeDimensions_ = true;

    if (IsInitialised()) {
        UpdateDimensionsOnScreen();
    }
}

void Element::UpdatePositionOnScreen() {
    if (parent_ != nullptr) {
        positionOnScreen_.x = parent_->positionOnScreen_.x + position_.x;
        positionOnScreen_.y = parent_->positionOnScreen_.y + position_.y;
    } else {
        positionOnScreen_.x = position_.x;
        positionOnScreen_.y = position_.y;
    }
}

void Element::UpdateDimensionsOnScreen() {
    if ((relativeDimensions_ == true) &&(parent_ != nullptr)) {
        dimensionsOnScreen_.height = parent_->dimensionsOnScreen_.height * (dimensions_.height / 100.0f);
        dimensionsOnScreen_.width = parent_->dimensionsOnScreen_.width * (dimensions_.width / 100.0f);
    }
}
