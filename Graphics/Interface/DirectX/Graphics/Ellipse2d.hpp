#pragma once

#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>

#include <ErrorHandling/Result.hpp>

class Engine2d;

class Ellipse2d : public Element {

public:
    Ellipse2d(Element* parent);
    ~Ellipse2d() = default;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager) override;
    void Render(const double& dt) override;

public:
    Result SetColour(const Colour& newColour);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
};
