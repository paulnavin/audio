#pragma once

#include "StlWrapper.hpp"
#include "DirectXInterface.hpp"

#include "Result.hpp"
#include "ShaderBuffer.hpp"
#include "Vertex.hpp"

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
    Result InitGraphics();
    void ClearBuffers();
    Result Present();
    Result RenderVertices();
    Result Resize();

private:
    Result CreateDxgiResources();
    Result InitShaders();
    Result LoadShader(const std::wstring& fileName, ShaderBuffer* shaderBuffer);

private:
    DXGI_FORMAT colourFormat_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext_;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader_;
    HWND windowHandle_;

    // TODO: Move this stuff out of the Engine, into the App.
    static constexpr size_t STAR_FIELD_SIZE = 1000;
    std::array<Vertex, STAR_FIELD_SIZE> starField;
};
