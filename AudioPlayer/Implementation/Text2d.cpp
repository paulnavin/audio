#include "Text2d.hpp"

Result Text2d::Init(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& newDeviceContext2d,
        const Microsoft::WRL::ComPtr<IDWriteTextFormat>& newTextFormat,
        const Microsoft::WRL::ComPtr<IDWriteFactory2>& newWriteFactory,
        const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& newBrush) {
    deviceContext2d_ = newDeviceContext2d;
    fpsTextFormat_ = newTextFormat;
    fpsBrush_ = newBrush;
    writeFactory_ = newWriteFactory;
    
    return SetFpsValue(0);
}

Result Text2d::RenderFps() {
    Result renderResult{};

    deviceContext2d_->BeginDraw();

    deviceContext2d_->DrawTextLayout(D2D1::Point2F(5.0f, 5.0f), fpsTextLayout_.Get(), fpsBrush_.Get());

    HRESULT hr = deviceContext2d_->EndDraw();
    if (FAILED(hr)) {
        renderResult.AppendError("Direct2dController::RenderFps() : Could not finish drawing FPS.");
    }

    return renderResult;
}

Result Text2d::SetFpsValue(const int64_t& newFps) {
    Result setResult{};

    std::wostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << newFps << std::endl;

    // TODO: Get these from the window or a parent object instead.
    static constexpr LONG MAX_TEXT_WIDTH = 1000;
    static constexpr LONG MAX_TEXT_HEIGHT = 600;

    HRESULT hr = writeFactory_->CreateTextLayout(
        fpsString.str().c_str(),
        static_cast<UINT32>(fpsString.str().size()),
        fpsTextFormat_.Get(),
        static_cast<float>(MAX_TEXT_WIDTH),
        static_cast<float>(MAX_TEXT_HEIGHT),
        &fpsTextLayout_);

    if (FAILED(hr)) {
        setResult.AppendError("Direct2dController::SetFpsValue() : Could not recreate text layout for FPS.");
    }

    return setResult;
}
