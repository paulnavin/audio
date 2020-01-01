#include <Graphics/Ellipse2d.hpp>

#include <Graphics/Engine2d.hpp>

Ellipse2d::Ellipse2d(Element* parent) : Element(parent) {

}

Result Ellipse2d::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();
    return Result{};
}

void Ellipse2d::Render(const double&) {
    Result renderResult{};
    D2D1_POINT_2F centre = { position_.x, position_.y};
    D2D1_ELLIPSE ellipse = { centre, dimensions_.width, dimensions_.height };
    deviceContext2d_->DrawEllipse(&ellipse, brush_.Get(), 5);
}

Result Ellipse2d::SetColour(const Colour& newColour) {
    colour_ = newColour;

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(colour_.red, colour_.green, colour_.blue, colour_.alpha), &brush_);
    Result setResult{};
    if (FAILED(hr)) {
        setResult.AppendError("Ellipse2d::SetColour() : Could not set colour for Ellipse 2D.");
    }
    return setResult;
}
