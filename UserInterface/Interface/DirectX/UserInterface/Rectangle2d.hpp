#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <UserInterface/Element.hpp>

class Rectangle2d : public Element {

public:
    Rectangle2d() = default;
    virtual ~Rectangle2d() = default;

public:
    Result Init(const GraphicsEngine& gfx) override;
    void Render(const double& dt) override;

public:
    const Colour& GetColour() const;
    Result SetColour(const Colour& newColour);

private:
    Result UpdateDetails();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> highlightBrush_;
    D2D1_RECT_F rectangle_;
};
