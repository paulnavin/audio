#pragma once

#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Model3d.hpp>
#include <Graphics/ShaderBuffer.hpp>
#include <Graphics/Vertex.hpp>
#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

class Window;

class Engine3d {
public:
    // TODO: Define move constructor/assignment?
    Engine3d() = default;
    ~Engine3d();

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
    Result ToggleFullScreen();

private:
    Result CreateDxgiResources();
    Result InitShaders();
    Result LoadShader(const std::wstring& fileName, ShaderBuffer* shaderBuffer);
    Result InitSupportedDisplayModes();

private:
    DXGI_FORMAT colourFormat_;
    BOOL currentlyInFullScreenMode_ = false;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext_;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView_;
    bool startInFullscreen_ = false;
    DXGI_MODE_DESC* supportedDisplayModes_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer_;
    size_t vertexCount_;
    VertexType vertexType_;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader_;
    HWND windowHandle_;
};
