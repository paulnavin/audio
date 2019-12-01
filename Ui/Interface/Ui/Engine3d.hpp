#pragma once

#include <Ui/DirectXInterface.hpp>
#include <Ui/Model3d.hpp>
#include <Ui/Result.hpp>
#include <Ui/ShaderBuffer.hpp>
#include <Ui/StlWrapper.hpp>
#include <Ui/Vertex.hpp>

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
    Result InitGraphics(const Model3d& model);
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
    size_t vertexCount_;
    VertexType vertexType_;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader_;
    HWND windowHandle_;
};