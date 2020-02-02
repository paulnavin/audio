#include <Graphics/Rectangle2d.hpp>

#include <Graphics/Engine2d.hpp>

Rectangle2d::Rectangle2d(Element* parent) : Element(parent) {

}

Result Rectangle2d::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();
    return Result{};
}

void Rectangle2d::Render(const double&) {
    rectangle_ = { position_.x, position_.y, position_.x + dimensions_.width, position_.y + dimensions_.height };
    deviceContext2d_->FillRectangle(&rectangle_, brush_.Get());
}

void Rectangle2d::OnClick() {
    if (colour_.alpha > 0.7f) {
        SetColour(Colour{ 1.0f, 1.0f, 1.0f, 0.5f });
    } else {
        SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
    }
}

Result Rectangle2d::SetColour(const Colour& newColour) {
    colour_ = newColour;

    D2D1::ColorF mainColour = D2D1::ColorF(colour_.red, colour_.green, colour_.blue, colour_.alpha);
    D2D1::ColorF fadeColour = D2D1::ColorF(colour_.red, colour_.green, colour_.blue, 0.0f);

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(mainColour, &brush_);
    Result setResult{};
    if (FAILED(hr)) {
        setResult.AppendError("Rectangle2dInternals::SetColour() : Could not create brush for rectangle.");
    }

    Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> stopCollection;
    D2D1_GRADIENT_STOP stops[] = {
        { 0.0f, D2D1::ColorF(fadeColour) },
        { 0.5f, D2D1::ColorF(mainColour)},
        { 1.0f, D2D1::ColorF(fadeColour) }
    };
    hr = deviceContext2d_->CreateGradientStopCollection(stops, _countof(stops), stopCollection.GetAddressOf());
    if (FAILED(hr)) {
        setResult.AppendError("Rectangle2dInternals::SetColour() : Could not create highlight stops.");
    }

    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES linearGradientBrushProperties = {};
    hr = deviceContext2d_->CreateLinearGradientBrush(linearGradientBrushProperties, stopCollection.Get(), highlightBrush_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        setResult.AppendError("Rectangle2dInternals::SetColour() : Could not create linear gradient brush.");
    }

    return setResult;
}
