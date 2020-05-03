#include <Graphics/Text.hpp>

#include <Graphics/Dimension2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <Graphics/TextResource.hpp>
#include <Platform/StringHandling.hpp>

Result Text::Init(GraphicsEngine* gfx, TextResource* resource) {
    textResource_ = resource;
    brush_ = resource->GetBrush();

    const Engine2d& engine = gfx->GetEngine2d();
    deviceContext2d_ = engine.GetDeviceContext2d();

    const TextManager2d& textManager = gfx->GetTextManager2d();
    writeFactory_ = textManager.GetWriteFactory();

    return Result{};
}

void Text::Render() {
    if (!textLayout_) {
        return;
    }

    deviceContext2d_->DrawTextLayout(textPosition_, textLayout_.Get(), brush_.Get());
}

void Text::RenderText(const std::string& text) {
    SetText(text);
    Render();
}

void Text::SetText(const std::string& newText) {
    StringUtil::StringToWideString(text_, newText.c_str(), MAX_STRING_LENGTH);

    UpdateTextLayout();
}

void Text::SetPosition(const Position2d& position) {
    textPosition_ = D2D1::Point2F(position.x, position.y);
}

void Text::SetDimensions(const Dimension2d& dimensions) {
    textHeight_ = dimensions.height;
    textWidth_ = dimensions.width;
}

void Text::UpdateTextLayout() {
    size_t stringLength = wcslen(text_);

    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = textResource_->GetTextFormat();

    // TODO: Error handling here.
    writeFactory_->CreateTextLayout(
        text_,
        static_cast<UINT32>(stringLength),
        textFormat.Get(),
        textWidth_,
        textHeight_,
        &textLayout_);
}