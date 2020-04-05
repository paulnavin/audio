#include <UserInterface/Element.hpp>

Result Element::Init(ModelPortal* portal) {
    chell_ = portal;
    UpdatePositionOnScreen();
    UpdateDimensionsOnScreen();
    isInitialised_ = true;
    return Result{};
}

void Element::Render(const double& dt) {
    for (Element* element : children_) {
        if (element->isEnabled_ == true) {
            element->Render(dt);
        }
    }
}

bool Element::OnClick() { return false; }

void Element::HandleCommand(const Command::Id& /*command*/) { }

void Element::HandleMouseMove(const float& /*x*/, const float& /*y*/) {}

const bool Element::IsEnabled() const {
    return isEnabled_;
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

void Element::AddChild(Element* newChild) {
    children_.push_back(newChild);
}

void Element::OnMouseClicked(const float& x, const float& y) {
    Position2d position;
    Dimension2d dimensions;
    for (Element* element : children_) {
        position = element->GetAbsolutePosition();
        dimensions = element->GetDimensions();
        if ((x >= position.x) &&
            (x <= position.x + dimensions.width) &&
            (y >= position.y) &&
            (y <= position.y + dimensions.height)) {
            // TODO: Swap the OnClick() order with the OnMouseClicked() order?  So children go first?
            bool clickResult = element->OnClick();
            if (clickResult == false) {
                element->OnMouseClicked(x, y);
            }
        }
    }
}
void Element::SetDimensions(const float& widthInPixels, const float& heightInPixels) {
    dimensionsOnScreen_.height = heightInPixels;
    dimensionsOnScreen_.width = widthInPixels;
    percentageDimensions_ = false;
}

void Element::SetEnabled(const bool& enabled) {
    isEnabled_ = enabled;
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
