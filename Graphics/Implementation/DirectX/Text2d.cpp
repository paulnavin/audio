#include <Graphics/Text2d.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/TextManager2d.hpp>

Text2d::Text2d(Element* parent) : Element(parent) {
}

Result Text2d::Init(const Engine2d& engine, const TextManager2d& textManager) {
    deviceContext2d_ = engine.GetDeviceContext2d();

    textFormat_ = textManager.GetFpsTextFormat();
    brush_ = textManager.GetFpsBrush();
    writeFactory_ = textManager.GetWriteFactory();

    return Result{};
}

void Text2d::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);

    if (!textLayout_) {
        return;
    }

    textPosition_ = D2D1::Point2F(position_.x, position_.y);
    deviceContext2d_->DrawTextLayout(textPosition_, textLayout_.Get(), brush_.Get());
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
        static_cast<float>(dimensions_.width),
        static_cast<float>(dimensions_.height),
        &textLayout_);

    if (FAILED(hr)) {
        setResult.AppendError("Text2d::SetText() : Could not recreate text layout.");
    }

    return setResult;
}
