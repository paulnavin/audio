#pragma once

#include <Ui/DirectXInterface.hpp>

#include <Ui/Result.hpp>

class Engine2d;

class Text2d {

public:
    Text2d() = default;
    ~Text2d() = default;

public:
    Result Init(const Engine2d& engine);
    void Render();
    Result SetText(const std::wstring& newText);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};