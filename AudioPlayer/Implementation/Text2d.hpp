#pragma once

#include "DirectXInterface.hpp"

#include "Result.hpp"

class Text2d {

public:
    Text2d() = default;
    ~Text2d() = default;

public:
    Result Init(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& newDeviceContext2d,
        const Microsoft::WRL::ComPtr<IDWriteTextFormat>& newTextFormat,
        const Microsoft::WRL::ComPtr<IDWriteFactory2>& newWriteFactory,
        const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& newBrush);
    Result RenderFps();
    Result SetFpsValue(const int64_t& newFps);

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> fpsBrush_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    fpsTextFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    fpsTextLayout_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
