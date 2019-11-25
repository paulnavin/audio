#pragma once

#include "DirectXInterface.hpp"

#include "Result.hpp"

class Window;

class Engine3d {
public:
    // TODO: Define move constructor/assignment?
    Engine3d() = default;
    ~Engine3d() = default;

public:
    const Microsoft::WRL::ComPtr<ID3D11Device>& GetDirect3dDevice() const;
    const Microsoft::WRL::ComPtr<IDXGISwapChain>& GetDirect3dSwapChain() const;

public:
    Result Init(const Window& newWindow);
    void ClearBuffers();
    Result Present();
    Result Resize();

private:
    Result CreateDxgiResources();

private:
    DXGI_FORMAT colourFormat_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;
    HWND windowHandle_;
};
