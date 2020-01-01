#pragma once

#include <Graphics/DirectXInterface.hpp>

#include <Utility/Result.hpp>

class Engine2d;

class Text2d {

public:
    Text2d() = default;
    ~Text2d() = default;

public:
    Result Init(const Engine2d& engine);
    void Render();
    Result SetPosition(const float& newX, const float& newY);
    Result SetText(const std::wstring& newText);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    D2D1_POINT_2F                                textPosition_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
