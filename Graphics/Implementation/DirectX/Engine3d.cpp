#include <Graphics/Engine3d.hpp>

#include <Graphics/ShaderBuffer.hpp>
#include <UserInterface/Window.hpp>
#include <Utility/ResourceManager.hpp>
#include <Utility/StringUtil.hpp>

const Microsoft::WRL::ComPtr<ID3D11Device>& Engine3d::GetDirect3dDevice() const {
    return device_;
}

const Microsoft::WRL::ComPtr<IDXGISwapChain>& Engine3d::GetDirect3dSwapChain() const {
    return swapChain_;
}

Engine3d::~Engine3d() {
    delete[] supportedDisplayModes_;
}

Result Engine3d::Init(const Window& newWindow, const ResourceManager& resourceManager) {
    windowHandle_ = newWindow.GetHandle();

    std::string shaderFileName = resourceManager.GetShaderDirectoryName();
    pixelShaderFileName_ = StringUtil::StringToWideString(shaderFileName);
    vertexShaderFileName_ = pixelShaderFileName_;

    pixelShaderFileName_.append(L"PixelShader.cso");
    vertexShaderFileName_.append(L"VertexShader.cso");

    // D3D11_CREATE_DEVICE_BGRA_SUPPORT is needed to do both 3D and 2D.
    UINT deviceCreationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &device_, &featureLevel, &deviceContext_);

    Result initResult;
    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::Init() : Couldn't create Direct3D context.");
    } else if (featureLevel < D3D_FEATURE_LEVEL_11_0) {
        initResult.AppendError("Engine3d::Init() : DirectX 11 isn't supported.");
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
        initResult.AppendError("Engine3d::InitGraphics() : Couldn't create vertex buffer.");
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
        presentResult.AppendError("Engine3d::Present() : Couldn't present rebuttal.");
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
    Result resizeResult;
    DXGI_MODE_DESC currentModeDescription = supportedDisplayModes_[currentDisplayMode_];
    DXGI_MODE_DESC zeroRefreshRate = currentModeDescription;
    zeroRefreshRate.RefreshRate.Numerator = 0;
    zeroRefreshRate.RefreshRate.Denominator = 0;

    BOOL alreadyInFullScreenMode = false;
    swapChain_->GetFullscreenState(&alreadyInFullScreenMode, NULL);

    if (currentlyInFullScreenMode_ != alreadyInFullScreenMode) {
        if (alreadyInFullScreenMode) {
            // switch from window to full screen -> Microsoft recommends resizing the target before going into fullscreen
            HRESULT hr = swapChain_->ResizeTarget(&zeroRefreshRate);
            if (FAILED(hr)) {
                resizeResult.AppendError("Engine3d::Resize() : Couldn't resize target.");
                return resizeResult;
            }

            hr = swapChain_->SetFullscreenState(true, nullptr);
            if (FAILED(hr)) {
                resizeResult.AppendError("Engine3d::Resize() : Couldn't switch to full screen mode.");
                return resizeResult;
            }
        } else {
            // switched to windowed -> simply set fullscreen mode to false
            HRESULT hr = swapChain_->SetFullscreenState(false, nullptr);
            if (FAILED(hr)) {
                resizeResult.AppendError("Engine3d::Resize() : Couldn't switch to windowed mode.");
                return resizeResult;
            }

            // recompute client area and set new window size
            RECT rect = { 0, 0, (long)currentModeDescription.Width,  (long)currentModeDescription.Height };
            hr = AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
            if (FAILED(hr)) {
                resizeResult.AppendError("Engine3d::Resize() : Couldn't resize window.");
                return resizeResult;
            }
            SetWindowPos(windowHandle_, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);
        }

        // change fullscreen mode
        currentlyInFullScreenMode_ = !currentlyInFullScreenMode_;
    }

    HRESULT hr = swapChain_->ResizeTarget(&zeroRefreshRate);
    if (FAILED(hr)) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't resize target.");
        return resizeResult;
    }

    deviceContext_->ClearState();
    renderTargetView_ = nullptr;
    depthStencilView_ = nullptr;

    // Should this FORMAT_UNKNOWN be colourFormat_?
    hr = swapChain_->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    if (FAILED(hr)) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't resize swap chain buffers.");
        return resizeResult;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    ID3D11Texture2D** backBufferPointer = backBuffer.GetAddressOf();
    const IID& textureId = __uuidof(ID3D11Texture2D);
    hr = swapChain_->GetBuffer(0, textureId, reinterpret_cast<void**>(backBufferPointer));
    if (FAILED(hr)) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't get the back buffer.");
        return resizeResult;
    }

    ID3D11Texture2D* backBufferTexture = backBuffer.Get();
    hr = device_->CreateRenderTargetView(backBufferTexture, 0, &renderTargetView_);
    if (FAILED(hr)) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't create a render target view.");
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
        resizeResult.AppendError("Engine3d::Resize() : Couldn't create a depth/stencil buffer.");
        return resizeResult;
    }

    hr = device_->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, depthStencilView_.GetAddressOf());
    if (FAILED(hr)) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't create a depth/stencil view.");
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

    resizeResult = InitShaders();
    if (resizeResult.HasErrors()) {
        resizeResult.AppendError("Engine3d::Resize() : Couldn't initialise shaders.");
    }

    return resizeResult;
}

