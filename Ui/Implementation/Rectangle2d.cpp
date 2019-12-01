#include <Ui/Rectangle2d.hpp>

#include <Ui/Engine2d.hpp>

Result Rectangle2d::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();
    return Result{};
}

void Rectangle2d::Render() {
    Result renderResult{};

    D2D1_RECT_F rect = { 100,100, 300, 500 };
    deviceContext2d_->FillRectangle(&rect, brush_.Get());
}

Result Rectangle2d::SetColour(const Colour& newColour) {
    colour_ = newColour;

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGoldenrodYellow), &brush_);
    Result setResult{};
    if (FAILED(hr)) {
        setResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not create brush for rectangle.");
    }
    return setResult;
}
