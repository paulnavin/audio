#include <Graphics/Model2d.hpp>

void Model2d::Render(const double& dt) {
    for (Element* element : elements_) {
        element->Render(dt);
    }
}

void Model2d::OnMouseClicked(const float& x, const float& y) {
    Position2d position;
    Dimension2d dimensions;
    for (Element* element : elements_) {
        position = element->GetPosition();
        dimensions = element->GetDimensions();
        if ((x >= position.x) &&
            (x <= position.x + dimensions.width) &&
            (y >= position.y) &&
            (y <= position.y + dimensions.height)) {
            element->OnClick();
        }
    }
}

void Model2d::SetFps(const int64_t& newFps) {
    fps_ = newFps;
}

void Model2d::SetShowFps(const bool show) {
    showFps_ = show;

    if (fpsElement_ == nullptr) {
        return;
    }

    if (showFps_ == true) {
        elements_.insert(fpsElement_);
    } else {
        elements_.erase(fpsElement_);
    }
}

void Model2d::SetFpsElement(Element* newElement) {
    fpsElement_ = newElement;
    SetShowFps(showFps_);
}

void Model2d::SetMousePosition(const int32_t& x, const int32_t& y) {
    mouseXPosition_ = x;
    mouseYPosition_ = y;
}

void Model2d::SetShowMousePosition(const bool show) {
    showMousePosition_ = show;

    if (mousePositionElement_ == nullptr) {
        return;
    }

    if (showMousePosition_ == true) {
        elements_.insert(mousePositionElement_);
    } else {
        elements_.erase(mousePositionElement_);
    }
}

void Model2d::SetMousePositionElement(Element* newElement) {
    mousePositionElement_ = newElement;
    SetShowMousePosition(showMousePosition_);
}
