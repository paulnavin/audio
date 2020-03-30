#include <Graphics/Engine2d.hpp>

#include <Graphics/Engine3d.hpp>
#include <Display/Window.hpp>

const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& Engine2d::GetDeviceContext2d() const {
    return deviceContext2d_;
}

const Microsoft::WRL::ComPtr<ID2D1Factory2>& Engine2d::GetFactory() const {
    return factory2d_;
}

const Microsoft::WRL::ComPtr<IWICImagingFactory>& Engine2d::GetImageFactory() const {
    return imageFactory_;
}

Result Engine2d::Init(const Window& newWindow, const Engine3d& newEngine) {
    windowHandle_ = newWindow.GetHandle();
    device3d_ = newEngine.GetDirect3dDevice();
    swapChain3d_ = newEngine.GetDirect3dSwapChain();

    // TODO: Check the CoInitialize() return value and deal with it?
    CoInitialize(NULL);

    Result initResult{};
    initResult = CreateDevice();
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine2d::Init() : Could not create device.");
        return initResult;
    }

    initResult = CreateImageFactory();
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine2d::Init() : Could not create image factory.");
        return initResult;
    }

    initResult = Resize();
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine2d::Init() : Could not resize.");
        return initResult;
    }

    return initResult;
}

Result Engine2d::PrepareForResize() {
    deviceContext2d_->SetTarget(nullptr);
    return Result{};
}

Result Engine2d::Resize() {
    Result resizeResult{};

    resizeResult = CreateBitmapRenderTarget();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("Engine2d::Resize() : Could not create bitmap render target.");
        return resizeResult;
    }

    return resizeResult;
}

void Engine2d::StartRender() {
    deviceContext2d_->BeginDraw();
}

void Engine2d::EndRender() {
    (void)deviceContext2d_->EndDraw();
}

Result Engine2d::CreateDevice() {
    Result createDeviceResult{};

    D2D1_FACTORY_OPTIONS options;
#ifdef _DEBUG
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
    options.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory2), &options, &factory2d_);
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

Result Engine2d::CreateBitmapRenderTarget() {
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

Result Engine2d::CreateImageFactory() {
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory2, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory2, &imageFactory_);

    Result creationResult{};
    if (FAILED(hr)) {
        creationResult.AppendError("Engine2d::CreateImageFactory() : Could not create WIC factory.");
    }

    return creationResult;
}
