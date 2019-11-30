#include "Engine3d.hpp"

#include "ShaderBuffer.hpp"
#include "Window.hpp"

const Microsoft::WRL::ComPtr<ID3D11Device>& Engine3d::GetDirect3dDevice() const {
    return device_;
}

const Microsoft::WRL::ComPtr<IDXGISwapChain>& Engine3d::GetDirect3dSwapChain() const {
    return swapChain_;
}

Result Engine3d::Init(const Window& newWindow) {
    windowHandle_ = newWindow.GetHandle();

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

    initResult = CreateDxgiResources();
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine3d::Init() : Couldn't create DXGI resources.");
        return initResult;
    }

    return initResult;
}

Result Engine3d::InitGraphics(const Model3d& model) {
    vertexCount_ = model.GetVertexCount();
    vertexType_ = model.GetVertexType();
    const size_t dataSize = sizeof(Vertex) * vertexCount_;

    D3D11_BUFFER_DESC bd;
    bd.ByteWidth = static_cast<UINT>(dataSize);
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA srd;
    srd.pSysMem = model.GetVertexData();
    srd.SysMemPitch = 0;
    srd.SysMemSlicePitch = 0;

    Result initResult{};
    HRESULT hr = device_->CreateBuffer(&bd, &srd, &vertexBuffer_);
    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::InitGraphics() : Couldn't create vertex buffer.");
    }

    return Result{};
}

