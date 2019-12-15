#pragma once

#include <Ui/DirectXInterface.hpp>

#include <Ui/Result.hpp>
#include <Ui/TextManager2d.hpp>

class Engine3d;
class Model2d;
class Window;

class Engine2d {
public:
    Engine2d() = default;
    ~Engine2d() = default;

public:
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& GetDeviceContext2d() const;
    const TextManager2d& GetTextManager() const;

public:
    Result Init(const Window& newWindow, const Engine3d& newEngine);
    Result InitGraphics(Model2d* model);
    void RenderModel();

private:
    Result CreateDevice();
    Result CreateBitmapRenderTarget();

private:
    Microsoft::WRL::ComPtr<ID3D11Device> device3d_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain3d_;

    Microsoft::WRL::ComPtr<ID2D1Device1> device2d_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1Factory2> factory2d_;

    TextManager2d textManager2d_;

    Model2d* model_;

    HWND windowHandle_;
};
