#include "Text2d.hpp"

Result Text2d::Init(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& newDeviceContext2d,
        const Microsoft::WRL::ComPtr<IDWriteTextFormat>& newTextFormat,
        const Microsoft::WRL::ComPtr<IDWriteFactory2>& newWriteFactory,
        const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& newBrush) {
    deviceContext2d_ = newDeviceContext2d;
    textFormat_ = newTextFormat;
    brush_ = newBrush;
    writeFactory_ = newWriteFactory;

    return Result{};
}

Result Text2d::RenderFps() {
    Result renderResult{};

    if (!textLayout_) {
        return renderResult;
    }

    deviceContext2d_->BeginDraw();

    deviceContext2d_->DrawTextLayout(D2D1::Point2F(5.0f, 5.0f), textLayout_.Get(), brush_.Get());

    HRESULT hr = deviceContext2d_->EndDraw();
    if (FAILED(hr)) {
        renderResult.AppendError("Text2d::RenderFps() : Could not finish drawing text.");
    }

    return renderResult;
}

Result Text2d::SetText(const std::wstring& newText) {
    Result setResult{};

    // TODO: Get these from the window or a parent object instead.
    static constexpr LONG MAX_TEXT_WIDTH = 1000;
    static constexpr LONG MAX_TEXT_HEIGHT = 600;

    HRESULT hr = writeFactory_->CreateTextLayout(
        newText.c_str(),
        static_cast<UINT32>(newText.size()),
        textFormat_.Get(),
        static_cast<float>(MAX_TEXT_WIDTH),
        static_cast<float>(MAX_TEXT_HEIGHT),
        &textLayout_);

    if (FAILED(hr)) {
        setResult.AppendError("Text2d::SetText() : Could not recreate text layout.");
    }

    return setResult;
}