Result Engine3d::ToggleFullScreen() {
    Result toggleResult{};
    // TODO: De-duplicate the code in these if statements.
    if (currentlyInFullScreenMode_ == FALSE) {
        // Switch to full screen.
        HRESULT hr = swapChain_->SetFullscreenState(true, nullptr);
        if (FAILED(hr)) {
            toggleResult.AppendError("Engine3d::ToggleFullScreen() : Couldn't set full screen state on swap chain.");
        }
        currentlyInFullScreenMode_ = true;
    } else {
        // Switch to window mode.
        HRESULT hr = swapChain_->SetFullscreenState(false, nullptr);
        if (FAILED(hr)) {
            toggleResult.AppendError("Engine3d::ToggleFullScreen() : Couldn't set full screen state on swap chain.");
        }
        currentlyInFullScreenMode_ = false;
    }
    return toggleResult;
}

void Engine3d::NextDisplayConfig() {
    currentDisplayMode_ = (currentDisplayMode_ + 1) % supportedDisplayModeCount_;
}

void Engine3d::PreviousDisplayConfig() {
    currentDisplayMode_ = (currentDisplayMode_ - 1) % supportedDisplayModeCount_;
}

void Engine3d::ResetDisplayConfig() {
    currentDisplayMode_ = 107;
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
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't get DXGI device.");
        return dxgiResult;
    }

    IDXGIAdapter** adapterPointer = dxgiAdapter.GetAddressOf();
    hr = dxgiDevice->GetAdapter(adapterPointer);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't get DXGI adapter.");
        return dxgiResult;
    }

    const IID& factoryId = __uuidof(IDXGIFactory);
    hr = dxgiAdapter->GetParent(factoryId, &dxgiFactory);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't get DXGI factory.");
        return dxgiResult;
    }

    // Turn off ALT-Enter and Print Screen being handled internally.
    hr = dxgiFactory->MakeWindowAssociation(windowHandle_, DXGI_MWA_NO_WINDOW_CHANGES);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't turn off associations.");
        return dxgiResult;
    }

    IDXGISwapChain** swapChainPointer = swapChain_.GetAddressOf();
    ID3D11Device* devicePointer = device_.Get();
    hr = dxgiFactory->CreateSwapChain(devicePointer, &swapChainDescriptor, swapChainPointer);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't create swap chain.");
        return dxgiResult;
    }

    // Use MakeWindowAssociation() to turn off DirectX direct Alt+Enter handling.
    // Annoyingly you can't just reuse the factory from above, you have to get the
    // factory again from the swap chain.
    // https://www.gamedev.net/forums/topic/634235-dxgidisabling-altenter/?do=findComment&comment=4999990
    Microsoft::WRL::ComPtr<IDXGIFactory> parentFactory;
    hr = swapChain_->GetParent(__uuidof(parentFactory), (void **)&parentFactory);
    if (FAILED(hr)) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't get swap chain parent.");
        return dxgiResult;
    }
    
    parentFactory->MakeWindowAssociation(windowHandle_, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

    dxgiResult = InitSupportedDisplayModes();

    if (startInFullscreen_ == true) {
        hr = swapChain_->SetFullscreenState(true, nullptr);
        if (FAILED(hr)) {
            dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't switch to full screen mode.");
            return dxgiResult;
        }
        currentlyInFullScreenMode_ = true;
    }

    dxgiResult = Resize();
    if (dxgiResult.HasErrors()) {
        dxgiResult.AppendError("Engine3d::CreateDxgiResources() : Couldn't resize swap chain.");
        return dxgiResult;
    }

    return dxgiResult;
}

Result Engine3d::InitShaders() {
    Result initResult{};

    // Pixel shaders
    ShaderBuffer pixelShaderBuffer;

    initResult = LoadShader(pixelShaderFileName_, &pixelShaderBuffer);
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't load pixel shader.");
        return initResult;
    }

    HRESULT hr = device_->CreatePixelShader(pixelShaderBuffer.buffer, pixelShaderBuffer.size, nullptr, &pixelShader_);

    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't create pixel shader.");
        return initResult;
    }
    deviceContext_->PSSetShader(pixelShader_.Get(), NULL, 0);

    // Vertex shaders
    ShaderBuffer vertexShaderBuffer;

    initResult = LoadShader(vertexShaderFileName_, &vertexShaderBuffer);
    if (initResult.HasErrors()) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't load vertex shader.");
        return initResult;
    }

    hr = device_->CreateVertexShader(vertexShaderBuffer.buffer, vertexShaderBuffer.size, nullptr, &vertexShader_);
    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::InitShaders() : Couldn't create vertex shader.");
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
        initResult.AppendError("Engine3d::InitShaders() : Couldn't create input layout.");
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

Result Engine3d::InitSupportedDisplayModes() {
    Result initResult{};

    IDXGIOutput *output = nullptr;
    HRESULT hr = swapChain_->GetContainingOutput(&output);
    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::InitSupportedDisplayModes() : Couldn't get output adapter.");
        return initResult;
    }

    UINT supportedModeCount = 0;
    hr = output->GetDisplayModeList(colourFormat_, 0, &supportedModeCount, NULL);
    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::InitSupportedDisplayModes() : Couldn't get supported display mode count.");
        return initResult;
    }

    supportedDisplayModeCount_ = static_cast<size_t>(supportedModeCount);
    currentDisplayMode_ = supportedDisplayModeCount_ - 1;
    supportedDisplayModes_ = new DXGI_MODE_DESC[supportedDisplayModeCount_];
    ZeroMemory(supportedDisplayModes_, sizeof(DXGI_MODE_DESC) * supportedModeCount);

    hr = output->GetDisplayModeList(colourFormat_, 0, &supportedModeCount, supportedDisplayModes_);
    if (FAILED(hr)) {
        initResult.AppendError("Engine3d::InitSupportedDisplayModes() : Couldn't get supported display modes.");
        return initResult;
    }

    output->Release();

    return initResult;
}
