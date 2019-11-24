#include "Direct2dController.hpp"

Result Direct2dController::Init(
        const HWND& newWindowHandle,
        const Microsoft::WRL::ComPtr<ID3D11Device>& newDevice3d,
        const Microsoft::WRL::ComPtr<IDXGISwapChain>& new3dSwapChain) {
    windowHandle_ = newWindowHandle;
    device3d_ = newDevice3d;
    swapChain3d_ = new3dSwapChain;

    Result initResult{};
    initResult = CreateDevice();
    if (initResult.HasErrors()) {
        initResult.AppendError("Direct2dController::Init() : Could not create device.");
        return initResult;
    }

    initResult = CreateBitmapRenderTarget();
    if (initResult.HasErrors()) {
        initResult.AppendError("Direct2dController::Init() : Could not create bitmap render target.");
        return initResult;
    }

    initResult = InitialiseTextFormats();
    if (initResult.HasErrors()) {
        initResult.AppendError("Direct2dController::Init() : Could not initialise text formats.");
        return initResult;
    }
    
    return SetFpsValue(0);
}

Result Direct2dController::RenderFps() {
    Result renderResult{};

    deviceContext2d_->BeginDraw();

    deviceContext2d_->DrawTextLayout(D2D1::Point2F(5.0f, 5.0f), fpsTextLayout_.Get(), fpsBrush_.Get());
    
    HRESULT hr = deviceContext2d_->EndDraw();
    if (FAILED(hr)) {
        renderResult.AppendError("Direct2dController::RenderFps() : Could not finish drawing FPS.");
    }

    return renderResult;
}

Result Direct2dController::SetFpsValue(const int64_t& newFps) {
    Result setResult{};

    std::wostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << newFps << std::endl;

    // TODO: Should this window size retrieval actually be in the Window?
    RECT rect;
    BOOL resultOfGet = GetWindowRect(windowHandle_, &rect);
    if (resultOfGet == 0) {
        setResult.AppendError("Direct2dController::SetFpsValue() : Could not get width of window for FPS.");
    }

    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

    HRESULT hr = writeFactory_->CreateTextLayout(
        fpsString.str().c_str(),
        static_cast<UINT32>(fpsString.str().size()),
        fpsTextFormat_.Get(),
        static_cast<float>(width),
        static_cast<float>(height),
        &fpsTextLayout_);

    if (FAILED(hr)) {
        setResult.AppendError("Direct2dController::SetFpsValue() : Could not recreate text layout for FPS.");
    }

    return setResult;
}

Result Direct2dController::CreateDevice() {
    Result createDeviceResult{};

    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &writeFactory_);
    if (FAILED(hr)) {
        createDeviceResult.AppendError("Direct2dController::CreateDevice() : Could not create Write Factory.");
        return createDeviceResult;
    }

    D2D1_FACTORY_OPTIONS options;
#ifdef _DEBUG
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
    options.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory2), &options, &factory2d_);
    if (FAILED(hr)) {
        createDeviceResult.AppendError("Direct2dController::CreateDevice() : Could not create 2D Factory.");
        return createDeviceResult;
    }

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
    hr = device3d_.Get()->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice);
    if (FAILED(hr)) {
        createDeviceResult.AppendError("Direct2dController::CreateDevice() : Could not get DXGI device from 3D device.");
        return createDeviceResult;
    }

    hr = factory2d_->CreateDevice(dxgiDevice.Get(), &device2d_);
    if (FAILED(hr)) {
        createDeviceResult.AppendError("Direct2dController::CreateDevice() : Could not create 2D device from DXGI device.");
        return createDeviceResult;
    }

    hr = device2d_->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext2d_);
    if (FAILED(hr)) {
        createDeviceResult.AppendError("Direct2dController::CreateDevice() : Could not create Direct2D device context.");
        return createDeviceResult;
    }

    return createDeviceResult;
}

Result Direct2dController::CreateBitmapRenderTarget() {
    Result createRenderTargetResult{};

    D2D1_BITMAP_PROPERTIES1 bitmapProperties;
    bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
    bitmapProperties.dpiX = 96.0f;
    bitmapProperties.dpiY = 96.0f;
    bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
    bitmapProperties.colorContext = nullptr;

    Microsoft::WRL::ComPtr<IDXGISurface> dxgiBuffer;
    HRESULT hr = swapChain3d_->GetBuffer(0, __uuidof(IDXGISurface), &dxgiBuffer);
    if (FAILED(hr)) {
        createRenderTargetResult.AppendError("Direct2dController::CreateBitmapRenderTarget() : Could not get 3D back buffer from 3D swap chain.");
        return createRenderTargetResult;
    }

    Microsoft::WRL::ComPtr<ID2D1Bitmap1> targetBitmap;
    hr = deviceContext2d_->CreateBitmapFromDxgiSurface(dxgiBuffer.Get(), &bitmapProperties, &targetBitmap);
    if (FAILED(hr)) {
        createRenderTargetResult.AppendError("Direct2dController::CreateBitmapRenderTarget() : Could not create 2D bitmap from DXGI surface.");
        return createRenderTargetResult;
    }

    deviceContext2d_->SetTarget(targetBitmap.Get());

    return createRenderTargetResult;
}

Result Direct2dController::InitialiseTextFormats() {
    Result initTextFormatResult{};

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue), &fpsBrush_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("Direct2dController::InitialiseTextFormats() : Could not create brush for FPS text.");
        return initTextFormatResult;
    }

    hr = writeFactory_.Get()->CreateTextFormat(L"Lucida Console", nullptr, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-GB", &fpsTextFormat_);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("Direct2dController::InitialiseTextFormats() : Could not create text format for FPS.");
        return initTextFormatResult;
    }

    hr = fpsTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("Direct2dController::InitialiseTextFormats() : Could not set text alignment for FPS text format.");
        return initTextFormatResult;
    }

    hr = fpsTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (FAILED(hr)) {
        initTextFormatResult.AppendError("Direct2dController::InitialiseTextFormats() : Could not set paragraph alignment for FPS text format.");
        return initTextFormatResult;
    }

    return initTextFormatResult;
}

