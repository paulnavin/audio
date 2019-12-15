#include <Ui/Ellipse2d.hpp>

#include <Ui/Engine2d.hpp>

Result Ellipse2d::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();
    return Result{};
}

void Ellipse2d::Render() {
    Result renderResult{};
    D2D1_POINT_2F centre = { 700.0f, 500.0f };
    D2D1_ELLIPSE ellipse = { centre, 200, 75 };
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
