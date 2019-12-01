#pragma once

#include <Ui/Colour.hpp>
#include <Ui/DirectXInterface.hpp>

#include <Ui/Result.hpp>

class Rectangle2d {

public:
    Rectangle2d() = default;
    ~Rectangle2d() = default;

public:
    Result Init(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext1>& newDeviceContext2d);
    Result Render();
    Result SetColour(const Colour& newColour);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
};
