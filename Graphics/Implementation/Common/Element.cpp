#include <Graphics/Element.hpp>

Element::Element(Element* parent) {
    parent_ = parent;
    if (parent_ == nullptr) {
        // TODO: Add ability to add a Window as parent, and get dimensions from Window.
        dimensions_.height = 900;
        dimensions_.width = 1600;
    }
}

void Element::SetDimensions(const float& heightInPixels, const float& widthInPixels) {
    dimensions_.height = heightInPixels;
    dimensions_.width = widthInPixels;
}

void Element::SetPosition(const float& newX, const float& newY) {
    position_.x = newX;
    position_.y = newY;
}

void Element::SetDimensionsAsPercentage(const float& height, const float& width) {
    if (parent_ == nullptr) {
        // TODO: Add ability to set percentage of Window.
        return;
    }

    dimensions_.height = parent_->dimensions_.height * (height / 100.0f);
    dimensions_.width = parent_->dimensions_.width * (width / 100.0f);
}
