#pragma once

#include "DirectXInterface.hpp"

#include <sstream>
#include "Result.hpp"

class Engine2d {
public:
    Engine2d() = default;
    ~Engine2d() = default;

public:
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& GetDeviceContext2d() const;

public:
    Result Init(const HWND& newWindowHandle, const Microsoft::WRL::ComPtr<ID3D11Device>& newDevice3d, const Microsoft::WRL::ComPtr<IDXGISwapChain>& new3dSwapChain);

private:
    Result CreateDevice();
    Result CreateBitmapRenderTarget();

private:
    Microsoft::WRL::ComPtr<ID3D11Device> device3d_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain3d_;

    Microsoft::WRL::ComPtr<ID2D1Device1> device2d_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1Factory2> factory2d_;

    HWND windowHandle_;
};
