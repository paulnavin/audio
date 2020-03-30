#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <UserInterface/Element.hpp>

class Ellipse2d : public Element {

public:
    Ellipse2d() = default;
    virtual ~Ellipse2d() = default;

public:
    Result Init(const GraphicsEngine& gfx) override;
    void Render(const double& dt) override;

public:
    Result SetColour(const Colour& newColour);

private:
    Result UpdateDetails();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
};
