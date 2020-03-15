#include <Graphics/Text2d.hpp>

#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/TextManager2d.hpp>

Result Text2d::Init(const GraphicsEngine& gfx) {
    const Engine2d& engine = gfx.GetEngine2d();
    const TextManager2d& textManager = gfx.GetTextManager2d();
    deviceContext2d_ = engine.GetDeviceContext2d();

    textFormat_ = textManager.GetFpsTextFormat();
    brush_ = textManager.GetFpsBrush();
    writeFactory_ = textManager.GetWriteFactory();

    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("Text2d::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Element::Init(gfx);
}

void Text2d::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);

    if (!textLayout_) {
        return;
    }

    // TODO: Update the position by overriding SetPosition().
    textPosition_ = D2D1::Point2F(positionOnScreen_.x, positionOnScreen_.y);
    deviceContext2d_->DrawTextLayout(textPosition_, textLayout_.Get(), brush_.Get());
}

Result Text2d::SetText(const std::wstring& newText) {
    text_ = newText;
    
    if (IsInitialised() == true) {
        return UpdateDetails();
    }
    return Result{};
}

Result Text2d::UpdateDetails() {
    Result updateResult{};
    // TODO: Get these from the window or a parent object instead.
    static constexpr LONG MAX_TEXT_WIDTH = 1000;
    static constexpr LONG MAX_TEXT_HEIGHT = 600;

    HRESULT hr = writeFactory_->CreateTextLayout(
        text_.c_str(),
        static_cast<UINT32>(text_.size()),
        textFormat_.Get(),
        static_cast<float>(dimensionsOnScreen_.width),
        static_cast<float>(dimensionsOnScreen_.height),
        &textLayout_);

    if (FAILED(hr)) {
        updateResult.AppendError("Text2d::SetText() : Could not recreate text layout.");
    }
    return updateResult;
}
