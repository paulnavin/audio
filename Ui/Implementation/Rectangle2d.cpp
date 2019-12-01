#include <Ui/Rectangle2d.hpp>

Result Rectangle2d::Init(
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& newDeviceContext2d) {
    deviceContext2d_ = newDeviceContext2d;
    return Result{};
}

Result Rectangle2d::Render() {
    Result renderResult{};

    // TODO: Move begin/end out into the Engine2d, so it's only called once per frame, not once per object.
    deviceContext2d_->BeginDraw();

    D2D1_RECT_F rect = { 100,100, 300, 500 };
    deviceContext2d_->FillRectangle(&rect, brush_.Get());

    HRESULT hr = deviceContext2d_->EndDraw();
    if (FAILED(hr)) {
        renderResult.AppendError("Rectangle2d::Render() : Could not finish drawing rectangle.");
    }

    return renderResult;
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
