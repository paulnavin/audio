#pragma once

#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>

#include <Utility/Result.hpp>

class Engine2d;

class Rectangle2d {

public:
    Rectangle2d() = default;
    ~Rectangle2d() = default;

public:
    Result Init(const Engine2d& engine);
    void Render();
    Result SetColour(const Colour& newColour);
    Result SetDimensions(const float& x, const float& y, const float& width, const float& height);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> highlightBrush_;
    D2D1_RECT_F rectangle_;
};
