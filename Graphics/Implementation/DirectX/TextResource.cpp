#include <Graphics/TextResource.hpp>

#include <Graphics/Dimension2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <Graphics/TextStyle.hpp>
#include <Platform/StringHandling.hpp>

Result TextResource::Init(GraphicsEngine* gfx, const TextStyle& style) {
    const TextManager2d& textManager = gfx->GetTextManager2d();
    deviceContext2d_ = gfx->GetEngine2d().GetDeviceContext2d();
    Microsoft::WRL::ComPtr<IDWriteFactory2> writeFactory = textManager.GetWriteFactory();

    Result initTextFormatResult{};
    HRESULT hr;
    D2D1::ColorF colour = { style.colour.red, style.colour.green, style.colour.blue, style.colour.alpha };
    hr = deviceContext2d_->CreateSolidColorBrush(colour, &brush_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextResource::Init() : Could not create brush for FPS text.");
        return initTextFormatResult;
    }

    static const size_t MAX_FONT_NAME_LENGTH = 512;
    wchar_t fontName[MAX_FONT_NAME_LENGTH];

    StringUtil::StringToWideString(fontName, style.fontName, MAX_FONT_NAME_LENGTH);
    hr = writeFactory.Get()->CreateTextFormat(fontName, nullptr, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, style.size, L"en-GB", &textFormat_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextResource::Init() : Could not create text format for FPS.");
        return initTextFormatResult;
    }

    if (style.horizontalAlignment == TextStyle::HorizontalAlignment::Centre) {
        hr = textFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    } else if (style.horizontalAlignment == TextStyle::HorizontalAlignment::Start) {
        hr = textFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    } else {
        hr = textFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
    }
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextResource::Init() : Could not set text alignment for FPS text format.");
        return initTextFormatResult;
    }

    hr = textFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextResource::Init() : Could not set paragraph alignment for FPS text format.");
        return initTextFormatResult;
    }

    return Result{};
}

const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& TextResource::GetBrush() {
    return brush_;
}

const Microsoft::WRL::ComPtr<IDWriteTextFormat>& TextResource::GetTextFormat() {
    return textFormat_;
}
