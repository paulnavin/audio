#pragma once

#include <Ui/DirectXInterface.hpp>

#include <Ui/Result.hpp>

class Engine2d;
class Window;

class TextManager2d {

public:
    TextManager2d() = default;
    ~TextManager2d() = default;

public:
    // TODO: Support multiple brushes and text formats. Also, maybe read them from file. :-)
    const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>&     GetFpsBrush() const;
    const Microsoft::WRL::ComPtr<IDWriteTextFormat>&        GetFpsTextFormat() const;
    const Microsoft::WRL::ComPtr<IDWriteFactory2>&          GetWriteFactory() const;

public:
    Result Init(const Window& newWindow, const Engine2d& newEngine);
    Result InitialiseFactory();
    Result InitialiseTextFormats();

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> fpsBrush_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    fpsTextFormat_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
    HWND windowHandle_;
};
