#include <Graphics/TextManager2d.hpp>

#include <Graphics/Engine2d.hpp>
#include <UserInterface/Window.hpp>

const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& TextManager2d::GetFpsBrush() const {
    return fpsBrush_;
}

const Microsoft::WRL::ComPtr<IDWriteTextFormat>& TextManager2d::GetFpsTextFormat() const {
    return fpsTextFormat_;
}

const Microsoft::WRL::ComPtr<IDWriteFactory2>& TextManager2d::GetWriteFactory() const {
    return writeFactory_;
}

Result TextManager2d::Init(const Window& newWindow, const Engine2d& newEngine) {
    windowHandle_ = newWindow.GetHandle();
    deviceContext2d_ = newEngine.GetDeviceContext2d();

    Result initResult = InitialiseFactory();
    if (initResult.HasErrors()) {
        initResult.AppendError("TextManager2d::Init() : Could not initialise write factory.");
        return initResult;
    }

    // TODO: Is this right, that TextManager's resize is called by the Engine2d?
    //initResult = Resize();
    //if (initResult.HasErrors()) {
    //    initResult.AppendError("TextManager2d::Init() : Could not resize.");
    //    return initResult;
    //}

    return initResult;
}

Result TextManager2d::InitialiseFactory() {
    Result initFactoryResult{};
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &writeFactory_);
    if (FAILED(hr)) {
        initFactoryResult.AppendError("TextManager2d::CreateDevice() : Could not create Write Factory.");
        return initFactoryResult;
    }

    deviceContext2d_->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

    return initFactoryResult;
}

Result TextManager2d::InitialiseTextFormats() {
    Result initTextFormatResult{};

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGoldenrodYellow), &fpsBrush_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not create brush for FPS text.");
        return initTextFormatResult;
    }

    hr = writeFactory_.Get()->CreateTextFormat(L"Lucida Console", nullptr, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-GB", &fpsTextFormat_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not create text format for FPS.");
        return initTextFormatResult;
    }

    hr = fpsTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not set text alignment for FPS text format.");
        return initTextFormatResult;
    }

    hr = fpsTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not set paragraph alignment for FPS text format.");
        return initTextFormatResult;
    }

    return initTextFormatResult;
}

Result TextManager2d::Resize() {
    Result resizeResult{};

    resizeResult = InitialiseTextFormats();

    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("TextManager2d::Resize() : Could not initialise text formats.");
    }

    return resizeResult;
}