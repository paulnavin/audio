#include <Ui/Text2d.hpp>

#include <Ui/Engine2d.hpp>
#include <Ui/TextManager2d.hpp>

Result Text2d::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();

    TextManager2d textManager = engine.GetTextManager();
    textFormat_ = textManager.GetFpsTextFormat();
    brush_ = textManager.GetFpsBrush();
    writeFactory_ = textManager.GetWriteFactory();

    return Result{};
}

void Text2d::Render() {
    if (!textLayout_) {
        return;
    }

    deviceContext2d_->DrawTextLayout(D2D1::Point2F(5.0f, 5.0f), textLayout_.Get(), brush_.Get());
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