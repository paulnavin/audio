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
    Result SetText(const std::wstring& newText);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
