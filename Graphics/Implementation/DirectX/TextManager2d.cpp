#include <Graphics/TextManager2d.hpp>

#include <Graphics/Engine2d.hpp>
#include <Display/Window.hpp>

const Microsoft::WRL::ComPtr<IDWriteFactory2>& TextManager2d::GetWriteFactory() const {
    return writeFactory_;
}

Result TextManager2d::Init(const Window& newWindow, const Engine2d& newEngine) {
    windowHandle_ = newWindow.GetHandle();
    deviceContext2d_ = newEngine.GetDeviceContext2d();

    Result initResult = InitialiseFactory();
    if (initResult.HasErrors()) {
        initResult.AppendError("TextManager2d::Init() : Could not initialise write factory.");
    }

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
