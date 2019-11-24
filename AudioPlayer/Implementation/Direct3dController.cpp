#include "Direct3dController.hpp"

Result Direct3dController::Init(const HWND& newWindowHandle) {
    windowHandle_ = newWindowHandle;

    // D3D11_CREATE_DEVICE_BGRA_SUPPORT is needed to do both 3D and 2D.
    UINT deviceCreationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &device_, &featureLevel, &deviceContext_);

    Result initResult;
    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::Init() : Couldn't create Direct3D context.");
    } else if (featureLevel < D3D_FEATURE_LEVEL_11_0) {
        initResult.AppendError("Direct3dController::Init() : DirectX 11 isn't supported.");
    }

    return CreateDxgiResources();
}

Result Direct3dController::CreateDxgiResources() {
    colourFormat_ = DXGI_FORMAT_B8G8R8A8_UNORM;

    DXGI_SWAP_CHAIN_DESC swapChainDescriptor{};
    swapChainDescriptor.BufferDesc.Width = 0;                                                // Auto sized.
    swapChainDescriptor.BufferDesc.Height = 0;                                               // Auto sized.
    swapChainDescriptor.BufferDesc.RefreshRate.Numerator = 0;                                // Auto chosen.
    swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;                              // Auto chosen.
    swapChainDescriptor.BufferDesc.Format = colourFormat_;                                   // Default format.
    swapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  // Auto chosen.
    swapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                  // Auto chosen.
    swapChainDescriptor.SampleDesc.Count = 1;                                                // No anti-aliasing.
    swapChainDescriptor.SampleDesc.Quality = 0;                                              // No quality.  ;-p
    swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                       // Render to output buffer.
    swapChainDescriptor.BufferCount = 3;                                                     // 3 buffers in the swap chain.
    swapChainDescriptor.OutputWindow = windowHandle_;                                        // Set the output window to our Window handle passed in.
    swapChainDescriptor.Windowed = true;                                                     // Not full screen by default (switch later).
    swapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;                          // Swapping a buffer discards it after it has been presented.
    swapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                      // Switching modes is okay.

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice{};
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter{};
    Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory{};

    Result dxgiResult{};
    HRESULT hr = device_.As(&dxgiDevice);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Direct3dController::CreateDxgiResources() : Couldn't get DXGI device.");
        return dxgiResult;
    }

    IDXGIAdapter** adapterPointer = dxgiAdapter.GetAddressOf();
    hr = dxgiDevice->GetAdapter(adapterPointer);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Direct3dController::CreateDxgiResources() : Couldn't get DXGI adapter.");
        return dxgiResult;
    }

    const IID& factoryId = __uuidof(IDXGIFactory);
    hr = dxgiAdapter->GetParent(factoryId, &dxgiFactory);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Direct3dController::CreateDxgiResources() : Couldn't get DXGI factory.");
        return dxgiResult;
    }

    IDXGISwapChain** swapChainPointer = swapChain_.GetAddressOf();
    ID3D11Device* devicePointer = device_.Get();
    hr = dxgiFactory->CreateSwapChain(devicePointer, &swapChainDescriptor, swapChainPointer);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Direct3dController::CreateDxgiResources() : Couldn't create swap chain.");
        return dxgiResult;
    }

    Result resizeResult = Resize();
    if (resizeResult.HasErrors()) {
        dxgiResult.AppendError("Direct3dController::CreateDxgiResources() : Couldn't resize swap chain.");
        return dxgiResult;
    }

    return Result{};
}

Result Direct3dController::Present() {
    HRESULT hr = swapChain_->Present(0, DXGI_PRESENT_DO_NOT_WAIT);
    if (FAILED(hr) && hr != DXGI_ERROR_WAS_STILL_DRAWING) {
        Result presentResult{};
        presentResult.AppendError("Direct3dController::Present() : Couldn't present rebuttal.");
        return presentResult;
    }

    return Result{};
}

Result Direct3dController::Resize() {
    HRESULT hr = swapChain_->ResizeBuffers(0, 0, 0, colourFormat_, 0);
    if (FAILED(hr)) {
        Result resizeResult;
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't resize swap chain buffers.");
        return resizeResult;
    }

    return Result{};
}