void Engine3d::ClearBuffers() {
    float clearColour[] = { 0.0f, 0.0f, 0.2f, 1.0f };
    deviceContext_->ClearRenderTargetView(renderTargetView_.Get(), clearColour);
    deviceContext_->ClearDepthStencilView(depthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

Result Engine3d::Present() {
    Result presentResult{};
    HRESULT hr = swapChain_->Present(0, DXGI_PRESENT_DO_NOT_WAIT);
    if (FAILED(hr) && hr != DXGI_ERROR_WAS_STILL_DRAWING) {
        presentResult.AppendError("Direct3dController::Present() : Couldn't present rebuttal.");
        return presentResult;
    }

    deviceContext_->OMSetRenderTargets(1, renderTargetView_.GetAddressOf(), depthStencilView_.Get());

    return presentResult;
}

Result Engine3d::RenderVertices() {
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    deviceContext_->IASetVertexBuffers(0, 1, vertexBuffer_.GetAddressOf(), &stride, &offset);
    if (vertexType_ == VertexType::Point) {
        deviceContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    } else {
        deviceContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
    deviceContext_->Draw(static_cast<UINT>(vertexCount_), 0);

    return Result{};
}

Result Engine3d::Resize() {
    deviceContext_->ClearState();
    renderTargetView_ = nullptr;
    depthStencilView_ = nullptr;

    HRESULT hr = swapChain_->ResizeBuffers(0, 0, 0, colourFormat_, 0);
    Result resizeResult;
    if (FAILED(hr)) {
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't resize swap chain buffers.");
        return resizeResult;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    ID3D11Texture2D** backBufferPointer = backBuffer.GetAddressOf();
    const IID& textureId = __uuidof(ID3D11Texture2D);
    hr = swapChain_->GetBuffer(0, textureId, reinterpret_cast<void**>(backBufferPointer));
    if (FAILED(hr)) {
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't get the back buffer.");
        return resizeResult;
    }

    ID3D11Texture2D* backBufferTexture = backBuffer.Get();
    hr = device_->CreateRenderTargetView(backBufferTexture, 0, &renderTargetView_);
    if (FAILED(hr)) {
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't create a render target view.");
        return resizeResult;
    }

    D3D11_TEXTURE2D_DESC depthStencilDescriptor;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
    backBuffer->GetDesc(&depthStencilDescriptor);
    depthStencilDescriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDescriptor.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDescriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = device_->CreateTexture2D(&depthStencilDescriptor, nullptr, depthStencilBuffer.GetAddressOf());
    if (FAILED(hr)) {
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't create a depth/stencil buffer.");
        return resizeResult;
    }

    hr = device_->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, depthStencilView_.GetAddressOf());
    if (FAILED(hr)) {
        resizeResult.AppendError("Direct3dController::Resize() : Couldn't create a depth/stencil view.");
        return resizeResult;
    }

    // Actually activate the render target with the depth/stencil buffer.
    deviceContext_->OMSetRenderTargets(1, renderTargetView_.GetAddressOf(), depthStencilView_.Get());

    // set the viewport to the entire backbuffer
    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = static_cast<float>(depthStencilDescriptor.Width);
    viewPort.Height = static_cast<float>(depthStencilDescriptor.Height);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    deviceContext_->RSSetViewports(1, &viewPort);

    return InitShaders();
}

Result Engine3d::CreateDxgiResources() {
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

Result Engine3d::InitShaders() {
    Result initResult{};

    // Pixel shaders
    ShaderBuffer pixelShaderBuffer;

#ifdef _DEBUG
    initResult = LoadShader(L"../../Binaries/x64/Debug/pixelShader.cso", &pixelShaderBuffer);
#else
    initResult = LoadShader(L"../../Binaries/x64/Release/pixelShader.cso", &pixelShaderBuffer_);
#endif
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't load pixel shader.");
        return initResult;
    }

    HRESULT hr = device_->CreatePixelShader(pixelShaderBuffer.buffer, pixelShaderBuffer.size, nullptr, &pixelShader_);

    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::InitShaders() : Couldn't create pixel shader.");
        return initResult;
    }
    deviceContext_->PSSetShader(pixelShader_.Get(), NULL, 0);

    // Vertex shaders
    ShaderBuffer vertexShaderBuffer;

#ifdef _DEBUG
    initResult = LoadShader(L"../../Binaries/x64/Debug/vertexShader.cso", &vertexShaderBuffer);
#else
    initResult = LoadShader(L"../../Binaries/x64/Release/vertexShader.cso", &vertexShaderBuffer_);
#endif
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't load vertex shader.");
        return initResult;
    }

    hr = device_->CreateVertexShader(vertexShaderBuffer.buffer, vertexShaderBuffer.size, nullptr, &vertexShader_);
    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::InitShaders() : Couldn't create vertex shader.");
        return initResult;
    }

    deviceContext_->VSSetShader(vertexShader_.Get(), NULL, 0);

    // specify the input layout
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, POSITION_OFFSET, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, COLOUR_OFFSET, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // create the input layout
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
    hr = device_->CreateInputLayout(ied, ARRAYSIZE(ied), vertexShaderBuffer.buffer, vertexShaderBuffer.size, &inputLayout);
    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::InitShaders() : Couldn't create input layout.");
        return initResult;
    }

    // set active input layout
    deviceContext_->IASetInputLayout(inputLayout.Get());

    if (pixelShaderBuffer.buffer != nullptr) {
        delete[] pixelShaderBuffer.buffer;
        pixelShaderBuffer.buffer = nullptr;
    }

    if (vertexShaderBuffer.buffer != nullptr) {
        delete[] vertexShaderBuffer.buffer;
        vertexShaderBuffer.buffer = nullptr;
    }

    return initResult;
}

// Loads precompiled shaders from .cso objects.
Result Engine3d::LoadShader(const std::wstring& fileName, ShaderBuffer* shaderBuffer) {
    Result loadResult{};

    // open the file
    std::ifstream csoFile(fileName, std::ios::in | std::ios::binary | std::ios::ate);

    if (csoFile.is_open()) {
        // get shader size
        std::streamsize fileStreamSize = csoFile.tellg();
        shaderBuffer->size = static_cast<size_t>(fileStreamSize);

        // TODO: Handle read errors here?
        shaderBuffer->buffer = new byte[static_cast<size_t>(shaderBuffer->size)];
        csoFile.seekg(0, std::ios::beg);
        csoFile.read(reinterpret_cast<char*>(shaderBuffer->buffer), fileStreamSize);
        csoFile.close();
    } else {
        loadResult.AppendError("Engine3d::LoadShader() : Couldn't load shader.");
    }

    return loadResult;
}