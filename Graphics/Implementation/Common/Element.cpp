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

const Position2d& Element::GetAbsolutePosition() const {
    return positionOnScreen_;
}

const Dimension2d& Element::GetDimensions() const {
    return dimensionsOnScreen_;
}

void Element::SetDimensions(const float& widthInPixels, const float& heightInPixels) {
    dimensionsOnScreen_.height = heightInPixels;
    dimensionsOnScreen_.width = widthInPixels;
    percentageDimensions_ = false;
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

void Element::SetPositionAsPercentage(const float& newX, const float& newY) {
    positionAsPercentage_.x = newX;
    positionAsPercentage_.y = newY;
    percentagePosition_ = true;

    if (IsInitialised()) {
        UpdateDimensionsOnScreen();
    }
}

void Element::SetDimensionsAsPercentage(const float& width, const float& height) {
    dimensions_.height = height;
    dimensions_.width = width;
    percentageDimensions_ = true;

    if (IsInitialised()) {
        UpdateDimensionsOnScreen();
    }
}

void Element::UpdatePositionOnScreen() {
    if (parent_ != nullptr) {
        if (percentagePosition_ == true) {
            if (positionAsPercentage_.x >= 0.0f) {
                positionOnScreen_.x = parent_->positionOnScreen_.x + (positionAsPercentage_.x * parent_->dimensionsOnScreen_.width / 100.0f);
            } else {
                positionOnScreen_.x = (parent_->positionOnScreen_.x + parent_->dimensionsOnScreen_.width) + (positionAsPercentage_.x * (parent_->positionOnScreen_.x + parent_->dimensionsOnScreen_.width) / 100.0f);
            }
            if (positionAsPercentage_.y >= 0.0f) {
                positionOnScreen_.y = parent_->positionOnScreen_.y + (positionAsPercentage_.y * parent_->dimensionsOnScreen_.height / 100.0f);
            } else {
                positionOnScreen_.y = (parent_->positionOnScreen_.y + parent_->dimensionsOnScreen_.height) + (positionAsPercentage_.y * (parent_->positionOnScreen_.y + parent_->dimensionsOnScreen_.height) / 100.0f);
            }
        } else {
            positionOnScreen_.x = parent_->positionOnScreen_.x + position_.x;
            positionOnScreen_.y = parent_->positionOnScreen_.y + position_.y;
        }
    } else {
        positionOnScreen_.x = position_.x;
        positionOnScreen_.y = position_.y;
    }
}

void Element::UpdateDimensionsOnScreen() {
    if (percentageDimensions_ == true) {
        dimensionsOnScreen_.height = parent_->dimensionsOnScreen_.height * (dimensions_.height / 100.0f);
        dimensionsOnScreen_.width = parent_->dimensionsOnScreen_.width * (dimensions_.width / 100.0f);
    }
}
