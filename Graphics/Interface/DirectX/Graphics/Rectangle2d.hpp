#pragma once

#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>

#include <Utility/Result.hpp>

class Engine2d;

class Rectangle2d : public Element {

public:
    Rectangle2d(Element* parent);
    ~Rectangle2d() = default;

public:
    Result Init(const Engine2d& engine) override;
    void Render(const double& dt);
    Result SetColour(const Colour& newColour);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> highlightBrush_;
    D2D1_RECT_F rectangle_;
};
