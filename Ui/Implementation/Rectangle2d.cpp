#include <Ui/Rectangle2d.hpp>

#include <Ui/Engine2d.hpp>

class Rectangle2dInternals {
public:
    Result Init(const Engine2d& engine) {
        deviceContext2d_ = engine.GetDeviceContext2d();
        rectangle_ = { 300, 300, 50, 50 };
        return Result{};
    }

    void Render() {
        Result renderResult{};

        deviceContext2d_->FillRectangle(&rectangle_, brush_.Get());
    }

    Result SetColour(const Colour& newColour) {
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

    Result SetDimensions(const float& x, const float& y, const float& width, const float& height) {
        rectangle_ = { x, y, x + width, y + height };
        return Result{};
    }

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> highlightBrush_;
    D2D1_RECT_F rectangle_;
};

Rectangle2d::Rectangle2d() {
    internals_ = new Rectangle2dInternals();
}

Rectangle2d::~Rectangle2d() {
    delete internals_;
}

Result Rectangle2d::Init(const Engine2d& engine) {
    return internals_->Init(engine);
}

void Rectangle2d::Render() {
    internals_->Render();
}

Result Rectangle2d::SetColour(const Colour& newColour) {
    return internals_->SetColour(newColour);
}

Result Rectangle2d::SetDimensions(const float& x, const float& y, const float& width, const float& height) {
    return internals_->SetDimensions(x, y, width, height);
}
