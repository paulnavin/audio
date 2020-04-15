#include <Graphics/TextResource.hpp>

#include <Display/ErrorDisplay.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <StringHandling/StringUtil.hpp>

Result TextResource::Init(GraphicsEngine* gfx/*, const char* fontName*/) {
    const Engine2d& engine = gfx->GetEngine2d();
    const TextManager2d& textManager = gfx->GetTextManager2d();
    deviceContext2d_ = engine.GetDeviceContext2d();

    textFormat_ = textManager.GetFpsTextFormat();
    brush_ = textManager.GetFpsBrush();
    writeFactory_ = textManager.GetWriteFactory();

    return Result{};
}

void TextResource::Render() {
    if (!textLayout_) {
        return;
    }

    deviceContext2d_->DrawTextLayout(textPosition_, textLayout_.Get(), brush_.Get());
}

void TextResource::SetText(const std::string& newText) {
    text_ = newText;

    UpdateDetails();
}

void TextResource::SetPosition(const Position2d& position) {
    textPosition_ = D2D1::Point2F(position.x, position.y);
}

void TextResource::SetDimensions(const Dimension2d& dimensions) {
    textHeight_ = dimensions.height;
    textWidth_ = dimensions.width;
}

void TextResource::UpdateDetails() {
    // TODO: Get these from the window or a parent object instead.
    static constexpr LONG MAX_TEXT_WIDTH = 1000;
    static constexpr LONG MAX_TEXT_HEIGHT = 600;

    std::wstring outputText = StringUtil::StringToWideString(text_);

    // TODO: Error handling here.
    writeFactory_->CreateTextLayout(
        outputText.c_str(),
        static_cast<UINT32>(outputText.size()),
        textFormat_.Get(),
        textWidth_,
        textHeight_,
        &textLayout_);
}
